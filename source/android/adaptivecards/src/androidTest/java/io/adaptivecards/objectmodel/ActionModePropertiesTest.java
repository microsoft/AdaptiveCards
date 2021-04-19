package io.adaptivecards.objectmodel;

import org.junit.Assert;
import org.junit.Test;

import java.io.IOException;
import java.util.List;

public class ActionModePropertiesTest
{

    static
    {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void test_AllSecondaryElementProperties() throws IOException
    {
        final String actions =
            "{\"actions\":[" +
                "{\"type\":\"Action.Submit\",\"title\":\"View\",\"data\":{\"key\":\"View\"},\"mode\":\"secondary\"}," +
                "{\"type\":\"Action.Submit\",\"title\":\"Edit\",\"data\":{\"key\":\"Edit\"},\"mode\":\"secondary\"}," +
                "{\"type\":\"Action.Submit\",\"title\":\"Delete\",\"data\":{\"key\":\"Delete\"},\"mode\":\"secondary\"}]," +
                "\"type\":\"ActionSet\"}";
        ActionSet parsedActionSet = getActionSet(actions);
        for (BaseActionElement actionElement : parsedActionSet.GetActions())
        {
            Assert.assertEquals(actionElement.GetMode(), Mode.Secondary);
        }
    }

    @Test
    public void test_mixedActionModeProperty() throws IOException
    {
        final String actions =
            "{\"type\":\"ActionSet\"," +
                "\"actions\":" +
                    "[{\"type\":\"Action.Submit\",\"title\":\"Action Submit\",\"data\":{\"key\":\"Submit from overflow menu\"},\"mode\":\"primary\"}," +
                    "{\"type\":\"Action.OpenUrl\",\"title\":\"OpenUrl\",\"url\":\"https://github.com/Microsoft/AdaptiveCards\",\"iconUrl\":\"https://scontent.ftpe5-1.fna.fbcdn.net/v/t1.0-9/122050521_10222320423416866_2987313765978046472_n.jpg?_nc_cat=103&ccb=2&_nc_sid=09cbfe&_nc_ohc=gLcNo1PMYHAAX_KI9HV&_nc_ht=scontent.ftpe5-1.fna&oh=1adaf81bd075ef9ba9d42c7eec78218a&oe=603E2FCE\",\"mode\":\"secondary\"}]}";
        ActionSet parsedActionSet = getActionSet(actions);
        for (BaseActionElement actionElement : parsedActionSet.GetActions())
        {
            if (actionElement.GetElementType() == ActionType.Submit)
            {
                Assert.assertEquals(actionElement.GetMode(), Mode.Primary);
            } else
            {
                Assert.assertEquals(actionElement.GetMode(), Mode.Secondary);
            }
        }
    }

    @Test
    public void test_ExceedMaxActions() throws IOException
    {
        final String actions =
            "{\"type\":\"ActionSet\"," +
                "\"actions\":" +
                    "[{\"type\":\"Action.Submit\",\"title\":\"Action 1\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 2\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 3\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 4\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 5\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 6\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 7\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 8\"}," +
                    "{\"type\":\"Action.Submit\",\"title\":\"Action 9\"}]}";

        ActionSet parsedActionSet = getActionSet(actions);
        final int total = 9;
        final int maxActions = 5; // default config
        final int secondaryActionListSize = total - maxActions;
        List<BaseActionElement> primaryActionElementList = parsedActionSet.GetActions().subList(0, maxActions);
        List<BaseActionElement> secondaryActionElementList = parsedActionSet.GetActions().subList(maxActions, total);

        Assert.assertEquals(maxActions, primaryActionElementList.size());
        Assert.assertEquals(secondaryActionListSize, secondaryActionElementList.size());
    }

    private ActionSet getActionSet(String actions) throws IOException
    {
        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(actions), "1.0");
        return TestUtil.castToActionSet(result.GetAdaptiveCard().GetBody().get(0));
    }
}
