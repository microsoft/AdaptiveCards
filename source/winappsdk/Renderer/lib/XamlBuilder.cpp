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
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;

// TODO: fix this later
using WholeItemsPanelWinRT = winrt::AdaptiveCards::Rendering::WinUI3::implementation::WholeItemsPanel;

namespace AdaptiveCards::Rendering::WinUI3
{
    XamlBuilder::XamlBuilder()
    {
        // TODO: work on this
        m_imageLoadTracker = winrt::make_self<::AdaptiveCards::Rendering::WinUI3::ImageLoadTracker>();
        m_imageLoadTracker->AddListener(dynamic_cast<IImageLoadTrackerListener*>(this));
        m_randomAccessStreamStatics = winrt::Windows::Storage::Streams::RandomAccessStream{};

        /*THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_RandomAccessStream).Get(),
                                             &m_randomAccessStreamStatics));*/
    }

    void XamlBuilder::AllImagesLoaded()
    {
        // TODO: do we need try/catch here?
        FireAllImagesLoaded();
    }

    void XamlBuilder::ImagesLoadingHadError() { FireImagesLoadingHadError(); }

    /* HRESULT XamlBuilder::AllImagesLoaded() noexcept
     try
     {
         FireAllImagesLoaded();
         return S_OK;
     }
     CATCH_RETURN();

     HRESULT XamlBuilder::ImagesLoadingHadError() noexcept
     try
     {
         FireImagesLoadingHadError();
         return S_OK;
     }
     CATCH_RETURN();*/

    rtxaml::FrameworkElement XamlBuilder::BuildXamlTreeFromAdaptiveCard(rtom::AdaptiveCard const& adaptiveCard,
                                                                        rtrender::AdaptiveRenderContext const& renderContext,
                                                                        XamlBuilder* xamlBuilder,
                                                                        rtom::ContainerStyle defaultContainerStyle)
    {
        try
        {
            rtxaml::FrameworkElement xamlTreeRoot{nullptr};

            auto hostConfig = renderContext.HostConfig();

            bool ifSupportsInteractivity = XamlHelpers::SupportsInteractivity(hostConfig);

            // TODO: why is it called adaptiveCard if it's config? :D
            auto adaptiveCardConfig = hostConfig.AdaptiveCard();

            bool allowCustomStyle = adaptiveCardConfig.AllowCustomStyle();

            auto containerStyle = defaultContainerStyle;
            if (allowCustomStyle)
            {
                auto cardStyle = adaptiveCard.Style();

                if (cardStyle != rtom::ContainerStyle::None)
                {
                    containerStyle = cardStyle;
                }
            }
            auto renderArgs =
                winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, nullptr, adaptiveCard, nullptr);

            rtxaml::Controls::Panel bodyElementContainer{nullptr};
            rtxaml::UIElement rootElement{nullptr};

            std::tie(bodyElementContainer, rootElement) =
                CreateRootCardElement(adaptiveCard, renderContext, renderArgs, xamlBuilder);

            rtxaml::FrameworkElement rootAsFrameworkElement = rootElement.as<rtxaml::FrameworkElement>();
            uint32_t cardMinHeight = adaptiveCard.MinHeight();

            if (cardMinHeight > 0)
            {
                rootAsFrameworkElement.MinHeight(cardMinHeight);
            }

            auto selectAction = adaptiveCard.SelectAction();

            // Create a new UIElement pointer to house the root element decorated with select action

            auto rootSelectActionElement =
                ActionHelpers::HandleSelectAction(nullptr, selectAction, renderContext, rootElement, ifSupportsInteractivity, true);

            rootAsFrameworkElement = rootSelectActionElement.as<rtxaml::FrameworkElement>();

            // Enumerate the child items of the card and build xaml for them
            auto body = adaptiveCard.Body();
            auto bodyRenderArgs =
                winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, rootAsFrameworkElement, adaptiveCard, nullptr);

            BuildPanelChildren(body, bodyElementContainer, renderContext, bodyRenderArgs, [](rtxaml::UIElement) {});

            rtom::VerticalContentAlignment verticalContentAlignment = adaptiveCard.VerticalContentAlignment();

            XamlHelpers::SetVerticalContentAlignmentToChildren(bodyElementContainer, verticalContentAlignment);

            auto actions = adaptiveCard.Actions();

            if (actions.Size() > 0)
            {
                if (ifSupportsInteractivity)
                {
                    ActionHelpers::BuildActions(adaptiveCard, actions, bodyElementContainer, body.Size() > 0, renderContext, renderArgs);
                }
                else
                {
                    renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                             L"Actions collection was present in card, but interactivity is not supported");
                }
            }

            bool isInShowCard = renderArgs.IsInShowCard();

            if (isInShowCard)
            {
                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ShowCard.Card", rootAsFrameworkElement);
            }
            else
            {
                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", rootAsFrameworkElement);
            }

            xamlTreeRoot = rootAsFrameworkElement;

            if (!isInShowCard && (xamlBuilder != nullptr))
            {
                // TODO: do we need to check if m_listeners is nullptr?
                if (xamlBuilder->m_listeners.size() == 0)
                {
                    // If we're done and no one's listening for the images to load, make sure
                    // any outstanding image loads are no longer tracked.
                    xamlBuilder->m_imageLoadTracker->AbandonOutstandingImages();
                }
                else if (xamlBuilder->m_imageLoadTracker->GetTotalImagesTracked() == 0)
                {
                    // If there are no images to track, fire the all images loaded
                    // event to signal the xaml is ready
                    xamlBuilder->FireAllImagesLoaded();
                }
            }
            return xamlTreeRoot;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }

    // HRESULT XamlBuilder::BuildXamlTreeFromAdaptiveCard(_In_ IAdaptiveCard* adaptiveCard,
    //                                                   _Outptr_ IFrameworkElement** xamlTreeRoot,
    //                                                   _In_ IAdaptiveRenderContext* renderContext,
    //                                                   ComPtr<XamlBuilder> xamlBuilder,
    //                                                   ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle
    //                                                   defaultContainerStyle) noexcept
    // try
    //{
    //    *xamlTreeRoot = nullptr;
    //    if (adaptiveCard != nullptr)
    //    {
    //        ComPtr<IAdaptiveHostConfig> hostConfig;
    //        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
    //        ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
    //        RETURN_IF_FAILED(hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

    //        boolean allowCustomStyle;
    //        RETURN_IF_FAILED(adaptiveCardConfig->get_AllowCustomStyle(&allowCustomStyle));

    //        rtom::ContainerStyle containerStyle = static_cast<rtom::ContainerStyle>(defaultContainerStyle);
    //        if (allowCustomStyle)
    //        {
    //            auto cardStyle = to_winrt(adaptiveCard).Style();
    //            if (cardStyle != rtom::ContainerStyle::None)
    //            {
    //                containerStyle = cardStyle;
    //            }
    //        }
    //        auto renderArgs =
    //            winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle, nullptr, to_winrt(adaptiveCard), nullptr);

    //        ComPtr<IPanel> bodyElementContainer;
    //        ComPtr<IUIElement> rootElement;
    //        /*RETURN_IF_FAILED(
    //            CreateRootCardElement(adaptiveCard, renderContext, renderArgs, xamlBuilder, &bodyElementContainer,
    //            &rootElement)); */
    //        ComPtr<IFrameworkElement> rootAsFrameworkElement;
    //        RETURN_IF_FAILED(rootElement.As(&rootAsFrameworkElement));

    //        UINT32 cardMinHeight{};
    //        RETURN_IF_FAILED(adaptiveCard->get_MinHeight(&cardMinHeight));
    //        if (cardMinHeight > 0)
    //        {
    //            RETURN_IF_FAILED(rootAsFrameworkElement->put_MinHeight(cardMinHeight));
    //        }

    //        ComPtr<IAdaptiveActionElement> selectAction;
    //        RETURN_IF_FAILED(adaptiveCard->get_SelectAction(&selectAction));

    //        // Create a new IUIElement pointer to house the root element decorated with select action
    //        ComPtr<IUIElement> rootSelectActionElement;
    //        ActionHelpers::HandleSelectAction(nullptr,
    //                                          selectAction.Get(),
    //                                          renderContext,
    //                                          rootElement.Get(),
    //                                          XamlHelpers::SupportsInteractivity(hostConfig.Get()),
    //                                          true,
    //                                          &rootSelectActionElement);
    //        RETURN_IF_FAILED(rootSelectActionElement.As(&rootAsFrameworkElement));

    //        // Enumerate the child items of the card and build xaml for them
    //        ComPtr<IVector<IAdaptiveCardElement*>> body;
    //        RETURN_IF_FAILED(adaptiveCard->get_Body(&body));
    //        auto bodyRenderArgs = winrt::make<rtrender::implementation::AdaptiveRenderArgs>(containerStyle,
    //                                                                                        rootAsFrameworkElement,
    //                                                                                        to_winrt(adaptiveCard),
    //                                                                                        nullptr);
    //        // RETURN_IF_FAILED(
    //        //    BuildPanelChildren(body.Get(), bodyElementContainer.Get(), renderContext, bodyRenderArgs.Get(), [](IUIElement*) {}));

    //        ABI::AdaptiveCards::ObjectModel::WinUI3::VerticalContentAlignment verticalContentAlignment;
    //        RETURN_IF_FAILED(adaptiveCard->get_VerticalContentAlignment(&verticalContentAlignment));
    //        XamlHelpers::SetVerticalContentAlignmentToChildren(bodyElementContainer.Get(), verticalContentAlignment);

    //        ComPtr<IVector<IAdaptiveActionElement*>> actions;
    //        RETURN_IF_FAILED(adaptiveCard->get_Actions(&actions));
    //        UINT32 actionsSize;
    //        RETURN_IF_FAILED(actions->get_Size(&actionsSize));
    //        if (actionsSize > 0)
    //        {
    //            if (XamlHelpers::SupportsInteractivity(hostConfig.Get()))
    //            {
    //                unsigned int bodyCount;
    //                RETURN_IF_FAILED(body->get_Size(&bodyCount));
    //                /*ActionHelpers::BuildActions(adaptiveCard,
    //                                            actions.Get(),
    //                                            bodyElementContainer.Get(),
    //                                            bodyCount > 0,
    //                                            renderContext,
    //                                            renderArgs);*/
    //            }
    //            else
    //            {
    //                renderContext->AddWarning(
    //                    ABI::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode::InteractivityNotSupported,
    //                    HStringReference(L"Actions collection was present in card, but interactivity is not supported").Get());
    //            }
    //        }

    //        bool isInShowCard = renderArgs.IsInShowCard();
    //        if (!isInShowCard)
    //        {
    //            RETURN_IF_FAILED(
    //                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", rootAsFrameworkElement.Get()));
    //        }
    //        else
    //        {
    //            RETURN_IF_FAILED(XamlHelpers::SetStyleFromResourceDictionary(renderContext,
    //                                                                         L"Adaptive.ShowCard.Card",
    //                                                                         rootAsFrameworkElement.Get()));
    //        }

    //        RETURN_IF_FAILED(rootAsFrameworkElement.CopyTo(xamlTreeRoot));

    //        if (!isInShowCard && (xamlBuilder != nullptr))
    //        {
    //            if (xamlBuilder->m_listeners.size() == 0)
    //            {
    //                // If we're done and no one's listening for the images to load, make sure
    //                // any outstanding image loads are no longer tracked.
    //                xamlBuilder->m_imageLoadTracker->AbandonOutstandingImages();
    //            }
    //            else if (xamlBuilder->m_imageLoadTracker->GetTotalImagesTracked() == 0)
    //            {
    //                // If there are no images to track, fire the all images loaded
    //                // event to signal the xaml is ready
    //                xamlBuilder->FireAllImagesLoaded();
    //            }
    //        }
    //    }
    //    return S_OK;
    //}
    // CATCH_RETURN();

    /* HRESULT XamlBuilder::AddListener(_In_ IXamlBuilderListener* listener) noexcept
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
     CATCH_RETURN();

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
     CATCH_RETURN();*/

    void XamlBuilder::AddListener(IXamlBuilderListener* listener)
    {
        //TODO: figure out how to do this
         if (m_listeners.find(listener) == m_listeners.end())
         {
             m_listeners.emplace(listener);
         }
    }

    void XamlBuilder::RemoveListener(IXamlBuilderListener* listener)
    {
        //TODO: figure out how to do this
        if (m_listeners.find(listener) != m_listeners.end())
        {
            m_listeners.erase(listener);
        }
    }

    void XamlBuilder::SetFixedDimensions(uint32_t width, uint32_t height) noexcept
    {
        m_fixedDimensions = true;
        m_fixedWidth = width;
        m_fixedHeight = height;
    }

    void XamlBuilder::SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept
    {
        m_enableXamlImageHandling = enableXamlImageHandling;
    }

    std::pair<winrt::Windows::UI::Xaml::Controls::Panel, winrt::Windows::UI::Xaml::UIElement>
    XamlBuilder::CreateRootCardElement(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard const& adaptiveCard,
                                       winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                                       XamlBuilder* xamlBuilder)
    {
        // The root of an adaptive card is a composite of several elements, depending on the card
        // properties.  From back to front these are:
        // Grid - Root element, used to enable children to stack above each other and size to fit
        // Image (optional) - Holds the background image if one is set
        // Shape (optional) - Provides the background image overlay, if one is set
        // StackPanel - The container for all the card's body elements
        try
        {
            rtxaml::Controls::Panel bodyElementContainer{nullptr};
            rtxaml::UIElement rootElementResult{nullptr};

            rtxaml::Controls::Grid rootElement{};

            auto hostConfig = renderContext.HostConfig();
            auto adaptiveHostConfig = hostConfig.AdaptiveCard();

            auto containerStyle = renderArgs.ContainerStyle();

            /*ABI::Windows::UI::Color backgroundColor;
            if (SUCCEEDED(GetBackgroundColorFromStyle(containerStyle, hostConfig.Get(), &backgroundColor)))
            {
                ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(backgroundColor);
                RETURN_IF_FAILED(rootAsPanel->put_Background(backgroundColorBrush.Get()));
            }*/
            // TODO: How do I check for errors here? are there gonna be any?
            auto backgroundColor = GetBackgroundColorFromStyle(containerStyle, hostConfig);
            rootElement.Background(XamlHelpers::GetSolidColorBrush(backgroundColor));

            auto backgroundImage = adaptiveCard.BackgroundImage();
            bool isBackgroundImageValid = IsBackgroundImageValid(backgroundImage);

            if (isBackgroundImageValid)
            {
                XamlHelpers::ApplyBackgroundToRoot(rootElement, backgroundImage, renderContext, renderArgs);
            }

            auto spacingConfig = hostConfig.Spacing();
            uint32_t padding = spacingConfig.Padding();

            // Configure WholeItemsPanel to not clip bleeding containers
            WholeItemsPanelWinRT::SetBleedMargin(padding);

            /* ComPtr<WholeItemsPanel> bodyElementHost;
            RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&bodyElementHost));
            bodyElementHost->SetMainPanel(TRUE);
            bodyElementHost->SetAdaptiveHeight(TRUE);*/

            auto bodyElementHostImpl = winrt::make_self<WholeItemsPanelWinRT>();
            bodyElementHostImpl->SetMainPanel(true);
            bodyElementHostImpl->SetAdaptiveHeight(true);
            winrt::AdaptiveCards::Rendering::WinUI3::WholeItemsPanel bodyElementHost = *bodyElementHostImpl;

            XamlHelpers::ApplyMarginToXamlElement(hostConfig, bodyElementHost);

            /*ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType adaptiveCardHeightType;
            RETURN_IF_FAILED(adaptiveCard->get_Height(&adaptiveCardHeightType));*/

            // TODO: why is it called height if it's height type?
            rtom::HeightType adaptiveCardHeightType = adaptiveCard.Height();

            XamlHelpers::AppendXamlElementToPanel(bodyElementHost, rootElement, adaptiveCardHeightType);
            /*RETURN_IF_FAILED(bodyElementHost.CopyTo(bodyElementContainer));*/
            // TODO: I should be able to cast here directly, right? *bodyElementHostImpl?
            bodyElementContainer = bodyElementHost;


            if (xamlBuilder && xamlBuilder->m_fixedDimensions)
            {
                rootElement.Width(xamlBuilder->m_fixedWidth);
                rootElement.Height(xamlBuilder->m_fixedHeight);
                rootElement.MaxHeight(xamlBuilder->m_fixedHeight);
            }

            if (adaptiveCardHeightType == rtom::HeightType::Stretch)
            {
                rootElement.VerticalAlignment(rtxaml::VerticalAlignment::Stretch);
            }

            // TODO: Add RTL check and add flow direction
            if (auto const contextRtl = renderContext.Rtl())
            {
                rootElement.FlowDirection(contextRtl.Value() ? rtxaml::FlowDirection::RightToLeft : rtxaml::FlowDirection::LeftToRight);
            }

            // TODO: no need to do that, remove later;
            rootElementResult = rootElement;

            return {bodyElementContainer, rootElementResult};
        }
        catch (winrt::hresult_error& ex)
        {
            // TODO: what do we do here?
            return {nullptr, nullptr};
        }
    }

    // HRESULT XamlBuilder::CreateRootCardElement(_In_ IAdaptiveCard* adaptiveCard,
    //                                           _In_ IAdaptiveRenderContext* renderContext,
    //                                           _In_ IAdaptiveRenderArgs* renderArgs,
    //                                           ComPtr<XamlBuilder> xamlBuilder,
    //                                           _COM_Outptr_ IPanel** bodyElementContainer,
    //                                           _COM_Outptr_ IUIElement** rootElementResult) noexcept
    // try
    //{
    //    // The root of an adaptive card is a composite of several elements, depending on the card
    //    // properties.  From back to front these are:
    //    // Grid - Root element, used to enable children to stack above each other and size to fit
    //    // Image (optional) - Holds the background image if one is set
    //    // Shape (optional) - Provides the background image overlay, if one is set
    //    // StackPanel - The container for all the card's body elements
    //    ComPtr<IGrid> rootElement =
    //        XamlHelpers::CreateABIClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
    //    ComPtr<IAdaptiveHostConfig> hostConfig;
    //    RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
    //    ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
    //    RETURN_IF_FAILED(hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

    //    ComPtr<IPanel> rootAsPanel;
    //    RETURN_IF_FAILED(rootElement.As(&rootAsPanel));
    //    ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;
    //    RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

    //    ABI::Windows::UI::Color backgroundColor;
    //    if (SUCCEEDED(GetBackgroundColorFromStyle(containerStyle, hostConfig.Get(), &backgroundColor)))
    //    {
    //        ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(backgroundColor);
    //        RETURN_IF_FAILED(rootAsPanel->put_Background(backgroundColorBrush.Get()));
    //    }

    //    ComPtr<IAdaptiveBackgroundImage> backgroundImage;
    //    BOOL backgroundImageIsValid;
    //    RETURN_IF_FAILED(adaptiveCard->get_BackgroundImage(&backgroundImage));
    //    RETURN_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));
    //    if (backgroundImageIsValid)
    //    {
    //        XamlHelpers::ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, renderArgs);
    //    }

    //    ComPtr<IAdaptiveSpacingConfig> spacingConfig;
    //    RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

    //    UINT32 padding;
    //    RETURN_IF_FAILED(spacingConfig->get_Padding(&padding));

    //    // Configure WholeItemsPanel to not clip bleeding containers
    //    // WholeItemsPanel::SetBleedMargin(padding);

    //    // Now create the inner stack panel to serve as the root host for all the
    //    // body elements and apply padding from host configuration
    //    ComPtr<WholeItemsPanel> bodyElementHost;
    //    RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&bodyElementHost));
    //    // bodyElementHost->SetMainPanel(TRUE);
    //    // bodyElementHost->SetAdaptiveHeight(TRUE);

    //    ComPtr<IFrameworkElement> bodyElementHostAsElement;
    //    RETURN_IF_FAILED(bodyElementHost.As(&bodyElementHostAsElement));
    //    RETURN_IF_FAILED(XamlHelpers::ApplyMarginToXamlElement(hostConfig.Get(), bodyElementHostAsElement.Get()));

    //    ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType adaptiveCardHeightType;
    //    RETURN_IF_FAILED(adaptiveCard->get_Height(&adaptiveCardHeightType));

    //    XamlHelpers::AppendXamlElementToPanel(bodyElementHost.Get(), rootAsPanel.Get(), adaptiveCardHeightType);
    //    RETURN_IF_FAILED(bodyElementHost.CopyTo(bodyElementContainer));

    //    if (xamlBuilder && xamlBuilder->m_fixedDimensions)
    //    {
    //        ComPtr<IFrameworkElement> rootAsFrameworkElement;
    //        RETURN_IF_FAILED(rootElement.As(&rootAsFrameworkElement));
    //        rootAsFrameworkElement->put_Width(xamlBuilder->m_fixedWidth);
    //        rootAsFrameworkElement->put_Height(xamlBuilder->m_fixedHeight);
    //        rootAsFrameworkElement->put_MaxHeight(xamlBuilder->m_fixedHeight);
    //    }

    //    if (adaptiveCardHeightType == ABI::AdaptiveCards::ObjectModel::WinUI3::HeightType::Stretch)
    //    {
    //        ComPtr<IFrameworkElement> rootAsFrameworkElement;
    //        RETURN_IF_FAILED(rootElement.As(&rootAsFrameworkElement));
    //        rootAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment::VerticalAlignment_Stretch);
    //    }

    //    ComPtr<IUIElement> rootUIElement;
    //    RETURN_IF_FAILED(rootElement.As(&rootUIElement));
    //    *rootElementResult = rootUIElement.Detach();
    //    return S_OK;
    //}
    // CATCH_RETURN();

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

    void XamlBuilder::BuildPanelChildren(
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> const& children,
        rtxaml::Controls::Panel parentPanel,
        rtrender::AdaptiveRenderContext renderContext,
        rtrender::AdaptiveRenderArgs renderArgs,
        std::function<void(rtxaml::UIElement child)> childCreatedCallback)
    {
        int iElement = 0;
        uint32_t childrenSize = children.Size();
        boolean ancestorHasFallback = renderArgs.AncestorHasFallback();
        rtrender::AdaptiveFeatureRegistration featureRegistration = renderContext.FeatureRegistration();
        for (auto element : children)
        {
            // Get fallback state
            rtom::FallbackType elementFallback = element.FallbackType();
            renderArgs.AncestorHasFallback(elementFallback != rtom::FallbackType::None || ancestorHasFallback);

            // Check to see if element's requirements are being met
            bool shouldFallback = !MeetsRequirements(element, featureRegistration);
            auto elementRenderers = renderContext.ElementRenderers();
            winrt::hstring elementType = element.ElementTypeString();
            auto elementRenderer = elementRenderers.Get(elementType);
            auto hostConfig = renderContext.HostConfig();

            rtxaml::UIElement newControl{nullptr};
            rtom::IAdaptiveCardElement renderedElement;
            if (!shouldFallback && elementRenderer != nullptr)
            {
                newControl = elementRenderer.Render(element, renderContext, renderArgs);
                renderedElement = element;
            }

            // If we don't have a renderer, or if the renderer told us to perform fallback, try falling back
            if (elementRenderer == nullptr || shouldFallback)
            {
                // TODO: figure out if we do it right
                std::tie(newControl, renderedElement) = XamlHelpers::RenderFallback(element, renderContext, renderArgs);
            }

            // If we got a control, add a separator if needed and the control to the parent panel
            if (newControl != nullptr)
            {
                /*  ComPtr<IUIElement> separator;*/
                auto separator = XamlHelpers::AddSeparatorIfNeeded(iElement, element, hostConfig, renderContext, parentPanel);

                // If the renderedElement was an input, render the label and error message
                /* ComPtr<IAdaptiveInputElement> inputElement;
                 if (SUCCEEDED(renderedElement.As(&inputElement)))
                 {
                     XamlHelpers::HandleLabelAndErrorMessage(inputElement.Get(), renderContext, renderArgs, newControl.GetAddressOf());
                 }*/
                if (auto const inputElement = renderedElement.try_as<rtom::IAdaptiveInputElement>())
                {
                    newControl = XamlHelpers::HandleLabelAndErrorMessage(inputElement, renderContext, renderArgs, newControl);
                }

                XamlHelpers::AddRenderedControl(newControl, element, parentPanel, separator, nullptr, childCreatedCallback);
            }

            // Revert the ancestorHasFallback value
            renderArgs.AncestorHasFallback(ancestorHasFallback);
        }
        XamlHelpers::SetSeparatorVisibility(parentPanel);
    }

    //    HRESULT XamlBuilder::BuildPanelChildren(_In_ IVector<IAdaptiveCardElement*>* children,
    //                                            _In_ IPanel* parentPanel,
    //                                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
    //                                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
    //                                            std::function<void(IUIElement* child)> childCreatedCallback) noexcept
    //    {
    //        int iElement = 0;
    //        unsigned int childrenSize;
    //        RETURN_IF_FAILED(children->get_Size(&childrenSize));
    //        boolean ancestorHasFallback;
    //        RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));
    //
    //        ComPtr<IAdaptiveFeatureRegistration> featureRegistration;
    //        RETURN_IF_FAILED(renderContext->get_FeatureRegistration(&featureRegistration));
    //
    //        HRESULT hr = IterateOverVectorWithFailure<IAdaptiveCardElement>(
    //            children,
    //            ancestorHasFallback,
    //            [&](IAdaptiveCardElement* element)
    //            {
    //                HRESULT hr = S_OK;
    //
    //                // Get fallback state
    //                ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType elementFallback;
    //                RETURN_IF_FAILED(element->get_FallbackType(&elementFallback));
    //                const bool elementHasFallback = (elementFallback != FallbackType_None);
    //                RETURN_IF_FAILED(renderArgs->put_AncestorHasFallback(elementHasFallback || ancestorHasFallback));
    //
    //                // Check to see if element's requirements are being met
    //                bool requirementsMet;
    //                RETURN_IF_FAILED(MeetsRequirements(element, featureRegistration.Get(), &requirementsMet));
    //                hr = requirementsMet ? S_OK : E_PERFORM_FALLBACK;
    //
    //                // Get element renderer
    //                ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
    //                RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
    //                ComPtr<IAdaptiveElementRenderer> elementRenderer;
    //                HString elementType;
    //                RETURN_IF_FAILED(element->get_ElementTypeString(elementType.GetAddressOf()));
    //                RETURN_IF_FAILED(elementRenderers->Get(elementType.Get(), &elementRenderer));
    //
    //                ComPtr<IAdaptiveHostConfig> hostConfig;
    //                RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
    //
    //                // If we have a renderer, render the element
    //                ComPtr<IUIElement> newControl;
    //                ComPtr<IAdaptiveCardElement> renderedElement;
    //                if (SUCCEEDED(hr) && elementRenderer != nullptr)
    //                {
    //                    hr = elementRenderer->Render(element, renderContext, renderArgs, newControl.GetAddressOf());
    //                    renderedElement = element;
    //                }
    //
    //                // If we don't have a renderer, or if the renderer told us to perform fallback, try falling back
    //                if (elementRenderer == nullptr || hr == E_PERFORM_FALLBACK)
    //                {
    //                    RETURN_IF_FAILED(XamlHelpers::RenderFallback(element, renderContext, renderArgs, &newControl, &renderedElement));
    //                }
    //
    //                // If we got a control, add a separator if needed and the control to the parent panel
    //                if (newControl != nullptr)
    //                {
    //                    ComPtr<IUIElement> separator;
    //                    XamlHelpers::AddSeparatorIfNeeded(iElement, element, hostConfig.Get(), renderContext, parentPanel, &separator);
    //
    //                    // If the renderedElement was an input, render the label and error message
    //                    ComPtr<IAdaptiveInputElement> inputElement;
    //                    if (SUCCEEDED(renderedElement.As(&inputElement)))
    //                    {
    //                        XamlHelpers::HandleLabelAndErrorMessage(inputElement.Get(),
    //                                                                renderContext,
    //                                                                renderArgs,
    //                                                                newControl.GetAddressOf());
    //                    }
    //
    //                    RETURN_IF_FAILED(
    //                        XamlHelpers::AddRenderedControl(newControl.Get(), element, parentPanel, separator.Get(), nullptr, childCreatedCallback));
    //                }
    //
    //                // Revert the ancestorHasFallback value
    //                renderArgs->put_AncestorHasFallback(ancestorHasFallback);
    //                return hr;
    //            });
    //
    //        RETURN_IF_FAILED(XamlHelpers::SetSeparatorVisibility(parentPanel));
    //        return hr;
    //    }
    //}
}
