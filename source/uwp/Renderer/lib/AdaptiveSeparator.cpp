// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSeparator.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveSeparator::RuntimeClassInitialize() noexcept
    try
    {
        m_sharedSeparator = std::make_shared<Separator>();
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveSeparator::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Separator>& sharedSeparator)
    {
        m_sharedSeparator = sharedSeparator;
        return S_OK;
    }

    HRESULT AdaptiveSeparator::get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* color)
    {
        *color = static_cast<ABI::AdaptiveNamespace::ForegroundColor>(m_sharedSeparator->GetColor());
        return S_OK;
    }

    HRESULT AdaptiveSeparator::put_Color(ABI::AdaptiveNamespace::ForegroundColor color)
    {
        m_sharedSeparator->SetColor(static_cast<AdaptiveSharedNamespace::ForegroundColor>(color));
        return S_OK;
    }

    HRESULT AdaptiveSeparator::get_Thickness(_Out_ ABI::AdaptiveNamespace::SeparatorThickness* thickness)
    {
        *thickness = static_cast<ABI::AdaptiveNamespace::SeparatorThickness>(m_sharedSeparator->GetThickness());
        return S_OK;
    }

    HRESULT AdaptiveSeparator::put_Thickness(ABI::AdaptiveNamespace::SeparatorThickness thickness)
    {
        m_sharedSeparator->SetThickness(static_cast<AdaptiveSharedNamespace::SeparatorThickness>(thickness));
        return S_OK;
    }
}
