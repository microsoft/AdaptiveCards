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

        // IAdaptiveImage
        IFACEMETHODIMP get_Uri(_In_ ABI::Windows::Foundation::IUriRuntimeClass** uri);
        IFACEMETHODIMP put_Uri(_Out_ ABI::Windows::Foundation::IUriRuntimeClass* uri);

        IFACEMETHODIMP get_ImageStyle(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ImageStyle* imageStyle);
        IFACEMETHODIMP put_ImageStyle(_In_ ABI::AdaptiveCards::XamlCardRenderer::ImageStyle imageStyle);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ElementType* elementType);
        IFACEMETHODIMP put_ElementType(_In_ ABI::AdaptiveCards::XamlCardRenderer::ElementType elementType);

        IFACEMETHODIMP Render(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** Image);

    private:
        std::unique_ptr<AdaptiveCards::Image> m_image;

    };

    ActivatableClass(AdaptiveImage);
}}