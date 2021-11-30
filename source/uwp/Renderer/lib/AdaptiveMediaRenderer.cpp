// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveMediaRenderer.h"
#include "AdaptiveMediaRenderer.g.cpp"

#include "ActionHelpers.h"
#include "MediaHelpers.h"

using namespace AdaptiveCards::Rendering::Uwp::MediaHelpers;

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    rtxaml::UIElement AdaptiveMediaRenderer::Render(rtom::IAdaptiveCardElement const& adaptiveCardElement,
                                                    rtrender::AdaptiveRenderContext const& renderContext,
                                                    rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            // TODO: what is the need for the local object? only to use ComPtr.as later? or for something else as well?
            auto adaptiveMedia = adaptiveCardElement.as<rtom::AdaptiveMedia>();
            auto hostConfig = renderContext.HostConfig();

            // Get the poster image
            auto posterImage = GetMediaPosterAsImage(renderContext, renderArgs, adaptiveMedia);

            // If the host doesn't support interactivity we're done here, just return the poster image
            if (!::AdaptiveCards::Rendering::Uwp::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Media was present in card, but interactivity is not supported");

                // TODO: we gotta return something here, so even if it's null we do return it regardless, right?
                return posterImage;
            }

            // Put the poster image in a container with a play button
            auto posterContainer = CreatePosterContainerWithPlayButton(posterImage, renderContext, renderArgs);

            winrt::hstring altText = adaptiveMedia.AltText();

            auto touchTargetUIElement = ::AdaptiveCards::Rendering::Uwp::ActionHelpers::WrapInTouchTarget(
                adaptiveCardElement, posterContainer, nullptr, renderContext, true, L"Adaptive.SelectAction", altText, false);

            // Create a panel to hold the poster and the media element
            rtxaml::Controls::StackPanel mediaStackPanel{};

            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(touchTargetUIElement, mediaStackPanel);

            // Check if this host allows inline playback
            auto mediaConfig = hostConfig.Media();

            bool allowInlinePlayback = mediaConfig.AllowInlinePlayback();

            auto mediaInvoker = renderContext.MediaEventInvoker();

            winrt::hstring mimeType{};
            winrt::Windows::Foundation::Uri mediaSourceUrl{nullptr};
            rtxaml::Controls::MediaElement mediaElement{nullptr};

            if (allowInlinePlayback)
            {
                // Create a media element and set it's source
                mediaElement = rtxaml::Controls::MediaElement{};

                std::tie(mediaSourceUrl, mimeType) = GetMediaSource(hostConfig, adaptiveMedia);

                if (mediaSourceUrl == nullptr)
                {
                    renderContext.AddWarning(rtom::WarningStatusCode::UnsupportedMediaType, L"Unsupported media element dropped");
                    // TODO: is this correct? do we just return null here?
                    return nullptr;
                }

                // Configure Auto Play and Controls
                mediaElement.AutoPlay(false);
                mediaElement.AreTransportControlsEnabled(true);
                auto mediaTransportControls = mediaElement.TransportControls();
                mediaTransportControls.IsCompact(true);
                mediaTransportControls.IsZoomButtonVisible(false);

                if (posterImage != nullptr)
                {
                    // Set the poster on the media element
                    auto posterImageSource = posterImage.Source();
                    mediaElement.PosterSource(posterImage.Source());
                }

                // Make the media element collapsed until the user clicks
                mediaElement.Visibility(rtxaml::Visibility::Collapsed);

                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(mediaElement, mediaStackPanel);
            }

            auto touchTargetAsButtonBase = touchTargetUIElement.as<rtxaml::Controls::Primitives::ButtonBase>();

            // TODO: can we do this? or do we need to return event token? I'm afraid it will revoke momentarily
            touchTargetAsButtonBase.Click(
                [touchTargetUIElement, renderContext, adaptiveMedia, mediaElement, mediaSourceUrl, mimeType, mediaInvoker](
                    winrt::Windows::Foundation::IInspectable const& /*sender*/, rtxaml::RoutedEventArgs const& /*args*/) -> void
                {
                    // Turn off the button to prevent extra clicks
                    if (const auto buttonAsControl = touchTargetUIElement.try_as<rtxaml::Controls::Control>())
                    {
                        buttonAsControl.IsEnabled(false);
                    }

                    // Handle the click
                    HandleMediaClick(renderContext, adaptiveMedia, mediaElement, touchTargetUIElement, mediaSourceUrl, mimeType, mediaInvoker);
                });
            return mediaStackPanel;
        }
        catch (winrt::hresult_error const& ex)
        {
            // TODO: what do we do here?
            return nullptr;
        }
    }
}
