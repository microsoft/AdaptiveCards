package com.microsoft.adaptivecards.renderer.action;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.ActionMode;
import com.microsoft.adaptivecards.objectmodel.ActionType;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.ShowCardAction;
import com.microsoft.adaptivecards.renderer.AdaptiveCardRenderer;
import com.microsoft.adaptivecards.renderer.IBaseActionElementRenderer;
import com.microsoft.adaptivecards.renderer.Util;
import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;

import java.util.HashMap;
import java.util.Vector;

public class ActionElementRenderer implements IBaseActionElementRenderer
{
    private ActionElementRenderer()
    {
    }

    public static ActionElementRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ActionElementRenderer();
        }

        return s_instance;
    }

    public static class ButtonOnClickListener implements View.OnClickListener
    {

        public ButtonOnClickListener(BaseActionElement action, Vector< IInputHandler > inputHandlerList, ICardActionHandler cardActionHandler)
        {
            m_action = action;
            m_inputHandlerList = inputHandlerList;
            m_cardActionHandler = cardActionHandler;
        }

        @Override
        public void onClick(View v)
        {
            HashMap<String, String> data = new HashMap<String, String>();
            for (IInputHandler inputHandler  : m_inputHandlerList)
            {
                Exception excep = inputHandler.getData(data);
                if (excep != null)
                {
                    Toast.makeText(v.getContext(), excep.getMessage(), Toast.LENGTH_SHORT).show();
                    return;
                }
            }

            m_cardActionHandler.onAction(m_action, data);
        }

        private BaseActionElement m_action;
        private Vector<IInputHandler> m_inputHandlerList;
        private ICardActionHandler m_cardActionHandler;
    }


    protected class ShowCardInlineClickListener implements View.OnClickListener
    {
        public ShowCardInlineClickListener(View invisibleCard, ViewGroup hiddenCardsLayout)
        {
            m_invisibleCard = invisibleCard;
            m_hiddenCardsLayout = hiddenCardsLayout;
        }

        @Override
        public void onClick(View v)
        {
            v.setPressed(m_invisibleCard.getVisibility() != View.VISIBLE);
            for(int i = 0; i < m_hiddenCardsLayout.getChildCount(); ++i)
            {
                View child = m_hiddenCardsLayout.getChildAt(i);
                if (child != m_invisibleCard)
                {
                    child.setVisibility(View.GONE);
                }
            }

            m_invisibleCard.setVisibility(m_invisibleCard.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
        }
        private View m_invisibleCard;
        private ViewGroup m_hiddenCardsLayout;
    }



    public Button renderButton(
            Context context,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement)
    {
        Button button = new Button(context);
        button.setText(baseActionElement.GetTitle());
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.MATCH_PARENT);
        button.setLayoutParams(layoutParams);
        viewGroup.addView(button);
        return button;
    }

    @Override
    public Button render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            Vector<IInputHandler> inputHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig) {
        if (cardActionHandler == null)
        {
            throw new IllegalArgumentException("Action Handler is null.");
        }

        Button button = renderButton(context, viewGroup, baseActionElement);
        button.setTextSize(hostConfig.getFontSizes().getDefaultFontSize());
        if (baseActionElement.GetElementType().swigValue() == ActionType.ShowCard.swigValue()
                && hostConfig.getActions().getShowCard().getActionMode().swigValue() == ActionMode.Inline.swigValue())
        {

            ShowCardAction showCardAction = null;
            if (baseActionElement instanceof ShowCardAction)
            {
                showCardAction = (ShowCardAction) baseActionElement;
            }
            else if ((showCardAction = ShowCardAction.dynamic_cast(baseActionElement)) == null)
            {
                throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
            }

            View invisibleCard = AdaptiveCardRenderer.getInstance().render(context, fragmentManager, showCardAction.GetCard(), cardActionHandler, hostConfig);
            invisibleCard.setVisibility(View.GONE);
            invisibleCard.setPadding(0,Util.dpToPixels(context, hostConfig.getActions().getShowCard().getInlineTopMargin()),0,0);


            ViewGroup parent = (ViewGroup) viewGroup.getParent();
            ViewGroup hiddenCards = (ViewGroup) parent.getChildAt(1);
            hiddenCards.addView(invisibleCard);

            button.setOnClickListener(new ShowCardInlineClickListener(invisibleCard, hiddenCards));
        }
        else
        {
            button.setOnClickListener(new ButtonOnClickListener(baseActionElement, inputHandlerList, cardActionHandler));
        }
        return button;
    }

    private static ActionElementRenderer s_instance = null;
}
