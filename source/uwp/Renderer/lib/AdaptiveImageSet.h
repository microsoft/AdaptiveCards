#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "ImageSet.h"
#include <windows.foundation.h>

namespace AdaptiveCards {
    namespace XamlCardRenderer
    {
        class AdaptiveImageSet :
            public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImageSet,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
        {
            InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImageSet, BaseTrust)

        public:
            AdaptiveImageSet();

            HRESULT RuntimeClassInitialize() noexcept;
            HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ImageSet>& sharedImageSet);

            // IAdaptiveImageSet
            IFACEMETHODIMP get_Images(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*>** columns);

            IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ImageSize* imageSize);
            IFACEMETHODIMP put_ImageSize(_In_ ABI::AdaptiveCards::XamlCardRenderer::ImageSize imageSize);

            // IAdaptiveCardElement
            IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

            IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing);
            IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing);

            IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator);
            IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator);

            IFACEMETHODIMP get_Speak(_In_ HSTRING *speak);
            IFACEMETHODIMP put_Speak(_Out_ HSTRING speak);

        private:
            // TODO: MSFT 11015796: Sync UWP Projection container classes to Shared object model counterparts.
            Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*>> m_images;

            std::shared_ptr<AdaptiveCards::ImageSet> m_sharedImageSet;
        };

        ActivatableClass(AdaptiveImageSet);
    }
}