// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ImageLoadTracker.h"

namespace AdaptiveCards::Rendering::Uwp
{
    ImageLoadTracker::~ImageLoadTracker()
    {
        for (auto& [_, trackedImageDetails] : m_eventRevokers)
        {
            UnsubscribeFromEvents(trackedImageDetails);
        }
    }

    void ImageLoadTracker::TrackBitmapImage(winrt::BitmapImage const& bitmapImage)
    {
        auto trackedImageDetails = winrt::make_self<TrackedImageDetails>();

        trackedImageDetails->imageOpenedRevoker =
            bitmapImage.ImageOpened(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_ImageLoaded});

        trackedImageDetails->imageFailedRevoker =
            bitmapImage.ImageFailed(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_ImageFailed});

        // Ensure we don't try and write the private data from multiple threads
        std::unique_lock lock{m_mutex};

        if (m_eventRevokers.find(bitmapImage) == m_eventRevokers.end())
        {
            m_eventRevokers[bitmapImage] = trackedImageDetails;
            m_trackedImageCount++;
            m_totalImageCount++;
        }
    }

    void ImageLoadTracker::MarkFailedLoadBitmapImage(winrt::BitmapImage const& bitmapImage)
    {
        // Record failure
        m_hasFailure = true;

        // And then notify this image is done
        ImageLoadResultReceived(bitmapImage);
    }

    void ImageLoadTracker::AbandonOutstandingImages()
    {
        std::unique_lock lock{m_mutex};
        for (auto& [_, trackedImageDetails] : m_eventRevokers)
        {
            UnsubscribeFromEvents(trackedImageDetails);
        }
        m_eventRevokers.clear();
    }

    void ImageLoadTracker::AddListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener)
    {
        if (m_listeners.find(listener) == m_listeners.end())
        {
            m_listeners.emplace(listener);
        }
    }

    void ImageLoadTracker::RemoveListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener)
    {
        if (m_listeners.find(listener) != m_listeners.end())
        {
            m_listeners.erase(listener);
        }
    }

    int ImageLoadTracker::GetTotalImagesTracked() { return m_totalImageCount; }

    void ImageLoadTracker::TrackedImage_ImageLoaded(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::TrackedImage_ImageFailed(winrt::IInspectable const& sender, winrt::ExceptionRoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::ImageLoadResultReceived(winrt::IInspectable const& sender)
    {
        std::unique_lock lock{m_mutex};

        m_trackedImageCount--;
        if (m_eventRevokers.find(sender) != m_eventRevokers.end())
        {
            UnsubscribeFromEvents(m_eventRevokers[sender]);
        }

        if (m_trackedImageCount == 0)
        {
            m_hasFailure ? FireImagesLoadingHadError() : FireAllImagesLoaded();
        }
    }

    void ImageLoadTracker::UnsubscribeFromEvents(winrt::com_ptr<TrackedImageDetails> const& trackedImageDetails)
    {
        trackedImageDetails->imageOpenedRevoker.revoke();
        trackedImageDetails->imageFailedRevoker.revoke();
    }

    void ImageLoadTracker::FireAllImagesLoaded()
    {
        for (auto listener : m_listeners)
        {
            listener->AllImagesLoaded();
        }
    }

    void ImageLoadTracker::FireImagesLoadingHadError()
    {
        for (auto listener : m_listeners)
        {
            listener->ImagesLoadingHadError();
        }
    }
}
