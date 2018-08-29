using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveCardApiTests
    {
        [TestMethod]
        public void TestAssigningVersion()
        {
            AdaptiveCard card = new AdaptiveCard();
            card.Version = new AdaptiveSchemaVersion(4, 5);

            Assert.AreEqual(4, card.Version.Major);
            Assert.AreEqual(5, card.Version.Minor);
        }

        [TestMethod]
        public void TestAssigningVersionAsString()
        {
            AdaptiveCard card = new AdaptiveCard();
            card.Version = "4.5";

            Assert.AreEqual(4, card.Version.Major);
            Assert.AreEqual(5, card.Version.Minor);

            card.Version = "3";

            Assert.AreEqual(3, card.Version.Major);
            Assert.AreEqual(0, card.Version.Minor);

            card.Version = "4.1.3";

            Assert.AreEqual(4, card.Version.Major);
            Assert.AreEqual(1, card.Version.Minor);

            try
            {
                card.Version = "tacos";
                Assert.Fail("Assigning tacos to version should fail");
            }
            catch (AssertFailedException) { throw; }
            catch { }

            try
            {
                card.Version = "1.tacos";
                Assert.Fail("Assigning 1.tacos to version should fail");
            }
            catch (AssertFailedException) { throw; }
            catch { }
        }

        [TestMethod]
        public void TestParsingCard()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""size"": ""large"",
      ""weight"": ""bolder""
    }
  ]
}";
            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);
            Assert.AreEqual(1, result.Card.Body.Count);
        }

        [TestMethod]
        public void TestParsingInvalidCardMissingVersion()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""size"": ""large"",
      ""weight"": ""bolder""
    }
  ]
}";
            // TODO: No longer throwing on this exception to work around bot framework integration issues. Revisit later
            //Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json));
        }

        [TestMethod]
        public void TestParsingInvalidCardMissingType()
        {
            var json = @"{
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""size"": ""large"",
      ""weight"": ""bolder""
    }
  ]
}";
            Assert.ThrowsException<AdaptiveSerializationException>(() => AdaptiveCard.FromJson(json));
        }

        [TestMethod]
        // Make sure resource information for all Images and Medias in a card are returned
        // TODO: Add test for Media information when Media type is added
        public void TestResourceInformation()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""fallbackText"": ""Fallback Text"",
  ""speak"": ""Speak"",
  ""backgroundImage"": ""http://adaptivecards.io/content/cats/1.png"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Hello""
    },
    {
      ""type"": ""Image"",
      ""url"": ""http://adaptivecards.io/content/cats/2.png""
    },
    {
      ""type"": ""Container"",
      ""items"": [
        {
          ""type"": ""Image"",
          ""url"": ""http://adaptivecards.io/content/cats/3.png""
        },
        {
          ""type"": ""ColumnSet"",
          ""columns"": [
            {
              ""type"": ""Column"",
              ""items"": [
                {
                    ""type"": ""Image"",
                    ""url"": ""http://adaptivecards.io/content/cats/2.png""
                }
              ]
            }
          ]
        },
        {
          ""type"": ""ImageSet"",
          ""images"": [
            {
              ""type"": ""Image"",
              ""url"": ""content/cats/4.png""
            }
          ]
        }
      ]
    }
  ],
  ""actions"": [
    {
      ""type"": ""Action.ShowCard"",
      ""iconUrl"": ""http://adaptivecards.io/content/cats/5.png"",
      ""card"": {
          ""type"": ""AdaptiveCard"",
          ""version"": ""1.0"",
          ""body"": [
            {
              ""type"": ""TextBlock"",
              ""text"": ""Hello""
            },
            {
              ""type"": ""Image"",
              ""url"": ""http://adaptivecards.io/content/cats/6.png""
            }
          ]
      }
    }
  ]
}";
            var card = AdaptiveCard.FromJson(json).Card;
            var expected = new RemoteResourceInformation[]
            {
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/1.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/2.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/3.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/2.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "content/cats/4.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/5.png",
                    typeof(AdaptiveImage),
                    null
                ),
                new RemoteResourceInformation(
                    "http://adaptivecards.io/content/cats/6.png",
                    typeof(AdaptiveImage),
                    null
                )
            };
            var actual = card.GetResourceInformation();
            CollectionAssert.AreEqual(expected, actual);
        }

        [TestMethod]
        public void TestExplicitImageTest()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""20px"",
                              ""height"": ""50px""
                          }
                      ]
                  }";

            var card = AdaptiveCard.FromJson(payload).Card;
            Assert.AreEqual(card.Body.Count, 1);
            var imageBlock = card.Body[0] as AdaptiveImage;
            Assert.AreEqual(20U,imageBlock.PixelWidth);
            Assert.AreEqual(50U, imageBlock.PixelHeight);
        }

        [TestMethod]
        public void TestExplicitImageTestWithMalformedUnit()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": ""20"",
                              ""height"": ""50 p x""
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(card.Body.Count, 1);
            var imageBlock = card.Body[0] as AdaptiveImage;
            Assert.AreEqual(0U, imageBlock.PixelWidth);
            Assert.AreEqual(0U, imageBlock.PixelHeight);
            Assert.AreEqual(2, result.Warnings.Count);
            Assert.AreEqual(
                result.Warnings[0].Message,
                @"The Value ""20"" for field ""width"" was not specified as a proper dimension in the format (\d+(.\d+)?px), it will be ignored.");
            Assert.AreEqual(
                result.Warnings[1].Message,
                @"The Value "" x"" was not specified as a proper unit(px), it will be ignored.");
        }

        [TestMethod]
        public void TestExplicitImageTestWithMalformedNumber()
        {
            var payload =
                @"{
                      ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
                      ""type"": ""AdaptiveCard"",
                      ""version"": ""1.0"",
                      ""body"": [
                          {
                              ""type"": ""Image"",
                              ""url"": ""http://adaptivecards.io/content/cats/1.png"",
                              ""width"": "".20px"",
                              ""height"": ""50.1234.12px""
                          }
                      ]
                  }";

            var result = AdaptiveCard.FromJson(payload);
            var card = result?.Card;
            Assert.AreEqual(1, card.Body.Count);
            var imageBlock = card.Body[0] as AdaptiveImage;
            Assert.AreEqual(0U, imageBlock.PixelWidth);
            Assert.AreEqual(0U, imageBlock.PixelHeight);
            Assert.AreEqual(2, result.Warnings.Count);
            Assert.AreEqual(
                @"The Value "".20px"" for field ""width"" was not specified as a proper dimension in the format (\d+(.\d+)?px), it will be ignored.",
                result.Warnings[0].Message); 
            Assert.AreEqual(
                @"The Value ""50.1234.12px"" for field ""height"" was not specified as a proper dimension in the format (\d+(.\d+)?px), it will be ignored.",
                result.Warnings[1].Message); 
        }
    }
}
