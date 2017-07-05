package com.microsoft.adaptivecards.renderer.registration;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.CardElementType;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.IBaseCardElementRenderer;
import com.microsoft.adaptivecards.renderer.input.ChoiceSetInputRenderer;
import com.microsoft.adaptivecards.renderer.input.DateInputRenderer;
import com.microsoft.adaptivecards.renderer.input.NumberInputRenderer;
import com.microsoft.adaptivecards.renderer.input.TextInputRenderer;
import com.microsoft.adaptivecards.renderer.input.TimeInputRenderer;
import com.microsoft.adaptivecards.renderer.input.ToggleInputRenderer;
import com.microsoft.adaptivecards.renderer.readonly.ColumnRenderer;
import com.microsoft.adaptivecards.renderer.readonly.ColumnSetRenderer;
import com.microsoft.adaptivecards.renderer.readonly.ContainerRenderer;
import com.microsoft.adaptivecards.renderer.readonly.FactSetRenderer;
import com.microsoft.adaptivecards.renderer.readonly.ImageRenderer;
import com.microsoft.adaptivecards.renderer.readonly.ImageSetRenderer;
import com.microsoft.adaptivecards.renderer.readonly.TextBlockRenderer;

import java.util.HashMap;
import java.util.Vector;

/**
 * Created by bekao on 4/28/2017.
 */

public class CardRendererRegistration
{
    private CardRendererRegistration()
    {
        // Register Readonly Renderers
        m_typeToRendererMap.put(CardElementType.Column.swigValue(), ColumnRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.ColumnSet.swigValue(), ColumnSetRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.Container.swigValue(), ContainerRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.FactSet.swigValue(), FactSetRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.Image.swigValue(), ImageRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.ImageSet.swigValue(), ImageSetRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.TextBlock.swigValue(), TextBlockRenderer.getInstance());

        // Register Input Renderers
        m_typeToRendererMap.put(CardElementType.TextInput.swigValue(), TextInputRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.NumberInput.swigValue(), NumberInputRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.DateInput.swigValue(), DateInputRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.TimeInput.swigValue(), TimeInputRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.ToggleInput.swigValue(), ToggleInputRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.ChoiceSetInput.swigValue(), ChoiceSetInputRenderer.getInstance());
    }

    public static CardRendererRegistration getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new CardRendererRegistration();
        }

        return s_instance;
    }

    public void registerRenderer(CardElementType cardElementType, IBaseCardElementRenderer renderer)
    {
        if (cardElementType != null || cardElementType == CardElementType.Unsupported)
        {
            throw new IllegalArgumentException("cardElementType is null or unsupported");
        }
        if (renderer == null)
        {
            throw new IllegalArgumentException("renderer is null");
        }

        m_typeToRendererMap.put(cardElementType.swigValue(), renderer);
    }

    public IBaseCardElementRenderer getRenderer(CardElementType cardElementType)
    {
        return m_typeToRendererMap.get(cardElementType.swigValue());
    }

    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            Object tag,
            BaseCardElementVector baseCardElementList,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        long size;
        if (baseCardElementList == null || (size = baseCardElementList.size()) <= 0)
        {
            return viewGroup;
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
            BaseCardElement cardElement = baseCardElementList.get(i);
            IBaseCardElementRenderer renderer = m_typeToRendererMap.get(cardElement.GetElementType().swigValue());
            if (renderer == null)
            {
                Toast.makeText(context, "Unsupported card element type: " + cardElement.GetElementType().toString(), Toast.LENGTH_SHORT);
                continue;
            }

            renderer.render(context, fragmentManager, layout, cardElement, inputActionHandlerList, hostConfig);
        }

        return layout;
    }

    private static CardRendererRegistration s_instance = null;

    private HashMap<Integer, IBaseCardElementRenderer> m_typeToRendererMap = new HashMap<Integer, IBaseCardElementRenderer>();
}
