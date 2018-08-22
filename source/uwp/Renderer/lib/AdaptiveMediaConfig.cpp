#include "pch.h"
#include "Util.h"
#include "AdaptiveMediaConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveMediaConfig::RuntimeClassInitialize() noexcept try
    {
        MediaConfig mediaConfig;
        return RuntimeClassInitialize(mediaConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveMediaConfig::RuntimeClassInitialize(MediaConfig mediaConfig) noexcept
    {
        RETURN_IF_FAILED(UTF8ToHString(mediaConfig.defaultPoster, m_defaultPoster.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(mediaConfig.playButton, m_playButton.GetAddressOf()));

        m_allowInlinePlayback = mediaConfig.allowInlinePlayback;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaConfig::get_DefaultPoster(HSTRING* defaultPoster)
    {
        return m_defaultPoster.CopyTo(defaultPoster);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaConfig::put_DefaultPoster(HSTRING defaultPoster)
    {
        return m_defaultPoster.Set(defaultPoster);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaConfig::get_PlayButton(HSTRING* playButton)
    {
        return m_playButton.CopyTo(playButton);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaConfig::put_PlayButton(HSTRING playButton)
    {
        return m_playButton.Set(playButton);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaConfig::get_AllowInlinePlayback(boolean* allowInlinePlayback)
    {
        *allowInlinePlayback = m_allowInlinePlayback;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaConfig::put_AllowInlinePlayback(boolean allowInlinePlayback)
    {
        m_allowInlinePlayback = allowInlinePlayback;
        return S_OK;
    }

AdaptiveNamespaceEnd
