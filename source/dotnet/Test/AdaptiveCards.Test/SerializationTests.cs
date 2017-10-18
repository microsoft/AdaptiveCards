using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;

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
            card.MinVersion = "1.0";
            card.FallbackText = "Fallback Text";
            card.Speak = "Speak";
            card.Title = "My Title";
            card.BackgroundImage = "http://adaptivecards.io/content/cats/1.png";
            card.Body.Add(new AdaptiveTextBlock { Text = "Hello"});
            card.Actions.Add(new AdaptiveSubmitAction() { Title = "Action 1"});

            var expected = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""minVersion"": ""1.0"",
  ""fallbackText"": ""Fallback Text"",
  ""speak"": ""Speak"",
  ""title"": ""My Title"",
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
    }
}
