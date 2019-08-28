// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.registration;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.AdaptiveCardObjectModel;
import io.adaptivecards.objectmodel.BaseElement;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.FallbackType;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.IResourceResolver;
import io.adaptivecards.renderer.IActionLayoutRenderer;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.IOnlineMediaLoader;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.ActionLayoutRenderer;
import io.adaptivecards.renderer.action.ActionSetRenderer;
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
import io.adaptivecards.renderer.inputhandler.IInputWatcher;
import io.adaptivecards.renderer.readonly.ColumnRenderer;
import io.adaptivecards.renderer.readonly.ColumnSetRenderer;
import io.adaptivecards.renderer.readonly.ContainerRenderer;
import io.adaptivecards.renderer.readonly.FactSetRenderer;
import io.adaptivecards.renderer.readonly.ImageRenderer;
import io.adaptivecards.renderer.readonly.ImageSetRenderer;
import io.adaptivecards.renderer.readonly.MediaRenderer;
import io.adaptivecards.renderer.readonly.RichTextBlockRenderer;
import io.adaptivecards.renderer.readonly.TextBlockRenderer;

import java.util.HashMap;

public class CardRendererRegistration
{
    private CardRendererRegistration()
    {
        // Register Readonly Renderers
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.Column), ColumnRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.ColumnSet), ColumnSetRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.Container), ContainerRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.FactSet), FactSetRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.Image), ImageRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.ImageSet), ImageSetRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.Media), MediaRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.RichTextBlock), RichTextBlockRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.TextBlock), TextBlockRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.ActionSet), ActionSetRenderer.getInstance());

        // Register Input Renderers
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.TextInput), TextInputRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.NumberInput), NumberInputRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.DateInput), DateInputRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.TimeInput), TimeInputRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.ToggleInput), ToggleInputRenderer.getInstance());
        registerRenderer(AdaptiveCardObjectModel.CardElementTypeToString(CardElementType.ChoiceSetInput), ChoiceSetInputRenderer.getInstance());

        // Register Action Renderer
        registerActionRenderer(AdaptiveCardObjectModel.ActionTypeToString(ActionType.Submit), ActionElementRenderer.getInstance());
        registerActionRenderer(AdaptiveCardObjectModel.ActionTypeToString(ActionType.ShowCard), ActionElementRenderer.getInstance());
        registerActionRenderer(AdaptiveCardObjectModel.ActionTypeToString(ActionType.OpenUrl), ActionElementRenderer.getInstance());
        registerActionRenderer(AdaptiveCardObjectModel.ActionTypeToString(ActionType.ToggleVisibility), ActionElementRenderer.getInstance());

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
        if (TextUtils.isEmpty(cardElementType))
        {
            throw new IllegalArgumentException("cardElementType is null");
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

    public void setInputWatcher(IInputWatcher inputWatcher) {
        m_InputWatcher = inputWatcher;
    }

    public IInputWatcher getInputWatcher() {
        return m_InputWatcher;
    }

    public void notifyInputChange(String id, String value)
    {
        if (m_InputWatcher != null)
        {
            m_InputWatcher.onInputChange(id, value);
        }
    }

    public void registerActionRenderer(String actionElementType, IBaseActionElementRenderer actionRenderer)
    {
        if (TextUtils.isEmpty(actionElementType))
        {
            throw new IllegalArgumentException("cardElementType is null");
        }
        if (actionRenderer == null)
        {
            throw new IllegalArgumentException("renderer is null");
        }

        m_typeToRenderActionMap.put(actionElementType, actionRenderer);
    }

    public IBaseActionElementRenderer getActionRenderer(String actionElementType)
    {
        return m_typeToRenderActionMap.get(actionElementType);
    }

    public void registerActionLayoutRenderer(IActionLayoutRenderer actionLayoutRenderer)
    {
        m_actionLayoutRenderer = actionLayoutRenderer;
    }

    public IOnlineMediaLoader getOnlineMediaLoader()
    {
        return m_onlineMediaLoader;
    }

    public void registerOnlineMediaLoader(IOnlineMediaLoader onlineMediaLoader)
    {
        m_onlineMediaLoader = onlineMediaLoader;
    }

    /**
     * @deprecated As of AdaptiveCards 1.2, replaced by {@link #registerResourceResolver(String, IResourceResolver)}
     */
    @Deprecated
    public void registerOnlineImageLoader(IOnlineImageLoader imageLoader)
    {
        m_onlineImageLoader = imageLoader;
    }

    /**
     * @deprecated As of AdaptiveCards 1.2, replaced by {@link #getResourceResolver(String)}
     */
    @Deprecated
    public  IOnlineImageLoader getOnlineImageLoader()
    {
        return m_onlineImageLoader;
    }

    public void registerResourceResolver(String scheme, IResourceResolver resolver)
    {
        m_resourceResolvers.put(scheme, resolver);
    }

    public IResourceResolver getResourceResolver(String scheme)
    {
        return m_resourceResolvers.get(scheme);
    }

    public IActionLayoutRenderer getActionLayoutRenderer()
    {
        return m_actionLayoutRenderer;
    }

    public void registerFeatureRegistration(FeatureRegistration featureRegistration)
    {
        m_featureRegistration = featureRegistration;
    }

    public FeatureRegistration getFeatureRegistration()
    {
        return m_featureRegistration;
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
            RenderArgs renderArgs) throws AdaptiveFallbackException
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

        // Add this two for allowing children to bleed
        layout.setClipChildren(false);
        layout.setClipToPadding(false);

        VerticalContentAlignment verticalContentAlignment = VerticalContentAlignment.Top;

        if (tag instanceof BaseCardElement)
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

        FeatureRegistration featureRegistration = CardRendererRegistration.getInstance().getFeatureRegistration();

        for (int i = 0; i < size; i++)
        {
            BaseCardElement cardElement = baseCardElementList.get(i);
            renderElementAndPerformFallback(renderedCard, context, fragmentManager, cardElement, layout, cardActionHandler, hostConfig, renderArgs, featureRegistration);
        }

        // This is made as the last operation so we can assure the contents were rendered properly
        if (verticalContentAlignment != VerticalContentAlignment.Top)
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

            if (viewGroup != null)
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

        return layout;
    }

    public void renderElementAndPerformFallback(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            BaseCardElement cardElement,
            ViewGroup viewGroup,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs,
            FeatureRegistration featureRegistration) throws AdaptiveFallbackException
    {
        IBaseCardElementRenderer renderer = m_typeToRendererMap.get(cardElement.GetElementTypeString());

        boolean elementHasFallback = (cardElement.GetFallbackType() != FallbackType.None);
        RenderArgs childRenderArgs = new RenderArgs(renderArgs);
        childRenderArgs.setAncestorHasFallback(elementHasFallback || renderArgs.getAncestorHasFallback());

        try
        {
            if (renderer == null)
            {
                throw new AdaptiveFallbackException(cardElement);
            }

            if ((featureRegistration != null) && (!cardElement.MeetsRequirements(featureRegistration)))
            {
                throw new AdaptiveFallbackException(cardElement, featureRegistration);
            }

            renderer.render(renderedCard, context, fragmentManager, viewGroup, cardElement, cardActionHandler, hostConfig, childRenderArgs);
        }
        catch (AdaptiveFallbackException e)
        {
            if (elementHasFallback)
            {
                if (cardElement.GetFallbackType() == FallbackType.Content)
                {
                    BaseElement fallbackElement = cardElement.GetFallbackContent();
                    while (fallbackElement != null)
                    {
                        // Try to render the fallback element
                        try
                        {
                            BaseCardElement fallbackCardElement = null;
                            if (fallbackElement instanceof BaseCardElement)
                            {
                                fallbackCardElement = (BaseCardElement) fallbackElement;
                            }
                            else if ((fallbackCardElement = BaseCardElement.dynamic_cast(fallbackElement)) == null)
                            {
                                throw new InternalError("Unable to convert BaseElement to BaseCardElement object model.");
                            }

                            IBaseCardElementRenderer fallbackRenderer = m_typeToRendererMap.get(fallbackElement.GetElementTypeString());

                            if (fallbackRenderer == null)
                            {
                                throw new AdaptiveFallbackException(fallbackCardElement);
                            }

                            if ((featureRegistration != null) && (!fallbackElement.MeetsRequirements(featureRegistration)))
                            {
                                throw new AdaptiveFallbackException(fallbackCardElement, featureRegistration);
                            }

                            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE,
                                "Performing fallback for '" + cardElement.GetElementTypeString() +
                                    "' (fallback element type: '" + fallbackCardElement.GetElementTypeString() + "')"));

                            fallbackRenderer.render(renderedCard, context, fragmentManager, viewGroup, fallbackCardElement, cardActionHandler, hostConfig, childRenderArgs);
                            break;
                        }
                        catch (AdaptiveFallbackException e2)
                        {
                            // As the fallback element didn't exist, go back to trying
                            if (fallbackElement.GetFallbackType() == FallbackType.Content)
                            {
                                fallbackElement = fallbackElement.GetFallbackContent();
                            }
                            else
                            {
                                // The element has no fallback, just clear the element so the cycle ends
                                fallbackElement = null;
                            }
                        }
                    }
                }
                else if (cardElement.GetFallbackType() == FallbackType.Drop)
                {
                    renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE,
                        "Dropping element '" + cardElement.GetElementTypeString() + "' for fallback"));
                }
            }
            else if (renderArgs.getAncestorHasFallback())
            {
                // There's an ancestor with fallback so we throw to trigger it
                throw e;
            }
            else
            {
                // The element doesn't have a fallback, so the element can't be rendered and it's dropped
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE,"Unsupported card element type: " + cardElement.GetElementTypeString()));
            }

        }
    }

    private static CardRendererRegistration s_instance = null;
    private IInputWatcher m_InputWatcher = null;
    private HashMap<String, IBaseCardElementRenderer> m_typeToRendererMap = new HashMap<String, IBaseCardElementRenderer>();
    private HashMap<String, IBaseActionElementRenderer> m_typeToRenderActionMap = new HashMap<String, IBaseActionElementRenderer>();
    private IActionLayoutRenderer m_actionLayoutRenderer = null;
    private IOnlineImageLoader m_onlineImageLoader = null;
    private HashMap<String, IResourceResolver> m_resourceResolvers = new HashMap<>();
    private IOnlineMediaLoader m_onlineMediaLoader = null;
    private FeatureRegistration m_featureRegistration = null;
}
