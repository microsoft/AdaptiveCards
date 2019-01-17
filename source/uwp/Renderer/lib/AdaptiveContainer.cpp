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

namespace AdaptiveNamespace
{
    AdaptiveContainer::AdaptiveContainer() { m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>(); }

    HRESULT AdaptiveContainer::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Container> container = std::make_shared<AdaptiveSharedNamespace::Container>();
        return RuntimeClassInitialize(container);
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainer::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Container>& sharedContainer) try
    {
        if (sharedContainer == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateContainedElementsProjection(sharedContainer->GetItems(), m_items.Get());
        GenerateActionProjection(sharedContainer->GetSelectAction(), &m_selectAction);
        m_style = static_cast<ABI::AdaptiveNamespace::ContainerStyle>(sharedContainer->GetStyle());
        m_verticalAlignment =
            static_cast<ABI::AdaptiveNamespace::VerticalContentAlignment>(sharedContainer->GetVerticalContentAlignment());
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveBackgroundImage>(m_backgroundImage.GetAddressOf(),
                                                                    sharedContainer->GetBackgroundImage()));

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedContainer));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveContainer::get_Items(_COM_Outptr_ IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    IFACEMETHODIMP AdaptiveContainer::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    IFACEMETHODIMP AdaptiveContainer::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Container;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_Style(ABI::AdaptiveNamespace::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    HRESULT AdaptiveContainer::get_VerticalContentAlignment(_Out_ ABI::AdaptiveNamespace::VerticalContentAlignment* verticalAlignment)
    {
        *verticalAlignment = m_verticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveContainer::put_VerticalContentAlignment(ABI::AdaptiveNamespace::VerticalContentAlignment verticalAlignment)
    {
        m_verticalAlignment = verticalAlignment;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainer::get_BackgroundImage(IAdaptiveBackgroundImage** backgroundImage)
    {
        return m_backgroundImage.CopyTo(backgroundImage);
    }

    _Use_decl_annotations_ HRESULT AdaptiveContainer::put_BackgroundImage(IAdaptiveBackgroundImage* backgroundImage)
    {
        m_backgroundImage = backgroundImage;
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
        container->SetVerticalContentAlignment(static_cast<AdaptiveSharedNamespace::VerticalContentAlignment>(m_verticalAlignment));

        std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage> sharedBackgroundImage;
        auto backgroundImage = static_cast<AdaptiveNamespace::AdaptiveBackgroundImage*>(m_backgroundImage.Get());
        RETURN_IF_FAILED(backgroundImage->GetSharedModel(sharedBackgroundImage));
        container->SetBackgroundImage(sharedBackgroundImage);

        GenerateSharedElements(m_items.Get(), container->GetItems());

        sharedModel = container;
        return S_OK;
    }
    CATCH_RETURN;
}
