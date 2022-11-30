// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "IImageLoadTrackerListener.h"

namespace AdaptiveCards::Rendering::Uwp
{
    struct TrackedImageDetails : winrt::implements<TrackedImageDetails, winrt::IInspectable>
    {
        winrt::BitmapImage::ImageOpened_revoker imageOpenedRevoker{};
        winrt::BitmapImage::ImageFailed_revoker imageFailedRevoker{};
    };

    struct TrackedSvgImageDetails : winrt::implements<TrackedImageDetails, winrt::IInspectable>
    {
        winrt::SvgImageSource::Opened_revoker openedRevoker{};
        winrt::SvgImageSource::OpenFailed_revoker openFailedRevoker{};
    };

    struct ImageLoadTracker : winrt::implements<ImageLoadTracker, winrt::IInspectable>
    {
    public:
        ~ImageLoadTracker();
        void TrackBitmapImage(winrt::BitmapImage const& bitmapImage);
        void TrackSvgImage(winrt::SvgImageSource const& svgImage);

        void MarkFailedLoadBitmapImage(winrt::BitmapImage const& bitmapImage);
        void MarkFailedLoadSvgImage(winrt::SvgImageSource const& svgImage);

        void AbandonOutstandingImages();
        void AddListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener);
        void RemoveListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener);
        int GetTotalImagesTracked();

    private:
        std::mutex m_mutex;
        int m_trackedImageCount = 0;
        int m_totalImageCount = 0;
        bool m_hasFailure = false;
        std::unordered_map<winrt::IInspectable, winrt::com_ptr<TrackedImageDetails>> m_eventRevokers;
        std::unordered_map<winrt::IInspectable, winrt::com_ptr<TrackedSvgImageDetails>> m_svgEventRevokers;

        std::set<::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener*> m_listeners;

        void TrackedImage_BitmapImageLoaded(winrt::IInspectable const& sender,
                                      winrt::RoutedEventArgs const& eventArgs);
        void TrackedImage_BitmapImageFailed(winrt::IInspectable const& sender,
                                      winrt::ExceptionRoutedEventArgs const& eventArgs);

        void TrackedImage_SvgImageLoaded(winrt::IInspectable const& sender, winrt::SvgImageSourceOpenedEventArgs const& eventArgs);
        void TrackedImage_SvgImageFailed(winrt::IInspectable const& sender, winrt::SvgImageSourceFailedEventArgs const& eventArgs);

        void ImageLoadResultReceived(winrt::IInspectable const& sender);

        void UnsubscribeFromEvents(winrt::com_ptr<TrackedImageDetails> const& trackedImageDetails);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
