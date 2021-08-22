// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveMedia.h"
#include "AdaptiveMediaSource.h"
#include "Vector.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    HRESULT AdaptiveMedia::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::Media> media = std::make_shared<AdaptiveCards::Media>();
        return RuntimeClassInitialize(media);
    }
    CATCH_RETURN;

    HRESULT AdaptiveMedia::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Media>& sharedMedia)
    try
    {
        if (sharedMedia == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedMedia->GetPoster(), m_poster.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedMedia->GetAltText(), m_altText.GetAddressOf()));

        m_sources = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMediaSource*>>();

        GenerateMediaSourcesProjection(sharedMedia->GetSources(), m_sources.Get());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedMedia));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveMedia::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::Media;
        return S_OK;
    }

    HRESULT AdaptiveMedia::get_Poster(_Outptr_ HSTRING* value) { return m_poster.CopyTo(value); }

    HRESULT AdaptiveMedia::put_Poster(_In_ HSTRING value) { return m_poster.Set(value); }

    HRESULT AdaptiveMedia::get_AltText(_Outptr_ HSTRING* value) { return m_altText.CopyTo(value); }

    HRESULT AdaptiveMedia::put_AltText(_In_ HSTRING value) { return m_altText.Set(value); }

    HRESULT AdaptiveMedia::get_Sources(_COM_Outptr_ IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMediaSource*>** sources)
    {
        return m_sources.CopyTo(sources);
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveMedia::GetSharedModel()
    {
        auto media = std::make_shared<AdaptiveCards::Media>();

        THROW_IF_FAILED(CopySharedElementProperties(*media));

        media->SetPoster(HStringToUTF8(m_poster.Get()));
        media->SetAltText(HStringToUTF8(m_altText.Get()));

        THROW_IF_FAILED(GenerateSharedMediaSources(m_sources.Get(), media->GetSources()));

        return media;
    }
}
