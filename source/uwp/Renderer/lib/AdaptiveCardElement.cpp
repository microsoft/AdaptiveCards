#include "pch.h"
#include "AdaptiveCardElement.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveCardElementBase::AdaptiveCardElementBase()
    {
        m_viewStates = Microsoft::WRL::Make<Vector<HSTRING>>();
    }

    HRESULT AdaptiveCardElementBase::InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) try
    {
        m_spacing = static_cast<ABI::AdaptiveNamespace::Spacing>(sharedModel->GetSpacing());
        m_separator = sharedModel->GetSeparator();
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetId(), m_id.GetAddressOf()));
        RETURN_IF_FAILED(JsonCppToJsonObject(sharedModel->GetAdditionalProperties(), &m_additionalProperties));
        RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetElementTypeString(), m_typeString.GetAddressOf()));
        m_height = static_cast<ABI::AdaptiveNamespace::HeightType>(sharedModel->GetHeight());

        for (auto& viewState : sharedModel->GetVisibleViewStates())
        {
            HString hstringViewState;
            RETURN_IF_FAILED(UTF8ToHString(viewState, hstringViewState.GetAddressOf()));
            RETURN_IF_FAILED(m_viewStates->Append(hstringViewState.Get()));
        }

        return S_OK;
    }
    CATCH_RETURN;

    IFACEMETHODIMP AdaptiveCardElementBase::get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Separator(boolean* separator)
    {
        *separator = m_separator;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Separator(boolean separator)
    {
        m_separator = separator;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Id(HSTRING* id) { return m_id.CopyTo(id); }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Id(HSTRING id) { return m_id.Set(id); }

    IFACEMETHODIMP AdaptiveCardElementBase::get_ElementTypeString(HSTRING* type) { return m_typeString.CopyTo(type); }

    IFACEMETHODIMP AdaptiveCardElementBase::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return m_additionalProperties.CopyTo(result);
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        m_additionalProperties = jsonObject;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_Height(ABI::AdaptiveNamespace::HeightType* height)
    {
        *height = m_height;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::put_Height(ABI::AdaptiveNamespace::HeightType height)
    {
        m_height = height;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveCardElementBase::get_VisibleViewStates(ABI::Windows::Foundation::Collections::IVector<HSTRING>** viewStates)
    {
        return m_viewStates.CopyTo(viewStates);
    }

    IFACEMETHODIMP AdaptiveCardElementBase::ToJson(ABI::Windows::Data::Json::IJsonObject** result)
    {
        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedModel;
        RETURN_IF_FAILED(GetSharedModel(sharedModel));

        return StringToJsonObject(sharedModel->Serialize(), result);
    }

    HRESULT AdaptiveCardElementBase::SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedCardElement) try
    {
        sharedCardElement->SetId(HStringToUTF8(m_id.Get()));
        sharedCardElement->SetSeparator(m_separator);
        sharedCardElement->SetSpacing(static_cast<AdaptiveSharedNamespace::Spacing>(m_spacing));
        sharedCardElement->SetHeight(static_cast<AdaptiveSharedNamespace::HeightType>(m_height));

        if (m_additionalProperties != nullptr)
        {
            Json::Value jsonCpp;
            RETURN_IF_FAILED(JsonObjectToJsonCpp(m_additionalProperties.Get(), &jsonCpp));
            sharedCardElement->SetAdditionalProperties(jsonCpp);
        }

        ComPtr<IIterable<HSTRING>> iterable;
        THROW_IF_FAILED(m_viewStates.As<IIterable<HSTRING>>(&iterable));

        Microsoft::WRL::ComPtr<IIterator<HSTRING>> iterator;
        HRESULT hr = iterable->First(&iterator);
        if (SUCCEEDED(hr))
        {
            boolean hasCurrent = false;
            HRESULT hr = iterator->get_HasCurrent(&hasCurrent);

            while (SUCCEEDED(hr) && hasCurrent)
            {
                HString currentViewState;
                RETURN_IF_FAILED(iterator->get_Current(currentViewState.GetAddressOf()));
                sharedCardElement->GetVisibleViewStates().push_back(HStringToUTF8(currentViewState.Get()));
                hr = iterator->MoveNext(&hasCurrent);
            }
        }

        return S_OK;
    }
    CATCH_RETURN;
}
