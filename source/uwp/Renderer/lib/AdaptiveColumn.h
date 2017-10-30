#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "Column.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveColumn :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveColumn,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveColumn, BaseTrust)

    public:
        AdaptiveColumn();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::Column>& sharedColumn);

        // IAdaptiveColumn
        IFACEMETHODIMP get_Width(_Out_ HSTRING* width);
        IFACEMETHODIMP put_Width(_In_ HSTRING width);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::Uwp::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveCards::Uwp::ContainerStyle style);

        IFACEMETHODIMP get_Items(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>** items);

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

    private:

        // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>> m_items;

        std::shared_ptr<AdaptiveCards::Column> m_sharedColumn;
    };

    ActivatableClass(AdaptiveColumn);
}}
