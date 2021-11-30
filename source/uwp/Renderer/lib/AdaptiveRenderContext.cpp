// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveRenderContext.g.cpp"
#include "InputValue.h"
#include "Util.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    AdaptiveRenderContext::AdaptiveRenderContext() :
        HostConfig{nullptr}, FeatureRegistration{nullptr}, ElementRenderers{nullptr}, ActionRenderers{nullptr},
        ResourceResolvers{nullptr}, OverrideStyles{nullptr}, ActionInvoker{nullptr}, MediaEventInvoker{nullptr},
        m_weakRenderResult{nullptr}, m_actionSentimentDefaultDictionary{nullptr}
    {
    }

    AdaptiveRenderContext::AdaptiveRenderContext(Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                                                 Rendering::Uwp::AdaptiveFeatureRegistration const& featureRegistration,
                                                 Rendering::Uwp::AdaptiveElementRendererRegistration const& elementRendererRegistration,
                                                 Rendering::Uwp::AdaptiveActionRendererRegistration const& actionRendererRegistration,
                                                 Rendering::Uwp::AdaptiveCardResourceResolvers const& resourceResolvers,
                                                 winrt::Windows::UI::Xaml::ResourceDictionary const& overrideStyles,
                                                 winrt::Windows::UI::Xaml::ResourceDictionary const& defaultActionSentimentStyles,
                                                 winrt::com_ptr<implementation::RenderedAdaptiveCard> const& renderResult) :
        HostConfig{hostConfig},
        FeatureRegistration{featureRegistration}, ElementRenderers{elementRendererRegistration},
        ActionRenderers{actionRendererRegistration}, ResourceResolvers{resourceResolvers},
        OverrideStyles{overrideStyles}, ActionInvoker{winrt::make<implementation::AdaptiveActionInvoker>(*renderResult)},
        MediaEventInvoker{winrt::make<implementation::AdaptiveMediaEventInvoker>(*renderResult)},
        m_weakRenderResult{*renderResult}, m_actionSentimentDefaultDictionary{defaultActionSentimentStyles}
    {
        if (const auto originatingCard = renderResult->OriginatingCard())
        {
            Rtl = originatingCard.Rtl();
        }
    }

    Uwp::AdaptiveInputs AdaptiveRenderContext::UserInputs() { return GetRenderResult()->UserInputs(); }

    void AdaptiveRenderContext::AddError(ObjectModel::Uwp::ErrorStatusCode statusCode, hstring const& message)
    {
        GetRenderResult()->Errors().Append({statusCode, message});
    }

    void AdaptiveRenderContext::AddWarning(ObjectModel::Uwp::WarningStatusCode statusCode, hstring const& message)
    {
        GetRenderResult()->Warnings().Append({statusCode, message});
    }

    void AdaptiveRenderContext::AddInlineShowCard(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                                                  ObjectModel::Uwp::AdaptiveShowCardAction const& showCardAction,
                                                  winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                  Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        GetRenderResult()->AddInlineShowCard(actionSet, showCardAction, showCardUIElement, renderArgs);
    }

    void AdaptiveRenderContext::AddInlineShowCard(ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
                                                  ObjectModel::Uwp::AdaptiveShowCardAction const& showCardAction,
                                                  winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                  Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        GetRenderResult()->AddInlineShowCard(adaptiveCard, showCardAction, showCardUIElement, renderArgs);
    }

    void AdaptiveRenderContext::AddOverflowButton(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        GetRenderResult()->AddOverflowButton(actionSet, actionUIElement);
    }

    void AdaptiveRenderContext::AddOverflowButton(ObjectModel::Uwp::AdaptiveCard const& actionCard,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        GetRenderResult()->AddOverflowButton(actionCard, actionUIElement);
    }

    void AdaptiveRenderContext::AddInputValue(Uwp::IAdaptiveInputValue const& inputValue, Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->AddInputValue(inputValue, renderArgs);
        }
    }

    void AdaptiveRenderContext::LinkSubmitActionToCard(ObjectModel::Uwp::IAdaptiveActionElement const& submitAction,
                                                       Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->LinkActionToCard(submitAction, renderArgs);
        }
    }

    void AdaptiveRenderContext::LinkCardToParent(ObjectModel::Uwp::AdaptiveCard const& card, Uwp::AdaptiveRenderArgs const& args)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->LinkCardToParent(card, args);
        }
    }

    Uwp::IAdaptiveInputValue AdaptiveRenderContext::GetInputValue(ObjectModel::Uwp::IAdaptiveInputElement const& inputElement)
    {
        if (auto renderResult = GetRenderResult())
        {
            return renderResult->GetInputValue(inputElement);
        }
        else
        {
            return nullptr;
        }
    }

    winrt::Windows::UI::Xaml::ResourceDictionary AdaptiveRenderContext::GetDefaultActionSentimentDictionary()
    {
        return m_actionSentimentDefaultDictionary;
    }

    winrt::com_ptr<implementation::RenderedAdaptiveCard> AdaptiveRenderContext::GetRenderResult()
    {
        return peek_innards<implementation::RenderedAdaptiveCard>(m_weakRenderResult.get());
    }
}
