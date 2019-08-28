// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFontTypeDefinition.h"
#include "AdaptiveFontTypesDefinition.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFontTypesDefinition::RuntimeClassInitialize() noexcept try
    {
        FontTypesDefinition stylesDefinition;
        return RuntimeClassInitialize(stylesDefinition);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFontTypesDefinition::RuntimeClassInitialize(FontTypesDefinition typesDefinition) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontTypeDefinition>(m_default.GetAddressOf(), typesDefinition.defaultFontType));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontTypeDefinition>(m_monospace.GetAddressOf(), typesDefinition.monospaceFontType));

        return S_OK;
    }

    HRESULT AdaptiveFontTypesDefinition::get_Default(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontTypeDefinition** value)
    {
        return m_default.CopyTo(value);
    }

    HRESULT AdaptiveFontTypesDefinition::put_Default(_In_ ABI::AdaptiveNamespace::IAdaptiveFontTypeDefinition* value)
    {
        m_default = value;
        return S_OK;
    }

    HRESULT AdaptiveFontTypesDefinition::get_Monospace(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontTypeDefinition** value)
    {
        return m_monospace.CopyTo(value);
    }

    HRESULT AdaptiveFontTypesDefinition::put_Monospace(_In_ ABI::AdaptiveNamespace::IAdaptiveFontTypeDefinition* value)
    {
        m_monospace = value;
        return S_OK;
    }
}
