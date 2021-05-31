// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlock.h"
#include "DateTimeParser.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards::Rendering::Uwp
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

        m_horizontalAlignment =
            static_cast<ABI::AdaptiveCards::Rendering::Uwp::HAlignment>(sharedRichTextBlock->GetHorizontalAlignment());

        GenerateInlinesProjection(sharedRichTextBlock->GetInlines(), m_inlines.Get());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedRichTextBlock));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlock::get_HorizontalAlignment(_Out_ ABI::AdaptiveCards::Rendering::Uwp::HAlignment* alignment)
    {
        *alignment = m_horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::put_HorizontalAlignment(ABI::AdaptiveCards::Rendering::Uwp::HAlignment alignment)
    {
        m_horizontalAlignment = alignment;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::get_Inlines(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline*>** inlines)
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

        richTextBlock->SetHorizontalAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(m_horizontalAlignment));

        RETURN_IF_FAILED(GenerateSharedInlines(m_inlines.Get(), richTextBlock->GetInlines()));

        sharedRichTextBlock = std::move(richTextBlock);
        return S_OK;
    }
    CATCH_RETURN;
}
