// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveMediaSource.h"

namespace AdaptiveNamespace
{
    HRESULT AdaptiveMediaSource::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::MediaSource> mediaSource =
            std::make_shared<AdaptiveSharedNamespace::MediaSource>();
        return RuntimeClassInitialize(mediaSource);
    }
    CATCH_RETURN;

    HRESULT AdaptiveMediaSource::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::MediaSource>& sharedMediaSource)
    try
    {
        if (sharedMediaSource == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedMediaSource->GetMimeType(), m_mimeType.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedMediaSource->GetUrl(), m_url.GetAddressOf()));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveMediaSource::get_MimeType(_Outptr_ HSTRING* value) { return m_mimeType.CopyTo(value); }

    HRESULT AdaptiveMediaSource::put_MimeType(_In_ HSTRING value) { return m_mimeType.Set(value); }

    HRESULT AdaptiveMediaSource::get_Url(_Outptr_ HSTRING* value) { return m_url.CopyTo(value); }

    HRESULT AdaptiveMediaSource::put_Url(_In_ HSTRING value) { return m_url.Set(value); }

    HRESULT AdaptiveMediaSource::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::MediaSource>& sharedMediaSource)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::MediaSource> mediaSource =
            std::make_shared<AdaptiveSharedNamespace::MediaSource>();

        mediaSource->SetMimeType(HStringToUTF8(m_mimeType.Get()));
        mediaSource->SetUrl(HStringToUTF8(m_url.Get()));

        sharedMediaSource = std::move(mediaSource);
        return S_OK;
    }
    CATCH_RETURN;
}
