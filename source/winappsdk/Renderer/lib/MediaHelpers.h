// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

void GetMediaPosterAsImage(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                           _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia* adaptiveMedia,
                           _Outptr_ ABI::Windows::UI::Xaml::Controls::IImage** posterImage);

void CreatePosterContainerWithPlayButton(_In_ ABI::Windows::UI::Xaml::Controls::IImage* posterImage,
                                         _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                         _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                                         _Outptr_ ABI::Windows::UI::Xaml::IUIElement** posterContainer);

void GetMediaSource(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                    _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia* adaptiveMedia,
                    _Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** mediaSourceUrl,
                    _Outptr_ HSTRING* mimeType);

HRESULT HandleMediaClick(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                         _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia* adaptiveMedia,
                         _In_ ABI::Windows::UI::Xaml::Controls::IMediaElement* mediaElement,
                         _In_ ABI::Windows::UI::Xaml::IUIElement* posterContainer,
                         _In_ ABI::Windows::Foundation::IUriRuntimeClass* mediaSourceUrl,
                         _In_ HSTRING mimeType,
                         _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveMediaEventInvoker* mediaInvoker);

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
