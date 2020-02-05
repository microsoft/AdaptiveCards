// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

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

        [TestMethod]
        public void ParseInvalidAction()
        {
            string url = "http://adaptivecards.io/content/cats/1.png";
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
	""type"": ""AdaptiveCard"",
	""version"": ""1.0"",
	""body"": [
		{
			""type"": ""Image"",
			""url"": """+ url + @""",
			""selectAction"": {
				""type"": ""Invalid Action"",
				""url"": ""https://www.youtube.com/watch?v=dQw4w9WgXcQ""
			}
		}
	]
}";

            var result = AdaptiveCard.FromJson(json);

            var card = result.Card;
            Assert.IsNotNull(card);

            Assert.IsTrue(result.Warnings.Count == 1);

            AdaptiveImage image = (AdaptiveImage) card.Body[0];
            Assert.AreEqual(image.Url, url);
            Assert.IsNull(image.SelectAction);

        }

        [TestMethod]
        public void ParseStyle()
        {
            var json = @"{
  ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.1"",
  ""body"": [ ],
  ""actions"": [
    {
      ""type"": ""Action.OpenUrl"",
      ""style"": ""default"",
      ""url"": ""http://adaptivecards.io"",
      ""title"": ""Action.Default""
    },
    {
      ""type"": ""Action.OpenUrl"",
      ""style"": ""positive"",
      ""url"": ""http://adaptivecards.io"",
      ""title"": ""Action.Pawsitive""
    },
    {
      ""type"": ""Action.OpenUrl"",
      ""style"": ""destructive"",
      ""url"": ""http://adaptivecards.io"",
      ""title"": ""Action.Destructive""
    }
  ]
}";

            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);

            var actions = result.Card.Actions;

            Assert.AreEqual(3, actions.Count);
            Assert.AreEqual("default", actions[0].Style);
            Assert.AreEqual("positive", actions[1].Style);
            Assert.AreEqual("destructive", actions[2].Style);
        }

        [TestMethod]
        public void ParseToggleVisibility()
        {
            string url = "http://adaptivecards.io/content/cats/1.png";
            var json = @"{
  ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""Image"",
      ""url"": """ + url + @""",
      ""selectAction"": {
        ""type"": ""Action.ToggleVisibility"",
        ""targetElements"": [
          ""id1"",
          { ""elementId"": ""id2"", ""isVisible"": false },
          { ""elementId"": ""id3"", ""isVisible"": true }
        ]
      }
    }
  ],
  ""actions"": [ ]
}";

            var result = AdaptiveCard.FromJson(json);
            Assert.IsNotNull(result.Card);

            var body = result.Card.Body;
            Assert.AreEqual(1, body.Count);

            AdaptiveAction toggleVisibilityAction = (body[0] as AdaptiveImage).SelectAction;
            Assert.IsNotNull(toggleVisibilityAction);

            Assert.IsInstanceOfType(toggleVisibilityAction, typeof(AdaptiveToggleVisibilityAction));

            List<AdaptiveTargetElement> targetElements = (toggleVisibilityAction as AdaptiveToggleVisibilityAction).TargetElements;

            Assert.AreEqual(3, targetElements.Count);

            AdaptiveTargetElement targetElement = targetElements[0];
            Assert.AreEqual("id1", targetElement.ElementId);
            Assert.IsNull(targetElement.IsVisible);

            targetElement = targetElements[1];
            Assert.AreEqual("id2", targetElement.ElementId);
            Assert.IsTrue(targetElement.IsVisible == false);

            targetElement = targetElements[2];
            Assert.AreEqual("id3", targetElement.ElementId);
            Assert.IsTrue(targetElement.IsVisible == true);
        }
    }
}
