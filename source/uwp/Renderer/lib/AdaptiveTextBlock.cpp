#include "pch.h"
#include "AdaptiveTextBlock.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "AdaptiveCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveTextBlock::RuntimeClassInitialize() noexcept try
    {
        m_sharedTextBlock = std::make_shared<TextBlock>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TextBlock>& sharedTextBlock)
    {
        if (sharedTextBlock == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedTextBlock = sharedTextBlock;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Text(HSTRING* text)
    {
        return UTF8ToHString(m_sharedTextBlock->GetText(), text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Text(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedTextBlock->SetText(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Size(ABI::AdaptiveCards::Uwp::TextSize* textSize)
    {
        *textSize = static_cast<ABI::AdaptiveCards::Uwp::TextSize>(m_sharedTextBlock->GetTextSize());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Size(ABI::AdaptiveCards::Uwp::TextSize textSize)
    {
        m_sharedTextBlock->SetTextSize(static_cast<AdaptiveCards::TextSize>(textSize));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Weight(ABI::AdaptiveCards::Uwp::TextWeight* textWeight)
    {
        *textWeight = static_cast<ABI::AdaptiveCards::Uwp::TextWeight>(m_sharedTextBlock->GetTextWeight());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Weight(ABI::AdaptiveCards::Uwp::TextWeight textWeight)
    {
        m_sharedTextBlock->SetTextWeight(static_cast<AdaptiveCards::TextWeight>(textWeight));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Color(ABI::AdaptiveCards::Uwp::ForegroundColor* textColor)
    {
        *textColor = static_cast<ABI::AdaptiveCards::Uwp::ForegroundColor>(m_sharedTextBlock->GetTextColor());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Color(ABI::AdaptiveCards::Uwp::ForegroundColor textColor)
    {
        m_sharedTextBlock->SetTextColor(static_cast<AdaptiveCards::ForegroundColor>(textColor));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Wrap(boolean* wrap)
    {
        *wrap = m_sharedTextBlock->GetWrap();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Wrap(boolean wrap)
    {
        m_sharedTextBlock->SetWrap(Boolify(wrap));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_IsSubtle(boolean* isSubtle)
    {
        *isSubtle = m_sharedTextBlock->GetIsSubtle();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_IsSubtle(boolean isSubtle)
    {
        m_sharedTextBlock->SetIsSubtle(Boolify(isSubtle));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_MaxLines(UINT32* maxLines)
    {
        *maxLines = m_sharedTextBlock->GetMaxLines();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_MaxLines(UINT32 maxLines)
    {
        m_sharedTextBlock->SetMaxLines(maxLines);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_HorizontalAlignment(ABI::AdaptiveCards::Uwp::HAlignment* alignment)
    {
        *alignment = static_cast<ABI::AdaptiveCards::Uwp::HAlignment>(m_sharedTextBlock->GetHorizontalAlignment());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_HorizontalAlignment(ABI::AdaptiveCards::Uwp::HAlignment alignment)
    {
        m_sharedTextBlock->SetHorizontalAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(alignment));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::TextBlock;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedTextBlock->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedTextBlock->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Separator(boolean* separator)
    {
        *separator = m_sharedTextBlock->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedTextBlock->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Separator(boolean separator)
    {
        m_sharedTextBlock->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedTextBlock->SetSeparator(sharedSeparator);
        */
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedTextBlock->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedTextBlock->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextBlock::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}}
