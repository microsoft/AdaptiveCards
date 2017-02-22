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

        public MainWindow()
        {
            InitializeComponent();

            _synth = new SpeechSynthesizer();
            _synth.SelectVoiceByHints(VoiceGender.Female, VoiceAge.Adult);
            _synth.SetOutputToDefaultAudioDevice();
        }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                this.cardGrid.Children.Clear();
                _card = JsonConvert.DeserializeObject<AC.AdaptiveCard>(this.textBox.Text);
                _renderContext = new RenderContext(this.Resources);
                _renderContext.OnAction += _renderer_OnAction;
                var element = _card.Render(_renderContext);
                this.cardGrid.Children.Add(element);
            }
            catch (Exception err)
            {
                this.cardGrid.Children.Clear();
                this.cardGrid.Children.Add(new System.Windows.Controls.TextBlock() { Text = err.Message, TextWrapping = TextWrapping.Wrap });
            }
        }

        private void loadButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                this.textBox.Text = File.ReadAllText(dlg.FileName).Replace("\t","  ");
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
            renderContext.ShowAction = false;
            renderContext.ShowInput = false;
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
                foreach(var element in card.Body)
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
    }
}
