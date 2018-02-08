package com.microsoft.adaptivecards.renderer.action;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.IBaseActionElementRenderer;
import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;

import java.util.HashMap;
import java.util.Vector;

public class ActionElementRenderer implements IBaseActionElementRenderer
{
    public ActionElementRenderer()
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

    private class ButtonOnClickListener implements View.OnClickListener
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
    public Button render(Context context, ViewGroup viewGroup, BaseActionElement baseActionElement, Vector<IInputHandler> inputHandlerList, ICardActionHandler cardActionHandler, HostConfig hostConfig) {
        if (cardActionHandler == null)
        {
            throw new IllegalArgumentException("Action Handler is null.");
        }

        Button button = renderButton(context, viewGroup, baseActionElement);
        button.setOnClickListener(new ButtonOnClickListener(baseActionElement, inputHandlerList, cardActionHandler));
        return button;
    }

    private static ActionElementRenderer s_instance = null;
}
