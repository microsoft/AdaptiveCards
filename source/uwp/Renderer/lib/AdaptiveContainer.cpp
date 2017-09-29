#include "pch.h"
#include "AdaptiveContainer.h"

#include "Util.h"
#include "Vector.h"
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
    AdaptiveContainer::AdaptiveContainer()
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveContainer::RuntimeClassInitialize() noexcept try
    {
        m_sharedContainer = std::make_shared<Container>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Container>& sharedContainer)
    {
        if (sharedContainer == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedContainer = sharedContainer;
        GenerateContainedElementsProjection(m_sharedContainer->GetItems(), m_items.Get());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveContainer::get_SelectAction(IAdaptiveActionElement** action)
    {
        return GenerateActionProjection(m_sharedContainer->GetSelectAction(), action);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveContainer::put_SelectAction(IAdaptiveActionElement* action)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Container;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Style(ABI::AdaptiveCards::Uwp::ContainerStyle* style)
    {
        *style = static_cast<ABI::AdaptiveCards::Uwp::ContainerStyle>(m_sharedContainer->GetStyle());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Style(ABI::AdaptiveCards::Uwp::ContainerStyle style)
    {
        m_sharedContainer->SetStyle(static_cast<AdaptiveCards::ContainerStyle>(style));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Spacing(ABI::AdaptiveCards::Uwp::Spacing* spacing)
    {
        *spacing = static_cast<ABI::AdaptiveCards::Uwp::Spacing>(m_sharedContainer->GetSpacing());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Spacing(ABI::AdaptiveCards::Uwp::Spacing spacing)
    {
        m_sharedContainer->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Separator(boolean* separator)
    {
        *separator = m_sharedContainer->GetSeparator();
        return S_OK;

        //Issue #629 to make separator an object
        //return GenerateSeparatorProjection(m_sharedContainer->GetSeparator(), separator);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Separator(boolean separator)
    {
        m_sharedContainer->SetSeparator(separator);

        /*Issue #629 to make separator an object
        std::shared_ptr<Separator> sharedSeparator;
        RETURN_IF_FAILED(GenerateSharedSeparator(separator, &sharedSeparator));

        m_sharedContainer->SetSeparator(sharedSeparator);
        */

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedContainer->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedContainer->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }
}
}
