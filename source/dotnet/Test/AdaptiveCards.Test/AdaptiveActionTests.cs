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

        AdaptiveTypedElement GetAdaptiveElementWithId(AdaptiveCard card, string Id)
        {
            Stack<AdaptiveTypedElement> stack = new Stack<AdaptiveTypedElement>();
            
			foreach (var element in card.Body)
            {
                stack.Push(element);
            }
			
            foreach (var action in card.Actions)
            {
                stack.Push(action);
            }

            while (stack?.Count > 0)
            {
                var element = stack.Pop();
                if (element.Id == Id)
                {
                    return element;
                }
				
                if (element is AdaptiveCollectionElement)
                {
                    foreach (var childElement in element as AdaptiveCollectionElement)
                    {
                        stack.Push(childElement);
                    }
                }
            }
			
            return null;
        } 
		
        string SetUpExpectedPayloadValue(AdaptiveCard card, string id, SerializableDictionary<string, object> testProperty = null)
        {
            AdaptiveTypedElement element = GetAdaptiveElementWithId(card, id);
			
            if (element != null)
            {
                if (element is AdaptiveCollectionElement)
                {
                    (element as AdaptiveCollectionElement).SelectAction.AdditionalProperties = testProperty;
                }
                else
                {
                    element.AdditionalProperties = testProperty;
                }
            }

            return card.ToJson();
        }

        AdaptiveCard BuildASimpleTestCard()
        {
            AdaptiveCard card = new AdaptiveCard(new AdaptiveSchemaVersion("1.5"));

            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                Id = "submitAction",
                Title = "Action.Submit",
                DataJson = "{\"x\": 13}",
            };

            card.Actions.Add(submitAction);

            return card;
        }

        public void RoundTripTest(string expectedCard, string cardInTest)
        {
            AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(cardInTest);

            Assert.IsTrue(parseResult.Warnings.Count == 0);

            Assert.AreEqual(expectedCard, parseResult?.Card.ToJson());
        }
		
        [TestMethod]
        public void TestActions_SerializationOfIsEnable()
        {
            var card = BuildASimpleTestCard();

            var element = GetAdaptiveElementWithId(card, "submitAction");

            Assert.IsNotNull(element);

            AdaptiveAction submitAction = element as AdaptiveAction;

            Assert.IsTrue(submitAction.IsEnabled);

            var expectedCard = BuildASimpleTestCard();

            var expectedPayloadValue = SetUpExpectedPayloadValue(expectedCard, submitAction.Id);

            Assert.AreEqual(expectedPayloadValue, card.ToJson());

            SerializableDictionary<string, object> expectedProperty = new SerializableDictionary<string, object>() { ["isEnabled"] = false };

            expectedPayloadValue = SetUpExpectedPayloadValue(expectedCard, submitAction.Id, expectedProperty);

            submitAction.IsEnabled = false;

            var cardInJson = card.ToJson();

            Assert.AreEqual(expectedPayloadValue, cardInJson);

            RoundTripTest(expectedPayloadValue, cardInJson);
        }

        AdaptiveCard BuildASimpleCardWithSelectAction()
        {
            AdaptiveCard card = new AdaptiveCard(new AdaptiveSchemaVersion("1.5"));
            AdaptiveContainer container = new AdaptiveContainer();
            AdaptiveTextBlock textBlock = new AdaptiveTextBlock();
            textBlock.Text = "Hello World!";
            container.Items.Add(textBlock);
            container.Id = "Container";
            AdaptiveSubmitAction submitAction = new AdaptiveSubmitAction
            {
                Title = "Action.Submit",
                DataJson = "{\"x\": 13}",
            };

            container.SelectAction = submitAction;

            card.Body.Add(container);

            return card;
        }

        [TestMethod]
        public void TestActions_SerializationOfIsEnableInSelectAction()
        {
            var expectedCard = BuildASimpleCardWithSelectAction();
            var cardInTest = BuildASimpleCardWithSelectAction();

            var element = GetAdaptiveElementWithId(cardInTest, "Container");

            Assert.IsNotNull(element);

            AdaptiveContainer container = element as AdaptiveContainer;

            Assert.IsTrue(container.SelectAction.IsEnabled);

            var expectedPayloadValue = SetUpExpectedPayloadValue(expectedCard, "Container");

            Assert.AreEqual(expectedPayloadValue, cardInTest.ToJson());

            SerializableDictionary<string, object> expectedProperty = new SerializableDictionary<string, object>() { ["isEnabled"] = false };

            expectedPayloadValue = SetUpExpectedPayloadValue(expectedCard, "Container", expectedProperty);

            container.SelectAction.IsEnabled = false;

            var cardInJson = cardInTest.ToJson();

            Assert.AreEqual(expectedPayloadValue, cardInTest.ToJson());

            RoundTripTest(expectedPayloadValue, cardInJson);
        }
    }
}
