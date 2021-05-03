// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.action;

import android.content.Context;
import android.graphics.Color;
import androidx.fragment.app.FragmentManager;
import android.util.Pair;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ActionSet;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.ActionLayoutRenderer;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.IActionLayoutRenderer;
import io.adaptivecards.renderer.OverflowActionLayoutRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class ActionSetRenderer extends BaseCardElementRenderer
{
    public static ActionSetRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ActionSetRenderer();
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
            RenderArgs renderArgs) throws ClassCastException
    {
        ActionSet actionSet = Util.castTo(baseCardElement, ActionSet.class);

        // This layout contains the space for the actions (top, first element) and the hidden cards (bottom, second element)
        LinearLayout rootLayout = new LinearLayout(context);
        // Add tag for rendering process
        rootLayout.setTag(new TagContent(actionSet));
        rootLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        rootLayout.setOrientation(LinearLayout.VERTICAL);

        // This layout will contain the rendered actions
        LinearLayout actionsLayout = new LinearLayout(context);
        actionsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        ContainerStyle style = renderArgs.getContainerStyle();
        String color = hostConfig.GetBackgroundColor(style);
        actionsLayout.setBackgroundColor(Color.parseColor(color));

        rootLayout.addView(actionsLayout);

        // This layout will contain the cards hidden until a showcard action is pressed
        LinearLayout showCardsLayout = new LinearLayout(context);
        showCardsLayout.setBackgroundColor(Color.parseColor(color));
        showCardsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        rootLayout.addView(showCardsLayout);

        BaseActionElementVector baseActionElementList = actionSet.GetActions();

        //Split Action Elements and render.
        Pair<BaseActionElementVector,BaseActionElementVector> actionElementVectorPair = Util.splitActionsByMode(baseActionElementList, hostConfig, renderedCard);
        BaseActionElementVector primaryElementVector = actionElementVectorPair.first;
        BaseActionElementVector secondaryElementVector = actionElementVectorPair.second;

        try
        {
            View actionButtonsLayout = ActionLayoutRenderer.getInstance().renderActions(renderedCard, context, fragmentManager, actionsLayout, primaryElementVector, cardActionHandler, hostConfig, renderArgs);
            if (!secondaryElementVector.isEmpty())
            {
                IActionLayoutRenderer secondaryActionLayoutRenderer = CardRendererRegistration.getInstance().getOverflowActionLayoutRenderer();
                //if the actionButtonsLayout is not a viewGroup, then use actionsLayout as a root.
                ViewGroup rootActionLayout = actionButtonsLayout instanceof ViewGroup ? (ViewGroup) actionButtonsLayout : actionsLayout;
                secondaryActionLayoutRenderer.renderActions(renderedCard, context, fragmentManager, rootActionLayout, secondaryElementVector, cardActionHandler, hostConfig, renderArgs);
            }
        }
        catch (Exception e) {}

        viewGroup.addView(rootLayout);
        return rootLayout;
    }

    private static ActionSetRenderer s_instance = null;
}
