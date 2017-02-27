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
    AdaptiveColumn::AdaptiveColumn() : m_column(std::make_unique<Container>())
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_StartGroup(boolean* startGroup)
    {
        *startGroup = m_column->GetStartGroup();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_StartGroup(boolean startGroup)
    {
        m_column->SetStartGroup(Boolify(startGroup));
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumn::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Column;
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumn::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size)
    {
        *size = static_cast<ABI::AdaptiveCards::XamlCardRenderer::CardElementSize>(m_column->GetSize());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size)
    {
        m_column->SetSize(static_cast<AdaptiveCards::CardElementSize>(size));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_ColumnSize(HSTRING* size)
    {
        *size = nullptr;

        if (m_size.IsValid())
        {
            RETURN_IF_FAILED(m_size.CopyTo(size));
        }
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_ColumnSize(HSTRING size)
    {
        RETURN_IF_FAILED(m_size.Set(size));
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumn::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }
}}
