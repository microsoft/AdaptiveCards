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
        setColumnHeader(renderArgs.isColumnHeader());
        setHorizontalAlignment(renderArgs.getHorizontalAlignment());
        setAncestorHasSelectAction(renderArgs.getAncestorHasSelectAction());
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
    public boolean isColumnHeader()
    {
        return m_isColumnHeader;
    }

    public void setColumnHeader(boolean isHeader)
    {
        m_isColumnHeader = isHeader;
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
    public void setRootLevelActions(boolean m_isRootLevelActions)
    {
        this.m_isRootLevelActions = m_isRootLevelActions;
    }

    /**
     * @return true if any ancestor has a select action.
     */
    public boolean getAncestorHasSelectAction() {
        return m_ancestorHasSelectAction;
    }

    /**
     * Set true to indicate an {@link io.adaptivecards.objectmodel.Container}, {@link io.adaptivecards.objectmodel.Column} or {@link io.adaptivecards.objectmodel.ColumnSet}
     * elements have a select action.
     *
     * @param ancestorHasSelectAction true for root level action otherwise false.
     */
    public void setAncestorHasSelectAction(boolean ancestorHasSelectAction)
    {
        m_ancestorHasSelectAction = ancestorHasSelectAction;
    }

    private boolean m_ancestorHasFallback;
    private ContainerStyle m_containerStyle = ContainerStyle.Default;
    private boolean m_isColumnHeader;
    private HorizontalAlignment m_horizontalAlignment = HorizontalAlignment.Left;
    private boolean m_allowAboveTitleIconPlacement;
    private long m_containerCardId;
    private boolean m_isRootLevelActions;
    private boolean m_ancestorHasSelectAction = false;
}
