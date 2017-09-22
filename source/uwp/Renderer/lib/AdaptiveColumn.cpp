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
    HRESULT AdaptiveColumn::get_Size(HSTRING* size)
    {
        return UTF8ToHString(m_sharedColumn->GetSize(), size);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Size(HSTRING size)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(size, out));
        m_sharedColumn->SetSize(out);
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
    HRESULT AdaptiveColumn::get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::XamlCardRenderer::Spacing>(m_sharedColumn->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing)
    {
        m_sharedColumn->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Separator(boolean* separator)
    {
        *separator = m_sharedColumn->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedColumn->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Separator(boolean separator)
    {
        m_sharedColumn->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedColumn->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }
}}
