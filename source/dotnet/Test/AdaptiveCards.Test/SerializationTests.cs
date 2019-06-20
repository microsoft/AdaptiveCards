// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class SerializationTests
    {
        [TestMethod]
        public void TestCardsSerializeInTheCorrectOrder()
        {
#pragma warning disable 0618
            var card = new AdaptiveCard();
#pragma warning restore 0618
            card.Version = "1.0";
            card.FallbackText = "Fallback Text";
            card.Speak = "Speak";
            card.BackgroundImage = new AdaptiveBackgroundImage("http://adaptivecards.io/content/cats/1.png");
            card.Body.Add(new AdaptiveTextBlock { Text = "Hello" });
            card.Actions.Add(new AdaptiveSubmitAction() { Title = "Action 1" });

            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""fallbackText"": ""Fallback Text"",
  ""speak"": ""Speak"",
  ""backgroundImage"": ""http://adaptivecards.io/content/cats/1.png"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Hello""
    }
  ],
  ""actions"": [
    {
      ""type"": ""Action.Submit"",
      ""title"": ""Action 1""
    }
  ]
}";
            Assert.AreEqual(expected, card.ToJson());

        }

        [TestMethod]
        public void TestKeepingUnknownElements()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""IDunno"",
      ""text"": ""Hello""
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""Hello""
    }
  ],
  ""actions"": [
    {
      ""type"": ""Action.IDunno"",
      ""title"": ""Action 1""
    },
    {
      ""type"": ""Action.Submit"",
      ""title"": ""Action 1""
    }
  ]
}";

            var result = AdaptiveCard.FromJson(json);

            Assert.IsNotNull(result.Card);
            Assert.AreEqual(2, result.Card.Body.Count);
            Assert.AreEqual(2, result.Card.Actions.Count);
            Assert.AreEqual(2, result.Warnings.Count);

            // check first unknown element
            var unknown_elem = (AdaptiveUnknownElement)result.Card.Body[0];
            Assert.AreEqual(unknown_elem.Type, "IDunno");
            Assert.AreEqual(unknown_elem.AdditionalProperties["text"], "Hello");

            // check second unknown element
            var unknown_action = result.Card.Actions[0];
            Assert.AreEqual(unknown_action.Type, "Action.IDunno");
            Assert.AreEqual(unknown_action.Title, "Action 1");
        }

        [TestMethod]
        public void TestSerializingAdditionalData()
        {
            // Disable this warning since we want to make sure that
            // the obsoleted constructor also outputs the right version
#pragma warning disable 0618
            var card = new AdaptiveCard()
            {
                Id = "myCard",
                Body =
                {
                    new AdaptiveTextBlock("Hello world")
                    {
                        AdditionalProperties =
                        {
                            ["-ms-shadowRadius"] = 5
                        }
                    },
                    new AdaptiveImage("http://adaptivecards.io/content/cats/1.png")
                    {
                        AdditionalProperties =
                        {
                            ["-ms-blur"] = true
                        }
                    }
                },
                AdditionalProperties =
                {
                    ["-ms-test"] = "Card extension data"
                }
            };
#pragma warning restore 0618

            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""id"": ""myCard"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Hello world"",
      ""-ms-shadowRadius"": 5
    },
    {
      ""type"": ""Image"",
      ""url"": ""http://adaptivecards.io/content/cats/1.png"",
      ""-ms-blur"": true
    }
  ],
  ""-ms-test"": ""Card extension data""
}";
            Assert.AreEqual(expected, card.ToJson());

            var deserializedCard = AdaptiveCard.FromJson(expected).Card;
            Assert.AreEqual(expected, deserializedCard.ToJson());
        }

        [TestMethod]
        public void TestSerializingUnknownItems()
        {
            var card = new AdaptiveCard("1.2")
            {
                Body =
                {
                    new AdaptiveUnknownElement()
                    {
                        Type = "Graph",
                        AdditionalProperties =
                        {
                            ["UnknownProperty1"] = "UnknownValue1"
                        }
                    }
                },
                Actions =
                {
                    new AdaptiveUnknownAction()
                    {
                        Type = "Action.Graph",
                        AdditionalProperties =
                        {
                            ["UnknownProperty2"] = "UnknownValue2"
                        }
                    }
                }
            };

            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""Graph"",
      ""UnknownProperty1"": ""UnknownValue1""
    }
  ],
  ""actions"": [
    {
      ""type"": ""Action.Graph"",
      ""UnknownProperty2"": ""UnknownValue2""
    }
  ]
}";
            Assert.AreEqual(expected, card.ToJson());

            var deserializedCard = AdaptiveCard.FromJson(expected).Card;
            Assert.AreEqual(expected, deserializedCard.ToJson());
        }

        [TestMethod]
        public void TestDefaultValuesAreNotSerialized()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body =
                {
                    new AdaptiveTextBlock("Hello world"),
                    new AdaptiveImage("http://adaptivecards.io/content/cats/1.png")
                }
            };

            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Hello world""
    },
    {
      ""type"": ""Image"",
      ""url"": ""http://adaptivecards.io/content/cats/1.png""
    }
  ]
}";
            Assert.AreEqual(expected, card.ToJson());
        }

        [TestMethod]
        public void TestStyleNullDeserialization()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""ColumnSet"",
      ""columns"": [
           {
              ""type"": ""Column"",
              ""style"": null
           }
       ]
    }
  ]
}";

            var result = AdaptiveCard.FromJson(json);

            Assert.IsNotNull(result.Card);
        }


        [TestMethod]
        public void Test_MissingTypePropertyThrowsException()
        {
            // TODO: we can actually pull this payload from ~/samples/Tests/TypeIsRequired.json
            // Should we also do this for the other Tests payloads in the samples folder?

            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""This payload should fail to parse""
    },
    {
      ""text"": ""What am I?""
    }
  ]
}";

            Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json));
        }

        [TestMethod]
        public void Test_AdaptiveCardTypeNameIsValid()
        {
            var json = @"{
  ""type"": ""Hello"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""This payload should fail to parse""
    }
  ]
}";

            Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json));
        }

        [TestMethod]
        public void TestSerializingTextBlock()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body =
                {
                    new AdaptiveTextBlock()
                    {
                        Text = "Hello world"
                    }
                }
            };

            string json = card.ToJson();

            // Re-parse the card
            card = AdaptiveCard.FromJson(json).Card;

            // Ensure there's a text element
            Assert.AreEqual(1, card.Body.Count);
            Assert.IsInstanceOfType(card.Body[0], typeof(AdaptiveTextBlock));

            Assert.AreEqual("Hello world", ((AdaptiveTextBlock)card.Body[0]).Text);
        }


        [TestMethod]
        public void TestShowCardActionSerialization()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body =
                {
                    new AdaptiveTextBlock()
                    {
                        Text = "Hello world"
                    }
                },
                Actions =
                {
                    new AdaptiveShowCardAction
                    {
                        Title = "Show Card",
                        Card = new AdaptiveCard("1.0")
                        {
                            Version = null,
                            Body =
                            {
                                new AdaptiveTextBlock
                                {
                                    Text = "Inside Show Card"
                                }
                            }
                        }
                    }
                }
            };

            string json = card.ToJson();

            // Re-parse the card
            card = AdaptiveCard.FromJson(json).Card;

            // Ensure there's a text element
            Assert.AreEqual(1, card.Actions.Count);
            Assert.IsNotNull(((AdaptiveShowCardAction)card.Actions[0]).Card);
        }

        [TestMethod]
        public void ConsumerCanProvideCardVersion()
        {
            var json = @"{
    ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
    ""type"": ""AdaptiveCard"",
    ""speak"": ""Hello""
}";

            var jObject = JObject.Parse(json);
            if (!jObject.TryGetValue("version", out var _))
                jObject["version"] = "0.5";

            var card = AdaptiveCard.FromJson(jObject.ToString()).Card;
            Assert.AreEqual(new AdaptiveSchemaVersion("0.5"), card.Version);
            Assert.AreEqual("Hello", card.Speak);

        }

        [TestMethod]
        public void ColumnTypeNotRequired()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""ColumnSet"",
      ""columns"": [
        {
          ""items"": [
            {
              ""type"": ""Image"",
              ""url"": ""http://3.bp.blogspot.com/-Xo0EuTNYNQg/UEI1zqGDUTI/AAAAAAAAAYE/PLYx5H4J4-k/s1600/smiley+face+super+happy.jpg"",
              ""size"": ""stretch""
            }
          ]
        },
        {
          ""width"": ""stretch"",
          ""items"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""This card has two ColumnSets on top of each other. In each, the left column is explicitly sized to be 50 pixels wide."",
              ""wrap"": true
            }
          ]
        }
       ]
    }
  ]
}";

            var result = AdaptiveCard.FromJson(json);

            Assert.IsNotNull(result.Card);
        }

        [TestMethod]
        public void CardLevelSelectAction()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""selectAction"": {
      ""type"": ""Action.OpenUrl"",
      ""title"": ""Open URL"",
      ""url"": ""http://adaptivecards.io""
  }
}";
            var card = AdaptiveCard.FromJson(json).Card;
            var actualSelectAction = card.SelectAction as AdaptiveOpenUrlAction;

            var expectedSelectAction = new AdaptiveOpenUrlAction
            {
                Title = "Open URL",
                UrlString = "http://adaptivecards.io"
            };
            Assert.AreEqual(expectedSelectAction.Title, actualSelectAction.Title);
            Assert.AreEqual(expectedSelectAction.UrlString, actualSelectAction.UrlString);
        }

        [TestMethod]
        public void ContainerStyle()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""Container"",
      ""style"": ""default"",
      ""items"": []
    },
    {
      ""type"": ""Container"",
      ""style"": ""emphasis"",
      ""items"": []
    },
    {
      ""type"": ""Container"",
      ""items"": []
    }
  ]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            var actualSelectAction = card.SelectAction as AdaptiveOpenUrlAction;

            var containerDefaultStyle = card.Body[0] as AdaptiveContainer;
            Assert.AreEqual(AdaptiveContainerStyle.Default, containerDefaultStyle.Style);

            var containerEmphasisStyle = card.Body[1] as AdaptiveContainer;
            Assert.AreEqual(AdaptiveContainerStyle.Emphasis, containerEmphasisStyle.Style);

            var containerNoneStyle = card.Body[2] as AdaptiveContainer;
            Assert.IsNull(containerNoneStyle.Style);
        }

        [TestMethod]
        public void BackgroundImage()
        {
            var card = new AdaptiveCard("1.2");
            card.BackgroundImage = new AdaptiveBackgroundImage("http://adaptivecards.io/content/cats/1.png", AdaptiveImageFillMode.Repeat, AdaptiveHorizontalAlignment.Right, AdaptiveVerticalAlignment.Bottom);

            var columnSet = new AdaptiveColumnSet();
            var column1 = new AdaptiveColumn();
            column1.BackgroundImage = new AdaptiveBackgroundImage("http://adaptivecards.io/content/cats/1.png", AdaptiveImageFillMode.RepeatVertically, AdaptiveHorizontalAlignment.Center, AdaptiveVerticalAlignment.Top);
            columnSet.Columns.Add(column1);
            var column2 = new AdaptiveColumn();
            column2.BackgroundImage = new AdaptiveBackgroundImage("http://adaptivecards.io/content/cats/2.png", AdaptiveImageFillMode.Cover, AdaptiveHorizontalAlignment.Right, AdaptiveVerticalAlignment.Bottom);
            columnSet.Columns.Add(column2);
            card.Body.Add(columnSet);

            var container1 = new AdaptiveContainer();
            container1.BackgroundImage = new AdaptiveBackgroundImage("http://adaptivecards.io/content/cats/2.png", AdaptiveImageFillMode.RepeatHorizontally, AdaptiveHorizontalAlignment.Left, AdaptiveVerticalAlignment.Center);
            card.Body.Add(container1);

            var container2 = new AdaptiveContainer();
            container2.BackgroundImage = new AdaptiveBackgroundImage("http://adaptivecards.io/content/cats/3.png");
            card.Body.Add(container2);

            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""backgroundImage"": {
    ""url"": ""http://adaptivecards.io/content/cats/1.png"",
    ""fillMode"": ""repeat"",
    ""horizontalAlignment"": ""right"",
    ""verticalAlignment"": ""bottom""
  },
  ""body"": [
    {
      ""type"": ""ColumnSet"",
      ""columns"": [
        {
          ""type"": ""Column"",
          ""backgroundImage"": {
            ""url"": ""http://adaptivecards.io/content/cats/1.png"",
            ""fillMode"": ""repeatVertically"",
            ""horizontalAlignment"": ""center""
          },
          ""items"": []
        },
        {
          ""type"": ""Column"",
          ""backgroundImage"": {
            ""url"": ""http://adaptivecards.io/content/cats/2.png"",
            ""horizontalAlignment"": ""right"",
            ""verticalAlignment"": ""bottom""
          },
          ""items"": []
        }
      ]
    },
    {
      ""type"": ""Container"",
      ""backgroundImage"": {
        ""url"": ""http://adaptivecards.io/content/cats/2.png"",
        ""fillMode"": ""repeatHorizontally"",
        ""verticalAlignment"": ""center""
      },
      ""items"": []
    },
    {
      ""type"": ""Container"",
      ""backgroundImage"": ""http://adaptivecards.io/content/cats/3.png"",
      ""items"": []
    }
  ]
}";
            Assert.AreEqual(expected, card.ToJson());
        }

        [TestMethod]
        public void RichTextBlock()
        {
            var card = new AdaptiveCard("1.2");

            var richTB = new AdaptiveRichTextBlock();
            richTB.HorizontalAlignment = AdaptiveHorizontalAlignment.Center;

            // Build text runs
            var textRun1 = new AdaptiveTextRun("Start the rich text block ");
            richTB.Inlines.Add(textRun1);

            var textRun2 = new AdaptiveTextRun("with some cool looking stuff. ");
            textRun2.Color = AdaptiveTextColor.Accent;
            textRun2.FontType = AdaptiveFontType.Monospace;
            textRun2.IsSubtle = true;
            textRun2.Italic = true;
            textRun2.Strikethrough = true;
            textRun2.Highlight = true;
            textRun2.Size = AdaptiveTextSize.Large;
            textRun2.Weight = AdaptiveTextWeight.Bolder;
            richTB.Inlines.Add(textRun2);

            var textRun3 = new AdaptiveTextRun("This run has a link!");
            textRun3.SelectAction = new AdaptiveOpenUrlAction()
            {
                Title = "Open URL",
                UrlString = "http://adaptivecards.io/"
            };
            richTB.Inlines.Add(textRun3);

            card.Body.Add(richTB);

            // Indentation needs to be kept as-is to match the result of card.ToJson
            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""RichTextBlock"",
      ""horizontalAlignment"": ""center"",
      ""inlines"": [
        {
          ""type"": ""TextRun"",
          ""text"": ""Start the rich text block ""
        },
        {
          ""type"": ""TextRun"",
          ""size"": ""large"",
          ""weight"": ""bolder"",
          ""color"": ""accent"",
          ""isSubtle"": true,
          ""italic"": true,
          ""strikethrough"": true,
          ""highlight"": true,
          ""text"": ""with some cool looking stuff. "",
          ""fontType"": ""monospace""
        },
        {
          ""type"": ""TextRun"",
          ""text"": ""This run has a link!"",
          ""selectAction"": {
            ""type"": ""Action.OpenUrl"",
            ""url"": ""http://adaptivecards.io/"",
            ""title"": ""Open URL""
          }
        }
      ]
    }
  ]
}";
            Assert.AreEqual(expected, card.ToJson());
        }

        [TestMethod]
        public void RichTextBlockFromJson()
        {
            var json = @"{
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.2"",
              ""body"": [
                {
                  ""type"": ""RichTextBlock"",
                  ""horizontalAlignment"": ""center"",
                  ""inlines"": [
                      {
                        ""type"": ""TextRun"",
                        ""text"": ""Start the rich text block ""
                      },
                      {
                          ""type"": ""TextRun"",
                          ""size"": ""large"",
                          ""weight"": ""bolder"",
                          ""color"": ""accent"",
                          ""isSubtle"": true,
                          ""italic"": true,
                          ""highlight"": true,
                          ""strikethrough"": true,
                          ""text"": ""with some cool looking stuff. "",
                          ""fontStyle"": ""monospace""
                      },
                      {
                        ""type"": ""TextRun"",
                        ""text"": ""This run has a link!"",
                        ""selectAction"": {
                          ""type"": ""Action.OpenUrl"",
                          ""url"": ""http://adaptivecards.io/"",
                          ""title"": ""Open URL""
                      }
                  }
                  ]
                }
              ]
            }";

            var card = AdaptiveCard.FromJson(json).Card;

            var richTB = card.Body[0] as AdaptiveRichTextBlock;
            Assert.AreEqual(richTB.HorizontalAlignment, AdaptiveHorizontalAlignment.Center);

            var inlines1 = richTB.Inlines;
            var run1 = inlines1[0] as AdaptiveTextRun;
            Assert.AreEqual("Start the rich text block ", run1.Text);

            var run2 = inlines1[1] as AdaptiveTextRun;
            Assert.AreEqual(run2.Text, "with some cool looking stuff. ");
            Assert.IsTrue(run2.Italic);
            Assert.IsTrue(run2.Strikethrough);
            Assert.IsTrue(run2.Highlight);

            var run3 = inlines1[2] as AdaptiveTextRun;
            Assert.AreEqual(run3.Text, "This run has a link!");
            Assert.AreEqual("Action.OpenUrl", run3.SelectAction.Type);
            Assert.AreEqual("Open URL", run3.SelectAction.Title);
            Assert.AreEqual("http://adaptivecards.io/", (run3.SelectAction as AdaptiveOpenUrlAction).UrlString); ;
        }

        [TestMethod]
        public void EmptyRichTextBlock()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""RichTextBlock"",
      ""inlines"": []
    }
  ]
}";

            var card = AdaptiveCard.FromJson(json).Card;

            // Validate RTB
            var richTB1 = card.Body[0] as AdaptiveRichTextBlock;
            Assert.IsTrue(richTB1.Inlines.Count == 0);

            Assert.AreEqual(json, card.ToJson());
        }

        [TestMethod]
        public void MediaInvalid_ShouldThrowException()
        {
            var json = @"{
  ""type"": ""Hello"",
  ""version"": ""1.0"",
  ""body"": [
    {
        ""type"": ""Media"",
        ""poster"": ""http://adaptivecards.io/content/cats/1.png""
    }
  ]
}";

            Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json));
        }

        [TestMethod]
        public void Media()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
        ""type"": ""Media"",
        ""sources"": [
            {
                ""mimeType"": ""video/mp4"",
                ""url"": ""http://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4""
            }
        ]
    },
    {
        ""type"": ""Media"",
        ""poster"": ""http://adaptivecards.io/content/cats/1.png"",
        ""altText"": ""Adaptive Cards Overview Video"",
        ""sources"": [
            {
                ""mimeType"": ""video/mp4"",
                ""url"": ""http://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4""
            }
        ]
    }
  ]
}";
            var card = AdaptiveCard.FromJson(json).Card;

            // The first media element does not have either poster or alt text
            var mediaElement = card.Body[0] as AdaptiveMedia;
            Assert.IsNull(mediaElement.Poster);
            Assert.IsNull(mediaElement.AltText);

            // The second media element has poster, alt text, and 1 source
            var mediaElementFull = card.Body[1] as AdaptiveMedia;
            Assert.AreEqual("http://adaptivecards.io/content/cats/1.png", mediaElementFull.Poster);
            Assert.AreEqual("Adaptive Cards Overview Video", mediaElementFull.AltText);

            var source = mediaElementFull.Sources[0] as AdaptiveMediaSource;
            Assert.AreEqual("video/mp4", source.MimeType);
            Assert.AreEqual("http://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4", source.Url);
        }

        [TestMethod]
        public void ImageBackgroundColor()
        {
            var json = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
    {
        ""type"": ""Image"",
        ""url"": ""http://adaptivecards.io/content/cats/2.png"",
        ""backgroundColor"" : ""Blue""
    },
    {
        ""type"": ""Image"",
        ""url"": ""http://adaptivecards.io/content/cats/2.png"",
        ""backgroundColor"" : ""#FF00FF""
    },
    {
        ""type"": ""Image"",
        ""url"": ""http://adaptivecards.io/content/cats/2.png"",
        ""backgroundColor"" : ""#FF00FFAA""
    },
    {
        ""type"": ""Image"",
        ""url"": ""http://adaptivecards.io/content/cats/2.png"",
        ""backgroundColor"" : ""#FREEBACE""
    },
    {
        ""type"": ""Image"",
        ""url"": ""http://adaptivecards.io/content/cats/2.png"",
        ""backgroundColor"" : ""#GREENS""
    }
    ]
}";

            // There should be 3 invalid colors in this card
            var parseResult = AdaptiveCard.FromJson(json);
            Assert.AreEqual(3, parseResult.Warnings.Count);
        }

        [TestMethod]
        public void ExplicitImageSerializationTest()
        {
            var expected =
@"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""id"": ""myCard"",
  ""body"": [
    {
      ""type"": ""Image"",
      ""url"": ""http://adaptivecards.io/content/cats/1.png"",
      ""width"": ""20px"",
      ""height"": ""50px""
    }
  ]
}";

            var card = new AdaptiveCard("1.2")
            {
                Id = "myCard",
                Body =
                {
                    new AdaptiveImage("http://adaptivecards.io/content/cats/1.png")
                    {
                        PixelWidth = 20,
                        PixelHeight = 50
                    },
                }
            };

            var actual = card.ToJson();
            Assert.AreEqual(expected: expected, actual: actual);
            var deserializedCard = AdaptiveCard.FromJson(expected).Card;
            var deserializedActual = deserializedCard.ToJson();
            Assert.AreEqual(expected: expected, actual: deserializedActual);
        }

        [TestMethod]
        public void TargetElementSerialization()
        {
            string url = "http://adaptivecards.io/content/cats/1.png";
            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""id"": ""myCard"",
  ""body"": [
    {
      ""type"": ""Image"",
      ""url"": """ + url + @""",
      ""selectAction"": {
        ""type"": ""Action.ToggleVisibility"",
        ""targetElements"": [
          ""id1"",
          {
            ""elementId"": ""id2"",
            ""isVisible"": false
          },
          {
            ""elementId"": ""id3"",
            ""isVisible"": true
          },
          ""id4""
        ]
      }
    }
  ],
  ""actions"": [
    {
      ""type"": ""Action.ToggleVisibility"",
      ""targetElements"": [
        ""id1"",
        {
          ""elementId"": ""id2"",
          ""isVisible"": false
        },
        {
          ""elementId"": ""id3"",
          ""isVisible"": true
        },
        ""id4""
      ]
    }
  ]
}";

            var card = new AdaptiveCard("1.2")
            {
                Id = "myCard",
                Body =
                {
                    new AdaptiveImage(url)
                    {
                        SelectAction = new AdaptiveToggleVisibilityAction()
                        {
                            TargetElements =
                            {
                                "id1",
                                new AdaptiveTargetElement("id2", false),
                                new AdaptiveTargetElement("id3", true),
                                new AdaptiveTargetElement("id4")
                            }
                        }
                    }
                },
                Actions =
                {
                    new AdaptiveToggleVisibilityAction()
                    {
                        TargetElements =
                        {
                            "id1",
                            new AdaptiveTargetElement("id2", false),
                            new AdaptiveTargetElement("id3", true),
                            new AdaptiveTargetElement("id4")
                        }
                    }
                }
            };

            var actual = card.ToJson();
            Assert.AreEqual(expected: expected, actual: actual);
            var deserializedCard = AdaptiveCard.FromJson(expected).Card;
            var deserializedActual = deserializedCard.ToJson();
            Assert.AreEqual(expected: expected, actual: deserializedActual);
        }

        [TestMethod]
        public void ColumnSetStyleSerialization()
        {
            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""id"": ""myCard"",
  ""body"": [
    {
      ""type"": ""ColumnSet"",
      ""columns"": [],
      ""style"": ""default""
    },
    {
      ""type"": ""ColumnSet"",
      ""columns"": [],
      ""style"": ""emphasis""
    }
  ]
}";

            var card = new AdaptiveCard("1.2")
            {
                Id = "myCard",
                Body =
                {
                    new AdaptiveColumnSet()
                    {
                        Style = AdaptiveContainerStyle.Default
                    },
                    new AdaptiveColumnSet()
                    {
                        Style = AdaptiveContainerStyle.Emphasis
                    }
                }
            };

            var actual = card.ToJson();
            Assert.AreEqual(expected: expected, actual: actual);
            var deserializedCard = AdaptiveCard.FromJson(expected).Card;
            var deserializedActual = deserializedCard.ToJson();
            Assert.AreEqual(expected: expected, actual: deserializedActual);
        }

        [TestMethod]
        public void ContainerBleedSerialization()
        {
            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""Container"",
      ""items"": [
        {
          ""type"": ""TextBlock"",
          ""text"": ""This container has a gray background that extends to the edges of the card"",
          ""wrap"": true
        }
      ],
      ""style"": ""emphasis"",
      ""bleed"": true
    }
  ]
}";

            var card = new AdaptiveCard("1.2")
            {
                Body =
                {
                    new AdaptiveContainer()
                    {
                        Style = AdaptiveContainerStyle.Emphasis,
                        Bleed = true,
                        Items = new List<AdaptiveElement>
                        {
                            new AdaptiveTextBlock()
                            {
                                Text = "This container has a gray background that extends to the edges of the card",
                                Wrap = true
                            }
                        }
                    }
                }
            };

            var actual = card.ToJson();
            Assert.AreEqual(expected: expected, actual: actual);
            var deserializedCard = AdaptiveCard.FromJson(expected).Card;
            var deserializedActual = deserializedCard.ToJson();
            Assert.AreEqual(expected: expected, actual: deserializedActual);
        }



    }
}
