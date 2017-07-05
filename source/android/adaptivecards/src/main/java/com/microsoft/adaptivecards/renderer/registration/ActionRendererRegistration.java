package com.microsoft.adaptivecards.renderer.registration;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.ActionType;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.BaseActionElementVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.IBaseActionElementRenderer;
import com.microsoft.adaptivecards.renderer.action.HttpActionRenderer;
import com.microsoft.adaptivecards.renderer.action.OpenUrlActionRenderer;
import com.microsoft.adaptivecards.renderer.action.ShowCardActionRenderer;
import com.microsoft.adaptivecards.renderer.action.SubmitActionRenderer;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;

import java.util.HashMap;
import java.util.Vector;

/**
 * Created by bekao on 7/1/2017.
 */

public class ActionRendererRegistration
{
    private ActionRendererRegistration()
    {
        // Register Action Renderers
        m_typeToRendererMap.put(ActionType.Http.swigValue(), HttpActionRenderer.getInstance());
        m_typeToRendererMap.put(ActionType.OpenUrl.swigValue(), OpenUrlActionRenderer.getInstance());
        m_typeToRendererMap.put(ActionType.ShowCard.swigValue(), ShowCardActionRenderer.getInstance());
        m_typeToRendererMap.put(ActionType.Submit.swigValue(), SubmitActionRenderer.getInstance());
    }

    public static ActionRendererRegistration getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ActionRendererRegistration();
        }

        return s_instance;
    }

    public void registerRenderer(ActionType actionType, IBaseActionElementRenderer renderer)
    {
        if (actionType != null || actionType == actionType.Unsupported)
        {
            throw new IllegalArgumentException("actionType is null or unsupported");
        }
        if (renderer == null)
        {
            throw new IllegalArgumentException("renderer is null");
        }

        m_typeToRendererMap.put(actionType.swigValue(), renderer);
    }

    public IBaseActionElementRenderer getRenderer(ActionType actionType)
    {
        return m_typeToRendererMap.get(actionType.swigValue());
    }

    public View render(
            Context context,
            ViewGroup viewGroup,
            Object tag,
            BaseActionElementVector baseActionElementList,
            Vector<IInputHandler> inputActionHandlerList,
            IShowCardActionHandler showCardActionHandler,
            ISubmitActionHandler submitActionHandler,
            HostConfig hostConfig)
    {
        long size;
        if (baseActionElementList == null || (size = baseActionElementList.size()) <= 0)
        {
            return null;
        }

        LinearLayout layout = new LinearLayout(context);
        layout.setTag(tag);
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        layout.setOrientation(LinearLayout.VERTICAL);

        if (viewGroup != null)
        {
            viewGroup.addView(layout);
        }

        for (int i = 0; i < size; i++)
        {
            BaseActionElement actionElement = baseActionElementList.get(i);
            IBaseActionElementRenderer renderer = m_typeToRendererMap.get(actionElement.GetElementType().swigValue());
            if (renderer == null)
            {
                Toast.makeText(context, "Unsupported action element type: " + actionElement.GetElementType().toString(), Toast.LENGTH_SHORT);
                continue;
            }

            renderer.render(context, layout, actionElement, inputActionHandlerList, showCardActionHandler, submitActionHandler, hostConfig);
        }

        return layout;
    }

    private static ActionRendererRegistration s_instance = null;

    private HashMap<Integer, IBaseActionElementRenderer> m_typeToRendererMap = new HashMap<Integer, IBaseActionElementRenderer>();
}
