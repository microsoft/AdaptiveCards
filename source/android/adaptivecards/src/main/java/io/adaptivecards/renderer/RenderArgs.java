// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.InternalId;

public class RenderArgs
{

    public RenderArgs(){}

    public RenderArgs(RenderArgs renderArgs)
    {
        setAncestorHasFallback(renderArgs.getAncestorHasFallback());
        setContainerStyle(renderArgs.getContainerStyle());
        setContainerCardId(renderArgs.getContainerCardId());
    }

    public boolean getAncestorHasFallback()
    {
        return m_ancestorHasFallback;
    }

    public void setAncestorHasFallback(boolean ancestorHasFallback)
    {
        m_ancestorHasFallback = ancestorHasFallback;
    }

    public ContainerStyle getContainerStyle()
    {
        return m_containerStyle;
    }

    public void setContainerStyle(ContainerStyle containerStyle)
    {
        m_containerStyle = containerStyle;
    }

    public boolean getAllowAboveTitleIconPlacement()
    {
        return m_allowAboveTitleIconPlacement;
    }

    public void setAllowAboveTitleIconPlacement(boolean allowAboveTitleIconPlacement)
    {
        m_allowAboveTitleIconPlacement = allowAboveTitleIconPlacement;
    }

    public void setContainerCardId(long id)
    {
        m_containerCardId = id;
    }

    public long getContainerCardId()
    {
        return m_containerCardId;
    }

    private boolean m_ancestorHasFallback;
    private ContainerStyle m_containerStyle;
    private boolean m_allowAboveTitleIconPlacement;
    private long m_containerCardId;
}
