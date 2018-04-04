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
    HRESULT AdaptiveContainer::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Container>& sharedContainer)
    {
        if (sharedContainer == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateContainedElementsProjection(sharedContainer->GetItems(), m_items.Get());
        GenerateActionProjection(sharedContainer->GetSelectAction(), &m_selectAction);
        m_style = static_cast<ABI::AdaptiveNamespace::ContainerStyle>(sharedContainer->GetStyle());
        
        m_spacing = static_cast<ABI::AdaptiveNamespace::Spacing>(sharedContainer->GetSpacing());
        m_separator = sharedContainer->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedContainer->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedContainer->GetAdditionalProperties(), &m_additionalProperties));

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

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Spacing(ABI::AdaptiveNamespace::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Spacing(ABI::AdaptiveNamespace::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveContainer::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveContainer::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::Container> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveContainer::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Container>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Container> container = std::make_shared<AdaptiveSharedNamespace::Container>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::AdaptivePointerCast<AdaptiveSharedNamespace::BaseCardElement>(container)));

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
