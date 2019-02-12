package io.adaptivecards.renderer;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.renderer.inputhandler.IInputHandler;

public class TagContent
{
    public TagContent(BaseCardElement baseCardElement)
    {
        m_baseElement = baseCardElement;
    }

    public TagContent(BaseCardElement baseCardElement, IInputHandler inputHandler)
    {
        m_baseElement = baseCardElement;
        m_inputHandler = inputHandler;
    }

    public String GetId()
    {
        return m_baseElement.GetId();
    }

    public BaseCardElement GetBaseElement()
    {
        return m_baseElement;
    }

    public IInputHandler GetInputHandler()
    {
        return m_inputHandler;
    }

    @Override
    public boolean equals(Object o)
    {
        // As of this version, we only care if the ids match and to provide a way to retrieve the content we were storing in the tags previously
        if(o != null)
        {
            if(o instanceof TagContent)
            {
                TagContent tagContentCmp = (TagContent)o;

                String id = GetId();
                // If there's no id there's no way to compare
                if(id != null && !id.isEmpty())
                {
                    return id.equals(tagContentCmp.GetId());
                }

                return false;
            }
            else
            {
                return false;
            }
        }

        return false;
    }

    private BaseCardElement m_baseElement = null;
    private IInputHandler m_inputHandler = null;
}
