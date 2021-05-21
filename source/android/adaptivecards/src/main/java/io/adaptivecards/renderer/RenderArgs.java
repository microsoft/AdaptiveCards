// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HorizontalAlignment;

/**
 * Used to inform child elements of their rendering context. Renderers should apply all supplied
 * arguments relevant to their element, unless overridden by a declared property on that element.
 *
 * Renderers with any children must use the copy constructor to pass arguments on. If any arguments
 * were overridden by a declared property, the new value(s) must be set on the copied instance
 * before passing arguments on.
 */
public class RenderArgs
{

    public RenderArgs(){}

    public RenderArgs(RenderArgs renderArgs)
    {
        setAncestorHasFallback(renderArgs.getAncestorHasFallback());
        setContainerStyle(renderArgs.getContainerStyle());
        setContainerCardId(renderArgs.getContainerCardId());
        setHeader(renderArgs.isHeader());
        setHorizontalAlignment(renderArgs.getHorizontalAlignment());
    }

    public boolean getAncestorHasFallback()
    {
        return m_ancestorHasFallback;
    }

    public void setAncestorHasFallback(boolean ancestorHasFallback)
    {
        m_ancestorHasFallback = ancestorHasFallback;
    }

    /**
     * @return background style used by parent
     */
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

    /**
     * @return true if text should used styles defined for table headers
     */
    public boolean isHeader()
    {
        return m_isHeader;
    }

    public void setHeader(boolean isHeader)
    {
        m_isHeader = isHeader;
    }

    /**
     * @return horizontal alignment
     */
    public HorizontalAlignment getHorizontalAlignment()
    {
        return m_horizontalAlignment;
    }

    public void setHorizontalAlignment(HorizontalAlignment horizontalAlignment)
    {
        m_horizontalAlignment = horizontalAlignment;
    }

    /**
     * @return true for root level action otherwise false.
     */
    public boolean isRootLevelActions() {
        return m_isRootLevelActions;
    }

    /**
     * Set true to indicate action elements are present as root level actions or false to indicate it is part of {@link io.adaptivecards.objectmodel.ActionSet} elements.
     *
     * @param m_isRootLevelActions true for root level action otherwise false.
     */
    public void setRootLevelActions(boolean m_isRootLevelActions) {
        this.m_isRootLevelActions = m_isRootLevelActions;
    }

    private boolean m_ancestorHasFallback;
    private ContainerStyle m_containerStyle = ContainerStyle.Default;
    private boolean m_isHeader;
    private HorizontalAlignment m_horizontalAlignment = HorizontalAlignment.Left;
    private boolean m_allowAboveTitleIconPlacement;
    private long m_containerCardId;
    private boolean m_isRootLevelActions;
}
