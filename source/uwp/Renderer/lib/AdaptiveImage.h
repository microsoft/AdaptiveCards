#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "Image.h"
#include <windows.foundation.h>

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveImage :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveImage, BaseTrust)

    public:
        AdaptiveImage();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::Image>& sharedImage);

        // IAdaptiveImage
        IFACEMETHODIMP get_Url(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_Url(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ImageStyle* imageStyle);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveCards::XamlCardRenderer::ImageStyle imageStyle);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ImageSize* imageSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::XamlCardRenderer::ImageSize imageSize);

        IFACEMETHODIMP get_AltText(_Out_ HSTRING *text);
        IFACEMETHODIMP put_AltText(_In_ HSTRING text);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment* hAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(_In_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment hAlignment);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::XamlCardRenderer::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** separator);
        IFACEMETHODIMP put_Separator(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING *text);
        IFACEMETHODIMP put_Speak(_In_ HSTRING text);

    private:
        std::shared_ptr<AdaptiveCards::Image> m_sharedImage;
    };

    ActivatableClass(AdaptiveImage);
}}