// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardGetResourceStreamArgs.h"

const double c_playIconSize = 30;
const double c_playIconCornerRadius = 5;
const double c_playIconOpacity = .5;
const double c_audioHeight = 100;
const winrt::hstring supportedMimeTypes[] = {L"video/mp4", L"audio/mp4", L"audio/aac", L"audio/mpeg"};

namespace AdaptiveCards::Rendering::Uwp::MediaHelpers
{
    winrt::Image GetMediaPosterAsImage(winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveRenderArgs const& renderArgs,
                                       winrt::AdaptiveMedia const& adaptiveMedia)
    {
        auto posterString = adaptiveMedia.Poster();

        if (posterString.empty())
        {
            auto hostConfig = renderContext.HostConfig();
            auto mediaConfig = hostConfig.Media();

            posterString = mediaConfig.DefaultPoster();

            if (posterString.empty())
            {
                return nullptr;
            }
        }

        winrt::AdaptiveImage adaptiveImage{};
        adaptiveImage.Url(posterString);

        auto altText = adaptiveMedia.AltText();
        adaptiveImage.AltText(altText);

        auto elementRenderers = renderContext.ElementRenderers();
        auto imageRenderer = elementRenderers.Get(L"Image");

        if (const auto posterUiElement = imageRenderer.Render(adaptiveImage, renderContext, renderArgs))
        {
            return posterUiElement.as<winrt::Image>();
        }
        // Not logging a warning because if we get nullptr from imageRendere - it will log warning for us.
        return nullptr;
    }

    void AddDefaultPlayIcon(winrt::Panel const& posterPanel,
                            winrt::AdaptiveHostConfig const& hostConfig,
                            winrt::AdaptiveRenderArgs const& renderArgs)
    {
        // Create a rectangle
        winrt::Rectangle rectangle{};

        // Set the size
        rectangle.Height(c_playIconSize);
        rectangle.Width(c_playIconSize);

        // Round the corners
        rectangle.RadiusX(c_playIconCornerRadius);
        rectangle.RadiusY(c_playIconCornerRadius);

        // Set it's fill and opacity
        winrt::Windows::UI::Color whiteBrushColor{0xFF, 0xFF, 0xFF, 0xFF};
        rectangle.Fill(winrt::SolidColorBrush{whiteBrushColor});
        rectangle.Opacity(c_playIconOpacity);

        // Outline it in the Dark color
        auto containerStyle = renderArgs.ContainerStyle();

        auto darkBrushColor = GetColorFromAdaptiveColor(hostConfig, winrt::ForegroundColor::Dark, containerStyle, false, false);
        winrt::SolidColorBrush darkBrush{darkBrushColor};
        rectangle.Stroke(darkBrush);

        // Create a play symbol icon
        winrt::SymbolIcon playIcon{winrt::Symbol::Play};

        playIcon.Foreground(darkBrush);

        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(rectangle, posterPanel);
        winrt::RelativePanel::SetAlignVerticalCenterWithPanel(rectangle, true);
        winrt::RelativePanel::SetAlignHorizontalCenterWithPanel(rectangle, true);

        ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(playIcon, posterPanel);
        winrt::RelativePanel::SetAlignHorizontalCenterWithPanel(playIcon, true);
        winrt::RelativePanel::SetAlignVerticalCenterWithPanel(playIcon, true);
    }

    void AddCustomPlayIcon(winrt::Panel const& posterPanel,
                           winrt::hstring const& playIconString,
                           winrt::AdaptiveRenderContext const& renderContext,
                           winrt::AdaptiveRenderArgs const& renderArgs)
    {
        // Render the custom play icon using the image renderer
        winrt::AdaptiveImage playIconAdaptiveImage{};
        playIconAdaptiveImage.Url(playIconString);

        auto imageRenderer = renderContext.ElementRenderers().Get(L"Image");

        auto playIconUIElement = imageRenderer.Render(playIconAdaptiveImage, renderContext, renderArgs);

        if (const auto playIconAsFrameworkElement = playIconUIElement.try_as<winrt::FrameworkElement>())
        {
            playIconAsFrameworkElement.Height(c_playIconSize);

            // Add it to the panel and center it
            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(playIconUIElement, posterPanel);
            winrt::RelativePanel::SetAlignHorizontalCenterWithPanel(playIconUIElement, true);
            winrt::RelativePanel::SetAlignVerticalCenterWithPanel(playIconUIElement, true);
        }
    }

    void AddPlayIcon(winrt::Panel const& posterPanel,
                     winrt::AdaptiveRenderContext const& renderContext,
                     winrt::AdaptiveRenderArgs const& renderArgs)
    {
        auto hostConfig = renderContext.HostConfig();

        auto mediaConfig = hostConfig.Media();

        winrt::hstring customPlayIconString = mediaConfig.PlayButton();

        if (customPlayIconString.empty())
        {
            AddDefaultPlayIcon(posterPanel, hostConfig, renderArgs);
        }
        else
        {
            AddCustomPlayIcon(posterPanel, customPlayIconString, renderContext, renderArgs);
        }
    }

    winrt::UIElement CreatePosterContainerWithPlayButton(winrt::Image const& posterImage,
                                                         winrt::AdaptiveRenderContext const& renderContext,
                                                         winrt::AdaptiveRenderArgs const& renderArgs)
    {
        winrt::RelativePanel posterRelativePanel{};

        if (posterImage)
        {
            ::AdaptiveCards::Rendering::Uwp::XamlHelpers::AppendXamlElementToPanel(posterImage, posterRelativePanel);
        }
        AddPlayIcon(posterRelativePanel, renderContext, renderArgs);

        return posterRelativePanel;
    }

    std::tuple<winrt::Uri, winrt::hstring> GetMediaSource(winrt::AdaptiveHostConfig const& hostConfig,
                                                          winrt::AdaptiveMedia const& adaptiveMedia)
    {
        winrt::Uri mediaSourceUrl{nullptr};
        winrt::hstring mimeType{};

        auto sources = adaptiveMedia.Sources();

        winrt::AdaptiveMediaSource selectedSource{nullptr};

        for (auto source : sources)
        {
            winrt::hstring currentMimeType = source.MimeType();

            for (uint32_t i = 0; i < std::size(supportedMimeTypes); i++)
            {
                if (currentMimeType == supportedMimeTypes[i])
                {
                    selectedSource = source;
                    break;
                }
            }
        }
        if (selectedSource)
        {
            mediaSourceUrl = GetUrlFromString(hostConfig, selectedSource.Url());
            mimeType = selectedSource.MimeType();
        }

        return {mediaSourceUrl, mimeType};
    }

    void HandleMediaResourceResolverCompleted(winrt::IAsyncOperation<winrt::IRandomAccessStream> const& operation,
                                              winrt::AsyncStatus status,
                                              winrt::MediaElement const& mediaElement,
                                              winrt::hstring const& mimeType)
    {
        if (status == winrt::AsyncStatus::Completed)
        {
            // Get the random access stream
            if (const auto randomAccessStream = operation.GetResults())
            {
                mediaElement.SetSource(randomAccessStream, mimeType);
            }
        }
    }

    void HandleMediaClick(winrt::AdaptiveRenderContext const& renderContext,
                          winrt::AdaptiveMedia const& adaptiveMedia,
                          winrt::MediaElement const& mediaElement,
                          winrt::UIElement const& posterContainer,
                          winrt::Uri const& mediaSourceUrl,
                          winrt::hstring const& mimeType,
                          winrt::AdaptiveMediaEventInvoker const& mediaInvoker)
    {
        if (mediaElement)
        {
            posterContainer.Visibility(winrt::Visibility::Collapsed);
            mediaElement.Visibility(winrt::Visibility::Visible);

            winrt::IAdaptiveCardResourceResolver resourceResolver{nullptr};
            if (const auto resourceResolvers = renderContext.ResourceResolvers())
            {
                resourceResolver = resourceResolvers.Get(mediaSourceUrl.SchemeName());
            }

            if (resourceResolver == nullptr)
            {
                mediaElement.Source(mediaSourceUrl);
            }
            else
            {
                auto args = winrt::make<winrt::implementation::AdaptiveCardGetResourceStreamArgs>(mediaSourceUrl);

                auto getResourceStreamOperation = resourceResolver.GetResourceStreamAsync(args);

                getResourceStreamOperation.Completed(
                    [mediaElement, mimeType](winrt::IAsyncOperation<winrt::IRandomAccessStream> operation, winrt::AsyncStatus status) -> void
                    { return HandleMediaResourceResolverCompleted(operation, status, mediaElement, mimeType); });
            }

            mediaElement.MediaOpened(
                [](winrt::IInspectable const& sender, winrt::RoutedEventArgs const& /*args*/) -> void
                {
                    if (const auto mediaElement = sender.try_as<winrt::MediaElement>())
                    {
                        bool audioOnly = mediaElement.IsAudioOnly();
                        auto posterSource = mediaElement.PosterSource();

                        if (audioOnly && posterSource == nullptr)
                        {
                            // If this is audio only and there's no poster, set the height so
                            // that the controls are visible.
                            mediaElement.Height(c_audioHeight);
                        }
                        mediaElement.Play();
                    }
                });
        }
        else
        {
            mediaInvoker.SendMediaClickedEvent(adaptiveMedia);
        }
    }
}
