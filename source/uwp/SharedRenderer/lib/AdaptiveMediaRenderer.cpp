// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveMediaRenderer.h"
#include "AdaptiveMediaRenderer.g.cpp"

#include "ActionHelpers.h"
#include "MediaHelpers.h"
#include "WholeItemsPanel.h"

using namespace ::AdaptiveCards::Rendering::Xaml_Rendering::MediaHelpers;

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::UIElement AdaptiveMediaRenderer::Render(winrt::IAdaptiveCardElement const& cardElement,
                                                   winrt::AdaptiveRenderContext const& renderContext,
                                                   winrt::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            auto adaptiveMedia = cardElement.as<winrt::AdaptiveMedia>();
            auto hostConfig = renderContext.HostConfig();

            // Get the poster image
            auto posterImage = GetMediaPosterAsImage(renderContext, renderArgs, adaptiveMedia);

            // If the host doesn't support interactivity we're done here, just return the poster image
            if (!XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(winrt::WarningStatusCode::InteractivityNotSupported,
                                         L"Media was present in card, but interactivity is not supported");

                return posterImage;
            }

            // Put the poster image in a container with a play button
            auto posterContainer = CreatePosterContainerWithPlayButton(posterImage, renderContext, renderArgs);

            winrt::hstring altText = adaptiveMedia.AltText();

            auto touchTargetUIElement = ::AdaptiveCards::Rendering::Xaml_Rendering::ActionHelpers::WrapInTouchTarget(
                cardElement, posterContainer, nullptr, renderContext, true, L"Adaptive.SelectAction", altText, false);

            // Create a panel to hold the poster and the media element
            winrt::StackPanel mediaStackPanel{};

            XamlHelpers::AppendXamlElementToPanel(touchTargetUIElement, mediaStackPanel);

            // Check if this host allows inline playback
            auto mediaConfig = hostConfig.Media();

            bool allowInlinePlayback = mediaConfig.AllowInlinePlayback();

            auto mediaInvoker = renderContext.MediaEventInvoker();

            winrt::hstring mimeType{};
            winrt::Uri mediaSourceUrl{nullptr};
            winrt::MediaElement mediaElement{nullptr};

            if (allowInlinePlayback)
            {
                // Create a media element and set it's source
                mediaElement = winrt::MediaElement{};

                std::tie(mediaSourceUrl, mimeType) = GetMediaSource(hostConfig, adaptiveMedia);

                if (mediaSourceUrl == nullptr)
                {
                    renderContext.AddWarning(winrt::WarningStatusCode::UnsupportedMediaType, L"Unsupported media element dropped");
                    return nullptr;
                }

                // Configure Auto Play and Controls
                mediaElement.AutoPlay(false);
                mediaElement.AreTransportControlsEnabled(true);
                auto mediaTransportControls = mediaElement.TransportControls();
                mediaTransportControls.IsCompact(true);
                mediaTransportControls.IsZoomButtonVisible(false);

                if (posterImage)
                {
                    // Set the poster on the media element
                    auto posterImageSource = posterImage.Source();
                    mediaElement.PosterSource(posterImage.Source());
                }

                // Make the media element collapsed until the user clicks
                mediaElement.Visibility(winrt::Visibility::Collapsed);

                XamlHelpers::AppendXamlElementToPanel(mediaElement, mediaStackPanel);
            }

            auto touchTargetAsButtonBase = touchTargetUIElement.as<winrt::ButtonBase>();

            touchTargetAsButtonBase.Click(
                [touchTargetAsButtonBase, renderContext, adaptiveMedia, mediaElement, mediaSourceUrl, mimeType, mediaInvoker](
                    winrt::IInspectable const& /*sender*/, winrt::RoutedEventArgs const& /*args*/) -> void
                {
                    // Turn off the button to prevent extra clicks
                    touchTargetAsButtonBase.IsEnabled(false);

                    // Handle the click
                    HandleMediaClick(renderContext, adaptiveMedia, mediaElement, touchTargetAsButtonBase, mediaSourceUrl, mimeType, mediaInvoker);
                });
            return mediaStackPanel;
        }
        catch (winrt::hresult_error const& ex)
        {
            XamlHelpers::ErrForRenderFailedForElement(renderContext, cardElement.ElementTypeString(), ex.message());
            return nullptr;
        }
    }
}
