// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

void GetMediaPosterAsImage(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                           _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                           _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia* adaptiveMedia,
                           _Outptr_ ABI::Windows::UI::Xaml::Controls::IImage** posterImage);

void CreatePosterContainerWithPlayButton(_In_ ABI::Windows::UI::Xaml::Controls::IImage* posterImage,
                                         _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                                         _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                                         _Outptr_ ABI::Windows::UI::Xaml::IUIElement** posterContainer);

void GetMediaSource(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                    _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia* adaptiveMedia,
                    _Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** mediaSourceUrl,
                    _Outptr_ HSTRING* mimeType);

HRESULT HandleMediaClick(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                         _In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia* adaptiveMedia,
                         _In_ ABI::Windows::UI::Xaml::Controls::IMediaElement* mediaElement,
                         _In_ ABI::Windows::UI::Xaml::IUIElement* posterContainer,
                         _In_ ABI::Windows::Foundation::IUriRuntimeClass* mediaSourceUrl,
                         _In_ HSTRING mimeType,
                         _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaEventInvoker* mediaInvoker);
