// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using Windows.Data.Json;

namespace UWPUnitTests
{
    [TestClass]
    public class ParserRegistrationTests
    {
        [TestMethod]
        public void ElementParserRegistraton_DefaultElementsTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();
            List<AdaptiveWarning> warnings = new List<AdaptiveWarning>();

            JsonObject jsonObject;

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"ActionSet\",\"id\":\"ActionSetId\"}", out jsonObject));
            Assert.AreEqual(ElementType.ActionSet, elementParserRegistration.Get("ActionSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.ChoiceSet\",\"id\":\"ChoiceSetId\", \"choices\":[{\"type\":\"Input.Choice\",\"title\":\"title\",\"value\":\"value\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.ChoiceSetInput, elementParserRegistration.Get("Input.ChoiceSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"ColumnSet\"}", out jsonObject));
            Assert.AreEqual(ElementType.ColumnSet, elementParserRegistration.Get("ColumnSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Container\", \"items\":[]}", out jsonObject));
            Assert.AreEqual(ElementType.Container, elementParserRegistration.Get("Container").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Date\", \"id\":\"DateId\"}", out jsonObject));
            Assert.AreEqual(ElementType.DateInput, elementParserRegistration.Get("Input.Date").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"FactSet\", \"facts\":[{\"title\":\"title\",\"value\":\"value\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.FactSet, elementParserRegistration.Get("FactSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Image\", \"url\":\"www.foo.com\"}", out jsonObject));
            Assert.AreEqual(ElementType.Image, elementParserRegistration.Get("Image").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"ImageSet\", \"images\":[{\"type\":\"Image\", \"url\":\"www.foo.com\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.ImageSet, elementParserRegistration.Get("ImageSet").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Media\", \"sources\":[{\"mimeType\":\"foo\",\"url\":\"www.foo.com\"}]}", out jsonObject));
            Assert.AreEqual(ElementType.Media, elementParserRegistration.Get("Media").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Number\", \"id\":\"NumberId\"}", out jsonObject));
            Assert.AreEqual(ElementType.NumberInput, elementParserRegistration.Get("Input.Number").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"TextBlock\",\"text\":\"Hello World\"}", out jsonObject));
            Assert.AreEqual(ElementType.TextBlock, elementParserRegistration.Get("TextBlock").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Text\", \"id\":\"TextId\"}", out jsonObject));
            Assert.AreEqual(ElementType.TextInput, elementParserRegistration.Get("Input.Text").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Time\", \"id\":\"TimeId\"}", out jsonObject));
            Assert.AreEqual(ElementType.TimeInput, elementParserRegistration.Get("Input.Time").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Input.Toggle\", \"id\":\"ToggleId\", \"title\":\"title\"}", out jsonObject));
            Assert.AreEqual(ElementType.ToggleInput, elementParserRegistration.Get("Input.Toggle").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ElementType);
        }

        class TestCustomElement : IAdaptiveCardElement
        {
            public TestCustomElement(IAdaptiveCardElement internalTextBlock)
            {
                InternalTextBlock = internalTextBlock;
            }

            public IAdaptiveCardElement InternalTextBlock { get; set; }
            public IAdaptiveActionElement InternalSubmitAction { get; set; }

            public IAdaptiveCardElement FallbackContent { get; }
            public FallbackType FallbackType { get; }

            public JsonObject ToJson()
            {
                return new JsonObject();
            }
            public JsonObject AdditionalProperties { get; set; }
            public ElementType ElementType { get { return ElementType.Custom; } }
            public string ElementTypeString { get { return "TestCustomElement"; } }
            public HeightType Height { get; set; }
            public string Id { get { return "TestID"; } set { } }
            public bool Separator { get; set; }
            public Spacing Spacing { get; set; }
            public bool IsVisible { get; set; }
            public UInt32 MinHeight { get; set; }
            IAdaptiveCardElement IAdaptiveCardElement.FallbackContent { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
            FallbackType IAdaptiveCardElement.FallbackType { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
            public IList<AdaptiveRequirement> Requirements { get; set; }
        };
        class TestElementParser : IAdaptiveElementParser
        {
            public IAdaptiveCardElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
            {
                // Validate that the registrations we were passed include the custom parsers
                Assert.IsNotNull(elementParsers.Get("TestCustomElement"));
                Assert.IsNotNull(actionParsers.Get("TestActionElement"));

                JsonObject jsonTextBlock = inputJson.GetNamedObject("internalTextBlock");
                var textBlockParser = elementParsers.Get("TextBlock");

                IAdaptiveCardElement textBlockElement = textBlockParser.FromJson(jsonTextBlock, elementParsers, actionParsers, warnings);
                return new TestCustomElement(textBlockElement) as IAdaptiveCardElement;
            }
        };

        [TestMethod]
        public void ElementParserRegistraton_CustomElementTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();

            actionParserRegistration.Set("TestActionElement", new TestActionParser());
            elementParserRegistration.Set("TestCustomElement", new TestElementParser());
            IAdaptiveElementParser testElementParserRetrieved = elementParserRegistration.Get("TestCustomElement");
            Assert.IsNotNull(testElementParserRetrieved);
            Assert.IsNotNull(testElementParserRetrieved as TestElementParser);

            String testCard =
                "{" +
                "   \"type\":\"AdaptiveCard\"," +
                "   \"version\":\"1.0\"," +
                "   \"body\":" +
                "   [" +
                "       {" +
                "           \"type\":\"TestCustomElement\"," +
                "           \"internalTextBlock\":" +
                "           {" +
                "               \"type\":\"TextBlock\"," +
                "               \"text\":\"Here is some text\"" +
                "           }" +
                "       }" +
                "   ]" +
                "}";

            AdaptiveCard card = AdaptiveCard.FromJsonString(testCard, elementParserRegistration, actionParserRegistration).AdaptiveCard;
            Assert.IsNotNull(card);

            Assert.AreEqual(1, card.Body.Count);

            IAdaptiveCardElement cardElement = card.Body[0];
            Assert.IsNotNull(cardElement);

            Assert.AreEqual(ElementType.Custom, cardElement.ElementType);
            Assert.AreEqual("TestCustomElement", cardElement.ElementTypeString);

            TestCustomElement customElement = card.Body[0] as TestCustomElement;
            Assert.IsNotNull(customElement);

            Assert.AreEqual(ElementType.TextBlock, customElement.InternalTextBlock.ElementType);
        }

        [TestMethod]
        public void ActionParserRegistraton_DefaultActionsTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();
            List<AdaptiveWarning> warnings = new List<AdaptiveWarning>();

            JsonObject jsonObject;

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Action.OpenUrl\", \"url\":\"http:\\\\www.foo.com\"}", out jsonObject));
            Assert.AreEqual(ActionType.OpenUrl, actionParserRegistration.Get("Action.OpenUrl").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ActionType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Action.ShowCard\", \"card\":{\"type\":\"AdaptiveCard\", \"version\":\"1.0\"}}", out jsonObject));
            Assert.AreEqual(ActionType.ShowCard, actionParserRegistration.Get("Action.ShowCard").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ActionType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Action.Submit\"}", out jsonObject));
            Assert.AreEqual(ActionType.Submit, actionParserRegistration.Get("Action.Submit").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ActionType);

            Assert.IsTrue(JsonObject.TryParse("{\"type\":\"Action.ToggleVisibility\",\"targetElements\": [{\"elementId\":\"idToggle\"}]}", out jsonObject));
            Assert.AreEqual(ActionType.ToggleVisibility, actionParserRegistration.Get("Action.ToggleVisibility").FromJson(jsonObject, elementParserRegistration, actionParserRegistration, warnings).ActionType);
        }

        class TestCustomAction : IAdaptiveActionElement
        {
            public TestCustomAction(IAdaptiveActionElement internalSubmitAction)
            {
                InternalSubmitAction = internalSubmitAction;
            }

            public IAdaptiveActionElement InternalSubmitAction { get; set; }

            public JsonObject ToJson()
            {
                return new JsonObject();
            }
            public JsonObject AdditionalProperties { get; set; }
            public string Id { get { return "TestID"; } set { } }
            public ActionType ActionType { get { return ActionType.Custom; } }
            public IAdaptiveActionElement FallbackContent { get; }
            public FallbackType FallbackType { get; }
            public string ActionTypeString { get { return "TestCustomAction"; } }
            public string IconUrl { get; set; }
            public string Style { get; set; }
            public string Title { get; set; }
            IAdaptiveActionElement IAdaptiveActionElement.FallbackContent { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
            FallbackType IAdaptiveActionElement.FallbackType { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        };

        class TestActionParser : IAdaptiveActionParser
        {
            public IAdaptiveActionElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
            {
                // Validate that the registrations we were passed include the custom parsers
                Assert.IsNotNull(elementParsers.Get("TestCustomElement"));
                Assert.IsNotNull(actionParsers.Get("TestCustomAction"));

                JsonObject jsonSubmitAction = inputJson.GetNamedObject("internalSubmitAction");
                var submitActionParser = actionParsers.Get("Action.Submit");

                IAdaptiveActionElement submitAction = submitActionParser.FromJson(jsonSubmitAction, elementParsers, actionParsers, warnings);
                return new TestCustomAction(submitAction) as IAdaptiveActionElement;
            }
        };

        [TestMethod]
        public void ActionParserRegistraton_CustomActionTest()
        {
            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            AdaptiveElementParserRegistration elementParserRegistration = new AdaptiveElementParserRegistration();

            actionParserRegistration.Set("TestCustomAction", new TestActionParser());
            elementParserRegistration.Set("TestCustomElement", new TestElementParser());
            IAdaptiveActionParser testActionParserRetrieved = actionParserRegistration.Get("TestCustomAction");
            Assert.IsNotNull(testActionParserRetrieved);
            Assert.IsNotNull(testActionParserRetrieved as TestActionParser);

            String testCard =
                "{" +
                "   \"type\":\"AdaptiveCard\"," +
                "   \"version\":\"1.0\"," +
                "   \"body\":" +
                "   [" +
                "   ]," +
                "   \"actions\":" +
                "   [" +
                "       {" +
                "           \"type\":\"TestCustomAction\"," +
                "           \"internalSubmitAction\":" +
                "           {" +
                "               \"type\": \"Action.Submit\"" +
                "           }" +
                "       }" +
                "   ]" +
                "}";

            AdaptiveCard card = AdaptiveCard.FromJsonString(testCard, elementParserRegistration, actionParserRegistration).AdaptiveCard;
            Assert.IsNotNull(card);

            Assert.AreEqual(1, card.Actions.Count);

            IAdaptiveActionElement action = card.Actions[0];
            Assert.IsNotNull(action);

            Assert.AreEqual(ActionType.Custom, action.ActionType);
            Assert.AreEqual("TestCustomAction", action.ActionTypeString);

            TestCustomAction customElement = card.Actions[0] as TestCustomAction;
            Assert.IsNotNull(customElement);

            Assert.AreEqual(ActionType.Submit, customElement.InternalSubmitAction.ActionType);
        }
    }
}
