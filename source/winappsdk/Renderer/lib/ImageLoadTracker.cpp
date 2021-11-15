// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ImageLoadTracker.h"

#include <wrl\event.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveCards::Rendering::WinUI3
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
        /*ComPtr<IBitmapImage> localBitmapImage(bitmapImage);*/
        // TODO: Am I doing this right?
        auto trackedImageDetails = winrt::make_self<TrackedImageDetails>();

        /* ComPtr<IRoutedEventHandler> imageOpenedEventHandler =
             Microsoft::WRL::Callback<IRoutedEventHandler, ImageLoadTracker>(this, &ImageLoadTracker::TrackedImage_ImageLoaded);
         THROW_IF_FAILED(bitmapImage->add_ImageOpened(imageOpenedEventHandler.Get(), &trackedImageDetails.imageOpenedRegistration));*/

        /*ComPtr<IExceptionRoutedEventHandler> imageFailedEventHandler =
            Microsoft::WRL::Callback<IExceptionRoutedEventHandler, ImageLoadTracker>(this,
        &ImageLoadTracker::trackedImage_ImageFailed); THROW_IF_FAILED(bitmapImage->add_ImageFailed(imageFailedEventHandler.Get(),
        &trackedImageDetails.imageFailedRegistration));*/

        trackedImageDetails->imageOpenedRevoker =
            bitmapImage.ImageOpened(winrt::auto_revoke, {this, &ImageLoadTracker::TrackedImage_ImageLoaded});

        // Ensure we don't try and write the private data from multiple threads
        auto exclusiveLock = m_lock.LockExclusive();

        /*ComPtr<winrt::Windows::Foundation::IInspectable> inspectableBitmapImage;
        THROW_IF_FAILED(localBitmapImage.As(&inspectableBitmapImage));*/
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
        /*ComPtr<IBitmapImage> localBitmapImage(bitmapImage);
        ComPtr<winrt::Windows::Foundation::IInspectable> inspectableBitmapImage;
        THROW_IF_FAILED(localBitmapImage.As(&inspectableBitmapImage));
        ImageLoadResultReceived(inspectableBitmapImage.Get());*/
        ImageLoadResultReceived(bitmapImage);
    }

    void ImageLoadTracker::AbandonOutstandingImages()
    {
        auto exclusiveLock = m_lock.LockExclusive();
        for (auto& eventRegistration : m_eventRevokers)
        {
            UnsubscribeFromEvents(eventRegistration.first, eventRegistration.second);
        }
        m_eventRevokers.clear();
    }

    void ImageLoadTracker::AddListener(::AdaptiveCards::Rendering::WinUI3::IImageLoadTrackerListener* listener)
    {
        try
        {
            if (m_listeners.find(listener) == m_listeners.end())
            {
                m_listeners.emplace(listener);
            }
            else
            {
                /*return E_INVALIDARG;*/
                // TODO: do we wanna return bool may be? indicating success/failure? do we need to at all?
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
        }
    }

    void ImageLoadTracker::RemoveListener(::AdaptiveCards::Rendering::WinUI3::IImageLoadTrackerListener* listener)
    {
        try
        {
            if (m_listeners.find(listener) != m_listeners.end())
            {
                m_listeners.erase(listener);
            }
            else
            {
                /*  return E_INVALIDARG;*/
                // TODO: do we wanna return bool may be? indicating success/failure? do we need to at all?
            }
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
        }
    }

    int ImageLoadTracker::GetTotalImagesTracked() { return m_totalImageCount; }

    void ImageLoadTracker::TrackedImage_ImageLoaded(winrt::Windows::Foundation::IInspectable const& sender, rtxaml::RoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::TrackedImage_ImageFailed(winrt::Windows::Foundation::IInspectable const& sender, rtxaml::ExceptionRoutedEventArgs const& /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
    }

    void ImageLoadTracker::ImageLoadResultReceived(winrt::Windows::Foundation::IInspectable const& sender)
    {
        auto exclusiveLock = m_lock.LockExclusive();
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

    void ImageLoadTracker::UnsubscribeFromEvents(winrt::Windows::Foundation::IInspectable const& bitmapImage, winrt::com_ptr<TrackedImageDetails> const& trackedImageDetails)
    {
        /*ComPtr<winrt::Windows::Foundation::IInspectable> inspectableBitmapImage(bitmapImage);
        ComPtr<IBitmapImage> localBitmapImage;
        inspectableBitmapImage.As(&localBitmapImage);*/

        // Best effort, ignore returns
        // if (const auto localBitMapImage = bitmapImage.try_as<rtxaml::Media::Imaging::BitmapImage>())
        //{
        //   /* localBitmapImage->remove_ImageOpened(trackedImageDetails.imageOpenedRegistration);
        //    localBitmapImage->remove_ImageFailed(trackedImageDetails.imageFailedRegistration);*/
        //    localBitMapImage.re
        //}
        // TODO: this is the right way to do it, correct?
        // TODO: should we use events instead?
        trackedImageDetails->imageOpenedRevoker.revoke();
        trackedImageDetails->imageFailedRevoker.revoke();
    }

    void ImageLoadTracker::FireAllImagesLoaded()
    {
        for (auto listener : m_listeners)
        {
            // TODO: solve these listeners
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
