using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveActionTests
    {
        [TestMethod]
        public void ParseIconUrl()
        {
            var json = @"{
  ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""actions"": [
    {
      ""type"": ""Action.OpenUrl"",
      ""iconUrl"": ""http://adaptivecards.io/content/cats/1.png"",
      ""url"": ""http://adaptivecards.io"",
      ""title"": ""Open URL""
    }
  ]
}";
            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);

            var expectedIconUrl = "http://adaptivecards.io/content/cats/1.png";
            var actualIconUrl = result.Card.Actions[0].IconUrl;
            Assert.AreEqual(expectedIconUrl, actualIconUrl);
        }
    }
}
