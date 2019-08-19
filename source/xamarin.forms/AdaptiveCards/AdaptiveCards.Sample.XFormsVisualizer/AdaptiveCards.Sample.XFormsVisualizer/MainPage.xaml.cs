using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using AdaptiveCards.Rendering.Forms;

namespace AdaptiveCards.Sample.XFormsVisualizer
{
    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer
    [DesignTimeVisible(false)]
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();

            RenderAdaptiveCard();
        }

        public void RenderAdaptiveCard()
        {
            StackLayout layout = this.FindByName<StackLayout>("MainPageLayout");

            /*
            AdaptiveCardParseResult parsedAdaptiveCard = AdaptiveCard.FromJson(
            @"{
              ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.0"",
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""This is some text""
                }
              ]
            }");
            */

            /*
            AdaptiveCardParseResult parsedAdaptiveCard = AdaptiveCard.FromJson(
            @"{
              ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.0"",
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""**horizontalAlignment:left**"",
                  ""horizontalAlignment"": ""left""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""**horizontalAlignment:center**"",
                  ""horizontalAlignment"": ""center""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""**horizontalAlignment:right**"",
                  ""horizontalAlignment"": ""right""
                }
              ]
            }");
            */

            AdaptiveCardParseResult parsedAdaptiveCard = AdaptiveCard.FromJson(
            @"{
	          ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
              ""type"": ""AdaptiveCard"",
	          ""version"": ""1.0"",
	          ""body"": [
		        {
                  ""type"": ""TextBlock"",
			      ""text"": ""Spacing controls the amount of space between this element and the one before it"",
			      ""size"": ""medium"",
			      ""wrap"": true
                },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""spacing: none"",
			      ""spacing"": ""none""
		        },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""spacing: small"",
			      ""spacing"": ""small""
		        },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""spacing: default"",
			      ""spacing"": ""default""
		        },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""spacing: medium"",
			      ""spacing"": ""medium""
		        },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""spacing: large"",
			      ""spacing"": ""large""
		        },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""spacing: extraLarge"",
			      ""spacing"": ""extraLarge""
		        },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""separator: true"",
			      ""separator"": true
		        },
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""separator: true, spacing: extraLarge"",
			      ""separator"": true,
			      ""spacing"": ""extraLarge""
		        }
	          ]
            }");

            AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();

            RenderedAdaptiveCard renderedCard = renderer.RenderCard(parsedAdaptiveCard.Card);

            layout.Children.Add(renderedCard.View);

        }
    }
}
