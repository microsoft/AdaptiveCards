#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    // This class is effectively a singleton, and stays around between subsequent renders.
    class ImageRenderResult :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::FtmBase,
            ABI::AdaptiveCards::XamlCardRenderer::IImageRenderResult>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_ImageRenderResult)

    public:
        HRESULT RuntimeClassInitialize(_In_ HSTRING altText, _In_ ABI::Windows::Storage::Streams::IBuffer* pixelBuffer, _In_ int width, _In_ int height);

        // IImageRenderResult
        STDMETHODIMP get_AltText(_Out_ HSTRING* altText);
        STDMETHODIMP get_ImageBuffer(_Out_ ABI::Windows::Storage::Streams::IBuffer **imageBuffer);
        STDMETHODIMP get_IsAllContentClippedOut(_Out_ boolean *allContentClipped);
        STDMETHODIMP get_ImageWidthPixels(_Out_ int *width);
        STDMETHODIMP get_ImageHeightPixels(_Out_ int *height);

    private:
        int m_pixelWidth;
        int m_pixelHeight;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IBuffer> m_pixelBuffer;
        Microsoft::WRL::Wrappers::HString m_altText;
    };
}}