#include "pch.h"
#include "ImageLoadTracker.h"

#include <wrl\event.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    ImageLoadTracker::~ImageLoadTracker()
    {
        for (auto& eventRegistration : m_eventRegistrations)
        {
            UnsubscribeFromEvents(eventRegistration.first, eventRegistration.second);
        }
    }

    _Use_decl_annotations_
    void ImageLoadTracker::TrackBitmapImage(IBitmapImage* bitmapImage)
    {
        ComPtr<IBitmapImage> localBitmapImage(bitmapImage);
        TrackedImageDetails trackedImageDetails;

        ComPtr<IRoutedEventHandler> imageOpenedEventHandler = Microsoft::WRL::Callback<IRoutedEventHandler, ImageLoadTracker>(this, &ImageLoadTracker::trackedImage_ImageLoaded);
        THROW_IF_FAILED(bitmapImage->add_ImageOpened(imageOpenedEventHandler.Get(), &trackedImageDetails.imageOpenedRegistration));
        ComPtr<IExceptionRoutedEventHandler> imageFailedEventHandler = Microsoft::WRL::Callback<IExceptionRoutedEventHandler, ImageLoadTracker>(this, &ImageLoadTracker::trackedImage_ImageFailed);
        THROW_IF_FAILED(bitmapImage->add_ImageFailed(imageFailedEventHandler.Get(), &trackedImageDetails.imageFailedRegistration));

        // Ensure we donn't try and write the private data from multiple threads
        auto exclusiveLock = m_lock.LockExclusive();

        ComPtr<IInspectable> inspectableBitmapImage;
        THROW_IF_FAILED(localBitmapImage.As(&inspectableBitmapImage));
        if (m_eventRegistrations.find(inspectableBitmapImage.Get()) == m_eventRegistrations.end())
        {
            // If we haven't registered for this image events yet, do so
            m_eventRegistrations[inspectableBitmapImage.Get()] = trackedImageDetails;
            m_trackedImageCount++;
        }
    }

    _Use_decl_annotations_
    HRESULT ImageLoadTracker::trackedImage_ImageLoaded(IInspectable* sender, IRoutedEventArgs* /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
        return S_OK;
    }
    
    _Use_decl_annotations_
    HRESULT ImageLoadTracker::trackedImage_ImageFailed(IInspectable* sender, IExceptionRoutedEventArgs* /*eventArgs*/)
    {
        ImageLoadResultReceived(sender);
        return S_OK;
    }

    _Use_decl_annotations_
    void ImageLoadTracker::ImageLoadResultReceived(IInspectable* sender)
    {
        auto exclusiveLock = m_lock.LockExclusive();
        m_trackedImageCount--;
        if (m_eventRegistrations.find(sender) != m_eventRegistrations.end())
        {
            UnsubscribeFromEvents(sender, m_eventRegistrations[sender]);
        }
    }

    _Use_decl_annotations_
    void ImageLoadTracker::UnsubscribeFromEvents(IInspectable* bitmapImage, TrackedImageDetails& trackedImageDetails)
    {
        auto exclusiveLock = m_lock.LockExclusive();
        ComPtr<IInspectable> inspectableBitmapImage(bitmapImage);
        ComPtr<IBitmapImage> localBitmapImage;
        inspectableBitmapImage.As(&localBitmapImage);

        // Best effort, ignore returns
        localBitmapImage->remove_ImageOpened(trackedImageDetails.imageOpenedRegistration);
        localBitmapImage->remove_ImageFailed(trackedImageDetails.imageFailedRegistration);
    }

}}