using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AC = Adaptive;
using Newtonsoft.Json;
using Microsoft.Win32;
using System.IO;
using System.Diagnostics;
using Adaptive;
using System.Windows.Threading;
using System.Speech.Synthesis;
using ICSharpCode.AvalonEdit.Document;
using System.Xml.Serialization;
using System.Reflection;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private RenderContext _renderContext;
        private AC.AdaptiveCard _card;
        private SpeechSynthesizer _synth;
        private DispatcherTimer _timer;
        private bool _dirty = false;

        public MainWindow()
        {
            InitializeComponent();

            _synth = new SpeechSynthesizer();
            _synth.SelectVoiceByHints(VoiceGender.Female, VoiceAge.Adult);
            _synth.SetOutputToDefaultAudioDevice();
            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(1);
            _timer.Tick += _timer_Tick;
            _timer.Start();
        }
        private DocumentLine errorLine;

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
                    _renderContext = new RenderContext(this.Resources);
                    _renderContext.OnAction += _renderer_OnAction;
                    _renderContext.OnMissingInput += _renderer_OnMissingInput;
                    var element = _card.Render(_renderContext);
                    this.cardGrid.Children.Clear();
                    this.cardGrid.Children.Add(element);
                }
                catch (Exception err)
                {
                    HandleParseError(err);
                }
            }
        }

        private void _renderer_OnMissingInput(object sender, MissingInputEventArgs args)
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

        private void _renderer_OnAction(object sender, ActionEventArgs e)
        {
            if (e.Action is AC.ActionOpenUrl)
            {
                AC.ActionOpenUrl action = (AC.ActionOpenUrl)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.ActionShowCard)
            {
                AC.ActionShowCard action = (AC.ActionShowCard)e.Action;
                ShowCardWindow dialog = new ShowCardWindow(action.Title, action.Card, this.Resources);
                dialog.Owner = this;
                dialog.ShowDialog();
            }
            else if (e.Action is AC.ActionSubmit)
            {
                AC.ActionSubmit action = (AC.ActionSubmit)e.Action;
                System.Windows.MessageBox.Show(this, JsonConvert.SerializeObject(e.Data, Newtonsoft.Json.Formatting.Indented), "SubmitAction");
            }
            else if (e.Action is AC.ActionHttp)
            {
                AC.ActionHttp action = (AC.ActionHttp)e.Action;
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
            RenderContext renderContext = new RenderContext(this.Resources);
            renderContext.Options.ShowAction = false;
            renderContext.Options.ShowInput = false;
            var uiCard = this._card.Render(renderContext);
            var bitmap = await Utilities.XamlToImageAsync(uiCard, 400);

            string path = @"c:\scratch\foo.png";
            var encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bitmap));

            using (FileStream stream = new FileStream(path, FileMode.Create))
            {
                encoder.Save(stream);
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
    }
}
