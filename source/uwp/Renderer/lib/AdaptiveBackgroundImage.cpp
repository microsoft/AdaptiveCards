#include "pch.h"
#include "AdaptiveBackgroundImage.h"

#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveBackgroundImage::AdaptiveBackgroundImage() {}

    HRESULT AdaptiveBackgroundImage::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage> image =
            std::make_shared<AdaptiveSharedNamespace::BackgroundImage>();
        return RuntimeClassInitialize(image);
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::RuntimeClassInitialize(
        const std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage>& sharedImage) try
    {
        if (sharedImage != nullptr)
        {
            RETURN_IF_FAILED(UTF8ToHString(sharedImage->GetUrl(), m_url.GetAddressOf()));
            m_mode = static_cast<ABI::AdaptiveNamespace::BackgroundImageMode>(sharedImage->GetMode());
            m_horizontalAlignment = static_cast<ABI::AdaptiveNamespace::HorizontalAlignment>(sharedImage->GetHorizontalAlignment());
            m_verticalAlignment = static_cast<ABI::AdaptiveNamespace::VerticalAlignment>(sharedImage->GetVerticalAlignment());
        }
        return S_OK;
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::get_Url(HSTRING* url) { return m_url.CopyTo(url); }

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::put_Url(HSTRING url) { return m_url.Set(url); }

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::get_Mode(ABI::AdaptiveNamespace::BackgroundImageMode* mode)
    {
        *mode = m_mode;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::put_Mode(ABI::AdaptiveNamespace::BackgroundImageMode mode)
    {
        m_mode = mode;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::get_HorizontalAlignment(ABI::AdaptiveNamespace::HorizontalAlignment* HorizontalAlignment)
    {
        *HorizontalAlignment = m_horizontalAlignment;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::put_HorizontalAlignment(ABI::AdaptiveNamespace::HorizontalAlignment HorizontalAlignment)
    {
        m_horizontalAlignment = HorizontalAlignment;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::get_VerticalAlignment(ABI::AdaptiveNamespace::VerticalAlignment* VerticalAlignment)
    {
        *VerticalAlignment = m_verticalAlignment;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveBackgroundImage::put_VerticalAlignment(ABI::AdaptiveNamespace::VerticalAlignment VerticalAlignment)
    {
        m_verticalAlignment = VerticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveBackgroundImage::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage>& sharedImage) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::BackgroundImage> image =
            std::make_shared<AdaptiveSharedNamespace::BackgroundImage>();

        image->SetUrl(HStringToUTF8(m_url.Get()));
        image->SetMode(static_cast<AdaptiveSharedNamespace::BackgroundImageMode>(m_mode));
        image->SetHorizontalAlignment(static_cast<AdaptiveSharedNamespace::HorizontalAlignment>(m_horizontalAlignment));
        image->SetVerticalAlignment(static_cast<AdaptiveSharedNamespace::VerticalAlignment>(m_verticalAlignment));

        sharedImage = image;
        return S_OK;
    }
    CATCH_RETURN;
}
