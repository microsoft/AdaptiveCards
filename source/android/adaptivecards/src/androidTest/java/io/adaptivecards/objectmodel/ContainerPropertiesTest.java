package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import static org.junit.Assert.*;

public class ContainerPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String containerNoDefaultValuesJson =
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

        Assert.assertEquals(containerNoDefaultValuesJson, container.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest() throws Exception
    {
        final String containerNoDefaultValues =
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
                "\"type\":\"Container\"," +
                "\"verticalContentAlignment\":\"Center\"}\n";

        Container container = TestUtil.createMockContainer();

        container.SetBackgroundImage(TestUtil.createMockBackgroundImage());
        container.SetBleed(true);
        container.SetFallbackType(FallbackType.Content);
        container.SetFallbackContent(TestUtil.createMockImage());
        container.SetHeight(HeightType.Stretch);
        container.SetId("Sample id");
        container.SetIsVisible(false);
        container.SetMinHeight(1);
        container.SetSelectAction(TestUtil.createSampleSubmitAction());
        container.SetSeparator(true);
        container.SetSpacing(Spacing.Medium);
        container.SetStyle(ContainerStyle.Attention);
        container.SetVerticalContentAlignment(VerticalContentAlignment.Center);

        Assert.assertEquals(containerNoDefaultValues, container.Serialize());
    }

}
