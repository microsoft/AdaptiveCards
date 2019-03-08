#include "pch.h"
#include "AdaptiveRichTextBlock.h"
#include "Util.h"
#include "DateTimeParser.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveRichTextBlock::AdaptiveRichTextBlock()
    {
        m_paragraphs = Microsoft::WRL::Make<Vector<AdaptiveParagraph*>>();
    }

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

        m_wrap = sharedRichTextBlock->GetWrap();
        m_maxLines = sharedRichTextBlock->GetMaxLines();
        m_horizontalAlignment = static_cast<ABI::AdaptiveNamespace::HAlignment>(sharedRichTextBlock->GetHorizontalAlignment());

        GenerateParagraphsProjection(sharedRichTextBlock->GetParagraphs(), m_paragraphs.Get());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedRichTextBlock));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRichTextBlock::get_Wrap(_Out_ boolean* wrap)
    {
        *wrap = m_wrap;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::put_Wrap(boolean wrap)
    {
        m_wrap = wrap;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::get_MaxLines(_Out_ UINT32* maxLines)
    {
        *maxLines = m_maxLines;
        return S_OK;
    }

    HRESULT AdaptiveRichTextBlock::put_MaxLines(UINT32 maxLines)
    {
        m_maxLines = maxLines;
        return S_OK;
    }

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

    HRESULT AdaptiveRichTextBlock::get_Paragraphs(
        ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveParagraph*>** paragraphs)
    {
        return m_paragraphs.CopyTo(paragraphs);
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

        richTextBlock->SetWrap(m_wrap);
        richTextBlock->SetMaxLines(m_maxLines);
        richTextBlock->SetHorizontalAlignment(static_cast<AdaptiveSharedNamespace::HorizontalAlignment>(m_horizontalAlignment));

        RETURN_IF_FAILED(GenerateSharedParagraphs(m_paragraphs.Get(), richTextBlock->GetParagraphs()));

        sharedRichTextBlock = richTextBlock;
        return S_OK;
    }
    CATCH_RETURN;
}
