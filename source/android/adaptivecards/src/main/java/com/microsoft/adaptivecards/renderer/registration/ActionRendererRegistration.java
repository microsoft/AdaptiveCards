package com.microsoft.adaptivecards.renderer.registration;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.ActionType;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.BaseActionElementVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.IBaseActionElementRenderer;
import com.microsoft.adaptivecards.renderer.action.ActionElementRenderer;
import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;

import java.util.HashMap;
import java.util.Vector;

public class ActionRendererRegistration
{
    private ActionRendererRegistration()
    {
        // Register Action Renderers
        registerRenderer(ActionType.OpenUrl.toString(), ActionElementRenderer.getInstance());
        registerRenderer(ActionType.ShowCard.toString(), ActionElementRenderer.getInstance());
        registerRenderer(ActionType.Submit.toString(), ActionElementRenderer.getInstance());
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
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            Object tag,
            BaseActionElementVector baseActionElementList,
            Vector<IInputHandler> inputActionHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig)
    {
        long size;
        if (baseActionElementList == null || (size = baseActionElementList.size()) <= 0)
        {
            return null;
        }

        LinearLayout actionsLayout = new LinearLayout(context);
        actionsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        actionsLayout.setOrientation(LinearLayout.VERTICAL);

        LinearLayout actionButtonsLayout = new LinearLayout(context);
        actionButtonsLayout.setTag(tag);
        actionButtonsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        actionButtonsLayout.setOrientation(LinearLayout.HORIZONTAL);

        LinearLayout hiddenCardsLayout = new LinearLayout(context);
        hiddenCardsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        hiddenCardsLayout.setOrientation(LinearLayout.VERTICAL);
        actionsLayout.addView(actionButtonsLayout);
        actionsLayout.addView(hiddenCardsLayout);

        if (viewGroup != null)
        {
            viewGroup.addView(actionsLayout);
        }

        for (int i = 0; i < size && i < hostConfig.getActions().getMaxActions(); i++)
        {
            BaseActionElement actionElement = baseActionElementList.get(i);
            IBaseActionElementRenderer renderer = m_typeToRendererMap.get(actionElement.GetElementType().toString());
            if (renderer == null)
            {
                Toast.makeText(context, "Unsupported action element type: " + actionElement.GetElementType().toString(), Toast.LENGTH_SHORT).show();
                continue;
            }

            renderer.render(context, fragmentManager, actionButtonsLayout, actionElement, inputActionHandlerList, cardActionHandler, hostConfig);
        }

        return actionsLayout;
    }

    private static ActionRendererRegistration s_instance = null;

    private HashMap<String, IBaseActionElementRenderer> m_typeToRendererMap = new HashMap<String, IBaseActionElementRenderer>();
}
