// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.util.LayoutDirection;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.google.android.flexbox.AlignItems;
import com.google.android.flexbox.AlignSelf;
import com.google.android.flexbox.FlexDirection;
import com.google.android.flexbox.FlexWrap;
import com.google.android.flexbox.FlexboxLayout;

import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BackgroundImage;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.BackgroundImageLoaderAsync;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import java.util.Locale;

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

    private void setVerticalContentAlignment(VerticalContentAlignment verticalContentAlignment, ViewGroup linearLayout)
    {
        ViewGroup.LayoutParams layoutParams = linearLayout.getLayoutParams();

        int alignment = AlignItems.FLEX_START;
        int gravity = Gravity.TOP;

        switch (verticalContentAlignment)
        {
            case Center:
                alignment = AlignItems.CENTER;
                gravity = Gravity.CENTER_VERTICAL;
                break;
            case Bottom:
                alignment = AlignItems.FLEX_END;
                gravity = Gravity.BOTTOM;
                break;
            case Top:
            default:
                alignment = AlignItems.FLEX_START;
                gravity = Gravity.TOP;
                break;
        }

        if (linearLayout instanceof FlexboxLayout)
        {
            ((FlexboxLayout)linearLayout).setAlignItems(alignment);
        }
        else if (linearLayout instanceof LinearLayout)
        {
            ((LinearLayout)linearLayout).setGravity(gravity);
        }
    }

    private ViewGroup setColumnWidth(RenderedAdaptiveCard renderedCard, Context context, Column column, ViewGroup columnLayout)
    {

        String columnSize = column.GetWidth().toLowerCase(Locale.getDefault());
        long pixelWidth = column.GetPixelWidth();

        if (pixelWidth != 0)
        {
            columnLayout.setLayoutParams(new FlexboxLayout.LayoutParams(Util.dpToPixels(context, pixelWidth), FlexboxLayout.LayoutParams.MATCH_PARENT));
            return columnLayout;
        }
        else if (hasRatioWidth(column))
        {
            // Set ratio to column
            float columnWeight = Float.parseFloat(columnSize);
            columnLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT, columnWeight));
            return columnLayout;
        }
        else if (TextUtils.isEmpty(columnSize) || columnSize.equals(g_columnSizeStretch))
        {
            FlexboxLayout.LayoutParams layoutParams = new FlexboxLayout.LayoutParams(FlexboxLayout.LayoutParams.WRAP_CONTENT, FlexboxLayout.LayoutParams.MATCH_PARENT);
            layoutParams.setFlexGrow(1);
            layoutParams.setFlexShrink(1);

            columnLayout.setLayoutParams(layoutParams);

            return columnLayout;
        }
        else
        {
            // If the width is Auto or is not valid (not weight, pixel, empty or stretch)
            FlexboxLayout.LayoutParams layoutParams = new FlexboxLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.MATCH_PARENT);
            layoutParams.setFlexGrow(0);
            layoutParams.setFlexShrink(1);
            columnLayout.setLayoutParams(layoutParams);

            if (!columnSize.equals(g_columnSizeAuto))
            {
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INVALID_COLUMN_WIDTH_VALUE, "Column Width (" + column.GetWidth() + ") is not a valid weight ('auto', 'stretch', <integer>)."));
            }

            return columnLayout;
        }
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

        ViewGroup columnLayout = null;

        // Due to flexbox not being able to calculate ratios correctly, ratios will be considered a special case of sorts, if this doesn't work then F :(
        if (hasRatioWidth(column))
        {
            columnLayout = new LinearLayout(context);
            ((LinearLayout)columnLayout).setOrientation(LinearLayout.VERTICAL);
        }
        else
        {
            columnLayout = new FlexboxLayout(context);
            ((FlexboxLayout)columnLayout).setFlexDirection(FlexDirection.COLUMN);
        }
        columnLayout.setTag(new TagContent(column));

        setVisibility(baseCardElement.GetIsVisible(), columnLayout);
        ViewGroup itemsContainer = setColumnWidth(renderedCard, context, column, columnLayout);

        if (column.GetMinHeight() != 0)
        {
            if (itemsContainer instanceof FlexboxLayout)
            {
                LinearLayout newItemsContainer = new LinearLayout(context);
                newItemsContainer.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
                newItemsContainer.setOrientation(LinearLayout.VERTICAL);
                itemsContainer.addView(newItemsContainer);

                itemsContainer = newItemsContainer;
            }

            setMinHeight(column.GetMinHeight(), itemsContainer, context);
        }

        columnLayout.setClipChildren(false);
        columnLayout.setClipToPadding(false);

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
                                                              itemsContainer,
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

        if (column.GetSelectAction() != null)
        {
            columnLayout.setClickable(true);
            columnLayout.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard, column.GetSelectAction(), cardActionHandler));
        }

        viewGroup.addView(columnLayout);
        return columnLayout;
    }

    private boolean hasRatioWidth(Column column)
    {
        String columnSize = column.GetWidth().toLowerCase(Locale.getDefault());
        long pixelWidth = column.GetPixelWidth();

        if (pixelWidth != 0)
        {
            return false;
        }
        else
        {
            try
            {
                // Set ratio to column
                Float.parseFloat(columnSize);
                return true;
            }
            catch (NumberFormatException ex)
            {
                return false;
            }
        }
    }

    private static ColumnRenderer s_instance = null;
    private final String g_columnSizeAuto = "auto";
    private final String g_columnSizeStretch = "stretch";
}
