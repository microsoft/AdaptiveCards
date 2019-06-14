package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

public class ColumnPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest() throws Exception
    {
        {
            final String columnWidth = "{\"columns\":[{\"items\":[],\"type\":\"Column\",\"width\":\"stretch\"}],\"type\":\"ColumnSet\"}\n";

            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Column column = TestUtil.createMockColumn();
            column.SetPixelWidth(50);
            column.SetWidth("stretch");
            columnSet.GetColumns().add(column);
            Assert.assertEquals(columnWidth, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(columnWidth), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("stretch", parsedColumnSet.GetColumns().get(0).GetWidth());
            Assert.assertEquals(0, parsedColumnSet.GetColumns().get(0).GetPixelWidth());
        }

        {
            final String columnPixelWidth = "{\"columns\":[{\"items\":[],\"type\":\"Column\",\"width\":\"50px\"}],\"type\":\"ColumnSet\"}\n";
            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Column column = TestUtil.createMockColumn();
            column.SetWidth("stretch");
            column.SetPixelWidth(50);
            columnSet.GetColumns().add(column);

            Assert.assertEquals(columnPixelWidth, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(columnPixelWidth), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("50px", parsedColumnSet.GetColumns().get(0).GetWidth());
            Assert.assertEquals(50, parsedColumnSet.GetColumns().get(0).GetPixelWidth());
        }
    }

    @Test
    public void AllPropertiesWithInheritedTest() throws Exception
    {
        {
            final String columnWidth =
                "{\"columns\":[" +
                    "{\"backgroundImage\":\"http://\"," +
                    "\"bleed\":true," +
                    "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                    "\"height\":\"Stretch\"," +
                    "\"id\":\"Sample id\"," +
                    "\"isVisible\":false," +
                    "\"items\":[]," +
                    "\"minHeight\":\"1px\"," +
                    "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"separator\":true," +
                    "\"spacing\":\"medium\"," +
                    "\"style\":\"Attention\"," +
                    "\"type\":\"Column\"," +
                    "\"verticalContentAlignment\":\"Center\"," +
                    "\"width\":\"stretch\"}]," +
                    "\"type\":\"ColumnSet\"}\n";

            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Column column = TestUtil.createMockColumn();
            column.SetBackgroundImage(TestUtil.createMockBackgroundImage());
            column.SetBleed(true);
            column.SetFallbackType(FallbackType.Content);
            column.SetFallbackContent(TestUtil.createMockImage());
            column.SetHeight(HeightType.Stretch);
            column.SetId("Sample id");
            column.SetIsVisible(false);
            column.SetMinHeight(1);
            column.SetSelectAction(TestUtil.createSampleSubmitAction());
            column.SetSeparator(true);
            column.SetSpacing(Spacing.Medium);
            column.SetStyle(ContainerStyle.Attention);
            column.SetVerticalContentAlignment(VerticalContentAlignment.Center);
            column.SetPixelWidth(50);
            column.SetWidth("stretch");

            columnSet.GetColumns().add(column);
            Assert.assertEquals(columnWidth, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(columnWidth), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("stretch", parsedColumnSet.GetColumns().get(0).GetWidth());
            Assert.assertEquals(0, parsedColumnSet.GetColumns().get(0).GetPixelWidth());
        }

        {
            final String columnPixelWidth =
                "{\"columns\":[" +
                    "{\"backgroundImage\":\"http://\"," +
                    "\"bleed\":true," +
                    "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                    "\"height\":\"Stretch\"," +
                    "\"id\":\"Sample id\"," +
                    "\"isVisible\":false," +
                    "\"items\":[]," +
                    "\"minHeight\":\"1px\"," +
                    "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"separator\":true," +
                    "\"spacing\":\"medium\"," +
                    "\"style\":\"Attention\"," +
                    "\"type\":\"Column\"," +
                    "\"verticalContentAlignment\":\"Center\"," +
                    "\"width\":\"50px\"}]," +
                    "\"type\":\"ColumnSet\"}\n";

            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Column column = TestUtil.createMockColumn();
            column.SetBackgroundImage(TestUtil.createMockBackgroundImage());
            column.SetBleed(true);
            column.SetFallbackType(FallbackType.Content);
            column.SetFallbackContent(TestUtil.createMockImage());
            column.SetHeight(HeightType.Stretch);
            column.SetId("Sample id");
            column.SetIsVisible(false);
            column.SetMinHeight(1);
            column.SetSelectAction(TestUtil.createSampleSubmitAction());
            column.SetSeparator(true);
            column.SetSpacing(Spacing.Medium);
            column.SetStyle(ContainerStyle.Attention);
            column.SetVerticalContentAlignment(VerticalContentAlignment.Center);
            column.SetWidth("stretch");
            column.SetPixelWidth(50);
            columnSet.GetColumns().add(column);

            Assert.assertEquals(columnPixelWidth, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(columnPixelWidth), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("50px", parsedColumnSet.GetColumns().get(0).GetWidth());
            Assert.assertEquals(50, parsedColumnSet.GetColumns().get(0).GetPixelWidth());
        }
    }

    @Test
    public void PixelWidthTest() throws Exception
    {
        final String columnPixelWidth = "{\"columns\":[{\"items\":[],\"type\":\"Column\",\"width\":\"%dpx\"}],\"type\":\"ColumnSet\"}\n";
        final String columnPixelWidthAuto= "{\"columns\":[{\"items\":[],\"type\":\"Column\",\"width\":\"Auto\"}],\"type\":\"ColumnSet\"}\n";

        ArrayList<Pair<Integer, String>> tests = new ArrayList<>();
        // TODO: Deine what happens here with 0px, should we respect the value or not
        tests.add(new Pair<>(new Integer(0), String.format(columnPixelWidth, 0)));
        tests.add(new Pair<>(new Integer(25), String.format(columnPixelWidth, 25)));
        tests.add(new Pair<>(new Integer(100), String.format(columnPixelWidth, 100)));

        for (Pair<Integer, String> testTuple : tests)
        {
            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Column column = TestUtil.createMockColumn();
            column.SetPixelWidth(testTuple.first.intValue());
            columnSet.GetColumns().add(column);
            Assert.assertEquals(testTuple.second, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first.intValue(), parsedColumnSet.GetColumns().get(0).GetPixelWidth());
        }
    }

    @Test
    public void WidthTest() throws Exception
    {
        final String columnWidth = "{\"columns\":[{\"items\":[],\"type\":\"Column\",\"width\":\"%s\"}],\"type\":\"ColumnSet\"}\n";

        ArrayList<Pair<String, String>> tests = new ArrayList<>();
        tests.add(new Pair<>("", s_defaultColumnSet));
        tests.add(new Pair<>("auto", String.format(columnWidth, "auto")));
        tests.add(new Pair<>("stretch", String.format(columnWidth, "stretch")));
        tests.add(new Pair<>("0", String.format(columnWidth, "0")));
        tests.add(new Pair<>("50", String.format(columnWidth, "50")));

        for (Pair<String, String> testTuple : tests)
        {
            ColumnSet columnSet = TestUtil.createMockColumnSet();
            Column column = TestUtil.createMockColumn();
            column.SetWidth(testTuple.first);
            columnSet.GetColumns().add(column);
            Assert.assertEquals(testTuple.second, columnSet.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            ColumnSet parsedColumnSet = TestUtil.castToColumnSet(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedColumnSet.GetColumns().get(0).GetWidth());
        }
    }

    public static final String s_defaultColumnSet = "{\"columns\":[{\"items\":[],\"type\":\"Column\"}],\"type\":\"ColumnSet\"}\n";

}
