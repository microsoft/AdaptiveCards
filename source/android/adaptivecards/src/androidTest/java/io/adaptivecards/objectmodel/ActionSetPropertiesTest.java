package io.adaptivecards.objectmodel;

import android.drm.DrmStore;
import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.*;

public class ActionSetPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String actionSetWithActions =
            "{\"actions\":[" +
                "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "{\"card\":{" +
                "\"actions\":[" +
                "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}]," +
                "\"body\":[" +
                "{\"text\":\"Test\",\"type\":\"TextBlock\"}]," +
                "\"type\":\"AdaptiveCard\",\"version\":\"1.0\"" +
                "},\"type\":\"Action.ShowCard\"}," +
                "{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                "{\"targetElements\":[" +
                "\"id1\"," +
                "{\"elementId\":\"id2\",\"isVisible\":true}," +
                "{\"elementId\":\"id3\",\"isVisible\":false}]," +
                "\"type\":\"Action.ToggleVisibility\"}]," +
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"Sample id\"," +
                "\"isVisible\":false," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"ActionSet\"}\n";

        ActionSet actionSet = TestUtil.createSampleActionSet();
        actionSet.SetFallbackType(FallbackType.Content);
        actionSet.SetFallbackContent(TestUtil.createMockImage());
        actionSet.SetHeight(HeightType.Stretch);
        actionSet.SetId("Sample id");
        actionSet.SetIsVisible(false);
        actionSet.SetSeparator(true);
        actionSet.SetSpacing(Spacing.Medium);

        Assert.assertEquals(actionSetWithActions, actionSet.Serialize());
    }

    @Test
    public void ActionsTest() throws Exception
    {
        {
            final String actionSetEmptyActions = "{\"actions\":[],\"type\":\"ActionSet\"}\n";
            ActionSet actionSet = TestUtil.createMockActionSet();
            Assert.assertEquals(actionSetEmptyActions, actionSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(actionSetEmptyActions), "1.0");
            ActionSet parsedActionSet = TestUtil.castToActionSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(0, parsedActionSet.GetActions().size());
        }

        {
            final String actionSetWithActions =
                "{\"actions\":[" +
                    "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                    "{\"card\":{" +
                        "\"actions\":[" +
                            "{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}]," +
                        "\"body\":[" +
                            "{\"text\":\"Test\",\"type\":\"TextBlock\"}]," +
                        "\"type\":\"AdaptiveCard\",\"version\":\"1.0\"" +
                    "},\"type\":\"Action.ShowCard\"}," +
                    "{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "{\"targetElements\":[" +
                        "\"id1\"," +
                        "{\"elementId\":\"id2\",\"isVisible\":true}," +
                        "{\"elementId\":\"id3\",\"isVisible\":false}]," +
                    "\"type\":\"Action.ToggleVisibility\"}]," +
                "\"type\":\"ActionSet\"}\n";

            ActionSet actionSet = TestUtil.createSampleActionSet();
            Assert.assertEquals(actionSetWithActions, actionSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(actionSetWithActions), "1.0");
            ActionSet parsedActionSet = TestUtil.castToActionSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(4, parsedActionSet.GetActions().size());
        }
    }

}
