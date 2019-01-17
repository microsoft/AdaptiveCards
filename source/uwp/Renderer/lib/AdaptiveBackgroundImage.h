#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "BackgroundImage.h"
#include <windows.foundation.h>

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("60F8A683-A7A3-4E34-BE86-C809F61BD5B6") AdaptiveBackgroundImage
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveNamespace::IAdaptiveBackgroundImage,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveBackgroundImage);

    public:
        AdaptiveBackgroundImage();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage>& sharedImage);

        IFACEMETHODIMP get_Url(_Out_ HSTRING* url);
        IFACEMETHODIMP put_Url(_In_ HSTRING url);

        IFACEMETHODIMP get_Mode(_Out_ ABI::AdaptiveNamespace::BackgroundImageMode* mode);
        IFACEMETHODIMP put_Mode(_In_ ABI::AdaptiveNamespace::BackgroundImageMode mode);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveNamespace::HorizontalAlignment* HorizontalAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(_In_ ABI::AdaptiveNamespace::HorizontalAlignment HorizontalAlignment);

        IFACEMETHODIMP get_VerticalAlignment(_Out_ ABI::AdaptiveNamespace::VerticalAlignment* VerticalAlignment);
        IFACEMETHODIMP put_VerticalAlignment(_In_ ABI::AdaptiveNamespace::VerticalAlignment VerticalAlignment);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_url;
        ABI::AdaptiveNamespace::BackgroundImageMode m_mode;
        ABI::AdaptiveNamespace::HorizontalAlignment m_horizontalAlignment;
        ABI::AdaptiveNamespace::VerticalAlignment m_verticalAlignment;
    };
    ActivatableClass(AdaptiveBackgroundImage);
}
