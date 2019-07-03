package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

public class ColumnSetPropertiesTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest() throws Exception
    {
        final String columnSetNoDefaultValuesJson =
            "{\"backgroundImage\":\"http://\"," +
            "\"bleed\":true," +
            "\"columns\":[" +
                "{\"items\":[]," +
                "\"type\":\"Column\"," +
                "\"width\":\"Auto\"}]," +
            "\"minHeight\":\"1px\"," +
            "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
            "\"style\":\"Attention\"," +
            "\"type\":\"ColumnSet\"," +
            "\"verticalContentAlignment\":\"Center\"}\n";

        ColumnSet columnSet = TestUtil.createMockColumnSet(TestUtil.createMockColumn());
        columnSet.SetBackgroundImage(TestUtil.createMockBackgroundImage());
        columnSet.SetBleed(true);
        columnSet.SetMinHeight(1);
        columnSet.SetSelectAction(TestUtil.createSampleSubmitAction());
        columnSet.SetStyle(ContainerStyle.Attention);
        columnSet.SetVerticalContentAlignment(VerticalContentAlignment.Center);

        Assert.assertEquals(columnSetNoDefaultValuesJson, columnSet.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest() throws Exception
    {
        final String columnSetNoDefaultValuesJson =
            "{\"backgroundImage\":\"http://\"," +
            "\"bleed\":true," +
            "\"columns\":[" +
                "{\"items\":[]," +
                "\"type\":\"Column\"," +
                "\"width\":\"Auto\"}]," +
            "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
            "\"height\":\"Stretch\"," +
            "\"id\":\"Sample id\"," +
            "\"isVisible\":false," +
            "\"minHeight\":\"1px\"," +
            "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
            "\"separator\":true," +
            "\"spacing\":\"medium\"," +
            "\"style\":\"Attention\"," +
            "\"type\":\"ColumnSet\"," +
            "\"verticalContentAlignment\":\"Center\"}\n";

        ColumnSet columnSet = TestUtil.createMockColumnSet(TestUtil.createMockColumn());
        columnSet.SetBackgroundImage(TestUtil.createMockBackgroundImage());
        columnSet.SetBleed(true);
        columnSet.SetFallbackType(FallbackType.Content);
        columnSet.SetFallbackContent(TestUtil.createMockImage());
        columnSet.SetHeight(HeightType.Stretch);
        columnSet.SetId("Sample id");
        columnSet.SetIsVisible(false);
        columnSet.SetMinHeight(1);
        columnSet.SetSelectAction(TestUtil.createSampleSubmitAction());
        columnSet.SetSeparator(true);
        columnSet.SetSpacing(Spacing.Medium);
        columnSet.SetStyle(ContainerStyle.Attention);
        columnSet.SetVerticalContentAlignment(VerticalContentAlignment.Center);

        Assert.assertEquals(columnSetNoDefaultValuesJson, columnSet.Serialize());
    }

    @Test
    public void ColumnsTest() throws Exception
    {
        {
            final String columnSetEmptyColumns = "{\"columns\":[],\"type\":\"ColumnSet\"}\n";
            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Assert.assertEquals(columnSetEmptyColumns, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(columnSetEmptyColumns), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(0, parsedColumnSet.GetColumns().size());
        }

        {
            final String columnSetWithColumn= "{\"columns\":[{\"items\":[],\"type\":\"Column\",\"width\":\"Auto\"}],\"type\":\"ColumnSet\"}\n";

            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Column column = TestUtil.createMockColumn();
            columnSet.GetColumns().add(column);
            Assert.assertEquals(columnSetWithColumn, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(columnSetWithColumn), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(1, parsedColumnSet.GetColumns().size());
        }
    }

}
