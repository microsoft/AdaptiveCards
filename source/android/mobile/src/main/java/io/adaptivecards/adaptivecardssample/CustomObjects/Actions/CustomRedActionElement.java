package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;

public class CustomRedActionElement extends BaseActionElement
{

    public CustomRedActionElement(ActionType type) {
        super(type);
    }

    public String getBackwardString()
    {
        return m_backwardsString;
    }

    public void setBackwardString(String s)
    {
        m_backwardsString = new String();
        for(int i = s.length() - 1; i >= 0; i--)
        {
            m_backwardsString += s.charAt(i);
        }
    }

    private String m_backwardsString;
    public static final String CustomActionId = "redAction";
}
