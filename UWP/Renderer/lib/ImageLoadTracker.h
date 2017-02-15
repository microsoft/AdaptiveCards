#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    struct TrackedImageDetails
    {
        EventRegistrationToken imageOpenedRegistration;
        EventRegistrationToken imageFailedRegistration;
    };

    class ImageLoadTracker
    {
    public:
        ~ImageLoadTracker();
        void TrackBitmapImage(_In_ ABI::Windows::UI::Xaml::Media::Imaging::IBitmapImage* bitmapImage);

    private:
        Microsoft::WRL::Wrappers::SRWLock m_lock;
        int m_trackedImageCount = 0;
        std::unordered_map<IInspectable*, TrackedImageDetails> m_eventRegistrations;

        HRESULT trackedImage_ImageLoaded(_In_ IInspectable* sender, _In_ ABI::Windows::UI::Xaml::IRoutedEventArgs* eventArgs);
        HRESULT trackedImage_ImageFailed(_In_ IInspectable* sender, _In_ ABI::Windows::UI::Xaml::IExceptionRoutedEventArgs* eventArgs);
        void ImageLoadResultReceived(_In_ IInspectable* sender);
        void UnsubscribeFromEvents(_In_ IInspectable* bitmapImage, _In_ TrackedImageDetails& trackedImageDetails);
    };
}}