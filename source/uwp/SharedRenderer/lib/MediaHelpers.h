// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering::MediaHelpers
{
    winrt::xaml_controls::Image GetMediaPosterAsImage(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                       winrt::render_xaml::AdaptiveRenderArgs const& renderArgs,
                                                      winrt::AdaptiveMedia const& adaptiveMedia);

    winrt::xaml::UIElement CreatePosterContainerWithPlayButton(winrt::xaml_controls::Image const& posterImage,
                                                                            winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                                                                            winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

    std::tuple<winrt::Uri, winrt::hstring> GetMediaSource(winrt::render_xaml::AdaptiveHostConfig const& hostConfig,
                                                          winrt::AdaptiveMedia const& adaptiveMedia);

    void HandleMediaClick(winrt::render_xaml::AdaptiveRenderContext const& renderContext,
                          winrt::AdaptiveMedia const& adaptiveMedia,
                          winrt::xaml_controls::MediaElement const& mediaElement,
                          winrt::xaml::UIElement const& posterContainer,
                          winrt::Uri const& mediaSourceUrl,
                          winrt::hstring const& mimeType,
                          winrt::render_xaml::AdaptiveMediaEventInvoker const& mediaInvoker);
}
