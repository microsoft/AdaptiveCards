// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTextBlock.h"
#include "Util.h"
#include "DateTimeParser.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTextBlock::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::TextBlock> textBlock = std::make_shared<AdaptiveSharedNamespace::TextBlock>();
        return RuntimeClassInitialize(textBlock);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlock::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::TextBlock>& sharedTextBlock) try
    {
        if (sharedTextBlock == nullptr)
        {
            return E_INVALIDARG;
        }

        m_wrap = sharedTextBlock->GetWrap();
        m_maxLines = sharedTextBlock->GetMaxLines();
        m_horizontalAlignment = static_cast<ABI::AdaptiveNamespace::HAlignment>(sharedTextBlock->GetHorizontalAlignment());

        InitializeTextElement(sharedTextBlock);
        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedTextBlock));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlock::get_Wrap(_Out_ boolean* wrap)
    {
        *wrap = m_wrap;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::put_Wrap(boolean wrap)
    {
        m_wrap = wrap;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::get_MaxLines(_Out_ UINT32* maxLines)
    {
        *maxLines = m_maxLines;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::put_MaxLines(UINT32 maxLines)
    {
        m_maxLines = maxLines;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::get_HorizontalAlignment(_Out_ ABI::AdaptiveNamespace::HAlignment* alignment)
    {
        *alignment = m_horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::put_HorizontalAlignment(ABI::AdaptiveNamespace::HAlignment alignment)
    {
        m_horizontalAlignment = alignment;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::TextBlock;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedTextBlock) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::TextBlock> textBlock = std::make_shared<AdaptiveSharedNamespace::TextBlock>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(textBlock)));
        RETURN_IF_FAILED(SetTextElementProperties(textBlock));

        textBlock->SetWrap(m_wrap);
        textBlock->SetMaxLines(m_maxLines);
        textBlock->SetHorizontalAlignment(static_cast<AdaptiveSharedNamespace::HorizontalAlignment>(m_horizontalAlignment));

        sharedTextBlock = textBlock;
        return S_OK;
    }
    CATCH_RETURN;
}
