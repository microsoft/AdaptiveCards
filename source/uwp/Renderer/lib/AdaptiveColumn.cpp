#include "pch.h"
#include "AdaptiveHeight.h"
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
    AdaptiveColumn::AdaptiveColumn()
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveColumn::RuntimeClassInitialize() noexcept try
    {
        m_sharedColumn = std::make_shared<Column>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Column>& sharedColumn)
    {
        m_sharedColumn = sharedColumn;
        GenerateContainedElementsProjection(m_sharedColumn->GetItems(), m_items.Get());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Width(HSTRING* width)
    {
        return UTF8ToHString(m_sharedColumn->GetWidth(), width);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Width(HSTRING width)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(width, out));
        m_sharedColumn->SetWidth(out);
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
    HRESULT AdaptiveColumn::get_Height(IAdaptiveHeight** height)
    {
        return MakeAndInitialize<AdaptiveHeight>(height, m_sharedColumn->GetHeight());
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Height(IAdaptiveHeight* height)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle* separation)
    {
        *separation = static_cast<ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle>(m_sharedColumn->GetSeparationStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Separation(ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation)
    {
        m_sharedColumn->SetSeparationStyle(static_cast<AdaptiveCards::SeparationStyle>(separation));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Speak(HSTRING* speak)
    {
        return UTF8ToHString(m_sharedColumn->GetSpeak(), speak);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Speak(HSTRING speak)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(speak, out));
        m_sharedColumn->SetSpeak(out);
        return S_OK;
    }
}}
