// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlock.h"
#include "DateTimeParser.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveRichTextBlock::AdaptiveRichTextBlock() { m_inlines = Microsoft::WRL::Make<Vector<IAdaptiveInline*>>(); }

    HRESULT AdaptiveRichTextBlock::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::RichTextBlock> richTextBlock =
            std::make_shared<AdaptiveSharedNamespace::RichTextBlock>();
        return RuntimeClassInitialize(richTextBlock);
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlock::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::RichTextBlock>& sharedRichTextBlock) noexcept try
    {
        if (sharedRichTextBlock == nullptr)
        {
            return E_INVALIDARG;
        }

        m_horizontalAlignment = static_cast<ABI::AdaptiveNamespace::HAlignment>(sharedRichTextBlock->GetHorizontalAlignment());

        GenerateInlinesProjection(sharedRichTextBlock->GetInlines(), m_inlines.Get());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedRichTextBlock));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlock::get_HorizontalAlignment(_Out_ ABI::AdaptiveNamespace::HAlignment* alignment)
    {
        *alignment = m_horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::put_HorizontalAlignment(ABI::AdaptiveNamespace::HAlignment alignment)
    {
        m_horizontalAlignment = alignment;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::get_Inlines(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveInline*>** inlines)
    {
        return m_inlines.CopyTo(inlines);
    }

    HRESULT AdaptiveRichTextBlock::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::RichTextBlock;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedRichTextBlock) noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::RichTextBlock> richTextBlock =
            std::make_shared<AdaptiveSharedNamespace::RichTextBlock>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(richTextBlock)));

        richTextBlock->SetHorizontalAlignment(static_cast<AdaptiveSharedNamespace::HorizontalAlignment>(m_horizontalAlignment));

        RETURN_IF_FAILED(GenerateSharedInlines(m_inlines.Get(), richTextBlock->GetInlines()));

        sharedRichTextBlock = richTextBlock;
        return S_OK;
    }
    CATCH_RETURN;
}
