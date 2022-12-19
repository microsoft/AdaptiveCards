#include "pch.h"
#include "ImageBuilder.h"

namespace AdaptiveCards::Rendering::Uwp
{
    //
    // Methods for the base class implementation
    //
    void ImageBuilder::CreateImage() { return; }

    void ImageBuilder::AssignBitmapOptions(winrt::BitmapCreateOptions const& /*option*/)
    {
        // do nothing in base implementation
    }

    void ImageBuilder::SetAsyncSource(winrt::IRandomAccessStream const& /*randomAccessStream*/,
                                      bool /*isAutoSize*/,
                                      std::function<void()> /*callback*/)
    {
        // do nothing in base implementation
        return;
    }

    void ImageBuilder::SetUriSource(winrt::Uri const& /*imageUrl*/)
    {
        // do nothing in base implementation
    }

    // return generic imageSource by default
    winrt::ImageSource ImageBuilder::GetImage() { return winrt::BitmapImage{}; }

    //
    // Methods for the BitmapImage implementation
    //
    void BitmapImageBuilder::CreateImage() { m_image = winrt::BitmapImage{}; }

    void BitmapImageBuilder::AssignBitmapOptions(winrt::BitmapCreateOptions const& option)
    {
        m_image.CreateOptions(option);
    }
    
    void BitmapImageBuilder::SetAsyncSource(winrt::IRandomAccessStream const& randomAccessStream,
                                            bool isAutoSize,
                                            std::function<void()> callback)
    {
        auto setSourceAction = m_image.SetSourceAsync(randomAccessStream);

        setSourceAction.Completed(
            [isAutoSize, callback](winrt::IAsyncAction const&, winrt::AsyncStatus status)
            {
                if (status == winrt::AsyncStatus::Completed && isAutoSize)
                {
                    callback();
                }
            });
    }

    void BitmapImageBuilder::SetUriSource(winrt::Uri const& imageUrl) { m_image.UriSource(imageUrl); }

    winrt::ImageSource BitmapImageBuilder::GetImage() { return m_image; }

    //
    // Methods for the SvgImageSource implementation
    //
    void SvgImageBuilder::CreateImage() { m_image = winrt::SvgImageSource{}; }
    
    void SvgImageBuilder::SetAsyncSource(winrt::IRandomAccessStream const& randomAccessStream,
                                         bool isAutoSize,
                                         std::function<void()> callback)
    {
        auto setSourceOperation = m_image.SetSourceAsync(randomAccessStream);

        setSourceOperation.Completed(
            [isAutoSize, callback](
                winrt::IAsyncOperation<winrt::SvgImageSourceLoadStatus> const& operation, winrt::AsyncStatus status)
            {
                auto loadStatus = operation.GetResults();
                if (status == winrt::AsyncStatus::Completed && isAutoSize && loadStatus == winrt::SvgImageSourceLoadStatus::Success)
                {
                    callback();
                }
            });
    }

    void SvgImageBuilder::SetUriSource(winrt::Uri const& imageUrl) { m_image.UriSource(imageUrl); }

    winrt::ImageSource SvgImageBuilder::GetImage() { return m_image; }
}
