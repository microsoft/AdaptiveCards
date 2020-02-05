package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;

public class CustomGreenActionElement extends BaseActionElement
{

    public CustomGreenActionElement(ActionType type) {
        super(type);
    }

    public String getMessage()
    {
        return m_message;
    }

    private final String m_message = "Smell you later!";
    public static final String CustomActionId = "greenAction";
}
