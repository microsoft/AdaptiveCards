#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Container.h"
#include <windows.foundation.h>

AdaptiveNamespaceStart
    class DECLSPEC_UUID("d6031009-7039-4735-bd07-ab6d99b29f03") AdaptiveContainer :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveContainer,
            ABI::AdaptiveNamespace::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveContainer)

    public:
        AdaptiveContainer();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::Container>& sharedcontainer);

        // IAdaptiveContainer
        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveNamespace::ContainerStyle style);

        IFACEMETHODIMP get_Items(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>** items);

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action);
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(_In_ boolean separator);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveSharedNamespace::Container>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>> m_items;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_selectAction;
        ABI::AdaptiveNamespace::ContainerStyle m_style;

        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
    };

    ActivatableClass(AdaptiveContainer);
AdaptiveNamespaceEnd