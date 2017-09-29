#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "ImageSet.h"
#include <windows.foundation.h>

namespace AdaptiveCards {
    namespace Uwp
    {
        class AdaptiveImageSet :
            public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveImageSet,
            ABI::AdaptiveCards::Uwp::IAdaptiveCardElement>
        {
            InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveImageSet, BaseTrust)

        public:
            AdaptiveImageSet();

            HRESULT RuntimeClassInitialize() noexcept;
            HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ImageSet>& sharedImageSet);

            // IAdaptiveImageSet
            IFACEMETHODIMP get_Images(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveImage*>** columns);

            IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveCards::Uwp::ImageSize* imageSize);
            IFACEMETHODIMP put_ImageSize(_In_ ABI::AdaptiveCards::Uwp::ImageSize imageSize);

            // IAdaptiveCardElement
            IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Uwp::ElementType* elementType);

            IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Uwp::Spacing* spacing);
            IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Uwp::Spacing spacing);

            IFACEMETHODIMP get_Separator(boolean* separator);
            IFACEMETHODIMP put_Separator(boolean separator);

            IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
            IFACEMETHODIMP put_Id(_In_ HSTRING id);

            IFACEMETHODIMP get_ElementTypeString(_Out_ HSTRING* value);

            IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        private:
            // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
            Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveImage*>> m_images;

            std::shared_ptr<AdaptiveCards::ImageSet> m_sharedImageSet;
        };

        ActivatableClass(AdaptiveImageSet);
    }
}