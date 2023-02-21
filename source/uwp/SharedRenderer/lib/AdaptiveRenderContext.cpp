// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRenderContext.h"
#include "AdaptiveRenderContext.g.cpp"
#include "InputValue.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    AdaptiveRenderContext::AdaptiveRenderContext() :
        HostConfig{nullptr}, FeatureRegistration{nullptr}, ElementRenderers{nullptr}, ActionRenderers{nullptr},
        ResourceResolvers{nullptr}, OverrideStyles{nullptr}, ActionInvoker{nullptr}, MediaEventInvoker{nullptr},
        m_weakRenderResult{nullptr}, m_actionSentimentDefaultDictionary{nullptr}
    {
    }

    AdaptiveRenderContext::AdaptiveRenderContext(winrt::AdaptiveHostConfig const& hostConfig,
                                                 winrt::AdaptiveFeatureRegistration const& featureRegistration,
                                                 winrt::AdaptiveElementRendererRegistration const& elementRendererRegistration,
                                                 winrt::AdaptiveActionRendererRegistration const& actionRendererRegistration,
                                                 winrt::AdaptiveCardResourceResolvers const& resourceResolvers,
                                                 winrt::ResourceDictionary const& overrideStyles,
                                                 winrt::ResourceDictionary const& defaultActionSentimentStyles,
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

    winrt::AdaptiveInputs AdaptiveRenderContext::UserInputs()
    {
        return GetRenderResult()->UserInputs();
    }

    void AdaptiveRenderContext::AddError(winrt::ErrorStatusCode statusCode, hstring const& message)
    {
        GetRenderResult()->Errors().Append({statusCode, message});
    }

    void AdaptiveRenderContext::AddWarning(winrt::WarningStatusCode statusCode, hstring const& message)
    {
        GetRenderResult()->Warnings().Append({statusCode, message});
    }

    void AdaptiveRenderContext::AddInlineShowCard(winrt::AdaptiveActionSet const& actionSet,
                                                  winrt::AdaptiveShowCardAction const& showCardAction,
                                                  winrt::UIElement const& showCardUIElement,
                                                  winrt::AdaptiveRenderArgs const& renderArgs)
    {
        GetRenderResult()->AddInlineShowCard(actionSet, showCardAction, showCardUIElement, renderArgs);
    }

    void AdaptiveRenderContext::AddInlineShowCard(winrt::AdaptiveCard const& adaptiveCard,
                                                  winrt::AdaptiveShowCardAction const& showCardAction,
                                                  winrt::UIElement const& showCardUIElement,
                                                  winrt::AdaptiveRenderArgs const& renderArgs)
    {
        GetRenderResult()->AddInlineShowCard(adaptiveCard, showCardAction, showCardUIElement, renderArgs);
    }

    void AdaptiveRenderContext::AddOverflowButton(winrt::AdaptiveActionSet const& actionSet, winrt::UIElement const& actionUIElement)
    {
        GetRenderResult()->AddOverflowButton(actionSet, actionUIElement);
    }

    void AdaptiveRenderContext::AddOverflowButton(winrt::AdaptiveCard const& actionCard, winrt::UIElement const& actionUIElement)
    {
        GetRenderResult()->AddOverflowButton(actionCard, actionUIElement);
    }

    void AdaptiveRenderContext::AddInputValue(winrt::IAdaptiveInputValue const& inputValue, winrt::AdaptiveRenderArgs const& renderArgs)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->AddInputValue(inputValue, renderArgs);
        }
    }

    void AdaptiveRenderContext::LinkSubmitActionToCard(winrt::IAdaptiveActionElement const& submitAction,
                                                       winrt::AdaptiveRenderArgs const& renderArgs)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->LinkActionToCard(submitAction, renderArgs);
        }
    }

    void AdaptiveRenderContext::LinkCardToParent(winrt::AdaptiveCard const& card, winrt::AdaptiveRenderArgs const& args)
    {
        if (auto renderResult = GetRenderResult())
        {
            renderResult->LinkCardToParent(card, args);
        }
    }

    winrt::IAdaptiveInputValue AdaptiveRenderContext::GetInputValue(winrt::IAdaptiveInputElement const& inputElement)
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

    winrt::ResourceDictionary AdaptiveRenderContext::GetDefaultActionSentimentDictionary()
    {
        return m_actionSentimentDefaultDictionary;
    }

    winrt::com_ptr<implementation::RenderedAdaptiveCard> AdaptiveRenderContext::GetRenderResult()
    {
        if (const auto renderResult = peek_innards<implementation::RenderedAdaptiveCard>(m_weakRenderResult.get()))
        {
            return renderResult;
        }

        throw winrt::hresult_invalid_argument(
            L"RenderResult could not be resolved. Most likely, the object is no longer alive because all the references were destroyed.");
    }
}
