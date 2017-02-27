#include "pch.h"
#include "AdaptiveContainer.h"

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
    HRESULT AdaptiveContainer::RuntimeClassInitialize(std::shared_ptr<AdaptiveCards::Container> sharedContainer)
    {
        m_sharedContainer = sharedContainer;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_StartGroup(boolean* startGroup)
    {
        *startGroup = m_sharedContainer->GetStartGroup();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_StartGroup(boolean startGroup)
    {
        m_sharedContainer->SetStartGroup(Boolify(startGroup));
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveContainer::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Container;
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveContainer::put_ElementType(ElementType /*elementType*/)
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize* size)
    {
        *size = static_cast<ABI::AdaptiveCards::XamlCardRenderer::CardElementSize>(m_sharedContainer->GetSize());
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Size(ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size)
    {
        m_sharedContainer->SetSize(static_cast<AdaptiveCards::CardElementSize>(size));
        return S_OK;
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveContainer::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

}
}
