// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp::MediaHelpers
{
    winrt::Image
    GetMediaPosterAsImage(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                          winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs,
                          winrt::AdaptiveMedia const& adaptiveMedia);

    winrt::Windows::UI::Xaml::UIElement
    CreatePosterContainerWithPlayButton(winrt::Image const& posterImage,
                                        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                                        winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

    std::tuple<winrt::Uri, winrt::hstring>
    GetMediaSource(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                   winrt::AdaptiveMedia const& adaptiveMedia);

    void HandleMediaClick(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
                          winrt::AdaptiveMedia const& adaptiveMedia,
                          winrt::MediaElement const& mediaElement,
                          winrt::Windows::UI::Xaml::UIElement const& posterContainer,
                          winrt::Uri const& mediaSourceUrl,
                          winrt::hstring const& mimeType,
                          winrt::AdaptiveCards::Rendering::Uwp::AdaptiveMediaEventInvoker const& mediaInvoker);
}
