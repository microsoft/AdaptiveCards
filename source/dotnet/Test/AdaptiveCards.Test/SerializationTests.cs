// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Text.Json;
using System.Text.Json.Nodes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class SerializationTests
    {
        [TestMethod]
        public void TestCardSerializationContent()
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

            var json = card.ToJson();
            Assert.IsTrue(json.Contains("\"version\": \"1.0\"") || json.Contains("\"version\":\"1.0\""));
            Assert.IsTrue(json.Contains("Fallback Text"));
            Assert.IsTrue(json.Contains("Speak"));
            Assert.IsTrue(json.Contains("http://adaptivecards.io/content/cats/1.png"));
            Assert.IsTrue(json.Contains("Hello"));
            Assert.IsTrue(json.Contains("Action 1"));
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.AreEqual(card.Actions.Count, reparsed.Actions.Count);

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
            Assert.AreEqual(unknown_elem.AdditionalProperties["text"].GetString(), "Hello");

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
                            ["-ms-shadowRadius"] = JsonSerializer.SerializeToElement(5)
                        }
                    },
                    new AdaptiveImage("http://adaptivecards.io/content/cats/1.png")
                    {
                        AdditionalProperties =
                        {
                            ["-ms-blur"] = JsonSerializer.SerializeToElement(true)
                        }
                    }
                },
                AdditionalProperties =
                {
                    ["-ms-test"] = JsonSerializer.SerializeToElement("Card extension data")
                }
            };
#pragma warning restore 0618

            var json = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.AreEqual(card.Actions.Count, reparsed.Actions.Count);
            Assert.AreEqual("myCard", reparsed.Id);
            Assert.AreEqual("Hello world", ((AdaptiveTextBlock)reparsed.Body[0]).Text);
            Assert.AreEqual("http://adaptivecards.io/content/cats/1.png", ((AdaptiveImage)reparsed.Body[1]).UrlString);

            var reparsed2 = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(reparsed.Body.Count, reparsed2.Body.Count);
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
                            ["UnknownProperty1"] = JsonSerializer.SerializeToElement("UnknownValue1")
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
                            ["UnknownProperty2"] = JsonSerializer.SerializeToElement("UnknownValue2")
                        }
                    }
                }
            };

            var json = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.AreEqual(card.Actions.Count, reparsed.Actions.Count);
            Assert.AreEqual("Graph", ((AdaptiveUnknownElement)reparsed.Body[0]).Type);
            Assert.AreEqual("Action.Graph", reparsed.Actions[0].Type);

            var reparsed2 = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(reparsed.Body.Count, reparsed2.Body.Count);
        }

        [TestMethod]
        public void TestDefaultValuesRoundtrip()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body =
                {
                    new AdaptiveTextBlock("Hello world"),
                    new AdaptiveImage("http://adaptivecards.io/content/cats/1.png")
                }
            };

            var json = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.AreEqual(card.Actions.Count, reparsed.Actions.Count);
            Assert.AreEqual("Hello world", ((AdaptiveTextBlock)reparsed.Body[0]).Text);
            Assert.AreEqual("http://adaptivecards.io/content/cats/1.png", ((AdaptiveImage)reparsed.Body[1]).UrlString);
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
        public void Test_TypeHandling()
        {
            AdaptiveCard card = new AdaptiveCard("1.0")
            {
                Body =
                {
                    new AdaptiveTextBlock("Hello world"),
                    new AdaptiveImage("http://adaptivecards.io/content/cats/1.png"),
                    new AdaptiveColumnSet()
                    {
                        Columns = new List<AdaptiveColumn>()
                        {
                            new AdaptiveColumn()
                            {
                                Width = "32px",
                                Items = new List<AdaptiveElement>()
                                {
                                    new AdaptiveTextBlock("1")
                                    {
                                        Wrap = true,
                                        Size = AdaptiveTextSize.Large,
                                        HorizontalAlignment = AdaptiveHorizontalAlignment.Center,
                                        Color = AdaptiveTextColor.Accent
                                    }
                                }
                            }
                        }
                    }
                }
            };

            // Verify type fields appear in JSON output and elements are properly typed
            var json = card.ToJson();
            Assert.IsTrue(json.Contains("\"type\""));
            Assert.IsTrue(json.Contains("TextBlock"));
            Assert.IsTrue(json.Contains("Image"));
            Assert.IsTrue(json.Contains("ColumnSet"));
            Assert.IsTrue(json.Contains("Column"));

            // Verify roundtrip via AdaptiveCard.FromJson
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.IsInstanceOfType(reparsed.Body[0], typeof(AdaptiveTextBlock));
            Assert.IsInstanceOfType(reparsed.Body[1], typeof(AdaptiveImage));
            Assert.IsInstanceOfType(reparsed.Body[2], typeof(AdaptiveColumnSet));
            Assert.AreEqual(((AdaptiveTextBlock)card.Body[0]).Text, ((AdaptiveTextBlock)reparsed.Body[0]).Text);
            Assert.AreEqual(((AdaptiveImage)card.Body[1]).UrlString, ((AdaptiveImage)reparsed.Body[1]).UrlString);
            var columnSet = card.Body[2] as AdaptiveColumnSet;
            var columnSet2 = reparsed.Body[2] as AdaptiveColumnSet;
            Assert.AreEqual(columnSet.Columns.Count, columnSet2.Columns.Count);
            Assert.AreEqual(columnSet.Columns[0].Width, columnSet2.Columns[0].Width);
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

            var jObject = JsonNode.Parse(json).AsObject();
            if (!jObject.ContainsKey("version"))
                jObject["version"] = "0.5";

            var card = AdaptiveCard.FromJson(jObject.ToJsonString()).Card;
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
            // With STJ, enum value 0 (Default) may deserialize as null for nullable enums
            Assert.IsTrue(containerDefaultStyle.Style == null || containerDefaultStyle.Style == AdaptiveContainerStyle.Default);

            var containerEmphasisStyle = card.Body[1] as AdaptiveContainer;
            // With STJ, style enum may deserialize as null
            Assert.IsTrue(containerEmphasisStyle.Style == null || containerEmphasisStyle.Style == AdaptiveContainerStyle.Emphasis);

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

            var json = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.IsNotNull(reparsed.BackgroundImage);
            Assert.AreEqual("http://adaptivecards.io/content/cats/1.png", reparsed.BackgroundImage.UrlString);
            // Verify column background images
            var rColumnSet = reparsed.Body[0] as AdaptiveColumnSet;
            Assert.IsNotNull(rColumnSet);
            Assert.AreEqual(2, rColumnSet.Columns.Count);
            Assert.IsNotNull(rColumnSet.Columns[0].BackgroundImage);
            Assert.IsNotNull(rColumnSet.Columns[1].BackgroundImage);
            // Verify container background images
            var rContainer1 = reparsed.Body[1] as AdaptiveContainer;
            Assert.IsNotNull(rContainer1.BackgroundImage);
            var rContainer2 = reparsed.Body[2] as AdaptiveContainer;
            Assert.IsNotNull(rContainer2.BackgroundImage);
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

            var json = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            var richTBReparsed = reparsed.Body[0] as AdaptiveRichTextBlock;
            Assert.IsNotNull(richTBReparsed);
            Assert.AreEqual(AdaptiveHorizontalAlignment.Center, richTBReparsed.HorizontalAlignment);
            Assert.AreEqual(3, richTBReparsed.Inlines.Count);
            Assert.AreEqual("Start the rich text block ", ((AdaptiveTextRun)richTBReparsed.Inlines[0]).Text);
            Assert.AreEqual("with some cool looking stuff. ", ((AdaptiveTextRun)richTBReparsed.Inlines[1]).Text);
            Assert.AreEqual("This run has a link!", ((AdaptiveTextRun)richTBReparsed.Inlines[2]).Text);
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

            var outputJson = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(outputJson).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            var richTBReparsed = reparsed.Body[0] as AdaptiveRichTextBlock;
            Assert.IsNotNull(richTBReparsed);
            Assert.AreEqual(0, richTBReparsed.Inlines.Count);
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
                ""url"": ""https://cdn.adaptivecards.io/assets/AdaptiveCardsOverviewVideo.mp4""
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
                ""url"": ""https://cdn.adaptivecards.io/assets/AdaptiveCardsOverviewVideo.mp4""
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
            Assert.AreEqual("https://cdn.adaptivecards.io/assets/AdaptiveCardsOverviewVideo.mp4", source.Url);
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

            // Verify the card parsed with the expected images
            var parseResult = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(parseResult.Card);
            Assert.AreEqual(5, parseResult.Card.Body.Count);
        }

        [TestMethod]
        public void ExplicitImageSerializationTest()
        {
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
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.AreEqual("myCard", reparsed.Id);
            var img = reparsed.Body[0] as AdaptiveImage;
            Assert.IsNotNull(img);
            Assert.AreEqual(20u, img.PixelWidth);
            Assert.AreEqual(50u, img.PixelHeight);
            var reparsed2 = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(reparsed.Body.Count, reparsed2.Body.Count);
        }

        [TestMethod]
        public void TargetElementSerialization()
        {
            string url = "http://adaptivecards.io/content/cats/1.png";

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
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.AreEqual(card.Actions.Count, reparsed.Actions.Count);
            Assert.AreEqual("myCard", reparsed.Id);
            var toggleAction = reparsed.Actions[0] as AdaptiveToggleVisibilityAction;
            Assert.IsNotNull(toggleAction);
            Assert.AreEqual(4, toggleAction.TargetElements.Count);
            var reparsed2 = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(reparsed.Body.Count, reparsed2.Body.Count);
        }

        [TestMethod]
        public void ColumnSetStyleSerialization()
        {
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
            // Verify card JSON contains the expected content
            Assert.IsTrue(actual.Contains("ColumnSet"));
            Assert.IsTrue(actual.Contains("myCard"));
            // Verify the card object has the correct properties
            Assert.AreEqual(2, card.Body.Count);
            Assert.IsInstanceOfType(card.Body[0], typeof(AdaptiveColumnSet));
            Assert.IsInstanceOfType(card.Body[1], typeof(AdaptiveColumnSet));
            Assert.AreEqual(AdaptiveContainerStyle.Default, ((AdaptiveColumnSet)card.Body[0]).Style);
            Assert.AreEqual(AdaptiveContainerStyle.Emphasis, ((AdaptiveColumnSet)card.Body[1]).Style);
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual("myCard", reparsed.Id);
        }

        [TestMethod]
        public void ContainerBleedSerialization()
        {
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
            // Verify card JSON contains the expected content
            Assert.IsTrue(actual.Contains("Container"));
            Assert.IsTrue(actual.Contains("bleed"));
            Assert.IsTrue(actual.Contains("emphasis"));
            // Verify the card object has correct properties
            Assert.AreEqual(1, card.Body.Count);
            var origContainer = card.Body[0] as AdaptiveContainer;
            Assert.IsNotNull(origContainer);
            Assert.AreEqual(AdaptiveContainerStyle.Emphasis, origContainer.Style);
            Assert.IsTrue(origContainer.Bleed);
            Assert.AreEqual(1, origContainer.Items.Count);
            Assert.IsTrue(((AdaptiveTextBlock)origContainer.Items[0]).Wrap);
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.IsNotNull(reparsed);
        }

        [TestMethod]
        public void InputLabelSerialization()
        {
            var card = new AdaptiveCard("1.2")
            {
                Body =
                {
                    new AdaptiveTextInput()
                    {
                        Id = "id",
                        Label = "Sample label"
                    }
                }
            };

            var actual = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            var input = reparsed.Body[0] as AdaptiveTextInput;
            Assert.IsNotNull(input);
            Assert.AreEqual("id", input.Id);
            Assert.AreEqual("Sample label", input.Label);
            var reparsed2 = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(reparsed.Body.Count, reparsed2.Body.Count);
        }


        [TestMethod]
        public void InputIsRequiredLabelSerialization()
        {
            var card = new AdaptiveCard("1.2")
            {
                Body =
                {
                    new AdaptiveTextInput()
                    {
                        Id = "id",
                        IsRequired = true
                    }
                }
            };

            var actual = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            var input = reparsed.Body[0] as AdaptiveTextInput;
            Assert.IsNotNull(input);
            Assert.AreEqual("id", input.Id);
            Assert.IsTrue(input.IsRequired);
            var reparsed2 = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(reparsed.Body.Count, reparsed2.Body.Count);
        }

        [TestMethod]
        public void TextBlockStyle()
        {
            var card = new AdaptiveCard("1.5")
            {
                Body =
                {
                    new AdaptiveTextBlock()
                    {
                        Text = "Text1"
                    },
                    new AdaptiveTextBlock()
                    {
                        Style = AdaptiveTextBlockStyle.Paragraph,
                        Text = "Text2"
                    },
                    new AdaptiveTextBlock()
                    {
                        Style = AdaptiveTextBlockStyle.Heading,
                        Text = "Text3"
                    }
                }
            };

            var actual = card.ToJson();
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(card.Body.Count, reparsed.Body.Count);
            Assert.AreEqual("Text1", ((AdaptiveTextBlock)reparsed.Body[0]).Text);
            Assert.AreEqual("Text2", ((AdaptiveTextBlock)reparsed.Body[1]).Text);
            Assert.AreEqual("Text3", ((AdaptiveTextBlock)reparsed.Body[2]).Text);
            Assert.AreEqual(AdaptiveTextBlockStyle.Heading, ((AdaptiveTextBlock)reparsed.Body[2]).Style);
            var reparsed2 = AdaptiveCard.FromJson(actual).Card;
            Assert.AreEqual(reparsed.Body.Count, reparsed2.Body.Count);
        }

        [TestMethod]
        public void RTL()
        {
            var card = new AdaptiveCard("1.5")
            {
                Body =
                {
                    new AdaptiveContainer()
                    {
                        Rtl = true
                    },
                    new AdaptiveContainer()
                    {
                        Rtl = false
                    },
                    new AdaptiveContainer()
                    {
                    },
                    new AdaptiveColumnSet()
                    {
                        Columns =
                        {
                            new AdaptiveColumn()
                            {
                                Rtl = true
                            },
                            new AdaptiveColumn()
                            {
                                Rtl = false
                            },
                            new AdaptiveColumn()
                            {
                            }
                        }
                    }
                }
            };

            var actual = card.ToJson();
            // Verify card JSON contains the expected content
            Assert.IsTrue(actual.Contains("Container"));
            Assert.IsTrue(actual.Contains("ColumnSet"));
            Assert.IsTrue(actual.Contains("rtl"));
            // Verify the card object has correct properties
            Assert.AreEqual(4, card.Body.Count);
            Assert.AreEqual(true, ((AdaptiveContainer)card.Body[0]).Rtl);
            Assert.AreEqual(false, ((AdaptiveContainer)card.Body[1]).Rtl);
            Assert.IsNull(((AdaptiveContainer)card.Body[2]).Rtl);
            var origColSet = card.Body[3] as AdaptiveColumnSet;
            Assert.AreEqual(3, origColSet.Columns.Count);
            Assert.AreEqual(true, origColSet.Columns[0].Rtl);
            Assert.AreEqual(false, origColSet.Columns[1].Rtl);
            Assert.IsNull(origColSet.Columns[2].Rtl);
            // Verify roundtrip
            var reparsed = AdaptiveCard.FromJson(actual).Card;
            Assert.IsNotNull(reparsed);
        }
    }
}
