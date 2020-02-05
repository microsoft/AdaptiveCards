package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

/**
 * Class for testing the collection typed elements, as BaseCardElement objects can't be parsed to
 * CollectionTypeElement then we use Container objects for testing, Column and ColumnSet will include
 * a test for the inherited elements too. This class tests the properties
 * shared by Container, Column and ColumnSet:
 * BackgroundImage
 * Bleed
 * MinHeight
 * SelectAction
 * Style
 * VerticalContentAlignment
 */
public class CollectionTypeElementPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest() throws Exception
    {
        final String containerNoDefaultValues =
            "{\"backgroundImage\":\"http://\"," +
            "\"bleed\":true," +
            "\"items\":[]," +
            "\"minHeight\":\"1px\"," +
            "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
            "\"style\":\"Attention\"," +
            "\"type\":\"Container\"," +
            "\"verticalContentAlignment\":\"Center\"}\n";

        Container container = TestUtil.createMockContainer();

        container.SetBackgroundImage(TestUtil.createMockBackgroundImage());
        container.SetBleed(true);
        container.SetMinHeight(1);
        container.SetSelectAction(TestUtil.createSampleSubmitAction());
        container.SetStyle(ContainerStyle.Attention);
        container.SetVerticalContentAlignment(VerticalContentAlignment.Center);

        Assert.assertEquals(containerNoDefaultValues, container.Serialize());
    }

    @Test
    public void BackgroundImageTest() throws Exception
    {
        /**
         * Tests container with no background image (default)
         */
        {
            Container container = TestUtil.createMockContainer();
            container.SetBackgroundImage(null);
            Assert.assertEquals(s_defaultContainerJson, container.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(s_defaultContainerJson), "1.0");
            Container parsedContainer = TestUtil.castToContainer(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(null, parsedContainer.GetBackgroundImage());
        }

        {
            final String containerBackgroundImage = "{\"backgroundImage\":\"http://\",\"items\":[],\"type\":\"Container\"}\n";
            Container container = TestUtil.createMockContainer();
            container.SetBackgroundImage(TestUtil.createMockBackgroundImage());
            Assert.assertEquals(containerBackgroundImage, container.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(containerBackgroundImage), "1.0");
            Container parsedContainer = TestUtil.castToContainer(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("http://", parsedContainer.GetBackgroundImage().GetUrl());
        }
    }

    @Test
    public void BleedTest() throws Exception
    {
        /**
         * Tests container with no background image (default)
         */
        final String containerBleed = "{\"bleed\":true,\"items\":[],\"type\":\"Container\"}\n";

        ArrayList<Pair<Boolean, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(false, s_defaultContainerJson));
        tests.add(new Pair<>(true, containerBleed));

        for (Pair<Boolean, String> testTuple : tests)
        {
            Container container = TestUtil.createMockContainer();
            container.SetBleed(testTuple.first);
            Assert.assertEquals(testTuple.second, container.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            Container parsedContainer = TestUtil.castToContainer(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals((boolean)testTuple.first, parsedContainer.GetBleed());
        }
    }

    @Test
    public void MinHeightTest() throws Exception
    {
        /**
         * Tests container with no background image (default)
         */
        final String containerMinHeight = "{\"items\":[],\"minHeight\":\"%dpx\",\"type\":\"Container\"}\n";

        ArrayList<Pair<Integer, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(new Integer(0), s_defaultContainerJson));
        tests.add(new Pair<>(new Integer(25), String.format(containerMinHeight, 25)));
        tests.add(new Pair<>(new Integer(100), String.format(containerMinHeight, 100)));

        for (Pair<Integer, String> testTuple : tests)
        {
            Container container = TestUtil.createMockContainer();
            container.SetMinHeight(testTuple.first.intValue());
            Assert.assertEquals(testTuple.second, container.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            Container parsedContainer = TestUtil.castToContainer(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first.intValue(), parsedContainer.GetMinHeight());
        }
    }

    @Test
    public void SelectActionTest() throws Exception
    {
        /**
         * Tests container with no background image (default)
         */
        final String containerSelectAction = "{\"items\":[],\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"},\"type\":\"Container\"}\n";

        {
            Container container = TestUtil.createMockContainer();
            container.SetSelectAction(null);
            Assert.assertEquals(s_defaultContainerJson, container.Serialize());
        }

        Container container = TestUtil.createMockContainer();
        container.SetSelectAction(TestUtil.createSampleSubmitAction());
        Assert.assertEquals(containerSelectAction, container.Serialize());

        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(containerSelectAction), "1.0");
        Container parsedContainer = TestUtil.castToContainer(result.GetAdaptiveCard().GetBody().get(0));
        Assert.assertEquals(TestUtil.createSampleSubmitAction().Serialize(), parsedContainer.GetSelectAction().Serialize());
    }

    @Test
    public void StyleTest() throws Exception
    {
        /**
         * Tests container with no background image (default)
         */
        final String containerStyle = "{\"items\":[],\"style\":\"%s\",\"type\":\"Container\"}\n";

        ArrayList<Pair<ContainerStyle, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(ContainerStyle.None, s_defaultContainerJson));
        tests.add(new Pair<>(ContainerStyle.Default, String.format(containerStyle, "Default")));
        tests.add(new Pair<>(ContainerStyle.Emphasis, String.format(containerStyle, "Emphasis")));
        tests.add(new Pair<>(ContainerStyle.Good, String.format(containerStyle, "Good")));
        tests.add(new Pair<>(ContainerStyle.Attention, String.format(containerStyle, "Attention")));
        tests.add(new Pair<>(ContainerStyle.Warning, String.format(containerStyle, "Warning")));
        tests.add(new Pair<>(ContainerStyle.Accent, String.format(containerStyle, "Accent")));

        for (Pair<ContainerStyle, String> testTuple : tests)
        {
            Container container = TestUtil.createMockContainer();
            container.SetStyle(testTuple.first);
            Assert.assertEquals(testTuple.second, container.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            Container parsedContainer = TestUtil.castToContainer(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedContainer.GetStyle());
        }
    }

    @Test
    public void VerticalContentAlignmentTest() throws Exception
    {
        /**
         * Tests container with no background image (default)
         */
        final String containerVerticalContentAlignment = "{\"items\":[],\"type\":\"Container\",\"verticalContentAlignment\":\"%s\"}\n";

        ArrayList<Pair<VerticalContentAlignment, String>> tests = new ArrayList<>();
        tests.add(new Pair<>(VerticalContentAlignment.Top, s_defaultContainerJson));
        tests.add(new Pair<>(VerticalContentAlignment.Center, String.format(containerVerticalContentAlignment, "Center")));
        tests.add(new Pair<>(VerticalContentAlignment.Bottom, String.format(containerVerticalContentAlignment, "Bottom")));

        for (Pair<VerticalContentAlignment, String> testTuple : tests)
        {
            Container container = TestUtil.createMockContainer();
            container.SetVerticalContentAlignment(testTuple.first);
            Assert.assertEquals(testTuple.second, container.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(testTuple.second), "1.0");
            Container parsedContainer = TestUtil.castToContainer(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(testTuple.first, parsedContainer.GetVerticalContentAlignment());
        }
    }

    private static final String s_defaultContainerJson = "{\"items\":[],\"type\":\"Container\"}\n";

}
