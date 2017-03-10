#include "pch.h"
#include "AdaptiveColumn.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    AdaptiveColumn::AdaptiveColumn() : m_sharedColumn(std::make_unique<Container>())
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Size(HSTRING* size)
    {
        *size = nullptr;

        if (m_size.IsValid())
        {
            RETURN_IF_FAILED(m_size.CopyTo(size));
        }
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Size(HSTRING size)
    {
        RETURN_IF_FAILED(m_size.Set(size));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }
    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Column;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* size)
    {
        *size = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedColumn->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle size)
    {
        m_sharedColumn->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(size));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedColumn->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Speak(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedColumn->SetSpeak(out);
        return S_OK;
    }
}}
