using System.Diagnostics;
using System.Text;
using System.Windows;
using AdaptiveCards;
using Newtonsoft.Json;
using AC = AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for ShowCardWindow.xaml
    /// </summary>
    public partial class ShowCardWindow : Window
    {
        private ShowCardAction _card;
        private ResourceDictionary _resources;

        public ShowCardWindow(string title, ShowCardAction showCardAction, ResourceDictionary resources)
        {
            _resources = resources;
            _card = showCardAction;

            InitializeComponent();

            this.Title = title;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var renderer = new XamlRendererExtended(new HostConfig(), this._resources, OnAction);
            var element = renderer.RenderShowCard(_card);

            this.Body.Children.Add(element);
        }

        private void OnAction(object sender, ActionEventArgs e)
        {
            if (e.Action is AC.OpenUrlAction)
            {
                AC.OpenUrlAction action = (AC.OpenUrlAction)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.ShowCardAction)
            {
                MessageBox.Show("Action.ShowCard is not alloed from within a sub-card");
            }
            else if (e.Action is AC.SubmitAction)
            {
                AC.SubmitAction action = (AC.SubmitAction)e.Action;
                System.Windows.MessageBox.Show(this, JsonConvert.SerializeObject(e.Data, Newtonsoft.Json.Formatting.Indented), "SubmitAction");
                this.Close();
            }
            else if (e.Action is AC.HttpAction)
            {
                AC.HttpAction action = (AC.HttpAction)e.Action;
                StringBuilder sb = new StringBuilder();
                sb.AppendLine($"HEADERS={JsonConvert.SerializeObject(action.Headers)}");
                sb.AppendLine($"BODY={action.Body}");
                sb.AppendLine($"DATA={e.Data}");
                System.Windows.MessageBox.Show(this, sb.ToString(), $"HttpAction {action.Method} {action.Url}");
                this.Close();
            }
        }
    }
}