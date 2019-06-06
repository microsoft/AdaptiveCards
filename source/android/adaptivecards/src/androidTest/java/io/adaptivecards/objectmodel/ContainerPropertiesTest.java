package io.adaptivecards.objectmodel;

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
        final String ImageNoDefaultValuesExplicitSize =
            "{\"altText\":\"altText\"," +
                "\"backgroundColor\":\"#FF128192\"," +
                "\"height\":\"50px\"," +
                "\"horizontalAlignment\":\"center\"," +
                "\"selectAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                "\"style\":\"person\"," +
                "\"type\":\"Image\"," +
                "\"url\":\"http://\"," +
                "\"width\":\"50px\"}\n";

        Container container = TestUtil.createMockContainer();
    }

}
