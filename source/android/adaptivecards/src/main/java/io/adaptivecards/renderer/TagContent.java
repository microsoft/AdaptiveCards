package io.adaptivecards.renderer;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.renderer.inputhandler.IInputHandler;

public class TagContent
{

    public TagContent(String id)
    {
        m_id = id;
    }

    public TagContent(BaseCardElement baseCardElement)
    {
        m_id = baseCardElement.GetId();
        m_baseElement = baseCardElement;
    }

    public TagContent(BaseCardElement baseCardElement, IInputHandler inputHandler)
    {
        m_id = baseCardElement.GetId();;
        m_baseElement = baseCardElement;
        m_inputHandler = inputHandler;
    }

    public String GetId()
    {
        return m_id;
    }

    public void SetId(String id)
    {
        m_id = id;
    }

    public BaseCardElement GetBaseElement()
    {
        return m_baseElement;
    }

    public void SetBaseElement(BaseCardElement baseCardElement)
    {
        m_baseElement = baseCardElement;
    }

    public IInputHandler GetInputHandler()
    {
        return m_inputHandler;
    }

    public void SetInputHandler(IInputHandler inputHandler)
    {
        m_inputHandler = inputHandler;
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
                // If there's no id there's no way to compare
                if(m_id != null && !m_id.isEmpty())
                {
                    return m_id.equals(tagContentCmp.GetId());
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

    private String m_id = null;
    private BaseCardElement m_baseElement = null;
    private IInputHandler m_inputHandler;
}
