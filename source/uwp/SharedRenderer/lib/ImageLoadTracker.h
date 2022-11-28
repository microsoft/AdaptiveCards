// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "IImageLoadTrackerListener.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    // Q: Can we have TrackedImageDetails and TrackedSvgImageDetails extend a base class?
    // If we do this, we could just store one map of the image details
    struct TrackedBitmapImageDetails : winrt::implements<TrackedBitmapImageDetails, winrt::IInspectable>
    {
        winrt::xaml_media_imaging::BitmapImage::ImageOpened_revoker imageOpenedRevoker{};
        winrt::xaml_media_imaging::BitmapImage::ImageFailed_revoker imageFailedRevoker{};
    };

    struct TrackedSvgImageDetails : winrt::implements<TrackedSvgImageDetails, winrt::IInspectable>
    {
        winrt::xaml_media_imaging::SvgImageSource::Opened_revoker openedRevoker{};
        winrt::xaml_media_imaging::SvgImageSource::OpenFailed_revoker openFailedRevoker{};
    };

    struct ImageLoadTracker : winrt::implements<ImageLoadTracker, winrt::IInspectable>
    {
    public:
        ~ImageLoadTracker();
        void TrackImage(winrt::ImageSource const& image);
        void TrackBitmapImage(winrt::xaml_media_imaging::BitmapImage const& bitmapImage);
        void TrackSvgImage(winrt::xaml_media_imaging::SvgImageSource const& svgImage);

        void MarkFailedLoadImage(winrt::ImageSource const& image);

        void AbandonOutstandingImages();
        void AddListener(IImageLoadTrackerListener* listener);
        void RemoveListener(IImageLoadTrackerListener* listener);
        int GetTotalImagesTracked();

    private:
        std::mutex m_mutex;
        int m_trackedImageCount = 0;
        int m_totalImageCount = 0;
        bool m_hasFailure = false;
        std::unordered_map<winrt::IInspectable, winrt::com_ptr<TrackedBitmapImageDetails>> m_bitmapEventRevokers;
        std::unordered_map<winrt::IInspectable, winrt::com_ptr<TrackedSvgImageDetails>> m_svgEventRevokers;

        std::set<IImageLoadTrackerListener*> m_listeners;

        void TrackedImage_BitmapImageLoaded(winrt::IInspectable const& sender,
                                      winrt::RoutedEventArgs const& eventArgs);
        void TrackedImage_BitmapImageFailed(winrt::IInspectable const& sender,
                                      winrt::ExceptionRoutedEventArgs const& eventArgs);

        void TrackedImage_SvgImageLoaded(winrt::IInspectable const& sender, winrt::xaml_media_imaging::SvgImageSourceOpenedEventArgs const& eventArgs);
        void TrackedImage_SvgImageFailed(winrt::IInspectable const& sender, winrt::xaml_media_imaging::SvgImageSourceFailedEventArgs const& eventArgs);

        void ImageLoadResultReceived(winrt::IInspectable const& sender);

        void UnsubscribeFromEvents(winrt::com_ptr<TrackedBitmapImageDetails> const& trackedImageDetails);
        void UnsubscribeFromEvents(winrt::com_ptr<TrackedSvgImageDetails> const& trackedSvgImageDetails);

        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
