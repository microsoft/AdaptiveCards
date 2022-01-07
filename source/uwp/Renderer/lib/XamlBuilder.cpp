// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "XamlBuilder.h"

#include "AdaptiveFeatureRegistration.h"
#include "AdaptiveRenderArgs.h"
#include "ActionHelpers.h"
#include "XamlHelpers.h"

// TODO: fix this later
using WholeItemsPanelWinRT = winrt::AdaptiveCards::Rendering::Uwp::implementation::WholeItemsPanel;

namespace AdaptiveCards::Rendering::Uwp
{
    XamlBuilder::XamlBuilder()
    {
        // TODO: work on this
        m_imageLoadTracker = winrt::make_self<::AdaptiveCards::Rendering::Uwp::ImageLoadTracker>();
        m_imageLoadTracker->AddListener(dynamic_cast<IImageLoadTrackerListener*>(this));
    }

    void XamlBuilder::AllImagesLoaded()
    {
        // TODO: do we need try/catch here?
        FireAllImagesLoaded();
    }

    void XamlBuilder::ImagesLoadingHadError() { FireImagesLoadingHadError(); }

    winrt::FrameworkElement XamlBuilder::BuildXamlTreeFromAdaptiveCard(winrt::AdaptiveCard const& adaptiveCard,
                                                                       winrt::AdaptiveRenderContext const& renderContext,
                                                                       XamlBuilder* xamlBuilder,
                                                                       winrt::ContainerStyle defaultContainerStyle)
    {
        try
        {
            winrt::FrameworkElement xamlTreeRoot{nullptr};

            auto hostConfig = renderContext.HostConfig();

            bool ifSupportsInteractivity = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig);

            // TODO: why is it called adaptiveCard if it's config? :D
            auto adaptiveCardConfig = hostConfig.AdaptiveCard();

            bool allowCustomStyle = adaptiveCardConfig.AllowCustomStyle();

            auto containerStyle = defaultContainerStyle;
            if (allowCustomStyle)
            {
                auto cardStyle = adaptiveCard.Style();

                if (cardStyle != winrt::ContainerStyle::None)
                {
                    containerStyle = cardStyle;
                }
            }
            auto renderArgs =
                winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, nullptr, adaptiveCard, nullptr);

            auto& [bodyElementContainer, rootElement] = CreateRootCardElement(adaptiveCard, renderContext, renderArgs, xamlBuilder);

            winrt::FrameworkElement rootAsFrameworkElement = rootElement.as<winrt::FrameworkElement>();
            uint32_t cardMinHeight = adaptiveCard.MinHeight();

            if (cardMinHeight > 0)
            {
                rootAsFrameworkElement.MinHeight(cardMinHeight);
            }

            auto selectAction = adaptiveCard.SelectAction();

            // Create a new UIElement pointer to house the root element decorated with select action

            auto rootSelectActionElement =
                ActionHelpers::HandleSelectAction(nullptr, selectAction, renderContext, rootElement, ifSupportsInteractivity, true);

            rootAsFrameworkElement = rootSelectActionElement.as<winrt::FrameworkElement>();

            // Enumerate the child items of the card and build xaml for them
            auto body = adaptiveCard.Body();
            auto bodyRenderArgs =
                winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, rootAsFrameworkElement, adaptiveCard, nullptr);

            BuildPanelChildren(body, bodyElementContainer, renderContext, bodyRenderArgs, [](winrt::UIElement) {});

            winrt::VerticalContentAlignment verticalContentAlignment = adaptiveCard.VerticalContentAlignment();

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetVerticalContentAlignmentToChildren(bodyElementContainer,
                                                                                                verticalContentAlignment);

            auto actions = adaptiveCard.Actions();

            if (actions.Size() > 0)
            {
                if (ifSupportsInteractivity)
                {
                    ActionHelpers::BuildActions(adaptiveCard, actions, bodyElementContainer, body.Size() > 0, renderContext, renderArgs);
                }
                else
                {
                    renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                             L"Actions collection was present in card, but interactivity is not supported");
                }
            }

            bool isInShowCard = renderArgs.IsInShowCard();

            if (isInShowCard)
            {
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext,
                                                                                             L"Adaptive.ShowCard.Card",
                                                                                             rootAsFrameworkElement);
            }
            else
            {
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", rootAsFrameworkElement);
            }

            xamlTreeRoot = rootAsFrameworkElement;

            if (!isInShowCard && xamlBuilder)
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

    void XamlBuilder::AddListener(IXamlBuilderListener* listener)
    {
        // TODO: figure out how to do this properly
        if (m_listeners.find(listener) == m_listeners.end())
        {
            m_listeners.emplace(listener);
        }
    }

    void XamlBuilder::RemoveListener(IXamlBuilderListener* listener)
    {
        // TODO: figure out how to do this properly
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

    std::pair<winrt::Panel, winrt::Windows::UI::Xaml::UIElement>
    XamlBuilder::CreateRootCardElement(winrt::IAdaptiveCard const& adaptiveCard,
                                       winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveRenderArgs const& renderArgs,
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
            winrt::Panel bodyElementContainer{nullptr};
            winrt::UIElement rootElementResult{nullptr};

            winrt::Grid rootElement{};

            auto hostConfig = renderContext.HostConfig();
            auto adaptiveHostConfig = hostConfig.AdaptiveCard();

            auto containerStyle = renderArgs.ContainerStyle();

            // TODO: How do I check for errors here? are there gonna be any?
            auto backgroundColor = GetBackgroundColorFromStyle(containerStyle, hostConfig);
            rootElement.Background(::AdaptiveCards::Rendering::Uwp::XamlHelpers::GetSolidColorBrush(backgroundColor));

            auto backgroundImage = adaptiveCard.BackgroundImage();
            bool isBackgroundImageValid = IsBackgroundImageValid(backgroundImage);

            if (isBackgroundImageValid)
            {
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::ApplyBackgroundToRoot(rootElement, backgroundImage, renderContext);
            }

            auto spacingConfig = hostConfig.Spacing();
            uint32_t padding = spacingConfig.Padding();

            // Configure WholeItemsPanel to not clip bleeding containers
            WholeItemsPanelWinRT::SetBleedMargin(padding);

            auto bodyElementHostImpl = winrt::make_self<WholeItemsPanelWinRT>();
            bodyElementHostImpl->SetMainPanel(true);
            bodyElementHostImpl->SetAdaptiveHeight(true);
            winrt::WholeItemsPanel bodyElementHost = *bodyElementHostImpl;

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::ApplyMarginToXamlElement(hostConfig, bodyElementHost);

            // TODO: why is it called height if it's height type?
            winrt::HeightType adaptiveCardHeightType = adaptiveCard.Height();

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(bodyElementHost, rootElement, adaptiveCardHeightType);
            // TODO: I should be able to cast here directly, right? *bodyElementHostImpl?
            bodyElementContainer = bodyElementHost;

            if (xamlBuilder && xamlBuilder->m_fixedDimensions)
            {
                rootElement.Width(xamlBuilder->m_fixedWidth);
                rootElement.Height(xamlBuilder->m_fixedHeight);
                rootElement.MaxHeight(xamlBuilder->m_fixedHeight);
            }

            if (adaptiveCardHeightType == winrt::HeightType::Stretch)
            {
                rootElement.VerticalAlignment(winrt::VerticalAlignment::Stretch);
            }

            // TODO: Add RTL check and add flow direction
            if (auto const contextRtl = renderContext.Rtl())
            {
                rootElement.FlowDirection(contextRtl.Value() ? winrt::FlowDirection::RightToLeft : winrt::FlowDirection::LeftToRight);
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

    void XamlBuilder::BuildPanelChildren(winrt::IVector<winrt::IAdaptiveCardElement> const& children,
                                         winrt::Panel parentPanel,
                                         winrt::AdaptiveRenderContext renderContext,
                                         winrt::AdaptiveRenderArgs renderArgs,
                                         std::function<void(winrt::UIElement const& child)> childCreatedCallback)
    {
        int iElement = 0;
        uint32_t childrenSize = children.Size();
        boolean ancestorHasFallback = renderArgs.AncestorHasFallback();
        winrt::AdaptiveFeatureRegistration featureRegistration = renderContext.FeatureRegistration();
        for (auto element : children)
        {
            // Get fallback state
            winrt::FallbackType elementFallback = element.FallbackType();
            renderArgs.AncestorHasFallback(elementFallback != winrt::FallbackType::None || ancestorHasFallback);

            // Check to see if element's requirements are being met
            bool shouldFallback = !MeetsRequirements(element, featureRegistration);
            auto elementRenderers = renderContext.ElementRenderers();
            winrt::hstring elementType = element.ElementTypeString();
            auto elementRenderer = elementRenderers.Get(elementType);
            auto hostConfig = renderContext.HostConfig();

            winrt::UIElement newControl{nullptr};
            winrt::IAdaptiveCardElement renderedElement;
            if (!shouldFallback && elementRenderer)
            {
                newControl = elementRenderer.Render(element, renderContext, renderArgs);
                renderedElement = element;
            }
            // TODO: figure all this stuff with rendering fallback everywhere. not sure if I'm doing this correctly...
            // If we don't have a renderer, or if the renderer told us to perform fallback, try falling back
            if (elementRenderer == nullptr || shouldFallback)
            {
                // TODO: figure out if we do it right
                std::tie(newControl, renderedElement) =
                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::RenderFallback(element, renderContext, renderArgs);
            }

            // If we got a control, add a separator if needed and the control to the parent panel
            if (newControl)
            {
                auto separator =
                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AddSeparatorIfNeeded(iElement, element, hostConfig, renderContext, parentPanel);

                // If the renderedElement was an input, render the label and error message
                if (auto const inputElement = renderedElement.try_as<winrt::IAdaptiveInputElement>())
                {
                    newControl = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleLabelAndErrorMessage(inputElement,
                                                                                                          renderContext,
                                                                                                          renderArgs,
                                                                                                          newControl);
                }

                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AddRenderedControl(newControl, element, parentPanel, separator, nullptr, childCreatedCallback);
            }

            // Revert the ancestorHasFallback value
            renderArgs.AncestorHasFallback(ancestorHasFallback);
        }
        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetSeparatorVisibility(parentPanel);
    }
}
