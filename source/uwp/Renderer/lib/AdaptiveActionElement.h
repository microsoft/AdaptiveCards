#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class DECLSPEC_UUID("8CFF4A73-2DE3-4BB2-8179-971A8A19F7DE") AdaptiveActionElementBase : public IUnknown
    {
    protected:

        HRESULT InitializeBaseElement(const std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel);

        IFACEMETHODIMP get_ActionTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT SetSharedElementProperties(std::shared_ptr<AdaptiveCards::BaseActionElement> sharedCardElement);

        virtual HRESULT GetSharedModel(std::shared_ptr<BaseActionElement>& sharedModel) = 0;

    private:
        Microsoft::WRL::Wrappers::HString m_id;
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
        Microsoft::WRL::Wrappers::HString m_typeString;
    };
}}}