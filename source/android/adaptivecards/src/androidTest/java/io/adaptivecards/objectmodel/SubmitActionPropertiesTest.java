package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.*;

public class SubmitActionPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {

    }

    @Test
    public void dataJsonTest() throws Exception
    {

        {
            SubmitAction submitAction = TestUtil.createMockSubmitAction();
            Assert.assertEquals(s_defaultSubmitAction, submitAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(s_defaultSubmitAction), "1.0");
            SubmitAction parsedSubmitAction = TestUtil.castToSubmitAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("null\n", parsedSubmitAction.GetDataJson());
        }

        {
            final String submitActionWithEmptyData = "{\"data\":{},\"type\":\"Action.Submit\"}";

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(submitActionWithEmptyData), "1.0");
            SubmitAction parsedSubmitAction = TestUtil.castToSubmitAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("{}\n", parsedSubmitAction.GetDataJson());
        }

        {
            final String submitActionDataJson = "{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}\n";

            SubmitAction submitAction = TestUtil.createSampleSubmitAction();
            Assert.assertEquals(submitActionDataJson, submitAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(submitActionDataJson), "1.0");
            SubmitAction parsedSubmitAction = TestUtil.castToSubmitAction(result.GetAdaptiveCard().GetActions().get(0));
            Assert.assertEquals("{\"data\":\"Some data\"}\n", parsedSubmitAction.GetDataJson());
        }

    }

    private static final String s_defaultSubmitAction = "{\"type\":\"Action.Submit\"}\n";
}
