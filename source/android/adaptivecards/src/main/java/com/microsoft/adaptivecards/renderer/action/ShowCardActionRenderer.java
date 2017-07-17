package com.microsoft.adaptivecards.renderer.action;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.microsoft.adaptivecards.renderer.AdaptiveCardRenderer;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.ShowCardAction;
import com.microsoft.adaptivecards.renderer.BaseActionElementRenderer;

import java.util.Vector;

/**
 * Created by bekao on 6/26/2017.
 */

public class ShowCardActionRenderer extends BaseActionElementRenderer
{
    private ShowCardActionRenderer()
    {
    }

    public static ShowCardActionRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ShowCardActionRenderer();
        }

        return s_instance;
    }

    protected class ShowCardButtonOnClickListener implements View.OnClickListener
    {
        public ShowCardButtonOnClickListener(ShowCardAction showCardAction, IShowCardActionHandler showCardActionHandler)
        {
            m_showCardAction = showCardAction;
            m_showCardActionHandler = showCardActionHandler;
        }

        @Override
        public void onClick(View v)
        {
            m_showCardActionHandler.onShowCard(m_showCardAction, m_showCardAction.GetCard());
        }

        private ShowCardAction m_showCardAction;
        private IShowCardActionHandler m_showCardActionHandler;
    }

    @Override
    public Button render(
            Context context,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            Vector<IInputHandler> inputHandlerList,
            IShowCardActionHandler showCardActionHandler,
            ISubmitActionHandler submitActionHandler,
            HostConfig hostConfig)
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

        if (showCardActionHandler == null)
        {
            throw new IllegalArgumentException("Show Card Action Handler is null.");
        }

        Button button = renderButton(context, viewGroup, showCardAction, hostConfig);
        button.setOnClickListener(new ShowCardButtonOnClickListener(showCardAction, showCardActionHandler));
        return button;
    }

    private static ShowCardActionRenderer s_instance = null;
}
