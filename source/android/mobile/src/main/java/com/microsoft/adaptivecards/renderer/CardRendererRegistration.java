package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.text.TextUtils;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.CardElementType;
import com.microsoft.adaptivecards.objectmodel.HostOptions;

import java.util.HashMap;

/**
 * Created by bekao on 4/28/2017.
 */

public class CardRendererRegistration
{
    private CardRendererRegistration()
    {
        m_typeToRendererMap.put(CardElementType.Column.toString(), ColumnRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.ColumnSet.toString(), ColumnSetRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.Container.toString(), ContainerRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.FactSet.toString(), FactSetRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.Image.toString(), ImageRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.ImageSet.toString(), ImageSetRenderer.getInstance());
        m_typeToRendererMap.put(CardElementType.TextBlock.toString(), TextBlockRenderer.getInstance());
    }

    public static CardRendererRegistration getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new CardRendererRegistration();
        }

        return s_instance;
    }

    public void registerRenderer(String cardType, IBaseCardElementRenderer renderer)
    {
        if (TextUtils.isEmpty(cardType))
        {
            throw new IllegalArgumentException("cardType is null or empty");
        }
        if (renderer == null)
        {
            throw new IllegalArgumentException("renderer is null");
        }

        m_typeToRendererMap.put(cardType, renderer);
    }

    public IBaseCardElementRenderer getRenderer(String cardElementType)
    {
        return m_typeToRendererMap.get(cardElementType);
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElementVector baseCardElementList, HostOptions hostOptions)
    {
        long size;
        if (baseCardElementList == null || (size = baseCardElementList.size()) <= 0)
        {
            return viewGroup;
        }

        LinearLayout layout = new LinearLayout(context);
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        layout.setOrientation(LinearLayout.VERTICAL);
        if (viewGroup != null)
        {
            viewGroup.addView(layout);
        }

        for (int i = 0; i < size; i++)
        {
            BaseCardElement cardElement = baseCardElementList.get(i);
            IBaseCardElementRenderer renderer = m_typeToRendererMap.get(cardElement.GetElementType().toString());
            if (renderer == null)
            {
                Toast.makeText(context, "Unsupported card element type: " + cardElement.GetElementType().toString(), Toast.LENGTH_SHORT);
                continue;
            }

            renderer.render(context, layout, cardElement, hostOptions);
        }

        return viewGroup == null ? layout : viewGroup;
    }

    private static CardRendererRegistration s_instance = null;

    private HashMap<String, IBaseCardElementRenderer> m_typeToRendererMap = new HashMap<String, IBaseCardElementRenderer>();
}
