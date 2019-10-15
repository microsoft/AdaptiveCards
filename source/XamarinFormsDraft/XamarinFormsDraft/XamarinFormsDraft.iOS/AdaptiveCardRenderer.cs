using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Foundation;
using UIKit;
using Xamarin.Forms;
using AdaptiveCards.Rendering.XamarinForms;
using Xamarin.Forms.Platform.iOS;

using AdaptiveCards;
using AdaptiveCards.Rendering.Xamarin.iOS;
using Newtonsoft.Json;

[assembly: ExportRenderer (typeof(AdaptiveCardControl), typeof(AdaptiveCards.Rendering.XamarinForms.iOS.AdaptiveCardRenderer))]
namespace AdaptiveCards.Rendering.XamarinForms.iOS
{

    public class ViewController : ACRActionDelegate
    {
        private AdaptiveCardControl newElement;

        public ViewController(AdaptiveCardControl newElement)
        {
            this.newElement = newElement;
        }

        private Dictionary<string, string> NSDataToDictionary(NSData data)
        {
            return JsonConvert.DeserializeObject<Dictionary<string, string>>(NSString.FromData(data, NSStringEncoding.UTF8));
        }

        public override void DidFetchUserResponses(ACOAdaptiveCard card, ACOBaseActionElement action)
        {
            AdaptiveEventArgs adaptiveEventArgs = new AdaptiveEventArgs();

            // adaptiveRenderArgs.AdaptiveCard = renderedCard.AdaptiveCard.SerializeToJsonValue().ToString();
            // adaptiveRenderArgs.BaseActionElement = baseAction;
            adaptiveEventArgs.Inputs = NSDataToDictionary(card.InputsAsMap);
            // adaptiveRenderArgs.Warnings = ToList(renderedCard.Warnings);
            adaptiveEventArgs.Visual = null;

            // This is how it should work
            newElement.SendActionEvent(adaptiveEventArgs);
            // newElement.SendActionEvent(renderedCard, adaptiveRenderArgs);
        }

        public override void DidFetchSecondaryView(ACOAdaptiveCard card, UINavigationController naviationController) { }
    }

    public class AdaptiveCardRenderer : ViewRenderer<AdaptiveCardControl, UIView>
    {
        private ViewController viewController;
        UIView adaptiveCardView;
        private ACOHostConfigParseResult m_config = null;
        string hostconfig = @"
        {
          ""spacing"": {
            ""small"": 3,
            ""default"": 8,
            ""medium"": 20,
            ""large"": 30,
            ""extraLarge"": 40,
            ""padding"": 20
          },
          ""separator"": {
            ""lineThickness"": 1,
            ""lineColor"": ""#EEEEEE""
          },
        ""supportsInteractivity"": true,
        ""fontFamily"": ""Segoe UI"",
        ""fontSizes"": {
           ""small"": 12,
           ""default"": 14,
           ""medium"": 17,
           ""large"": 21,
           ""extraLarge"": 26
          },
          ""fontWeights"": {
            ""lighter"": 200,
            ""default"": 400,
            ""bolder"": 600
          },
          ""containerStyles"": {
            ""default"": {
              ""backgroundColor"": ""#00000000"",
              ""fontColors"": {
                ""default"": {
                  ""normal"": ""#333333"",
                  ""subtle"": ""#EE333333""
                },
                ""accent"": {
                  ""normal"": ""#2E89FC"",
                  ""subtle"": ""#882E89FC""
                },
                ""attention"": {
                  ""normal"": ""#cc3300"",
                  ""subtle"": ""#DDcc3300""
                },
                ""good"": {
                  ""normal"": ""#54a254"",
                  ""subtle"": ""#DD54a254""
                },
                ""warning"": {
                  ""normal"": ""#e69500"",
                  ""subtle"": ""#DDe69500""
                }
              }
            },
            ""emphasis"": {
              ""backgroundColor"": ""#08000000"",
              ""fontColors"": {
                ""default"": {
                  ""normal"": ""#333333"",
                  ""subtle"": ""#EE333333""
                },
                ""accent"": {
                  ""normal"": ""#2E89FC"",
                  ""subtle"": ""#882E89FC""
                },
                ""attention"": {
                  ""normal"": ""#cc3300"",
                  ""subtle"": ""#DDcc3300""
                },
                ""good"": {
                  ""normal"": ""#54a254"",
                  ""subtle"": ""#DD54a254""
                },
                ""warning"": {
                  ""normal"": ""#e69500"",
                  ""subtle"": ""#DDe69500""
                }
              }
            }
          },
          ""imageSizes"": {
            ""small"": 50,
            ""medium"": 80,
            ""large"": 120
          },
          ""actions"": {
            ""maxActions"": 5,
            ""spacing"": ""default"",
            ""buttonSpacing"": 10,
            ""showCard"": {
              ""actionMode"": ""inline"",
              ""inlineTopMargin"": 16
            },
            ""actionsOrientation"": ""horizontal"",
            ""actionAlignment"": ""stretch""
          },
          ""adaptiveCard"": {
            ""allowCustomStyle"": false
          },
          ""image"": {
            ""size"": ""medium""
          },
          ""imageSet"": {
            ""imageSize"": ""medium"",
            ""maxImageHeight"": 100
          },
          ""factSet"": {
            ""title"": {
              ""color"": ""default"",
              ""size"": ""default"",
              ""isSubtle"": false,
              ""weight"": ""bolder"",
              ""wrap"": true,
              ""maxWidth"": 150
            },
            ""value"": {
              ""color"": ""default"",
              ""size"": ""default"",
              ""isSubtle"": false,
              ""weight"": ""default"",
              ""wrap"": true
            },
            ""spacing"": 10
          }
        }";

        protected override void OnElementChanged(ElementChangedEventArgs<AdaptiveCardControl> e)
        {
            base.OnElementChanged(e);

            if (e.OldElement != null)
            {

            }

            if (m_config == null)
            {
                m_config = ACOHostConfig.FromJson(hostconfig);
            }

            if (e.NewElement != null)
            {
                if (Control == null)
                {
                    string cardContent = e.NewElement.CardContent;

                    var parsedCard = ACOAdaptiveCard.FromJson(cardContent);

                    if (parsedCard.IsValid == true)
                    {
                        viewController = new ViewController(e.NewElement);

                        var renderResult = ACRRenderer.Render(parsedCard.Card, m_config.Config,
                                                              UIScreen.MainScreen.Bounds.Size.Width - 20, viewController);

                        adaptiveCardView = renderResult.View;

                        adaptiveCardView.TranslatesAutoresizingMaskIntoConstraints = true;
                        adaptiveCardView.Frame = new CoreGraphics.CGRect(20,
                                                                     UIScreen.MainScreen.Bounds.Size.Height * 0.15f,
                                                                     UIScreen.MainScreen.Bounds.Size.Width - 40,
                                                                     UIScreen.MainScreen.Bounds.Size.Height * 0.8f);
                    }
                    SetNativeControl(adaptiveCardView);
                }

            }
        }

    }
}
