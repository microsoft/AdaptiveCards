package com.microsoft.adaptivecards.renderer.registration;

import android.content.Context;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.ActionType;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.BaseActionElementVector;
import com.microsoft.adaptivecards.objectmodel.CardElementType;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.IBaseActionElementRenderer;
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
        registerRenderer(ActionType.OpenUrl.toString(), OpenUrlActionRenderer.getInstance());
        registerRenderer(ActionType.ShowCard.toString(), ShowCardActionRenderer.getInstance());
        registerRenderer(ActionType.Submit.toString(), SubmitActionRenderer.getInstance());
    }

    public static ActionRendererRegistration getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ActionRendererRegistration();
        }

        return s_instance;
    }

    public void registerRenderer(String actionType, IBaseActionElementRenderer renderer)
    {
        if (TextUtils.isEmpty(actionType) || ActionType.Unsupported.toString().equals(actionType))
        {
            throw new IllegalArgumentException("actionType is null or unsupported");
        }
        if (renderer == null)
        {
            throw new IllegalArgumentException("renderer is null");
        }

        m_typeToRendererMap.put(actionType, renderer);
    }

    public IBaseActionElementRenderer getRenderer(String actionType)
    {
        return m_typeToRendererMap.get(actionType);
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
        layout.setOrientation(LinearLayout.HORIZONTAL);

        if (viewGroup != null)
        {
            viewGroup.addView(layout);
        }

        for (int i = 0; i < size; i++)
        {
            BaseActionElement actionElement = baseActionElementList.get(i);
            IBaseActionElementRenderer renderer = m_typeToRendererMap.get(actionElement.GetElementType().toString());
            if (renderer == null)
            {
                Toast.makeText(context, "Unsupported action element type: " + actionElement.GetElementType().toString(), Toast.LENGTH_SHORT).show();
                continue;
            }

            renderer.render(context, layout, actionElement, inputActionHandlerList, showCardActionHandler, submitActionHandler, hostConfig);
        }

        return layout;
    }

    private static ActionRendererRegistration s_instance = null;

    private HashMap<String, IBaseActionElementRenderer> m_typeToRendererMap = new HashMap<String, IBaseActionElementRenderer>();
}
