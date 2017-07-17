package com.microsoft.adaptivecards.renderer.action;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.SubmitAction;
import com.microsoft.adaptivecards.renderer.BaseActionElementRenderer;

import java.util.HashMap;
import java.util.Vector;

/**
 * Created by bekao on 6/26/2017.
 */

public class SubmitActionRenderer extends BaseActionElementRenderer
{
    private SubmitActionRenderer()
    {
    }

    public static SubmitActionRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new SubmitActionRenderer();
        }

        return s_instance;
    }

    protected class SubmitButtonOnClickListener implements View.OnClickListener
    {
        public SubmitButtonOnClickListener(SubmitAction submitAction, Vector<IInputHandler> inputHandlerList, ISubmitActionHandler submitActionHandler)
        {
            m_submitAction = submitAction;
            m_inputHandlerList = inputHandlerList;
            m_submitActionHandler = submitActionHandler;
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
                    Toast.makeText(v.getContext(), excep.getMessage(), Toast.LENGTH_SHORT);
                    return;
                }
            }

            m_submitActionHandler.onSubmit(m_submitAction, data);
        }

        private SubmitAction m_submitAction;
        private Vector<IInputHandler> m_inputHandlerList;
        private ISubmitActionHandler m_submitActionHandler;
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
        SubmitAction submitAction = null;
        if (baseActionElement instanceof SubmitAction)
        {
            submitAction = (SubmitAction) baseActionElement;
        }
        else if ((submitAction = SubmitAction.dynamic_cast(baseActionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to SubmitAction object model.");
        }

        if (submitActionHandler == null)
        {
            throw new IllegalArgumentException("Submit Action Handler is null.");
        }

        Button button = renderButton(context, viewGroup, submitAction, hostConfig);
        button.setOnClickListener(new SubmitButtonOnClickListener(submitAction, inputHandlerList, submitActionHandler));
        return button;
    }

    private static SubmitActionRenderer s_instance = null;
}
