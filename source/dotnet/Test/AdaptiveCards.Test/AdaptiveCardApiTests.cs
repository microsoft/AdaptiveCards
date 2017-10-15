using System;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveCardApiTests
    {
        /// <summary>
        /// Note that tests take a hard dependency on the items within this card. Do not change this payload.
        /// </summary>
        private const string SIMPLE_CARD = @"{
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

        private const string INVALID_CARD_MISSING_VERSION = @"{
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

        private const string INVALID_CARD_MISSING_TYPE = @"{
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
            AdaptiveCardParseResult result = AdaptiveCard.FromJson(SIMPLE_CARD);

            Assert.IsNotNull(result.Card);

            Assert.AreEqual(1, result.Card.Body.Count);
        }

        [TestMethod]
        public void TestParsingInvalidCardMissingVersion()
        {
            TestParsingInvalidCard(INVALID_CARD_MISSING_VERSION);
        }

        [TestMethod]
        public void TestParsingInvalidCardMissingType()
        {
            TestParsingInvalidCard(INVALID_CARD_MISSING_TYPE);
        }

        private void TestParsingInvalidCard(string cardPayload)
        {
            AdaptiveCardParseResult result = AdaptiveCard.FromJson(cardPayload);

            Assert.IsNull(result.Card);
        }

        [TestMethod]
        public void TestChoiceSetExpanded()
        {
            var card = new AdaptiveCard();
            card.Body.Add(new ChoiceSet()
            {
                Style = ChoiceInputStyle.Expanded
            });

            var expected = @"""style"":""expanded""";

            StringAssert.Contains(card.ToJson(), expected);
        }
    }
}
