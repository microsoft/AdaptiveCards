// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "XamlBuilder.h"

#include "AdaptiveFeatureRegistration.h"
#include "AdaptiveRenderArgs.h"
#include "ActionHelpers.h"
#include "XamlHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;

namespace AdaptiveNamespace
{
    XamlBuilder::XamlBuilder()
    {
        m_imageLoadTracker.AddListener(dynamic_cast<IImageLoadTrackerListener*>(this));

        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_RandomAccessStream).Get(),
                                             &m_randomAccessStreamStatics));
    }

    HRESULT XamlBuilder::AllImagesLoaded() noexcept
    try
    {
        FireAllImagesLoaded();
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT XamlBuilder::ImagesLoadingHadError() noexcept
    try
    {
        FireImagesLoadingHadError();
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT XamlBuilder::BuildXamlTreeFromAdaptiveCard(_In_ IAdaptiveCard* adaptiveCard,
                                                       _Outptr_ IFrameworkElement** xamlTreeRoot,
                                                       _In_ IAdaptiveRenderContext* renderContext,
                                                       ComPtr<XamlBuilder> xamlBuilder,
                                                       ABI::AdaptiveNamespace::ContainerStyle defaultContainerStyle) noexcept
    try
    {
        *xamlTreeRoot = nullptr;
        if (adaptiveCard != nullptr)
        {
            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
            ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
            RETURN_IF_FAILED(hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

            boolean allowCustomStyle;
            RETURN_IF_FAILED(adaptiveCardConfig->get_AllowCustomStyle(&allowCustomStyle));

            ABI::AdaptiveNamespace::ContainerStyle containerStyle = defaultContainerStyle;
            if (allowCustomStyle)
            {
                ABI::AdaptiveNamespace::ContainerStyle cardStyle;
                RETURN_IF_FAILED(adaptiveCard->get_Style(&cardStyle));

                if (cardStyle != ABI::AdaptiveNamespace::ContainerStyle::None)
                {
                    containerStyle = cardStyle;
                }
            }
            ComPtr<IAdaptiveRenderArgs> renderArgs;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&renderArgs, containerStyle, nullptr, nullptr));

            ComPtr<IPanel> bodyElementContainer;
            ComPtr<IUIElement> rootElement;
            RETURN_IF_FAILED(
                CreateRootCardElement(adaptiveCard, renderContext, renderArgs.Get(), xamlBuilder, &bodyElementContainer, &rootElement));
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            RETURN_IF_FAILED(rootElement.As(&rootAsFrameworkElement));

            UINT32 cardMinHeight{};
            RETURN_IF_FAILED(adaptiveCard->get_MinHeight(&cardMinHeight));
            if (cardMinHeight > 0)
            {
                RETURN_IF_FAILED(rootAsFrameworkElement->put_MinHeight(cardMinHeight));
            }

            ComPtr<IAdaptiveActionElement> selectAction;
            RETURN_IF_FAILED(adaptiveCard->get_SelectAction(&selectAction));

            // Create a new IUIElement pointer to house the root element decorated with select action
            ComPtr<IUIElement> rootSelectActionElement;
            ActionHelpers::HandleSelectAction(nullptr,
                                              selectAction.Get(),
                                              renderContext,
                                              rootElement.Get(),
                                              XamlHelpers::SupportsInteractivity(hostConfig.Get()),
                                              true,
                                              &rootSelectActionElement);
            RETURN_IF_FAILED(rootSelectActionElement.As(&rootAsFrameworkElement));

            // Enumerate the child items of the card and build xaml for them
            ComPtr<IVector<IAdaptiveCardElement*>> body;
            RETURN_IF_FAILED(adaptiveCard->get_Body(&body));
            ComPtr<IAdaptiveRenderArgs> bodyRenderArgs;
            RETURN_IF_FAILED(
                MakeAndInitialize<AdaptiveRenderArgs>(&bodyRenderArgs, containerStyle, rootAsFrameworkElement.Get(), nullptr));
            RETURN_IF_FAILED(
                BuildPanelChildren(body.Get(), bodyElementContainer.Get(), renderContext, bodyRenderArgs.Get(), [](IUIElement*) {}));

            ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment;
            RETURN_IF_FAILED(adaptiveCard->get_VerticalContentAlignment(&verticalContentAlignment));
            XamlHelpers::SetVerticalContentAlignmentToChildren(bodyElementContainer.Get(), verticalContentAlignment);

            ComPtr<IVector<IAdaptiveActionElement*>> actions;
            RETURN_IF_FAILED(adaptiveCard->get_Actions(&actions));
            UINT32 actionsSize;
            RETURN_IF_FAILED(actions->get_Size(&actionsSize));
            if (actionsSize > 0)
            {
                if (XamlHelpers::SupportsInteractivity(hostConfig.Get()))
                {
                    unsigned int bodyCount;
                    RETURN_IF_FAILED(body->get_Size(&bodyCount));
                    ActionHelpers::BuildActions(adaptiveCard,
                                                actions.Get(),
                                                bodyElementContainer.Get(),
                                                bodyCount > 0,
                                                renderContext,
                                                renderArgs.Get());
                }
                else
                {
                    renderContext->AddWarning(
                        ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                        HStringReference(L"Actions collection was present in card, but interactivity is not supported").Get());
                }
            }

            boolean isInShowCard;
            renderArgs->get_IsInShowCard(&isInShowCard);

            if (!isInShowCard)
            {
                RETURN_IF_FAILED(
                    XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", rootAsFrameworkElement.Get()));
            }
            else
            {
                RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                             L"Adaptive.ShowCard.Card",
                                                                             rootAsFrameworkElement.Get()));
            }

            RETURN_IF_FAILED(rootAsFrameworkElement.CopyTo(xamlTreeRoot));

            if (!isInShowCard && (xamlBuilder != nullptr))
            {
                if (xamlBuilder->m_listeners.size() == 0)
                {
                    // If we're done and no one's listening for the images to load, make sure
                    // any outstanding image loads are no longer tracked.
                    xamlBuilder->m_imageLoadTracker.AbandonOutstandingImages();
                }
                else if (xamlBuilder->m_imageLoadTracker.GetTotalImagesTracked() == 0)
                {
                    // If there are no images to track, fire the all images loaded
                    // event to signal the xaml is ready
                    xamlBuilder->FireAllImagesLoaded();
                }
            }
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT XamlBuilder::AddListener(_In_ IXamlBuilderListener* listener) noexcept
    try
    {
        if (m_listeners.find(listener) == m_listeners.end())
        {
            m_listeners.emplace(listener);
        }
        else
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT XamlBuilder::RemoveListener(_In_ IXamlBuilderListener* listener) noexcept
    try
    {
        if (m_listeners.find(listener) != m_listeners.end())
        {
            m_listeners.erase(listener);
        }
        else
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }
    CATCH_RETURN;

    void XamlBuilder::SetFixedDimensions(UINT width, UINT height) noexcept
    {
        m_fixedDimensions = true;
        m_fixedWidth = width;
        m_fixedHeight = height;
    }

    void XamlBuilder::SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept
    {
        m_enableXamlImageHandling = enableXamlImageHandling;
    }

    HRESULT XamlBuilder::CreateRootCardElement(_In_ IAdaptiveCard* adaptiveCard,
                                               _In_ IAdaptiveRenderContext* renderContext,
                                               _In_ IAdaptiveRenderArgs* renderArgs,
                                               ComPtr<XamlBuilder> xamlBuilder,
                                               _COM_Outptr_ IPanel** bodyElementContainer,
                                               _COM_Outptr_ IUIElement** rootElementResult) noexcept
    try
    {
        // The root of an adaptive card is a composite of several elements, depending on the card
        // properties.  From back to front these are:
        // Grid - Root element, used to enable children to stack above each other and size to fit
        // Image (optional) - Holds the background image if one is set
        // Shape (optional) - Provides the background image overlay, if one is set
        // StackPanel - The container for all the card's body elements
        ComPtr<IGrid> rootElement =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
        RETURN_IF_FAILED(hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

        ComPtr<IPanel> rootAsPanel;
        RETURN_IF_FAILED(rootElement.As(&rootAsPanel));
        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

        ABI::Windows::UI::Color backgroundColor;
        if (SUCCEEDED(GetBackgroundColorFromStyle(containerStyle, hostConfig.Get(), &backgroundColor)))
        {
            ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(backgroundColor);
            RETURN_IF_FAILED(rootAsPanel->put_Background(backgroundColorBrush.Get()));
        }

        ComPtr<IAdaptiveBackgroundImage> backgroundImage;
        BOOL backgroundImageIsValid;
        RETURN_IF_FAILED(adaptiveCard->get_BackgroundImage(&backgroundImage));
        RETURN_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));
        if (backgroundImageIsValid)
        {
            XamlHelpers::ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, renderArgs);
        }

        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        RETURN_IF_FAILED(spacingConfig->get_Padding(&padding));

        // Configure WholeItemsPanel to not clip bleeding containers
        WholeItemsPanel::SetBleedMargin(padding);

        // Now create the inner stack panel to serve as the root host for all the
        // body elements and apply padding from host configuration
        ComPtr<WholeItemsPanel> bodyElementHost;
        RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&bodyElementHost));
        bodyElementHost->SetMainPanel(TRUE);
        bodyElementHost->SetAdaptiveHeight(TRUE);

        ComPtr<IFrameworkElement> bodyElementHostAsElement;
        RETURN_IF_FAILED(bodyElementHost.As(&bodyElementHostAsElement));
        RETURN_IF_FAILED(XamlHelpers::ApplyMarginToXamlElement(hostConfig.Get(), bodyElementHostAsElement.Get()));

        ABI::AdaptiveNamespace::HeightType adaptiveCardHeightType;
        RETURN_IF_FAILED(adaptiveCard->get_Height(&adaptiveCardHeightType));

        XamlHelpers::AppendXamlElementToPanel(bodyElementHost.Get(), rootAsPanel.Get(), adaptiveCardHeightType);
        RETURN_IF_FAILED(bodyElementHost.CopyTo(bodyElementContainer));

        if (xamlBuilder && xamlBuilder->m_fixedDimensions)
        {
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            RETURN_IF_FAILED(rootElement.As(&rootAsFrameworkElement));
            rootAsFrameworkElement->put_Width(xamlBuilder->m_fixedWidth);
            rootAsFrameworkElement->put_Height(xamlBuilder->m_fixedHeight);
            rootAsFrameworkElement->put_MaxHeight(xamlBuilder->m_fixedHeight);
        }

        if (adaptiveCardHeightType == ABI::AdaptiveNamespace::HeightType::Stretch)
        {
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            RETURN_IF_FAILED(rootElement.As(&rootAsFrameworkElement));
            rootAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment::VerticalAlignment_Stretch);
        }

        ComPtr<IUIElement> rootUIElement;
        RETURN_IF_FAILED(rootElement.As(&rootUIElement));
        *rootElementResult = rootUIElement.Detach();
        return S_OK;
    }
    CATCH_RETURN;

    void XamlBuilder::FireAllImagesLoaded()
    {
        for (auto& listener : m_listeners)
        {
            listener->AllImagesLoaded();
        }
    }

    void XamlBuilder::FireImagesLoadingHadError()
    {
        for (auto& listener : m_listeners)
        {
            listener->ImagesLoadingHadError();
        }
    }

    HRESULT XamlBuilder::BuildPanelChildren(_In_ IVector<IAdaptiveCardElement*>* children,
                                            _In_ IPanel* parentPanel,
                                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                            std::function<void(IUIElement* child)> childCreatedCallback) noexcept
    {
        int iElement = 0;
        unsigned int childrenSize;
        RETURN_IF_FAILED(children->get_Size(&childrenSize));
        boolean ancestorHasFallback;
        RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));

        ComPtr<IAdaptiveFeatureRegistration> featureRegistration;
        RETURN_IF_FAILED(renderContext->get_FeatureRegistration(&featureRegistration));
        ComPtr<AdaptiveFeatureRegistration> featureRegistrationImpl = PeekInnards<AdaptiveFeatureRegistration>(featureRegistration);

        HRESULT hr = XamlHelpers::IterateOverVectorWithFailure<IAdaptiveCardElement>(children, ancestorHasFallback, [&](IAdaptiveCardElement* element) {
            HRESULT hr = S_OK;

            // Get fallback state
            ABI::AdaptiveNamespace::FallbackType elementFallback;
            RETURN_IF_FAILED(element->get_FallbackType(&elementFallback));
            const bool elementHasFallback = (elementFallback != FallbackType_None);
            RETURN_IF_FAILED(renderArgs->put_AncestorHasFallback(elementHasFallback || ancestorHasFallback));

            // Check to see if element's requirements are being met
            bool requirementsMet;
            RETURN_IF_FAILED(MeetsRequirements(element, featureRegistration.Get(), &requirementsMet));
            hr = requirementsMet ? S_OK : E_PERFORM_FALLBACK;

            // Get element renderer
            ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
            ComPtr<IAdaptiveElementRenderer> elementRenderer;
            HString elementType;
            RETURN_IF_FAILED(element->get_ElementTypeString(elementType.GetAddressOf()));
            RETURN_IF_FAILED(elementRenderers->Get(elementType.Get(), &elementRenderer));

            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            // If we have a renderer, render the element
            ComPtr<IUIElement> newControl;
            if (SUCCEEDED(hr) && elementRenderer != nullptr)
            {
                hr = elementRenderer->Render(element, renderContext, renderArgs, newControl.GetAddressOf());
            }

            // If we don't have a renderer, or if the renderer told us to perform fallback, try falling back
            if (elementRenderer == nullptr || hr == E_PERFORM_FALLBACK)
            {
                RETURN_IF_FAILED(XamlHelpers::RenderFallback(element, renderContext, renderArgs, &newControl));
            }

            // If we got a control, add a separator if needed and the control to the parent panel
            if (newControl != nullptr)
            {
                ComPtr<IUIElement> separator;
                XamlHelpers::AddSeparatorIfNeeded(iElement, element, hostConfig.Get(), renderContext, parentPanel, &separator);

                RETURN_IF_FAILED(XamlHelpers::AddRenderedControl(newControl.Get(), element, parentPanel, separator.Get(), nullptr, childCreatedCallback));
            }

            // Revert the ancestorHasFallback value
            renderArgs->put_AncestorHasFallback(ancestorHasFallback);
            return hr;
        });

        RETURN_IF_FAILED(XamlHelpers::SetSeparatorVisibility(parentPanel));
        return hr;
    }
}
