// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.view.View;
import android.view.ViewGroup;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.renderer.inputhandler.IInputHandler;

public class TagContent
{
    /**
     * Constructor to signalize explicitly if the element is an separator
     * @param isSeparator
     */
    public TagContent(boolean isSeparator)
    {
        m_isSeparator = isSeparator;
    }

    // This constructor is necessary as using visualTree.findViewWithTag(param) for searching make
    // the match comparison as param.equals(visualTreeNode) which means that the Equals method for
    // param type is called, so in this case we must convert the string into a tag object for the lookup
    public TagContent(String id)
    {
        m_id = id;
    }

    public TagContent(BaseCardElement baseCardElement, View separatorView, ViewGroup viewContainer)
    {
        this(false);
        m_baseElement = baseCardElement;
        m_separatorView = separatorView;
        m_viewContainer = viewContainer;
    }

    public TagContent(BaseCardElement baseCardElement, IInputHandler inputHandler, View separatorView, ViewGroup viewContainer)
    {
        this(baseCardElement, separatorView, viewContainer);
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

    public boolean IsSeparator()
    {
        return m_isSeparator;
    }

    public View GetSeparator()
    {
        return m_separatorView;
    }

    public ViewGroup GetViewContainer()
    {
        return m_viewContainer;
    }

    public View GetStretchContainer()
    {
        return m_stretchContainer;
    }

    public void SetStretchContainer(View stretchContainer)
    {
        m_stretchContainer = stretchContainer;
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

    private boolean m_isSeparator = false;
    private String m_id = null;
    private BaseCardElement m_baseElement = null;
    private IInputHandler m_inputHandler = null;
    private ViewGroup m_viewContainer = null;
    private View m_separatorView = null;
    private View m_stretchContainer = null;
}
