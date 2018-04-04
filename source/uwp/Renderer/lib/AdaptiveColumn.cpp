#include "pch.h"
#include "AdaptiveColumn.h"

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
    AdaptiveColumn::AdaptiveColumn()
    {
        m_items = Microsoft::WRL::Make<Vector<IAdaptiveCardElement*>>();
    }

    HRESULT AdaptiveColumn::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Column> column = std::make_shared<AdaptiveSharedNamespace::Column>();
        return RuntimeClassInitialize(column);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Column>& sharedColumn)
    {
        GenerateContainedElementsProjection(sharedColumn->GetItems(), m_items.Get());
        GenerateActionProjection(sharedColumn->GetSelectAction(), &m_selectAction);

        m_style = static_cast<ABI::AdaptiveNamespace::ContainerStyle>(sharedColumn->GetStyle());
        RETURN_IF_FAILED(UTF8ToHString(sharedColumn->GetWidth(), m_width.GetAddressOf()));

        m_spacing = static_cast<ABI::AdaptiveNamespace::Spacing>(sharedColumn->GetSpacing());
        m_separator = sharedColumn->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedColumn->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedColumn->GetAdditionalProperties(), &m_additionalProperties));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Width(HSTRING* width)
    {
        return m_width.CopyTo(width);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Width(HSTRING width)
    {
        return m_width.Set(width);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Style(ABI::AdaptiveNamespace::ContainerStyle* style)
    {
        *style = m_style;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Style(ABI::AdaptiveNamespace::ContainerStyle style)
    {
        m_style = style;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Items(IVector<IAdaptiveCardElement*>** items)
    {
        return m_items.CopyTo(items);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_SelectAction(IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_SelectAction(IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_ElementType(ElementType* elementType)
    {
        *elementType = ElementType::Column;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Spacing(ABI::AdaptiveNamespace::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Spacing(ABI::AdaptiveNamespace::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_Id(HSTRING* id)
    {
        return m_id.CopyTo(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_Id(HSTRING id)
    {
        return m_id.Set(id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_ElementTypeString(HSTRING* type)
    {
        ElementType typeEnum;
        RETURN_IF_FAILED(get_ElementType(&typeEnum));
        return ProjectedElementTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::Column> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumn::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::Column>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Column> column = std::make_shared<AdaptiveSharedNamespace::Column>();

        RETURN_IF_FAILED(SetSharedElementProperties(this, std::AdaptivePointerCast<AdaptiveSharedNamespace::BaseCardElement>(column)));

        column->SetStyle(static_cast<AdaptiveSharedNamespace::ContainerStyle>(m_style));
        column->SetWidth(HStringToUTF8(m_width.Get()));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            column->SetSelectAction(sharedAction);
        }

        GenerateSharedElements(m_items.Get(), column->GetItems());

        sharedModel = column;
        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
