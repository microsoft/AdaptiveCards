// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.google.android.flexbox.FlexDirection;
import com.google.android.flexbox.FlexWrap;
import com.google.android.flexbox.FlexboxLayout;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HeightType;
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
import io.adaptivecards.renderer.layout.SelectableFlexboxLayout;
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

        SelectableFlexboxLayout columnSetLayout = new SelectableFlexboxLayout(context);
        columnSetLayout.setFlexWrap(FlexWrap.NOWRAP);
        columnSetLayout.setFlexDirection(FlexDirection.ROW);

        // TODO: Consistent column-width across platforms, which may need normalized weights:
        // normalizeWeights(columnVector);

        ContainerStyle parentContainerStyle = renderArgs.getContainerStyle();
        ContainerStyle styleForThis = ContainerRenderer.GetLocalContainerStyle(columnSet, parentContainerStyle);

        for (int i = 0; i < columnVectorSize; i++)
        {
            Column column = columnVector.get(i);

            if(columnSet.GetMinHeight() > column.GetMinHeight())
            {
                column.SetMinHeight(columnSet.GetMinHeight());
            }

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

        ContainerRenderer.setSelectAction(renderedCard, columnSet.GetSelectAction(), columnSetLayout, cardActionHandler, renderArgs);

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
            columnSetLayout.setLayoutParams(new FlexboxLayout.LayoutParams(FlexboxLayout.LayoutParams.MATCH_PARENT, FlexboxLayout.LayoutParams.WRAP_CONTENT));
            viewGroup.addView(columnSetLayout);
        }

        columnSetLayout.setTag(tagContent);

        ContainerRenderer.ApplyPadding(styleForThis, parentContainerStyle, columnSetLayout, context, hostConfig);
        ContainerRenderer.ApplyBleed(columnSet, columnSetLayout, context, hostConfig);

        return columnSetLayout;
    }

    /**
     * Normalize width of columns such that all relative weights, if any, sum to 1.
     * @param columns Columns to normalize
     */
    private static void normalizeWeights(ColumnVector columns) {
        float totalWeight = 0;
        for(Column c : columns)
        {
            Float relativeWidth = ColumnRenderer.getRelativeWidth(c);
            if(relativeWidth != null)
            {
                totalWeight += relativeWidth;
            }
        }
        for(Column c : columns)
        {
            Float relativeWidth = ColumnRenderer.getRelativeWidth(c);
            if(relativeWidth != null && totalWeight > 0)
            {
                c.SetWidth(String.valueOf(relativeWidth / totalWeight));
            }
        }
    }

    private static ColumnSetRenderer s_instance = null;
}
