using System;
using UIKit;
using System.Net.Http;
using AdaptiveCards.Rendering.Xamarin.iOS;

namespace Adaptive.Cards.Rendering.Xamarin.IOS.Sample
{
    public class DemoViewController :UIViewController
    {
        public DemoViewController() 
        {
        }

        string card = @"
        {
            ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
            ""type"": ""AdaptiveCard"",
            ""version"": ""0.5"",
            ""body"": [
                {
                    ""speak"": ""<s>Tom's Pie is a Pizza restaurant which is rated 9.3 by customers.</s>"",
                    ""type"": ""ColumnSet"",
                    ""columns"": [
                        {
                            ""type"": ""Column"",
                            ""width"": 2,
                            ""items"": [
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""PIZZA""
                                },
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""Tom's Pie"",
                                    ""weight"": ""bolder"",
                                    ""size"": ""extraLarge"",
                                    ""spacing"": ""none""
                                },
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""4.2 ★★★☆ (93) · $$"",
                                    ""isSubtle"": true,
                                    ""spacing"": ""none""
                                },
                                {
                                    ""type"": ""TextBlock"",
                                    ""text"": ""**Matt H. said** \""I'm compelled to give this place 5 stars due to the number of times I've chosen to eat here this past year!\"""",
                                    ""size"": ""small"",
                                    ""wrap"": true
                                }
                            ]
                        },
                        {
                            ""type"": ""Column"",
                            ""width"": 1,
                            ""items"": [
                                {
                                    ""type"": ""Image"",
                                    ""url"": ""http://res.cloudinary.com/sagacity/image/upload/c_crop,h_670,w_635,x_0,y_0/c_scale,w_640/v1397425743/Untitled-4_lviznp.jpg"",
                                    ""size"": ""auto""
                                }
                            ]
                        }
                    ]
                }
            ],
            ""actions"": [
                {
                    ""type"": ""Action.OpenUrl"",
                    ""title"": ""More Info"",
                    ""url"": ""https://www.youtube.com/watch?v=dQw4w9WgXcQ""
                }
            ]
        }";

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
        
        public override void ViewDidLoad()
        {
            base.ViewDidLoad();

            var testcard = ACOAdaptiveCard.FromJson(card);

            if (testcard.IsValid == true)
            {
                var config = ACOHostConfig.FromJson(hostconfig);

                var renderResult = ACRRenderer.Render(testcard.Card, config.Config, new CoreGraphics.CGRect(50, 100, 300, 400));

                ACRViewController vc = renderResult.Viewcontroller;

                View.BackgroundColor = UIColor.White;

                View.AddSubview(vc.View);
            }
        }
    }
}
