// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"
#include "AdaptiveMediaEventInvoker.h"
#include "AdaptiveRenderContext.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct DECLSPEC_UUID("F29649FF-C718-4F94-8F39-2415C86BE77E") AdaptiveRenderContext
        : AdaptiveRenderContextT<AdaptiveRenderContext, ITypePeek>
    {
        AdaptiveRenderContext();

        AdaptiveRenderContext(Rendering::WinUI3::AdaptiveHostConfig const& hostConfig,
                              Rendering::WinUI3::AdaptiveFeatureRegistration const& featureRegistration,
                              Rendering::WinUI3::AdaptiveElementRendererRegistration const& elementRendererRegistration,
                              Rendering::WinUI3::AdaptiveActionRendererRegistration const& actionRendererRegistration,
                              Rendering::WinUI3::AdaptiveCardResourceResolvers const& resourceResolvers,
                              winrt::Windows::UI::Xaml::ResourceDictionary const& overrideStyles,
                              winrt::Windows::UI::Xaml::ResourceDictionary const& defaultActionSentimentStyles,
                              winrt::com_ptr<implementation::RenderedAdaptiveCard> const& renderResult);

        property<WinUI3::AdaptiveHostConfig> HostConfig;
        property<WinUI3::AdaptiveFeatureRegistration> FeatureRegistration;
        property<WinUI3::AdaptiveElementRendererRegistration> ElementRenderers;
        property<WinUI3::AdaptiveActionRendererRegistration> ActionRenderers;
        property<WinUI3::AdaptiveActionInvoker> ActionInvoker;
        property<WinUI3::AdaptiveMediaEventInvoker> MediaEventInvoker;
        property_opt<bool> Rtl;
        property_opt<ObjectModel::WinUI3::TextStyle> TextStyle;
        property_opt<ObjectModel::WinUI3::HAlignment> HorizontalContentAlignment;
        property<WinUI3::AdaptiveCardResourceResolvers> ResourceResolvers;
        property<winrt::Windows::UI::Xaml::ResourceDictionary> OverrideStyles;

        WinUI3::AdaptiveInputs UserInputs();

        void AddInputValue(WinUI3::IAdaptiveInputValue const& inputValue, WinUI3::AdaptiveRenderArgs const& renderArgs);
        void LinkSubmitActionToCard(ObjectModel::WinUI3::IAdaptiveActionElement const& submitAction,
                                    WinUI3::AdaptiveRenderArgs const& renderArgs);
        void LinkCardToParent(ObjectModel::WinUI3::AdaptiveCard const& card, WinUI3::AdaptiveRenderArgs const& args);

        WinUI3::IAdaptiveInputValue GetInputValue(ObjectModel::WinUI3::IAdaptiveInputElement const& inputElement);

        void AddError(ObjectModel::WinUI3::ErrorStatusCode statusCode, hstring const& message);
        void AddWarning(ObjectModel::WinUI3::WarningStatusCode statusCode, hstring const& message);

        void AddInlineShowCard(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                               ObjectModel::WinUI3::AdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               WinUI3::AdaptiveRenderArgs const& renderArgs);

        void AddInlineShowCard(ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                               ObjectModel::WinUI3::AdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               WinUI3::AdaptiveRenderArgs const& renderArgs);

        void AddOverflowButton(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        void AddOverflowButton(ObjectModel::WinUI3::AdaptiveCard const& actionCard,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        winrt::com_ptr<implementation::RenderedAdaptiveCard> GetRenderResult();
        winrt::Windows::UI::Xaml::ResourceDictionary GetDefaultActionSentimentDictionary();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        winrt::weak_ref<WinUI3::RenderedAdaptiveCard> m_weakRenderResult;
        winrt::Windows::UI::Xaml::ResourceDictionary m_actionSentimentDefaultDictionary;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveRenderContext : AdaptiveRenderContextT<AdaptiveRenderContext, implementation::AdaptiveRenderContext>
    {
    };
}
