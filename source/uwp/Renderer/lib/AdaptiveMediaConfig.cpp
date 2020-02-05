// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveMediaConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveMediaConfig::RuntimeClassInitialize() noexcept
    try
    {
        MediaConfig mediaConfig;
        return RuntimeClassInitialize(mediaConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveMediaConfig::RuntimeClassInitialize(MediaConfig mediaConfig) noexcept
    {
        RETURN_IF_FAILED(UTF8ToHString(mediaConfig.defaultPoster, m_defaultPoster.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(mediaConfig.playButton, m_playButton.GetAddressOf()));

        m_allowInlinePlayback = mediaConfig.allowInlinePlayback;

        return S_OK;
    }

    HRESULT AdaptiveMediaConfig::get_DefaultPoster(_Outptr_ HSTRING* defaultPoster)
    {
        return m_defaultPoster.CopyTo(defaultPoster);
    }

    HRESULT AdaptiveMediaConfig::put_DefaultPoster(_In_ HSTRING defaultPoster)
    {
        return m_defaultPoster.Set(defaultPoster);
    }

    HRESULT AdaptiveMediaConfig::get_PlayButton(_Outptr_ HSTRING* playButton)
    {
        return m_playButton.CopyTo(playButton);
    }

    HRESULT AdaptiveMediaConfig::put_PlayButton(_In_ HSTRING playButton) { return m_playButton.Set(playButton); }

    HRESULT AdaptiveMediaConfig::get_AllowInlinePlayback(_Out_ boolean* allowInlinePlayback)
    {
        *allowInlinePlayback = m_allowInlinePlayback;
        return S_OK;
    }

    HRESULT AdaptiveMediaConfig::put_AllowInlinePlayback(boolean allowInlinePlayback)
    {
        m_allowInlinePlayback = allowInlinePlayback;
        return S_OK;
    }
}
