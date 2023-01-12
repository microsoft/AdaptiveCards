// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ImageLoadTracker.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    ImageLoadTracker::~ImageLoadTracker()
    {
        for (auto& [_, trackedBitmapImageDetails] : m_bitmapEventRevokers)
        {
            UnsubscribeFromEvents(trackedBitmapImageDetails);
        }
        for (auto& [_, trackedSvgImageDetails] : m_svgEventRevokers)
        {
            UnsubscribeFromEvents(trackedSvgImageDetails);
        }
    }

    void ImageLoadTracker::TrackImage(winrt::ImageSource const& image)
    {
        if (auto bitmapImage = image.try_as<winrt::BitmapImage>())
        {
            TrackBitmapImage(bitmapImage);
        }
        else
        {
            TrackSvgImage(image.as<winrt::SvgImageSource>());
        }
    }

    void ImageLoadTracker::TrackBitmapImage(winrt::BitmapImage const& bitmapImage)
    {
        auto trackedImageDetails = winrt::make_self<TrackedBitmapImageDetails>();

        trackedImageDetails->imageOpenedRevoker =
            bitmapImage.ImageOpened(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_BitmapImageLoaded});

        trackedImageDetails->imageFailedRevoker =
            bitmapImage.ImageFailed(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_BitmapImageFailed});

        // Ensure we don't try and write the private data from multiple threads
        std::unique_lock lock{m_mutex};

        if (m_bitmapEventRevokers.find(bitmapImage) == m_bitmapEventRevokers.end())
        {
            m_bitmapEventRevokers[bitmapImage] = trackedImageDetails;
            m_trackedImageCount++;
            m_totalImageCount++;
        }
    }

    void ImageLoadTracker::TrackSvgImage(winrt::SvgImageSource const& svgImage)
    {
        auto trackedSvgImageDetails = winrt::make_self<TrackedSvgImageDetails>();

        trackedSvgImageDetails->openedRevoker =
            svgImage.Opened(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_SvgImageLoaded});

        trackedSvgImageDetails->openFailedRevoker =
            svgImage.OpenFailed(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_SvgImageFailed});

        // Ensure we don't try and write the private data from multiple threads
        std::unique_lock lock{m_mutex};

        if (m_svgEventRevokers.find(svgImage) == m_svgEventRevokers.end())
        {
            m_svgEventRevokers[svgImage] = trackedSvgImageDetails;
            m_trackedImageCount++;
            m_totalImageCount++;
        }
    }

    void ImageLoadTracker::MarkFailedLoadImage(winrt::ImageSource const& image)
    {
        // Record failure
        m_hasFailure = true;

        // And then notify this image is done
        ImageLoadResultReceived(image);
    }

    void ImageLoadTracker::AbandonOutstandingImages()
    {
        std::unique_lock lock{m_mutex};
        for (auto& [_, trackedBitmapImageDetails] : m_bitmapEventRevokers)
        {
            UnsubscribeFromEvents(trackedBitmapImageDetails);
        }
        m_bitmapEventRevokers.clear();

        for (auto& [_, trackedSvgImageDetails] : m_svgEventRevokers)
        {
            UnsubscribeFromEvents(trackedSvgImageDetails);
        }
        m_svgEventRevokers.clear();
    }

    void ImageLoadTracker::AddListener(::AdaptiveCards::Rendering::Xaml_Rendering::IImageLoadTrackerListener* listener)
    {
        if (m_listeners.find(listener) == m_listeners.end())
        {
            m_listeners.emplace(listener);
        }
    }

    void ImageLoadTracker::RemoveListener(::AdaptiveCards::Rendering::Xaml_Rendering::IImageLoadTrackerListener* listener)
    {
        if (m_listeners.find(listener) != m_listeners.end())
        {
            m_listeners.erase(listener);
        }
    }

    int ImageLoadTracker::GetTotalImagesTracked()
    {
        return m_totalImageCount;
    }

    // Question: Is it safe to assume that sender will be a bitmapImage or svgImageSource for these methods?
    void ImageLoadTracker::TrackedImage_BitmapImageLoaded(winrt::IInspectable const& sender, winrt::RoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::TrackedImage_BitmapImageFailed(winrt::IInspectable const& sender, winrt::ExceptionRoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::TrackedImage_SvgImageLoaded(winrt::IInspectable const& sender, winrt::SvgImageSourceOpenedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::TrackedImage_SvgImageFailed(winrt::IInspectable const& sender, winrt::SvgImageSourceFailedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::ImageLoadResultReceived(winrt::IInspectable const& sender)
    {
        std::unique_lock lock{m_mutex};

        m_trackedImageCount--;

        // Check if the sender is a bitmap
        if (const auto bitmap = sender.try_as<winrt::BitmapImage>())
        {
            if (m_bitmapEventRevokers.find(bitmap) != m_bitmapEventRevokers.end())
            {
                UnsubscribeFromEvents(m_bitmapEventRevokers[bitmap]);
            }
        }
        else
        {
            // Otherwise, we have an svg
            if (m_svgEventRevokers.find(sender.as<winrt::SvgImageSource>()) != m_svgEventRevokers.end())
            {
                UnsubscribeFromEvents(m_svgEventRevokers[sender.as<winrt::SvgImageSource>()]);
            }
        }

        if (m_trackedImageCount == 0)
        {
            m_hasFailure ? FireImagesLoadingHadError() : FireAllImagesLoaded();
        }
    }

    void ImageLoadTracker::UnsubscribeFromEvents(winrt::com_ptr<TrackedBitmapImageDetails> const& trackedImageDetails)
    {
        trackedImageDetails->imageOpenedRevoker.revoke();
        trackedImageDetails->imageFailedRevoker.revoke();
    }

    void ImageLoadTracker::UnsubscribeFromEvents(winrt::com_ptr<TrackedSvgImageDetails> const& trackedSvgImageDetails)
    {
        trackedSvgImageDetails->openedRevoker.revoke();
        trackedSvgImageDetails->openFailedRevoker.revoke();
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
