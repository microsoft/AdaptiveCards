// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering::MediaHelpers
{
    winrt::Image GetMediaPosterAsImage(winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveRenderArgs const& renderArgs,
                                       winrt::AdaptiveMedia const& adaptiveMedia);

    winrt::UIElement CreatePosterContainerWithPlayButton(winrt::Image const& posterImage,
                                                                            winrt::AdaptiveRenderContext const& renderContext,
                                                                            winrt::AdaptiveRenderArgs const& renderArgs);

    std::tuple<winrt::Uri, winrt::hstring> GetMediaSource(winrt::AdaptiveHostConfig const& hostConfig,
                                                          winrt::AdaptiveMedia const& adaptiveMedia);

    void HandleMediaClick(winrt::AdaptiveRenderContext const& renderContext,
                          winrt::AdaptiveMedia const& adaptiveMedia,
                          winrt::MediaElement const& mediaElement,
                          winrt::UIElement const& posterContainer,
                          winrt::Uri const& mediaSourceUrl,
                          winrt::hstring const& mimeType,
                          winrt::AdaptiveMediaEventInvoker const& mediaInvoker);
}
