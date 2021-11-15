// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveMediaRenderer.h"
#include "ActionHelpers.h"
#include "MediaHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Media;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    rtxaml::UIElement AdaptiveMediaRenderer::Render(rtom::IAdaptiveCardElement const& adaptiveCardElement,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs)
    {
        try
        {
            // TODO: what is the need for the local object? only to user ComPtr.as later? or for something else as well?
            /*ComPtr<IAdaptiveCardElement> localCardElement{adaptiveCardElement};
            ComPtr<IAdaptiveMedia> adaptiveMedia;
            RETURN_IF_FAILED(localCardElement.As(&adaptiveMedia));*/
            auto adaptiveMedia = adaptiveCardElement.as<rtom::AdaptiveMedia>();

            /*ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/

            auto hostConfig = renderContext.HostConfig();

            // Get the poster image
            /* ComPtr<IImage> posterImage;
             GetMediaPosterAsImage(renderContext, renderArgs, adaptiveMedia.Get(), &posterImage);*/

            auto posterImage = GetMediaPosterAsImage(renderContext, renderArgs, adaptiveMedia);

            // If the host doesn't support interactivity we're done here, just return the poster image
            if (!::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SupportsInteractivity(hostConfig))
            {
                renderContext.AddWarning(rtom::WarningStatusCode::InteractivityNotSupported,
                                         L"Media was present in card, but interactivity is not supported");

                //if (posterImage != nullptr)
                //{
                //    /* RETURN_IF_FAILED(posterImage.CopyTo(mediaControl));*/
                //    return posterImage;
                //}
                // TODO: we gotta return something here, so even if it's null we do return it, right?
                return posterImage;

                // return S_OK;
            }

            // Put the poster image in a container with a play button
            /*ComPtr<IUIElement> posterContainer;
            CreatePosterContainerWithPlayButton(posterImage.Get(), renderContext, renderArgs, &posterContainer);*/
            auto posterContainer = CreatePosterContainerWithPlayButton(posterImage, renderContext, renderArgs);

            /*HString altText;
            RETURN_IF_FAILED(adaptiveMedia->get_AltText(altText.GetAddressOf()));

            ComPtr<IUIElement> touchTargetUIElement;
            ActionHelpers::WrapInTouchTarget(adaptiveCardElement,
                                             posterContainer.Get(),
                                             nullptr,
                                             renderContext,
                                             true,
                                             L"Adaptive.SelectAction",
                                             altText.Get(),
                                             false,
                                             &touchTargetUIElement);*/

            winrt::hstring altText = adaptiveMedia.AltText();

            auto touchTargetUIElement = ::AdaptiveCards::Rendering::WinUI3::ActionHelpers::WrapInTouchTarget(
                adaptiveCardElement, posterContainer, nullptr, renderContext, true, L"Adaptive.SelectAction", altText, false);

            // Create a panel to hold the poster and the media element
            /* ComPtr<IStackPanel> mediaStackPanel =
                 XamlHelpers::CreateABIClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
             ComPtr<IPanel> mediaPanel;
             RETURN_IF_FAILED(mediaStackPanel.As(&mediaPanel));*/
            rtxaml::Controls::StackPanel mediaStackPanel{};
            // TODO: I don't need to cast to Panel, right?
            ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(touchTargetUIElement, mediaStackPanel);

            // Check if this host allows inline playback
            /* ComPtr<IAdaptiveMediaConfig> mediaConfig;
             RETURN_IF_FAILED(hostConfig->get_Media(&mediaConfig));

             boolean allowInlinePlayback;
             RETURN_IF_FAILED(mediaConfig->get_AllowInlinePlayback(&allowInlinePlayback));

             ComPtr<IAdaptiveMediaEventInvoker> mediaInvoker;
             RETURN_IF_FAILED(renderContext->get_MediaEventInvoker(&mediaInvoker));

             HString mimeType;
             ComPtr<IMediaElement> mediaElement;
             ComPtr<IUriRuntimeClass> mediaSourceUrl;*/

            auto mediaConfig = hostConfig.Media();

            bool allowInlinePlayback = mediaConfig.AllowInlinePlayback();

            auto mediaInvoker = renderContext.MediaEventInvoker();

            winrt::hstring mimeType{};
            rtxaml::Controls::MediaElement mediaElement{nullptr};
            winrt::Windows::Foundation::Uri mediaSourceUrl{nullptr};

            if (allowInlinePlayback)
            {
                // Create a media element and set it's source
                /*mediaElement = XamlHelpers::CreateABIClass<IMediaElement>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_MediaElement));*/
                mediaElement = rtxaml::Controls::MediaElement{};

                std::tie(mediaSourceUrl, mimeType) = GetMediaSource(hostConfig, adaptiveMedia);

                if (mediaSourceUrl == nullptr)
                {
                    renderContext.AddWarning(rtom::WarningStatusCode::UnsupportedMediaType, L"Unsupported media element dropped");
                    return nullptr;
                }

                // Configure Auto Play and Controls
                /* RETURN_IF_FAILED(mediaElement->put_AutoPlay(false));

                 ComPtr<IMediaElement2> mediaElement2;
                 RETURN_IF_FAILED(mediaElement.As(&mediaElement2));
                 RETURN_IF_FAILED(mediaElement2->put_AreTransportControlsEnabled(true));
                 ComPtr<IMediaElement3> mediaElement3;
                 RETURN_IF_FAILED(mediaElement.As(&mediaElement3));
                 ComPtr<IMediaTransportControls> mediaTransportControl;
                 RETURN_IF_FAILED(mediaElement3->get_TransportControls(&mediaTransportControl));
                 RETURN_IF_FAILED(mediaTransportControl->put_IsCompact(true));
                 RETURN_IF_FAILED(mediaTransportControl->put_IsZoomButtonVisible(false));

                 ComPtr<IUIElement> mediaUIElement;
                 RETURN_IF_FAILED(mediaElement.As(&mediaUIElement));*/
                mediaElement.AutoPlay(false);
                mediaElement.AreTransportControlsEnabled(true);
                auto mediaTransportControls = mediaElement.TransportControls();
                mediaTransportControls.IsCompact(true);
                mediaTransportControls.IsZoomButtonVisible(false);

                if (posterImage != nullptr)
                {
                    // Set the poster on the media element
                    /*ComPtr<IImageSource> posterImageSource;
                    RETURN_IF_FAILED(posterImage->get_Source(&posterImageSource));
                    RETURN_IF_FAILED(mediaElement->put_PosterSource(posterImageSource.Get()));*/
                    auto posterImageSource = posterImage.Source();
                    mediaElement.PosterSource(posterImageSource);
                }

                // Make the media element collapsed until the user clicks
                /*RETURN_IF_FAILED(mediaUIElement->put_Visibility(Visibility_Collapsed));*/
                mediaElement.Visibility(rtxaml::Visibility::Collapsed);

                // TODO: I don't need to cast StackPanel, to Panel right?
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::AppendXamlElementToPanel(mediaElement, mediaStackPanel);
            }

            /* ComPtr<IUIElement> mediaPanelAsUIElement;
             RETURN_IF_FAILED(mediaPanel.As(&mediaPanelAsUIElement));

             ComPtr<IButtonBase> touchTargetAsButtonBase;
             RETURN_IF_FAILED(touchTargetUIElement.As(&touchTargetAsButtonBase));*/
            auto touchTargetAsButtonBase = touchTargetUIElement.as<rtxaml::Controls::Primitives::ButtonBase>();
            // Take a reference to the mime type string for the lambda (lifetime dictated by localMimeType in the below
            // lambda)
            /* HSTRING lambdaMimeType;
             WindowsDuplicateString(mimeType.Get(), &lambdaMimeType);*/

            // TODO: why create another comPtr to renderContext?
            /*ComPtr<IAdaptiveRenderContext> lambdaRenderContext{renderContext};*/

            /*EventRegistrationToken clickToken;
            RETURN_IF_FAILED(touchTargetAsButtonBase->add_Click(
                Callback<IRoutedEventHandler>(*/
            /*   HSTRING lambdaMimeType = winrt::detach_abi(mimeType);*/
        /*    winrt::hstring lambdaMimeType{mimeType};*/
            touchTargetAsButtonBase.Click(
                [touchTargetUIElement, renderContext, adaptiveMedia, mediaElement, mediaSourceUrl, mimeType, mediaInvoker](
                    winrt::Windows::Foundation::IInspectable const& /*sender*/, rtxaml::RoutedEventArgs const& /*args*/) -> HRESULT
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
