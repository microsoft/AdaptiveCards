// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseElement;
import io.adaptivecards.objectmodel.FallbackType;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.Spacing;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.IActionLayoutRenderer;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class ActionLayoutRenderer implements IActionLayoutRenderer {

    protected ActionLayoutRenderer()
    {
    }

    public static ActionLayoutRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ActionLayoutRenderer();
        }

        return s_instance;
    }

    public View renderActions(
                RenderedAdaptiveCard renderedCard,
                Context context,
                FragmentManager fragmentManager,
                ViewGroup viewGroup,
                BaseActionElementVector baseActionElementList,
                ICardActionHandler cardActionHandler,
                HostConfig hostConfig,
                RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        long size;
        if (baseActionElementList == null || (size = baseActionElementList.size()) <= 0)
        {
            return null;
        }

        LinearLayout actionButtonsLayout = new LinearLayout(context);
        actionButtonsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        int alignment = hostConfig.GetActions().getActionAlignment().swigValue();

        int actionButtonsAlignment = Gravity.START | Gravity.TOP; // default gravity
        if (alignment == ActionAlignment.Right.swigValue())
        {
            actionButtonsAlignment = Gravity.RIGHT;
        }
        else if (alignment == ActionAlignment.Center.swigValue())
        {
            actionButtonsAlignment = Gravity.CENTER_HORIZONTAL;
        }
        actionButtonsLayout.setGravity(actionButtonsAlignment);

        int actionButtonsLayoutOrientation = hostConfig.GetActions().getActionsOrientation().swigValue();
        if (actionButtonsLayoutOrientation == ActionsOrientation.Vertical.swigValue())
        {
            actionButtonsLayout.setOrientation(LinearLayout.VERTICAL);
        }
        else
        {
            actionButtonsLayout.setOrientation(LinearLayout.HORIZONTAL);
        }

        Spacing spacing = hostConfig.GetActions().getSpacing();
        /* Passing false for separator since we do not have any configuration for separator in actionsConfig */
        BaseCardElementRenderer.setSpacingAndSeparator(context, viewGroup, spacing, false, hostConfig, true /* Horizontal Line */);

        if (viewGroup != null)
        {
            if(actionButtonsLayoutOrientation == ActionsOrientation.Horizontal.swigValue())
            {
                HorizontalScrollView actionButtonsContainer = new HorizontalScrollView(context);
                // Make elements alignment works when not enough space to make them scroll
                LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT);
                layoutParams.gravity = actionButtonsAlignment;
                actionButtonsContainer.setLayoutParams(layoutParams);

                actionButtonsContainer.setHorizontalScrollBarEnabled(false);
                actionButtonsContainer.addView(actionButtonsLayout);
                viewGroup.addView(actionButtonsContainer);
            }
            else
            {
                viewGroup.addView(actionButtonsLayout);
            }
        }

        int i = 0;
        long maxActions = hostConfig.GetActions().getMaxActions();

        // Allow the actions to have the icon drawn at the top as long as all actions have an icon
        renderArgs.setAllowAboveTitleIconPlacement(true);
        for(; i < size && i < maxActions; ++i)
        {
            BaseActionElement actionElement = baseActionElementList.get(i);
            if(actionElement.GetIconUrl().isEmpty())
            {
                renderArgs.setAllowAboveTitleIconPlacement(false);
                break;
            }
        }

        if (i >= maxActions && size != maxActions)
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.MAX_ACTIONS_EXCEEDED, "A maximum of " + maxActions + " actions are allowed"));
        }

        FeatureRegistration featureRegistration = CardRendererRegistration.getInstance().getFeatureRegistration();
        for (i = 0; i < size && i < maxActions; i++)
        {
            BaseActionElement actionElement = baseActionElementList.get(i);

            IBaseActionElementRenderer actionRenderer = CardRendererRegistration.getInstance().getActionRenderer(actionElement.GetElementTypeString());

            try
            {
                if (actionRenderer == null)
                {
                    throw new AdaptiveFallbackException(actionElement);
                }

                if ((featureRegistration != null) && (!actionElement.MeetsRequirements(featureRegistration)))
                {
                    throw new AdaptiveFallbackException(actionElement, featureRegistration);
                }

                actionRenderer.render(renderedCard, context, fragmentManager, actionButtonsLayout, actionElement, cardActionHandler, hostConfig, renderArgs);
            }
            catch (AdaptiveFallbackException e)
            {
                boolean elementHasFallback = (actionElement.GetFallbackType() != FallbackType.None);

                if (elementHasFallback)
                {
                    if (actionElement.GetFallbackType() == FallbackType.Content)
                    {
                        BaseElement fallbackElement = actionElement.GetFallbackContent();

                        while (fallbackElement != null)
                        {
                            try
                            {
                                BaseActionElement fallbackActionElement = Util.castToBaseActionElement(fallbackElement);
                                IBaseActionElementRenderer fallbackActionRenderer = CardRendererRegistration.getInstance().getActionRenderer(fallbackActionElement.GetElementTypeString());

                                if (fallbackActionRenderer == null)
                                {
                                    throw new AdaptiveFallbackException(fallbackElement);
                                }

                                if ((featureRegistration != null) && (!fallbackElement.MeetsRequirements(featureRegistration)))
                                {
                                    throw new AdaptiveFallbackException(fallbackElement, featureRegistration);
                                }

                                fallbackActionRenderer.render(renderedCard, context, fragmentManager, actionButtonsLayout, fallbackActionElement, cardActionHandler, hostConfig, renderArgs);
                                break;
                            }
                            catch (AdaptiveFallbackException e2)
                            {
                                // As the fallback element didn't exist, go back to trying
                                if (fallbackElement.GetFallbackType() == FallbackType.Content)
                                {
                                    fallbackElement = fallbackElement.GetFallbackContent();
                                }
                                else
                                {
                                    // The element has no fallback, just clear the element so the cycle ends
                                    fallbackElement = null;
                                }
                            }
                        }
                    }
                }
                else if (renderArgs.getAncestorHasFallback())
                {
                    // There's an ancestor with fallback so we throw to trigger it
                    throw e;
                }
                else
                {
                    renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE, "Unsupported card element type: " + actionElement.GetElementTypeString()));
                    continue;
                }
            }
        }

        return actionButtonsLayout;
    }

    private static ActionLayoutRenderer s_instance = null;
}
