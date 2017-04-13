using System.Diagnostics;
using System.Text;
using System.Windows;
using AdaptiveCards;
using Newtonsoft.Json;
using AC = AdaptiveCards;
using AdaptiveCards.Rendering;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for ShowCardWindow.xaml
    /// </summary>
    public partial class ShowCardWindow : Window
    {
        private ActionShowCard _card;
        private ResourceDictionary _resources;

        public ShowCardWindow(string title, ActionShowCard showCardAction, ResourceDictionary resources)
        {
            _resources = resources;
            _card = showCardAction;

            InitializeComponent();

            this.Title = title;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            XamlRenderer renderer = new XamlRendererExtended(new HostOptions(), this._resources, OnAction);
            var element = renderer.RenderShowCard(_card);

            this.Body.Children.Add(element);
        }

        private void OnAction(object sender, ActionEventArgs e)
        {
            if (e.Action is AC.ActionOpenUrl)
            {
                AC.ActionOpenUrl action = (AC.ActionOpenUrl)e.Action;
                Process.Start(action.Url);
            }
            else if (e.Action is AC.ActionShowCard)
            {
                MessageBox.Show("Action.ShowCard is not alloed from within a sub-card");
            }
            else if (e.Action is AC.ActionSubmit)
            {
                AC.ActionSubmit action = (AC.ActionSubmit)e.Action;
                System.Windows.MessageBox.Show(this, JsonConvert.SerializeObject(e.Data, Newtonsoft.Json.Formatting.Indented), "SubmitAction");
                this.Close();
            }
            else if (e.Action is AC.ActionHttp)
            {
                AC.ActionHttp action = (AC.ActionHttp)e.Action;
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