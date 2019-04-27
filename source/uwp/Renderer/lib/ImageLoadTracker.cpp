// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ImageLoadTracker.h"

#include <wrl\event.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveNamespace
{
    ImageLoadTracker::~ImageLoadTracker()
    {
        for (auto& eventRegistration : m_eventRegistrations)
        {
            UnsubscribeFromEvents(eventRegistration.first, eventRegistration.second);
        }
    }

    void ImageLoadTracker::TrackBitmapImage(_In_ IBitmapImage* bitmapImage)
    {
        ComPtr<IBitmapImage> localBitmapImage(bitmapImage);
        TrackedImageDetails trackedImageDetails;

        ComPtr<IRoutedEventHandler> imageOpenedEventHandler =
            Microsoft::WRL::Callback<IRoutedEventHandler, ImageLoadTracker>(this, &ImageLoadTracker::trackedImage_ImageLoaded);
        THROW_IF_FAILED(bitmapImage->add_ImageOpened(imageOpenedEventHandler.Get(), &trackedImageDetails.imageOpenedRegistration));
        ComPtr<IExceptionRoutedEventHandler> imageFailedEventHandler =
            Microsoft::WRL::Callback<IExceptionRoutedEventHandler, ImageLoadTracker>(this, &ImageLoadTracker::trackedImage_ImageFailed);
        THROW_IF_FAILED(bitmapImage->add_ImageFailed(imageFailedEventHandler.Get(), &trackedImageDetails.imageFailedRegistration));

        // Ensure we don't try and write the private data from multiple threads
        auto exclusiveLock = m_lock.LockExclusive();

        ComPtr<IInspectable> inspectableBitmapImage;
        THROW_IF_FAILED(localBitmapImage.As(&inspectableBitmapImage));
        if (m_eventRegistrations.find(inspectableBitmapImage.Get()) == m_eventRegistrations.end())
        {
            // If we haven't registered for this image events yet, do so
            m_eventRegistrations[inspectableBitmapImage.Get()] = trackedImageDetails;
            m_trackedImageCount++;
            m_totalImageCount++;
        }
    }

    void ImageLoadTracker::MarkFailedLoadBitmapImage(_In_ IBitmapImage* bitmapImage)
    {
        // Record failure
        m_hasFailure = true;

        // And then notify this image is done
        ComPtr<IBitmapImage> localBitmapImage(bitmapImage);
        ComPtr<IInspectable> inspectableBitmapImage;
        THROW_IF_FAILED(localBitmapImage.As(&inspectableBitmapImage));
        ImageLoadResultReceived(inspectableBitmapImage.Get());
    }

    void ImageLoadTracker::AbandonOutstandingImages()
    {
        auto exclusiveLock = m_lock.LockExclusive();
        for (auto& eventRegistration : m_eventRegistrations)
        {
            UnsubscribeFromEvents(eventRegistration.first, eventRegistration.second);
        }
        m_eventRegistrations.clear();
    }

    HRESULT ImageLoadTracker::AddListener(_In_ IImageLoadTrackerListener* listener) try
    {
        if (m_listeners.find(listener) == m_listeners.end())
        {
            m_listeners.emplace(listener);
        }
        else
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT ImageLoadTracker::RemoveListener(_In_ IImageLoadTrackerListener* listener) try
    {
        if (m_listeners.find(listener) != m_listeners.end())
        {
            m_listeners.erase(listener);
        }
        else
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }
    CATCH_RETURN;

    int ImageLoadTracker::GetTotalImagesTracked() { return m_totalImageCount; }

    HRESULT ImageLoadTracker::trackedImage_ImageLoaded(_In_ IInspectable* sender, _In_ IRoutedEventArgs* /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
        return S_OK;
    }

    HRESULT ImageLoadTracker::trackedImage_ImageFailed(_In_ IInspectable* sender, _In_ IExceptionRoutedEventArgs* /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
        return S_OK;
    }

    void ImageLoadTracker::ImageLoadResultReceived(_In_ IInspectable* sender)
    {
        auto exclusiveLock = m_lock.LockExclusive();
        m_trackedImageCount--;
        if (m_eventRegistrations.find(sender) != m_eventRegistrations.end())
        {
            UnsubscribeFromEvents(sender, m_eventRegistrations[sender]);
        }

        if (m_trackedImageCount == 0)
        {
            m_hasFailure ? FireImagesLoadingHadError() : FireAllImagesLoaded();
        }
    }

    void ImageLoadTracker::UnsubscribeFromEvents(_In_ IInspectable* bitmapImage, TrackedImageDetails& trackedImageDetails)
    {
        ComPtr<IInspectable> inspectableBitmapImage(bitmapImage);
        ComPtr<IBitmapImage> localBitmapImage;
        inspectableBitmapImage.As(&localBitmapImage);

        // Best effort, ignore returns
        localBitmapImage->remove_ImageOpened(trackedImageDetails.imageOpenedRegistration);
        localBitmapImage->remove_ImageFailed(trackedImageDetails.imageFailedRegistration);
    }

    void ImageLoadTracker::FireAllImagesLoaded()
    {
        for (auto& listener : m_listeners)
        {
            listener->AllImagesLoaded();
        }
    }

    void ImageLoadTracker::FireImagesLoadingHadError()
    {
        for (auto& listener : m_listeners)
        {
            listener->ImagesLoadingHadError();
        }
    }
}
