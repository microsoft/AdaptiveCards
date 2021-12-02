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

            auto& [bodyElementContainer, rootElement] =
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

    std::pair<winrt::Windows::UI::Xaml::Controls::Panel, winrt::Windows::UI::Xaml::UIElement>
    XamlBuilder::CreateRootCardElement(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard const& adaptiveCard,
                                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
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

            auto bodyElementHostImpl = winrt::make_self<WholeItemsPanelWinRT>();
            bodyElementHostImpl->SetMainPanel(true);
            bodyElementHostImpl->SetAdaptiveHeight(true);
            winrt::AdaptiveCards::Rendering::Uwp::WholeItemsPanel bodyElementHost = *bodyElementHostImpl;

            XamlHelpers::ApplyMarginToXamlElement(hostConfig, bodyElementHost);

            // TODO: why is it called height if it's height type?
            rtom::HeightType adaptiveCardHeightType = adaptiveCard.Height();

            XamlHelpers::AppendXamlElementToPanel(bodyElementHost, rootElement, adaptiveCardHeightType);
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
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement> const& children,
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
            // TODO: figure all this stuff with rendering fallback everywhere. not sure if I'm doing this correctly...
            // If we don't have a renderer, or if the renderer told us to perform fallback, try falling back
            if (elementRenderer == nullptr || shouldFallback)
            {
                // TODO: figure out if we do it right
                std::tie(newControl, renderedElement) = XamlHelpers::RenderFallback(element, renderContext, renderArgs);
            }

            // If we got a control, add a separator if needed and the control to the parent panel
            if (newControl != nullptr)
            {
                auto separator = XamlHelpers::AddSeparatorIfNeeded(iElement, element, hostConfig, renderContext, parentPanel);

                // If the renderedElement was an input, render the label and error message
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
}
