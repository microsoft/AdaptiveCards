// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "IImageLoadTrackerListener.h"

namespace AdaptiveCards::Rendering::Uwp
{
    struct TrackedImageDetails : winrt::implements<TrackedImageDetails, ::IInspectable>
    {
        // TODO: add {} for initialization?
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage::ImageOpened_revoker imageOpenedRevoker{};
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage::ImageFailed_revoker imageFailedRevoker{};
    };

    struct ImageLoadTracker : winrt::implements<ImageLoadTracker, ::IInspectable>
    {
    public:
        ~ImageLoadTracker();
        void TrackBitmapImage(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& bitmapImage);
        void MarkFailedLoadBitmapImage(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& bitmapImage);

        void AbandonOutstandingImages();
        void AddListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener);
        void RemoveListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener);
        int GetTotalImagesTracked();

    private:
        std::mutex m_lock;
        int m_trackedImageCount = 0;
        int m_totalImageCount = 0;
        bool m_hasFailure = false;
        std::unordered_map<winrt::Windows::Foundation::IInspectable, winrt::com_ptr<TrackedImageDetails>> m_eventRevokers;
        std::set<::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener*> m_listeners;

        void TrackedImage_ImageLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& eventArgs);
        void TrackedImage_ImageFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::ExceptionRoutedEventArgs const& eventArgs);
        void ImageLoadResultReceived(winrt::Windows::Foundation::IInspectable const& sender);

        // TODO: Do I need a const ref here? or just ref?
        void UnsubscribeFromEvents(winrt::Windows::Foundation::IInspectable const& bitmapImage, winrt::com_ptr<TrackedImageDetails> const& trackedImageDetails);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
