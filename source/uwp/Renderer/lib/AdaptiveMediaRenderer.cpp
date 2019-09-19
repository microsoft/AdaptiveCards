// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveMedia.h"
#include "AdaptiveMediaRenderer.h"
#include "AdaptiveElementParserRegistration.h"
#include "MediaHelpers.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Media;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveMediaRenderer::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveMediaRenderer::Render(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                          _In_ IAdaptiveRenderContext* renderContext,
                                          _In_ IAdaptiveRenderArgs* renderArgs,
                                          _COM_Outptr_ IUIElement** mediaControl) noexcept try
    {
        ComPtr<IAdaptiveCardElement> localCardElement{adaptiveCardElement};
        ComPtr<IAdaptiveMedia> adaptiveMedia;
        RETURN_IF_FAILED(localCardElement.As(&adaptiveMedia));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        // Get the poster image
        ComPtr<IImage> posterImage;
        GetMediaPosterAsImage(renderContext, renderArgs, adaptiveMedia.Get(), &posterImage);

        // If the host doesn't support interactivity we're done here, just return the poster image
        if (!XamlHelpers::SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                                      HStringReference(L"Media was present in card, but interactivity is not supported").Get());

            if (posterImage != nullptr)
            {
                RETURN_IF_FAILED(posterImage.CopyTo(mediaControl));
            }

            return S_OK;
        }

        // Put the poster image in a container with a play button
        ComPtr<IUIElement> posterContainer;
        CreatePosterContainerWithPlayButton(posterImage.Get(), renderContext, renderArgs, &posterContainer);

        ComPtr<IUIElement> touchTargetUIElement;
        XamlHelpers::WrapInTouchTarget(adaptiveCardElement, posterContainer.Get(), nullptr, renderContext, true, L"Adaptive.SelectAction", &touchTargetUIElement);

        // Create a panel to hold the poster and the media element
        ComPtr<IStackPanel> mediaStackPanel =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IPanel> mediaPanel;
        RETURN_IF_FAILED(mediaStackPanel.As(&mediaPanel));

        XamlHelpers::AppendXamlElementToPanel(touchTargetUIElement.Get(), mediaPanel.Get());

        // Check if this host allows inline playback
        ComPtr<IAdaptiveMediaConfig> mediaConfig;
        RETURN_IF_FAILED(hostConfig->get_Media(&mediaConfig));

        boolean allowInlinePlayback;
        RETURN_IF_FAILED(mediaConfig->get_AllowInlinePlayback(&allowInlinePlayback));

        ComPtr<IAdaptiveMediaEventInvoker> mediaInvoker;
        RETURN_IF_FAILED(renderContext->get_MediaEventInvoker(&mediaInvoker));

        HString mimeType;
        ComPtr<IMediaElement> mediaElement;
        ComPtr<IUriRuntimeClass> mediaSourceUrl;
        if (allowInlinePlayback)
        {
            // Create a media element and set it's source
            mediaElement =
                XamlHelpers::CreateXamlClass<IMediaElement>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_MediaElement));

            GetMediaSource(hostConfig.Get(), adaptiveMedia.Get(), mediaSourceUrl.GetAddressOf(), mimeType.GetAddressOf());

            if (mediaSourceUrl == nullptr)
            {
                renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::UnsupportedMediaType,
                                          HStringReference(L"Unsupported media element dropped").Get());
                return S_OK;
            }

            // Configure Auto Play and Controls
            RETURN_IF_FAILED(mediaElement->put_AutoPlay(false));

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
            RETURN_IF_FAILED(mediaElement.As(&mediaUIElement));

            if (posterImage != nullptr)
            {
                // Set the poster on the media element
                ComPtr<IImageSource> posterImageSource;
                RETURN_IF_FAILED(posterImage->get_Source(&posterImageSource));
                RETURN_IF_FAILED(mediaElement->put_PosterSource(posterImageSource.Get()));
            }

            // Make the media element collapsed until the user clicks
            RETURN_IF_FAILED(mediaUIElement->put_Visibility(Visibility_Collapsed));

            XamlHelpers::AppendXamlElementToPanel(mediaElement.Get(), mediaPanel.Get());
        }

        ComPtr<IUIElement> mediaPanelAsUIElement;
        RETURN_IF_FAILED(mediaPanel.As(&mediaPanelAsUIElement));

        ComPtr<IButtonBase> touchTargetAsButtonBase;
        RETURN_IF_FAILED(touchTargetUIElement.As(&touchTargetAsButtonBase));

        // Take a reference to the mime type string for the lambda (lifetime dictated by localMimeType in the below
        // lambda)
        HSTRING lambdaMimeType;
        WindowsDuplicateString(mimeType.Get(), &lambdaMimeType);
        ComPtr<IAdaptiveRenderContext> lambdaRenderContext{renderContext};

        EventRegistrationToken clickToken;
        RETURN_IF_FAILED(touchTargetAsButtonBase->add_Click(
            Callback<IRoutedEventHandler>([touchTargetUIElement, lambdaRenderContext, adaptiveMedia, mediaElement, mediaSourceUrl, lambdaMimeType, mediaInvoker](
                                              IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                // Take ownership of the passed in HSTRING
                HString localMimeType;
                localMimeType.Attach(lambdaMimeType);

                // Turn off the button to prevent extra clicks
                ComPtr<ABI::Windows::UI::Xaml::Controls::IControl> buttonAsControl;
                touchTargetUIElement.As(&buttonAsControl);
                RETURN_IF_FAILED(buttonAsControl->put_IsEnabled(false));

                // Handle the click
                return HandleMediaClick(lambdaRenderContext.Get(),
                                        adaptiveMedia.Get(),
                                        mediaElement.Get(),
                                        touchTargetUIElement.Get(),
                                        mediaSourceUrl.Get(),
                                        lambdaMimeType,
                                        mediaInvoker.Get());
            }).Get(),
            &clickToken));

        RETURN_IF_FAILED(mediaPanelAsUIElement.CopyTo(mediaControl));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveMediaRenderer::FromJson(
        _In_ ABI::Windows::Data::Json::IJsonObject* jsonObject,
        _In_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration* elementParserRegistration,
        _In_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration* actionParserRegistration,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** element) noexcept try
    {
        return AdaptiveNamespace::FromJson<AdaptiveNamespace::AdaptiveMedia, AdaptiveSharedNamespace::Media, AdaptiveSharedNamespace::MediaParser>(
            jsonObject, elementParserRegistration, actionParserRegistration, adaptiveWarnings, element);
    }
    CATCH_RETURN;
}
