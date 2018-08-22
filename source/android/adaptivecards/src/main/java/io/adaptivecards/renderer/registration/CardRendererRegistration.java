package io.adaptivecards.renderer.registration;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.OrientationEventListener;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.IActionLayoutRenderer;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.ActionLayoutRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
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

import static io.adaptivecards.objectmodel.AdaptiveCardObjectModel.CardElementTypeToString;

public class CardRendererRegistration
{
    private CardRendererRegistration()
    {
        // Register Readonly Renderers
        registerRenderer(CardElementTypeToString(CardElementType.Column), ColumnRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.ColumnSet), ColumnSetRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.Container), ContainerRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.FactSet), FactSetRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.Image), ImageRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.ImageSet), ImageSetRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.TextBlock), TextBlockRenderer.getInstance());

        // Register Input Renderers
        registerRenderer(CardElementTypeToString(CardElementType.TextInput), TextInputRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.NumberInput), NumberInputRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.DateInput), DateInputRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.TimeInput), TimeInputRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.ToggleInput), ToggleInputRenderer.getInstance());
        registerRenderer(CardElementTypeToString(CardElementType.ChoiceSetInput), ChoiceSetInputRenderer.getInstance());

        // Register Action Renderer
        m_actionRenderer = ActionElementRenderer.getInstance();
        m_actionLayoutRenderer = ActionLayoutRenderer.getInstance();
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

    public void registerOnlineImageLoader(IOnlineImageLoader imageLoader)
    {
        m_onlineImageLoader = imageLoader;
    }

    public  IOnlineImageLoader getOnlineImageLoader()
    {
        return m_onlineImageLoader;
    }

    public void registerActionRenderer(IBaseActionElementRenderer actionRenderer)
    {
        m_actionRenderer = actionRenderer;
    }

    public IBaseActionElementRenderer getActionRenderer()
    {
        return m_actionRenderer;
    }

    public void registerActionLayoutRenderer(IActionLayoutRenderer actionLayoutRenderer)
    {
        m_actionLayoutRenderer = actionLayoutRenderer;
    }

    public IActionLayoutRenderer getActionLayoutRenderer()
    {
        return m_actionLayoutRenderer;
    }

    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            Object tag,
            BaseCardElementVector baseCardElementList,
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
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        layout.setOrientation(LinearLayout.VERTICAL);

        VerticalContentAlignment verticalContentAlignment = VerticalContentAlignment.Top;

        if(tag instanceof BaseCardElement)
        {
            if(tag instanceof Column)
            {
                Column column = (Column)tag;
                verticalContentAlignment = column.GetVerticalContentAlignment();
            }
            else if(tag instanceof Container)
            {
                Container container = (Container)tag;
                verticalContentAlignment = container.GetVerticalContentAlignment();
            }
        }
        else if(tag instanceof AdaptiveCard)
        {
            AdaptiveCard adaptiveCard = (AdaptiveCard)tag;
            verticalContentAlignment = adaptiveCard.GetVerticalContentAlignment();
        }

        if(verticalContentAlignment != VerticalContentAlignment.Top)
        {
            LinearLayout verticalAlignmentLayout = new LinearLayout(context);
            verticalAlignmentLayout.setOrientation(LinearLayout.HORIZONTAL);
            verticalAlignmentLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
            layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));

            if (verticalContentAlignment == VerticalContentAlignment.Center)
            {
                verticalAlignmentLayout.setGravity(Gravity.CENTER_VERTICAL);
            }
            else
            {
                verticalAlignmentLayout.setGravity(Gravity.BOTTOM);
            }

            verticalAlignmentLayout.addView(layout);

            if(viewGroup != null)
            {
                viewGroup.addView(verticalAlignmentLayout);
            }
        }
        else
        {
            if (viewGroup != null)
            {
                viewGroup.addView(layout);
            }
        }

        for (int i = 0; i < size; i++)
        {
            BaseCardElement cardElement = baseCardElementList.get(i);
            IBaseCardElementRenderer renderer = m_typeToRendererMap.get(cardElement.GetElementTypeString());
            if (renderer == null)
            {
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE,"Unsupported card element type: " + cardElement.GetElementTypeString()));
                continue;
            }

            renderer.render(renderedCard, context, fragmentManager, layout, cardElement, cardActionHandler, hostConfig, containerStyle);
        }

        return layout;
    }

    private static CardRendererRegistration s_instance = null;

    private HashMap<String, IBaseCardElementRenderer> m_typeToRendererMap = new HashMap<String, IBaseCardElementRenderer>();
    private IBaseActionElementRenderer m_actionRenderer = null;
    private IActionLayoutRenderer m_actionLayoutRenderer = null;
    private IOnlineImageLoader m_onlineImageLoader = null;
}
