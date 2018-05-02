#include "pch.h"
#include "AdaptiveContainer.h"

#include "Util.h"
#include "Vector.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    AdaptiveContainer::AdaptiveContainer()
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveContainer::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Container> container = std::make_shared<AdaptiveSharedNamespace::Container>();
        return RuntimeClassInitialize(container);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Container>& sharedContainer) try
    {
        if (sharedContainer == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateContainedElementsProjection(sharedContainer->GetItems(), m_items.Get());
        GenerateActionProjection(sharedContainer->GetSelectAction(), &m_selectAction);
        m_style = static_cast<ABI::AdaptiveNamespace::ContainerStyle>(sharedContainer->GetStyle());
        
        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedContainer));
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveContainer::get_SelectAction(IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    _Use_decl_annotations_
    IFACEMETHODIMP AdaptiveContainer::put_SelectAction(IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Container;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Style(ABI::AdaptiveNamespace::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Style(ABI::AdaptiveNamespace::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Container> container = std::make_shared<AdaptiveSharedNamespace::Container>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(container)));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            container->SetSelectAction(sharedAction);
        }

        container->SetStyle(static_cast<AdaptiveSharedNamespace::ContainerStyle>(m_style));

        GenerateSharedElements(m_items.Get(), container->GetItems());

        sharedModel = container;
        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
