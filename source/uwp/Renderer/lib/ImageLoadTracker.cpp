// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ImageLoadTracker.h"

namespace AdaptiveCards::Rendering::Uwp
{
    ImageLoadTracker::~ImageLoadTracker()
    {
        for (auto& eventRegistration : m_eventRevokers)
        {
            UnsubscribeFromEvents(eventRegistration.first, eventRegistration.second);
        }
    }

    void ImageLoadTracker::TrackBitmapImage(rtxaml::Media::Imaging::BitmapImage const& bitmapImage)
    {
        // TODO: Am I doing this right?
        auto trackedImageDetails = winrt::make_self<TrackedImageDetails>();

        // TODO: are these revokers correct?
        trackedImageDetails->imageOpenedRevoker =
            bitmapImage.ImageOpened(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_ImageLoaded});

        trackedImageDetails->imageFailedRevoker =
            bitmapImage.ImageFailed(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_ImageFailed});

        // Ensure we don't try and write the private data from multiple threads
        // TODO: I can also use scoped_lock but as I understand - scope lock is usually used for multiple mutexes
        std::unique_lock lock{m_mutex};

        if (m_eventRevokers.find(bitmapImage) == m_eventRevokers.end())
        {
            // If we haven't registered for this image events yet, do so
            // TODO: I'm not sure if this is the right way.... com_ptr to imageDetails, weird..
            m_eventRevokers[bitmapImage] = trackedImageDetails;
            m_trackedImageCount++;
            m_totalImageCount++;
        }
    }

    void ImageLoadTracker::MarkFailedLoadBitmapImage(rtxaml::Media::Imaging::BitmapImage const& bitmapImage)
    {
        // Record failure
        m_hasFailure = true;

        // And then notify this image is done
        ImageLoadResultReceived(bitmapImage);
    }

    void ImageLoadTracker::AbandonOutstandingImages()
    {
        // TODO: will scoped lock work here?
        std::unique_lock lock{m_mutex};
        for (auto& eventRegistration : m_eventRevokers)
        {
            UnsubscribeFromEvents(eventRegistration.first, eventRegistration.second);
        }
        m_eventRevokers.clear();
    }

    void ImageLoadTracker::AddListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener)
    {
        try
        {
            if (m_listeners.find(listener) == m_listeners.end())
            {
                m_listeners.emplace(listener);
            }

            // TODO: COME BACK AND FIX IT
            // if (m_listeners.find(listener) == m_listeners.end())
            //{
            //    m_listeners.emplace(listener);
            //}
            // else
            //{
            //    /*return E_INVALIDARG;*/
            //    // TODO: do we wanna return bool may be? indicating success/failure? do we need to at all?
            //}
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
        }
    }

    void ImageLoadTracker::RemoveListener(::AdaptiveCards::Rendering::Uwp::IImageLoadTrackerListener* listener)
    {
        try
        {
            if (m_listeners.find(listener) != m_listeners.end())
            {
                m_listeners.erase(listener);
            }
            // TODO: COME BACK AND FIX IT
            // if (m_listeners.find(listener) != m_listeners.end())
            //{
            //    m_listeners.erase(listener);
            //}
            // else
            //{
            //    /*  return E_INVALIDARG;*/
            //    // TODO: do we wanna return bool may be? indicating success/failure? do we need to at all?
            //}
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
        }
    }

    int ImageLoadTracker::GetTotalImagesTracked() { return m_totalImageCount; }

    void ImageLoadTracker::TrackedImage_ImageLoaded(winrt::Windows::Foundation::IInspectable const& sender,
                                                    rtxaml::RoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::TrackedImage_ImageFailed(winrt::Windows::Foundation::IInspectable const& sender,
                                                    rtxaml::ExceptionRoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::ImageLoadResultReceived(winrt::Windows::Foundation::IInspectable const& sender)
    {
        std::unique_lock lock {m_mutex};

        m_trackedImageCount--;
        if (m_eventRevokers.find(sender) != m_eventRevokers.end())
        {
            UnsubscribeFromEvents(sender, m_eventRevokers[sender]);
        }

        if (m_trackedImageCount == 0)
        {
            m_hasFailure ? FireImagesLoadingHadError() : FireAllImagesLoaded();
        }
    }

    void ImageLoadTracker::UnsubscribeFromEvents(winrt::Windows::Foundation::IInspectable const& bitmapImage,
                                                 winrt::com_ptr<TrackedImageDetails> const& trackedImageDetails)
    {
        // TODO: this is the right way to do it, correct?
        // TODO: should we use events instead?
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
