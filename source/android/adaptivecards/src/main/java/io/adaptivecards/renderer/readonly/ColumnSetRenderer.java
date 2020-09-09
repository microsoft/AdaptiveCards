// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.util.Pair;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.google.android.flexbox.AlignContent;
import com.google.android.flexbox.AlignItems;
import com.google.android.flexbox.FlexDirection;
import com.google.android.flexbox.FlexWrap;
import com.google.android.flexbox.FlexboxLayout;
import com.google.android.flexbox.JustifyContent;

import java.util.ArrayList;
import java.util.Locale;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.ColumnSet;
import io.adaptivecards.objectmodel.ColumnVector;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;
import io.adaptivecards.renderer.IBaseCardElementRenderer;


public class ColumnSetRenderer extends BaseCardElementRenderer
{
    protected ColumnSetRenderer()
    {
    }

    public static ColumnSetRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ColumnSetRenderer();
        }

        return s_instance;
    }

    void recalculateRatioWidths(FlexboxLayout columnSetLayout)
    {
        int renderedColumnCount = columnSetLayout.getChildCount();
        float ratioTotal = 0.0f;
        // Instead of passing though all elements twice, just save what columns need to be recalculated
        // The first value refers to the rendered view index and the second value refers to the ratio
        ArrayList<Pair<Integer, Float>> columnsToRecalculate = new ArrayList<>();

        for (int i = 0; i < renderedColumnCount; ++i)
        {
            View renderedColumn = columnSetLayout.getChildAt(i);

            Object tag = renderedColumn.getTag();
            if (tag != null && tag instanceof TagContent)
            {
                TagContent columnTag = (TagContent) renderedColumn.getTag();
                if (!columnTag.IsSeparator())
                {
                    Column column = Util.castTo(columnTag.GetBaseElement(), Column.class);

                    String columnSize = column.GetWidth().toLowerCase(Locale.getDefault());
                    try
                    {
                        float columnRatio = Float.parseFloat(columnSize);
                        ratioTotal += columnRatio;
                        columnsToRecalculate.add(new Pair<>(i, columnRatio));
                    }
                    // This is just for retrieving the rendered ratios, we don't mind anything else
                    catch (Exception e) { }
                }
            }
        }

        for (Pair<Integer, Float> columnToRecalculate : columnsToRecalculate)
        {
            View renderedColumn = columnSetLayout.getChildAt(columnToRecalculate.first);

            ViewGroup.LayoutParams layoutParams = renderedColumn.getLayoutParams();

            if (layoutParams != null && layoutParams instanceof FlexboxLayout.LayoutParams)
            {
                FlexboxLayout.LayoutParams flexBoxLayoutParams = (FlexboxLayout.LayoutParams)layoutParams;
                // flexBoxLayoutParams.setFlexGrow(0);
                // flexBoxLayoutParams.setFlexShrink(2);
                // flexBoxLayoutParams.setFlexBasisPercent((columnToRecalculate.second * 100) / ratioTotal);
            }
        }


        columnSetLayout.requestLayout();
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
        ColumnSet columnSet = Util.castTo(baseCardElement, ColumnSet.class);

        IBaseCardElementRenderer columnRenderer = CardRendererRegistration.getInstance().getRenderer(CardElementType.Column.toString());
        if (columnRenderer == null)
        {
            throw new UnknownError(CardElementType.Column.toString() + " is not a registered renderer.");
        }

        ColumnVector columnVector = columnSet.GetColumns();
        long columnVectorSize = columnVector.size();

        // FlexboxLayout columnSetLayout = new FlexboxLayout(context);


        FlexboxLayout columnSetLayout = new FlexboxLayout(context);

        // Add this two for allowing children to bleed
        columnSetLayout.setClipChildren(false);
        columnSetLayout.setClipToPadding(false);

        columnSetLayout.setFlexWrap(FlexWrap.NOWRAP);
        columnSetLayout.setFlexDirection(FlexDirection.ROW);

        setMinHeight(columnSet.GetMinHeight(), columnSetLayout, context);

        ContainerStyle parentContainerStyle = renderArgs.getContainerStyle();
        ContainerStyle styleForThis = ContainerRenderer.GetLocalContainerStyle(columnSet, parentContainerStyle);

        for (int i = 0; i < columnVectorSize; i++)
        {
            Column column = columnVector.get(i);

            RenderArgs columnRenderArgs = new RenderArgs(renderArgs);
            columnRenderArgs.setContainerStyle(styleForThis);

            FeatureRegistration featureRegistration = CardRendererRegistration.getInstance().getFeatureRegistration();

            CardRendererRegistration.getInstance().renderElementAndPerformFallback(renderedCard,
                                                                                   context,
                                                                                   fragmentManager,
                                                                                   column,
                                                                                   columnSetLayout,
                                                                                   cardActionHandler,
                                                                                   hostConfig,
                                                                                   columnRenderArgs,
                                                                                   featureRegistration);
        }

        // recalculateRatioWidths(columnSetLayout);

        if (columnSet.GetSelectAction() != null)
        {
            columnSetLayout.setClickable(true);
            columnSetLayout.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard, columnSet.GetSelectAction(), cardActionHandler));
        }

        TagContent tagContent = new TagContent(columnSet);

        if (columnSet.GetHeight() == HeightType.Stretch)
        {
            LinearLayout stretchLayout = new LinearLayout(context);
            stretchLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));
            stretchLayout.setOrientation(LinearLayout.VERTICAL);

            columnSetLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));

            tagContent.SetStretchContainer(stretchLayout);

            stretchLayout.addView(columnSetLayout);
            viewGroup.addView(stretchLayout);
        }
        else
        {
            columnSetLayout.setLayoutParams(new FlexboxLayout.LayoutParams(FlexboxLayout.LayoutParams.MATCH_PARENT, FlexboxLayout.LayoutParams.MATCH_PARENT));
            viewGroup.addView(columnSetLayout);
        }

        columnSetLayout.setTag(tagContent);

        ContainerRenderer.ApplyPadding(styleForThis, parentContainerStyle, columnSetLayout, context, hostConfig);
        ContainerRenderer.ApplyBleed(columnSet, columnSetLayout, context, hostConfig);

        return columnSetLayout;
    }

    private static ColumnSetRenderer s_instance = null;
}
