#include "pch.h"
#include "AdaptiveMediaSource.h"

AdaptiveNamespaceStart
    HRESULT AdaptiveMediaSource::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::MediaSource> mediaSource = std::make_shared<AdaptiveSharedNamespace::MediaSource>();
        return RuntimeClassInitialize(mediaSource);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveMediaSource::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::MediaSource>& sharedMediaSource) try
    {
        if (sharedMediaSource == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedMediaSource->GetMimeType(), m_mimeType.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedMediaSource->GetUrl(), m_url.GetAddressOf()));

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveMediaSource::get_MimeType(HSTRING* value)
    {
        return m_mimeType.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaSource::put_MimeType(HSTRING value)
    {
        return m_mimeType.Set(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaSource::get_Url(HSTRING* value)
    {
        return m_url.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaSource::put_Url(HSTRING value)
    {
        return m_url.Set(value);
    }

    HRESULT AdaptiveMediaSource::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::MediaSource>& sharedMediaSource) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::MediaSource> mediaSource = std::make_shared<AdaptiveSharedNamespace::MediaSource>();

        mediaSource->SetMimeType(HStringToUTF8(m_mimeType.Get()));
        mediaSource->SetUrl(HStringToUTF8(m_url.Get()));

        sharedMediaSource = mediaSource;
        return S_OK;
    } CATCH_RETURN;
AdaptiveNamespaceEnd
