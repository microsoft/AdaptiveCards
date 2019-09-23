// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImage.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveImage::AdaptiveImage() {}

    HRESULT AdaptiveImage::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Image> image = std::make_shared<AdaptiveSharedNamespace::Image>();
        return RuntimeClassInitialize(image);
    }
    CATCH_RETURN;

    HRESULT AdaptiveImage::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Image>& sharedImage)
    try
    {
        if (sharedImage == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedImage->GetUrl(), m_url.GetAddressOf()));

        RETURN_IF_FAILED(UTF8ToHString(sharedImage->GetBackgroundColor(), m_backgroundColor.GetAddressOf()));

        m_imageStyle = static_cast<ABI::AdaptiveNamespace::ImageStyle>(sharedImage->GetImageStyle());
        m_imageSize = static_cast<ABI::AdaptiveNamespace::ImageSize>(sharedImage->GetImageSize());
        m_pixelWidth = sharedImage->GetPixelWidth();
        m_pixelHeight = sharedImage->GetPixelHeight();
        m_horizontalAlignment = static_cast<ABI::AdaptiveNamespace::HAlignment>(sharedImage->GetHorizontalAlignment());
        RETURN_IF_FAILED(UTF8ToHString(sharedImage->GetAltText(), m_altText.GetAddressOf()));
        GenerateActionProjection(sharedImage->GetSelectAction(), &m_selectAction);

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedImage));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveImage::get_Url(_Outptr_ HSTRING* url) { return m_url.CopyTo(url); }

    HRESULT AdaptiveImage::put_Url(_In_ HSTRING url) { return m_url.Set(url); }

    HRESULT AdaptiveImage::get_BackgroundColor(_Outptr_ HSTRING* backgroundColor)
    {
        return m_backgroundColor.CopyTo(backgroundColor);
    }

    HRESULT AdaptiveImage::put_BackgroundColor(_In_ HSTRING backgroundColor)
    {
        return m_backgroundColor.Set(backgroundColor);
    }

    HRESULT AdaptiveImage::get_Style(_Out_ ABI::AdaptiveNamespace::ImageStyle* imageStyle)
    {
        *imageStyle = m_imageStyle;
        return S_OK;
    }

    HRESULT AdaptiveImage::put_Style(ABI::AdaptiveNamespace::ImageStyle imageStyle)
    {
        m_imageStyle = imageStyle;
        return S_OK;
    }

    HRESULT AdaptiveImage::get_Size(_Out_ ABI::AdaptiveNamespace::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    HRESULT AdaptiveImage::put_Size(ABI::AdaptiveNamespace::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK;
    }

    HRESULT AdaptiveImage::get_PixelWidth(_Out_ UINT32* pixelWidth)
    {
        *pixelWidth = m_pixelWidth;
        return S_OK;
    }

    HRESULT AdaptiveImage::put_PixelWidth(UINT32 pixelWidth)
    {
        m_pixelWidth = pixelWidth;
        return S_OK;
    }

    HRESULT AdaptiveImage::get_PixelHeight(_Out_ UINT32* pixelHeight)
    {
        *pixelHeight = m_pixelHeight;
        return S_OK;
    }

    HRESULT AdaptiveImage::put_PixelHeight(UINT32 pixelHeight)
    {
        m_pixelHeight = pixelHeight;
        return S_OK;
    }

    HRESULT AdaptiveImage::get_AltText(_Outptr_ HSTRING* text) { return m_altText.CopyTo(text); }

    HRESULT AdaptiveImage::put_AltText(_In_ HSTRING text) { return m_altText.Set(text); }

    HRESULT AdaptiveImage::get_HorizontalAlignment(ABI::AdaptiveNamespace::HAlignment* alignment)
    {
        *alignment = m_horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveImage::put_HorizontalAlignment(ABI::AdaptiveNamespace::HAlignment alignment)
    {
        m_horizontalAlignment = alignment;
        return S_OK;
    }

    HRESULT AdaptiveImage::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Image;
        return S_OK;
    }

    HRESULT AdaptiveImage::get_SelectAction(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_selectAction.CopyTo(action);
    }

    HRESULT AdaptiveImage::put_SelectAction(_In_ IAdaptiveActionElement* action)
    {
        m_selectAction = action;
        return S_OK;
    }

    HRESULT AdaptiveImage::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedImage)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::Image> image = std::make_shared<AdaptiveSharedNamespace::Image>();

        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseCardElement>(image)));

        if (m_selectAction != nullptr)
        {
            std::shared_ptr<BaseActionElement> sharedAction;
            RETURN_IF_FAILED(GenerateSharedAction(m_selectAction.Get(), sharedAction));
            image->SetSelectAction(sharedAction);
        }

        image->SetUrl(HStringToUTF8(m_url.Get()));
        image->SetBackgroundColor(HStringToUTF8(m_backgroundColor.Get()));

        if (m_altText != nullptr)
        {
            std::string out;
            RETURN_IF_FAILED(HStringToUTF8(m_altText.Get(), out));
            image->SetAltText(out);
        }

        image->SetImageStyle(static_cast<AdaptiveSharedNamespace::ImageStyle>(m_imageStyle));
        image->SetImageSize(static_cast<AdaptiveSharedNamespace::ImageSize>(m_imageSize));
        image->SetPixelHeight(m_pixelHeight);
        image->SetPixelWidth(m_pixelWidth);
        image->SetHorizontalAlignment(static_cast<AdaptiveSharedNamespace::HorizontalAlignment>(m_horizontalAlignment));

        sharedImage = image;
        return S_OK;
    }
    CATCH_RETURN;
}
