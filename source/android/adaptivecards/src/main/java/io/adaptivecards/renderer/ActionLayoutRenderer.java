// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import java.util.List;

import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseElement;
import io.adaptivecards.objectmodel.FallbackType;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Mode;
import io.adaptivecards.objectmodel.Spacing;
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
        if (baseActionElementList == null || baseActionElementList.size() <= 0)
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

        long maxActions = hostConfig.GetActions().getMaxActions();

        // Allow the actions to have the icon drawn at the top as long as all actions have an icon
        renderArgs.setAllowAboveTitleIconPlacement(true);

        //Splits "Primary" and "Secondary" actions.
        BaseActionElementVector primaryActionElementVector = new BaseActionElementVector();
        BaseActionElementVector secondaryActionElementVector = new BaseActionElementVector();

        for (BaseActionElement actionElement : baseActionElementList)
        {
            if (actionElement.GetMode() == Mode.Secondary)
            {
                secondaryActionElementVector.add(actionElement);
            }
            else
            {
                primaryActionElementVector.add(actionElement);
            }

            if (actionElement.GetIconUrl().isEmpty())
            {
                renderArgs.setAllowAboveTitleIconPlacement(false);
            }
        }

        int primaryElementsSize = primaryActionElementVector.size();
        if (primaryElementsSize > maxActions)
        {
            List<BaseActionElement> excessElements = primaryActionElementVector.subList((int) maxActions, primaryElementsSize);
            //Add excess elements to the secondary list if flag is enabled.
            if (hostConfig.GetActions().getAllowMoreThanMaxActionsInOverflowMenu())
            {
                secondaryActionElementVector.addAll(excessElements);
            }
            else
            {
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.MAX_ACTIONS_EXCEEDED, "A maximum of " + maxActions + " actions are allowed"));
            }
            excessElements.clear();
        }

        renderPrimaryActionElements(primaryActionElementVector, renderedCard, context, fragmentManager, actionButtonsLayout, cardActionHandler, hostConfig, renderArgs);
        if (!secondaryActionElementVector.isEmpty())
        {
            renderSecondaryActionElements(secondaryActionElementVector, renderedCard, context, fragmentManager, actionButtonsLayout, cardActionHandler, hostConfig, renderArgs);
        }

        return actionButtonsLayout;
    }

    /**
     * Renders primary action elements list.
     * @param primaryActionElementVector list of primary action elements
     * @param renderedCard renderedCard
     * @param context context
     * @param fragmentManager fragmentManager
     * @param actionButtonsLayout root view of the action elements set
     * @param cardActionHandler cardActionHandler
     * @param hostConfig client config
     * @param renderArgs renderArgs
     * @throws AdaptiveFallbackException error
     */
    private void renderPrimaryActionElements(@NonNull BaseActionElementVector primaryActionElementVector, RenderedAdaptiveCard renderedCard,
                                             Context context,
                                             FragmentManager fragmentManager,
                                             ViewGroup actionButtonsLayout,
                                             ICardActionHandler cardActionHandler,
                                             HostConfig hostConfig,
                                             RenderArgs renderArgs) throws AdaptiveFallbackException{
        FeatureRegistration featureRegistration = CardRendererRegistration.getInstance().getFeatureRegistration();

        for (BaseActionElement actionElement : primaryActionElementVector)
        {

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

                if (elementHasFallback) {
                    if (actionElement.GetFallbackType() == FallbackType.Content) {
                        BaseElement fallbackElement = actionElement.GetFallbackContent();

                        while (fallbackElement != null) {
                            try {
                                BaseActionElement fallbackActionElement = Util.castToBaseActionElement(fallbackElement);
                                IBaseActionElementRenderer fallbackActionRenderer = CardRendererRegistration.getInstance().getActionRenderer(fallbackActionElement.GetElementTypeString());

                                if (fallbackActionRenderer == null) {
                                    throw new AdaptiveFallbackException(fallbackElement);
                                }

                                if ((featureRegistration != null) && (!fallbackElement.MeetsRequirements(featureRegistration))) {
                                    throw new AdaptiveFallbackException(fallbackElement, featureRegistration);
                                }

                                fallbackActionRenderer.render(renderedCard, context, fragmentManager, actionButtonsLayout, fallbackActionElement, cardActionHandler, hostConfig, renderArgs);
                                break;
                            } catch (AdaptiveFallbackException e2) {
                                // As the fallback element didn't exist, go back to trying
                                if (fallbackElement.GetFallbackType() == FallbackType.Content) {
                                    fallbackElement = fallbackElement.GetFallbackContent();
                                } else {
                                    // The element has no fallback, just clear the element so the cycle ends
                                    fallbackElement = null;
                                }
                            }
                        }
                    }
                } else if (renderArgs.getAncestorHasFallback()) {
                    // There's an ancestor with fallback so we throw to trigger it
                    throw e;
                } else {
                    renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE, "Unsupported card element type: " + actionElement.GetElementTypeString()));
                }
            }
        }
    }

    /**
     * Renders secondary action elements list.
     * @param secondaryActionElementVector list of secondary action elements
     * @param renderedCard renderedCard
     * @param context context
     * @param fragmentManager fragmentManager
     * @param actionButtonsLayout root view of the action elements set
     * @param cardActionHandler cardActionHandler
     * @param hostConfig client config
     * @param renderArgs renderArgs
     * @throws AdaptiveFallbackException error
     */
    private void renderSecondaryActionElements(@NonNull BaseActionElementVector secondaryActionElementVector, RenderedAdaptiveCard renderedCard,
                                               Context context,
                                               FragmentManager fragmentManager,
                                               ViewGroup actionButtonsLayout,
                                               ICardActionHandler cardActionHandler,
                                               HostConfig hostConfig,
                                               RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        IActionLayoutRenderer overflowActionRenderer = OverflowActionLayoutRenderer.getInstance();
        overflowActionRenderer.renderActions(renderedCard, context, fragmentManager, actionButtonsLayout, secondaryActionElementVector, cardActionHandler, hostConfig, renderArgs);
    }

    private static ActionLayoutRenderer s_instance = null;
}
