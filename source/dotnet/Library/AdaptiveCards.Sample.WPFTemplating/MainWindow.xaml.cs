using AdaptiveCards.Rendering.Wpf;
using AdaptiveCards.Templating;
using System;
using System.Collections.Generic;
using System.IO;
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

namespace AdaptiveCards.Sample.WPFTemplating
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            Renderer = new AdaptiveCardRenderer()
            {
                Resources = Resources
            };

            cardTemplate.Text = File.ReadAllText("Samples\\CardTemplate.json");
            templateData.Text = File.ReadAllText("Samples\\DataTemplate.json");
        }

        public AdaptiveCardRenderer Renderer { get; set; }

        private void renderCard_Click(object sender, RoutedEventArgs e)
        {
            /*
            AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(cardTemplate.Text);
            AdaptiveCard card = parseResult.Card;
            RenderedAdaptiveCard renderedCard = Renderer.RenderCard(card);
            */

            try
            { 
                var transformer = new AdaptiveTransformer();
                var cardJson = transformer.Transform(cardTemplate.Text, templateData.Text);
                AdaptiveCard card2 = AdaptiveCard.FromJson(cardJson).Card;
                RenderedAdaptiveCard renderedCard = Renderer.RenderCard(card2);

                cardExceptionPanel.Visibility = Visibility.Collapsed;
                cardGrid.Visibility = Visibility.Visible;
                cardGrid.Opacity = 1;
                cardGrid.Children.Clear();
                cardGrid.Children.Add(renderedCard.FrameworkElement);
            }
            catch (Exception ex)
            {
                cardExceptionPanel.Visibility = Visibility.Visible;
                cardGrid.Visibility = Visibility.Collapsed;

                cardException.Text = ex.Message + "\n" + (ex.StackTrace != null ? ex.StackTrace : "");
            }
        }
    }
}
