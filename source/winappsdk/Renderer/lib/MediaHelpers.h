// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3::MediaHelpers
{
    winrt::Windows::UI::Xaml::Controls::Image
    GetMediaPosterAsImage(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                          winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs,
                          winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMedia const& adaptiveMedia);

    winrt::Windows::UI::Xaml::UIElement
    CreatePosterContainerWithPlayButton(winrt::Windows::UI::Xaml::Controls::Image const& posterImage,
                                        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                                        winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

    std::tuple<winrt::Windows::Foundation::Uri, winrt::hstring>
    GetMediaSource(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveHostConfig const& hostConfig,
                   winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMedia const& adaptiveMedia);

    void HandleMediaClick(winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext const& renderContext,
                          winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMedia const& adaptiveMedia,
                          winrt::Windows::UI::Xaml::Controls::MediaElement const& mediaElement,
                          winrt::Windows::UI::Xaml::UIElement const& posterContainer,
                          winrt::Windows::Foundation::Uri const& mediaSourceUrl,
                          winrt::hstring const& mimeType,
                          winrt::AdaptiveCards::Rendering::WinUI3::AdaptiveMediaEventInvoker const& mediaInvoker);
}
