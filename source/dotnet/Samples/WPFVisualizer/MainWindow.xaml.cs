using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Speech.Synthesis;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Effects;
using System.Windows.Threading;
using System.Xml.Serialization;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;
using ICSharpCode.AvalonEdit.Document;
using Microsoft.Win32;
using Newtonsoft.Json;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using AC = AdaptiveCards;

namespace WpfVisualizer
{
    public partial class MainWindow : Window
    {
        private AC.AdaptiveCard _card;
        private bool _dirty;
        private readonly SpeechSynthesizer _synth;
        private DocumentLine _errorLine;

        public MainWindow()
        {
            foreach (var type in typeof(AdaptiveHostConfig).Assembly.GetExportedTypes()
                .Where(t => t.Namespace == typeof(AdaptiveHostConfig).Namespace))
                TypeDescriptor.AddAttributes(type, new ExpandableObjectAttribute());

            InitializeComponent();

            _synth = new SpeechSynthesizer();
            _synth.SelectVoiceByHints(VoiceGender.Female, VoiceAge.Adult);
            _synth.SetOutputToDefaultAudioDevice();
            var timer = new DispatcherTimer { Interval = TimeSpan.FromSeconds(1) };
            timer.Tick += _timer_Tick;
            timer.Start();

            var hostConfig = new AdaptiveHostConfig();

            hostConfig.ContainerStyles.Default.BackgroundColor = Colors.WhiteSmoke.ToString();
            Renderer = new AdaptiveCardRenderer(hostConfig) { Resources = Resources };
            Renderer.UseXceedElementRenderers();
            hostConfigEditor.SelectedObject = hostConfig;

            foreach (var style in Directory.GetFiles(@"..\..\..\..\..\..\samples\v1.0\HostConfig", "*.json"))
            {
                hostConfigs.Items.Add(new ComboBoxItem
                {
                    Content = Path.GetFileNameWithoutExtension(style),
                    Tag = style
                });
            }
        }

        public AdaptiveCardRenderer Renderer { get; set; }

        public AdaptiveHostConfig HostConfig
        {
            get => (AdaptiveHostConfig)hostConfigEditor.SelectedObject;
            set => hostConfigEditor.SelectedObject = value;
        }

        private void Config_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            _dirty = true;
        }

        private void _timer_Tick(object sender, EventArgs e)
        {
            if (_dirty)
            {
                _dirty = false;
                try
                {
                    cardError.Children.Clear();

                    if (textBox.Text.Trim().StartsWith("<"))
                    {
                        var types = Assembly.GetAssembly(typeof(AC.AdaptiveCard)).ExportedTypes
                            .Where(t => t.IsAssignableFrom(typeof(AC.AdaptiveTypedElement))).ToArray();
                        var ser = new XmlSerializer(typeof(AC.AdaptiveCard), types);
                        _card = (AC.AdaptiveCard)ser.Deserialize(new StringReader(textBox.Text));
                    }
                    else
                    {
                        var result = AC.AdaptiveCard.FromJson(textBox.Text);
                        if (result.Card != null)
                            _card = result.Card;
                    }

                    cardGrid.Children.Clear();
                    if (_card != null)
                    {
                        var renderedAdaptiveCard = Renderer.RenderCard(_card);
                        if (renderedAdaptiveCard.FrameworkElement != null)
                        {
                            // Wire up click handler
                            renderedAdaptiveCard.OnAction += _onAction;

                            renderedAdaptiveCard.FrameworkElement.Effect = new DropShadowEffect
                            {
                                BlurRadius = 15,
                                Direction = -90,
                                RenderingBias = RenderingBias.Quality,
                                ShadowDepth = 2
                            };

                            cardGrid.Children.Add(renderedAdaptiveCard.FrameworkElement);
                        }
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
            var textBlock = new TextBlock
            {
                Text = err.Message,
                TextWrapping = TextWrapping.Wrap,
                Style = Resources["Error"] as Style
            };
            var button = new Button { Content = textBlock };
            button.Click += Button_Click;
            cardError.Children.Add(button);

            var iPos = err.Message.IndexOf("line ");
            if (iPos > 0)
            {
                iPos += 5;
                var iEnd = err.Message.IndexOf(",", iPos);

                var line = 0;
                if (int.TryParse(err.Message.Substring(iPos, iEnd - iPos), out line))
                {
                    iPos = err.Message.IndexOf("position ");
                    if (iPos > 0)
                    {
                        iPos += 9;
                        iEnd = err.Message.IndexOf(".", iPos);
                        var position = 0;
                        if (int.TryParse(err.Message.Substring(iPos, iEnd - iPos), out position))
                            _errorLine = textBox.Document.GetLineByNumber(Math.Min(line, textBox.Document.LineCount));
                    }
                }
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (_errorLine != null)
                textBox.Select(_errorLine.Offset, _errorLine.Length);
        }

        private void loadButton_Click(object sender, RoutedEventArgs e)
        {
            var dlg = new OpenFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                textBox.Text = File.ReadAllText(dlg.FileName).Replace("\t", "  ");
                _dirty = true;
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var binding = new CommandBinding(NavigationCommands.GoToPage, GoToPage, CanGoToPage);
            // Register CommandBinding for all windows.
            CommandManager.RegisterClassCommandBinding(typeof(Window), binding);
        }

        private void _onAction(object sender, AdaptiveActionEventArgs e)
        {
            if (e.Action is AC.OpenUrlAction)
            {
                var action = (AC.OpenUrlAction)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.ShowCardAction)
            {
                var action = (AC.ShowCardAction)e.Action;
                if (HostConfig.Actions.ShowCard.ActionMode == ShowCardActionMode.Popup)
                {
                    var dialog = new ShowCardWindow(action.Title, action, Resources);
                    dialog.Owner = this;
                    dialog.ShowDialog();
                }
            }
            else if (e.Action is AC.SubmitAction)
            {
                var action = (AC.SubmitAction)e.Action;
                MessageBox.Show(this, JsonConvert.SerializeObject(e.Data, Formatting.Indented), "SubmitAction");
            }
        }

        private void GoToPage(object sender, ExecutedRoutedEventArgs e)
        {
            if (e.Parameter is string)
            {
                var name = e.Parameter as string;
                if (!string.IsNullOrWhiteSpace(name))
                    Process.Start(name);
            }
        }

        private void CanGoToPage(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        private async void viewImage_Click(object sender, RoutedEventArgs e)
        {
            var renderer = new AdaptiveCardRenderer(new AdaptiveHostConfig());
            renderer.Resources = Resources;
            var imageStream = renderer.RenderToImage(_card, 480);
            var path = Path.GetRandomFileName() + ".png";
            using (var fileStream = new FileStream(path, FileMode.Create))
            {
                await imageStream.CopyToAsync(fileStream);
            }
            Process.Start(path);
        }

        private void speak_Click(object sender, RoutedEventArgs e)
        {
            var result = AC.AdaptiveCard.FromJson(textBox.Text);
            if (result.Card != null)
            {
                var card = result.Card;

                _synth.SpeakAsyncCancelAll();
                if (card.Speak != null)
                    _synth.SpeakSsmlAsync(FixSSML(card.Speak));
                else
                    foreach (var element in card.Body)
                    {
#pragma warning disable CS0618 // Type or member is obsolete
                        if (element.Speak != null)
                            _synth.SpeakSsmlAsync(FixSSML(element.Speak));
#pragma warning restore CS0618 // Type or member is obsolete
                    }
            }
        }

        private string FixSSML(string speak)
        {
            var sb = new StringBuilder();
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

        private void toggleOptions_Click(object sender, RoutedEventArgs e)
        {
            hostConfigEditor.Visibility = hostConfigEditor.Visibility == Visibility.Visible ? Visibility.Collapsed : Visibility.Visible;
        }

        private void options_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            _dirty = true;
        }

        private void hostConfigs_Selected(object sender, RoutedEventArgs e)
        {
            var parseResult =
                AdaptiveHostConfig.FromJson(File.ReadAllText((string)((ComboBoxItem)hostConfigs.SelectedItem).Tag));
            if (parseResult.HostConfig != null)
                HostConfig = parseResult.HostConfig;
            _dirty = true;
        }

        private void loadConfig_Click(object sender, RoutedEventArgs e)
        {
            var dlg = new OpenFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                var json = File.ReadAllText(dlg.FileName);

                var parseResult = AdaptiveHostConfig.FromJson(json);
                if (parseResult.HostConfig != null)
                    HostConfig = parseResult.HostConfig;

                _dirty = true;
            }
        }

        private void saveConfig_Click(object sender, RoutedEventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                var json = JsonConvert.SerializeObject(HostConfig, Formatting.Indented);
                File.WriteAllText(dlg.FileName, json);
            }
        }
    }
}