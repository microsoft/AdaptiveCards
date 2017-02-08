#include "pch.h"
#include "AdaptiveCard.h"

#include <windows.foundation.collections.h>

using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::get_Items(IVector<IAdaptiveCardElement*>** /*items*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::get_ElementType(ElementType* /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveCard::Render(IUIElement** element)
    {
        *element = nullptr;
        return S_OK;
    }
}}