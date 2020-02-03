package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

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

}
