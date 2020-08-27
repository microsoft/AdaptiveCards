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
import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.Column;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.FallbackType;
import io.adaptivecards.objectmodel.FeatureRegistration;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSet;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.IResourceResolver;
import io.adaptivecards.renderer.IActionLayoutRenderer;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.IOnlineMediaLoader;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
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
import io.adaptivecards.renderer.input.InputUtil;
import io.adaptivecards.renderer.input.NumberInputRenderer;
import io.adaptivecards.renderer.input.TextInputRenderer;
import io.adaptivecards.renderer.input.TimeInputRenderer;
import io.adaptivecards.renderer.input.ToggleInputRenderer;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.renderer.inputhandler.IInputWatcher;
import io.adaptivecards.renderer.layout.StretchableElementLayout;
import io.adaptivecards.renderer.layout.StretchableInputLayout;
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
            RenderArgs renderArgs) throws AdaptiveFallbackException, Exception
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
            FeatureRegistration featureRegistration) throws AdaptiveFallbackException, Exception
    {
        IBaseCardElementRenderer renderer = m_typeToRendererMap.get(cardElement.GetElementTypeString());

        boolean elementHasFallback = (cardElement.GetFallbackType() != FallbackType.None);
        RenderArgs childRenderArgs = new RenderArgs(renderArgs);
        childRenderArgs.setAncestorHasFallback(elementHasFallback || renderArgs.getAncestorHasFallback());

        // To avoid tampering with this method, this two variables are introduced:
        // - renderedElement contains the element that was finally rendered (after performing fallback)
        //      this allows us to check if it was an input and render the label and error message
        BaseCardElement renderedElement = null;
        View renderedElementView = null;

        // - mockLayout is a layout to contain the rendered element, as android renderers have to add
        //      the drawn views into the container view, it makes it easier to do not draw something unwanted
        //      into the final rendered card
        LinearLayout mockLayout = new LinearLayout(context);

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

            renderedElementView = renderer.render(renderedCard, context, fragmentManager, mockLayout, cardElement, cardActionHandler, hostConfig, childRenderArgs);
            renderedElement = cardElement;
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
                            BaseCardElement fallbackCardElement = Util.castToBaseCardElement(fallbackElement);
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

                            // before rendering, check if the element to render is an input, if it is, then create an stretchable input layout, and add the label
                            // pass that as the viewgroup and

                            renderedElementView = fallbackRenderer.render(renderedCard, context, fragmentManager, mockLayout, fallbackCardElement, cardActionHandler, hostConfig, childRenderArgs);
                            renderedElement = fallbackCardElement;
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

                            renderedElement = null;
                        }
                    }
                }
                else if (cardElement.GetFallbackType() == FallbackType.Drop)
                {
                    renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE,
                                                                "Dropping element '" + cardElement.GetElementTypeString() + "' for fallback"));

                    renderedElement = null;
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
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNKNOWN_ELEMENT_TYPE, "Unsupported card element type: " + cardElement.GetElementTypeString()));
                renderedElement = null;
            }
        }

        if (renderedElement != null)
        {

            View taggedView = findElementWithTagContent(mockLayout);
            TagContent tagContent = BaseCardElementRenderer.getTagContent(taggedView);

            // Sets this view container as the element is being moved to the correct location
            tagContent.SetViewContainer(viewGroup);

            // Render the spacing so no other renderers have to do it
            boolean isColumn = Util.isOfType(renderedElement, Column.class);

            // Only columns render vertical spacing, so if it's not a column, then we need a horizontal spacing
            HandleSpacing(context, viewGroup, renderedElement, hostConfig, tagContent, !isColumn);

            // Check if the element is an input or must be stretched
            BaseInputElement baseInputElement = Util.tryCastTo(renderedElement, BaseInputElement.class);
            if (baseInputElement != null)
            {
                // put the element in a Stretchable input layout and
                HandleLabelAndValidation(renderedCard, mockLayout, viewGroup, baseInputElement, context, hostConfig, renderArgs, tagContent);
            }
            else
            {
                // Column, container, image and imageSet handle their height on their own, so let's not add an extra view for them
                if (renderedElement.GetHeight() == HeightType.Stretch && !isColumn && !Util.isOfType(renderedElement, Container.class)
                    && !Util.isOfType(renderedElement, Image.class) && !Util.isOfType(renderedElement, ImageSet.class))
                {
                    // put the element in a StretchableElementLayout
                    HandleStretchHeight(mockLayout, viewGroup, renderedElement, context, tagContent);
                }
                else
                {
                    Util.MoveChildrenViews(mockLayout, viewGroup);
                }
            }

            HandleVisibility(renderedElement, renderedElementView);
        }
    }

    private static void HandleSpacing(Context context,
                                      ViewGroup viewGroup,
                                      BaseCardElement cardElement,
                                      HostConfig hostConfig,
                                      TagContent tagContent,
                                      boolean isHorizontalSpacing)
    {
        // Render spacing
        View separator = BaseCardElementRenderer.setSpacingAndSeparator(context,
                                                                        viewGroup,
                                                                        cardElement.GetSpacing(),
                                                                        cardElement.GetSeparator(),
                                                                        hostConfig,
                                                                        isHorizontalSpacing,
                                                                        false /* isImageSet */);

        // Sets the spacing as now we handle the spacing rendering
        tagContent.SetSeparator(separator);
    }

    private static void HandleVisibility(BaseCardElement element, View renderedElementView)
    {
        BaseCardElementRenderer.setVisibility(element.GetIsVisible(), renderedElementView);
    }

    private static void HandleLabelAndValidation(RenderedAdaptiveCard renderedCard,
                                                ViewGroup mockLayout,
                                                ViewGroup container,
                                                BaseInputElement element,
                                                Context context,
                                                HostConfig hostConfig,
                                                RenderArgs renderArgs,
                                                TagContent tagContent)
    {
        // as first step we must figure out if the input requires a container layout
        // it will require a container layout if:
        // it needs to be stretched
        // it contains a label
        // it needs validation (has an error message or isrequired or hasSpecificValidation)
        // Specific validation refers to validation not in all input elements, e.g. regex or min/max
        boolean mustStretch = (element.GetHeight() == HeightType.Stretch);
        boolean inputHasLabel = !element.GetLabel().isEmpty();
        boolean inputHasErrorMessage = !element.GetErrorMessage().isEmpty();
        boolean requiresSurroundingLayout =  mustStretch || inputHasLabel || inputHasErrorMessage;

        if (requiresSurroundingLayout)
        {
            StretchableInputLayout inputLayout = new StretchableInputLayout(context, mustStretch);
            View actualInput = findElementWithTagContent(mockLayout);

            if (inputHasLabel)
            {
                View inputLabel = InputUtil.RenderInputLabel(element.GetLabel(), element.GetIsRequired(), context, hostConfig, renderArgs);
                inputLayout.setLabel(inputLabel);

                // Render spacing
                BaseCardElementRenderer.setSpacingAndSeparator(context,
                    inputLayout,
                    hostConfig.GetInputs().getLabel().getInputSpacing(),
                    false /* separator */,
                    hostConfig,
                    true /* horizontalLine */);

                inputLabel.setLabelFor(actualInput.getId());
            }
            else if (element.GetIsRequired())
            {
                renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.EMPTY_LABEL_IN_REQUIRED_INPUT, "Input is required but there's no label for required hint rendering"));
            }

            tagContent.SetStretchContainer(inputLayout);

            if (mockLayout.getChildCount() == 1)
            {
                View inputView = mockLayout.getChildAt(0);
                mockLayout.removeView(inputView);
                inputLayout.setInputView(inputView);
            }
            else
            {
                Util.MoveChildrenViews(mockLayout, inputLayout);
            }

            if (inputHasErrorMessage)
            {
                // Render spacing
                View spacing = BaseCardElementRenderer.setSpacingAndSeparator(context,
                    inputLayout,
                    hostConfig.GetInputs().getErrorMessage().getSpacing(),
                    false /* separator */,
                    hostConfig,
                    true /* horizontalLine */);

                View errorMessage = InputUtil.RenderErrorMessage(element.GetErrorMessage(), context, hostConfig, renderArgs);
                errorMessage.setTag(new TagContent(null, spacing, null));
                inputLayout.setErrorMessage(errorMessage);

                BaseCardElementRenderer.setVisibility(false, errorMessage);

                IInputHandler inputHandler = tagContent.GetInputHandler();
                if (inputHandler instanceof BaseInputHandler)
                {
                    ((BaseInputHandler)inputHandler).setInputLayout(inputLayout);
                }
            }

            container.addView(inputLayout);
        }
        else
        {
            Util.MoveChildrenViews(mockLayout, container);
        }
    }

    private static void HandleStretchHeight(ViewGroup mockLayout,
                                           ViewGroup container,
                                           BaseCardElement element,
                                           Context context,
                                           TagContent tagContent)
    {
        boolean mustStretch = element.GetHeight() == HeightType.Stretch;

        if (mustStretch)
        {
            // Create a stretchable input lay
            StretchableElementLayout stretchElementLayout = new StretchableElementLayout(context, mustStretch);
            Util.MoveChildrenViews(mockLayout, stretchElementLayout);
            container.addView(stretchElementLayout);

            tagContent.SetStretchContainer(container);
        }
        else
        {
            // Just move the generated views into the actual container
            Util.MoveChildrenViews(mockLayout, container);
        }
    }

    public static View findElementWithTagContent(ViewGroup viewContainer)
    {
        for (int i = 0; i < viewContainer.getChildCount(); ++i)
        {
            View view = viewContainer.getChildAt(i);
            Object rawTag = view.getTag();
            if (rawTag != null  && rawTag instanceof TagContent)
            {
                return view;
            }

            // Test whether the taggedView is in a child view
            if (view instanceof ViewGroup)
            {
                View childTaggedContent = findElementWithTagContent((ViewGroup)view);
                if (childTaggedContent != null)
                {
                    return childTaggedContent;
                }
            }
        }

        return null;
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
