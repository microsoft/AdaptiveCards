// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "IImageLoadTrackerListener.h"

namespace AdaptiveNamespace
{
    struct TrackedImageDetails
    {
        EventRegistrationToken imageOpenedRegistration;
        EventRegistrationToken imageFailedRegistration;
    };

    class ImageLoadTracker
    {
    public:
        ~ImageLoadTracker();
        void TrackBitmapImage(_In_ ABI::Windows::UI::Xaml::Media::Imaging::IBitmapImage* bitmapImage);
        void MarkFailedLoadBitmapImage(_In_ ABI::Windows::UI::Xaml::Media::Imaging::IBitmapImage* bitmapImage);

        void AbandonOutstandingImages();
        HRESULT AddListener(_In_ IImageLoadTrackerListener* listener);
        HRESULT RemoveListener(_In_ IImageLoadTrackerListener* listener);
        int GetTotalImagesTracked();

    private:
        Microsoft::WRL::Wrappers::SRWLock m_lock;
        int m_trackedImageCount = 0;
        int m_totalImageCount = 0;
        bool m_hasFailure = false;
        std::unordered_map<IInspectable*, TrackedImageDetails> m_eventRegistrations;
        std::set<Microsoft::WRL::ComPtr<IImageLoadTrackerListener>> m_listeners;

        HRESULT trackedImage_ImageLoaded(_In_ IInspectable* sender, _In_ ABI::Windows::UI::Xaml::IRoutedEventArgs* eventArgs);
        HRESULT trackedImage_ImageFailed(_In_ IInspectable* sender, _In_ ABI::Windows::UI::Xaml::IExceptionRoutedEventArgs* eventArgs);
        void ImageLoadResultReceived(_In_ IInspectable* sender);
        void UnsubscribeFromEvents(_In_ IInspectable* bitmapImage, TrackedImageDetails& trackedImageDetails);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
