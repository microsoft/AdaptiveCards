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
            var card = new AdaptiveCard();
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
            var card = new AdaptiveCard
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
            var card = new AdaptiveCard
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
            var card = new AdaptiveCard()
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
            var card = new AdaptiveCard()
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
                        Card = new AdaptiveCard
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
    }
}
