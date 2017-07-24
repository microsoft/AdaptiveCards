package com.microsoft.adaptivecards.renderer.action;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.OpenUrlAction;
import com.microsoft.adaptivecards.renderer.BaseActionElementRenderer;

import java.util.Vector;

/**
 * Created by bekao on 6/26/2017.
 */

public class OpenUrlActionRenderer extends BaseActionElementRenderer
{
    private OpenUrlActionRenderer()
    {
    }

    public static OpenUrlActionRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new OpenUrlActionRenderer();
        }

        return s_instance;
    }

    protected class OpenUrlButtonOnClickListener implements View.OnClickListener
    {
        public OpenUrlButtonOnClickListener(OpenUrlAction openUrlAction)
        {
            m_openUrlAction = openUrlAction;
        }

        @Override
        public void onClick(View v)
        {
            Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(m_openUrlAction.GetUrl()));
            v.getContext().startActivity(browserIntent);
        }

        private OpenUrlAction m_openUrlAction;
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
        OpenUrlAction openUrlAction = null;
        if (baseActionElement instanceof OpenUrlAction)
        {
            openUrlAction = (OpenUrlAction) baseActionElement;
        }
        else if ((openUrlAction = OpenUrlAction.dynamic_cast(baseActionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to OpenUrlAction object model.");
        }

        Button button = renderButton(context, viewGroup, openUrlAction, hostConfig);
        button.setOnClickListener(new OpenUrlActionRenderer.OpenUrlButtonOnClickListener(openUrlAction));
        return button;
    }

    private static OpenUrlActionRenderer s_instance = null;
}
