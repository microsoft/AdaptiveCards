// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFeatureRegistration.h"
#include "AdaptiveRenderArgs.h"
#include "ActionHelpers.h"
#include "WholeItemsPanel.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering
{


    XamlBuilder::XamlBuilder()
    {
        m_imageLoadTracker = winrt::make_self<ImageLoadTracker>();
        m_imageLoadTracker->AddListener(dynamic_cast<IImageLoadTrackerListener*>(this));
    }

    void XamlBuilder::AllImagesLoaded()
    {
        FireAllImagesLoaded();
    }

    void XamlBuilder::ImagesLoadingHadError()
    {
        FireImagesLoadingHadError();
    }

        void XamlBuilder::DumpXamlTree(winrt::DependencyObject const& obj, int indent)
    {
        if (!obj)
        {
            return;
        }

        std::wstringstream ss;
        for (int i = 0; i < indent; ++i)
        {
            ss << L"  ";
        }

        // Get the runtime class name (e.g. "Windows.UI.Xaml.Controls.Grid")
        auto typeName = winrt::get_class_name(obj);
        ss << typeName.c_str();

        // If it's a FrameworkElement, append detailed layout properties
        if (auto fe = obj.try_as<winrt::FrameworkElement>())
        {
            auto name = fe.Name();
            if (!name.empty())
            {
                ss << L" Name=\"" << name.c_str() << L"\"";
            }
            ss << L" W=" << fe.Width() << L" H=" << fe.Height();
            ss << L" MinW=" << fe.MinWidth() << L" MinH=" << fe.MinHeight();
            ss << L" MaxW=" << fe.MaxWidth() << L" MaxH=" << fe.MaxHeight();
            ss << L" HAlign=" << static_cast<int>(fe.HorizontalAlignment());
            ss << L" VAlign=" << static_cast<int>(fe.VerticalAlignment());

            // Show margin (can cause layout issues)
            auto margin = fe.Margin();
            if (margin.Left != 0 || margin.Top != 0 || margin.Right != 0 || margin.Bottom != 0)
            {
                ss << L" Margin=" << margin.Left << L"," << margin.Top << L"," << margin.Right << L"," << margin.Bottom;
            }

            // Show padding for Controls
            if (auto control = obj.try_as<winrt::Control>())
            {
                auto padding = control.Padding();
                if (padding.Left != 0 || padding.Top != 0 || padding.Right != 0 || padding.Bottom != 0)
                {
                    ss << L" Padding=" << padding.Left << L"," << padding.Top << L"," << padding.Right << L","
                       << padding.Bottom;
                }
            }

            // Show actual size if already measured
            if (fe.ActualWidth() > 0 || fe.ActualHeight() > 0)
            {
                ss << L" ActualW=" << fe.ActualWidth() << L" ActualH=" << fe.ActualHeight();
            }
        }

        // If it's a TextBlock, append Text
        if (auto tb = obj.try_as<winrt::TextBlock>())
        {
            auto text = tb.Text();
            // Truncate long text for readability
            if (text.size() > 50)
            {
                ss << L" Text=\"" << std::wstring_view(text).substr(0, 50) << L"...\"";
            }
            else
            {
                ss << L" Text=\"" << text.c_str() << L"\"";
            }
            ss << L" TextWrapping=" << static_cast<int>(tb.TextWrapping());
        }

        // If it's a Panel, show child count and orientation for StackPanel
        if (auto panel = obj.try_as<winrt::Panel>())
        {
            ss << L" Children=" << panel.Children().Size();
        }
        if (auto sp = obj.try_as<winrt::StackPanel>())
        {
            ss << L" Orientation=" << (sp.Orientation() == winrt::Orientation::Horizontal ? L"Horizontal" : L"Vertical");
        }

        // If it's a Grid, show row/column definitions
        if (auto grid = obj.try_as<winrt::Grid>())
        {
            auto rows = grid.RowDefinitions();
            if (rows.Size() > 0)
            {
                ss << L" Rows=[";
                for (uint32_t r = 0; r < rows.Size(); ++r)
                {
                    auto rd = rows.GetAt(r);
                    auto gl = rd.Height();
                    if (r > 0)
                        ss << L",";
                    if (gl.GridUnitType == winrt::GridUnitType::Auto)
                        ss << L"Auto";
                    else if (gl.GridUnitType == winrt::GridUnitType::Star)
                        ss << gl.Value << L"*";
                    else
                        ss << gl.Value << L"px";
                }
                ss << L"]";
            }
            auto cols = grid.ColumnDefinitions();
            if (cols.Size() > 0)
            {
                ss << L" Cols=[";
                for (uint32_t c = 0; c < cols.Size(); ++c)
                {
                    auto cd = cols.GetAt(c);
                    auto gl = cd.Width();
                    if (c > 0)
                        ss << L",";
                    if (gl.GridUnitType == winrt::GridUnitType::Auto)
                        ss << L"Auto";
                    else if (gl.GridUnitType == winrt::GridUnitType::Star)
                        ss << gl.Value << L"*";
                    else
                        ss << gl.Value << L"px";
                }
                ss << L"]";
            }
        }

        // Border specifics
        if (auto border = obj.try_as<winrt::Border>())
        {
            auto padding = border.Padding();
            if (padding.Left != 0 || padding.Top != 0 || padding.Right != 0 || padding.Bottom != 0)
            {
                ss << L" Padding=" << padding.Left << L"," << padding.Top << L"," << padding.Right << L"," << padding.Bottom;
            }
        }

        // FlipView / ItemsControl specifics (key for carousel layout cycle)
        if (auto itemsControl = obj.try_as<winrt::ItemsControl>())
        {
            ss << L" Items=" << itemsControl.Items().Size();
        }

        // ScrollViewer specifics (can cause layout cycles)
        if (auto sv = obj.try_as<winrt::ScrollViewer>())
        {
            ss << L" HScroll=" << static_cast<int>(sv.HorizontalScrollBarVisibility());
            ss << L" VScroll=" << static_cast<int>(sv.VerticalScrollBarVisibility());
            ss << L" HScrollMode=" << static_cast<int>(sv.HorizontalScrollMode());
            ss << L" VScrollMode=" << static_cast<int>(sv.VerticalScrollMode());
        }

        ss << L"\n";
        OutputDebugStringW(ss.str().c_str());

        // Walk logical children
        if (auto panel = obj.try_as<winrt::Panel>())
        {
            for (auto&& child : panel.Children())
            {
                DumpXamlTree(child, indent + 1);
            }
        }
        else if (auto border = obj.try_as<winrt::Border>())
        {
            DumpXamlTree(border.Child(), indent + 1);
        }
        else if (auto contentControl = obj.try_as<winrt::ContentControl>())
        {
            if (auto content = contentControl.Content().try_as<winrt::DependencyObject>())
            {
                DumpXamlTree(content, indent + 1);
            }
        }
        // Walk FlipView/ItemsControl items (they aren't Panel children)
        else if (auto itemsControl = obj.try_as<winrt::ItemsControl>())
        {
            for (uint32_t i = 0; i < itemsControl.Items().Size(); ++i)
            {
                if (auto item = itemsControl.Items().GetAt(i).try_as<winrt::DependencyObject>())
                {
                    DumpXamlTree(item, indent + 1);
                }
            }
        }
        else if (auto sv = obj.try_as<winrt::ScrollViewer>())
        {
            if (auto content = sv.Content().try_as<winrt::DependencyObject>())
            {
                DumpXamlTree(content, indent + 1);
            }
        }
    }

    winrt::FrameworkElement XamlBuilder::BuildXamlTreeFromAdaptiveCard(winrt::AdaptiveCard const& adaptiveCard,
                                                                       winrt::AdaptiveRenderContext const& renderContext,
                                                                       XamlBuilder* xamlBuilder,
                                                                       winrt::ContainerStyle defaultContainerStyle)
    {
        try
        {
            winrt::FrameworkElement xamlTreeRoot{nullptr};

            auto hostConfig = renderContext.HostConfig();

            bool ifSupportsInteractivity = XamlHelpers::SupportsInteractivity(hostConfig);

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

            auto [bodyElementContainer, rootElement] = CreateRootCardElement(adaptiveCard, renderContext, renderArgs, xamlBuilder);

            winrt::FrameworkElement rootAsFrameworkElement = rootElement.as<winrt::FrameworkElement>();
            uint32_t cardMinHeight = adaptiveCard.MinHeight();

            if (cardMinHeight > 0)
            {
                rootAsFrameworkElement.MinHeight(cardMinHeight);
            }

            auto selectAction = adaptiveCard.SelectAction();

            // Create a new UIElement pointer to house the root element decorated with select action

            auto rootSelectActionElement =
                ActionHelpers::HandleSelectAction(nullptr, selectAction, renderContext, renderArgs, rootElement, ifSupportsInteractivity, true);

            rootAsFrameworkElement = rootSelectActionElement.as<winrt::FrameworkElement>();

            // Set automation name using speak property
            winrt::Automation::AutomationProperties::SetName(rootAsFrameworkElement, adaptiveCard.Speak());

            // Enumerate the child items of the card and build xaml for them
            auto body = adaptiveCard.Body();
            auto bodyRenderArgs =
                winrt::make<winrt::implementation::AdaptiveRenderArgs>(containerStyle, rootAsFrameworkElement, adaptiveCard, nullptr);

            BuildPanelChildren(body, bodyElementContainer, renderContext, bodyRenderArgs, [](winrt::UIElement) {});

            winrt::VerticalContentAlignment verticalContentAlignment = adaptiveCard.VerticalContentAlignment();

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
                    renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                             L"Actions collection was present in card, but interactivity is not supported");
                }
            }

            bool isInShowCard = renderArgs.IsInShowCard();

            xamlTreeRoot = rootAsFrameworkElement;

            if (!isInShowCard && xamlBuilder)
            {
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
            XamlHelpers::ErrForRenderFailed(renderContext, ex.message());
            return nullptr;
        }
    }

    void XamlBuilder::AddListener(IXamlBuilderListener* listener)
    {
        if (m_listeners.find(listener) == m_listeners.end())
        {
            m_listeners.emplace(listener);
        }
    }

    void XamlBuilder::RemoveListener(IXamlBuilderListener* listener)
    {
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

    std::pair<winrt::Panel, winrt::UIElement> XamlBuilder::CreateRootCardElement(winrt::IAdaptiveCard const& adaptiveCard,
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

            auto backgroundColor = GetBackgroundColorFromStyle(containerStyle, hostConfig);
            rootElement.Background(winrt::SolidColorBrush{backgroundColor});

            auto backgroundImage = adaptiveCard.BackgroundImage();
            bool isBackgroundImageValid = IsBackgroundImageValid(backgroundImage);

            if (isBackgroundImageValid)
            {
                XamlHelpers::ApplyBackgroundToRoot(rootElement, backgroundImage, renderContext);
            }

            auto spacingConfig = hostConfig.Spacing();
            uint32_t padding = spacingConfig.Padding();

            // Configure WholeItemsPanel to not clip bleeding containers
            winrt::implementation::WholeItemsPanel::SetBleedMargin(padding);

            auto bodyElementHostImpl = winrt::make_self<winrt::implementation::WholeItemsPanel>();
            bodyElementHostImpl->SetMainPanel(true);
            bodyElementHostImpl->SetAdaptiveHeight(true);
            winrt::WholeItemsPanel bodyElementHost = *bodyElementHostImpl;

            // Override the root styles
            if (renderArgs.IsInShowCard())
            {
                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.ShowCard.Card", bodyElementHost);
            }
            else
            {
                XamlHelpers::SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", bodyElementHost);
            }

            // If a style was not applied, add margins from the host config
            if (!bodyElementHost.Style())
            {
                XamlHelpers::ApplyMarginToXamlElement(hostConfig, bodyElementHost);
            }

            winrt::HeightType adaptiveCardHeightType = adaptiveCard.Height();

            XamlHelpers::AppendXamlElementToPanel(bodyElementHost, rootElement, adaptiveCardHeightType);
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

            if (auto const contextRtl = renderContext.Rtl())
            {
                rootElement.FlowDirection(contextRtl.Value() ? winrt::FlowDirection::RightToLeft : winrt::FlowDirection::LeftToRight);
            }

            return {bodyElementContainer, rootElement};
        }
        catch (winrt::hresult_error& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, L"RootElement (visual tree root)", ex.message());
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

    void XamlBuilder::ShouldFallback(
        winrt::IAdaptiveCardElement const& element,
        winrt::IAdaptiveElementRenderer const& elementRenderer,
        winrt::AdaptiveRenderArgs const& renderArgs,
        winrt::AdaptiveFeatureRegistration const& featureRegistration,
        boolean ancestorHasFallback)
    {
        winrt::FallbackType elementFallback = element.FallbackType();
        bool elementHasFallback = elementFallback != winrt::FallbackType::None || ancestorHasFallback;
        renderArgs.AncestorHasFallback(elementHasFallback);
        // Check to see if element's requirements are being met
        bool shouldFallback = featureRegistration && !MeetsRequirements(element, featureRegistration);
        if (!elementRenderer || shouldFallback)
        {
            throw winrt::hresult_error(E_PERFORM_FALLBACK);
        }
    }

    RenderedElementStruct XamlBuilder::RenderAsUIElement(
        winrt::IAdaptiveCardElement const& element,
        winrt::AdaptiveRenderContext const&renderContext,
        winrt::AdaptiveRenderArgs const&renderArgs,
        winrt::AdaptiveFeatureRegistration const& featureRegistration,
        bool ancestorHasFallback)
    {
        winrt::UIElement newControl{nullptr};
        winrt::IAdaptiveCardElement renderedElement{nullptr};

        try
        {
            auto elementRenderer = renderContext.ElementRenderers().Get(element.ElementTypeString());

            ShouldFallback(
                element,
                elementRenderer,
                renderArgs,
                featureRegistration,
                ancestorHasFallback);

            return {elementRenderer.Render(element, renderContext, renderArgs), element};

        }
        catch (winrt::hresult_error const& ex)
        {
            // We're only interested in fallback exception
            if (ex.code() != E_PERFORM_FALLBACK)
            {
                throw ex;
            }

            try
            {
                std::tie(newControl, renderedElement) = XamlHelpers::RenderFallback(element, renderContext, renderArgs);
            }
            catch (winrt::hresult_error const& ex)
            {
                // if we get an E_PERFORM_FALLBACK error again, we should only throw it if `ancestorHasFallBack`
                if (ex.code() != E_PERFORM_FALLBACK || (ex.code() == E_PERFORM_FALLBACK && ancestorHasFallback))
                {
                    throw ex;
                }
            }
        }

        return {};
    }

    void XamlBuilder::BuildPanelChildren(winrt::IVector<winrt::IAdaptiveCardElement> const& children,
                                         winrt::Panel parentPanel,
                                         winrt::AdaptiveRenderContext renderContext,
                                         winrt::AdaptiveRenderArgs renderArgs,
                                         std::function<void(winrt::UIElement const& child)> childCreatedCallback)
    {
        int iElement = 0;
        boolean ancestorHasFallback = renderArgs.AncestorHasFallback();
        winrt::AdaptiveFeatureRegistration featureRegistration = renderContext.FeatureRegistration();
        for (auto element : children)
        {
            auto [newControl, renderedElement] =
                RenderAsUIElement(element, renderContext, renderArgs, featureRegistration, ancestorHasFallback);

            // If we got a control, add a separator if needed and the control to the parent panel
            if (newControl)
            {
                auto hostConfig = renderContext.HostConfig();
                auto separator = XamlHelpers::AddSeparatorIfNeeded(iElement, element, hostConfig, renderContext, parentPanel);

                // If the renderedElement was an input, render the label and error message
                if (auto const inputElement = renderedElement.try_as<winrt::IAdaptiveInputElement>())
                {
                    newControl = XamlHelpers::HandleLabelAndErrorMessage(inputElement, renderContext, newControl);
                }

                XamlHelpers::AddRenderedControl(newControl, element, parentPanel, separator, nullptr, childCreatedCallback);
            }

            // Revert the ancestorHasFallback value
            renderArgs.AncestorHasFallback(ancestorHasFallback);
        }
        XamlHelpers::SetSeparatorVisibility(parentPanel);
    }
}
