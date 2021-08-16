// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "BackgroundImage.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("60F8A683-A7A3-4E34-BE86-C809F61BD5B6") AdaptiveBackgroundImage
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveBackgroundImage,
                                              Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveBackgroundImage);

    public:
        AdaptiveBackgroundImage();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::BackgroundImage>& sharedImage);

        IFACEMETHODIMP get_Url(_Outptr_ HSTRING* url);
        IFACEMETHODIMP put_Url(_In_ HSTRING url);

        IFACEMETHODIMP get_FillMode(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode* fillMode);
        IFACEMETHODIMP put_FillMode(ABI::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode fillMode);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment* HorizontalAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment HorizontalAlignment);

        IFACEMETHODIMP get_VerticalAlignment(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::VAlignment* VerticalAlignment);
        IFACEMETHODIMP put_VerticalAlignment(ABI::AdaptiveCards::ObjectModel::Uwp::VAlignment VerticalAlignment);

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::BackgroundImage>& sharedModel);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::Wrappers::HString m_url;
        ABI::AdaptiveCards::ObjectModel::Uwp::BackgroundImageFillMode m_fillMode;
        ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment m_horizontalAlignment;
        ABI::AdaptiveCards::ObjectModel::Uwp::VAlignment m_verticalAlignment;
    };
    ActivatableClass(AdaptiveBackgroundImage);
}
