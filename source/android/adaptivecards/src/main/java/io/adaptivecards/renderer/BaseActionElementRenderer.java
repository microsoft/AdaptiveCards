// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IsVisible;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.objectmodel.ToggleVisibilityAction;
import io.adaptivecards.objectmodel.ToggleVisibilityTarget;
import io.adaptivecards.objectmodel.ToggleVisibilityTargetVector;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public abstract class BaseActionElementRenderer implements IBaseActionElementRenderer
{
    protected static int getColor(String colorCode)
    {
        return android.graphics.Color.parseColor(colorCode);
    }

    /**
     * Callback to be invoked when an select action for a card element is clicked
     */
    public static class SelectActionOnClickListener extends ActionOnClickListener
    {

        public SelectActionOnClickListener(RenderedAdaptiveCard renderedCard, BaseActionElement action, ICardActionHandler cardActionHandler)
        {
            super(renderedCard, action, cardActionHandler);

            if (m_action.GetElementType() == ActionType.ShowCard)
            {
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.SELECT_SHOW_CARD_ACTION, "ShowCard not supported for SelectAction"));
            }
        }

        @Override
        public void onClick(View v)
        {
            // As we don't support show card actions for select action, then avoid triggering the event
            if (m_action.GetElementType() != ActionType.ShowCard)
            {
                super.onClick(v);
            }
        }

    }

    /**
     * Callback to be invoked when an action is clicked
     */
    public static class ActionOnClickListener implements View.OnClickListener
    {

        /**
         * Constructs an ActionOnClickListener. Use this constructor if you want to support any type of action
         * @param renderedCard
         * @param context
         * @param fragmentManager
         * @param viewGroup
         * @param baseActionElement
         * @param cardActionHandler
         * @param hostConfig
         */
        public ActionOnClickListener(RenderedAdaptiveCard renderedCard,
                                     Context context,
                                     FragmentManager fragmentManager,
                                     ViewGroup viewGroup,
                                     BaseActionElement baseActionElement,
                                     ICardActionHandler cardActionHandler,
                                     HostConfig hostConfig,
                                     RenderArgs renderArgs)
        {
            this(renderedCard, baseActionElement, cardActionHandler);

            m_isInlineShowCardAction = (baseActionElement.GetElementType() == ActionType.ShowCard) && (hostConfig.GetActions().getShowCard().getActionMode() == ActionMode.Inline);

            // As SelectAction doesn't support ShowCard actions, then this line won't be executed
            if (m_isInlineShowCardAction)
            {
                renderHiddenCard(context, fragmentManager, viewGroup, hostConfig, renderArgs);
            }
        }

        /**
         * Constructs an ActionOnClickListener. Use this constructor if you want to support any type of action except ShowCardAction
         * @param renderedCard
         * @param baseActionElement
         * @param cardActionHandler
         */
        public ActionOnClickListener(RenderedAdaptiveCard renderedCard, BaseActionElement baseActionElement, ICardActionHandler cardActionHandler)
        {
            m_action = baseActionElement;
            m_renderedAdaptiveCard = renderedCard;
            m_cardActionHandler = cardActionHandler;

            // In case of the action being a ToggleVisibility action, store the action as ToggleVisibility action so no recasting must be made
            if (m_action.GetElementType() == ActionType.ToggleVisibility)
            {
                m_toggleVisibilityAction = null;
                if (m_action instanceof ToggleVisibilityAction)
                {
                    m_toggleVisibilityAction = (ToggleVisibilityAction) m_action;
                }
                else if ((m_toggleVisibilityAction = ToggleVisibilityAction.dynamic_cast(m_action)) == null)
                {
                    throw new InternalError("Unable to convert BaseActionElement to ToggleVisibilityAction object model.");
                }
            }
        }

        /**
         * Resets the visibility of all separators in this viewGroup hiding, if it has, the separator for the first visible element and showing the separator for all other elements
         * @param viewGroup
         */
        private void resetSeparatorVisibilities(ViewGroup viewGroup)
        {
            boolean isFirstElement = true;
            for (int i = 0; i < viewGroup.getChildCount(); ++i)
            {
                View element = viewGroup.getChildAt(i);
                TagContent tagContent = BaseCardElementRenderer.getTagContent(element);

                if (tagContent != null)
                {
                    if (!tagContent.IsSeparator() && element.getVisibility() == View.VISIBLE)
                    {
                        View separator = tagContent.GetSeparator();

                        if (separator != null)
                        {
                            // Only the first element must hide its separator
                            if (isFirstElement)
                            {
                                separator.setVisibility(View.GONE);
                            }
                            else
                            {
                                separator.setVisibility(View.VISIBLE);
                            }
                        }

                        // Reset this so all the other elements can have their separators visible
                        isFirstElement = false;
                    }
                }

            }
        }

        private void renderHiddenCard(Context context, FragmentManager fragmentManager, ViewGroup viewGroup, HostConfig hostConfig, RenderArgs renderArgs)
        {
            ShowCardAction showCardAction = Util.castTo(m_action, ShowCardAction.class);

            m_invisibleCard = AdaptiveCardRenderer.getInstance().internalRender(m_renderedAdaptiveCard, context, fragmentManager, showCardAction.GetCard(),
                                                                                m_cardActionHandler, hostConfig, true, renderArgs.getContainerCardId());
            m_invisibleCard.setVisibility(View.GONE);
            LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
            layoutParams.setMargins(0, Util.dpToPixels(context, hostConfig.GetActions().getShowCard().getInlineTopMargin()), 0, 0);
            m_invisibleCard.setLayoutParams(layoutParams);

            ViewGroup parent = (ViewGroup) viewGroup.getParent();
            if (parent instanceof HorizontalScrollView) // Required when the actions are set in horizontal
            {
                parent = (ViewGroup) parent.getParent().getParent();
            }
            else
            {
                parent = (ViewGroup) parent.getParent();
            }

            m_hiddenCardsLayout = (ViewGroup) parent.getChildAt(1);
            m_hiddenCardsLayout.addView(m_invisibleCard);
        }

        private Activity getActivity(Context context)
        {
            while (context instanceof ContextWrapper)
            {
                if (context instanceof Activity)
                {
                    return (Activity)context;
                }
                context = ((ContextWrapper)context).getBaseContext();
            }
            return null;
        }

        private void populateViewsDictionary()
        {
            m_viewDictionary = new HashMap<>();

            ToggleVisibilityTargetVector toggleVisibilityTargetVector = m_toggleVisibilityAction.GetTargetElements();
            View rootView = m_renderedAdaptiveCard.getView();

            for (int i = 0; i < toggleVisibilityTargetVector.size(); ++i)
            {
                ToggleVisibilityTarget target = toggleVisibilityTargetVector.get(i);
                String elementId = target.GetElementId();

                View foundView = rootView.findViewWithTag(new TagContent(elementId));
                if (foundView != null)
                {
                    m_viewDictionary.put(elementId, foundView);
                }
            }
        }

        private void handleInlineShowCardAction(View v)
        {
            Activity hostingActivity = getActivity(v.getContext());
            if (hostingActivity != null)
            {
                View currentFocusedView = hostingActivity.getCurrentFocus();
                if (currentFocusedView != null)
                {
                    currentFocusedView.clearFocus();
                }
            }

            v.setSelected(m_invisibleCard.getVisibility() != View.VISIBLE);
            // Reset all other buttons
            ViewGroup parentContainer = (ViewGroup)v.getParent();
            for (int i = 0; i < parentContainer.getChildCount(); ++i)
            {
                View actionInActionSet = parentContainer.getChildAt(i);
                if (v != actionInActionSet)
                {
                    actionInActionSet.setSelected(false);
                }
            }

            for (int i = 0; i < m_hiddenCardsLayout.getChildCount(); ++i)
            {
                View child = m_hiddenCardsLayout.getChildAt(i);
                if (child != m_invisibleCard)
                {
                    child.setVisibility(View.GONE);
                }
            }

            m_invisibleCard.setVisibility(m_invisibleCard.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);

            View mainCardView = ((ViewGroup) m_hiddenCardsLayout.getParent()).getChildAt(0);
            int padding = mainCardView.getPaddingTop();

            //remove bottom padding from top linear layout
            if (m_invisibleCard.getVisibility() == View.VISIBLE)
            {
                mainCardView.setPadding(padding, padding, padding, 0);
            }
            else
            {
                mainCardView.setPadding(padding, padding, padding, padding);
            }
        }

        private void handleToggleVisibilityAction(View v)
        {
            ToggleVisibilityTargetVector toggleVisibilityTargetVector = m_toggleVisibilityAction.GetTargetElements();

            // Populate the dictionary only once so multiple clicks don't perform the search operation every time
            if (m_viewDictionary == null)
            {
                populateViewsDictionary();
            }

            // Store the viewgroups to update to avoid updating the same one multiple times
            Set<ViewGroup> viewGroupsToUpdate = new HashSet<>();

            for (int i = 0; i < toggleVisibilityTargetVector.size(); ++i)
            {
                ToggleVisibilityTarget target = toggleVisibilityTargetVector.get(i);
                String elementId = target.GetElementId();

                if (m_viewDictionary.containsKey(elementId))
                {
                    View foundView = m_viewDictionary.get(elementId);
                    IsVisible isVisible = target.GetIsVisible();

                    boolean elementWillBeVisible = true;

                    // If the visibility changes to not visible or the visibility toggles and the element is currently visible then the element will not be visible
                    // Otherwise it will be visible (default value)
                    if ((isVisible == IsVisible.IsVisibleFalse) ||
                        (isVisible == IsVisible.IsVisibleToggle && foundView.getVisibility() == View.VISIBLE))
                    {
                        elementWillBeVisible = false;
                    }

                    BaseCardElementRenderer.setVisibility(elementWillBeVisible, foundView, viewGroupsToUpdate);

                }
            }

            for (ViewGroup container : viewGroupsToUpdate)
            {
                resetSeparatorVisibilities(container);
            }
        }

        @Override
        public void onClick(View view)
        {
            m_renderedAdaptiveCard.clearValidatedInputs();

            if (m_isInlineShowCardAction)
            {
                handleInlineShowCardAction(view);
            }
            else if (m_action.GetElementType() == ActionType.ToggleVisibility)
            {
                handleToggleVisibilityAction(view);
            }
            else
            {
                if (m_action.GetElementType() == ActionType.Submit || m_renderedAdaptiveCard.isActionSubmitable(view))
                {
                    // If an input is in focus before submit, and the same input is focused on error,
                    // the input would not be scrolled into view. Instead, clearing focus first ensures scroll.
                    Util.clearFocus(view);

                    if (!m_renderedAdaptiveCard.areInputsValid(Util.getViewId(view)))
                    {
                        return;
                    }
                }

                m_cardActionHandler.onAction(m_action, m_renderedAdaptiveCard);
            }
        }

        protected BaseActionElement m_action;
        protected RenderedAdaptiveCard m_renderedAdaptiveCard;
        protected ICardActionHandler m_cardActionHandler;

        // Information for handling ShowCard actions
        private View m_invisibleCard = null;
        private ViewGroup m_hiddenCardsLayout = null;
        private boolean m_isInlineShowCardAction = false;

        // Information for handling ToggleVisibility actions
        private HashMap<String, View> m_viewDictionary = null;
        private ToggleVisibilityAction m_toggleVisibilityAction = null;
    }
}
