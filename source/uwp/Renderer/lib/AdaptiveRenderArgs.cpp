// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRenderArgs.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveRenderArgs::RuntimeClassInitialize() noexcept { return S_OK; }

    // This constructor is kept so all elements keep working as expected
    HRESULT AdaptiveRenderArgs::RuntimeClassInitialize(ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                                       _In_opt_ IInspectable* parentElement,
                                                       _In_opt_ IAdaptiveRenderArgs* renderArgs) noexcept
    try
    {
        m_containerStyle = containerStyle;
        m_parentElement = parentElement;

        if (renderArgs)
        {
            RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&m_ancestorHasFallback));
            RETURN_IF_FAILED(renderArgs->get_ParentCard(&m_parentCard));
        }

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRenderArgs::RuntimeClassInitialize(ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                                       _In_opt_ IInspectable* parentElement,
                                                       _In_ ABI::AdaptiveNamespace::IAdaptiveCard* parentCard,
                                                       _In_opt_ IAdaptiveRenderArgs* renderArgs) noexcept
    try
    {
        m_containerStyle = containerStyle;
        m_parentElement = parentElement;
        m_parentCard = parentCard;

        if (renderArgs)
        {
            RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&m_ancestorHasFallback));
        }

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRenderArgs::get_ContainerStyle(_Out_ ABI::AdaptiveNamespace::ContainerStyle* value)
    {
        *value = m_containerStyle;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::put_ContainerStyle(ABI::AdaptiveNamespace::ContainerStyle value)
    {
        m_containerStyle = value;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::get_ParentElement(_COM_Outptr_ IInspectable** value)
    {
        return m_parentElement.CopyTo(value);
    }

    HRESULT AdaptiveRenderArgs::put_ParentElement(_In_ IInspectable* value)
    {
        m_parentElement = value;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::get_IsInShowCard(_Out_ boolean* isInShowCard)
    {
        *isInShowCard = m_isInShowCard;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::put_IsInShowCard(boolean isInShowCard)
    {
        m_isInShowCard = isInShowCard;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::get_AllowAboveTitleIconPlacement(_Out_ boolean* value)
    {
        *value = m_allowAboveTitleIconPlacement;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::put_AllowAboveTitleIconPlacement(boolean value)
    {
        m_allowAboveTitleIconPlacement = value;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::get_AncestorHasFallback(_Out_ boolean* hasFallback)
    {
        *hasFallback = m_ancestorHasFallback;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::put_AncestorHasFallback(boolean hasFallback)
    {
        m_ancestorHasFallback = hasFallback;
        return S_OK;
    }

    HRESULT AdaptiveRenderArgs::get_ParentCard(_COM_Outptr_ IAdaptiveCard** value)
    {
        return m_parentCard.CopyTo(value);
    }

    HRESULT AdaptiveRenderArgs::put_ParentCard(_In_ IAdaptiveCard* value)
    {
        m_parentCard = value;
        return S_OK;
    }
}
