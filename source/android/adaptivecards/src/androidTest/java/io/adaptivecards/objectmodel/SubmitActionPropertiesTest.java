package io.adaptivecards.objectmodel;

import static org.junit.Assert.*;

public class SubmitActionPropertiesTest
{

    public static SubmitAction createMockSubmitAction()
    {
        SubmitAction submitAction = new SubmitAction();
        submitAction.SetDataJson("{\"data\":\"Some data\"}");
        return submitAction;
    }

}
