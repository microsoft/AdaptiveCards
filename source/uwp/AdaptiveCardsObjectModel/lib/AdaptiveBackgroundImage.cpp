// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveBackgroundImage.h"

#include "ObjectModelUtil.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveBackgroundImage::AdaptiveBackgroundImage() {}

    HRESULT AdaptiveBackgroundImage::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::BackgroundImage> image = std::make_shared<AdaptiveCards::BackgroundImage>();
        return RuntimeClassInitialize(image);
    }
    CATCH_RETURN;

    HRESULT AdaptiveBackgroundImage::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::BackgroundImage>& sharedImage)
    try
    {
        if (sharedImage == nullptr)
        {
            return E_INVALIDARG;
        }

        if (!sharedImage->GetUrl().empty())
        {
            RETURN_IF_FAILED(UTF8ToHString(sharedImage->GetUrl(), m_url.GetAddressOf()));
        }

        m_fillMode = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode>(sharedImage->GetFillMode());
        m_horizontalAlignment =
            static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>(sharedImage->GetHorizontalAlignment());
        m_verticalAlignment = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::VAlignment>(sharedImage->GetVerticalAlignment());

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveBackgroundImage::get_Url(_Outptr_ HSTRING* url) { return m_url.CopyTo(url); }

    HRESULT AdaptiveBackgroundImage::put_Url(_In_ HSTRING url) { return m_url.Set(url); }

    HRESULT AdaptiveBackgroundImage::get_FillMode(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode* fillMode)
    {
        *fillMode = m_fillMode;
        return S_OK;
    }

    HRESULT AdaptiveBackgroundImage::put_FillMode(ABI::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode fillMode)
    {
        m_fillMode = fillMode;
        return S_OK;
    }

    HRESULT AdaptiveBackgroundImage::get_HorizontalAlignment(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment* HorizontalAlignment)
    {
        *HorizontalAlignment = m_horizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveBackgroundImage::put_HorizontalAlignment(ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment HorizontalAlignment)
    {
        m_horizontalAlignment = HorizontalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveBackgroundImage::get_VerticalAlignment(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::VAlignment* VerticalAlignment)
    {
        *VerticalAlignment = m_verticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveBackgroundImage::put_VerticalAlignment(ABI::AdaptiveCards::ObjectModel::Uwp::VAlignment VerticalAlignment)
    {
        m_verticalAlignment = VerticalAlignment;
        return S_OK;
    }

    HRESULT AdaptiveBackgroundImage::GetSharedModel(std::shared_ptr<AdaptiveCards::BackgroundImage>& sharedImage)
    try
    {
        std::shared_ptr<AdaptiveCards::BackgroundImage> image = std::make_shared<AdaptiveCards::BackgroundImage>();

        image->SetUrl(HStringToUTF8(m_url.Get()));
        image->SetFillMode(static_cast<AdaptiveCards::ImageFillMode>(m_fillMode));
        image->SetHorizontalAlignment(static_cast<AdaptiveCards::HorizontalAlignment>(m_horizontalAlignment));
        image->SetVerticalAlignment(static_cast<AdaptiveCards::VerticalAlignment>(m_verticalAlignment));

        sharedImage = std::move(image);
        return S_OK;
    }
    CATCH_RETURN;
}
