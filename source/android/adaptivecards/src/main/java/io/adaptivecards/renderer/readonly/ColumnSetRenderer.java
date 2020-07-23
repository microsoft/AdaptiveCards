// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import androidx.fragment.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HeightType;
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

        LinearLayout layout = new LinearLayout(context);

        // Add this two for allowing children to bleed
        layout.setClipChildren(false);
        layout.setClipToPadding(false);

        setMinHeight(columnSet.GetMinHeight(), layout, context);

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
                                                                                   layout,
                                                                                   cardActionHandler,
                                                                                   hostConfig,
                                                                                   columnRenderArgs,
                                                                                   featureRegistration);
        }

        if (columnSet.GetSelectAction() != null)
        {
            layout.setClickable(true);
            layout.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard, columnSet.GetSelectAction(), cardActionHandler));
        }

        TagContent tagContent = new TagContent(columnSet);

        if (columnSet.GetHeight() == HeightType.Stretch)
        {
            LinearLayout stretchLayout = new LinearLayout(context);
            stretchLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));
            stretchLayout.setOrientation(LinearLayout.VERTICAL);

            layout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));

            tagContent.SetStretchContainer(stretchLayout);

            stretchLayout.addView(layout);
            viewGroup.addView(stretchLayout);
        }
        else
        {
            layout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
            viewGroup.addView(layout);
        }

        layout.setTag(tagContent);

        ContainerRenderer.ApplyPadding(styleForThis, parentContainerStyle, layout, context, hostConfig);
        ContainerRenderer.ApplyBleed(columnSet, layout, context, hostConfig);

        return layout;
    }

    private static ColumnSetRenderer s_instance = null;
}
