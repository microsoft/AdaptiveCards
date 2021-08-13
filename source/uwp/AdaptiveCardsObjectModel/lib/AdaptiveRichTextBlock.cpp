// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlock.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveRichTextBlock::AdaptiveRichTextBlock() { m_inlines = Microsoft::WRL::Make<Vector<IAdaptiveInline*>>(); }

    HRESULT AdaptiveRichTextBlock::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::RichTextBlock> richTextBlock = std::make_shared<AdaptiveCards::RichTextBlock>();
        return RuntimeClassInitialize(richTextBlock);
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlock::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::RichTextBlock>& sharedRichTextBlock) noexcept
    try
    {
        if (sharedRichTextBlock == nullptr)
        {
            return E_INVALIDARG;
        }

        if (sharedRichTextBlock->GetHorizontalAlignment().has_value())
        {
            m_horizontalAlignment =
                winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HAlignment>(
                                     sharedRichTextBlock->GetHorizontalAlignment().value()))
                    .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>>()
                    .get();
        }

        GenerateInlinesProjection(sharedRichTextBlock->GetInlines(), m_inlines.Get());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedRichTextBlock));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlock::get_HorizontalAlignment(
        _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalAlignment)
    {
        return m_horizontalAlignment.CopyTo(horizontalAlignment);
    }

    HRESULT AdaptiveRichTextBlock::put_HorizontalAlignment(
        _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalAlignment)
    {
        m_horizontalAlignment = horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::get_Inlines(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline*>** inlines)
    {
        return m_inlines.CopyTo(inlines);
    }

    HRESULT AdaptiveRichTextBlock::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::RichTextBlock;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedRichTextBlock) noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::RichTextBlock> richTextBlock = std::make_shared<AdaptiveCards::RichTextBlock>();

        RETURN_IF_FAILED(CopySharedElementProperties(*richTextBlock));

        if (m_horizontalAlignment != nullptr)
        {
            ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment horizontalAlignmentValue;
            RETURN_IF_FAILED(m_horizontalAlignment->get_Value(&horizontalAlignmentValue));
            richTextBlock->SetHorizontalAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(horizontalAlignmentValue));
        }

        RETURN_IF_FAILED(GenerateSharedInlines(m_inlines.Get(), richTextBlock->GetInlines()));

        sharedRichTextBlock = std::move(richTextBlock);
        return S_OK;
    }
    CATCH_RETURN;
}
