package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.*;

public class OpenUrlActionPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {

    }

    @Test
    public void urlTest() throws Exception
    {
        {
            final String openUrlActionWithNoUrl = "{\"type\":\"Action.OpenUrl\"}";

            try
            {
                AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionWithNoUrl), "1.0");
                Assert.fail();
            }
            catch (Exception e){
                Assert.fail();
            }
        }

        {
            OpenUrlAction openUrlAction = TestUtil.createMockOpenUrlAction();
            Assert.assertEquals(s_defaultOpenUrlJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(s_defaultOpenUrlJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("", parsedOpenUrlAction.GetUrl());
        }

        {
            final String openUrlActionUrlJson = "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}\n";

            OpenUrlAction openUrlAction = TestUtil.createSampleOpenUrlAction();
            Assert.assertEquals(openUrlActionUrlJson, openUrlAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(openUrlActionUrlJson), "1.0");
            OpenUrlAction parsedOpenUrlAction = TestUtil.castToOpenUrlAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("http://", parsedOpenUrlAction.GetUrl());
        }
    }

    public static final String s_defaultOpenUrlJson = "{\"type\":\"Action.OpenUrl\",\"url\":\"\"}\n";

}
