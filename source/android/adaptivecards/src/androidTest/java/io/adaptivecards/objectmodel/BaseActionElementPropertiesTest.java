package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import io.adaptivecards.renderer.Util;

import static org.junit.Assert.*;

public class BaseActionElementPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest() throws Exception
    {
        final String openUrlActionNoDefaultValues =
            "{\"fallback\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                "\"iconUrl\":\"http://\"," +
                "\"id\":\"Sample id\"," +
                "\"style\":\"positive\"," +
                "\"title\":\"Sample Title\"," +
                "\"type\":\"Action.OpenUrl\"," +
                "\"url\":\"http://\"}\n";

        OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
        openUrlAction.SetFallbackType(FallbackType.Content);
        openUrlAction.SetFallbackContent(TestUtil.createSampleSubmitAction());
        openUrlAction.SetIconUrl("http://");
        openUrlAction.SetId("Sample id");
        openUrlAction.SetStyle("positive");
        openUrlAction.SetTitle("Sample Title");

        Assert.assertEquals(openUrlActionNoDefaultValues, openUrlAction.Serialize());
    }

    @Test
    public void FallbackContentTest() throws Exception
    {
        {
            final String openUrlJson = "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetFallbackContent(null);
            Assert.assertEquals(openUrlJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals(null, parsedOpenUrlAction.GetFallbackContent());
        }

        {
            final String openUrlActionDropFallbackJson = "{\"fallback\":\"drop\",\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetFallbackType(FallbackType.Drop);
            Assert.assertEquals(openUrlActionDropFallbackJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionDropFallbackJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals(FallbackType.Drop, parsedOpenUrlAction.GetFallbackType());
        }

        {
            final String openUrlActionSubmitActionFallbackJson =
                "{\"fallback\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetFallbackType(FallbackType.Content);
            openUrlAction.SetFallbackContent(TestUtil.createSampleSubmitAction());
            Assert.assertEquals(openUrlActionSubmitActionFallbackJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionSubmitActionFallbackJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals(FallbackType.Content, parsedOpenUrlAction.GetFallbackType());

            BaseActionElement fallbackBaseActionElement = TestUtil.castToBaseActionElement(parsedOpenUrlAction.GetFallbackContent());
            Assert.assertEquals(ActionType.Submit, fallbackBaseActionElement.GetElementType());

            SubmitAction fallbackSubmitAction = TestUtil.castToSubmitAction(fallbackBaseActionElement);
            Assert.assertEquals("{\"data\":\"Some data\"}\n", fallbackSubmitAction.GetDataJson());
        }

    }

    @Test
    public void IdTest() throws Exception
    {
        {
            final String openUrlActionJson = "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("", parsedOpenUrlAction.GetId());

            openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetId("");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("", parsedOpenUrlAction.GetId());
        }

        {
            final String openUrlActionJson = "{\"id\":\"Sample Id\",\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetId("Sample Id");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("Sample Id", parsedOpenUrlAction.GetId());
        }
    }

    @Test
    public void IconUrlTest() throws Exception
    {
        {
            final String openUrlActionJson = "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("", parsedOpenUrlAction.GetIconUrl());

            openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetIconUrl("");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("", parsedOpenUrlAction.GetIconUrl());
        }

        {
            final String openUrlActionJson = "{\"iconUrl\":\"http://\",\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetIconUrl("http://");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("http://", parsedOpenUrlAction.GetIconUrl());
        }
    }

    @Test
    public void StyleTest() throws Exception
    {
        {
            final String openUrlActionJson = "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("default", parsedOpenUrlAction.GetStyle());

            openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetStyle("");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("default", parsedOpenUrlAction.GetStyle());
        }

        {
            final String openUrlActionJson = "{\"style\":\"positive\",\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetStyle("positive");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("positive", parsedOpenUrlAction.GetStyle());
        }
    }

    @Test
    public void TitleTest() throws Exception
    {
        {
            final String openUrlActionJson = "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("default", parsedOpenUrlAction.GetStyle());

            openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetTitle("");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("", parsedOpenUrlAction.GetTitle());
        }

        {
            final String openUrlActionJson = "{\"title\":\"Sample Title\",\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            openUrlAction.SetTitle("Sample Title");
            Assert.assertEquals(openUrlActionJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("Sample Title", parsedOpenUrlAction.GetTitle());
        }
    }

    @Test
    public void ExtractBaseActionPropertiesFromStringTest() throws Exception
    {
        class MockCustomAction extends BaseActionElement
        {
            public MockCustomAction(ActionType type) {
                super(type);
            }
        }

        class MockCustomActionParser extends ActionElementParser
        {
            // This is the method that is called during parsing
            @Override
            public BaseActionElement Deserialize(ParseContext context, JsonValue value)
            {
                MockCustomAction customAction = new MockCustomAction(ActionType.Custom);
                Util.deserializeBaseActionProperties(context, value, customAction);

                Assert.assertEquals(customAction.GetIconUrl(), "http://");
                Assert.assertEquals(customAction.GetId(), "Sample id");
                Assert.assertEquals(customAction.GetStyle(), "positive");
                String title = customAction.GetTitle();
                Assert.assertEquals(title, "Sample Title");
                Assert.assertEquals(customAction.GetFallbackType(), FallbackType.Content);

                // TODO: We need an util class method to cast from BaseElement to BaseCardElement
                Assert.assertEquals(customAction.GetFallbackContent().GetElementTypeString(), "Action.Submit");

                return customAction;
            }

            @Override
            public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
            {
                MockCustomAction customAction = new MockCustomAction(ActionType.Custom);
                Util.deserializeBaseActionPropertiesFromString(context, jsonString, customAction);

                Assert.assertEquals(customAction.GetIconUrl(), "http://");
                Assert.assertEquals(customAction.GetId(), "Sample id");
                Assert.assertEquals(customAction.GetStyle(), "positive");
                Assert.assertEquals(customAction.GetTitle(), "Sample Title");
                Assert.assertEquals(customAction.GetFallbackType(), FallbackType.Content);

                // TODO: We need an util class method to cast from BaseElement to BaseCardElement
                Assert.assertEquals(customAction.GetFallbackContent().GetElementTypeString(), "Action.Submit");

                return customAction;
            }
        }

        final String customElementJson = "{\"fallback\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
            "\"iconUrl\":\"http://\"," +
            "\"id\":\"Sample id\"," +
            "\"style\":\"positive\"," +
            "\"title\":\"Sample Title\"," +
            "\"type\":\"CustomAction\"}\n";

        ActionParserRegistration actionParserRegistration = new ActionParserRegistration();
        MockCustomActionParser actionParser = new MockCustomActionParser();
        actionParserRegistration.AddParser("CustomAction", actionParser);
        ParseContext parseContext = new ParseContext(null, actionParserRegistration);

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(customElementJson), "1.0", parseContext);
        AdaptiveCard adaptiveCard = result.GetAdaptiveCard();

        BaseActionElement action = adaptiveCard.GetActions().get(0);

        // Verify that the element in the card has all the properties
        Assert.assertEquals(action.GetIconUrl(), "http://");
        Assert.assertEquals(action.GetId(), "Sample id");
        Assert.assertEquals(action.GetStyle(), "positive");
        Assert.assertEquals(action.GetTitle(), "Sample Title");
        Assert.assertEquals(action.GetFallbackType(), FallbackType.Content);

        // TODO: We need an util class method to cast from BaseElement to BaseCardElement
        Assert.assertEquals(action.GetFallbackContent().GetElementTypeString(), "Action.Submit");

        // Verify that the DeserializeFromString method works
        actionParser.DeserializeFromString(parseContext, customElementJson);
    }

}
