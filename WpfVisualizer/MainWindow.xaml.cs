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
                this.cardGrid.Children.Add(new TextBlock() { Text = err.Message });
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
            this._renderer = new AdaptiveXamlRenderer(this.Resources);
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
                ShowCardWindow dialog = new ShowCardWindow(action.Card, this.Resources);
                dialog.ShowDialog();
            }
            else if (e.Action is AC.SubmitAction)
            {
                AC.SubmitAction action = (AC.SubmitAction)e.Action;
                System.Windows.MessageBox.Show(JsonConvert.SerializeObject(e.Data, Newtonsoft.Json.Formatting.Indented), action.Title);
            }
            else if (e.Action is AC.HttpAction)
            {
                AC.HttpAction action = (AC.HttpAction)e.Action;
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

        private void viewImage_Click(object sender, RoutedEventArgs e)
        {
            //var brush = CreateBrushFromUIElementWithBitmap(cardGrid, BrushMappingMode.Absolute, )

            //var card = this._card.Actions.OfType<AC.ShowCardAction>().First().Card;
            //var uiCard = (FrameworkElement)_renderer.Render(card);
            
            //RenderTargetBitmap renderBitmap = new RenderTargetBitmap(width, height, 1/300, 1/300, PixelFormats.Pbgra32);

            //DrawingVisual visual = new DrawingVisual();
            //using (DrawingContext context = visual.RenderOpen())
            //{
            //    VisualBrush brush = new VisualBrush(c);
            //    context.DrawRectangle(brush,
            //                          null,
            //                          new Rect(new Point(), new Size(c.Width, c.Height)));
            //}

            //visual.Transform = new ScaleTransform(width / c.ActualWidth, height / c.ActualHeight);
            //renderBitmap.Render(visual);

            ////RenderTargetBitmap bitmapImage = new RenderTargetBitmap((int)uiCard.ActualWidth, (int)uiCard.ActualHeight, 96, 96, PixelFormats.Default);
            ////bitmapImage.Render(uiCard);

            //var encoder = new PngBitmapEncoder();
            //encoder.Frames.Add(BitmapFrame.Create(bitmapImage));

            //string path = @"c:\scratch\foo.png";
            //using (FileStream stream = new FileStream(path, FileMode.Create))
            //{
            //    encoder.Save(stream);
            //}
            //Process.Start(path);
        }
    }
}
