// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlock.h"
#include "DateTimeParser.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveTextBlock::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::TextBlock> textBlock = std::make_shared<AdaptiveCards::TextBlock>();
        return RuntimeClassInitialize(textBlock);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextBlock::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TextBlock>& sharedTextBlock)
    try
    {
        if (sharedTextBlock == nullptr)
        {
            return E_INVALIDARG;
        }

        m_wrap = sharedTextBlock->GetWrap();
        m_maxLines = sharedTextBlock->GetMaxLines();
        m_horizontalAlignment =
            static_cast<ABI::AdaptiveCards::Rendering::Uwp::HAlignment>(sharedTextBlock->GetHorizontalAlignment());
        m_style = static_cast<ABI::AdaptiveCards::Rendering::Uwp::TextStyle>(sharedTextBlock->GetStyle());

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

    HRESULT AdaptiveTextBlock::get_HorizontalAlignment(_Out_ ABI::AdaptiveCards::Rendering::Uwp::HAlignment* alignment)
    {
        *alignment = m_horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::put_HorizontalAlignment(ABI::AdaptiveCards::Rendering::Uwp::HAlignment alignment)
    {
        m_horizontalAlignment = alignment;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::get_Style(_Out_ ABI::AdaptiveCards::Rendering::Uwp::TextStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::put_Style(ABI::AdaptiveCards::Rendering::Uwp::TextStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::TextBlock;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedTextBlock)
    try
    {
        std::shared_ptr<AdaptiveCards::TextBlock> textBlock = std::make_shared<AdaptiveCards::TextBlock>();

        RETURN_IF_FAILED(CopySharedElementProperties(*textBlock));
        RETURN_IF_FAILED(CopyTextElementProperties(*textBlock));

        textBlock->SetWrap(m_wrap);
        textBlock->SetMaxLines(m_maxLines);
        textBlock->SetHorizontalAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(m_horizontalAlignment));
        textBlock->SetStyle(static_cast<AdaptiveCards::TextStyle>(m_style));

        sharedTextBlock = std::move(textBlock);
        return S_OK;
    }
    CATCH_RETURN;
}
