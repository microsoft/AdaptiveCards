// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextBlock.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
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

        if (sharedTextBlock->GetHorizontalAlignment().has_value())
        {
            m_horizontalAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HAlignment>(
                                     sharedTextBlock->GetHorizontalAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>>()
                    .get();
        }

        if (sharedTextBlock->GetStyle().has_value())
        {
            m_style = winrt::box_value(
                          static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::TextStyle>(sharedTextBlock->GetStyle().value()))
                          .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>>()
                          .get();
        }

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

    HRESULT AdaptiveTextBlock::get_HorizontalAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalAlignment)
    {
        return m_horizontalAlignment.CopyTo(horizontalAlignment);
    }

    HRESULT AdaptiveTextBlock::put_HorizontalAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalAlignment)
    {
        m_horizontalAlignment = horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveTextBlock::get_Style(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>** style)
    {
        return m_style.CopyTo(style);
    }

    HRESULT AdaptiveTextBlock::put_Style(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle>* style)
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

        if (m_horizontalAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment horizontalAlignmentValue;
            RETURN_IF_FAILED(m_horizontalAlignment->get_Value(&horizontalAlignmentValue));
            textBlock->SetHorizontalAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(horizontalAlignmentValue));
        }

        if (m_style != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::TextStyle styleValue;
            RETURN_IF_FAILED(m_style->get_Value(&styleValue));
            textBlock->SetStyle(static_cast<AdaptiveCards::TextStyle>(styleValue));
        }

        sharedTextBlock = std::move(textBlock);
        return S_OK;
    }
    CATCH_RETURN;
}
