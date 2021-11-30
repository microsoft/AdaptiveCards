// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"
#include "AdaptiveMediaEventInvoker.h"
#include "AdaptiveRenderContext.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct DECLSPEC_UUID("F29649FF-C718-4F94-8F39-2415C86BE77E") AdaptiveRenderContext
        : AdaptiveRenderContextT<AdaptiveRenderContext, ITypePeek>
    {
        AdaptiveRenderContext();

        AdaptiveRenderContext(Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                              Rendering::Uwp::AdaptiveFeatureRegistration const& featureRegistration,
                              Rendering::Uwp::AdaptiveElementRendererRegistration const& elementRendererRegistration,
                              Rendering::Uwp::AdaptiveActionRendererRegistration const& actionRendererRegistration,
                              Rendering::Uwp::AdaptiveCardResourceResolvers const& resourceResolvers,
                              winrt::Windows::UI::Xaml::ResourceDictionary const& overrideStyles,
                              winrt::Windows::UI::Xaml::ResourceDictionary const& defaultActionSentimentStyles,
                              winrt::com_ptr<implementation::RenderedAdaptiveCard> const& renderResult);

        property<Uwp::AdaptiveHostConfig> HostConfig;
        property<Uwp::AdaptiveFeatureRegistration> FeatureRegistration;
        property<Uwp::AdaptiveElementRendererRegistration> ElementRenderers;
        property<Uwp::AdaptiveActionRendererRegistration> ActionRenderers;
        property<Uwp::AdaptiveActionInvoker> ActionInvoker;
        property<Uwp::AdaptiveMediaEventInvoker> MediaEventInvoker;
        property_opt<bool> Rtl;
        property_opt<ObjectModel::Uwp::TextStyle> TextStyle;
        property_opt<ObjectModel::Uwp::HAlignment> HorizontalContentAlignment;
        property<Uwp::AdaptiveCardResourceResolvers> ResourceResolvers;
        property<winrt::Windows::UI::Xaml::ResourceDictionary> OverrideStyles;

        Uwp::AdaptiveInputs UserInputs();

        void AddInputValue(Uwp::IAdaptiveInputValue const& inputValue, Uwp::AdaptiveRenderArgs const& renderArgs);
        void LinkSubmitActionToCard(ObjectModel::Uwp::IAdaptiveActionElement const& submitAction,
                                    Uwp::AdaptiveRenderArgs const& renderArgs);
        void LinkCardToParent(ObjectModel::Uwp::AdaptiveCard const& card, Uwp::AdaptiveRenderArgs const& args);

        Uwp::IAdaptiveInputValue GetInputValue(ObjectModel::Uwp::IAdaptiveInputElement const& inputElement);

        void AddError(ObjectModel::Uwp::ErrorStatusCode statusCode, hstring const& message);
        void AddWarning(ObjectModel::Uwp::WarningStatusCode statusCode, hstring const& message);

        void AddInlineShowCard(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                               ObjectModel::Uwp::AdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               Uwp::AdaptiveRenderArgs const& renderArgs);

        void AddInlineShowCard(ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
                               ObjectModel::Uwp::AdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               Uwp::AdaptiveRenderArgs const& renderArgs);

        void AddOverflowButton(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        void AddOverflowButton(ObjectModel::Uwp::AdaptiveCard const& actionCard,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        winrt::com_ptr<implementation::RenderedAdaptiveCard> GetRenderResult();
        winrt::Windows::UI::Xaml::ResourceDictionary GetDefaultActionSentimentDictionary();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        winrt::weak_ref<Uwp::RenderedAdaptiveCard> m_weakRenderResult;
        winrt::Windows::UI::Xaml::ResourceDictionary m_actionSentimentDefaultDictionary;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveRenderContext : AdaptiveRenderContextT<AdaptiveRenderContext, implementation::AdaptiveRenderContext>
    {
    };
}
