// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

//#include "AdaptiveCards.Rendering.WinUI3.h"
#include "IImageLoadTrackerListener.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3
{
    struct TrackedImageDetails : winrt::implements<TrackedImageDetails, IInspectable>
    {
        // TODO: add {} for initialization?
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage::ImageOpened_revoker imageOpenedRevoker{};
        winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage::ImageFailed_revoker imageFailedRevoker{};
    };

    struct ImageLoadTracker : winrt::implements<ImageLoadTracker, IInspectable>
    {
    public:
        ~ImageLoadTracker();
        void TrackBitmapImage(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& bitmapImage);
        void MarkFailedLoadBitmapImage(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& bitmapImage);

        void AbandonOutstandingImages();
        void AddListener(::AdaptiveCards::Rendering::WinUI3::IImageLoadTrackerListener const& listener);
        void RemoveListener(::AdaptiveCards::Rendering::WinUI3::IImageLoadTrackerListener const& listener);
        int GetTotalImagesTracked();

    private:
        Microsoft::WRL::Wrappers::SRWLock m_lock;
        int m_trackedImageCount = 0;
        int m_totalImageCount = 0;
        bool m_hasFailure = false;
        std::unordered_map<IInspectable, winrt::com_ptr<TrackedImageDetails>> m_eventRevokers;
        std::set<::AdaptiveCards::Rendering::WinUI3::IImageLoadTrackerListener> m_listeners;

        void TrackedImage_ImageLoaded(IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& eventArgs);
        void TrackedImage_ImageFailed(IInspectable const& sender, winrt::Windows::UI::Xaml::ExceptionRoutedEventArgs const& eventArgs);
        void ImageLoadResultReceived(IInspectable const& sender);

        // TODO: Do I need a const ref here? or just ref?
        void UnsubscribeFromEvents(IInspectable const& bitmapImage, winrt::com_ptr<TrackedImageDetails> const& trackedImageDetails);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
    };
}
