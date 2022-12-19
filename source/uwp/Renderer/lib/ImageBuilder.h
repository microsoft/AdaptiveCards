#pragma once

#include "pch.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class ImageBuilder
    {
    public:
        virtual void CreateImage();

        virtual void AssignBitmapOptions(winrt::BitmapCreateOptions const& option);

        virtual void SetAsyncSource(winrt::IRandomAccessStream const& randomAccessStream,
                                    bool isAutoSize,
                                    std::function<void()> callback);

        virtual void SetUriSource(winrt::Uri const& imageUrl);

        virtual winrt::ImageSource GetImage();
    };

    class BitmapImageBuilder: public ImageBuilder
    {
    public:
        winrt::BitmapImage m_image;

        void CreateImage() override;

        void AssignBitmapOptions(winrt::BitmapCreateOptions const& option) override;

        void SetAsyncSource(winrt::IRandomAccessStream const& randomAccessStream,
                            bool isAutoSize,
                            std::function<void()> callback) override;

        void SetUriSource(winrt::Uri const& imageUrl) override;

        winrt::ImageSource GetImage() override;
    };

    class SvgImageBuilder: public ImageBuilder
    {
    public:
        winrt::SvgImageSource m_image;

        void CreateImage() override;

        void SetAsyncSource(winrt::IRandomAccessStream const& randomAccessStream,
                            bool isAutoSize,
                            std::function<void()> callback) override;

        void SetUriSource(winrt::Uri const& imageUrl) override;

        winrt::ImageSource GetImage() override;
    };
}
