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

        public void RoundTripTest(string expectedCard, string cardInTest)
        {
            AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(cardInTest);

            Assert.IsTrue(parseResult.Warnings.Count == 0);

            Assert.AreEqual(expectedCard, parseResult?.Card.ToJson());
        }

        [TestMethod]
        public void TestActions_SerializationOfIsEnable()
        {
            var card = Utilities.BuildASimpleTestCard();

            var element = Utilities.GetAdaptiveElementWithId(card, "submitAction");

            Assert.IsNotNull(element);

            AdaptiveAction submitAction = element as AdaptiveAction;

            Assert.IsTrue(submitAction.IsEnabled);

            var expectedCard = Utilities.BuildASimpleTestCard();

            var expectedPayloadValue = Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(expectedCard, submitAction.Id);

            Assert.AreEqual(expectedPayloadValue, card.ToJson());

            SerializableDictionary<string, object> expectedProperty = new SerializableDictionary<string, object>() { ["isEnabled"] = false };

            expectedPayloadValue = Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(expectedCard, submitAction.Id, expectedProperty);

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

            var element = Utilities.GetAdaptiveElementWithId(cardInTest, "Container");

            Assert.IsNotNull(element);

            AdaptiveContainer container = element as AdaptiveContainer;

            Assert.IsTrue(container.SelectAction.IsEnabled);

            var expectedPayloadValue = Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(expectedCard, "Container");

            Assert.AreEqual(expectedPayloadValue, cardInTest.ToJson());

            SerializableDictionary<string, object> expectedProperty = new SerializableDictionary<string, object>() { ["isEnabled"] = false };

            expectedPayloadValue = Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(expectedCard, "Container", expectedProperty);

            container.SelectAction.IsEnabled = false;

            var cardInJson = cardInTest.ToJson();

            Assert.AreEqual(expectedPayloadValue, cardInTest.ToJson());

            RoundTripTest(expectedPayloadValue, cardInJson);
        }

        [TestMethod]
        public void TestActions_SerializationOfMode()
        {
            var card = Utilities.BuildASimpleTestCard();

            var element = Utilities.GetAdaptiveElementWithId(card, "submitAction");

            AdaptiveAction submitAction = element as AdaptiveAction;

            Assert.AreEqual(submitAction.Mode, AdaptiveActionMode.Primary);

            var expectedCard = Utilities.BuildASimpleTestCard();

            var expectedJSON = Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(expectedCard, submitAction.Id);

            submitAction.Mode = AdaptiveActionMode.Primary;

            Assert.AreEqual(expectedJSON, card.ToJson());

            var expectedProperty = new SerializableDictionary<string, object>() { ["mode"] = "secondary"};

            expectedJSON = Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(expectedCard, submitAction.Id, expectedProperty);

            submitAction.Mode = AdaptiveActionMode.Secondary;

            var cardJson = card.ToJson();

            Assert.AreEqual(expectedJSON, cardJson);

            RoundTripTest(expectedJSON, cardJson);
        }

        [TestMethod]
        public void TestActions_SerializationOfModeWithInvalidValue()
        {
            var card = Utilities.BuildASimpleTestCard();

            var expectedCard = Utilities.BuildASimpleTestCard();

            var badValue = new SerializableDictionary<string, object>() { ["mode"] = "randomBadValue"};

            var element = Utilities.GetAdaptiveElementWithId(card, "submitAction");

            var cardJSON = Utilities.SerializeAfterManuallyWritingTestValueToAdaptiveElementWithTheGivenId(card, element.Id, badValue);

            var parseResult = AdaptiveCard.FromJson(cardJSON);

            Assert.IsTrue(parseResult.Warnings.Count > 0);

            element = Utilities.GetAdaptiveElementWithId(parseResult.Card, "submitAction");

            Assert.AreEqual((element as AdaptiveAction)?.Mode, AdaptiveActionMode.Primary);
        }

        [TestMethod]
        public void TestActions_Tooltips()
        {
            const string tooltipText = "this button submits the input";

            var tooltipValue = new SerializableDictionary<string, object>() { ["tooltip"] = tooltipText};

            var expectedCardJSON = Utilities.BuildExpectedCardJSON("submitAction", tooltipValue);

            var parseResult = AdaptiveCard.FromJson(expectedCardJSON);

            var testElement = Utilities.GetAdaptiveElementWithId(parseResult.Card, "submitAction");

            Assert.AreEqual((testElement as AdaptiveAction)?.Tooltip, tooltipText);
        }

        [TestMethod]
        public void TestActions_TooltipsRoundTrip()
        {
            const string tooltipText = "this button submits the input";

            var cardInTest = Utilities.BuildASimpleTestCard();

            var testElement = Utilities.GetAdaptiveElementWithId(cardInTest, "submitAction") as AdaptiveAction;

            Assert.IsNotNull(testElement);

            testElement.Tooltip = tooltipText;

            var tooltipValue = new SerializableDictionary<string, object>() { ["tooltip"] = tooltipText};

            var expectedCardJSON = Utilities.BuildExpectedCardJSON("submitAction", tooltipValue);

            RoundTripTest(expectedCardJSON, cardInTest.ToJson());
        }

        [TestMethod]
        public void TestActions_TooltipsSelectAction()
        {
            var cardInTest = Utilities.BuildASimpleTestCard();

            var expectedCard = Utilities.BuildASimpleTestCard();

            const string tooltipText = "this button submits the input";

            var tooltipValue = new SerializableDictionary<string, object>() { ["tooltip"] = tooltipText};

            var container = Utilities.GetAdaptiveElementWithId(expectedCard, "container") as AdaptiveContainer;

            Assert.IsNotNull(container);

            container.SelectAction.AdditionalProperties = tooltipValue;

            var testElement = Utilities.GetAdaptiveElementWithId(cardInTest, "container") as AdaptiveContainer;

            Assert.IsNotNull(testElement);

            testElement.SelectAction.Tooltip = tooltipText;

            RoundTripTest(expectedCard.ToJson(), cardInTest.ToJson());
        }

        [TestMethod]
        public void TestActions_TooltipsSelectActionDeserialization()
        {
            var expectedCard = Utilities.BuildASimpleTestCard();

            const string tooltipText = "this button submits the input";

            var tooltipValue = new SerializableDictionary<string, object>() { ["tooltip"] = tooltipText};

            var container = Utilities.GetAdaptiveElementWithId(expectedCard, "container") as AdaptiveContainer;

            Assert.IsNotNull(container);

            container.SelectAction.AdditionalProperties = tooltipValue;

            var expectedCardJSON = expectedCard.ToJson();

            var parseResult = AdaptiveCard.FromJson(expectedCardJSON);

            Assert.AreEqual(0, parseResult.Warnings.Count);

            var deserializedContainer = Utilities.GetAdaptiveElementWithId(parseResult.Card, "container") as AdaptiveContainer;

            Assert.IsNotNull(deserializedContainer);

            Assert.AreEqual(tooltipText, deserializedContainer.SelectAction.Tooltip);
        }
    }
}
