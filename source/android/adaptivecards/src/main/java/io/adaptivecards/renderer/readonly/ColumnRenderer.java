// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.google.android.flexbox.AlignItems;
import com.google.android.flexbox.FlexDirection;
import com.google.android.flexbox.FlexboxLayout;
import com.google.android.flexbox.JustifyContent;

import java.util.Locale;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.layout.SelectableFlexboxLayout;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class ColumnRenderer extends BaseCardElementRenderer
{
    protected ColumnRenderer()
    {
    }

    public static ColumnRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ColumnRenderer();
        }

        return s_instance;
    }

    private void setVerticalContentAlignment(VerticalContentAlignment verticalContentAlignment, LinearLayout columnLayout)
    {
        int gravity = Gravity.TOP;
        if(verticalContentAlignment == VerticalContentAlignment.Center)
        {
            gravity = Gravity.CENTER;
        }
        else if(verticalContentAlignment == VerticalContentAlignment.Bottom)
        {
            gravity = Gravity.BOTTOM;
        }
        columnLayout.setGravity(gravity);
    }

    /**
     * If column width is given as a relative weight, get the weight
     * @param column The Column element
     * @return weight, or null if width is not relative
     */
    static Float getRelativeWidth(Column column)
    {
        try
        {
            String columnSize = column.GetWidth().toLowerCase(Locale.getDefault());
            return Float.parseFloat(columnSize);
        }
        catch (NumberFormatException ex)
        {
            return null;
        }
    }

    private ViewGroup setColumnWidth(RenderedAdaptiveCard renderedCard, Context context, Column column, ViewGroup columnLayout)
    {

        String columnSize = column.GetWidth().toLowerCase(Locale.getDefault());
        long pixelWidth = column.GetPixelWidth();
        Float relativeWidth = ColumnRenderer.getRelativeWidth(column);

        FlexboxLayout.LayoutParams layoutParams = new FlexboxLayout.LayoutParams(0, FlexboxLayout.LayoutParams.MATCH_PARENT);

        if (pixelWidth != 0)
        {
            layoutParams.setFlexGrow(0);
            layoutParams.setFlexShrink(0);
            layoutParams.setWidth(Util.dpToPixels(context, pixelWidth));
        }
        else if (relativeWidth != null)
        {
            // Set ratio to column
            layoutParams.setFlexGrow(1);
            layoutParams.setFlexShrink(1);
            layoutParams.setFlexBasisPercent(relativeWidth);
        }
        else if (TextUtils.isEmpty(columnSize) || columnSize.equals(g_columnSizeStretch))
        {
            layoutParams.setFlexGrow(1);
            layoutParams.setFlexShrink(1);
        }
        else
        {
            // If the width is Auto or is not valid (not weight, pixel, empty or stretch)
            layoutParams.setFlexGrow(0);
            layoutParams.setFlexShrink(1);
            layoutParams.setWidth(FlexboxLayout.LayoutParams.WRAP_CONTENT);

            if (!columnSize.equals(g_columnSizeAuto))
            {
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INVALID_COLUMN_WIDTH_VALUE, "Column Width (" + column.GetWidth() + ") is not a valid weight ('auto', 'stretch', <integer>)."));
            }
        }
        columnLayout.setLayoutParams(layoutParams);
        return columnLayout;
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        Column column = Util.castTo(baseCardElement, Column.class);

        // TODO: Check compatibility with model on top
        View separator = setSpacingAndSeparator(context, viewGroup, column.GetSpacing(), column.GetSeparator(), hostConfig, false);

        LinearLayout columnLayout = new LinearLayout(context);
        columnLayout.setOrientation(LinearLayout.VERTICAL);
        columnLayout.setTag(new TagContent(column));

        setVisibility(baseCardElement.GetIsVisible(), columnLayout);

        setColumnWidth(renderedCard, context, column, columnLayout);
        setMinHeight(column.GetMinHeight(), columnLayout, context);

        ContainerStyle containerStyle = renderArgs.getContainerStyle();
        ContainerStyle styleForThis = ContainerRenderer.GetLocalContainerStyle(column, containerStyle);

        RenderArgs columnRenderArgs = new RenderArgs(renderArgs);
        columnRenderArgs.setContainerStyle(styleForThis);
        if (!column.GetItems().isEmpty())
        {
            try
            {
                CardRendererRegistration.getInstance().renderElements(renderedCard,
                                                              context,
                                                              fragmentManager,
                                                              columnLayout,
                                                              column.GetItems(),
                                                              cardActionHandler,
                                                              hostConfig,
                                                              columnRenderArgs);
            }
            catch (AdaptiveFallbackException e)
            {
                // If the column couldn't be rendered, the separator is removed
                viewGroup.removeView(separator);
                throw e;
            }
        }

        ContainerRenderer.setBackgroundImage(renderedCard, context, column.GetBackgroundImage(), hostConfig, columnLayout);

        setVerticalContentAlignment(column.GetVerticalContentAlignment(), columnLayout);

        ContainerRenderer.ApplyPadding(styleForThis, renderArgs.getContainerStyle(), columnLayout, context, hostConfig);
        ContainerRenderer.ApplyBleed(column, columnLayout, context, hostConfig);

        ContainerRenderer.setSelectAction(renderedCard, column.GetSelectAction(), columnLayout, cardActionHandler, renderArgs);

        viewGroup.addView(columnLayout);
        return columnLayout;
    }

    private static ColumnRenderer s_instance = null;
    private final String g_columnSizeAuto = "auto";
    private final String g_columnSizeStretch = "stretch";
}
