package io.adaptivecards.renderer;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.renderer.inputhandler.IInputHandler;

public class TagContent
{
    // This constructor is necessary as using visualTree.findViewWithTag(param) for searching make
    // the match comparison as param.equals(visualTreeNode) which means that the Equals method for
    // param type is called, so in this case we must convert the string into a tag object for the lookup
    public TagContent(String id)
    {
        m_id = id;
    }

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
        // baseElement should only be empty when the object was built for lookup, so m_id is not
        // always filled, it will only be filled for lookup and so we can save some memory
        if(m_baseElement != null)
        {
            return m_baseElement.GetId();
        }
        else
        {
            return m_id;
        }
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

    private String m_id = null;
    private BaseCardElement m_baseElement = null;
    private IInputHandler m_inputHandler = null;
}
