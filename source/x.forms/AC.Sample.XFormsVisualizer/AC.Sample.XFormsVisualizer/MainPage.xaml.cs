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
        private StackLayout cardLayout = null;
        private int index = 0;
        private AdaptiveCardRenderer cardRenderer = null;

        private readonly string[] cardJsons = {
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
            }",
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
            }",
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
            }",
            @"{
              ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.0"",
              ""body"": [
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""size:default""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""size:small"",
                  ""size"": ""small""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""size:default"",
                  ""size"": ""default""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""size:medium"",
                  ""size"": ""medium""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""size:large"",
                  ""size"": ""large""
                },
                {
                  ""type"": ""TextBlock"",
                  ""text"": ""size:extraLarge"",
                  ""size"": ""extraLarge""
                }
              ]
            }",
            @"{
	          ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.0"",
              ""body"": [
		        {
			      ""type"": ""TextBlock"",
			      ""text"": ""Publish Adaptive Card schema"",
			      ""weight"": ""bolder"",
			      ""size"": ""medium""
                },
		        {
			      ""type"": ""ColumnSet"",
			      ""columns"": [
                    {
					  ""type"": ""Column"",
					  ""width"": ""auto"",
					  ""items"": [
                        {
						  ""type"": ""Image"",
                          ""url"": ""https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"",
						  ""size"": ""small"",
						  ""style"": ""person""
                        }
					  ]
				    },
				    {
					  ""type"": ""Column"",
					  ""width"": ""stretch"",
                      ""items"": [
                        {
						  ""type"": ""TextBlock"",
                          ""text"": ""Matt Hidinger"",
                          ""weight"": ""bolder"",
                          ""wrap"": true
                        },
						{
						  ""type"": ""TextBlock"",
                          ""spacing"": ""none"",
                          ""text"": ""Created {{DATE(2017-02-14T06:08:39Z, SHORT)}}"",
                          ""isSubtle"": true,
                          ""wrap"": true
                        }
					  ]
				    }
			      ]
		        },
		        {
			      ""type"": ""TextBlock"",
                  ""text"": ""Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to GitHub. The schema will be the starting point of our reference documentation."",
			      ""wrap"": true
		        }
	          ]
            }
            "
        };

        public MainPage()
        {
            InitializeComponent();

            cardLayout = this.FindByName<StackLayout>("MainPageLayout");
            cardRenderer = new AdaptiveCardRenderer();

            RenderAdaptiveCard();
        }

        public void RenderAdaptiveCard()
        {
            cardLayout.Children.Clear();

            AdaptiveCardParseResult parsedAdaptiveCard = AdaptiveCard.FromJson(cardJsons[index]);
            RenderedAdaptiveCard renderedCard = cardRenderer.RenderCard(parsedAdaptiveCard.Card);

            cardLayout.Children.Add(renderedCard.View);
        }

        private void NextCardClicked(object sender, EventArgs e)
        {
            index = (index + 1) % cardJsons.Length;
            RenderAdaptiveCard();
        }
    }
}
