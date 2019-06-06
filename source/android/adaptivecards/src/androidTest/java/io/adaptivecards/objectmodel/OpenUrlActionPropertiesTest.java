package io.adaptivecards.objectmodel;

import static org.junit.Assert.*;

public class OpenUrlActionPropertiesTest
{

    public static OpenUrlAction createMockOpenUrlAction()
    {
        OpenUrlAction openUrlAction = new OpenUrlAction();
        openUrlAction.SetUrl("http://");
        return openUrlAction;
    }

}
