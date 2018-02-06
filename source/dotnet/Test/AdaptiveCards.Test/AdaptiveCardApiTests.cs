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
    }
}
