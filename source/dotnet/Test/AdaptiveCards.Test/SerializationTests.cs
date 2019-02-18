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
            card.BackgroundImage = new Uri("http://adaptivecards.io/content/cats/1.png");
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
        public void TestSkippingUnknownElements()
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
            Assert.AreEqual(1, result.Card.Body.Count);
            Assert.AreEqual(1, result.Card.Actions.Count);
            Assert.AreEqual(2, result.Warnings.Count);
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

            var containerNonStyle = card.Body[2] as AdaptiveContainer;
            Assert.AreEqual(null, containerNonStyle.Style);
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
          {
            ""elementId"": ""id4""
          }
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
        {
          ""elementId"": ""id4""
        }
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
      ""columns"": []
    },
    {
      ""type"": ""ColumnSet"",
      ""style"": ""emphasis"",
      ""columns"": []
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
    }
}
