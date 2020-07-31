// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveBase64Util.h"
#include "AdaptiveCardGetResourceStreamArgs.h"
#include "AdaptiveCardRendererComponent.h"
#include "AdaptiveCardResourceResolvers.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"
#include "AdaptiveFeatureRegistration.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveImage.h"
#include "AdaptiveRenderArgs.h"
#include "AdaptiveShowCardAction.h"
#include "AdaptiveTextRun.h"
#include "DateTimeParser.h"
#include "ElementTagContent.h"
#include "FeatureRegistration.h"
#include "TextHelpers.h"
#include "json/json.h"
#include "MarkDownParser.h"
#include "MediaHelpers.h"
#include <robuffer.h>
#include "TileControl.h"
#include "WholeItemsPanel.h"
#include <windows.foundation.collections.h>
#include <windows.storage.h>
#include <windows.ui.xaml.markup.h>
#include <windows.ui.xaml.shapes.h>
#include <windows.web.http.h>
#include <windows.web.http.filters.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "LinkButton.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage;
using namespace ABI::Windows::Storage::Streams;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Text;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Data;
using namespace ABI::Windows::UI::Xaml::Documents;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::Web::Http;
using namespace ABI::Windows::Web::Http::Filters;

const PCWSTR c_BackgroundImageOverlayBrushKey = L"AdaptiveCard.BackgroundOverlayBrush";

namespace AdaptiveNamespace
{
    XamlBuilder::XamlBuilder()
    {
        m_imageLoadTracker.AddListener(dynamic_cast<IImageLoadTrackerListener*>(this));

        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_RandomAccessStream).Get(),
                                             &m_randomAccessStreamStatics));
    }

    ComPtr<IUIElement> XamlBuilder::CreateSeparator(_In_ IAdaptiveRenderContext* renderContext,
                                                    UINT spacing,
                                                    UINT separatorThickness,
                                                    ABI::Windows::UI::Color separatorColor,
                                                    bool isHorizontal)
    {
        ComPtr<IGrid> separator =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
        THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));

        ComPtr<IBrush> lineColorBrush = XamlHelpers::GetSolidColorBrush(separatorColor);
        ComPtr<IPanel> separatorAsPanel;
        THROW_IF_FAILED(separator.As(&separatorAsPanel));
        separatorAsPanel->put_Background(lineColorBrush.Get());

        UINT32 separatorMarginValue = spacing > separatorThickness ? (spacing - separatorThickness) / 2 : 0;
        Thickness margin = {0, 0, 0, 0};

        if (isHorizontal)
        {
            margin.Top = margin.Bottom = separatorMarginValue;
            separatorAsFrameworkElement->put_Height(separatorThickness);
        }
        else
        {
            margin.Left = margin.Right = separatorMarginValue;
            separatorAsFrameworkElement->put_Width(separatorThickness);
        }

        THROW_IF_FAILED(separatorAsFrameworkElement->put_Margin(margin));

        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Separator", separatorAsFrameworkElement.Get()));

        ComPtr<IUIElement> result;
        THROW_IF_FAILED(separator.As(&result));
        return result;
    }

    HRESULT XamlBuilder::AllImagesLoaded()
    {
        FireAllImagesLoaded();
        return S_OK;
    }

    HRESULT XamlBuilder::ImagesLoadingHadError()
    {
        FireImagesLoadingHadError();
        return S_OK;
    }

    HRESULT XamlBuilder::BuildXamlTreeFromAdaptiveCard(_In_ IAdaptiveCard* adaptiveCard,
                                                       _Outptr_ IFrameworkElement** xamlTreeRoot,
                                                       _In_ IAdaptiveRenderContext* renderContext,
                                                       ComPtr<XamlBuilder> xamlBuilder,
                                                       ABI::AdaptiveNamespace::ContainerStyle defaultContainerStyle)
    {
        *xamlTreeRoot = nullptr;
        if (adaptiveCard != nullptr)
        {
            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
            ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
            RETURN_IF_FAILED(hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

            boolean allowCustomStyle;
            RETURN_IF_FAILED(adaptiveCardConfig->get_AllowCustomStyle(&allowCustomStyle));

            ABI::AdaptiveNamespace::ContainerStyle containerStyle = defaultContainerStyle;
            if (allowCustomStyle)
            {
                ABI::AdaptiveNamespace::ContainerStyle cardStyle;
                RETURN_IF_FAILED(adaptiveCard->get_Style(&cardStyle));

                if (cardStyle != ABI::AdaptiveNamespace::ContainerStyle::None)
                {
                    containerStyle = cardStyle;
                }
            }
            ComPtr<IAdaptiveRenderArgs> renderArgs;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&renderArgs, containerStyle, nullptr, nullptr));

            ComPtr<IPanel> bodyElementContainer;
            ComPtr<IUIElement> rootElement =
                CreateRootCardElement(adaptiveCard, renderContext, renderArgs.Get(), xamlBuilder, &bodyElementContainer);
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            RETURN_IF_FAILED(rootElement.As(&rootAsFrameworkElement));

            UINT32 cardMinHeight{};
            RETURN_IF_FAILED(adaptiveCard->get_MinHeight(&cardMinHeight));
            if (cardMinHeight > 0)
            {
                RETURN_IF_FAILED(rootAsFrameworkElement->put_MinHeight(cardMinHeight));
            }

            ComPtr<IAdaptiveActionElement> selectAction;
            RETURN_IF_FAILED(adaptiveCard->get_SelectAction(&selectAction));

            // Create a new IUIElement pointer to house the root element decorated with select action
            ComPtr<IUIElement> rootSelectActionElement;
            HandleSelectAction(nullptr,
                               selectAction.Get(),
                               renderContext,
                               rootElement.Get(),
                               SupportsInteractivity(hostConfig.Get()),
                               true,
                               &rootSelectActionElement);
            RETURN_IF_FAILED(rootSelectActionElement.As(&rootAsFrameworkElement));

            // Enumerate the child items of the card and build xaml for them
            ComPtr<IVector<IAdaptiveCardElement*>> body;
            RETURN_IF_FAILED(adaptiveCard->get_Body(&body));
            ComPtr<IAdaptiveRenderArgs> bodyRenderArgs;
            RETURN_IF_FAILED(
                MakeAndInitialize<AdaptiveRenderArgs>(&bodyRenderArgs, containerStyle, rootAsFrameworkElement.Get(), nullptr));
            RETURN_IF_FAILED(
                BuildPanelChildren(body.Get(), bodyElementContainer.Get(), renderContext, bodyRenderArgs.Get(), [](IUIElement*) {}));

            ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment;
            RETURN_IF_FAILED(adaptiveCard->get_VerticalContentAlignment(&verticalContentAlignment));
            XamlBuilder::SetVerticalContentAlignmentToChildren(bodyElementContainer.Get(), verticalContentAlignment);

            ComPtr<IVector<IAdaptiveActionElement*>> actions;
            RETURN_IF_FAILED(adaptiveCard->get_Actions(&actions));
            UINT32 actionsSize;
            RETURN_IF_FAILED(actions->get_Size(&actionsSize));
            if (actionsSize > 0)
            {
                if (SupportsInteractivity(hostConfig.Get()))
                {
                    unsigned int bodyCount;
                    RETURN_IF_FAILED(body->get_Size(&bodyCount));
                    BuildActions(actions.Get(), bodyElementContainer.Get(), bodyCount > 0, renderContext, renderArgs.Get());
                }
                else
                {
                    renderContext->AddWarning(
                        ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                        HStringReference(L"Actions collection was present in card, but interactivity is not supported").Get());
                }
            }

            boolean isInShowCard;
            renderArgs->get_IsInShowCard(&isInShowCard);

            if (!isInShowCard)
            {
                RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", rootAsFrameworkElement.Get()));
            }
            else
            {
                RETURN_IF_FAILED(
                    SetStyleFromResourceDictionary(renderContext, L"Adaptive.ShowCard.Card", rootAsFrameworkElement.Get()));
            }

            RETURN_IF_FAILED(rootAsFrameworkElement.CopyTo(xamlTreeRoot));

            if (!isInShowCard && (xamlBuilder != nullptr))
            {
                if (xamlBuilder->m_listeners.size() == 0)
                {
                    // If we're done and no one's listening for the images to load, make sure
                    // any outstanding image loads are no longer tracked.
                    xamlBuilder->m_imageLoadTracker.AbandonOutstandingImages();
                }
                else if (xamlBuilder->m_imageLoadTracker.GetTotalImagesTracked() == 0)
                {
                    // If there are no images to track, fire the all images loaded
                    // event to signal the xaml is ready
                    xamlBuilder->FireAllImagesLoaded();
                }
            }
        }
        return S_OK;
    }

    HRESULT XamlBuilder::AddListener(_In_ IXamlBuilderListener* listener) noexcept
    try
    {
        if (m_listeners.find(listener) == m_listeners.end())
        {
            m_listeners.emplace(listener);
        }
        else
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT XamlBuilder::RemoveListener(_In_ IXamlBuilderListener* listener) noexcept
    try
    {
        if (m_listeners.find(listener) != m_listeners.end())
        {
            m_listeners.erase(listener);
        }
        else
        {
            return E_INVALIDARG;
        }
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT XamlBuilder::SetFixedDimensions(UINT width, UINT height) noexcept
    {
        m_fixedDimensions = true;
        m_fixedWidth = width;
        m_fixedHeight = height;
        return S_OK;
    }

    HRESULT XamlBuilder::SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept
    {
        m_enableXamlImageHandling = enableXamlImageHandling;
        return S_OK;
    }

    template<typename T>
    HRESULT XamlBuilder::TryGetResourceFromResourceDictionaries(_In_ IResourceDictionary* resourceDictionary,
                                                                std::wstring resourceName,
                                                                _COM_Outptr_ T** style)
    {
        if (resourceDictionary == nullptr)
        {
            return E_INVALIDARG;
        }

        *style = nullptr;
        try
        {
            // Get a resource key for the requested style that we can use for ResourceDistionary Lookups
            ComPtr<IPropertyValueStatics> propertyValueStatics;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(),
                                                 &propertyValueStatics));
            ComPtr<IInspectable> resourceKey;
            THROW_IF_FAILED(propertyValueStatics->CreateString(HStringReference(resourceName.c_str()).Get(),
                                                               resourceKey.GetAddressOf()));

            // Search for the named resource
            ComPtr<IResourceDictionary> strongDictionary = resourceDictionary;
            ComPtr<IInspectable> dictionaryValue;
            ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;

            boolean hasKey{};
            if (SUCCEEDED(strongDictionary.As(&resourceDictionaryMap)) &&
                SUCCEEDED(resourceDictionaryMap->HasKey(resourceKey.Get(), &hasKey)) && hasKey &&
                SUCCEEDED(resourceDictionaryMap->Lookup(resourceKey.Get(), dictionaryValue.GetAddressOf())))
            {
                ComPtr<T> resourceToReturn;
                if (SUCCEEDED(dictionaryValue.As(&resourceToReturn)))
                {
                    THROW_IF_FAILED(resourceToReturn.CopyTo(style));
                    return S_OK;
                }
            }
        }
        catch (...)
        {
        }
        return E_FAIL;
    }

    HRESULT XamlBuilder::TryInsertResourceToResourceDictionaries(_In_ IResourceDictionary* resourceDictionary,
                                                                 std::wstring resourceName,
                                                                 _In_ IInspectable* value)
    {
        if (resourceDictionary == nullptr)
        {
            return E_INVALIDARG;
        }

        try
        {
            ComPtr<IPropertyValueStatics> propertyValueStatics;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(),
                                                 &propertyValueStatics));

            ComPtr<IInspectable> resourceKey;
            THROW_IF_FAILED(propertyValueStatics->CreateString(HStringReference(resourceName.c_str()).Get(),
                                                               resourceKey.GetAddressOf()));

            ComPtr<IResourceDictionary> strongDictionary = resourceDictionary;
            ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;
            THROW_IF_FAILED(strongDictionary.As(&resourceDictionaryMap));

            boolean replaced{};
            THROW_IF_FAILED(resourceDictionaryMap->Insert(resourceKey.Get(), value, &replaced));
            return S_OK;
        }
        catch (...)
        {
        }
        return E_FAIL;
    }

    HRESULT XamlBuilder::SetStyleFromResourceDictionary(_In_ IAdaptiveRenderContext* renderContext,
                                                        std::wstring resourceName,
                                                        _In_ IFrameworkElement* frameworkElement)
    {
        ComPtr<IResourceDictionary> resourceDictionary;
        RETURN_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));

        ComPtr<IStyle> style;
        if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(), resourceName, &style)))
        {
            RETURN_IF_FAILED(frameworkElement->put_Style(style.Get()));
        }

        return S_OK;
    }

    ComPtr<IUIElement> XamlBuilder::CreateRootCardElement(_In_ IAdaptiveCard* adaptiveCard,
                                                          _In_ IAdaptiveRenderContext* renderContext,
                                                          _In_ IAdaptiveRenderArgs* renderArgs,
                                                          ComPtr<XamlBuilder> xamlBuilder,
                                                          _Outptr_ IPanel** bodyElementContainer)
    {
        // The root of an adaptive card is a composite of several elements, depending on the card
        // properties.  From back to front these are:
        // Grid - Root element, used to enable children to stack above each other and size to fit
        // Image (optional) - Holds the background image if one is set
        // Shape (optional) - Provides the background image overlay, if one is set
        // StackPanel - The container for all the card's body elements
        ComPtr<IGrid> rootElement =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
        THROW_IF_FAILED(hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

        ComPtr<IPanel> rootAsPanel;
        THROW_IF_FAILED(rootElement.As(&rootAsPanel));
        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

        ABI::Windows::UI::Color backgroundColor;
        if (SUCCEEDED(GetBackgroundColorFromStyle(containerStyle, hostConfig.Get(), &backgroundColor)))
        {
            ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(backgroundColor);
            THROW_IF_FAILED(rootAsPanel->put_Background(backgroundColorBrush.Get()));
        }

        ComPtr<IAdaptiveBackgroundImage> backgroundImage;
        BOOL backgroundImageIsValid;
        THROW_IF_FAILED(adaptiveCard->get_BackgroundImage(&backgroundImage));
        THROW_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));
        if (backgroundImageIsValid)
        {
            ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, renderArgs);
        }

        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        THROW_IF_FAILED(spacingConfig->get_Padding(&padding));

        // Configure WholeItemsPanel to not clip bleeding containers
        WholeItemsPanel::SetBleedMargin(padding);

        // Now create the inner stack panel to serve as the root host for all the
        // body elements and apply padding from host configuration
        ComPtr<WholeItemsPanel> bodyElementHost;
        THROW_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&bodyElementHost));
        bodyElementHost->SetMainPanel(TRUE);
        bodyElementHost->SetAdaptiveHeight(TRUE);

        ComPtr<IFrameworkElement> bodyElementHostAsElement;
        THROW_IF_FAILED(bodyElementHost.As(&bodyElementHostAsElement));
        ApplyMarginToXamlElement(hostConfig.Get(), bodyElementHostAsElement.Get());

        ABI::AdaptiveNamespace::HeightType adaptiveCardHeightType;
        THROW_IF_FAILED(adaptiveCard->get_Height(&adaptiveCardHeightType));

        XamlHelpers::AppendXamlElementToPanel(bodyElementHost.Get(), rootAsPanel.Get(), adaptiveCardHeightType);
        THROW_IF_FAILED(bodyElementHost.CopyTo(bodyElementContainer));

        if (xamlBuilder && xamlBuilder->m_fixedDimensions)
        {
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            THROW_IF_FAILED(rootElement.As(&rootAsFrameworkElement));
            rootAsFrameworkElement->put_Width(xamlBuilder->m_fixedWidth);
            rootAsFrameworkElement->put_Height(xamlBuilder->m_fixedHeight);
            rootAsFrameworkElement->put_MaxHeight(xamlBuilder->m_fixedHeight);
        }

        if (adaptiveCardHeightType == ABI::AdaptiveNamespace::HeightType::Stretch)
        {
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            THROW_IF_FAILED(rootElement.As(&rootAsFrameworkElement));
            rootAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment::VerticalAlignment_Stretch);
        }

        ComPtr<IUIElement> rootAsUIElement;
        THROW_IF_FAILED(rootElement.As(&rootAsUIElement));
        return rootAsUIElement;
    }

    void XamlBuilder::ApplyBackgroundToRoot(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
                                            _In_ IAdaptiveBackgroundImage* backgroundImage,
                                            _In_ IAdaptiveRenderContext* renderContext,
                                            _In_ IAdaptiveRenderArgs* renderArgs)
    {
        // In order to reuse the image creation code paths, we simply create an adaptive card
        // image element and then build that into xaml and apply to the root.
        ComPtr<IAdaptiveImage> adaptiveImage;
        HSTRING url;
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));
        THROW_IF_FAILED(backgroundImage->get_Url(&url));
        THROW_IF_FAILED(adaptiveImage->put_Url(url));

        ComPtr<IAdaptiveCardElement> adaptiveCardElement;
        THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));

        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

        ComPtr<IAdaptiveElementRenderer> elementRenderer;
        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &elementRenderer));

        ComPtr<IUIElement> background;
        if (elementRenderer != nullptr)
        {
            elementRenderer->Render(adaptiveCardElement.Get(), renderContext, renderArgs, &background);
            if (background == nullptr)
            {
                return;
            }
        }

        ComPtr<IImage> xamlImage;
        THROW_IF_FAILED(background.As(&xamlImage));

        ABI::AdaptiveNamespace::BackgroundImageFillMode fillMode;
        THROW_IF_FAILED(backgroundImage->get_FillMode(&fillMode));

        // Creates the background image for all fill modes
        ComPtr<TileControl> tileControl;
        THROW_IF_FAILED(MakeAndInitialize<TileControl>(&tileControl));
        THROW_IF_FAILED(tileControl->put_BackgroundImage(backgroundImage));

        // Set IsEnabled to false to avoid generating a tab stop for the background image tile control
        ComPtr<IControl> tileControlAsControl;
        THROW_IF_FAILED(tileControl.As(&tileControlAsControl));
        THROW_IF_FAILED(tileControlAsControl->put_IsEnabled(false));

        ComPtr<IFrameworkElement> rootElement;
        THROW_IF_FAILED(rootPanel->QueryInterface(rootElement.GetAddressOf()));
        THROW_IF_FAILED(tileControl->put_RootElement(rootElement.Get()));

        THROW_IF_FAILED(tileControl->LoadImageBrush(background.Get()));

        ComPtr<IFrameworkElement> backgroundAsFrameworkElement;
        THROW_IF_FAILED(tileControl.As(&backgroundAsFrameworkElement));

        XamlHelpers::AppendXamlElementToPanel(backgroundAsFrameworkElement.Get(), rootPanel);

        // The overlay applied to the background image is determined by a resouce, so create
        // the overlay if that resources exists
        ComPtr<IResourceDictionary> resourceDictionary;
        THROW_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
        ComPtr<IBrush> backgroundOverlayBrush;
        if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IBrush>(resourceDictionary.Get(), c_BackgroundImageOverlayBrushKey, &backgroundOverlayBrush)))
        {
            ComPtr<IShape> overlayRectangle =
                XamlHelpers::CreateXamlClass<IShape>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle));
            THROW_IF_FAILED(overlayRectangle->put_Fill(backgroundOverlayBrush.Get()));

            ComPtr<IUIElement> overlayRectangleAsUIElement;
            THROW_IF_FAILED(overlayRectangle.As(&overlayRectangleAsUIElement));
            XamlHelpers::AppendXamlElementToPanel(overlayRectangle.Get(), rootPanel);
        }
    }

    template<typename T>
    void XamlBuilder::SetImageSource(_In_ T* destination, _In_ IImageSource* imageSource, ABI::Windows::UI::Xaml::Media::Stretch /*stretch*/)
    {
        THROW_IF_FAILED(destination->put_Source(imageSource));
    };

    template<>
    void XamlBuilder::SetImageSource<IEllipse>(_In_ IEllipse* destination,
                                               _In_ IImageSource* imageSource,
                                               ABI::Windows::UI::Xaml::Media::Stretch stretch)
    {
        ComPtr<IImageBrush> imageBrush =
            XamlHelpers::CreateXamlClass<IImageBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_ImageBrush));
        THROW_IF_FAILED(imageBrush->put_ImageSource(imageSource));

        ComPtr<ITileBrush> tileBrush;
        THROW_IF_FAILED(imageBrush.As(&tileBrush));
        THROW_IF_FAILED(tileBrush->put_Stretch(stretch));

        ComPtr<IBrush> brush;
        THROW_IF_FAILED(imageBrush.As(&brush));

        ComPtr<IShape> ellipseAsShape;
        ComPtr<IEllipse> ellipse(destination);
        THROW_IF_FAILED(ellipse.As(&ellipseAsShape));

        THROW_IF_FAILED(ellipseAsShape->put_Fill(brush.Get()));
    };

    template<typename T>
    void XamlBuilder::SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl,
                                          _In_ T* uiElement,
                                          _In_opt_ IAdaptiveCardResourceResolvers* resolvers,
                                          bool isAutoSize,
                                          IInspectable* parentElement,
                                          IInspectable* imageContainer,
                                          bool isVisible,
                                          _Out_ bool* mustHideElement,
                                          ABI::Windows::UI::Xaml::Media::Stretch stretch)
    {
        *mustHideElement = true;

        // Get the image url scheme
        HString schemeName;
        THROW_IF_FAILED(imageUrl->get_SchemeName(schemeName.GetAddressOf()));

        // Get the resolver for the image
        ComPtr<IAdaptiveCardResourceResolver> resolver;
        if (resolvers != nullptr)
        {
            THROW_IF_FAILED(resolvers->Get(schemeName.Get(), &resolver));
            // If we have a resolver
            if (resolver != nullptr)
            {
                // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
                // the tracker to subscribe to the ImageLoaded/Failed events
                ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));

                if (!m_enableXamlImageHandling && (m_listeners.size() != 0))
                {
                    m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
                }

                THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_None));
                ComPtr<IBitmapSource> bitmapSource;
                bitmapImage.As(&bitmapSource);

                // Create the arguments to pass to the resolver
                ComPtr<IAdaptiveCardGetResourceStreamArgs> args;
                THROW_IF_FAILED(MakeAndInitialize<AdaptiveCardGetResourceStreamArgs>(&args, imageUrl));

                // And call the resolver to get the image stream
                ComPtr<IAsyncOperation<IRandomAccessStream*>> getResourceStreamOperation;
                THROW_IF_FAILED(resolver->GetResourceStreamAsync(args.Get(), &getResourceStreamOperation));

                ComPtr<T> strongImageControl(uiElement);
                ComPtr<XamlBuilder> strongThis(this);
                THROW_IF_FAILED(getResourceStreamOperation->put_Completed(
                    Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationCompletedHandler<IRandomAccessStream*>>>(
                        [strongThis, this, bitmapSource, strongImageControl, bitmapImage, stretch, isAutoSize, parentElement, imageContainer, isVisible](
                            IAsyncOperation<IRandomAccessStream*>* operation, AsyncStatus status) -> HRESULT {
                            if (status == AsyncStatus::Completed)
                            {
                                // Get the random access stream
                                ComPtr<IRandomAccessStream> randomAccessStream;
                                RETURN_IF_FAILED(operation->GetResults(&randomAccessStream));

                                if (randomAccessStream == nullptr)
                                {
                                    m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                                    return S_OK;
                                }

                                RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                                ComPtr<IImageSource> imageSource;
                                RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                                SetImageSource(strongImageControl.Get(), imageSource.Get(), stretch);

                                // Here should be the auto resizing, at this time we already have the image and everything set
                                if (isAutoSize)
                                {
                                    SetAutoSize(strongImageControl.Get(), parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                                }

                                return S_OK;
                            }
                            else
                            {
                                m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                                return S_OK;
                            }
                        })
                        .Get()));

                return;
            }
        }

        INT32 isDataUriImage{};
        THROW_IF_FAILED(WindowsCompareStringOrdinal(schemeName.Get(), HStringReference(L"data").Get(), &isDataUriImage));
        if (isDataUriImage == 0)
        {
            // Decode base 64 string
            HString dataPath;
            THROW_IF_FAILED(imageUrl->get_Path(dataPath.GetAddressOf()));

            std::string data = AdaptiveBase64Util::ExtractDataFromUri(HStringToUTF8(dataPath.Get()));
            std::vector<char> decodedData = AdaptiveBase64Util::Decode(data);

            ComPtr<IBufferFactory> bufferFactory;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_Buffer).Get(),
                                                 bufferFactory.GetAddressOf()));

            ComPtr<IBuffer> buffer;
            THROW_IF_FAILED(bufferFactory->Create(static_cast<UINT32>(decodedData.size()), buffer.GetAddressOf()));

            ComPtr<::Windows::Storage::Streams::IBufferByteAccess> bufferByteAccess;
            THROW_IF_FAILED(buffer.As(&bufferByteAccess));

            BYTE* dataInternal{};
            THROW_IF_FAILED(bufferByteAccess->Buffer(&dataInternal));

            memcpy_s(dataInternal, decodedData.size(), decodedData.data(), decodedData.size());

            THROW_IF_FAILED(buffer->put_Length(static_cast<UINT32>(decodedData.size())));

            ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
            m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
            THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_IgnoreImageCache));
            ComPtr<IBitmapSource> bitmapSource;
            THROW_IF_FAILED(bitmapImage.As(&bitmapSource));

            ComPtr<IRandomAccessStream> randomAccessStream = XamlHelpers::CreateXamlClass<IRandomAccessStream>(
                HStringReference(RuntimeClass_Windows_Storage_Streams_InMemoryRandomAccessStream));

            ComPtr<IOutputStream> outputStream;
            THROW_IF_FAILED(randomAccessStream.As(&outputStream));

            ComPtr<IAsyncOperationWithProgress<UINT32, UINT32>> bufferWriteOperation;
            THROW_IF_FAILED(outputStream->WriteAsync(buffer.Get(), &bufferWriteOperation));

            ComPtr<T> strongImageControl(uiElement);
            ComPtr<XamlBuilder> strongThis(this);
            THROW_IF_FAILED(bufferWriteOperation->put_Completed(
                Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<UINT32, UINT32>>>(
                    [strongThis, this, bitmapSource, randomAccessStream, strongImageControl, isAutoSize, parentElement, imageContainer, isVisible](
                        IAsyncOperationWithProgress<UINT32, UINT32>* /*operation*/, AsyncStatus /*status*/) -> HRESULT {
                        randomAccessStream->Seek(0);
                        RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                        ComPtr<IImageSource> imageSource;
                        RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                        SetImageSource(strongImageControl.Get(), imageSource.Get());

                        if (isAutoSize)
                        {
                            SetAutoSize(strongImageControl.Get(), parentElement, imageContainer, isVisible, false /* imageFiresOpenEvent */);
                        }

                        return S_OK;
                    })
                    .Get()));

            m_writeAsyncOperations.push_back(bufferWriteOperation);
            *mustHideElement = false;
            return;
        }

        // Otherwise, no resolver...
        if ((m_enableXamlImageHandling) || (m_listeners.size() == 0))
        {
            // If we've been explicitly told to let Xaml handle the image loading, or there are
            // no listeners waiting on the image load callbacks, use Xaml to load the images
            ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
            THROW_IF_FAILED(bitmapImage->put_UriSource(imageUrl));

            ComPtr<IImageSource> bitmapImageSource;
            THROW_IF_FAILED(bitmapImage.As(&bitmapImageSource));
            SetImageSource(uiElement, bitmapImageSource.Get(), stretch);

            if (isAutoSize)
            {
                SetAutoSize(uiElement, parentElement, imageContainer, isVisible, true /* imageFiresOpenEvent */);
            }
        }
        else
        {
            PopulateImageFromUrlAsync(imageUrl, uiElement);
        }
    }

    template<typename T>
    void XamlBuilder::PopulateImageFromUrlAsync(_In_ IUriRuntimeClass* imageUrl, _In_ T* imageControl)
    {
        // Create the HttpClient to load the image stream
        ComPtr<IHttpBaseProtocolFilter> httpBaseProtocolFilter = XamlHelpers::CreateXamlClass<IHttpBaseProtocolFilter>(
            HStringReference(RuntimeClass_Windows_Web_Http_Filters_HttpBaseProtocolFilter));
        THROW_IF_FAILED(httpBaseProtocolFilter->put_AllowUI(false));
        ComPtr<IHttpFilter> httpFilter;
        THROW_IF_FAILED(httpBaseProtocolFilter.As(&httpFilter));
        ComPtr<IHttpClient> httpClient;
        ComPtr<IHttpClientFactory> httpClientFactory;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Web_Http_HttpClient).Get(),
                                             httpClientFactory.ReleaseAndGetAddressOf()));
        THROW_IF_FAILED(httpClientFactory->Create(httpFilter.Get(), httpClient.ReleaseAndGetAddressOf()));

        // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
        // the tracker to subscribe to the ImageLoaded/Failed events
        ComPtr<IBitmapImage> bitmapImage =
            XamlHelpers::CreateXamlClass<IBitmapImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
        m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
        THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_None));
        ComPtr<IBitmapSource> bitmapSource;
        bitmapImage.As(&bitmapSource);
        ComPtr<IAsyncOperationWithProgress<IInputStream*, HttpProgress>> getStreamOperation;
        THROW_IF_FAILED(httpClient->GetInputStreamAsync(imageUrl, &getStreamOperation));

        ComPtr<T> strongImageControl(imageControl);
        ComPtr<XamlBuilder> strongThis(this);
        THROW_IF_FAILED(getStreamOperation->put_Completed(
            Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<IInputStream*, HttpProgress>>>(
                [strongThis, this, bitmapSource, strongImageControl, bitmapImage](
                    IAsyncOperationWithProgress<IInputStream*, HttpProgress>* operation, AsyncStatus status) -> HRESULT {
                    if (status == AsyncStatus::Completed)
                    {
                        // Load the image stream into an in memory random access stream, which is what
                        // SetSource needs
                        ComPtr<IInputStream> imageStream;
                        RETURN_IF_FAILED(operation->GetResults(&imageStream));
                        ComPtr<IRandomAccessStream> randomAccessStream = XamlHelpers::CreateXamlClass<IRandomAccessStream>(
                            HStringReference(RuntimeClass_Windows_Storage_Streams_InMemoryRandomAccessStream));
                        ComPtr<IOutputStream> outputStream;
                        RETURN_IF_FAILED(randomAccessStream.As(&outputStream));
                        ComPtr<IAsyncOperationWithProgress<UINT64, UINT64>> copyStreamOperation;
                        RETURN_IF_FAILED(m_randomAccessStreamStatics->CopyAsync(imageStream.Get(), outputStream.Get(), &copyStreamOperation));

                        return copyStreamOperation->put_Completed(
                            Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<UINT64, UINT64>>>(
                                [strongThis, this, bitmapSource, randomAccessStream, strongImageControl](
                                    IAsyncOperationWithProgress<UINT64, UINT64>* /*operation*/, AsyncStatus /*status*/) -> HRESULT {
                                    randomAccessStream->Seek(0);
                                    RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                                    ComPtr<IImageSource> imageSource;
                                    RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                                    SetImageSource(strongImageControl.Get(), imageSource.Get());
                                    return S_OK;
                                })
                                .Get());
                        m_copyStreamOperations.push_back(copyStreamOperation);
                    }
                    else
                    {
                        m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                        return S_OK;
                    }
                })
                .Get()));
        m_getStreamOperations.push_back(getStreamOperation);
    }

    void XamlBuilder::FireAllImagesLoaded()
    {
        for (auto& listener : m_listeners)
        {
            listener->AllImagesLoaded();
        }
    }

    void XamlBuilder::FireImagesLoadingHadError()
    {
        for (auto& listener : m_listeners)
        {
            listener->ImagesLoadingHadError();
        }
    }

    static HRESULT AddRenderedControl(_In_ IUIElement* newControl,
                                      _In_ IAdaptiveCardElement* element,
                                      _In_ IPanel* parentPanel,
                                      _In_ IUIElement* separator,
                                      _In_ IColumnDefinition* columnDefinition,
                                      std::function<void(IUIElement* child)> childCreatedCallback)
    {
        if (newControl != nullptr)
        {
            boolean isVisible;
            RETURN_IF_FAILED(element->get_IsVisible(&isVisible));

            if (!isVisible)
            {
                RETURN_IF_FAILED(newControl->put_Visibility(Visibility_Collapsed));
            }

            ComPtr<IUIElement> localControl(newControl);
            ComPtr<IFrameworkElement> newControlAsFrameworkElement;
            RETURN_IF_FAILED(localControl.As(&newControlAsFrameworkElement));

            HString id;
            RETURN_IF_FAILED(element->get_Id(id.GetAddressOf()));

            if (id.IsValid())
            {
                RETURN_IF_FAILED(newControlAsFrameworkElement->put_Name(id.Get()));
            }

            ABI::AdaptiveNamespace::HeightType heightType{};
            RETURN_IF_FAILED(element->get_Height(&heightType));

            ComPtr<ElementTagContent> tagContent;
            RETURN_IF_FAILED(MakeAndInitialize<ElementTagContent>(
                &tagContent, element, parentPanel, separator, columnDefinition, isVisible, heightType == HeightType_Stretch));
            RETURN_IF_FAILED(newControlAsFrameworkElement->put_Tag(tagContent.Get()));

            XamlHelpers::AppendXamlElementToPanel(newControl, parentPanel, heightType);

            childCreatedCallback(newControl);
        }
        return S_OK;
    }

    void XamlBuilder::AddSeparatorIfNeeded(int& currentElement,
                                           _In_ IAdaptiveCardElement* element,
                                           _In_ IAdaptiveHostConfig* hostConfig,
                                           _In_ IAdaptiveRenderContext* renderContext,
                                           _In_ IPanel* parentPanel,
                                           _Outptr_ IUIElement** addedSeparator)
    {
        // First element does not need a separator added
        if (currentElement++ > 0)
        {
            bool needsSeparator;
            UINT spacing;
            UINT separatorThickness;
            ABI::Windows::UI::Color separatorColor;
            GetSeparationConfigForElement(element, hostConfig, &spacing, &separatorThickness, &separatorColor, &needsSeparator);
            if (needsSeparator)
            {
                auto separator = CreateSeparator(renderContext, spacing, separatorThickness, separatorColor);
                XamlHelpers::AppendXamlElementToPanel(separator.Get(), parentPanel);
                THROW_IF_FAILED(separator.CopyTo(addedSeparator));
            }
        }
    }

    static inline HRESULT WarnFallbackString(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                             const std::string& warning)
    {
        HString warningMsg;
        RETURN_IF_FAILED(UTF8ToHString(warning, warningMsg.GetAddressOf()));

        RETURN_IF_FAILED(
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::PerformingFallback, warningMsg.Get()));
        return S_OK;
    }

    static inline HRESULT WarnForFallbackContentElement(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                                        _In_ HSTRING parentElementType,
                                                        _In_ HSTRING fallbackElementType)
    try
    {
        std::string warning = "Performing fallback for element of type \"";
        warning.append(HStringToUTF8(parentElementType));
        warning.append("\" (fallback element type \"");
        warning.append(HStringToUTF8(fallbackElementType));
        warning.append("\")");

        return WarnFallbackString(renderContext, warning);
    }
    CATCH_RETURN;

    static inline HRESULT WarnForFallbackDrop(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext, _In_ HSTRING elementType)
    try
    {
        std::string warning = "Dropping element of type \"";
        warning.append(HStringToUTF8(elementType));
        warning.append("\" for fallback");

        return WarnFallbackString(renderContext, warning);
    }
    CATCH_RETURN;

    HRESULT SetSeparatorVisibility(_In_ IPanel* parentPanel)
    {
        // Iterate over the elements in a container and ensure that the correct separators are marked as visible
        ComPtr<IVector<UIElement*>> children;
        RETURN_IF_FAILED(parentPanel->get_Children(&children));

        bool foundPreviousVisibleElement = false;
        XamlHelpers::IterateOverVector<UIElement, IUIElement>(children.Get(), [&](IUIElement* child) {
            ComPtr<IUIElement> localChild(child);

            ComPtr<IFrameworkElement> childAsFrameworkElement;
            RETURN_IF_FAILED(localChild.As(&childAsFrameworkElement));

            // Get the tag for the element. The separators themselves will not have tags.
            ComPtr<IInspectable> tag;
            RETURN_IF_FAILED(childAsFrameworkElement->get_Tag(&tag));

            if (tag)
            {
                ComPtr<IElementTagContent> elementTagContent;
                RETURN_IF_FAILED(tag.As(&elementTagContent));

                ComPtr<IUIElement> separator;
                RETURN_IF_FAILED(elementTagContent->get_Separator(&separator));

                Visibility visibility;
                RETURN_IF_FAILED(child->get_Visibility(&visibility));

                boolean expectedVisibility{};
                RETURN_IF_FAILED(elementTagContent->get_ExpectedVisibility(&expectedVisibility));

                if (separator)
                {
                    if (!expectedVisibility || !foundPreviousVisibleElement)
                    {
                        // If the element is collapsed, or if it's the first visible element, collapse the separator
                        // Images are hidden while they are retrieved, we shouldn't hide the separator
                        RETURN_IF_FAILED(separator->put_Visibility(Visibility_Collapsed));
                    }
                    else
                    {
                        // Otherwise show the separator
                        RETURN_IF_FAILED(separator->put_Visibility(Visibility_Visible));
                    }
                }

                foundPreviousVisibleElement |= (visibility == Visibility_Visible);
            }

            return S_OK;
        });

        return S_OK;
    }

    HRESULT XamlBuilder::RenderFallback(_In_ IAdaptiveCardElement* currentElement,
                                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                        _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** result)
    {
        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

        ABI::AdaptiveNamespace::FallbackType elementFallback;
        RETURN_IF_FAILED(currentElement->get_FallbackType(&elementFallback));

        HString elementType;
        RETURN_IF_FAILED(currentElement->get_ElementTypeString(elementType.GetAddressOf()));

        bool fallbackHandled = false;
        ComPtr<IUIElement> fallbackControl;
        switch (elementFallback)
        {
        case ABI::AdaptiveNamespace::FallbackType::Content:
        {
            // We have content, get the type of the fallback element
            ComPtr<IAdaptiveCardElement> fallbackElement;
            RETURN_IF_FAILED(currentElement->get_FallbackContent(&fallbackElement));

            HString fallbackElementType;
            RETURN_IF_FAILED(fallbackElement->get_ElementTypeString(fallbackElementType.GetAddressOf()));

            RETURN_IF_FAILED(WarnForFallbackContentElement(renderContext, elementType.Get(), fallbackElementType.Get()));

            // Try to render the fallback element
            ComPtr<IAdaptiveElementRenderer> fallbackElementRenderer;
            RETURN_IF_FAILED(elementRenderers->Get(fallbackElementType.Get(), &fallbackElementRenderer));
            HRESULT hr = E_PERFORM_FALLBACK;

            if (fallbackElementRenderer)
            {
                // perform this element's fallback
                hr = fallbackElementRenderer->Render(fallbackElement.Get(), renderContext, renderArgs, &fallbackControl);
            }

            if (hr == E_PERFORM_FALLBACK)
            {
                // The fallback content told us to fallback, make a recursive call to this method
                RETURN_IF_FAILED(RenderFallback(fallbackElement.Get(), renderContext, renderArgs, &fallbackControl));
            }
            else
            {
                // Check the non-fallback return value from the render call
                RETURN_IF_FAILED(hr);
            }

            // We handled the fallback content
            fallbackHandled = true;
            break;
        }
        case ABI::AdaptiveNamespace::FallbackType::Drop:
        {
            // If the fallback is drop, nothing to do but warn
            RETURN_IF_FAILED(WarnForFallbackDrop(renderContext, elementType.Get()));
            fallbackHandled = true;
            break;
        }
        case ABI::AdaptiveNamespace::FallbackType::None:
        default:
        {
            break;
        }
        }

        if (fallbackHandled)
        {
            // We did it, copy out the result if any
            RETURN_IF_FAILED(fallbackControl.CopyTo(result));
            return S_OK;
        }
        else
        {
            // We didn't do it, can our ancestor?
            boolean ancestorHasFallback;
            RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));

            if (!ancestorHasFallback)
            {
                // standard unknown element handling
                std::wstring errorString = L"No Renderer found for type: ";
                errorString += elementType.GetRawBuffer(nullptr);
                RETURN_IF_FAILED(renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                                                           HStringReference(errorString.c_str()).Get()));
                return S_OK;
            }
            else
            {
                return E_PERFORM_FALLBACK;
            }
        }
    }

    HRESULT XamlBuilder::BuildPanelChildren(_In_ IVector<IAdaptiveCardElement*>* children,
                                            _In_ IPanel* parentPanel,
                                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                            std::function<void(IUIElement* child)> childCreatedCallback)
    {
        int iElement = 0;
        unsigned int childrenSize;
        RETURN_IF_FAILED(children->get_Size(&childrenSize));
        boolean ancestorHasFallback;
        RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));

        ComPtr<IAdaptiveFeatureRegistration> featureRegistration;
        RETURN_IF_FAILED(renderContext->get_FeatureRegistration(&featureRegistration));
        ComPtr<AdaptiveFeatureRegistration> featureRegistrationImpl = PeekInnards<AdaptiveFeatureRegistration>(featureRegistration);
        std::shared_ptr<FeatureRegistration> sharedFeatureRegistration = featureRegistrationImpl->GetSharedFeatureRegistration();

        HRESULT hr = XamlHelpers::IterateOverVectorWithFailure<IAdaptiveCardElement>(children, ancestorHasFallback, [&](IAdaptiveCardElement* element) {
            HRESULT hr = S_OK;

            // Get fallback state
            ABI::AdaptiveNamespace::FallbackType elementFallback;
            RETURN_IF_FAILED(element->get_FallbackType(&elementFallback));
            const bool elementHasFallback = (elementFallback != FallbackType_None);
            RETURN_IF_FAILED(renderArgs->put_AncestorHasFallback(elementHasFallback || ancestorHasFallback));

            // Check to see if element's requirements are being met
            boolean requirementsMet;
            RETURN_IF_FAILED(element->MeetsRequirements(featureRegistration.Get(), &requirementsMet));
            hr = requirementsMet ? S_OK : E_PERFORM_FALLBACK;

            // Get element renderer
            ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
            ComPtr<IAdaptiveElementRenderer> elementRenderer;
            HString elementType;
            RETURN_IF_FAILED(element->get_ElementTypeString(elementType.GetAddressOf()));
            RETURN_IF_FAILED(elementRenderers->Get(elementType.Get(), &elementRenderer));

            ComPtr<IAdaptiveHostConfig> hostConfig;
            RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

            // If we have a renderer, render the element
            ComPtr<IUIElement> newControl;
            if (SUCCEEDED(hr) && elementRenderer != nullptr)
            {
                hr = elementRenderer->Render(element, renderContext, renderArgs, newControl.GetAddressOf());
            }

            // If we don't have a renderer, or if the renderer told us to perform fallback, try falling back
            if (elementRenderer == nullptr || hr == E_PERFORM_FALLBACK)
            {
                RETURN_IF_FAILED(RenderFallback(element, renderContext, renderArgs, &newControl));
            }

            // If we got a control, add a separator if needed and the control to the parent panel
            if (newControl != nullptr)
            {
                ComPtr<IUIElement> separator;
                AddSeparatorIfNeeded(iElement, element, hostConfig.Get(), renderContext, parentPanel, &separator);

                RETURN_IF_FAILED(AddRenderedControl(newControl.Get(), element, parentPanel, separator.Get(), nullptr, childCreatedCallback));
            }

            // Revert the ancestorHasFallback value
            renderArgs->put_AncestorHasFallback(ancestorHasFallback);
            return hr;
        });

        RETURN_IF_FAILED(SetSeparatorVisibility(parentPanel));
        return hr;
    }

    HRESULT XamlBuilder::BuildShowCard(_In_ IAdaptiveCard* showCard,
                                       _In_ IAdaptiveRenderContext* renderContext,
                                       _In_ IAdaptiveRenderArgs* renderArgs,
                                       bool isBottomActionBar,
                                       _Outptr_ IUIElement** uiShowCard)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(&actionsConfig));

        ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
        RETURN_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));

        ABI::AdaptiveNamespace::ContainerStyle showCardConfigStyle;
        RETURN_IF_FAILED(showCardActionConfig->get_Style(&showCardConfigStyle));

        boolean wasInShowCard;
        RETURN_IF_FAILED(renderArgs->get_IsInShowCard(&wasInShowCard));
        RETURN_IF_FAILED(renderArgs->put_IsInShowCard(true));

        ComPtr<IFrameworkElement> localUiShowCard;
        RETURN_IF_FAILED(BuildXamlTreeFromAdaptiveCard(showCard, localUiShowCard.GetAddressOf(), renderContext, nullptr, showCardConfigStyle));

        RETURN_IF_FAILED(renderArgs->put_IsInShowCard(wasInShowCard));

        ComPtr<IGrid2> showCardGrid;
        RETURN_IF_FAILED(localUiShowCard.As(&showCardGrid));

        // Set the padding
        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        RETURN_IF_FAILED(spacingConfig->get_Padding(&padding));

        ABI::AdaptiveNamespace::ActionMode showCardActionMode;
        RETURN_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        // Set the top margin
        ComPtr<IFrameworkElement> showCardFrameworkElement;
        RETURN_IF_FAILED(localUiShowCard.As(&showCardFrameworkElement));

        UINT32 inlineTopMargin;
        RETURN_IF_FAILED(showCardActionConfig->get_InlineTopMargin(&inlineTopMargin));

        double sideMargin = (double)padding * -1;
        double topMargin = isBottomActionBar ? inlineTopMargin + padding : inlineTopMargin;
        double bottomMargin = isBottomActionBar ? (double)padding * -1 : 0;

        Thickness margin = {sideMargin, topMargin, sideMargin, bottomMargin};
        RETURN_IF_FAILED(showCardFrameworkElement->put_Margin(margin));

        ComPtr<IUIElement> showCardUIElement;
        RETURN_IF_FAILED(localUiShowCard.As(&showCardUIElement));

        // Set the visibility as Collapsed until the action is triggered
        RETURN_IF_FAILED(showCardUIElement->put_Visibility(Visibility_Collapsed));

        *uiShowCard = showCardUIElement.Detach();
        return S_OK;
    }

    void XamlBuilder::ArrangeButtonContent(_In_ IAdaptiveActionElement* action,
                                           _In_ IAdaptiveActionsConfig* actionsConfig,
                                           _In_ IAdaptiveRenderContext* renderContext,
                                           ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                           _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                           bool allActionsHaveIcons,
                                           _In_ IButton* button)
    {
        HString title;
        THROW_IF_FAILED(action->get_Title(title.GetAddressOf()));

        HSTRING iconUrl;
        THROW_IF_FAILED(action->get_IconUrl(&iconUrl));

        ComPtr<IButton> localButton(button);
        ComPtr<IAutomationPropertiesStatics> automationProperties;
        THROW_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationProperties));
        ComPtr<IDependencyObject> buttonAsDependencyObject;
        THROW_IF_FAILED(localButton.As(&buttonAsDependencyObject));
        THROW_IF_FAILED(automationProperties->SetName(buttonAsDependencyObject.Get(), title.Get()));

        // Check if the button has an iconUrl
        if (iconUrl != nullptr)
        {
            // Get icon configs
            ABI::AdaptiveNamespace::IconPlacement iconPlacement;
            UINT32 iconSize;

            THROW_IF_FAILED(actionsConfig->get_IconPlacement(&iconPlacement));
            THROW_IF_FAILED(actionsConfig->get_IconSize(&iconSize));

            // Define the alignment for the button contents
            ComPtr<IStackPanel> buttonContentsStackPanel =
                XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

            // Create image and add it to the button
            ComPtr<IAdaptiveImage> adaptiveImage;
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));

            adaptiveImage->put_Url(iconUrl);
            adaptiveImage->put_HorizontalAlignment(ABI::AdaptiveNamespace::HAlignment::Center);

            ComPtr<IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
            ComPtr<AdaptiveRenderArgs> childRenderArgs;
            THROW_IF_FAILED(
                MakeAndInitialize<AdaptiveRenderArgs>(&childRenderArgs, containerStyle, buttonContentsStackPanel.Get(), nullptr));

            ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

            ComPtr<IUIElement> buttonIcon;
            ComPtr<IAdaptiveElementRenderer> elementRenderer;
            THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &elementRenderer));
            if (elementRenderer != nullptr)
            {
                elementRenderer->Render(adaptiveCardElement.Get(), renderContext, childRenderArgs.Get(), &buttonIcon);
                if (buttonIcon == nullptr)
                {
                    XamlHelpers::SetContent(localButton.Get(), title.Get());
                    return;
                }
            }

            // Create title text block
            ComPtr<ITextBlock> buttonText =
                XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            THROW_IF_FAILED(buttonText->put_Text(title.Get()));
            THROW_IF_FAILED(buttonText->put_TextAlignment(TextAlignment::TextAlignment_Center));

            // Handle different arrangements inside button
            ComPtr<IFrameworkElement> buttonIconAsFrameworkElement;
            THROW_IF_FAILED(buttonIcon.As(&buttonIconAsFrameworkElement));
            ComPtr<IUIElement> separator;
            if (iconPlacement == ABI::AdaptiveNamespace::IconPlacement::AboveTitle && allActionsHaveIcons)
            {
                THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Vertical));

                // Set icon height to iconSize (aspect ratio is automatically maintained)
                THROW_IF_FAILED(buttonIconAsFrameworkElement->put_Height(iconSize));
            }
            else
            {
                THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Horizontal));

                // Add event to the image to resize itself when the textblock is rendered
                ComPtr<IImage> buttonIconAsImage;
                THROW_IF_FAILED(buttonIcon.As(&buttonIconAsImage));

                EventRegistrationToken eventToken;
                THROW_IF_FAILED(buttonIconAsImage->add_ImageOpened(
                    Callback<IRoutedEventHandler>([buttonIconAsFrameworkElement,
                                                   buttonText](IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                        ComPtr<IFrameworkElement> buttonTextAsFrameworkElement;
                        RETURN_IF_FAILED(buttonText.As(&buttonTextAsFrameworkElement));

                        return SetMatchingHeight(buttonIconAsFrameworkElement.Get(), buttonTextAsFrameworkElement.Get());
                    }).Get(),
                    &eventToken));

                // Only add spacing when the icon must be located at the left of the title
                UINT spacingSize;
                THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig, ABI::AdaptiveNamespace::Spacing::Default, &spacingSize));

                ABI::Windows::UI::Color color = {0};
                separator = CreateSeparator(renderContext, spacingSize, spacingSize, color, false);
            }

            ComPtr<IPanel> buttonContentsPanel;
            THROW_IF_FAILED(buttonContentsStackPanel.As(&buttonContentsPanel));

            // Add image to stack panel
            XamlHelpers::AppendXamlElementToPanel(buttonIcon.Get(), buttonContentsPanel.Get());

            // Add separator to stack panel
            if (separator != nullptr)
            {
                XamlHelpers::AppendXamlElementToPanel(separator.Get(), buttonContentsPanel.Get());
            }

            // Add text to stack panel
            XamlHelpers::AppendXamlElementToPanel(buttonText.Get(), buttonContentsPanel.Get());

            // Finally, put the stack panel inside the final button
            ComPtr<IContentControl> buttonContentControl;
            THROW_IF_FAILED(localButton.As(&buttonContentControl));
            THROW_IF_FAILED(buttonContentControl->put_Content(buttonContentsPanel.Get()));
        }
        else
        {
            XamlHelpers::SetContent(localButton.Get(), title.Get());
        }
    }

    HRESULT HandleColumnWidth(_In_ IAdaptiveColumn* column, boolean isVisible, _In_ IColumnDefinition* columnDefinition)
    {
        HString adaptiveColumnWidth;
        RETURN_IF_FAILED(column->get_Width(adaptiveColumnWidth.GetAddressOf()));

        INT32 isStretchResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"stretch").Get(), &isStretchResult));
        const boolean isStretch = (isStretchResult == 0);

        INT32 isAutoResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"auto").Get(), &isAutoResult));
        const boolean isAuto = (isAutoResult == 0);

        double widthAsDouble = _wtof(adaptiveColumnWidth.GetRawBuffer(nullptr));
        UINT32 pixelWidth = 0;
        RETURN_IF_FAILED(column->get_PixelWidth(&pixelWidth));

        // Valid widths are "auto", "stretch", a pixel width ("50px"), unset, or a value greater than 0 to use as a star value ("2")
        const boolean isValidWidth = isAuto || isStretch || pixelWidth || !adaptiveColumnWidth.IsValid() || (widthAsDouble > 0);

        GridLength columnWidth;
        if (!isVisible || isAuto || !isValidWidth)
        {
            // If the column isn't visible, or is set to "auto" or an invalid value ("-1", "foo"), set it to Auto
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Auto;
            columnWidth.Value = 0;
        }
        else if (pixelWidth)
        {
            // If it's visible and pixel width is specified, use pixel width
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Pixel;
            columnWidth.Value = pixelWidth;
        }
        else if (isStretch || !adaptiveColumnWidth.IsValid())
        {
            // If it's visible and stretch is specified, or width is unset, use stretch with default of 1
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
            columnWidth.Value = 1;
        }
        else
        {
            // If it's visible and the user specified a valid non-pixel width, use that as a star width
            columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
            columnWidth.Value = _wtof(adaptiveColumnWidth.GetRawBuffer(nullptr));
        }

        RETURN_IF_FAILED(columnDefinition->put_Width(columnWidth));

        return S_OK;
    }

    HRESULT XamlBuilder::HandleToggleVisibilityClick(_In_ IFrameworkElement* cardFrameworkElement, _In_ IAdaptiveActionElement* action)
    {
        ComPtr<IAdaptiveActionElement> localAction(action);
        ComPtr<IAdaptiveToggleVisibility> toggleAction;
        RETURN_IF_FAILED(localAction.As(&toggleAction));

        ComPtr<IVector<AdaptiveToggleVisibilityTarget*>> targets;
        RETURN_IF_FAILED(toggleAction->get_TargetElements(&targets));

        ComPtr<IIterable<AdaptiveToggleVisibilityTarget*>> targetsIterable;
        RETURN_IF_FAILED(targets.As<IIterable<AdaptiveToggleVisibilityTarget*>>(&targetsIterable));

        boolean hasCurrent;
        ComPtr<IIterator<AdaptiveToggleVisibilityTarget*>> targetIterator;
        HRESULT hr = targetsIterable->First(&targetIterator);
        RETURN_IF_FAILED(targetIterator->get_HasCurrent(&hasCurrent));

        std::unordered_set<IPanel*> parentPanels;
        while (SUCCEEDED(hr) && hasCurrent)
        {
            ComPtr<IAdaptiveToggleVisibilityTarget> currentTarget;
            RETURN_IF_FAILED(targetIterator->get_Current(&currentTarget));

            HString toggleId;
            RETURN_IF_FAILED(currentTarget->get_ElementId(toggleId.GetAddressOf()));

            ABI::AdaptiveNamespace::IsVisible toggle;
            RETURN_IF_FAILED(currentTarget->get_IsVisible(&toggle));

            ComPtr<IInspectable> toggleElement;
            RETURN_IF_FAILED(cardFrameworkElement->FindName(toggleId.Get(), &toggleElement));

            if (toggleElement != nullptr)
            {
                ComPtr<IUIElement> toggleElementAsUIElement;
                RETURN_IF_FAILED(toggleElement.As(&toggleElementAsUIElement));

                ComPtr<IFrameworkElement> toggleElementAsFrameworkElement;
                RETURN_IF_FAILED(toggleElement.As(&toggleElementAsFrameworkElement));

                ComPtr<IInspectable> tag;
                RETURN_IF_FAILED(toggleElementAsFrameworkElement->get_Tag(&tag));

                ComPtr<IElementTagContent> elementTagContent;
                RETURN_IF_FAILED(tag.As(&elementTagContent));

                Visibility visibilityToSet = Visibility_Visible;
                if (toggle == ABI::AdaptiveNamespace::IsVisible_IsVisibleTrue)
                {
                    visibilityToSet = Visibility_Visible;
                }
                else if (toggle == ABI::AdaptiveNamespace::IsVisible_IsVisibleFalse)
                {
                    visibilityToSet = Visibility_Collapsed;
                }
                else if (toggle == ABI::AdaptiveNamespace::IsVisible_IsVisibleToggle)
                {
                    boolean currentVisibility{};
                    RETURN_IF_FAILED(elementTagContent->get_ExpectedVisibility(&currentVisibility));
                    visibilityToSet = (currentVisibility) ? Visibility_Collapsed : Visibility_Visible;
                }

                RETURN_IF_FAILED(toggleElementAsUIElement->put_Visibility(visibilityToSet));
                RETURN_IF_FAILED(elementTagContent->set_ExpectedVisibility(visibilityToSet == Visibility_Visible));

                ComPtr<IPanel> parentPanel;
                RETURN_IF_FAILED(elementTagContent->get_ParentPanel(&parentPanel));
                parentPanels.insert(parentPanel.Get());

                ComPtr<IAdaptiveCardElement> cardElement;
                RETURN_IF_FAILED(elementTagContent->get_AdaptiveCardElement(&cardElement));

                // If the element we're toggling is a column, we'll need to change the width on the column definition
                ComPtr<IAdaptiveColumn> cardElementAsColumn;
                if (SUCCEEDED(cardElement.As(&cardElementAsColumn)))
                {
                    ComPtr<IColumnDefinition> columnDefinition;
                    RETURN_IF_FAILED(elementTagContent->get_ColumnDefinition(&columnDefinition));
                    RETURN_IF_FAILED(HandleColumnWidth(cardElementAsColumn.Get(),
                                                       (visibilityToSet == Visibility_Visible),
                                                       columnDefinition.Get()));
                }
            }

            hr = targetIterator->MoveNext(&hasCurrent);
        }

        for (auto parentPanel : parentPanels)
        {
            if (parentPanel)
            {
                SetSeparatorVisibility(parentPanel);
            }
        }

        return S_OK;
    }

    HRESULT XamlBuilder::BuildActionSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                        _COM_Outptr_ IUIElement** actionSetControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"ActionSet was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveActionSet> adaptiveActionSet;
        RETURN_IF_FAILED(cardElement.As(&adaptiveActionSet));

        ComPtr<IVector<IAdaptiveActionElement*>> actions;
        RETURN_IF_FAILED(adaptiveActionSet->get_Actions(&actions));

        return BuildActionSetHelper(adaptiveActionSet.Get(), actions.Get(), renderContext, renderArgs, actionSetControl);
    }

    HRESULT XamlBuilder::BuildActions(_In_ IVector<IAdaptiveActionElement*>* children,
                                      _In_ IPanel* bodyPanel,
                                      bool insertSeparator,
                                      _In_ IAdaptiveRenderContext* renderContext,
                                      _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        // Create a separator between the body and the actions
        if (insertSeparator)
        {
            ABI::AdaptiveNamespace::Spacing spacing;
            RETURN_IF_FAILED(actionsConfig->get_Spacing(&spacing));

            UINT spacingSize;
            RETURN_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), spacing, &spacingSize));

            ABI::Windows::UI::Color color = {0};
            auto separator = CreateSeparator(renderContext, spacingSize, 0, color);
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), bodyPanel);
        }

        ComPtr<IUIElement> actionSetControl;
        RETURN_IF_FAILED(BuildActionSetHelper(nullptr, children, renderContext, renderArgs, &actionSetControl));

        XamlHelpers::AppendXamlElementToPanel(actionSetControl.Get(), bodyPanel);
        return S_OK;
    }

    Thickness XamlBuilder::GetButtonMargin(_In_ IAdaptiveActionsConfig* actionsConfig)
    {
        UINT32 buttonSpacing;
        THROW_IF_FAILED(actionsConfig->get_ButtonSpacing(&buttonSpacing));

        ABI::AdaptiveNamespace::ActionsOrientation actionsOrientation;
        THROW_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        Thickness buttonMargin = {0, 0, 0, 0};
        if (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
        {
            buttonMargin.Left = buttonMargin.Right = buttonSpacing / 2;
        }
        else
        {
            buttonMargin.Top = buttonMargin.Bottom = buttonSpacing / 2;
        }

        return buttonMargin;
    }

    HRESULT XamlBuilder::BuildActionSetHelper(_In_opt_ IAdaptiveActionSet* adaptiveActionSet,
                                              _In_ IVector<IAdaptiveActionElement*>* children,
                                              _In_ IAdaptiveRenderContext* renderContext,
                                              _In_ IAdaptiveRenderArgs* renderArgs,
                                              _Outptr_ IUIElement** actionSetControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        ABI::AdaptiveNamespace::ActionAlignment actionAlignment;
        RETURN_IF_FAILED(actionsConfig->get_ActionAlignment(&actionAlignment));

        ABI::AdaptiveNamespace::ActionsOrientation actionsOrientation;
        RETURN_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        // Declare the panel that will host the buttons
        ComPtr<IPanel> actionsPanel;
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;

        if (actionAlignment == ABI::AdaptiveNamespace::ActionAlignment::Stretch &&
            actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
        {
            // If stretch alignment and orientation is horizontal, we use a grid with equal column widths to achieve
            // stretch behavior. For vertical orientation, we'll still just use a stack panel since the concept of
            // stretching buttons height isn't really valid, especially when the height of cards are typically dynamic.
            ComPtr<IGrid> actionsGrid =
                XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            RETURN_IF_FAILED(actionsGrid->get_ColumnDefinitions(&columnDefinitions));
            RETURN_IF_FAILED(actionsGrid.As(&actionsPanel));
        }
        else
        {
            // Create a stack panel for the action buttons
            ComPtr<IStackPanel> actionStackPanel =
                XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

            auto uiOrientation = (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal) ?
                Orientation::Orientation_Horizontal :
                Orientation::Orientation_Vertical;

            RETURN_IF_FAILED(actionStackPanel->put_Orientation(uiOrientation));

            ComPtr<IFrameworkElement> actionsFrameworkElement;
            RETURN_IF_FAILED(actionStackPanel.As(&actionsFrameworkElement));

            switch (actionAlignment)
            {
            case ABI::AdaptiveNamespace::ActionAlignment::Center:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Center));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Left:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Right:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Stretch:
                RETURN_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Stretch));
                break;
            }

            // Add the action buttons to the stack panel
            RETURN_IF_FAILED(actionStackPanel.As(&actionsPanel));
        }

        Thickness buttonMargin = GetButtonMargin(actionsConfig.Get());
        if (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
        {
            // Negate the spacing on the sides so the left and right buttons are flush on the side.
            // We do NOT remove the margin from the individual button itself, since that would cause
            // the equal columns stretch behavior to not have equal columns (since the first and last
            // button would be narrower without the same margins as its peers).
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            RETURN_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({buttonMargin.Left * -1, 0, buttonMargin.Right * -1, 0}));
        }
        else
        {
            // Negate the spacing on the top and bottom so the first and last buttons don't have extra padding
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            RETURN_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({0, buttonMargin.Top * -1, 0, buttonMargin.Bottom * -1}));
        }

        UINT32 maxActions;
        RETURN_IF_FAILED(actionsConfig->get_MaxActions(&maxActions));

        bool allActionsHaveIcons{true};
        XamlHelpers::IterateOverVector<IAdaptiveActionElement>(children, [&](IAdaptiveActionElement* child) {
            HSTRING iconUrl;
            RETURN_IF_FAILED(child->get_IconUrl(&iconUrl));

            bool iconUrlIsEmpty = WindowsIsStringEmpty(iconUrl);
            if (iconUrlIsEmpty)
            {
                allActionsHaveIcons = false;
            }
            return S_OK;
        });

        UINT currentAction = 0;

        RETURN_IF_FAILED(renderArgs->put_AllowAboveTitleIconPlacement(allActionsHaveIcons));

        std::shared_ptr<std::vector<ComPtr<IUIElement>>> allShowCards = std::make_shared<std::vector<ComPtr<IUIElement>>>();
        ComPtr<IStackPanel> showCardsStackPanel =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));
        XamlHelpers::IterateOverVector<IAdaptiveActionElement>(children, [&](IAdaptiveActionElement* child) {
            if (currentAction < maxActions)
            {
                // Render each action using the registered renderer
                ComPtr<IAdaptiveActionElement> action(child);
                ComPtr<IAdaptiveActionRendererRegistration> actionRegistration;
                RETURN_IF_FAILED(renderContext->get_ActionRenderers(&actionRegistration));

                ComPtr<IAdaptiveActionRenderer> renderer;
                while (!renderer)
                {
                    HString actionTypeString;
                    RETURN_IF_FAILED(action->get_ActionTypeString(actionTypeString.GetAddressOf()));
                    RETURN_IF_FAILED(actionRegistration->Get(actionTypeString.Get(), &renderer));
                    if (!renderer)
                    {
                        ABI::AdaptiveNamespace::FallbackType actionFallbackType;
                        action->get_FallbackType(&actionFallbackType);
                        switch (actionFallbackType)
                        {
                        case ABI::AdaptiveNamespace::FallbackType::Drop:
                        {
                            RETURN_IF_FAILED(WarnForFallbackDrop(renderContext, actionTypeString.Get()));
                            return S_OK;
                        }

                        case ABI::AdaptiveNamespace::FallbackType::Content:
                        {
                            ComPtr<IAdaptiveActionElement> actionFallback;
                            RETURN_IF_FAILED(action->get_FallbackContent(&actionFallback));

                            HString fallbackTypeString;
                            RETURN_IF_FAILED(actionFallback->get_ActionTypeString(fallbackTypeString.GetAddressOf()));
                            RETURN_IF_FAILED(
                                WarnForFallbackContentElement(renderContext, actionTypeString.Get(), fallbackTypeString.Get()));

                            action = actionFallback;
                            break;
                        }

                        case ABI::AdaptiveNamespace::FallbackType::None:
                        default:
                            return E_FAIL;
                        }
                    }
                }

                ComPtr<IUIElement> actionControl;
                RETURN_IF_FAILED(renderer->Render(action.Get(), renderContext, renderArgs, &actionControl));

                XamlHelpers::AppendXamlElementToPanel(actionControl.Get(), actionsPanel.Get());

                ABI::AdaptiveNamespace::ActionType actionType;
                RETURN_IF_FAILED(action->get_ActionType(&actionType));

                // Build inline show cards if needed
                if (actionType == ABI::AdaptiveNamespace::ActionType_ShowCard)
                {
                    ComPtr<IUIElement> uiShowCard;

                    ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
                    RETURN_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));

                    ABI::AdaptiveNamespace::ActionMode showCardActionMode;
                    RETURN_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

                    if (showCardActionMode == ABI::AdaptiveNamespace::ActionMode::Inline)
                    {
                        ComPtr<IAdaptiveShowCardAction> showCardAction;
                        RETURN_IF_FAILED(action.As(&showCardAction));

                        ComPtr<IAdaptiveCard> showCard;
                        RETURN_IF_FAILED(showCardAction->get_Card(&showCard));

                        RETURN_IF_FAILED(BuildShowCard(
                            showCard.Get(), renderContext, renderArgs, (adaptiveActionSet == nullptr), uiShowCard.GetAddressOf()));

                        ComPtr<IPanel> showCardsPanel;
                        RETURN_IF_FAILED(showCardsStackPanel.As(&showCardsPanel));
                        XamlHelpers::AppendXamlElementToPanel(uiShowCard.Get(), showCardsPanel.Get());

                        RETURN_IF_FAILED(
                            renderContext->AddInlineShowCard(adaptiveActionSet, showCardAction.Get(), uiShowCard.Get()));
                    }
                }

                if (columnDefinitions != nullptr)
                {
                    // If using the equal width columns, we'll add a column and assign the column
                    ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                    RETURN_IF_FAILED(columnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Star}));
                    RETURN_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

                    ComPtr<IFrameworkElement> actionFrameworkElement;
                    THROW_IF_FAILED(actionControl.As(&actionFrameworkElement));
                    THROW_IF_FAILED(gridStatics->SetColumn(actionFrameworkElement.Get(), currentAction));
                }
            }
            else
            {
                renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::MaxActionsExceeded,
                                          HStringReference(L"Some actions were not rendered due to exceeding the maximum number of actions allowed")
                                              .Get());
            }
            currentAction++;
            return S_OK;
        });

        // Reset icon placement value
        RETURN_IF_FAILED(renderArgs->put_AllowAboveTitleIconPlacement(false));

        ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
        RETURN_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
        RETURN_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Actions", actionsPanelAsFrameworkElement.Get()));

        ComPtr<IStackPanel> actionSet =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IPanel> actionSetAsPanel;
        actionSet.As(&actionSetAsPanel);

        // Add buttons and show cards to panel
        XamlHelpers::AppendXamlElementToPanel(actionsPanel.Get(), actionSetAsPanel.Get());
        XamlHelpers::AppendXamlElementToPanel(showCardsStackPanel.Get(), actionSetAsPanel.Get());

        return actionSetAsPanel.CopyTo(actionSetControl);
    }

    HRESULT XamlBuilder::BuildAction(_In_ IAdaptiveActionElement* adaptiveActionElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ IUIElement** actionControl)
    {
        // Render a button for the action
        ComPtr<IAdaptiveActionElement> action(adaptiveActionElement);
        ABI::AdaptiveNamespace::ActionType actionType;
        RETURN_IF_FAILED(action->get_ActionType(&actionType));

        ComPtr<IButton> button;
        try
        {
            CreateAppropriateButton(actionType, button);
        }
        CATCH_RETURN;

        ComPtr<IFrameworkElement> buttonFrameworkElement;
        RETURN_IF_FAILED(button.As(&buttonFrameworkElement));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        RETURN_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        Thickness buttonMargin = GetButtonMargin(actionsConfig.Get());
        RETURN_IF_FAILED(buttonFrameworkElement->put_Margin(buttonMargin));

        ABI::AdaptiveNamespace::ActionsOrientation actionsOrientation;
        RETURN_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        ABI::AdaptiveNamespace::ActionAlignment actionAlignment;
        RETURN_IF_FAILED(actionsConfig->get_ActionAlignment(&actionAlignment));

        if (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
        {
            // For horizontal alignment, we always use stretch
            RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(
                ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Stretch));
        }
        else
        {
            switch (actionAlignment)
            {
            case ABI::AdaptiveNamespace::ActionAlignment::Center:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Center));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Left:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Right:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Stretch:
                RETURN_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Stretch));
                break;
            }
        }

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        renderArgs->get_ContainerStyle(&containerStyle);

        boolean allowAboveTitleIconPlacement;
        RETURN_IF_FAILED(renderArgs->get_AllowAboveTitleIconPlacement(&allowAboveTitleIconPlacement));

        ArrangeButtonContent(action.Get(),
                             actionsConfig.Get(),
                             renderContext,
                             containerStyle,
                             hostConfig.Get(),
                             allowAboveTitleIconPlacement,
                             button.Get());

        ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
        RETURN_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));
        ABI::AdaptiveNamespace::ActionMode showCardActionMode;
        RETURN_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));
        std::shared_ptr<std::vector<ComPtr<IUIElement>>> allShowCards = std::make_shared<std::vector<ComPtr<IUIElement>>>();

        // Add click handler which calls IAdaptiveActionInvoker::SendActionEvent
        ComPtr<IButtonBase> buttonBase;
        RETURN_IF_FAILED(button.As(&buttonBase));

        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        RETURN_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));
        EventRegistrationToken clickToken;
        RETURN_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>([action, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs *
                                                                                                     /*args*/) -> HRESULT {
                                                   return actionInvoker->SendActionEvent(action.Get());
                                               }).Get(),
                                               &clickToken));

        RETURN_IF_FAILED(HandleActionStyling(adaptiveActionElement, buttonFrameworkElement.Get(), renderContext));

        ComPtr<IUIElement> buttonAsUIElement;
        RETURN_IF_FAILED(button.As(&buttonAsUIElement));
        *actionControl = buttonAsUIElement.Detach();
        return S_OK;
    }

    HRESULT XamlBuilder::HandleActionStyling(_In_ IAdaptiveActionElement* adaptiveActionElement,
                                             _In_ IFrameworkElement* buttonFrameworkElement,
                                             _In_ IAdaptiveRenderContext* renderContext)
    {
        HString actionSentiment;
        RETURN_IF_FAILED(adaptiveActionElement->get_Style(actionSentiment.GetAddressOf()));

        INT32 isSentimentPositive{}, isSentimentDestructive{}, isSentimentDefault{};

        ComPtr<IResourceDictionary> resourceDictionary;
        RETURN_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
        ComPtr<IStyle> styleToApply;

        ComPtr<AdaptiveNamespace::AdaptiveRenderContext> contextImpl =
            PeekInnards<AdaptiveNamespace::AdaptiveRenderContext>(renderContext);

        if ((SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"default").Get(), &isSentimentDefault)) &&
             (isSentimentDefault == 0)) ||
            WindowsIsStringEmpty(actionSentiment.Get()))
        {
            RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Action", buttonFrameworkElement));
        }
        else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"positive").Get(), &isSentimentPositive)) &&
                 (isSentimentPositive == 0))
        {
            if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(), L"Adaptive.Action.Positive", &styleToApply)))
            {
                RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
            }
            else
            {
                // By default, set the action background color to accent color
                ComPtr<IResourceDictionary> actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

                if (SUCCEEDED(TryGetResourceFromResourceDictionaries(actionSentimentDictionary.Get(),
                                                                     L"PositiveActionDefaultStyle",
                                                                     styleToApply.GetAddressOf())))
                {
                    RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                }
            }
        }
        else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"destructive").Get(), &isSentimentDestructive)) &&
                 (isSentimentDestructive == 0))
        {
            if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(), L"Adaptive.Action.Destructive", &styleToApply)))
            {
                RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
            }
            else
            {
                // By default, set the action text color to attention color
                ComPtr<IResourceDictionary> actionSentimentDictionary = contextImpl->GetDefaultActionSentimentDictionary();

                if (SUCCEEDED(TryGetResourceFromResourceDictionaries(actionSentimentDictionary.Get(),
                                                                     L"DestructiveActionDefaultStyle",
                                                                     styleToApply.GetAddressOf())))
                {
                    RETURN_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                }
            }
        }
        else
        {
            HString actionSentimentStyle;
            RETURN_IF_FAILED(WindowsConcatString(HStringReference(L"Adaptive.Action.").Get(),
                                                 actionSentiment.Get(),
                                                 actionSentimentStyle.GetAddressOf()));
            RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext,
                                                            StringToWstring(HStringToUTF8(actionSentimentStyle.Get())),
                                                            buttonFrameworkElement));
        }
        return S_OK;
    }

    void XamlBuilder::ApplyMarginToXamlElement(_In_ IAdaptiveHostConfig* hostConfig, _In_ IFrameworkElement* element)
    {
        ComPtr<IFrameworkElement> localElement(element);
        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        spacingConfig->get_Padding(&padding);
        Thickness margin = {(double)padding, (double)padding, (double)padding, (double)padding};

        THROW_IF_FAILED(localElement->put_Margin(margin));
    }

    void XamlBuilder::GetSeparationConfigForElement(_In_ IAdaptiveCardElement* cardElement,
                                                    _In_ IAdaptiveHostConfig* hostConfig,
                                                    _Out_ UINT* spacing,
                                                    _Out_ UINT* separatorThickness,
                                                    _Out_ ABI::Windows::UI::Color* separatorColor,
                                                    _Out_ bool* needsSeparator)
    {
        ABI::AdaptiveNamespace::Spacing elementSpacing;
        THROW_IF_FAILED(cardElement->get_Spacing(&elementSpacing));

        UINT localSpacing;
        THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig, elementSpacing, &localSpacing));

        boolean hasSeparator;
        THROW_IF_FAILED(cardElement->get_Separator(&hasSeparator));

        ABI::Windows::UI::Color localColor = {0};
        UINT localThickness = 0;
        if (hasSeparator)
        {
            ComPtr<IAdaptiveSeparatorConfig> separatorConfig;
            THROW_IF_FAILED(hostConfig->get_Separator(&separatorConfig));

            THROW_IF_FAILED(separatorConfig->get_LineColor(&localColor));
            THROW_IF_FAILED(separatorConfig->get_LineThickness(&localThickness));
        }

        *needsSeparator = hasSeparator || (elementSpacing != ABI::AdaptiveNamespace::Spacing::None);

        *spacing = localSpacing;
        *separatorThickness = localThickness;
        *separatorColor = localColor;
    }

    HRESULT XamlBuilder::BuildRichTextBlock(ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                            ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                            ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                            ABI::Windows::UI::Xaml::IUIElement** textBlockControl)
    {
        // Create the top level rich text block and set it's properties
        ComPtr<IRichTextBlock> xamlRichTextBlock =
            XamlHelpers::CreateXamlClass<IRichTextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RichTextBlock));

        ComPtr<IAdaptiveCardElement> localAdaptiveCardElement(adaptiveCardElement);
        ComPtr<IAdaptiveRichTextBlock> adaptiveRichTextBlock;
        RETURN_IF_FAILED(localAdaptiveCardElement.As(&adaptiveRichTextBlock));

        // Set the horizontal Alingment
        RETURN_IF_FAILED(SetHorizontalAlignment(adaptiveRichTextBlock.Get(), xamlRichTextBlock.Get()));

        // Get the highlighters
        ComPtr<IRichTextBlock5> xamlRichTextBlock5;
        RETURN_IF_FAILED(xamlRichTextBlock.As(&xamlRichTextBlock5));

        ComPtr<IVector<TextHighlighter*>> textHighlighters;
        RETURN_IF_FAILED(xamlRichTextBlock5->get_TextHighlighters(&textHighlighters));

        // Add a paragraph for the inlines
        ComPtr<IVector<Block*>> xamlBlocks;
        RETURN_IF_FAILED(xamlRichTextBlock->get_Blocks(&xamlBlocks));

        ComPtr<IParagraph> xamlParagraph =
            XamlHelpers::CreateXamlClass<IParagraph>(HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Paragraph));

        ComPtr<IBlock> paragraphAsBlock;
        RETURN_IF_FAILED(xamlParagraph.As(&paragraphAsBlock));
        RETURN_IF_FAILED(xamlBlocks->Append(paragraphAsBlock.Get()));

        // Add the Inlines
        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> xamlInlines;
        RETURN_IF_FAILED(xamlParagraph->get_Inlines(&xamlInlines));

        ComPtr<IVector<IAdaptiveInline*>> adaptiveInlines;
        RETURN_IF_FAILED(adaptiveRichTextBlock->get_Inlines(&adaptiveInlines));

        UINT currentOffset = 0;
        XamlHelpers::IterateOverVector<IAdaptiveInline>(adaptiveInlines.Get(), [&](IAdaptiveInline* adaptiveInline) {
            // We only support TextRun inlines for now
            ComPtr<IAdaptiveInline> localInline(adaptiveInline);
            ComPtr<IAdaptiveTextRun> adaptiveTextRun;
            RETURN_IF_FAILED(localInline.As(&adaptiveTextRun));

            ComPtr<IAdaptiveActionElement> selectAction;
            RETURN_IF_FAILED(adaptiveTextRun->get_SelectAction(&selectAction));

            ComPtr<IAdaptiveTextElement> adaptiveTextElement;
            RETURN_IF_FAILED(localInline.As(&adaptiveTextElement));

            HString text;
            RETURN_IF_FAILED(adaptiveTextElement->get_Text(text.GetAddressOf()));

            boolean isStrikethrough{false};
            RETURN_IF_FAILED(adaptiveTextRun->get_Strikethrough(&isStrikethrough));

            boolean isItalic{false};
            RETURN_IF_FAILED(adaptiveTextRun->get_Italic(&isItalic));

            UINT inlineLength;
            if (selectAction != nullptr)
            {
                // If there's a select action, create a hyperlink that triggers the action
                ComPtr<ABI::Windows::UI::Xaml::Documents::IHyperlink> hyperlink =
                    XamlHelpers::CreateXamlClass<ABI::Windows::UI::Xaml::Documents::IHyperlink>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Hyperlink));

                ComPtr<IAdaptiveActionInvoker> actionInvoker;
                renderContext->get_ActionInvoker(&actionInvoker);

                // Use the selectAction's title as the accessibility name for this link.
                HString actionTitle;
                RETURN_IF_FAILED(selectAction->get_Title(actionTitle.ReleaseAndGetAddressOf()));
                if (actionTitle.IsValid() && !WindowsIsStringEmpty(actionTitle.Get()))
                {
                    ComPtr<IAutomationPropertiesStatics> automationProperties;
                    RETURN_IF_FAILED(GetActivationFactory(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(), &automationProperties));
                    ComPtr<IDependencyObject> linkAsDependencyObject;
                    RETURN_IF_FAILED(hyperlink.As(&linkAsDependencyObject));
                    RETURN_IF_FAILED(automationProperties->SetName(linkAsDependencyObject.Get(), actionTitle.Get()));
                }

                EventRegistrationToken clickToken;
                RETURN_IF_FAILED(
                    hyperlink->add_Click(Callback<ABI::Windows::Foundation::ITypedEventHandler<Hyperlink*, HyperlinkClickEventArgs*>>(
                                             [selectAction, actionInvoker](IInspectable*, IHyperlinkClickEventArgs*) -> HRESULT {
                                                 return actionInvoker->SendActionEvent(selectAction.Get());
                                             })
                                             .Get(),
                                         &clickToken));

                // Add the run text to the hyperlink's inlines
                ComPtr<ABI::Windows::UI::Xaml::Documents::ISpan> hyperlinkAsSpan;
                RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsSpan));

                ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> hyperlinkInlines;
                RETURN_IF_FAILED(hyperlinkAsSpan->get_Inlines(hyperlinkInlines.GetAddressOf()));
                RETURN_IF_FAILED(AddSingleTextInline(adaptiveTextElement.Get(),
                                                     renderContext,
                                                     renderArgs,
                                                     text.Get(),
                                                     isStrikethrough,
                                                     isItalic,
                                                     true,
                                                     hyperlinkInlines.Get(),
                                                     &inlineLength));

                ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> hyperlinkAsInline;
                RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsInline));

                // Add the hyperlink to the paragraph's inlines
                RETURN_IF_FAILED(xamlInlines->Append(hyperlinkAsInline.Get()));
            }
            else
            {
                // Add the text to the paragraph's inlines
                RETURN_IF_FAILED(AddSingleTextInline(adaptiveTextElement.Get(),
                                                     renderContext,
                                                     renderArgs,
                                                     text.Get(),
                                                     isStrikethrough,
                                                     isItalic,
                                                     false,
                                                     xamlInlines.Get(),
                                                     &inlineLength));
            }

            boolean highlight;
            RETURN_IF_FAILED(adaptiveTextRun->get_Highlight(&highlight));

            if (highlight)
            {
                ComPtr<ITextHighlighter> textHighlighter;
                RETURN_IF_FAILED(GetHighlighter(adaptiveTextElement.Get(), renderContext, renderArgs, &textHighlighter));

                ComPtr<IVector<TextRange>> ranges;
                RETURN_IF_FAILED(textHighlighter->get_Ranges(&ranges));

                TextRange textRange = {(INT32)currentOffset, (INT32)inlineLength};
                RETURN_IF_FAILED(ranges->Append(textRange));

                RETURN_IF_FAILED(textHighlighters->Append(textHighlighter.Get()));
            }

            currentOffset += inlineLength;
            return S_OK;
        });

        return xamlRichTextBlock.CopyTo(textBlockControl);
    }

    HRESULT XamlBuilder::BuildTextBlock(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                        _COM_Outptr_ IUIElement** textBlockControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
        RETURN_IF_FAILED(cardElement.As(&adaptiveTextBlock));

        ComPtr<IAdaptiveTextElement> textBlockAsTextElement;
        RETURN_IF_FAILED(adaptiveTextBlock.As(&textBlockAsTextElement));
        HString text;
        RETURN_IF_FAILED(textBlockAsTextElement->get_Text(text.ReleaseAndGetAddressOf()));

        // If the text is null, return immediately without constructing a text block
        if (text.Get() == nullptr)
        {
            *textBlockControl = nullptr;
            return S_OK;
        }

        ComPtr<ITextBlock> xamlTextBlock =
            XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

        ComPtr<IAdaptiveTextElement> adaptiveTextElement;
        RETURN_IF_FAILED(adaptiveTextBlock.As(&adaptiveTextElement));

        RETURN_IF_FAILED(StyleXamlTextBlockProperties(adaptiveTextBlock.Get(), renderContext, renderArgs, xamlTextBlock.Get()));

        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
        RETURN_IF_FAILED(xamlTextBlock->get_Inlines(&inlines));

        RETURN_IF_FAILED(SetXamlInlines(adaptiveTextElement.Get(), renderContext, renderArgs, false, inlines.Get()));

        // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
        // are flush on the left edge of the card by enabling TrimSideBearings
        ComPtr<ITextBlock2> xamlTextBlock2;
        RETURN_IF_FAILED(xamlTextBlock.As(&xamlTextBlock2));
        RETURN_IF_FAILED(xamlTextBlock2->put_OpticalMarginAlignment(OpticalMarginAlignment_TrimSideBearings));

        ComPtr<IFrameworkElement> frameworkElement;
        RETURN_IF_FAILED(xamlTextBlock.As(&frameworkElement));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", frameworkElement.Get()));

        return xamlTextBlock.CopyTo(textBlockControl);
    }

    HRESULT XamlBuilder::SetAutoImageSize(_In_ IFrameworkElement* imageControl,
                                          _In_ IInspectable* parentElement,
                                          _In_ IBitmapSource* imageSource,
                                          bool setVisible)
    {
        INT32 pixelHeight;
        RETURN_IF_FAILED(imageSource->get_PixelHeight(&pixelHeight));
        INT32 pixelWidth;
        RETURN_IF_FAILED(imageSource->get_PixelWidth(&pixelWidth));
        DOUBLE maxHeight;
        DOUBLE maxWidth;
        ComPtr<IInspectable> localParentElement(parentElement);
        ComPtr<IFrameworkElement> localElement(imageControl);
        ComPtr<IColumnDefinition> parentAsColumnDefinition;

        RETURN_IF_FAILED(localElement->get_MaxHeight(&maxHeight));
        RETURN_IF_FAILED(localElement->get_MaxWidth(&maxWidth));

        if (SUCCEEDED(localParentElement.As(&parentAsColumnDefinition)))
        {
            DOUBLE parentWidth;
            RETURN_IF_FAILED(parentAsColumnDefinition->get_ActualWidth(&parentWidth));
            if (parentWidth >= pixelWidth)
            {
                // Make sure to keep the aspect ratio of the image
                maxWidth = min(maxWidth, parentWidth);
                double aspectRatio = (double)pixelHeight / pixelWidth;
                maxHeight = maxWidth * aspectRatio;
            }
        }

        // Prevent an image from being stretched out if it is smaller than the
        // space allocated for it (when in auto mode).
        RETURN_IF_FAILED(localElement->put_MaxHeight(min(maxHeight, pixelHeight)));
        RETURN_IF_FAILED(localElement->put_MaxWidth(min(maxWidth, pixelWidth)));

        if (setVisible)
        {
            ComPtr<IUIElement> frameworkElementAsUIElement;
            RETURN_IF_FAILED(localElement.As(&frameworkElementAsUIElement));
            RETURN_IF_FAILED(frameworkElementAsUIElement->put_Visibility(Visibility::Visibility_Visible));
        }

        return S_OK;
    }

    HRESULT XamlBuilder::SetMatchingHeight(_In_ IFrameworkElement* elementToChange, _In_ IFrameworkElement* elementToMatch)
    {
        DOUBLE actualHeight;
        RETURN_IF_FAILED(elementToMatch->get_ActualHeight(&actualHeight));

        ComPtr<IFrameworkElement> localElement(elementToChange);
        RETURN_IF_FAILED(localElement->put_Height(actualHeight));

        ComPtr<IUIElement> frameworkElementAsUIElement;
        RETURN_IF_FAILED(localElement.As(&frameworkElementAsUIElement));
        RETURN_IF_FAILED(frameworkElementAsUIElement->put_Visibility(Visibility::Visibility_Visible));
        return S_OK;
    }

    template<>
    void XamlBuilder::SetAutoSize<IEllipse>(IEllipse* destination, IInspectable* parentElement, IInspectable* imageContainer, bool isVisible, bool imageFiresOpenEvent)
    {
        // Check if the image source fits in the parent container, if so, set the framework element's size to match the original image.
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            ComPtr<IInspectable> ellipseShape(imageContainer);
            ComPtr<IShape> ellipseAsShape;
            THROW_IF_FAILED(ellipseShape.As(&ellipseAsShape));

            ComPtr<IBrush> ellipseBrush;
            THROW_IF_FAILED(ellipseAsShape->get_Fill(&ellipseBrush));
            ComPtr<IImageBrush> brushAsImageBrush;
            THROW_IF_FAILED(ellipseBrush.As(&brushAsImageBrush));

            ComPtr<IEllipse> ellipse(destination);

            ComPtr<IUIElement> ellipseAsUIElement;
            THROW_IF_FAILED(ellipse.As(&ellipseAsUIElement));

            ComPtr<IImageSource> imageSource;
            THROW_IF_FAILED(brushAsImageBrush->get_ImageSource(&imageSource));
            ComPtr<IBitmapSource> imageSourceAsBitmap;
            THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Ellipse while the image loads, so that resizing is not noticeable
                THROW_IF_FAILED(ellipseAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));
                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                EventRegistrationToken eventToken;
                ComPtr<IInspectable> localParentElement(parentElement);

                // Take weak references to the ellipse and parent to avoid circular references between this lambda and
                // its parents (Parent->Ellipse->ImageBrush->Lambda->(Parent and Ellipse))
                WeakRef weakParent;
                THROW_IF_FAILED(localParentElement.AsWeak(&weakParent));

                WeakRef weakEllipse;
                THROW_IF_FAILED(ellipseAsUIElement.AsWeak(&weakEllipse));
                THROW_IF_FAILED(brushAsImageBrush->add_ImageOpened(
                    Callback<IRoutedEventHandler>([weakEllipse, imageSourceAsBitmap, weakParent, isVisible](
                                                      IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                        if (isVisible)
                        {
                            ComPtr<IFrameworkElement> lambdaEllipseAsFrameworkElement;
                            RETURN_IF_FAILED(weakEllipse.As(&lambdaEllipseAsFrameworkElement));

                            ComPtr<IInspectable> lambdaParentElement;
                            RETURN_IF_FAILED(weakParent.As(&lambdaParentElement));

                            if (lambdaEllipseAsFrameworkElement && lambdaParentElement)
                            {
                                RETURN_IF_FAILED(SetAutoImageSize(lambdaEllipseAsFrameworkElement.Get(),
                                                                  lambdaParentElement.Get(),
                                                                  imageSourceAsBitmap.Get(),
                                                                  isVisible));
                            }
                        }
                        return S_OK;
                    }).Get(),
                    &eventToken));
            }
        }
    }

    template<typename T>
    void XamlBuilder::SetAutoSize(T* destination, IInspectable* parentElement, IInspectable* /* imageContainer */, bool isVisible, bool imageFiresOpenEvent)
    {
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            ComPtr<IImage> xamlImage(destination);
            ComPtr<IFrameworkElement> imageAsFrameworkElement;
            THROW_IF_FAILED(xamlImage.As(&imageAsFrameworkElement));
            ComPtr<IImageSource> imageSource;
            THROW_IF_FAILED(xamlImage->get_Source(&imageSource));
            ComPtr<IBitmapSource> imageSourceAsBitmap;
            THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));

            ComPtr<IUIElement> imageAsUIElement;
            THROW_IF_FAILED(xamlImage.As(&imageAsUIElement));

            // If the image hasn't loaded yet
            if (imageFiresOpenEvent)
            {
                // Collapse the Image control while the image loads, so that resizing is not noticeable
                THROW_IF_FAILED(imageAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                ComPtr<IInspectable> localParentElement(parentElement);

                // Take weak references to the image and parent to avoid circular references between this lambda and
                // its parents (Parent->Image->Lambda->(Parent and Image))
                WeakRef weakParent;
                THROW_IF_FAILED(localParentElement.AsWeak(&weakParent));

                WeakRef weakImage;
                THROW_IF_FAILED(imageAsFrameworkElement.AsWeak(&weakImage));
                EventRegistrationToken eventToken;
                THROW_IF_FAILED(xamlImage->add_ImageOpened(
                    Callback<IRoutedEventHandler>([weakImage, weakParent, imageSourceAsBitmap, isVisible](IInspectable* /*sender*/, IRoutedEventArgs *
                                                                                                          /*args*/) -> HRESULT {
                        ComPtr<IFrameworkElement> lambdaImageAsFrameworkElement;
                        RETURN_IF_FAILED(weakImage.As(&lambdaImageAsFrameworkElement));

                        ComPtr<IInspectable> lambdaParentElement;
                        RETURN_IF_FAILED(weakParent.As(&lambdaParentElement));

                        if (lambdaImageAsFrameworkElement && lambdaParentElement)
                        {
                            RETURN_IF_FAILED(SetAutoImageSize(lambdaImageAsFrameworkElement.Get(),
                                                              lambdaParentElement.Get(),
                                                              imageSourceAsBitmap.Get(),
                                                              isVisible));
                        }
                        return S_OK;
                    }).Get(),
                    &eventToken));
            }
            else
            {
                SetAutoImageSize(imageAsFrameworkElement.Get(), parentElement, imageSourceAsBitmap.Get(), isVisible);
            }
        }
    }

    HRESULT XamlBuilder::BuildImage(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    _In_ IAdaptiveRenderArgs* renderArgs,
                                    _COM_Outptr_ IUIElement** imageControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        RETURN_IF_FAILED(cardElement.As(&adaptiveImage));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        HSTRING url;
        RETURN_IF_FAILED(adaptiveImage->get_Url(&url));

        ComPtr<IUriRuntimeClass> imageUrl;
        GetUrlFromString(hostConfig.Get(), url, imageUrl.GetAddressOf());

        if (imageUrl == nullptr)
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::AssetLoadFailed,
                                      HStringReference(L"Image not found").Get());
            *imageControl = nullptr;
            return S_OK;
        }

        UINT32 pixelWidth = 0, pixelHeight = 0;
        RETURN_IF_FAILED(adaptiveImage->get_PixelWidth(&pixelWidth));
        RETURN_IF_FAILED(adaptiveImage->get_PixelHeight(&pixelHeight));
        bool hasExplicitMeasurements = (pixelWidth || pixelHeight);
        bool isAspectRatioNeeded = (pixelWidth && pixelHeight);

        // Get the image's size and style
        ABI::AdaptiveNamespace::ImageSize size = ABI::AdaptiveNamespace::ImageSize::None;
        if (!hasExplicitMeasurements)
        {
            RETURN_IF_FAILED(adaptiveImage->get_Size(&size));
        }

        if (size == ABI::AdaptiveNamespace::ImageSize::None && !hasExplicitMeasurements)
        {
            ComPtr<IAdaptiveImageConfig> imageConfig;
            RETURN_IF_FAILED(hostConfig->get_Image(&imageConfig));
            RETURN_IF_FAILED(imageConfig->get_ImageSize(&size));
        }

        ABI::AdaptiveNamespace::ImageStyle imageStyle;
        RETURN_IF_FAILED(adaptiveImage->get_Style(&imageStyle));
        ComPtr<IAdaptiveCardResourceResolvers> resourceResolvers;
        RETURN_IF_FAILED(renderContext->get_ResourceResolvers(&resourceResolvers));

        HSTRING backgroundColor;
        RETURN_IF_FAILED(adaptiveImage->get_BackgroundColor(&backgroundColor));

        boolean isVisible;
        RETURN_IF_FAILED(adaptiveCardElement->get_IsVisible(&isVisible));

        ComPtr<IFrameworkElement> frameworkElement;
        if (imageStyle == ImageStyle_Person)
        {
            ComPtr<IEllipse> ellipse =
                XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));
            ComPtr<IEllipse> backgroundEllipse =
                XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));

            Stretch imageStretch = (isAspectRatioNeeded) ? Stretch::Stretch_Fill : Stretch::Stretch_UniformToFill;
            bool mustHideElement{true};

            ComPtr<IInspectable> parentElement;
            RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));

            ComPtr<IShape> ellipseAsShape;
            RETURN_IF_FAILED(ellipse.As(&ellipseAsShape));

            SetImageOnUIElement(imageUrl.Get(),
                                ellipse.Get(),
                                resourceResolvers.Get(),
                                (size == ABI::AdaptiveNamespace::ImageSize_Auto),
                                parentElement.Get(),
                                ellipseAsShape.Get(),
                                isVisible,
                                &mustHideElement,
                                imageStretch);

            ComPtr<IShape> backgroundEllipseAsShape;
            RETURN_IF_FAILED(backgroundEllipse.As(&backgroundEllipseAsShape));

            if (size == ABI::AdaptiveNamespace::ImageSize::None || size == ABI::AdaptiveNamespace::ImageSize::Stretch ||
                size == ABI::AdaptiveNamespace::ImageSize::Auto || hasExplicitMeasurements)
            {
                RETURN_IF_FAILED(ellipseAsShape->put_Stretch(imageStretch));
                RETURN_IF_FAILED(backgroundEllipseAsShape->put_Stretch(imageStretch));
            }
            else
            {
                // Set the stretch for the ellipse - this is different to the stretch used for the image brush
                // above. This will force the ellipse to conform to fit within the confines of its parent.
                Stretch ellipseStretch = Stretch::Stretch_UniformToFill;
                RETURN_IF_FAILED(ellipseAsShape->put_Stretch(ellipseStretch));
                RETURN_IF_FAILED(backgroundEllipseAsShape->put_Stretch(ellipseStretch));
            }

            if (backgroundColor != nullptr)
            {
                // Fill the background ellipse with solid color brush
                ABI::Windows::UI::Color color;
                RETURN_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor), &color));
                ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                RETURN_IF_FAILED(backgroundEllipseAsShape->put_Fill(backgroundColorBrush.Get()));

                // Create a grid to contain the background color ellipse and the image ellipse
                ComPtr<IGrid> imageGrid =
                    XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));

                ComPtr<IPanel> panel;
                RETURN_IF_FAILED(imageGrid.As(&panel));

                XamlHelpers::AppendXamlElementToPanel(backgroundEllipse.Get(), panel.Get());
                XamlHelpers::AppendXamlElementToPanel(ellipse.Get(), panel.Get());

                RETURN_IF_FAILED(imageGrid.As(&frameworkElement));
            }
            else
            {
                RETURN_IF_FAILED(ellipse.As(&frameworkElement));
            }
        }
        else
        {
            ComPtr<IImage> xamlImage =
                XamlHelpers::CreateXamlClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));

            if (backgroundColor != nullptr)
            {
                // Create a surrounding border with solid color background to contain the image
                ComPtr<IBorder> border =
                    XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

                ABI::Windows::UI::Color color;
                RETURN_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor), &color));
                ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(color);
                RETURN_IF_FAILED(border->put_Background(backgroundColorBrush.Get()));

                ComPtr<IUIElement> imageAsUiElement;
                RETURN_IF_FAILED(xamlImage.CopyTo(imageAsUiElement.GetAddressOf()));
                RETURN_IF_FAILED(border->put_Child(imageAsUiElement.Get()));

                RETURN_IF_FAILED(border.As(&frameworkElement));
            }
            else
            {
                RETURN_IF_FAILED(xamlImage.As(&frameworkElement));
            }

            if (isAspectRatioNeeded)
            {
                xamlImage->put_Stretch(Stretch::Stretch_Fill);
            }

            ComPtr<IInspectable> parentElement;
            RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));

            bool mustHideElement{true};
            SetImageOnUIElement(imageUrl.Get(),
                                xamlImage.Get(),
                                resourceResolvers.Get(),
                                (size == ABI::AdaptiveNamespace::ImageSize_Auto),
                                parentElement.Get(),
                                frameworkElement.Get(),
                                isVisible,
                                &mustHideElement);
        }

        ComPtr<IAdaptiveImageSizesConfig> sizeOptions;
        RETURN_IF_FAILED(hostConfig->get_ImageSizes(sizeOptions.GetAddressOf()));

        if (hasExplicitMeasurements)
        {
            if (pixelWidth)
            {
                if (imageStyle == ImageStyle_Person)
                {
                    RETURN_IF_FAILED(frameworkElement->put_Width(pixelWidth));
                }
                else
                {
                    RETURN_IF_FAILED(frameworkElement->put_MaxWidth(pixelWidth));
                }
            }

            if (pixelHeight)
            {
                if (imageStyle == ImageStyle_Person)
                {
                    RETURN_IF_FAILED(frameworkElement->put_Height(pixelHeight));
                }
                else
                {
                    RETURN_IF_FAILED(frameworkElement->put_MaxHeight(pixelHeight));
                }
            }
        }
        else
        {
            if (size == ABI::AdaptiveNamespace::ImageSize::Small || size == ABI::AdaptiveNamespace::ImageSize::Medium ||
                size == ABI::AdaptiveNamespace::ImageSize::Large)
            {
                UINT32 imageSize;
                switch (size)
                {
                case ABI::AdaptiveNamespace::ImageSize::Small:
                {
                    RETURN_IF_FAILED(sizeOptions->get_Small(&imageSize));
                    break;
                }

                case ABI::AdaptiveNamespace::ImageSize::Medium:
                {
                    RETURN_IF_FAILED(sizeOptions->get_Medium(&imageSize));
                    break;
                }

                case ABI::AdaptiveNamespace::ImageSize::Large:
                {
                    RETURN_IF_FAILED(sizeOptions->get_Large(&imageSize));

                    break;
                }
                default:
                {
                    return E_UNEXPECTED;
                }
                }

                RETURN_IF_FAILED(frameworkElement->put_MaxWidth(imageSize));

                // We don't want to set a max height on the person ellipse as ellipses do not understand preserving
                // aspect ratio when constrained on both axes.
                if (imageStyle != ImageStyle_Person)
                {
                    RETURN_IF_FAILED(frameworkElement->put_MaxHeight(imageSize));
                }
            }
        }

        ABI::AdaptiveNamespace::HAlignment adaptiveHorizontalAlignment;
        RETURN_IF_FAILED(adaptiveImage->get_HorizontalAlignment(&adaptiveHorizontalAlignment));

        switch (adaptiveHorizontalAlignment)
        {
        case ABI::AdaptiveNamespace::HAlignment::Left:
            RETURN_IF_FAILED(frameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Left));
            break;
        case ABI::AdaptiveNamespace::HAlignment::Right:
            RETURN_IF_FAILED(frameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Right));
            break;
        case ABI::AdaptiveNamespace::HAlignment::Center:
            RETURN_IF_FAILED(frameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Center));
            break;
        }

        RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Image", frameworkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(adaptiveImage->get_SelectAction(&selectAction));

        ComPtr<IUIElement> imageAsUIElement;
        RETURN_IF_FAILED(frameworkElement.As(&imageAsUIElement));

        HString altText;
        RETURN_IF_FAILED(adaptiveImage->get_AltText(altText.GetAddressOf()));

        ComPtr<IDependencyObject> imageAsDependencyObject;
        RETURN_IF_FAILED(imageAsUIElement.As(&imageAsDependencyObject));

        ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
        RETURN_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationPropertiesStatics));

        RETURN_IF_FAILED(automationPropertiesStatics->SetName(imageAsDependencyObject.Get(), altText.Get()));

        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           imageAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           true,
                           imageControl);

        return S_OK;
    }

    HRESULT HandleStylingAndPadding(_In_ IAdaptiveContainerBase* adaptiveContainer,
                                    _In_ IBorder* containerBorder,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    _In_ IAdaptiveRenderArgs* renderArgs,
                                    _Out_ ABI::AdaptiveNamespace::ContainerStyle* containerStyle)
    {
        ABI::AdaptiveNamespace::ContainerStyle localContainerStyle;
        RETURN_IF_FAILED(adaptiveContainer->get_Style(&localContainerStyle));

        ABI::AdaptiveNamespace::ContainerStyle parentContainerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&parentContainerStyle));

        bool hasExplicitContainerStyle{true};
        if (localContainerStyle == ABI::AdaptiveNamespace::ContainerStyle::None)
        {
            hasExplicitContainerStyle = false;
            localContainerStyle = parentContainerStyle;
        }

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        RETURN_IF_FAILED(spacingConfig->get_Padding(&padding));
        DOUBLE paddingAsDouble = static_cast<DOUBLE>(padding);

        // If container style was explicitly assigned, apply background color and padding
        if (hasExplicitContainerStyle)
        {
            ABI::Windows::UI::Color backgroundColor;
            RETURN_IF_FAILED(GetBackgroundColorFromStyle(localContainerStyle, hostConfig.Get(), &backgroundColor));
            ComPtr<IBrush> backgroundColorBrush = XamlHelpers::GetSolidColorBrush(backgroundColor);
            RETURN_IF_FAILED(containerBorder->put_Background(backgroundColorBrush.Get()));

            // If the container style doesn't match its parent apply padding.
            if (localContainerStyle != parentContainerStyle)
            {
                Thickness paddingThickness = {paddingAsDouble, paddingAsDouble, paddingAsDouble, paddingAsDouble};
                RETURN_IF_FAILED(containerBorder->put_Padding(paddingThickness));
            }
        }

        // Find out which direction(s) we bleed in, and apply a negative margin to cause the
        // container to bleed
        ABI::AdaptiveNamespace::BleedDirection bleedDirection;
        RETURN_IF_FAILED(adaptiveContainer->get_BleedDirection(&bleedDirection));

        Thickness marginThickness = {0};
        if (bleedDirection != ABI::AdaptiveNamespace::BleedDirection::None)
        {
            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Left) != ABI::AdaptiveNamespace::BleedDirection::None)
            {
                marginThickness.Left = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Right) != ABI::AdaptiveNamespace::BleedDirection::None)
            {
                marginThickness.Right = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Up) != ABI::AdaptiveNamespace::BleedDirection::None)
            {
                marginThickness.Top = -paddingAsDouble;
            }

            if ((bleedDirection & ABI::AdaptiveNamespace::BleedDirection::Down) != ABI::AdaptiveNamespace::BleedDirection::None)
            {
                marginThickness.Bottom = -paddingAsDouble;
            }

            ComPtr<IBorder> localContainerBorder(containerBorder);
            ComPtr<IFrameworkElement> containerBorderAsFrameworkElement;
            RETURN_IF_FAILED(localContainerBorder.As(&containerBorderAsFrameworkElement));
            RETURN_IF_FAILED(containerBorderAsFrameworkElement->put_Margin(marginThickness));
        }

        *containerStyle = localContainerStyle;

        return S_OK;
    }

    HRESULT XamlBuilder::BuildContainer(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                        _COM_Outptr_ IUIElement** containerControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveContainer> adaptiveContainer;
        RETURN_IF_FAILED(cardElement.As(&adaptiveContainer));

        ComPtr<WholeItemsPanel> containerPanel;
        RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&containerPanel));

        ComPtr<IFrameworkElement> containerPanelAsFrameWorkElement;
        RETURN_IF_FAILED(containerPanel.As(&containerPanelAsFrameWorkElement));

        // Assign vertical alignment to the top so that on fixed height cards, the content
        // still renders at the top even if the content is shorter than the full card
        ABI::AdaptiveNamespace::HeightType containerHeightType{};
        RETURN_IF_FAILED(cardElement->get_Height(&containerHeightType));
        if (containerHeightType == ABI::AdaptiveNamespace::HeightType::Auto)
        {
            RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
        }

        ComPtr<IAdaptiveContainerBase> containerAsContainerBase;
        RETURN_IF_FAILED(adaptiveContainer.As(&containerAsContainerBase));

        UINT32 containerMinHeight{};
        RETURN_IF_FAILED(containerAsContainerBase->get_MinHeight(&containerMinHeight));
        if (containerMinHeight > 0)
        {
            RETURN_IF_FAILED(containerPanelAsFrameWorkElement->put_MinHeight(containerMinHeight));
        }

        ComPtr<IBorder> containerBorder =
            XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        RETURN_IF_FAILED(
            HandleStylingAndPadding(containerAsContainerBase.Get(), containerBorder.Get(), renderContext, renderArgs, &containerStyle));

        ComPtr<IFrameworkElement> parentElement;
        RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
        ComPtr<IAdaptiveRenderArgs> newRenderArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&newRenderArgs, containerStyle, parentElement.Get(), renderArgs));

        ComPtr<IPanel> containerPanelAsPanel;
        RETURN_IF_FAILED(containerPanel.As(&containerPanelAsPanel));
        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        RETURN_IF_FAILED(adaptiveContainer->get_Items(&childItems));
        RETURN_IF_FAILED(
            BuildPanelChildren(childItems.Get(), containerPanelAsPanel.Get(), renderContext, newRenderArgs.Get(), [](IUIElement*) {}));

        ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment;
        RETURN_IF_FAILED(adaptiveContainer->get_VerticalContentAlignment(&verticalContentAlignment));

        XamlBuilder::SetVerticalContentAlignmentToChildren(containerPanel.Get(), verticalContentAlignment);

        // Check if backgroundImage defined
        ComPtr<IAdaptiveBackgroundImage> backgroundImage;
        BOOL backgroundImageIsValid;
        RETURN_IF_FAILED(adaptiveContainer->get_BackgroundImage(&backgroundImage));
        RETURN_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));
        if (backgroundImageIsValid)
        {
            ComPtr<IGrid> rootElement =
                XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            ComPtr<IPanel> rootAsPanel;
            RETURN_IF_FAILED(rootElement.As(&rootAsPanel));

            ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, newRenderArgs.Get());

            // Add rootElement to containerBorder
            ComPtr<IUIElement> rootAsUIElement;
            RETURN_IF_FAILED(rootElement.As(&rootAsUIElement));
            RETURN_IF_FAILED(containerBorder->put_Child(rootAsUIElement.Get()));

            // Add containerPanel to rootElement
            ComPtr<IFrameworkElement> containerPanelAsFElement;
            RETURN_IF_FAILED(containerPanel.As(&containerPanelAsFElement));
            XamlHelpers::AppendXamlElementToPanel(containerPanelAsFElement.Get(), rootAsPanel.Get(), containerHeightType);
        }
        else
        {
            // instead, directly add containerPanel to containerBorder
            ComPtr<IUIElement> containerPanelAsUIElement;
            RETURN_IF_FAILED(containerPanel.As(&containerPanelAsUIElement));
            RETURN_IF_FAILED(containerBorder->put_Child(containerPanelAsUIElement.Get()));
        }

        RETURN_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Container", containerPanelAsFrameWorkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(containerAsContainerBase->get_SelectAction(&selectAction));

        ComPtr<IUIElement> containerBorderAsUIElement;
        RETURN_IF_FAILED(containerBorder.As(&containerBorderAsUIElement));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           containerBorderAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           true,
                           containerControl);
        return S_OK;
    }

    HRESULT XamlBuilder::BuildColumn(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _COM_Outptr_ IUIElement** ColumnControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumn> adaptiveColumn;
        RETURN_IF_FAILED(cardElement.As(&adaptiveColumn));

        ComPtr<IBorder> columnBorder =
            XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        ComPtr<WholeItemsPanel> columnPanel;
        RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&columnPanel));

        ComPtr<IUIElement> columnPanelAsUIElement;
        RETURN_IF_FAILED(columnPanel.As(&columnPanelAsUIElement));

        RETURN_IF_FAILED(columnBorder->put_Child(columnPanelAsUIElement.Get()));

        ComPtr<IAdaptiveContainerBase> columnAsContainerBase;
        RETURN_IF_FAILED(adaptiveColumn.As(&columnAsContainerBase));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        RETURN_IF_FAILED(HandleStylingAndPadding(columnAsContainerBase.Get(), columnBorder.Get(), renderContext, renderArgs, &containerStyle));

        ComPtr<IFrameworkElement> parentElement;
        RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
        ComPtr<IAdaptiveRenderArgs> newRenderArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&newRenderArgs, containerStyle, parentElement.Get(), renderArgs));

        ComPtr<IPanel> columnAsPanel;
        THROW_IF_FAILED(columnPanel.As(&columnAsPanel));

        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        RETURN_IF_FAILED(adaptiveColumn->get_Items(&childItems));
        RETURN_IF_FAILED(
            BuildPanelChildren(childItems.Get(), columnAsPanel.Get(), renderContext, newRenderArgs.Get(), [](IUIElement*) {}));

        ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment;
        RETURN_IF_FAILED(adaptiveColumn->get_VerticalContentAlignment(&verticalContentAlignment));

        XamlBuilder::SetVerticalContentAlignmentToChildren(columnPanel.Get(), verticalContentAlignment);

        // Assign vertical alignment to the top so that on fixed height cards, the content
        // still renders at the top even if the content is shorter than the full card
        ComPtr<IFrameworkElement> columnPanelAsFrameworkElement;
        RETURN_IF_FAILED(columnPanel.As(&columnPanelAsFrameworkElement));
        RETURN_IF_FAILED(columnPanelAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));

        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Column", columnPanelAsFrameworkElement.Get()));

        UINT32 columnMinHeight{};
        RETURN_IF_FAILED(columnAsContainerBase->get_MinHeight(&columnMinHeight));
        if (columnMinHeight > 0)
        {
            RETURN_IF_FAILED(columnPanelAsFrameworkElement->put_MinHeight(columnMinHeight));
        }

        ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(columnAsContainerBase->get_SelectAction(&selectAction));

        // Define columnAsUIElement based on the existence of a backgroundImage
        ComPtr<IUIElement> columnAsUIElement;
        ComPtr<IAdaptiveBackgroundImage> backgroundImage;
        BOOL backgroundImageIsValid;
        RETURN_IF_FAILED(adaptiveColumn->get_BackgroundImage(&backgroundImage));
        RETURN_IF_FAILED(IsBackgroundImageValid(backgroundImage.Get(), &backgroundImageIsValid));
        if (backgroundImageIsValid)
        {
            ComPtr<IGrid> rootElement =
                XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            ComPtr<IPanel> rootAsPanel;
            RETURN_IF_FAILED(rootElement.As(&rootAsPanel));

            ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage.Get(), renderContext, newRenderArgs.Get());

            // get HeightType for column
            ABI::AdaptiveNamespace::HeightType columnHeightType{};
            RETURN_IF_FAILED(cardElement->get_Height(&columnHeightType));

            // Add columnBorder to rootElement
            ComPtr<IFrameworkElement> columnBorderAsFElement;
            RETURN_IF_FAILED(columnBorder.As(&columnBorderAsFElement));
            XamlHelpers::AppendXamlElementToPanel(columnBorderAsFElement.Get(), rootAsPanel.Get(), columnHeightType);

            RETURN_IF_FAILED(rootElement.As(&columnAsUIElement));
        }
        else
        {
            RETURN_IF_FAILED(columnBorder.As(&columnAsUIElement));
        }

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           columnAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           false,
                           ColumnControl);
        return S_OK;
    }

    HRESULT XamlBuilder::BuildColumnSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                        _COM_Outptr_ IUIElement** columnSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumnSet> adaptiveColumnSet;
        RETURN_IF_FAILED(cardElement.As(&adaptiveColumnSet));

        ComPtr<IBorder> columnSetBorder =
            XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

        ComPtr<WholeItemsPanel> gridContainer;
        RETURN_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&gridContainer));

        ComPtr<IUIElement> gridContainerAsUIElement;
        RETURN_IF_FAILED(gridContainer.As(&gridContainerAsUIElement));

        RETURN_IF_FAILED(columnSetBorder->put_Child(gridContainerAsUIElement.Get()));

        ComPtr<IAdaptiveContainerBase> columnSetAsContainerBase;
        RETURN_IF_FAILED(adaptiveColumnSet.As(&columnSetAsContainerBase));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        RETURN_IF_FAILED(
            HandleStylingAndPadding(columnSetAsContainerBase.Get(), columnSetBorder.Get(), renderContext, renderArgs, &containerStyle));

        ComPtr<IFrameworkElement> parentElement;
        RETURN_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
        ComPtr<IAdaptiveRenderArgs> newRenderArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&newRenderArgs, containerStyle, parentElement.Get(), renderArgs));

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IVector<AdaptiveColumn*>> columns;
        RETURN_IF_FAILED(adaptiveColumnSet->get_Columns(&columns));
        int currentColumn{};
        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        ComPtr<IAdaptiveElementRenderer> columnRenderer;
        RETURN_IF_FAILED(elementRenderers->Get(HStringReference(L"Column").Get(), &columnRenderer));

        if (columnRenderer == nullptr)
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                                      HStringReference(L"No renderer found for type: Column").Get());
            *columnSetControl = nullptr;
            return S_OK;
        }

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        boolean ancestorHasFallback;
        RETURN_IF_FAILED(renderArgs->get_AncestorHasFallback(&ancestorHasFallback));

        ComPtr<IPanel> gridAsPanel;
        RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));

        HRESULT hrColumns = XamlHelpers::IterateOverVectorWithFailure<AdaptiveColumn, IAdaptiveColumn>(columns.Get(), ancestorHasFallback, [&](IAdaptiveColumn* column) {
            ComPtr<IAdaptiveCardElement> columnAsCardElement;
            ComPtr<IAdaptiveColumn> localColumn(column);
            RETURN_IF_FAILED(localColumn.As(&columnAsCardElement));

            ComPtr<IAdaptiveColumn> testColumn;
            columnAsCardElement.As(&testColumn);

            ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
            RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));

            ABI::AdaptiveNamespace::FallbackType fallbackType;
            RETURN_IF_FAILED(columnAsCardElement->get_FallbackType(&fallbackType));

            // Build the Column
            RETURN_IF_FAILED(newRenderArgs->put_AncestorHasFallback(
                ancestorHasFallback || fallbackType != ABI::AdaptiveNamespace::FallbackType::None));

            ComPtr<IUIElement> xamlColumn;
            HRESULT hr = columnRenderer->Render(columnAsCardElement.Get(), renderContext, newRenderArgs.Get(), &xamlColumn);
            if (hr == E_PERFORM_FALLBACK)
            {
                RETURN_IF_FAILED(RenderFallback(columnAsCardElement.Get(), renderContext, newRenderArgs.Get(), &xamlColumn));
            }

            RETURN_IF_FAILED(newRenderArgs->put_AncestorHasFallback(ancestorHasFallback));

            // Check the column for nullptr as it may have been dropped due to fallback
            if (xamlColumn != nullptr)
            {
                // If not the first column
                ComPtr<IUIElement> separator;
                if (currentColumn > 0)
                {
                    // Add Separator to the columnSet
                    bool needsSeparator;
                    UINT spacing;
                    UINT separatorThickness;
                    ABI::Windows::UI::Color separatorColor;
                    GetSeparationConfigForElement(
                        columnAsCardElement.Get(), hostConfig.Get(), &spacing, &separatorThickness, &separatorColor, &needsSeparator);

                    if (needsSeparator)
                    {
                        // Create a new ColumnDefinition for the separator
                        ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                        RETURN_IF_FAILED(separatorColumnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Auto}));
                        RETURN_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

                        separator = CreateSeparator(renderContext, spacing, separatorThickness, separatorColor, false);
                        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
                        RETURN_IF_FAILED(separator.As(&separatorAsFrameworkElement));
                        gridStatics->SetColumn(separatorAsFrameworkElement.Get(), currentColumn++);
                        XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());
                    }
                }

                // Determine if the column is auto, stretch, or percentage width, and set the column width appropriately
                ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));

                boolean isVisible;
                RETURN_IF_FAILED(columnAsCardElement->get_IsVisible(&isVisible));

                RETURN_IF_FAILED(HandleColumnWidth(column, isVisible, columnDefinition.Get()));

                RETURN_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

                // Mark the column container with the current column
                ComPtr<IFrameworkElement> columnAsFrameworkElement;
                RETURN_IF_FAILED(xamlColumn.As(&columnAsFrameworkElement));
                gridStatics->SetColumn(columnAsFrameworkElement.Get(), currentColumn++);

                // Finally add the column container to the grid
                RETURN_IF_FAILED(AddRenderedControl(xamlColumn.Get(),
                                                    columnAsCardElement.Get(),
                                                    gridAsPanel.Get(),
                                                    separator.Get(),
                                                    columnDefinition.Get(),
                                                    [](IUIElement*) {}));
            }
            return S_OK;
        });
        RETURN_IF_FAILED(hrColumns);

        RETURN_IF_FAILED(SetSeparatorVisibility(gridAsPanel.Get()));

        ComPtr<IFrameworkElement> columnSetAsFrameworkElement;
        RETURN_IF_FAILED(xamlGrid.As(&columnSetAsFrameworkElement));
        RETURN_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.ColumnSet", columnSetAsFrameworkElement.Get()));
        RETURN_IF_FAILED(columnSetAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));

        ComPtr<IAdaptiveActionElement> selectAction;
        RETURN_IF_FAILED(columnSetAsContainerBase->get_SelectAction(&selectAction));

        ComPtr<IPanel> gridContainerAsPanel;
        RETURN_IF_FAILED(gridContainer.As(&gridContainerAsPanel));

        ComPtr<IFrameworkElement> gridContainerAsFrameworkElement;
        RETURN_IF_FAILED(gridContainer.As(&gridContainerAsFrameworkElement));

        ComPtr<IUIElement> gridAsUIElement;
        RETURN_IF_FAILED(xamlGrid.As(&gridAsUIElement));

        ComPtr<IAdaptiveCardElement> columnSetAsCardElement;
        RETURN_IF_FAILED(adaptiveColumnSet.As(&columnSetAsCardElement));

        ABI::AdaptiveNamespace::HeightType columnSetHeightType;
        RETURN_IF_FAILED(columnSetAsCardElement->get_Height(&columnSetHeightType));

        ComPtr<IAdaptiveContainerBase> columnAsContainerBase;
        RETURN_IF_FAILED(adaptiveColumnSet.As(&columnAsContainerBase));

        UINT32 columnSetMinHeight{};
        RETURN_IF_FAILED(columnAsContainerBase->get_MinHeight(&columnSetMinHeight));
        if (columnSetMinHeight > 0)
        {
            RETURN_IF_FAILED(gridContainerAsFrameworkElement->put_MinHeight(columnSetMinHeight));
        }

        XamlHelpers::AppendXamlElementToPanel(xamlGrid.Get(), gridContainerAsPanel.Get(), columnSetHeightType);

        ComPtr<IUIElement> columnSetBorderAsUIElement;
        RETURN_IF_FAILED(columnSetBorder.As(&columnSetBorderAsUIElement));

        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           columnSetBorderAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           true,
                           columnSetControl);
        return S_OK;
    }

    HRESULT XamlBuilder::BuildFactSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                      _In_ IAdaptiveRenderContext* renderContext,
                                      _In_ IAdaptiveRenderArgs* renderArgs,
                                      _COM_Outptr_ IUIElement** factSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveFactSet> adaptiveFactSet;

        RETURN_IF_FAILED(cardElement.As(&adaptiveFactSet));

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IColumnDefinition> titleColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        ComPtr<IColumnDefinition> valueColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        GridLength factSetGridTitleLength = {0, GridUnitType::GridUnitType_Auto};
        GridLength factSetGridValueLength = {1, GridUnitType::GridUnitType_Star};

        RETURN_IF_FAILED(titleColumn->put_Width(factSetGridTitleLength));
        RETURN_IF_FAILED(valueColumn->put_Width(factSetGridValueLength));
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
        RETURN_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
        RETURN_IF_FAILED(columnDefinitions->Append(titleColumn.Get()));
        RETURN_IF_FAILED(columnDefinitions->Append(valueColumn.Get()));

        GridLength factSetGridHeight = {0, GridUnitType::GridUnitType_Auto};
        ABI::AdaptiveNamespace::HeightType heightType;
        RETURN_IF_FAILED(cardElement->get_Height(&heightType));
        if (heightType == ABI::AdaptiveNamespace::HeightType::Stretch)
        {
            factSetGridHeight = {1, GridUnitType::GridUnitType_Star};
        }

        ComPtr<IVector<AdaptiveFact*>> facts;
        RETURN_IF_FAILED(adaptiveFactSet->get_Facts(&facts));
        int currentFact = 0;
        XamlHelpers::IterateOverVector<AdaptiveFact, IAdaptiveFact>(
            facts.Get(), [xamlGrid, gridStatics, factSetGridHeight, &currentFact, renderContext, renderArgs](IAdaptiveFact* fact) {
                ComPtr<IRowDefinition> factRow = XamlHelpers::CreateXamlClass<IRowDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
                RETURN_IF_FAILED(factRow->put_Height(factSetGridHeight));

                ComPtr<IVector<RowDefinition*>> rowDefinitions;
                RETURN_IF_FAILED(xamlGrid->get_RowDefinitions(&rowDefinitions));
                RETURN_IF_FAILED(rowDefinitions->Append(factRow.Get()));

                ComPtr<IAdaptiveFact> localFact(fact);
                ComPtr<IAdaptiveHostConfig> hostConfig;
                RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
                ComPtr<IAdaptiveFactSetConfig> factSetConfig;
                RETURN_IF_FAILED(hostConfig->get_FactSet(&factSetConfig));

                // Get Language
                HString language;
                RETURN_IF_FAILED(localFact->get_Language(language.GetAddressOf()));

                // Create the title xaml textblock and style it from Host options
                ComPtr<IAdaptiveTextConfig> titleTextConfig;
                RETURN_IF_FAILED(factSetConfig->get_Title(&titleTextConfig));

                ComPtr<ITextBlock> titleTextBlock =
                    XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

                HString factTitle;
                RETURN_IF_FAILED(localFact->get_Title(factTitle.GetAddressOf()));

                RETURN_IF_FAILED(SetXamlInlinesWithTextConfig(
                    renderContext, renderArgs, titleTextConfig.Get(), language.Get(), factTitle.Get(), titleTextBlock.Get()));

                // Create the value xaml textblock and style it from Host options
                ComPtr<IAdaptiveTextConfig> valueTextConfig;
                RETURN_IF_FAILED(factSetConfig->get_Value(&valueTextConfig));

                ComPtr<ITextBlock> valueTextBlock =
                    XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

                HString factValue;
                RETURN_IF_FAILED(localFact->get_Value(factValue.GetAddressOf()));

                RETURN_IF_FAILED(SetXamlInlinesWithTextConfig(
                    renderContext, renderArgs, valueTextConfig.Get(), language.Get(), factValue.Get(), valueTextBlock.Get()));

                // Mark the column container with the current column
                ComPtr<IFrameworkElement> titleTextBlockAsFrameWorkElement;
                RETURN_IF_FAILED(titleTextBlock.As(&titleTextBlockAsFrameWorkElement));
                ComPtr<IFrameworkElement> valueTextBlockAsFrameWorkElement;
                RETURN_IF_FAILED(valueTextBlock.As(&valueTextBlockAsFrameWorkElement));

                UINT32 spacing;
                RETURN_IF_FAILED(factSetConfig->get_Spacing(&spacing));
                // Add spacing from hostconfig to right margin of title.
                titleTextBlockAsFrameWorkElement->put_Margin({0, 0, (double)spacing, 0});

                RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext,
                                                                L"Adaptive.Fact.Title",
                                                                titleTextBlockAsFrameWorkElement.Get()));
                RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext,
                                                                L"Adaptive.Fact.Value",
                                                                valueTextBlockAsFrameWorkElement.Get()));

                RETURN_IF_FAILED(gridStatics->SetColumn(titleTextBlockAsFrameWorkElement.Get(), 0));
                RETURN_IF_FAILED(gridStatics->SetRow(titleTextBlockAsFrameWorkElement.Get(), currentFact));

                RETURN_IF_FAILED(gridStatics->SetColumn(valueTextBlockAsFrameWorkElement.Get(), 1));
                RETURN_IF_FAILED(gridStatics->SetRow(valueTextBlockAsFrameWorkElement.Get(), currentFact));

                // Finally add the column container to the grid, and increment the column count
                ComPtr<IPanel> gridAsPanel;
                RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));
                ComPtr<IUIElement> titleUIElement;
                RETURN_IF_FAILED(titleTextBlockAsFrameWorkElement.As(&titleUIElement));
                ComPtr<IUIElement> valueUIElement;
                RETURN_IF_FAILED(valueTextBlockAsFrameWorkElement.As(&valueUIElement));

                XamlHelpers::AppendXamlElementToPanel(titleUIElement.Get(), gridAsPanel.Get());
                XamlHelpers::AppendXamlElementToPanel(valueUIElement.Get(), gridAsPanel.Get());
                ++currentFact;
                return S_OK;
            });

        ComPtr<IFrameworkElement> factSetAsFrameworkElement;
        RETURN_IF_FAILED(xamlGrid.As(&factSetAsFrameworkElement));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.FactSet", factSetAsFrameworkElement.Get()));

        return xamlGrid.CopyTo(factSetControl);
    }

    HRESULT XamlBuilder::BuildImageSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                       _In_ IAdaptiveRenderContext* renderContext,
                                       _In_ IAdaptiveRenderArgs* renderArgs,
                                       _COM_Outptr_ IUIElement** imageSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImageSet> adaptiveImageSet;
        RETURN_IF_FAILED(cardElement.As(&adaptiveImageSet));

        ComPtr<IVariableSizedWrapGrid> xamlGrid = XamlHelpers::CreateXamlClass<IVariableSizedWrapGrid>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_VariableSizedWrapGrid));

        RETURN_IF_FAILED(xamlGrid->put_Orientation(Orientation_Horizontal));

        ComPtr<IVector<ABI::AdaptiveNamespace::AdaptiveImage*>> images;
        RETURN_IF_FAILED(adaptiveImageSet->get_Images(&images));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveImageSetConfig> imageSetConfig;
        RETURN_IF_FAILED(hostConfig->get_ImageSet(&imageSetConfig));

        ABI::AdaptiveNamespace::ImageSize imageSize;
        RETURN_IF_FAILED(adaptiveImageSet->get_ImageSize(&imageSize));

        if (imageSize == ABI::AdaptiveNamespace::ImageSize::None)
        {
            RETURN_IF_FAILED(imageSetConfig->get_ImageSize(&imageSize));
        }

        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        RETURN_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        ComPtr<IAdaptiveElementRenderer> imageRenderer;
        RETURN_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));
        if (imageRenderer != nullptr)
        {
            ABI::AdaptiveNamespace::ContainerStyle containerStyle;
            RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

            ComPtr<AdaptiveRenderArgs> childRenderArgs;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&childRenderArgs, containerStyle, xamlGrid.Get(), renderArgs));

            XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveImage, ABI::AdaptiveNamespace::IAdaptiveImage>(
                images.Get(),
                [imageSize, xamlGrid, renderContext, childRenderArgs, imageRenderer, imageSetConfig](IAdaptiveImage* adaptiveImage) {
                    ComPtr<IUIElement> uiImage;
                    ComPtr<IAdaptiveImage> localAdaptiveImage(adaptiveImage);
                    RETURN_IF_FAILED(localAdaptiveImage->put_Size(imageSize));

                    ComPtr<IAdaptiveCardElement> adaptiveElementImage;
                    localAdaptiveImage.As(&adaptiveElementImage);
                    RETURN_IF_FAILED(imageRenderer->Render(adaptiveElementImage.Get(), renderContext, childRenderArgs.Get(), &uiImage));

                    ComPtr<IFrameworkElement> imageAsFrameworkElement;
                    RETURN_IF_FAILED(uiImage.As(&imageAsFrameworkElement));

                    UINT32 maxImageHeight;
                    RETURN_IF_FAILED(imageSetConfig->get_MaxImageHeight(&maxImageHeight));
                    RETURN_IF_FAILED(imageAsFrameworkElement->put_MaxHeight(maxImageHeight));

                    ComPtr<IPanel> gridAsPanel;
                    RETURN_IF_FAILED(xamlGrid.As(&gridAsPanel));

                    XamlHelpers::AppendXamlElementToPanel(uiImage.Get(), gridAsPanel.Get());
                    return S_OK;
                });
        }
        else
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                                      HStringReference(L"No renderer found for type: Image").Get());
            *imageSetControl = nullptr;
            return S_OK;
        }

        ComPtr<IFrameworkElement> imageSetAsFrameworkElement;
        RETURN_IF_FAILED(xamlGrid.As(&imageSetAsFrameworkElement));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.ImageSet", imageSetAsFrameworkElement.Get()));

        return xamlGrid.CopyTo(imageSetControl);
    }

    static std::vector<std::string> GetChoiceSetValueVector(_In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput)
    {
        HString value;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_Value(value.GetAddressOf()));

        std::vector<std::string> values;
        std::string stdValue = HStringToUTF8(value.Get());
        std::stringstream streamValue(stdValue);

        while (streamValue.good())
        {
            std::string subString;
            std::getline(streamValue, subString, ',');
            values.push_back(subString);
        }

        return values;
    }

    static bool IsChoiceSelected(std::vector<std::string> selectedValues, _In_ IAdaptiveChoiceInput* choice)
    {
        HString value;
        THROW_IF_FAILED(choice->get_Value(value.GetAddressOf()));
        std::string stdValue = HStringToUTF8(value.Get());
        return std::find(selectedValues.begin(), selectedValues.end(), stdValue) != selectedValues.end();
    }

    HRESULT XamlBuilder::BuildCompactChoiceSetInput(_In_ IAdaptiveRenderContext* renderContext,
                                                    _In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                    _COM_Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IComboBox> comboBox =
            XamlHelpers::CreateXamlClass<IComboBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBox));

        // Set HorizontalAlignment to Stretch (defaults to Left for combo boxes)
        ComPtr<IFrameworkElement> comboBoxAsFrameworkElement;
        RETURN_IF_FAILED(comboBox.As(&comboBoxAsFrameworkElement));
        RETURN_IF_FAILED(comboBoxAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));

        ComPtr<IItemsControl> itemsControl;
        RETURN_IF_FAILED(comboBox.As(&itemsControl));

        ComPtr<IObservableVector<IInspectable*>> items;
        RETURN_IF_FAILED(itemsControl->get_Items(items.GetAddressOf()));

        ComPtr<IVector<IInspectable*>> itemsVector;
        RETURN_IF_FAILED(items.As(&itemsVector));

        ComPtr<IVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);
        boolean wrap;
        adaptiveChoiceSetInput->get_Wrap(&wrap);

        int currentIndex = 0;
        int selectedIndex = -1;
        XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [&currentIndex, &selectedIndex, itemsVector, values, wrap](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                HString title;
                RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));

                ComPtr<IComboBoxItem> comboBoxItem = XamlHelpers::CreateXamlClass<IComboBoxItem>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBoxItem));

                XamlHelpers::SetContent(comboBoxItem.Get(), title.Get(), wrap);

                // If multiple values are specified, no option is selected
                if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
                {
                    selectedIndex = currentIndex;
                }

                ComPtr<IInspectable> inspectable;
                RETURN_IF_FAILED(comboBoxItem.As(&inspectable));

                RETURN_IF_FAILED(itemsVector->Append(inspectable.Get()));
                currentIndex++;
                return S_OK;
            });

        ComPtr<ISelector> selector;
        RETURN_IF_FAILED(comboBox.As(&selector));
        RETURN_IF_FAILED(selector->put_SelectedIndex(selectedIndex));

        ComPtr<IUIElement> comboBoxAsUIElement;
        RETURN_IF_FAILED(comboBox.As(&comboBoxAsUIElement));
        RETURN_IF_FAILED(AddHandledTappedEvent(comboBoxAsUIElement.Get()));

        SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.ChoiceSet.Compact", comboBoxAsFrameworkElement.Get());

        return comboBoxAsUIElement.CopyTo(choiceInputSet);
    }

    HRESULT XamlBuilder::BuildExpandedChoiceSetInput(_In_ IAdaptiveRenderContext* renderContext,
                                                     _In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                     boolean isMultiSelect,
                                                     _COM_Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IVector<AdaptiveChoiceInput*>> choices;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        ComPtr<IStackPanel> stackPanel =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        stackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IPanel> panel;
        RETURN_IF_FAILED(stackPanel.As(&panel));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        boolean wrap;
        adaptiveChoiceSetInput->get_Wrap(&wrap);

        XamlHelpers::IterateOverVector<AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [panel, isMultiSelect, renderContext, values, wrap](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                ComPtr<IUIElement> choiceItem;
                if (isMultiSelect)
                {
                    ComPtr<ICheckBox> checkBox =
                        XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));
                    RETURN_IF_FAILED(checkBox.As(&choiceItem));

                    ComPtr<IFrameworkElement> frameworkElement;
                    RETURN_IF_FAILED(checkBox.As(&frameworkElement));
                    SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Choice.Multiselect", frameworkElement.Get());

                    XamlHelpers::SetToggleValue(choiceItem.Get(), IsChoiceSelected(values, adaptiveChoiceInput));
                }
                else
                {
                    ComPtr<IRadioButton> radioButton = XamlHelpers::CreateXamlClass<IRadioButton>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RadioButton));
                    RETURN_IF_FAILED(radioButton.As(&choiceItem));

                    ComPtr<IFrameworkElement> frameworkElement;
                    RETURN_IF_FAILED(radioButton.As(&frameworkElement));
                    SetStyleFromResourceDictionary(renderContext,
                                                   L"Adaptive.Input.Choice.SingleSelect",
                                                   frameworkElement.Get());

                    if (values.size() == 1)
                    {
                        // When isMultiSelect is false, only 1 specified value is accepted.
                        // Otherwise, leave all options unset
                        XamlHelpers::SetToggleValue(choiceItem.Get(), IsChoiceSelected(values, adaptiveChoiceInput));
                    }
                }

                HString title;
                RETURN_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));
                XamlHelpers::SetContent(choiceItem.Get(), title.Get(), wrap);

                RETURN_IF_FAILED(AddHandledTappedEvent(choiceItem.Get()));

                XamlHelpers::AppendXamlElementToPanel(choiceItem.Get(), panel.Get());
                return S_OK;
            });

        ComPtr<IFrameworkElement> choiceSetAsFrameworkElement;
        RETURN_IF_FAILED(stackPanel.As(&choiceSetAsFrameworkElement));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext,
                                                        L"Adaptive.Input.ChoiceSet.Expanded",
                                                        choiceSetAsFrameworkElement.Get()));

        return stackPanel.CopyTo(choiceInputSet);
    }

    static void AddInputValueToContext(_In_ IAdaptiveRenderContext* renderContext,
                                       _In_ IAdaptiveCardElement* adaptiveCardElement,
                                       _In_ IUIElement* inputUiElement)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveInputElement> inputElement;
        THROW_IF_FAILED(cardElement.As(&inputElement));

        ComPtr<InputValue> input;
        THROW_IF_FAILED(MakeAndInitialize<InputValue>(&input, inputElement.Get(), inputUiElement));
        THROW_IF_FAILED(renderContext->AddInputValue(input.Get()));
    }

    HRESULT XamlBuilder::BuildChoiceSetInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                             _In_ IAdaptiveRenderContext* renderContext,
                                             _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                             _COM_Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"ChoiceSet was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveChoiceSetInput> adaptiveChoiceSetInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveChoiceSetInput));

        ABI::AdaptiveNamespace::ChoiceSetStyle choiceSetStyle;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_ChoiceSetStyle(&choiceSetStyle));

        boolean isMultiSelect;
        RETURN_IF_FAILED(adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));

        if (choiceSetStyle == ABI::AdaptiveNamespace::ChoiceSetStyle_Compact && !isMultiSelect)
        {
            BuildCompactChoiceSetInput(renderContext, adaptiveChoiceSetInput.Get(), choiceInputSet);
        }
        else
        {
            BuildExpandedChoiceSetInput(renderContext, adaptiveChoiceSetInput.Get(), isMultiSelect, choiceInputSet);
        }

        AddInputValueToContext(renderContext, adaptiveCardElement, *choiceInputSet);
        return S_OK;
    }

    HRESULT XamlBuilder::BuildDateInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                        _COM_Outptr_ IUIElement** dateInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Date input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveDateInput> adaptiveDateInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveDateInput));

        ComPtr<ICalendarDatePicker> datePicker = XamlHelpers::CreateXamlClass<ICalendarDatePicker>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CalendarDatePicker));

        HString placeHolderText;
        RETURN_IF_FAILED(adaptiveDateInput->get_Placeholder(placeHolderText.GetAddressOf()));
        RETURN_IF_FAILED(datePicker->put_PlaceholderText(placeHolderText.Get()));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> datePickerAsFrameworkElement;
        RETURN_IF_FAILED(datePicker.As(&datePickerAsFrameworkElement));
        RETURN_IF_FAILED(datePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
        RETURN_IF_FAILED(datePickerAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));

        RETURN_IF_FAILED(datePicker.CopyTo(dateInputControl));

        // Value
        HString hstringValue;
        RETURN_IF_FAILED(adaptiveDateInput->get_Value(hstringValue.GetAddressOf()));
        std::string value = HStringToUTF8(hstringValue.Get());
        unsigned int year, month, day;
        if (DateTimePreparser::TryParseSimpleDate(value, year, month, day))
        {
            ComPtr<IReference<DateTime>> initialDateTimeReference;
            RETURN_IF_FAILED(GetDateTimeReference(year, month, day, &initialDateTimeReference));
            RETURN_IF_FAILED(datePicker->put_Date(initialDateTimeReference.Get()));
        }

        // Min date
        HString hstringMin;
        RETURN_IF_FAILED(adaptiveDateInput->get_Min(hstringMin.GetAddressOf()));
        std::string min = HStringToUTF8(hstringMin.Get());
        if (DateTimePreparser::TryParseSimpleDate(min, year, month, day))
        {
            DateTime minDate = GetDateTime(year, month, day);
            RETURN_IF_FAILED(datePicker->put_MinDate(minDate));
        }

        // Max date
        HString hstringMax;
        RETURN_IF_FAILED(adaptiveDateInput->get_Max(hstringMax.GetAddressOf()));
        std::string max = HStringToUTF8(hstringMax.Get());
        if (DateTimePreparser::TryParseSimpleDate(max, year, month, day))
        {
            DateTime maxDate = GetDateTime(year, month, day);
            RETURN_IF_FAILED(datePicker->put_MaxDate(maxDate));
        }

        RETURN_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Date", datePickerAsFrameworkElement.Get()));

        AddInputValueToContext(renderContext, adaptiveCardElement, *dateInputControl);
        return S_OK;
    }

    HRESULT XamlBuilder::BuildNumberInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                          _In_ IAdaptiveRenderContext* renderContext,
                                          _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                          _COM_Outptr_ IUIElement** numberInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Number input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveNumberInput> adaptiveNumberInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveNumberInput));

        ComPtr<ITextBox> textBox =
            XamlHelpers::CreateXamlClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

        ComPtr<IInputScopeName> inputScopeName =
            XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
        RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Number));

        ComPtr<IInputScope> inputScope =
            XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
        ComPtr<IVector<InputScopeName*>> names;
        RETURN_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
        RETURN_IF_FAILED(names->Append(inputScopeName.Get()));

        RETURN_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

        INT32 value;
        RETURN_IF_FAILED(adaptiveNumberInput->get_Value(&value));

        std::wstring stringValue = std::to_wstring(value);
        RETURN_IF_FAILED(textBox->put_Text(HStringReference(stringValue.c_str()).Get()));

        ComPtr<ITextBox2> textBox2;
        RETURN_IF_FAILED(textBox.As(&textBox2));

        HString placeHolderText;
        RETURN_IF_FAILED(adaptiveNumberInput->get_Placeholder(placeHolderText.GetAddressOf()));
        RETURN_IF_FAILED(textBox2->put_PlaceholderText(placeHolderText.Get()));

        ComPtr<IFrameworkElement> frameworkElement;
        RETURN_IF_FAILED(textBox.As(&frameworkElement));
        RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Number", frameworkElement.Get()));

        // TODO: Handle max and min?
        RETURN_IF_FAILED(textBox.CopyTo(numberInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *numberInputControl);

        return S_OK;
    }

    static HRESULT HandleKeydownForInlineAction(_In_ IKeyRoutedEventArgs* args,
                                                _In_ IAdaptiveActionInvoker* actionInvoker,
                                                _In_ IAdaptiveActionElement* inlineAction)
    {
        ABI::Windows::System::VirtualKey key;
        RETURN_IF_FAILED(args->get_Key(&key));

        if (key == ABI::Windows::System::VirtualKey::VirtualKey_Enter)
        {
            ComPtr<ABI::Windows::UI::Core::ICoreWindowStatic> coreWindowStatics;
            RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Core_CoreWindow).Get(), &coreWindowStatics));

            ComPtr<ABI::Windows::UI::Core::ICoreWindow> coreWindow;
            RETURN_IF_FAILED(coreWindowStatics->GetForCurrentThread(&coreWindow));

            ABI::Windows::UI::Core::CoreVirtualKeyStates shiftKeyState;
            RETURN_IF_FAILED(coreWindow->GetKeyState(ABI::Windows::System::VirtualKey_Shift, &shiftKeyState));

            ABI::Windows::UI::Core::CoreVirtualKeyStates ctrlKeyState;
            RETURN_IF_FAILED(coreWindow->GetKeyState(ABI::Windows::System::VirtualKey_Control, &ctrlKeyState));

            if (shiftKeyState == ABI::Windows::UI::Core::CoreVirtualKeyStates_None &&
                ctrlKeyState == ABI::Windows::UI::Core::CoreVirtualKeyStates_None)
            {
                RETURN_IF_FAILED(actionInvoker->SendActionEvent(inlineAction));
                RETURN_IF_FAILED(args->put_Handled(true));
            }
        }

        return S_OK;
    }

    static bool WarnForInlineShowCard(_In_ IAdaptiveRenderContext* renderContext,
                                      _In_ IAdaptiveActionElement* action,
                                      const std::wstring& warning)
    {
        if (action != nullptr)
        {
            ABI::AdaptiveNamespace::ActionType actionType;
            THROW_IF_FAILED(action->get_ActionType(&actionType));

            if (actionType == ABI::AdaptiveNamespace::ActionType::ShowCard)
            {
                THROW_IF_FAILED(renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::UnsupportedValue,
                                                          HStringReference(warning.c_str()).Get()));
                return true;
            }
        }

        return false;
    }

    void XamlBuilder::HandleInlineAcion(_In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                        _In_ ITextBox* textBox,
                                        _In_ IAdaptiveActionElement* inlineAction,
                                        _COM_Outptr_ IUIElement** textBoxWithInlineAction)
    {
        ComPtr<ITextBox> localTextBox(textBox);
        ComPtr<IAdaptiveActionElement> localInlineAction(inlineAction);

        ABI::AdaptiveNamespace::ActionType actionType;
        THROW_IF_FAILED(localInlineAction->get_ActionType(&actionType));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        // Inline ShowCards are not supported for inline actions
        if (WarnForInlineShowCard(renderContext, localInlineAction.Get(), L"Inline ShowCard not supported for InlineAction"))
        {
            THROW_IF_FAILED(localTextBox.CopyTo(textBoxWithInlineAction));
            return;
        }

        // Create a grid to hold the text box and the action button
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
        THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
        ComPtr<IPanel> gridAsPanel;
        THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));

        // Create the first column and add the text box to it
        ComPtr<IColumnDefinition> textBoxColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        THROW_IF_FAILED(textBoxColumnDefinition->put_Width({1, GridUnitType::GridUnitType_Star}));
        THROW_IF_FAILED(columnDefinitions->Append(textBoxColumnDefinition.Get()));

        ComPtr<IFrameworkElement> textBoxAsFrameworkElement;
        THROW_IF_FAILED(localTextBox.As(&textBoxAsFrameworkElement));

        THROW_IF_FAILED(gridStatics->SetColumn(textBoxAsFrameworkElement.Get(), 0));
        XamlHelpers::AppendXamlElementToPanel(textBox, gridAsPanel.Get());

        // Create a separator column
        ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        THROW_IF_FAILED(separatorColumnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Auto}));
        THROW_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

        UINT spacingSize;
        THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), ABI::AdaptiveNamespace::Spacing::Default, &spacingSize));

        auto separator = CreateSeparator(renderContext, spacingSize, 0, {0}, false);

        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
        THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));

        THROW_IF_FAILED(gridStatics->SetColumn(separatorAsFrameworkElement.Get(), 1));
        XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());

        // Create a column for the button
        ComPtr<IColumnDefinition> inlineActionColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        THROW_IF_FAILED(inlineActionColumnDefinition->put_Width({0, GridUnitType::GridUnitType_Auto}));
        THROW_IF_FAILED(columnDefinitions->Append(inlineActionColumnDefinition.Get()));

        // Create a text box with the action title. This will be the tool tip if there's an icon
        // or the content of the button otherwise
        ComPtr<ITextBlock> titleTextBlock =
            XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
        HString title;
        THROW_IF_FAILED(localInlineAction->get_Title(title.GetAddressOf()));
        THROW_IF_FAILED(titleTextBlock->put_Text(title.Get()));

        HString iconUrl;
        THROW_IF_FAILED(localInlineAction->get_IconUrl(iconUrl.GetAddressOf()));
        ComPtr<IUIElement> actionUIElement;
        if (iconUrl != nullptr)
        {
            // Render the icon using the adaptive image renderer
            ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
            ComPtr<IAdaptiveElementRenderer> imageRenderer;
            THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));

            ComPtr<IAdaptiveImage> adaptiveImage;
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));

            THROW_IF_FAILED(adaptiveImage->put_Url(iconUrl.Get()));

            ComPtr<IAdaptiveCardElement> adaptiveImageAsElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveImageAsElement));

            THROW_IF_FAILED(imageRenderer->Render(adaptiveImageAsElement.Get(), renderContext, renderArgs, &actionUIElement));

            // Add the tool tip
            ComPtr<IToolTip> toolTip =
                XamlHelpers::CreateXamlClass<IToolTip>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ToolTip));
            ComPtr<IContentControl> toolTipAsContentControl;
            THROW_IF_FAILED(toolTip.As(&toolTipAsContentControl));
            THROW_IF_FAILED(toolTipAsContentControl->put_Content(titleTextBlock.Get()));

            ComPtr<IToolTipServiceStatics> toolTipService;
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ToolTipService).Get(),
                                                 &toolTipService));

            ComPtr<IDependencyObject> actionAsDependencyObject;
            THROW_IF_FAILED(actionUIElement.As(&actionAsDependencyObject));

            THROW_IF_FAILED(toolTipService->SetToolTip(actionAsDependencyObject.Get(), toolTip.Get()));
        }
        else
        {
            // If there's no icon, just use the title text. Put it centered in a grid so it is
            // centered relative to the text box.
            ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
            THROW_IF_FAILED(titleTextBlock.As(&textBlockAsFrameworkElement));
            THROW_IF_FAILED(textBlockAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Center));

            ComPtr<IGrid> titleGrid =
                XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            ComPtr<IPanel> panel;
            THROW_IF_FAILED(titleGrid.As(&panel));
            XamlHelpers::AppendXamlElementToPanel(titleTextBlock.Get(), panel.Get());

            THROW_IF_FAILED(panel.As(&actionUIElement));
        }

        // Make the action the same size as the text box
        EventRegistrationToken eventToken;
        THROW_IF_FAILED(textBoxAsFrameworkElement->add_Loaded(
            Callback<IRoutedEventHandler>([actionUIElement, textBoxAsFrameworkElement](IInspectable* /*sender*/, IRoutedEventArgs *
                                                                                       /*args*/) -> HRESULT {
                ComPtr<IFrameworkElement> actionFrameworkElement;
                RETURN_IF_FAILED(actionUIElement.As(&actionFrameworkElement));

                return SetMatchingHeight(actionFrameworkElement.Get(), textBoxAsFrameworkElement.Get());
            }).Get(),
            &eventToken));

        // Wrap the action in a button
        ComPtr<IUIElement> touchTargetUIElement;
        WrapInTouchTarget(nullptr, actionUIElement.Get(), localInlineAction.Get(), renderContext, false, L"Adaptive.Input.Text.InlineAction", &touchTargetUIElement);

        ComPtr<IFrameworkElement> touchTargetFrameworkElement;
        THROW_IF_FAILED(touchTargetUIElement.As(&touchTargetFrameworkElement));

        // Align to bottom so the icon stays with the bottom of the text box as it grows in the multiline case
        THROW_IF_FAILED(touchTargetFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Bottom));

        // Add the action to the column
        THROW_IF_FAILED(gridStatics->SetColumn(touchTargetFrameworkElement.Get(), 2));
        XamlHelpers::AppendXamlElementToPanel(touchTargetFrameworkElement.Get(), gridAsPanel.Get());

        // If this isn't a multiline input, enter should invoke the action
        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        THROW_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));

        boolean isMultiLine;
        THROW_IF_FAILED(textBox->get_AcceptsReturn(&isMultiLine));

        if (!isMultiLine)
        {
            ComPtr<IUIElement> textBoxAsUIElement;
            THROW_IF_FAILED(localTextBox.As(&textBoxAsUIElement));

            EventRegistrationToken keyDownEventToken;
            THROW_IF_FAILED(textBoxAsUIElement->add_KeyDown(
                Callback<IKeyEventHandler>([actionInvoker, localInlineAction](IInspectable* /*sender*/, IKeyRoutedEventArgs* args) -> HRESULT {
                    return HandleKeydownForInlineAction(args, actionInvoker.Get(), localInlineAction.Get());
                }).Get(),
                &keyDownEventToken));
        }

        THROW_IF_FAILED(xamlGrid.CopyTo(textBoxWithInlineAction));
    }

    HRESULT XamlBuilder::BuildTextInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                        _COM_Outptr_ IUIElement** textInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Text Input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextInput> adaptiveTextInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveTextInput));

        ComPtr<ITextBox> textBox =
            XamlHelpers::CreateXamlClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

        boolean isMultiLine;
        RETURN_IF_FAILED(adaptiveTextInput->get_IsMultiline(&isMultiLine));
        RETURN_IF_FAILED(textBox->put_AcceptsReturn(isMultiLine));

        HString textValue;
        RETURN_IF_FAILED(adaptiveTextInput->get_Value(textValue.GetAddressOf()));
        RETURN_IF_FAILED(textBox->put_Text(textValue.Get()));

        UINT32 maxLength;
        RETURN_IF_FAILED(adaptiveTextInput->get_MaxLength(&maxLength));
        RETURN_IF_FAILED(textBox->put_MaxLength(maxLength));

        ComPtr<ITextBox2> textBox2;
        RETURN_IF_FAILED(textBox.As(&textBox2));

        HString placeHolderText;
        RETURN_IF_FAILED(adaptiveTextInput->get_Placeholder(placeHolderText.GetAddressOf()));
        RETURN_IF_FAILED(textBox2->put_PlaceholderText(placeHolderText.Get()));

        ABI::AdaptiveNamespace::TextInputStyle textInputStyle;
        RETURN_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));

        ComPtr<IInputScopeName> inputScopeName =
            XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
        switch (textInputStyle)
        {
        case ABI::AdaptiveNamespace::TextInputStyle::Email:
            RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_EmailSmtpAddress));
            break;

        case ABI::AdaptiveNamespace::TextInputStyle::Tel:
            RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_TelephoneNumber));
            break;

        case ABI::AdaptiveNamespace::TextInputStyle::Url:
            RETURN_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Url));
            break;
        }

        ComPtr<IInputScope> inputScope =
            XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
        ComPtr<IVector<InputScopeName*>> names;
        RETURN_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
        RETURN_IF_FAILED(names->Append(inputScopeName.Get()));

        RETURN_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

        ComPtr<IUIElement> textBoxAsUIElement;
        textBox.As(&textBoxAsUIElement);
        AddInputValueToContext(renderContext, adaptiveCardElement, textBoxAsUIElement.Get());

        ComPtr<IAdaptiveActionElement> inlineAction;
        RETURN_IF_FAILED(adaptiveTextInput->get_InlineAction(&inlineAction));

        ComPtr<IFrameworkElement> textBoxAsFrameworkElement;
        RETURN_IF_FAILED(textBox.As(&textBoxAsFrameworkElement));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBoxAsFrameworkElement.Get()));

        if (inlineAction != nullptr)
        {
            ComPtr<IUIElement> textBoxWithInlineAction;
            HandleInlineAcion(renderContext, renderArgs, textBox.Get(), inlineAction.Get(), &textBoxWithInlineAction);
            if (!isMultiLine)
            {
                RETURN_IF_FAILED(textBoxWithInlineAction.As(&textBoxAsFrameworkElement));
                RETURN_IF_FAILED(textBoxAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
            }

            RETURN_IF_FAILED(textBoxWithInlineAction.CopyTo(textInputControl));
        }
        else
        {
            if (!isMultiLine)
            {
                RETURN_IF_FAILED(textBoxAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
            }

            RETURN_IF_FAILED(textBox.CopyTo(textInputControl));
        }
        return S_OK;
    }

    HRESULT XamlBuilder::BuildTimeInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                        _COM_Outptr_ IUIElement** timeInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Time Input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<ITimePicker> timePicker =
            XamlHelpers::CreateXamlClass<ITimePicker>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TimePicker));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> timePickerAsFrameworkElement;
        RETURN_IF_FAILED(timePicker.As(&timePickerAsFrameworkElement));
        RETURN_IF_FAILED(timePickerAsFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment_Stretch));
        RETURN_IF_FAILED(timePickerAsFrameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));

        RETURN_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Time", timePickerAsFrameworkElement.Get()));

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTimeInput> adaptiveTimeInput;
        THROW_IF_FAILED(cardElement.As(&adaptiveTimeInput));

        // Set initial value
        HString hstringValue;
        THROW_IF_FAILED(adaptiveTimeInput->get_Value(hstringValue.GetAddressOf()));
        std::string value = HStringToUTF8(hstringValue.Get());
        unsigned int hours, minutes;
        if (DateTimePreparser::TryParseSimpleTime(value, hours, minutes))
        {
            TimeSpan initialTime{(INT64)(hours * 60 + minutes) * 10000000 * 60};
            THROW_IF_FAILED(timePicker->put_Time(initialTime));
        }

        // Note: Placeholder text and min/max are not supported by ITimePicker

        RETURN_IF_FAILED(timePicker.CopyTo(timeInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *timeInputControl);
        return S_OK;
    }

    HRESULT XamlBuilder::BuildToggleInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                          _In_ IAdaptiveRenderContext* renderContext,
                                          _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                          _COM_Outptr_ IUIElement** toggleInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Toggle Input was stripped from card because interactivity is not supported").Get());
            return S_OK;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveToggleInput> adaptiveToggleInput;
        RETURN_IF_FAILED(cardElement.As(&adaptiveToggleInput));

        ComPtr<ICheckBox> checkBox =
            XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));

        HString title;
        RETURN_IF_FAILED(adaptiveToggleInput->get_Title(title.GetAddressOf()));

        boolean wrap;
        adaptiveToggleInput->get_Wrap(&wrap);

        XamlHelpers::SetContent(checkBox.Get(), title.Get(), wrap);

        HString value;
        RETURN_IF_FAILED(adaptiveToggleInput->get_Value(value.GetAddressOf()));

        HString valueOn;
        RETURN_IF_FAILED(adaptiveToggleInput->get_ValueOn(valueOn.GetAddressOf()));

        INT32 compareValueOn;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(value.Get(), valueOn.Get(), &compareValueOn));

        XamlHelpers::SetToggleValue(checkBox.Get(), (compareValueOn == 0));

        ComPtr<IUIElement> checkboxAsUIElement;
        RETURN_IF_FAILED(checkBox.As(&checkboxAsUIElement));
        RETURN_IF_FAILED(AddHandledTappedEvent(checkboxAsUIElement.Get()));

        ComPtr<IFrameworkElement> frameworkElement;
        RETURN_IF_FAILED(checkBox.As(&frameworkElement));
        RETURN_IF_FAILED(frameworkElement->put_VerticalAlignment(ABI::Windows::UI::Xaml::VerticalAlignment_Top));
        RETURN_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", frameworkElement.Get()));

        RETURN_IF_FAILED(checkboxAsUIElement.CopyTo(toggleInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *toggleInputControl);
        return S_OK;
    }

    HRESULT XamlBuilder::BuildMedia(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    _In_ IAdaptiveRenderArgs* renderArgs,
                                    _COM_Outptr_ IUIElement** mediaControl)
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
        if (!SupportsInteractivity(hostConfig.Get()))
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
        WrapInTouchTarget(adaptiveCardElement, posterContainer.Get(), nullptr, renderContext, true, L"Adaptive.SelectAction", &touchTargetUIElement);

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

        // Take a reference to the mime type string for the lambda
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

    bool XamlBuilder::SupportsInteractivity(_In_ IAdaptiveHostConfig* hostConfig)
    {
        boolean supportsInteractivity;
        THROW_IF_FAILED(hostConfig->get_SupportsInteractivity(&supportsInteractivity));
        return Boolify(supportsInteractivity);
    }

    void XamlBuilder::CreateAppropriateButton(ABI::AdaptiveNamespace::ActionType actionType, ComPtr<IButton>& button)
    {
        // construct an appropriate button for the action type
        if (actionType == ABI::AdaptiveNamespace::ActionType_OpenUrl)
        {
            // OpenUrl buttons should appear as links for accessibility purposes, so we use our custom LinkButton.
            auto linkButton = winrt::make<LinkButton>();
            button = linkButton.as<IButton>().detach();
        }

        if (!button)
        {
            // Either non-OpenUrl action or instantiating LinkButton failed. Use standard button.
            button = XamlHelpers::CreateXamlClass<IButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Button));
        }
    }

    void XamlBuilder::WrapInTouchTarget(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IUIElement* elementToWrap,
                                        _In_ IAdaptiveActionElement* action,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        bool fullWidth,
                                        const std::wstring& style,
                                        _COM_Outptr_ IUIElement** finalElement)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        if (WarnForInlineShowCard(renderContext, action, L"Inline ShowCard not supported for SelectAction"))
        {
            // Was inline show card, so don't wrap the element and just return
            ComPtr<IUIElement> localElementToWrap(elementToWrap);
            localElementToWrap.CopyTo(finalElement);
            return;
        }

        // We only care about action type for creating the button below. If an action wasn't supplied (this can happen
        // e.g. when using WrapInTouchTarget to build a media element), just default to a non-OpenUrl action type so
        // that a generic button is used.
        ABI::AdaptiveNamespace::ActionType actionType = ABI::AdaptiveNamespace::ActionType::Submit;
        if (action != nullptr)
        {
            action->get_ActionType(&actionType);
        }

        ComPtr<IButton> button;
        CreateAppropriateButton(actionType, button);

        ComPtr<IContentControl> buttonAsContentControl;
        THROW_IF_FAILED(button.As(&buttonAsContentControl));
        THROW_IF_FAILED(buttonAsContentControl->put_Content(elementToWrap));

        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 cardPadding = 0;
        if (fullWidth)
        {
            THROW_IF_FAILED(spacingConfig->get_Padding(&cardPadding));
        }

        ComPtr<IFrameworkElement> buttonAsFrameworkElement;
        THROW_IF_FAILED(button.As(&buttonAsFrameworkElement));

        // We want the hit target to equally split the vertical space above and below the current item.
        // However, all we know is the spacing of the current item, which only applies to the spacing above.
        // We don't know what the spacing of the NEXT element will be, so we can't calculate the correct spacing
        // below. For now, we'll simply assume the bottom spacing is the same as the top. NOTE: Only apply spacings
        // (padding, margin) for adaptive card elements to avoid adding spacings to card-level selectAction.
        if (adaptiveCardElement != nullptr)
        {
            ABI::AdaptiveNamespace::Spacing elementSpacing;
            THROW_IF_FAILED(adaptiveCardElement->get_Spacing(&elementSpacing));
            UINT spacingSize;
            THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), elementSpacing, &spacingSize));
            double topBottomPadding = spacingSize / 2.0;

            // For button padding, we apply the cardPadding and topBottomPadding (and then we negate these in the margin)
            ComPtr<IControl> buttonAsControl;
            THROW_IF_FAILED(button.As(&buttonAsControl));
            THROW_IF_FAILED(buttonAsControl->put_Padding({(double)cardPadding, topBottomPadding, (double)cardPadding, topBottomPadding}));

            double negativeCardMargin = cardPadding * -1.0;
            double negativeTopBottomMargin = topBottomPadding * -1.0;

            THROW_IF_FAILED(buttonAsFrameworkElement->put_Margin(
                {negativeCardMargin, negativeTopBottomMargin, negativeCardMargin, negativeTopBottomMargin}));
        }

        // Style the hit target button
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, style.c_str(), buttonAsFrameworkElement.Get()));

        if (action != nullptr)
        {
            // If we have an action, use the title for the AutomationProperties.Name
            HString title;
            THROW_IF_FAILED(action->get_Title(title.GetAddressOf()));

            ComPtr<IDependencyObject> buttonAsDependencyObject;
            THROW_IF_FAILED(button.As(&buttonAsDependencyObject));

            ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
            THROW_IF_FAILED(
                GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                     &automationPropertiesStatics));

            THROW_IF_FAILED(automationPropertiesStatics->SetName(buttonAsDependencyObject.Get(), title.Get()));

            WireButtonClickToAction(button.Get(), action, renderContext);
        }

        THROW_IF_FAILED(button.CopyTo(finalElement));
    }

    void XamlBuilder::HandleSelectAction(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                         _In_ IAdaptiveActionElement* selectAction,
                                         _In_ IAdaptiveRenderContext* renderContext,
                                         _In_ IUIElement* uiElement,
                                         bool supportsInteractivity,
                                         bool fullWidthTouchTarget,
                                         _COM_Outptr_ IUIElement** outUiElement)
    {
        if (selectAction != nullptr && supportsInteractivity)
        {
            WrapInTouchTarget(adaptiveCardElement, uiElement, selectAction, renderContext, fullWidthTouchTarget, L"Adaptive.SelectAction", outUiElement);
        }
        else
        {
            if (selectAction != nullptr)
            {
                renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                                          HStringReference(L"SelectAction present, but Interactivity is not supported").Get());
            }

            ComPtr<IUIElement> localUiElement(uiElement);
            THROW_IF_FAILED(localUiElement.CopyTo(outUiElement));
        }
    }

    void XamlBuilder::WireButtonClickToAction(_In_ IButton* button, _In_ IAdaptiveActionElement* action, _In_ IAdaptiveRenderContext* renderContext)
    {
        // Note that this method currently doesn't support inline show card actions, it
        // assumes the caller won't call this method if inline show card is specified.
        ComPtr<IButton> localButton(button);
        ComPtr<IAdaptiveActionInvoker> actionInvoker;
        THROW_IF_FAILED(renderContext->get_ActionInvoker(&actionInvoker));
        ComPtr<IAdaptiveActionElement> strongAction(action);

        // Add click handler
        ComPtr<IButtonBase> buttonBase;
        THROW_IF_FAILED(localButton.As(&buttonBase));

        EventRegistrationToken clickToken;
        THROW_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>([strongAction, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs *
                                                                                                          /*args*/) -> HRESULT {
                                                  THROW_IF_FAILED(actionInvoker->SendActionEvent(strongAction.Get()));
                                                  return S_OK;
                                              }).Get(),
                                              &clickToken));
    }

    HRESULT XamlBuilder::AddHandledTappedEvent(_In_ IUIElement* uiElement)
    {
        if (uiElement == nullptr)
        {
            return E_INVALIDARG;
        }

        EventRegistrationToken clickToken;
        // Add Tap handler that sets the event as handled so that it doesn't propagate to the parent containers.
        return uiElement->add_Tapped(Callback<ITappedEventHandler>([](IInspectable* /*sender*/, ITappedRoutedEventArgs* args) -> HRESULT {
                                         return args->put_Handled(TRUE);
                                     }).Get(),
                                     &clickToken);
    }

    template<typename T>
    static void XamlBuilder::SetVerticalContentAlignmentToChildren(_In_ T* container,
                                                                   _In_ ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment)
    {
        ComPtr<T> localContainer(container);
        ComPtr<IWholeItemsPanel> containerAsPanel;
        THROW_IF_FAILED(localContainer.As(&containerAsPanel));

        ComPtr<WholeItemsPanel> panel = PeekInnards<WholeItemsPanel>(containerAsPanel);
        panel->SetVerticalContentAlignment(verticalContentAlignment);
    }
}
