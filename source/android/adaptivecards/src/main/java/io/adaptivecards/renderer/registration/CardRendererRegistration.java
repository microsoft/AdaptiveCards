package io.adaptivecards.renderer.registration;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.Toast;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseCardElementVector;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.IBaseCardElementRenderer;
import io.adaptivecards.renderer.input.ChoiceSetInputRenderer;
import io.adaptivecards.renderer.input.DateInputRenderer;
import io.adaptivecards.renderer.input.NumberInputRenderer;
import io.adaptivecards.renderer.input.TextInputRenderer;
import io.adaptivecards.renderer.input.TimeInputRenderer;
import io.adaptivecards.renderer.input.ToggleInputRenderer;
import io.adaptivecards.renderer.readonly.ColumnRenderer;
import io.adaptivecards.renderer.readonly.ColumnSetRenderer;
import io.adaptivecards.renderer.readonly.ContainerRenderer;
import io.adaptivecards.renderer.readonly.FactSetRenderer;
import io.adaptivecards.renderer.readonly.ImageRenderer;
import io.adaptivecards.renderer.readonly.ImageSetRenderer;
import io.adaptivecards.renderer.readonly.TextBlockRenderer;

import java.util.HashMap;
import java.util.Vector;

public class CardRendererRegistration
{
    private CardRendererRegistration()
    {
        // Register Readonly Renderers
        registerRenderer(CardElementType.Column.toString(), ColumnRenderer.getInstance());
        registerRenderer(CardElementType.ColumnSet.toString(), ColumnSetRenderer.getInstance());
        registerRenderer(CardElementType.Container.toString(), ContainerRenderer.getInstance());
        registerRenderer(CardElementType.FactSet.toString(), FactSetRenderer.getInstance());
        registerRenderer(CardElementType.Image.toString(), ImageRenderer.getInstance());
        registerRenderer(CardElementType.ImageSet.toString(), ImageSetRenderer.getInstance());
        registerRenderer(CardElementType.TextBlock.toString(), TextBlockRenderer.getInstance());

        // Register Input Renderers
        registerRenderer(CardElementType.TextInput.toString(), TextInputRenderer.getInstance());
        registerRenderer(CardElementType.NumberInput.toString(), NumberInputRenderer.getInstance());
        registerRenderer(CardElementType.DateInput.toString(), DateInputRenderer.getInstance());
        registerRenderer(CardElementType.TimeInput.toString(), TimeInputRenderer.getInstance());
        registerRenderer(CardElementType.ToggleInput.toString(), ToggleInputRenderer.getInstance());
        registerRenderer(CardElementType.ChoiceSetInput.toString(), ChoiceSetInputRenderer.getInstance());
    }

    public static CardRendererRegistration getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new CardRendererRegistration();
        }

        return s_instance;
    }

    public void registerRenderer(String cardElementType, IBaseCardElementRenderer renderer)
    {
        if (TextUtils.isEmpty(cardElementType) || CardElementType.Unsupported.toString().equals(cardElementType))
        {
            throw new IllegalArgumentException("cardElementType is null or unsupported");
        }
        if (renderer == null)
        {
            throw new IllegalArgumentException("renderer is null");
        }

        m_typeToRendererMap.put(cardElementType, renderer);
    }

    public IBaseCardElementRenderer getRenderer(String cardElementType)
    {
        return m_typeToRendererMap.get(cardElementType);
    }

    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            Object tag,
            BaseCardElementVector baseCardElementList,
            Vector<IInputHandler> inputActionHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
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
            IBaseCardElementRenderer renderer = m_typeToRendererMap.get(cardElement.GetElementType().toString());
            if (renderer == null)
            {
                Toast.makeText(context, "Unsupported card element type: " + cardElement.GetElementType().toString(), Toast.LENGTH_SHORT).show();
                continue;
            }

            renderer.render(context, fragmentManager, layout, cardElement, inputActionHandlerList, cardActionHandler, hostConfig, containerStyle);
        }

        return layout;
    }

    private static CardRendererRegistration s_instance = null;

    private HashMap<String, IBaseCardElementRenderer> m_typeToRendererMap = new HashMap<String, IBaseCardElementRenderer>();
}
