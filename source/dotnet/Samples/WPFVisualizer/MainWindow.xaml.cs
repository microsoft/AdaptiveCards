using System;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using AC = AdaptiveCards;
using Newtonsoft.Json;
using Microsoft.Win32;
using System.IO;
using System.Diagnostics;
using AdaptiveCards;
using System.Windows.Threading;
using System.Speech.Synthesis;
using ICSharpCode.AvalonEdit.Document;
using System.Xml.Serialization;
using System.Reflection;
using AdaptiveCards.Rendering;
using System.Windows.Media;
using AdaptiveCards.Rendering.Config;
using System.ComponentModel;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using System.Threading.Tasks;
using System.Windows.Media.Effects;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private AC.AdaptiveCard _card;
        private SpeechSynthesizer _synth;
        private DispatcherTimer _timer;
        private bool _dirty = false;

        public MainWindow()
        {
            foreach (var type in typeof(HostConfig).Assembly.GetExportedTypes().Where(t => t.Namespace == typeof(HostConfig).Namespace))
            {
                TypeDescriptor.AddAttributes(type, new ExpandableObjectAttribute());
            }

            InitializeComponent();

            _synth = new SpeechSynthesizer();
            _synth.SelectVoiceByHints(VoiceGender.Female, VoiceAge.Adult);
            _synth.SetOutputToDefaultAudioDevice();
            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(1);
            _timer.Tick += _timer_Tick;
            _timer.Start();

            var hostConfig = new HostConfig();
            hostConfig.AdaptiveCard.BackgroundColor = Colors.WhiteSmoke.ToString();
            this.Renderer = new XamlRendererExtended(hostConfig, this.Resources, _onAction, _OnMissingInput);
            this.hostConfigEditor.SelectedObject = hostConfig;

            foreach (var style in Directory.GetFiles(@"..\..\..\..\..\..\samples\Themes", "*.json"))
            {
                this.hostConfigs.Items.Add(new ComboBoxItem()
                {
                    Content = Path.GetFileNameWithoutExtension(style),
                    Tag = style
                });
            }
        }

        private void Config_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            _dirty = true;
        }

        private DocumentLine errorLine;

        public XamlRendererExtended Renderer { get; set; }

        public HostConfig HostConfig
        {
            get
            {
                return (HostConfig)this.hostConfigEditor.SelectedObject;
            }
            set
            {
                this.hostConfigEditor.SelectedObject = value;
            }
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            if (_dirty)
            {
                _dirty = false;
                try
                {
                    this.cardError.Children.Clear();

                    if (this.textBox.Text.Trim().StartsWith("<"))
                    {
                        var types = Assembly.GetAssembly(typeof(AdaptiveCard)).ExportedTypes.Where(t => t.IsAssignableFrom(typeof(TypedElement))).ToArray();
                        XmlSerializer ser = new XmlSerializer(typeof(AdaptiveCard), extraTypes: types);
                        _card = (AdaptiveCard)ser.Deserialize(new StringReader(this.textBox.Text));
                    }
                    else
                    {

                        _card = JsonConvert.DeserializeObject<AC.AdaptiveCard>(this.textBox.Text);
                    }

                    this.cardGrid.Children.Clear();
                    if (_card != null)
                    {
                        this.Renderer = new XamlRendererExtended(this.HostConfig, this.Resources, _onAction, _OnMissingInput);
                        var uiCard = this.Renderer.RenderAdaptiveCard(_card, hostConfig: HostConfig);
                        uiCard.Effect = new DropShadowEffect()
                        {
                            BlurRadius = 15,
                            Direction = -90,
                            RenderingBias = RenderingBias.Quality,
                            ShadowDepth = 2
                        };
 
                        this.cardGrid.Children.Add(uiCard);
                    }
                }
                catch (Exception err)
                {
                    HandleParseError(err);
                }
            }
        }

        private void _OnMissingInput(object sender, MissingInputEventArgs args)
        {
            MessageBox.Show($"Required input is missing.");
            args.FrameworkElement.Focus();
        }

        private void HandleParseError(Exception err)
        {
            var textBlock = new System.Windows.Controls.TextBlock()
            {
                Text = err.Message,
                TextWrapping = TextWrapping.Wrap,
                Style = this.Resources["Error"] as Style
            };
            var button = new Button() { Content = textBlock };
            button.Click += Button_Click;
            this.cardError.Children.Add(button);

            int iPos = err.Message.IndexOf("line ");
            if (iPos > 0)
            {
                iPos += 5;
                int iEnd = err.Message.IndexOf(",", iPos);

                int line = 0;
                if (int.TryParse(err.Message.Substring(iPos, iEnd - iPos), out line))
                {
                    iPos = err.Message.IndexOf("position ");
                    if (iPos > 0)
                    {
                        iPos += 9;
                        iEnd = err.Message.IndexOf(".", iPos);
                        int position = 0;
                        if (int.TryParse(err.Message.Substring(iPos, iEnd - iPos), out position))
                        {
                            errorLine = this.textBox.Document.GetLineByNumber(Math.Min(line, this.textBox.Document.LineCount));
                        }
                    }
                }
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (this.errorLine != null)
                this.textBox.Select(this.errorLine.Offset, this.errorLine.Length);
        }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            _dirty = true;
        }

        private void loadButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                this.textBox.Text = File.ReadAllText(dlg.FileName).Replace("\t", "  ");
                _dirty = true;
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var binding = new CommandBinding(NavigationCommands.GoToPage, GoToPage, CanGoToPage);
            // Register CommandBinding for all windows.
            CommandManager.RegisterClassCommandBinding(typeof(Window), binding);

        }

        private void _onAction(object sender, ActionEventArgs e)
        {
            if (e.Action is AC.OpenUrlAction)
            {
                AC.OpenUrlAction action = (AC.OpenUrlAction)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.ShowCardAction)
            {
                ShowCardAction action = (AC.ShowCardAction)e.Action;
                if (HostConfig.Actions.ShowCard.ActionMode == AC.Rendering.Config.ShowCardActionMode.Popup)
                {
                    ShowCardWindow dialog = new ShowCardWindow(action.Title, action, this.Resources);
                    dialog.Owner = this;
                    dialog.ShowDialog();
                }
            }
            else if (e.Action is AC.SubmitAction)
            {
                AC.SubmitAction action = (AC.SubmitAction)e.Action;
                System.Windows.MessageBox.Show(this, JsonConvert.SerializeObject(e.Data, Newtonsoft.Json.Formatting.Indented), "SubmitAction");
            }
            else if (e.Action is AC.HttpAction)
            {
                AC.HttpAction action = (AC.HttpAction)e.Action;
                StringBuilder sb = new StringBuilder();
                sb.AppendLine($"HEADERS={JsonConvert.SerializeObject(action.Headers)}");
                sb.AppendLine($"BODY={action.Body}");
                sb.AppendLine($"DATA={e.Data}");
                System.Windows.MessageBox.Show(this, sb.ToString(), $"HttpAction {action.Method} {action.Url}");
            }
        }

        private void GoToPage(object sender, ExecutedRoutedEventArgs e)
        {
            if (e.Parameter is string)
            {
                string name = e.Parameter as string;
                if (!String.IsNullOrWhiteSpace(name))
                    Process.Start(name);
            }
        }

        private void CanGoToPage(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private async void viewImage_Click(object sender, RoutedEventArgs e)
        {
            var renderer = new ImageRenderer(new HostConfig(), this.Resources);
            var imageStream = renderer.RenderAdaptiveCard(this._card, 480);
            string path = System.IO.Path.GetRandomFileName() + ".png";
            using (FileStream fileStream = new FileStream(path, FileMode.Create))
            {
                await imageStream.CopyToAsync(fileStream);
            }
            Process.Start(path);
        }

        private void speak_Click(object sender, RoutedEventArgs e)
        {
            var card = JsonConvert.DeserializeObject<AC.AdaptiveCard>(this.textBox.Text);
            _synth.SpeakAsyncCancelAll();
            if (card.Speak != null)
                _synth.SpeakSsmlAsync(FixSSML(card.Speak));
            else
            {
                foreach (var element in card.Body)
                {
                    if (element.Speak != null)
                    {
                        _synth.SpeakSsmlAsync(FixSSML(element.Speak));
                    }
                }
            }
        }

        private string FixSSML(String speak)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("<speak version=\"1.0\"");
            sb.AppendLine(" xmlns =\"http://www.w3.org/2001/10/synthesis\"");
            sb.AppendLine(" xml:lang=\"en-US\">");
            sb.AppendLine(speak);
            sb.AppendLine("</speak>");
            return sb.ToString();
        }

        private void textBox_TextChanged(object sender, EventArgs e)
        {
            _dirty = true;
        }

        private void toJson_Click(object sender, RoutedEventArgs e)
        {
            if (this.textBox.Text.Trim().StartsWith("<"))
            {
                try
                {
                    this.textBox.Text = JsonConvert.SerializeObject(_card, Formatting.Indented);
                }
                catch (Exception err)
                {
                    Debug.Print(err.ToString());
                    HandleParseError(err);
                }
            }
        }

        private void toXml_Click(object sender, RoutedEventArgs e)
        {
            if (this.textBox.Text.Trim().StartsWith("{"))
            {
                try
                {

                    var types = Assembly.GetAssembly(typeof(AdaptiveCard)).ExportedTypes.Where(t => t.IsAssignableFrom(typeof(TypedElement))).ToArray();
                    XmlSerializer ser = new XmlSerializer(typeof(AdaptiveCard), extraTypes: types);
                    StringWriter writer = new StringWriter();
                    ser.Serialize(writer, _card);
                    this.textBox.Text = writer.ToString();
                }
                catch (Exception err)
                {
                    Debug.Print(err.ToString());
                    HandleParseError(err);
                }
            }
        }

        private void options_TextChanged(object sender, EventArgs e)
        {
            _dirty = true;
        }

        private void toggleOptions_Click(object sender, RoutedEventArgs e)
        {
            if (this.hostConfigEditor.Visibility == Visibility.Visible)
                this.hostConfigEditor.Visibility = Visibility.Collapsed;
            else
                this.hostConfigEditor.Visibility = Visibility.Visible;
        }

        private void options_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            _dirty = true;
        }

        private void hostConfigs_Selected(object sender, RoutedEventArgs e)
        {
            var config = JsonConvert.DeserializeObject<HostConfig>(File.ReadAllText((string)((ComboBoxItem)this.hostConfigs.SelectedItem).Tag));
            this.HostConfig = config;
            _dirty = true;
        }

        private void loadConfig_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                var json = File.ReadAllText(dlg.FileName);
                this.HostConfig = JsonConvert.DeserializeObject<HostConfig>(json);
                _dirty = true;
            }
        }

        private void saveConfig_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                var json = JsonConvert.SerializeObject(this.HostConfig, Formatting.Indented);
                File.WriteAllText(dlg.FileName, json);
            }
        }
    }
}
