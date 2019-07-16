// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveMediaSource
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveMediaSource,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveMediaSource);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::MediaSource>& sharedMediaSource);

        // IAdaptiveMediaSource
        IFACEMETHODIMP get_MimeType(_Outptr_ HSTRING* mimeType);
        IFACEMETHODIMP put_MimeType(_In_ HSTRING mimeType);

        IFACEMETHODIMP get_Url(_Outptr_ HSTRING* url);
        IFACEMETHODIMP put_Url(_In_ HSTRING url);

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::MediaSource>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_mimeType;
        Microsoft::WRL::Wrappers::HString m_url;
    };

    ActivatableClass(AdaptiveMediaSource);
}
