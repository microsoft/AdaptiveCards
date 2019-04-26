// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import java.util.HashMap;

import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IsVisible;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.objectmodel.ToggleVisibilityAction;
import io.adaptivecards.objectmodel.ToggleVisibilityTarget;
import io.adaptivecards.objectmodel.ToggleVisibilityTargetVector;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public abstract class BaseActionElementRenderer implements IBaseActionElementRenderer
{
    protected static class ButtonOnLayoutChangedListener implements View.OnLayoutChangeListener
    {
        public ButtonOnLayoutChangedListener(){}

        @Override
        public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom)
        {
            Button button = (Button)v;

            double textHeight = button.getTextSize();

            Rect bounds = new Rect();
            String text = button.getText().toString().toUpperCase();

            Paint paint = button.getPaint();
            paint.setTextSize((float) textHeight);
            paint.getTextBounds(text, 0, text.length(), bounds);

            Drawable[] icons = button.getCompoundDrawables();
            if(icons[0] != null) {
                double iconWidth = icons[0].getIntrinsicWidth();
                double buttonWidth = button.getWidth();
                double boundsWidth = bounds.width();
                double iconStartPosition = (buttonWidth - (iconWidth + mPadding + boundsWidth)) / 2;

                button.setCompoundDrawablePadding((int) (-iconStartPosition + mPadding));
                button.setPadding((int) iconStartPosition, 0, 0, 0);
            }
        }

        public void setPadding(int padding){
            mPadding = padding;
        }

        private int mPadding;
    }

    protected static int getColor(String colorCode)
    {
        return android.graphics.Color.parseColor(colorCode);
    }

    /**
     * Callback to be invoked when an select action for a card element is clicked
     */
    public static class SelectActionOnClickListener implements View.OnClickListener
    {

        public SelectActionOnClickListener(RenderedAdaptiveCard renderedCard, BaseActionElement action, ICardActionHandler cardActionHandler)
        {
            m_action = action;
            m_renderedAdaptiveCard = renderedCard;
            m_cardActionHandler = cardActionHandler;

            if(m_action.GetElementType() == ActionType.ToggleVisibility)
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
                if(foundView != null)
                {
                    m_viewDictionary.put(elementId, foundView);
                }
            }
        }

        @Override
        public void onClick(View v)
        {
            if(m_action.GetElementType() == ActionType.ToggleVisibility)
            {
                ToggleVisibilityTargetVector toggleVisibilityTargetVector = m_toggleVisibilityAction.GetTargetElements();

                // Populate the dictionary only once so multiple clicks don't perform the search operation every time
                if (m_viewDictionary == null)
                {
                    populateViewsDictionary();
                }

                for (int i = 0; i < toggleVisibilityTargetVector.size(); ++i)
                {
                    ToggleVisibilityTarget target = toggleVisibilityTargetVector.get(i);
                    String elementId = target.GetElementId();

                    if (m_viewDictionary.containsKey(elementId))
                    {
                        View foundView = m_viewDictionary.get(elementId);
                        IsVisible isVisible = target.GetIsVisible();

                        if (isVisible == IsVisible.IsVisibleFalse)
                        {
                            foundView.setVisibility(View.GONE);
                        }
                        else if (isVisible == IsVisible.IsVisibleTrue)
                        {
                            foundView.setVisibility(View.VISIBLE);
                        }
                        else
                        {
                            // Toggle
                            if (foundView.getVisibility() == View.GONE)
                            {
                                foundView.setVisibility(View.VISIBLE);
                            }
                            else
                            {
                                foundView.setVisibility(View.GONE);
                            }
                        }
                    }
                }
            }
            else
            {
                m_cardActionHandler.onAction(m_action, m_renderedAdaptiveCard);
            }
        }

        protected BaseActionElement m_action;
        protected RenderedAdaptiveCard m_renderedAdaptiveCard;
        protected ICardActionHandler m_cardActionHandler;

        private ToggleVisibilityAction m_toggleVisibilityAction = null;
        private HashMap<String, View> m_viewDictionary = null;
    }

    /**
     * Callback to be invoked when an action is clicked
     */
    public static class ActionOnClickListener extends SelectActionOnClickListener
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
                                     HostConfig hostConfig)
        {
            super(renderedCard, baseActionElement, cardActionHandler);
            m_isInlineShowCardAction = (baseActionElement.GetElementType() == ActionType.ShowCard) && (hostConfig.GetActions().getShowCard().getActionMode() == ActionMode.Inline);
            if (m_isInlineShowCardAction)
            {
                renderHiddenCard(context, fragmentManager, viewGroup, hostConfig);
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
            super(renderedCard, baseActionElement, cardActionHandler);
            m_isInlineShowCardAction = false;
        }

        private void renderHiddenCard(Context context, FragmentManager fragmentManager, ViewGroup viewGroup, HostConfig hostConfig)
        {
            ShowCardAction showCardAction = null;
            if (m_action instanceof ShowCardAction)
            {
                showCardAction = (ShowCardAction) m_action;
            }
            else if ((showCardAction = ShowCardAction.dynamic_cast(m_action)) == null)
            {
                throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
            }

            m_invisibleCard = AdaptiveCardRenderer.getInstance().internalRender(m_renderedAdaptiveCard, context, fragmentManager, showCardAction.GetCard(), m_cardActionHandler, hostConfig, true);
            m_invisibleCard.setVisibility(View.GONE);
            LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
            layoutParams.setMargins(0, Util.dpToPixels(context, hostConfig.GetActions().getShowCard().getInlineTopMargin()), 0, 0);
            m_invisibleCard.setLayoutParams(layoutParams);

            ViewGroup parent = (ViewGroup) viewGroup.getParent();
            if(parent instanceof HorizontalScrollView) // Required when the actions are set in horizontal
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

        @Override
        public void onClick(View v) {
            if (m_isInlineShowCardAction)
            {
                Activity hostingActivity = getActivity(v.getContext());
                if (hostingActivity != null) {
                    View currentFocusedView = hostingActivity.getCurrentFocus();
                    if (currentFocusedView != null) {
                        currentFocusedView.clearFocus();
                    }
                }

                v.setPressed(m_invisibleCard.getVisibility() != View.VISIBLE);
                for (int i = 0; i < m_hiddenCardsLayout.getChildCount(); ++i) {
                    View child = m_hiddenCardsLayout.getChildAt(i);
                    if (child != m_invisibleCard) {
                        child.setVisibility(View.GONE);
                    }
                }

                m_invisibleCard.setVisibility(m_invisibleCard.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);

                View mainCardView = ((ViewGroup) m_hiddenCardsLayout.getParent()).getChildAt(0);
                int padding = mainCardView.getPaddingTop();

                //remove bottom padding from top linear layout
                if (m_invisibleCard.getVisibility() == View.VISIBLE) {
                    mainCardView.setPadding(padding, padding, padding, 0);
                    m_invisibleCard.requestFocus();
                } else {
                    mainCardView.setPadding(padding, padding, padding, padding);
                }
            }
            else
            {
                super.onClick(v);
            }
        }

        private View m_invisibleCard;
        private ViewGroup m_hiddenCardsLayout;
        private boolean m_isInlineShowCardAction;
    }
}
