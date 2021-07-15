package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.*;

public class ToggleVisibilityActionPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {

    }

    @Test
    public void targetElementTest() throws Exception
    {
        {
            ToggleVisibilityAction toggleVisibilityAction = TestUtil.createMockToggleVisibilityAction();
            Assert.assertEquals(s_defaultToggleVisibilityActionJson, toggleVisibilityAction.Serialize());

            try
            {
                AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(s_defaultToggleVisibilityActionJson), "1.0");
            }
            catch (IOException e)
            {
                Assert.assertEquals(true, e.getMessage().contains("Could not parse required key: targetElements."));
            }
            catch (Exception e)
            {
                Assert.fail();
            }
        }

        {
            final String toggleVisibilityActionTargetJson = "{\"targetElements\":[\"id\"],\"type\":\"Action.ToggleVisibility\"}\n";

            ToggleVisibilityAction toggleVisibilityAction = TestUtil.createMockToggleVisibilityAction(TestUtil.createTarget("id", null));
            Assert.assertEquals(toggleVisibilityActionTargetJson, toggleVisibilityAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(toggleVisibilityActionTargetJson), "1.0");
            ToggleVisibilityAction parsedToggleVisibilityAction = TestUtil.castToToggleVisibilityAction(result.GetAdaptiveCard().GetActions().get(0));

            Assert.assertEquals(1, parsedToggleVisibilityAction.GetTargetElements().size());
            Assert.assertEquals("id", parsedToggleVisibilityAction.GetTargetElements().get(0).GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleToggle, parsedToggleVisibilityAction.GetTargetElements().get(0).GetIsVisible());

            final String toggleVisibilityActionTargetAsObjectJson = "{\"targetElements\":[{\"elementId\":\"id\"}],\"type\":\"Action.ToggleVisibility\"}\n";

            result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(toggleVisibilityActionTargetAsObjectJson), "1.0");
            parsedToggleVisibilityAction = TestUtil.castToToggleVisibilityAction(result.GetAdaptiveCard().GetActions().get(0));

            Assert.assertEquals(1, parsedToggleVisibilityAction.GetTargetElements().size());
            Assert.assertEquals("id", parsedToggleVisibilityAction.GetTargetElements().get(0).GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleToggle, parsedToggleVisibilityAction.GetTargetElements().get(0).GetIsVisible());
        }

        {
            final String toggleVisibilityActionTargetTrueJson = "{\"targetElements\":[{\"elementId\":\"id\",\"isVisible\":true}],\"type\":\"Action.ToggleVisibility\"}\n";

            ToggleVisibilityAction toggleVisibilityAction = TestUtil.createMockToggleVisibilityAction(TestUtil.createTarget("id", true));
            Assert.assertEquals(toggleVisibilityActionTargetTrueJson, toggleVisibilityAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(toggleVisibilityActionTargetTrueJson), "1.0");
            ToggleVisibilityAction parsedToggleVisibilityAction = TestUtil.castToToggleVisibilityAction(result.GetAdaptiveCard().GetActions().get(0));

            Assert.assertEquals(1, parsedToggleVisibilityAction.GetTargetElements().size());
            Assert.assertEquals("id", parsedToggleVisibilityAction.GetTargetElements().get(0).GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleTrue, parsedToggleVisibilityAction.GetTargetElements().get(0).GetIsVisible());
        }

        {
            final String toggleVisibilityActionTargetFalseJson = "{\"targetElements\":[{\"elementId\":\"id\",\"isVisible\":false}],\"type\":\"Action.ToggleVisibility\"}\n";

            ToggleVisibilityAction toggleVisibilityAction = TestUtil.createMockToggleVisibilityAction(TestUtil.createTarget("id", false));
            Assert.assertEquals(toggleVisibilityActionTargetFalseJson, toggleVisibilityAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(toggleVisibilityActionTargetFalseJson), "1.0");
            ToggleVisibilityAction parsedToggleVisibilityAction = TestUtil.castToToggleVisibilityAction(result.GetAdaptiveCard().GetActions().get(0));

            Assert.assertEquals(1, parsedToggleVisibilityAction.GetTargetElements().size());
            Assert.assertEquals("id", parsedToggleVisibilityAction.GetTargetElements().get(0).GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleFalse, parsedToggleVisibilityAction.GetTargetElements().get(0).GetIsVisible());
        }

        {
            final String toggleVisibilityActionMultipleTargetsJson =
                "{\"targetElements\":[\"id1\",{\"elementId\":\"id2\",\"isVisible\":true}," +
                    "{\"elementId\":\"id3\",\"isVisible\":false}],\"type\":\"Action.ToggleVisibility\"}\n";

            ToggleVisibilityAction toggleVisibilityAction =
                TestUtil.createMockToggleVisibilityAction(
                    TestUtil.createTarget("id1", null),
                    TestUtil.createTarget("id2", true),
                    TestUtil.createTarget("id3", false));

            Assert.assertEquals(toggleVisibilityActionMultipleTargetsJson, toggleVisibilityAction.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseActionJsonInCard(toggleVisibilityActionMultipleTargetsJson), "1.0");
            ToggleVisibilityAction parsedToggleVisibilityAction = TestUtil.castToToggleVisibilityAction(result.GetAdaptiveCard().GetActions().get(0));

            ToggleVisibilityTargetVector targets = parsedToggleVisibilityAction.GetTargetElements();
            Assert.assertEquals(3, targets.size());

            ToggleVisibilityTarget target = targets.get(0);
            Assert.assertEquals("id1", target.GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleToggle, target.GetIsVisible());

            target = targets.get(1);
            Assert.assertEquals("id2", target.GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleTrue, target.GetIsVisible());

            target = targets.get(2);
            Assert.assertEquals("id3", target.GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleFalse, target.GetIsVisible());
        }
    }

    public static final String s_defaultToggleVisibilityActionJson = "{\"targetElements\":[],\"type\":\"Action.ToggleVisibility\"}\n";

}
