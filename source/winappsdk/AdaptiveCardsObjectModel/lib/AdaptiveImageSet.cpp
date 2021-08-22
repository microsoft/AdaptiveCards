// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSet.h"
#include "AdaptiveImage.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    AdaptiveImageSet::AdaptiveImageSet()
    {
        m_images = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveImage*>>();
    }

    HRESULT AdaptiveImageSet::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ImageSet> imageSet = std::make_shared<AdaptiveCards::ImageSet>();
        return RuntimeClassInitialize(imageSet);
    }
    CATCH_RETURN();

    HRESULT AdaptiveImageSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ImageSet>& sharedImageSet)
    try
    {
        if (sharedImageSet == nullptr)
        {
            return E_INVALIDARG;
        }

        GenerateImagesProjection(sharedImageSet->GetImages(), m_images.Get());

        m_imageSize = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize>(sharedImageSet->GetImageSize());

        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedImageSet));
        return S_OK;
    }
    CATCH_RETURN();

    IFACEMETHODIMP AdaptiveImageSet::get_Images(_COM_Outptr_ IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveImage*>** images)
    {
        return m_images.CopyTo(images);
    }

    HRESULT AdaptiveImageSet::get_ImageSize(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    HRESULT AdaptiveImageSet::put_ImageSize(ABI::AdaptiveCards::ObjectModel::WinUI3::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveImageSet::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::ImageSet;
        return S_OK;
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveImageSet::GetSharedModel()
    {
        auto imageSet = std::make_shared<AdaptiveCards::ImageSet>();

        THROW_IF_FAILED(CopySharedElementProperties(*imageSet));

        imageSet->SetImageSize(static_cast<AdaptiveCards::ImageSize>(m_imageSize));

        THROW_IF_FAILED(GenerateSharedImages(m_images.Get(), imageSet->GetImages()));

        return imageSet;
    }
}
