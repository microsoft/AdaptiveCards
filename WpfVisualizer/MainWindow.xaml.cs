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
using AC = Adaptive.Schema.Net;
using Newtonsoft.Json;
using Microsoft.Win32;
using System.IO;
using System.Diagnostics;
using Adaptive.Renderers;
using System.Windows.Threading;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private AdaptiveXamlRenderer _renderer;
        private AC.AdaptiveCard _card;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                this.cardGrid.Children.Clear();
                _card = JsonConvert.DeserializeObject<AC.AdaptiveCard>(this.textBox.Text);
                var element = this._renderer.Render(_card);
                this.cardGrid.Children.Add(element);
            }
            catch (Exception err)
            {
                this.cardGrid.Children.Clear();
                this.cardGrid.Children.Add(new TextBlock() { Text = err.Message, TextWrapping = TextWrapping.Wrap });
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
                this.textBox.Text = File.ReadAllText(dlg.FileName);
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //this._renderer = new AdaptiveXamlRenderer(this.Resources);
            this._renderer = new MyAdaptiveRenderer(this.Resources);
            this._renderer.OnAction += _renderer_OnAction;

            var binding = new CommandBinding(NavigationCommands.GoToPage, GoToPage, CanGoToPage);
            // Register CommandBinding for all windows.
            CommandManager.RegisterClassCommandBinding(typeof(Window), binding);

        }

        private void _renderer_OnAction(object sender, ActionEventArgs e)
        {
            if (e.Action is AC.OpenUrlAction)
            {
                AC.OpenUrlAction action = (AC.OpenUrlAction)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.ShowCardAction)
            {
                AC.ShowCardAction action = (AC.ShowCardAction)e.Action;
                ShowCardWindow dialog = new ShowCardWindow(action.Title, action.Card, this.Resources);
                dialog.Owner = this;
                dialog.ShowDialog();
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
            AdaptiveImageRenderer imageRenderer = new AdaptiveImageRenderer(this.Resources);

            var bitmap = await imageRenderer.RenderToImageAsync(this._card, 400);

            string path = @"c:\scratch\foo.png";
            var encoder = new PngBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(bitmap));

            using (FileStream stream = new FileStream(path, FileMode.Create))
            {
                encoder.Save(stream);
            }
            Process.Start(path);
        }
    }
}
