// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.h"
#include "AdaptiveMediaEventInvoker.h"
#include "AdaptiveRenderContext.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct DECLSPEC_UUID("F29649FF-C718-4F94-8F39-2415C86BE77E") AdaptiveRenderContext
        : AdaptiveRenderContextT<AdaptiveRenderContext, ITypePeek>
    {
        AdaptiveRenderContext();

        AdaptiveRenderContext(winrt::render_xaml::AdaptiveHostConfig const& hostConfig,
                              winrt::render_xaml::AdaptiveFeatureRegistration const& featureRegistration,
                              winrt::render_xaml::AdaptiveElementRendererRegistration const& elementRendererRegistration,
                              winrt::render_xaml::AdaptiveActionRendererRegistration const& actionRendererRegistration,
                              winrt::render_xaml::AdaptiveCardResourceResolvers const& resourceResolvers,
                              winrt::xaml::ResourceDictionary const& overrideStyles,
                              winrt::xaml::ResourceDictionary const& defaultActionSentimentStyles,
                              winrt::com_ptr<implementation::RenderedAdaptiveCard> const& renderResult);

        property<winrt::render_xaml::AdaptiveHostConfig> HostConfig;
        property<winrt::render_xaml::AdaptiveFeatureRegistration> FeatureRegistration;
        property<winrt::render_xaml::AdaptiveElementRendererRegistration> ElementRenderers;
        property<winrt::render_xaml::AdaptiveActionRendererRegistration> ActionRenderers;
        property<winrt::render_xaml::AdaptiveActionInvoker> ActionInvoker;
        property<winrt::render_xaml::AdaptiveMediaEventInvoker> MediaEventInvoker;
        property_opt<bool> Rtl;
        property_opt<winrt::TextStyle> TextStyle;
        property_opt<winrt::HAlignment> HorizontalContentAlignment;
        property<winrt::render_xaml::AdaptiveCardResourceResolvers> ResourceResolvers;
        property<winrt::xaml::ResourceDictionary> OverrideStyles;

        winrt::render_xaml::AdaptiveInputs UserInputs();

        void AddInputValue(winrt::render_xaml::IAdaptiveInputValue const& inputValue, winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);
        void LinkSubmitActionToCard(winrt::IAdaptiveActionElement const& submitAction, winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);
        void LinkCardToParent(winrt::AdaptiveCard const& card, winrt::render_xaml::AdaptiveRenderArgs const& args);

        winrt::render_xaml::IAdaptiveInputValue GetInputValue(winrt::IAdaptiveInputElement const& inputElement);

        void AddError(winrt::ErrorStatusCode statusCode, hstring const& message);
        void AddWarning(winrt::WarningStatusCode statusCode, hstring const& message);

        void AddInlineShowCard(winrt::AdaptiveActionSet const& actionSet,
                               winrt::AdaptiveShowCardAction const& showCardAction,
                               winrt::xaml::UIElement const& showCardUIElement,
                               winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

        void AddInlineShowCard(winrt::AdaptiveCard const& adaptiveCard,
                               winrt::AdaptiveShowCardAction const& showCardAction,
                               winrt::xaml::UIElement const& showCardUIElement,
                               winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

        void AddOverflowButton(winrt::AdaptiveActionSet const& actionSet, winrt::xaml::UIElement const& actionUIElement);

        void AddOverflowButton(winrt::AdaptiveCard const& actionCard, winrt::xaml::UIElement const& actionUIElement);

        winrt::com_ptr<implementation::RenderedAdaptiveCard> GetRenderResult();
        winrt::xaml::ResourceDictionary GetDefaultActionSentimentDictionary();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        winrt::weak_ref<winrt::render_xaml::RenderedAdaptiveCard> m_weakRenderResult;
        winrt::xaml::ResourceDictionary m_actionSentimentDefaultDictionary;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveRenderContext : AdaptiveRenderContextT<AdaptiveRenderContext, implementation::AdaptiveRenderContext>
    {
    };
}
