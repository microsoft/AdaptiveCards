#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "Container.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace Uwp
{
    class DECLSPEC_UUID("d6031009-7039-4735-bd07-ab6d99b29f03") AdaptiveContainer :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveContainer,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveContainer, BaseTrust)

    public:
        AdaptiveContainer();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::Container>& sharedcontainer);

        // IAdaptiveContainer
        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::Uwp::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveCards::Uwp::ContainerStyle style);

        IFACEMETHODIMP get_Items(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>** items);

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionElement** action);
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* action);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(_In_ boolean separator);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveCards::Container>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>> m_items;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement> m_selectAction;
        ABI::AdaptiveCards::Uwp::ContainerStyle m_style;

        boolean m_separator;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveCards::Uwp::Spacing m_spacing;
    };

    ActivatableClass(AdaptiveContainer);
}}