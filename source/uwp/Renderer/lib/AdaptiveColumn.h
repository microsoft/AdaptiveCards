#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Column.h"
#include <windows.foundation.h>

AdaptiveNamespaceStart
    class DECLSPEC_UUID("d674610a-a76b-4283-bd09-b5a25c41433d") AdaptiveColumn :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveColumn,
            ABI::AdaptiveNamespace::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveColumn)

    public:
        AdaptiveColumn();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::Column>& sharedColumn);

        // IAdaptiveColumn
        IFACEMETHODIMP get_Width(_Out_ HSTRING* width);
        IFACEMETHODIMP put_Width(_In_ HSTRING width);

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

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveSharedNamespace::Column>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:

        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>> m_items; 
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_selectAction;

        Microsoft::WRL::Wrappers::HString m_width;
        ABI::AdaptiveNamespace::ContainerStyle m_style;
        
        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
    };

    ActivatableClass(AdaptiveColumn);
AdaptiveNamespaceEnd
