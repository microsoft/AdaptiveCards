#include "pch.h"
#include "AdaptiveColumnSet.h"

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
    AdaptiveColumnSet::AdaptiveColumnSet()
    {
        m_columns = Microsoft::WRL::Make<Vector<IAdaptiveColumn*>>();
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::ColumnSet;
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::get_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size)
    {
        *size = m_size;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSet::put_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size)
    {
        m_size = size;
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveColumnSet::get_Columns(IVector<IAdaptiveColumn*>** columns)
    {
        return m_columns.CopyTo(columns);
    }

}}
