#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("49496982-18E7-48A8-9D16-99E389BE9133") AdaptiveCardElementBase : public IUnknown
    {
    protected:

        HRESULT InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing);
        
        IFACEMETHODIMP get_Separator(boolean* separator);
        IFACEMETHODIMP put_Separator(boolean separator);

        IFACEMETHODIMP get_Id(HSTRING* id);
        IFACEMETHODIMP put_Id(HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(HSTRING* type);

        IFACEMETHODIMP get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject);

        IFACEMETHODIMP ToJson(ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedCardElement);

        virtual HRESULT GetSharedModel(std::shared_ptr<BaseCardElement>& sharedModel) = 0;

    private:
        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
        Microsoft::WRL::Wrappers::HString m_typeString;
    };
AdaptiveNamespaceEnd