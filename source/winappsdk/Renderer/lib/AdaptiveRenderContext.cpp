// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveRenderContext.g.cpp"
#include "InputValue.h"
#include "Util.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveRenderContext::AdaptiveRenderContext() :
        HostConfig{nullptr}, FeatureRegistration{nullptr}, ElementRenderers{nullptr}, ActionRenderers{nullptr},
        ResourceResolvers{nullptr}, OverrideStyles{nullptr}, ActionInvoker{nullptr}, MediaEventInvoker{nullptr},
        m_weakRenderResult{nullptr}, m_actionSentimentDefaultDictionary{nullptr}
    {
    }

    AdaptiveRenderContext::AdaptiveRenderContext(Rendering::WinUI3::AdaptiveHostConfig const& hostConfig,
                                                 Rendering::WinUI3::AdaptiveFeatureRegistration const& featureRegistration,
                                                 Rendering::WinUI3::AdaptiveElementRendererRegistration const& elementRendererRegistration,
                                                 Rendering::WinUI3::AdaptiveActionRendererRegistration const& actionRendererRegistration,
                                                 Rendering::WinUI3::AdaptiveCardResourceResolvers const& resourceResolvers,
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
    }

    WinUI3::AdaptiveInputs AdaptiveRenderContext::UserInputs() { return GetRenderResult()->UserInputs(); }

    void AdaptiveRenderContext::AddError(ObjectModel::WinUI3::ErrorStatusCode statusCode, hstring const& message)
    {
        GetRenderResult()->Errors().Append({statusCode, message});
    }

    void AdaptiveRenderContext::AddWarning(ObjectModel::WinUI3::WarningStatusCode statusCode, hstring const& message)
    {
        GetRenderResult()->Warnings().Append({statusCode, message});
    }

    void AdaptiveRenderContext::AddInlineShowCard(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                                                  ObjectModel::WinUI3::AdaptiveShowCardAction const& showCardAction,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionButtonUIElement,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionOverflowUIElement,
                                                  winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                  uint32_t primaryButtonIndex,
                                                  WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        return GetRenderResult()->AddInlineShowCard(
            actionSet, showCardAction, actionButtonUIElement, actionOverflowUIElement, showCardUIElement, primaryButtonIndex, renderArgs);
    }

    void AdaptiveRenderContext::AddInlineShowCard(ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                                                  ObjectModel::WinUI3::AdaptiveShowCardAction const& showCardAction,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionButtonUIElement,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionOverflowUIElement,
                                                  winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                  uint32_t primaryButtonIndex,
                                                  WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        GetRenderResult()->AddInlineShowCard(
            adaptiveCard, showCardAction, actionButtonUIElement, actionOverflowUIElement, showCardUIElement, primaryButtonIndex, renderArgs);
    }

    void AdaptiveRenderContext::AddOverflowButton(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        GetRenderResult()->AddOverflowButton(actionSet, actionUIElement);
    }

    void AdaptiveRenderContext::AddOverflowButton(ObjectModel::WinUI3::AdaptiveCard const& actionCard,
                                                  winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        GetRenderResult()->AddOverflowButton(actionCard, actionUIElement);
    }

    void AdaptiveRenderContext::AddInputValue(WinUI3::IAdaptiveInputValue const& inputValue, WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->AddInputValue(inputValue, renderArgs);
        }
    }

    void AdaptiveRenderContext::LinkSubmitActionToCard(ObjectModel::WinUI3::IAdaptiveActionElement const& submitAction,
                                                       WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->LinkActionToCard(submitAction, renderArgs);
        }
    }

    void AdaptiveRenderContext::LinkCardToParent(ObjectModel::WinUI3::AdaptiveCard const& card, WinUI3::AdaptiveRenderArgs const& args)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->LinkCardToParent(card, args);
        }
    }

    WinUI3::IAdaptiveInputValue AdaptiveRenderContext::GetInputValue(ObjectModel::WinUI3::IAdaptiveInputElement const& inputElement)
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
