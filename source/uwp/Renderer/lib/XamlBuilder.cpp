#include "pch.h"

#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveImage.h"
#include <windows.foundation.collections.h>
#include <windows.storage.h>
#include <windows.ui.xaml.shapes.h>
#include <windows.web.http.h>
#include <windows.web.http.filters.h>
#include "XamlBuilder.h"
#include "AdaptiveCardGetResourceStreamArgs.h"
#include "AdaptiveCardResourceResolvers.h"
#include "XamlHelpers.h"
#include "AdaptiveRenderArgs.h"
#include "json/json.h"
#include "WholeItemsPanel.h"
#include "AdaptiveCardRendererComponent.h"
#include "MarkDownParser.h"
#include "HtmlHelpers.h"
#include "DateTimeParser.h"

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
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::Web::Http;
using namespace ABI::Windows::Web::Http::Filters;

const PCWSTR c_TextBlockSubtleOpacityKey = L"TextBlock.SubtleOpacity";
const PCWSTR c_BackgroundImageOverlayBrushKey = L"AdaptiveCard.BackgroundOverlayBrush";

AdaptiveNamespaceStart
    XamlBuilder::XamlBuilder()
    {

        m_imageLoadTracker.AddListener(dynamic_cast<IImageLoadTrackerListener*>(this));

        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_RandomAccessStream).Get(), &m_randomAccessStreamStatics));
    }

    _Use_decl_annotations_
    ComPtr<IUIElement> XamlBuilder::CreateSeparator(
        _Inout_ IAdaptiveRenderContext* renderContext,
        UINT spacing, 
        UINT separatorThickness, 
        ABI::Windows::UI::Color separatorColor,
        bool isHorizontal)
    {
        ComPtr<IGrid> separator = XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
        THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));

        ComPtr<IBrush> lineColorBrush = GetSolidColorBrush(separatorColor);
        ComPtr<IPanel> separatorAsPanel;
        THROW_IF_FAILED(separator.As(&separatorAsPanel));
        separatorAsPanel->put_Background(lineColorBrush.Get());

        UINT32 separatorMarginValue = spacing > separatorThickness ? (spacing - separatorThickness) / 2 : 0;
        Thickness margin = { 0, 0, 0, 0 };

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

    _Use_decl_annotations_
    void XamlBuilder::BuildXamlTreeFromAdaptiveCard(
        IAdaptiveCard* adaptiveCard,
        IFrameworkElement** xamlTreeRoot, 
        AdaptiveCardRenderer* renderer,
        AdaptiveRenderContext* renderContext,
        boolean isOuterCard,
        ABI::AdaptiveNamespace::ContainerStyle defaultContainerStyle)
    {
        *xamlTreeRoot = nullptr;
        if (adaptiveCard != nullptr)
        {
            ComPtr<IAdaptiveHostConfig> hostConfig;
            THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
            ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
            THROW_IF_FAILED(hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

            boolean allowCustomStyle;
            THROW_IF_FAILED(adaptiveCardConfig->get_AllowCustomStyle(&allowCustomStyle));

            ABI::AdaptiveNamespace::ContainerStyle containerStyle = defaultContainerStyle;
            if (allowCustomStyle)
            {
                ABI::AdaptiveNamespace::ContainerStyle cardStyle;
                THROW_IF_FAILED(adaptiveCard->get_Style(&cardStyle));

                if (cardStyle != ABI::AdaptiveNamespace::ContainerStyle::None)
                {
                    containerStyle = cardStyle;
                }
            }
            ComPtr<IAdaptiveRenderArgs> renderArgs;
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&renderArgs, containerStyle, nullptr));

            ComPtr<IPanel> outerElementContainer;
            ComPtr<IPanel> bodyElementContainer;
            ComPtr<IUIElement> rootElement = CreateRootCardElement(adaptiveCard, renderContext, renderArgs.Get(), &outerElementContainer, &bodyElementContainer);
            ComPtr<IFrameworkElement> childElementContainerAsFE;
            THROW_IF_FAILED(rootElement.As(&childElementContainerAsFE));

            // Enumerate the child items of the card and build xaml for them
            ComPtr<IVector<IAdaptiveCardElement*>> body;
            THROW_IF_FAILED(adaptiveCard->get_Body(&body));
            ComPtr<IAdaptiveRenderArgs> bodyRenderArgs;
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&bodyRenderArgs, containerStyle, childElementContainerAsFE.Get()));
            BuildPanelChildren(body.Get(), bodyElementContainer.Get(), renderContext, bodyRenderArgs.Get(), [](IUIElement*) {});

            ComPtr<IVector<IAdaptiveActionElement*>> actions;
            THROW_IF_FAILED(adaptiveCard->get_Actions(&actions));
            UINT32 actionsSize;
            THROW_IF_FAILED(actions->get_Size(&actionsSize));
            if (actionsSize > 0)
            {
                if (SupportsInteractivity(hostConfig.Get()))
                {
                    unsigned int bodyCount;
                    THROW_IF_FAILED(body->get_Size(&bodyCount));
                    BuildActions(actions.Get(), renderer, outerElementContainer.Get(), bodyElementContainer.Get(), bodyCount > 0, renderContext, containerStyle);
                }
                else
                {
                    renderContext->AddWarning(
                        ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                        HStringReference(L"Actions collection was present in card, but interactivity is not supported").Get());
                }
            }

            if (isOuterCard)
            {
                THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", childElementContainerAsFE.Get()));
            }
            else
            {
                THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.ShowCard.Card", childElementContainerAsFE.Get()));
            }

            THROW_IF_FAILED(childElementContainerAsFE.CopyTo(xamlTreeRoot));

            if (isOuterCard)
            {
                if (m_listeners.size() == 0)
                {
                    // If we're done and no one's listening for the images to load, make sure 
                    // any outstanding image loads are no longer tracked.
                    m_imageLoadTracker.AbandonOutstandingImages();
                }
                else if (m_imageLoadTracker.GetTotalImagesTracked() == 0)
                {
                    // If there are no images to track, fire the all images loaded
                    // event to signal the xaml is ready
                    FireAllImagesLoaded();
                }
            }
        }
    }

    _Use_decl_annotations_
    HRESULT XamlBuilder::AddListener(IXamlBuilderListener* listener) noexcept try
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
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT XamlBuilder::RemoveListener(IXamlBuilderListener* listener) noexcept try
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
    } CATCH_RETURN;

    HRESULT XamlBuilder::SetFixedDimensions(_In_ UINT width, _In_ UINT height) noexcept
    {
        m_fixedDimensions = true;
        m_fixedWidth = width;
        m_fixedHeight = height;
        return S_OK;
    }

    HRESULT XamlBuilder::SetEnableXamlImageHandling(_In_ bool enableXamlImageHandling) noexcept
    {
        m_enableXamlImageHandling = enableXamlImageHandling;
        return S_OK;
    }

    _Use_decl_annotations_
    template<typename T>
    HRESULT XamlBuilder::TryGetResourceFromResourceDictionaries(IResourceDictionary* resourceDictionary, std::wstring resourceName, T** style)
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
            THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(), &propertyValueStatics));
            ComPtr<IInspectable> resourceKey;
            THROW_IF_FAILED(propertyValueStatics->CreateString(HStringReference(resourceName.c_str()).Get(), resourceKey.GetAddressOf()));

            // Search for the named resource
            ComPtr<IResourceDictionary> strongDictionary = resourceDictionary;
            ComPtr<IInspectable> dictionaryValue;
            ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;

            boolean hasKey{};
            if (SUCCEEDED(strongDictionary.As(&resourceDictionaryMap)) &&
                SUCCEEDED(resourceDictionaryMap->HasKey(resourceKey.Get(), &hasKey)) &&
                hasKey && SUCCEEDED(resourceDictionaryMap->Lookup(resourceKey.Get(), dictionaryValue.GetAddressOf())))
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

    HRESULT XamlBuilder::SetStyleFromResourceDictionary(
        IAdaptiveRenderContext* renderContext,
        std::wstring resourceName,
        IFrameworkElement* frameworkElement)
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

    _Use_decl_annotations_
    ComPtr<IUIElement> XamlBuilder::CreateRootCardElement(
        IAdaptiveCard* adaptiveCard,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IPanel** outerElementContainer,
        IPanel** bodyElementContainer)
    {
        // The root of an adaptive card is a composite of several elements, depending on the card
        // properties.  From back to fron these are:
        // Grid - Root element, used to enable children to stack above each other and size to fit
        // Image (optional) - Holds the background image if one is set
        // Shape (optional) - Provides the background image overlay, if one is set
        // StackPanel - The container for all the card's body elements
        ComPtr<IGrid> rootElement = XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
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
            ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
            THROW_IF_FAILED(rootAsPanel->put_Background(backgroundColorBrush.Get()));
        }

        ComPtr<IUriRuntimeClass> backgroundImageUrl;
        THROW_IF_FAILED(adaptiveCard->get_BackgroundImage(&backgroundImageUrl));
        if (backgroundImageUrl != nullptr)
        {
            ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImageUrl.Get(), renderContext, renderArgs);
        }

        // Outer panel that contains the main body and any inline show cards
        ComPtr<WholeItemsPanel> outerPanel;
        THROW_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&outerPanel));
        ComPtr<IPanel> outerPanelAsPanel;
        THROW_IF_FAILED(outerPanel.As(&outerPanelAsPanel));

        // Now create the inner stack panel to serve as the root host for all the 
        // body elements and apply padding from host configuration
        ComPtr<WholeItemsPanel> bodyElementHost;
        THROW_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&bodyElementHost));
        bodyElementHost->SetMainPanel(TRUE);
        bodyElementHost->SetAdaptiveHeight(TRUE);

        ComPtr<IFrameworkElement> bodyElementHostAsElement;
        THROW_IF_FAILED(bodyElementHost.As(&bodyElementHostAsElement));
        ApplyMarginToXamlElement(hostConfig.Get(), bodyElementHostAsElement.Get());

        // Assign vertical alignment to the top so that on fixed height cards, the content
        // still renders at the top even if the content is shorter than the full card
        THROW_IF_FAILED(bodyElementHostAsElement->put_VerticalAlignment(VerticalAlignment_Top));

        XamlHelpers::AppendXamlElementToPanel(bodyElementHost.Get(), outerPanelAsPanel.Get());
        THROW_IF_FAILED(bodyElementHost.CopyTo(bodyElementContainer));
        
        XamlHelpers::AppendXamlElementToPanel(outerPanelAsPanel.Get(), rootAsPanel.Get());
        THROW_IF_FAILED(outerPanelAsPanel.CopyTo(outerElementContainer));

        if (m_fixedDimensions)
        {
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            THROW_IF_FAILED(rootElement.As(&rootAsFrameworkElement));
            rootAsFrameworkElement->put_Width(m_fixedWidth);
            rootAsFrameworkElement->put_Height(m_fixedHeight);
            rootAsFrameworkElement->put_MaxHeight(m_fixedHeight);
        }
        
        ComPtr<IUIElement> rootAsUIElement;
        THROW_IF_FAILED(rootElement.As(&rootAsUIElement));
        return rootAsUIElement;
    }

    _Use_decl_annotations_
    void XamlBuilder::ApplyBackgroundToRoot(
        ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
        ABI::Windows::Foundation::IUriRuntimeClass* url,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs)
    {
        // In order to reuse the image creation code paths, we simply create an adaptive card
        // image element and then build that into xaml and apply to the root.
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));
        adaptiveImage->put_Url(url);

        ComPtr<IAdaptiveCardElement> adaptiveCardElement;
        THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
        ComPtr<IUIElement> backgroundImage;
        BuildImage(adaptiveCardElement.Get(), renderContext, renderArgs, &backgroundImage);
        XamlHelpers::AppendXamlElementToPanel(backgroundImage.Get(), rootPanel);

        // All background images should be stretched to fill the whole card.
        ComPtr<IImage> xamlImage;
        THROW_IF_FAILED(backgroundImage.As(&xamlImage));
        THROW_IF_FAILED(xamlImage->put_Stretch(Stretch::Stretch_UniformToFill));

        // The overlay applied to the background image is determined by a resouce, so create
        // the overlay if that resources exists
        ComPtr<IResourceDictionary> resourceDictionary;
        THROW_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
        ComPtr<IBrush> backgroundOverlayBrush;
        if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IBrush>(resourceDictionary.Get(), c_BackgroundImageOverlayBrushKey, &backgroundOverlayBrush)))
        {
            ComPtr<IShape> overlayRectangle = XamlHelpers::CreateXamlClass<IShape>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Rectangle));
            THROW_IF_FAILED(overlayRectangle->put_Fill(backgroundOverlayBrush.Get()));

            ComPtr<IUIElement> overlayRectangleAsUIElement;
            THROW_IF_FAILED(overlayRectangle.As(&overlayRectangleAsUIElement));
            XamlHelpers::AppendXamlElementToPanel(overlayRectangle.Get(), rootPanel);
        }
    }

    _Use_decl_annotations_
    template<typename T>
    void XamlBuilder::SetImageSource(
        T* destination,
        IImageSource* imageSource)
    {
        THROW_IF_FAILED(destination->put_Source(imageSource));
    };

    _Use_decl_annotations_
    template<>
    void XamlBuilder::SetImageSource<IEllipse>(
        IEllipse* destination,
        IImageSource* imageSource)
    {
        ComPtr<IImageBrush> imageBrush = XamlHelpers::CreateXamlClass<IImageBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_ImageBrush));
        THROW_IF_FAILED(imageBrush->put_ImageSource(imageSource));

        ComPtr<ITileBrush> tileBrush;
        THROW_IF_FAILED(imageBrush.As(&tileBrush));
        THROW_IF_FAILED(tileBrush->put_Stretch(Stretch_UniformToFill));

        ComPtr<IBrush> brush;
        THROW_IF_FAILED(imageBrush.As(&brush));

        ComPtr<IShape> ellipseAsShape;
        ComPtr<IEllipse> ellipse(destination);
        THROW_IF_FAILED(ellipse.As(&ellipseAsShape));
        THROW_IF_FAILED(ellipseAsShape->put_Fill(brush.Get()));
    };

    _Use_decl_annotations_
    template<typename T>
    void XamlBuilder::SetImageOnUIElement(
        _In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUri,
        T* uiElement,
        IAdaptiveCardResourceResolvers* resolvers)
    {
        // Get the image url scheme
        HString schemeName;
        THROW_IF_FAILED(imageUri->get_SchemeName(schemeName.GetAddressOf()));

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
                ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));

                if ((m_enableXamlImageHandling) || (m_listeners.size() == 0))
                {
                    m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
                }

                THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_None));
                ComPtr<IBitmapSource> bitmapSource;
                bitmapImage.As(&bitmapSource);

                // Create the arguments to pass to the resolver
                ComPtr<IAdaptiveCardGetResourceStreamArgs> args;
                THROW_IF_FAILED(MakeAndInitialize<AdaptiveCardGetResourceStreamArgs>(&args, imageUri));

                // And call the resolver to get the image stream
                ComPtr<IAsyncOperation<IRandomAccessStream*>> getResourceStreamOperation;
                THROW_IF_FAILED(resolver->GetResourceStreamAsync(args.Get(), &getResourceStreamOperation));

                ComPtr<T> strongImageControl(uiElement);
                ComPtr<XamlBuilder> strongThis(this);
                THROW_IF_FAILED(getResourceStreamOperation->put_Completed(Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationCompletedHandler<IRandomAccessStream*>>>
                    ([strongThis, this, bitmapSource, strongImageControl, bitmapImage](IAsyncOperation<IRandomAccessStream*>* operation, AsyncStatus status) -> HRESULT
                {
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

                        SetImageSource(strongImageControl.Get(), imageSource.Get());
                        return S_OK;
                    }
                    else
                    {
                        m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                        return S_OK;
                    }
                }).Get()));

                return;
            }
        }

        // Otherwise, no resolver...
        if ((m_enableXamlImageHandling) || (m_listeners.size() == 0))
        {
            // If we've been explicitly told to let Xaml handle the image loading, or there are
            // no listeners waiting on the image load callbacks, use Xaml to load the images
            ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
            THROW_IF_FAILED(bitmapImage->put_UriSource(imageUri));

            ComPtr<IImageSource> bitmapImageSource;
            THROW_IF_FAILED(bitmapImage.As(&bitmapImageSource));
            SetImageSource(uiElement, bitmapImageSource.Get());
        }
        else
        {
            PopulateImageFromUrlAsync(imageUri, uiElement);
        }
    }

    _Use_decl_annotations_
    template<typename T>
    void XamlBuilder::PopulateImageFromUrlAsync(IUriRuntimeClass* imageUri, T* imageControl)
    {
        // Create the HttpClient to load the image stream
        ComPtr<IHttpBaseProtocolFilter> httpBaseProtocolFilter =
            XamlHelpers::CreateXamlClass<IHttpBaseProtocolFilter>(HStringReference(RuntimeClass_Windows_Web_Http_Filters_HttpBaseProtocolFilter));
        THROW_IF_FAILED(httpBaseProtocolFilter->put_AllowUI(false));
        ComPtr<IHttpFilter> httpFilter;
        THROW_IF_FAILED(httpBaseProtocolFilter.As(&httpFilter));
        ComPtr<IHttpClient> httpClient;
        ComPtr<IHttpClientFactory> httpClientFactory;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Web_Http_HttpClient).Get(), httpClientFactory.ReleaseAndGetAddressOf()));
        THROW_IF_FAILED(httpClientFactory->Create(httpFilter.Get(), httpClient.ReleaseAndGetAddressOf()));

        // Create a BitmapImage to hold the image data.  We use BitmapImage in order to allow
        // the tracker to subscribe to the ImageLoaded/Failed events
        ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
        m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());
        THROW_IF_FAILED(bitmapImage->put_CreateOptions(BitmapCreateOptions::BitmapCreateOptions_None));
        ComPtr<IBitmapSource> bitmapSource;
        bitmapImage.As(&bitmapSource);
        ComPtr<IAsyncOperationWithProgress<IInputStream*, HttpProgress>> getStreamOperation;
        THROW_IF_FAILED(httpClient->GetInputStreamAsync(imageUri, &getStreamOperation));

        ComPtr<T> strongImageControl(imageControl);
        ComPtr<XamlBuilder> strongThis(this);
        THROW_IF_FAILED(getStreamOperation->put_Completed(Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<IInputStream*, HttpProgress>>>
            ([strongThis, this, bitmapSource, strongImageControl, bitmapImage](IAsyncOperationWithProgress<IInputStream*, HttpProgress>* operation, AsyncStatus status) -> HRESULT
        {
            if (status == AsyncStatus::Completed)
            {
                // Load the image stream into an in memory random access stream, which is what
                // SetSource needs
                ComPtr<IInputStream> imageStream;
                RETURN_IF_FAILED(operation->GetResults(&imageStream));
                ComPtr<IRandomAccessStream> randomAccessStream =
                    XamlHelpers::CreateXamlClass<IRandomAccessStream>(HStringReference(RuntimeClass_Windows_Storage_Streams_InMemoryRandomAccessStream));
                ComPtr<IOutputStream> outputStream;
                RETURN_IF_FAILED(randomAccessStream.As(&outputStream));
                ComPtr<IAsyncOperationWithProgress<UINT64, UINT64>> copyStreamOperation;
                RETURN_IF_FAILED(m_randomAccessStreamStatics->CopyAsync(imageStream.Get(), outputStream.Get(), &copyStreamOperation));

                return copyStreamOperation->put_Completed(Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<UINT64, UINT64>>>
                    ([strongThis, this, bitmapSource, randomAccessStream, strongImageControl](IAsyncOperationWithProgress<UINT64, UINT64>* /*operation*/, AsyncStatus /*status*/) -> HRESULT
                {
                    randomAccessStream->Seek(0);
                    RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                    ComPtr<IImageSource> imageSource;
                    RETURN_IF_FAILED(bitmapSource.As(&imageSource));

                    SetImageSource(strongImageControl.Get(), imageSource.Get());
                    return S_OK;
                }).Get());
                m_copyStreamOperations.push_back(copyStreamOperation);
            }
            else
            {
                m_imageLoadTracker.MarkFailedLoadBitmapImage(bitmapImage.Get());
                return S_OK;
            }
        }).Get()));
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

    _Use_decl_annotations_
    void XamlBuilder::BuildPanelChildren(
        IVector<IAdaptiveCardElement*>* children,
        IPanel* parentPanel,
        ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
        ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
        std::function<void(IUIElement* child)> childCreatedCallback)
    {
        int currentElement = 0;
        unsigned int childrenSize;
        THROW_IF_FAILED(children->get_Size(&childrenSize));
        XamlHelpers::IterateOverVector<IAdaptiveCardElement>(children, [&](IAdaptiveCardElement* element)
        {
            HString elementType;
            THROW_IF_FAILED(element->get_ElementTypeString(elementType.GetAddressOf()));
            ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
            THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
            ComPtr<IAdaptiveElementRenderer> elementRenderer;
            THROW_IF_FAILED(elementRenderers->Get(elementType.Get(), &elementRenderer));
            if (elementRenderer != nullptr)
            {
                ComPtr<IAdaptiveHostConfig> hostConfig;
                THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
                // First element does not need a separator added
                if (currentElement++ > 0)
                {
                    bool needsSeparator;
                    UINT spacing;
                    UINT separatorThickness;
                    ABI::Windows::UI::Color separatorColor;
                    GetSeparationConfigForElement(element, hostConfig.Get(), &spacing, &separatorThickness, &separatorColor, &needsSeparator);
                    if (needsSeparator)
                    {
                        auto separator = CreateSeparator(renderContext, spacing, separatorThickness, separatorColor);
                        XamlHelpers::AppendXamlElementToPanel(separator.Get(), parentPanel);
                    }
                }
                ComPtr<IUIElement> newControl;
                elementRenderer->Render(element, renderContext, renderArgs, &newControl);
                XamlHelpers::AppendXamlElementToPanel(newControl.Get(), parentPanel);
                childCreatedCallback(newControl.Get());
            }
            else
            {
                std::wstring errorString = L"No Renderer found for type: ";
                errorString += elementType.GetRawBuffer(nullptr);
                renderContext->AddWarning(
                   ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                    HStringReference(errorString.c_str()).Get());
            }
        });
    }

    void XamlBuilder::BuildShowCard(
        AdaptiveCardRenderer* renderer,
        IAdaptiveShowCardActionConfig* showCardActionConfig,
        IAdaptiveActionElement* action,
        AdaptiveRenderContext* renderContext,
        IUIElement** uiShowCard)
    {
        ComPtr<IAdaptiveActionElement> localAction(action);
        ComPtr<AdaptiveRenderContext> localRenderContext(renderContext);
        ComPtr<IAdaptiveShowCardAction> showCardAction;
        THROW_IF_FAILED(localAction.As(&showCardAction));

        ABI::AdaptiveNamespace::ContainerStyle showCardConfigStyle;
        THROW_IF_FAILED(showCardActionConfig->get_Style(&showCardConfigStyle));

        ComPtr<IAdaptiveCard> showCard;
        THROW_IF_FAILED(showCardAction->get_Card(showCard.GetAddressOf()));

        ComPtr<IFrameworkElement> localUiShowCard;
        BuildXamlTreeFromAdaptiveCard(showCard.Get(), localUiShowCard.GetAddressOf(), renderer, localRenderContext.Get(), false, showCardConfigStyle);

        ComPtr<IGrid2> showCardGrid;
        THROW_IF_FAILED(localUiShowCard.As(&showCardGrid));

        // Set the padding
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        THROW_IF_FAILED(spacingConfig->get_Padding(&padding));

        ABI::AdaptiveNamespace::ActionMode showCardActionMode;
        THROW_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        // Set the top margin
        ComPtr<IFrameworkElement> showCardFrameworkElement;
        THROW_IF_FAILED(localUiShowCard.As(&showCardFrameworkElement));

        UINT32 inlineTopMargin;
        THROW_IF_FAILED(showCardActionConfig->get_InlineTopMargin(&inlineTopMargin));
        Thickness margin = { 0, (double)inlineTopMargin, 0, 0 };
        THROW_IF_FAILED(showCardFrameworkElement->put_Margin(margin));

        ComPtr<IUIElement> showCardUIElement;
        THROW_IF_FAILED(localUiShowCard.As(&showCardUIElement));

        // Set the visibility as Collapsed until the action is triggered
        THROW_IF_FAILED(showCardUIElement->put_Visibility(Visibility_Collapsed));

        *uiShowCard = showCardUIElement.Detach();
    }

    _Use_decl_annotations_
    void XamlBuilder::ArrangeButtonContent(
        IAdaptiveActionElement* action,
        IAdaptiveActionsConfig* actionsConfig,
        AdaptiveRenderContext* renderContext,
        ABI::AdaptiveNamespace::ContainerStyle containerStyle,
        ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
        IButton* button)
    {
        HString title;
        THROW_IF_FAILED(action->get_Title(title.GetAddressOf()));
        ComPtr<IUriRuntimeClass> iconUrl;
        THROW_IF_FAILED(action->get_IconUrl(iconUrl.GetAddressOf()));
        ComPtr<IButton> localButton(button);

        // Check if the button has an iconUrl
        if (iconUrl.Get())
        {
            ABI::AdaptiveNamespace::IconPlacement iconPlacement;
            THROW_IF_FAILED(actionsConfig->get_IconPlacement(&iconPlacement));

            // Define the alignment for the button contents
            ComPtr<IStackPanel> buttonContentsStackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
            if (iconPlacement == ABI::AdaptiveNamespace::IconPlacement::AboveTitle)
            {
                THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Vertical));
            }
            else
            {
                THROW_IF_FAILED(buttonContentsStackPanel->put_Orientation(Orientation::Orientation_Horizontal));
            }
            ComPtr<IPanel> buttonContentsPanel;
            THROW_IF_FAILED(buttonContentsStackPanel.As(&buttonContentsPanel));

            // Create image and add it to the button
            ComPtr<IAdaptiveImage> adaptiveImage;
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));
            adaptiveImage->put_Url(iconUrl.Get());
            adaptiveImage->put_HorizontalAlignment(HAlignment_Center);

            ComPtr<IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
            ComPtr<AdaptiveRenderArgs> childRenderArgs;
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&childRenderArgs, containerStyle, buttonContentsStackPanel.Get()));

            ComPtr<IUIElement> buttonIcon;
            BuildImage(adaptiveCardElement.Get(), renderContext, childRenderArgs.Get(), &buttonIcon);
            XamlHelpers::AppendXamlElementToPanel(buttonIcon.Get(), buttonContentsPanel.Get()); // Add image to stack panel
            ComPtr<IFrameworkElement> buttonIconAsFrameworkElement;
            THROW_IF_FAILED(buttonIcon.As(&buttonIconAsFrameworkElement));

            // Just add spacing when the icon must be located at the left of the title
            if (iconPlacement == ABI::AdaptiveNamespace::IconPlacement::LeftOfTitle)
            {
                UINT spacingSize;
                THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig, ABI::AdaptiveNamespace::Spacing::Default, &spacingSize));

                ABI::Windows::UI::Color color = {0};
                auto separator = CreateSeparator(renderContext, spacingSize, spacingSize, color, false);
                XamlHelpers::AppendXamlElementToPanel(separator.Get(), buttonContentsPanel.Get());
            }

            // Add text to button
            ComPtr<ITextBlock> buttonText = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            THROW_IF_FAILED(buttonText->put_Text(title.Get()));
            THROW_IF_FAILED(buttonText->put_TextAlignment(TextAlignment::TextAlignment_Center));
            XamlHelpers::AppendXamlElementToPanel(buttonText.Get(), buttonContentsPanel.Get()); // Add text to stack panel

                                                                                                // Add event to the image to resize itself when the textblock is rendered
            ComPtr<IImage> buttonIconAsImage;
            THROW_IF_FAILED(buttonIcon.As(&buttonIconAsImage));

            EventRegistrationToken eventToken;
            THROW_IF_FAILED(buttonIconAsImage->add_ImageOpened(Callback<IRoutedEventHandler>(
                [ buttonIconAsFrameworkElement, buttonText ](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT
            {
                return SetImageSizeAsTextBlockSize(buttonIconAsFrameworkElement.Get(), buttonText.Get());
            }).Get(), &eventToken));

            ComPtr<IContentControl> buttonContentControl;
            THROW_IF_FAILED(localButton.As(&buttonContentControl));
            THROW_IF_FAILED(buttonContentControl->put_Content(buttonContentsPanel.Get()));
        }
        else
        {
            XamlHelpers::SetContent(localButton.Get(), title.Get());
        }
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildActions(
        IVector<IAdaptiveActionElement*>* children,
        AdaptiveCardRenderer* renderer,
        IPanel* parentPanel,
        IPanel* bodyPanel,
        bool insertSeparator,
        AdaptiveRenderContext* renderContext,
        ABI::AdaptiveNamespace::ContainerStyle containerStyle)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        THROW_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));
        ComPtr<AdaptiveRenderContext> strongRenderContext(renderContext);
        // Create a separator between the body and the actions
        if (insertSeparator)
        {
            ABI::AdaptiveNamespace::Spacing spacing;
            THROW_IF_FAILED(actionsConfig->get_Spacing(&spacing)); 

            UINT spacingSize;
            THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), spacing, &spacingSize));

            ABI::Windows::UI::Color color = { 0 };
            auto separator = CreateSeparator(renderContext, spacingSize, 0, color);
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), bodyPanel);
        }

        ABI::AdaptiveNamespace::ActionAlignment actionAlignment;
        THROW_IF_FAILED(actionsConfig->get_ActionAlignment(&actionAlignment));

        ABI::AdaptiveNamespace::ActionsOrientation actionsOrientation;
        THROW_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        // Declare the panel that will host the buttons
        ComPtr<IPanel> actionsPanel;
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;

        if (actionAlignment == ABI::AdaptiveNamespace::ActionAlignment::Stretch &&
            actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
        {
            // If stretch alignment and orientation is horizontal, we use a grid with equal column widths to achieve stretch behavior.
            // For vertical orientation, we'll still just use a stack panel since the concept of stretching buttons height isn't really
            // valid, especially when the height of cards are typically dynamic.
            ComPtr<IGrid> actionsGrid = XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            THROW_IF_FAILED(actionsGrid->get_ColumnDefinitions(&columnDefinitions));
            THROW_IF_FAILED(actionsGrid.As(&actionsPanel));
        }

        else
        {
            // Create a stack panel for the action buttons
            ComPtr<IStackPanel> actionStackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

            auto uiOrientation = (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal) ?
                Orientation::Orientation_Horizontal :
                Orientation::Orientation_Vertical;

            THROW_IF_FAILED(actionStackPanel->put_Orientation(uiOrientation));

            ComPtr<IFrameworkElement> actionsFrameworkElement;
            THROW_IF_FAILED(actionStackPanel.As(&actionsFrameworkElement));

            switch (actionAlignment)
            {
            case ABI::AdaptiveNamespace::ActionAlignment::Center:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Center));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Left:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Right:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveNamespace::ActionAlignment::Stretch:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
                break;
            }

            // Add the action buttons to the stack panel
            THROW_IF_FAILED(actionStackPanel.As(&actionsPanel));
        }

        UINT32 buttonSpacing;
        THROW_IF_FAILED(actionsConfig->get_ButtonSpacing(&buttonSpacing));

        Thickness buttonMargin = { 0, 0, 0, 0 };
        if (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
        {
            buttonMargin.Left = buttonMargin.Right = buttonSpacing / 2;

            // Negate the spacing on the sides so the left and right buttons are flush on the side.
            // We do NOT remove the margin from the individual button itself, since that would cause
            // the equal columns stretch behavior to not have equal columns (since the first and last
            // button would be narrower without the same margins as its peers).
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            THROW_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            THROW_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({ buttonMargin.Left * -1, 0, buttonMargin.Right * -1, 0 }));
        }
        else
        {
            buttonMargin.Top = buttonMargin.Bottom = buttonSpacing / 2;

            // Negate the spacing on the top and bottom so the first and last buttons don't have extra padding
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            THROW_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            THROW_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({ 0, buttonMargin.Top * -1, 0, buttonMargin.Bottom * -1 }));
        }

        UINT32 maxActions;
        THROW_IF_FAILED(actionsConfig->get_MaxActions(&maxActions));

        ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
        THROW_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));

        ABI::AdaptiveNamespace::ActionMode showCardActionMode;
        THROW_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        UINT currentAction = 0;

        ComPtr<AdaptiveCardRenderer> strongRenderer(renderer);
        std::shared_ptr<std::vector<ComPtr<IUIElement>>> allShowCards = std::make_shared<std::vector<ComPtr<IUIElement>>>();
        ComPtr<IStackPanel> showCardsStackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));
        XamlHelpers::IterateOverVector<IAdaptiveActionElement>(children, [&](IAdaptiveActionElement* child)
        {
            if (currentAction < maxActions)
            {
                // Render a button for each action
                ComPtr<IAdaptiveActionElement> action(child);
                ComPtr<IButton> button = XamlHelpers::CreateXamlClass<IButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Button));

                ComPtr<IFrameworkElement> buttonFrameworkElement;
                THROW_IF_FAILED(button.As(&buttonFrameworkElement));

                THROW_IF_FAILED(buttonFrameworkElement->put_Margin(buttonMargin));

                if (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
                {
                    // For horizontal alignment, we always use stretch
                    THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Stretch));
                }
                else
                {
                    switch (actionAlignment)
                    {
                    case ABI::AdaptiveNamespace::ActionAlignment::Center:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Center));
                        break;
                    case ABI::AdaptiveNamespace::ActionAlignment::Left:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Left));
                        break;
                    case ABI::AdaptiveNamespace::ActionAlignment::Right:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Right));
                        break;
                    case ABI::AdaptiveNamespace::ActionAlignment::Stretch:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
                        break;
                    }
                }

                ArrangeButtonContent(action.Get(), actionsConfig.Get(), renderContext, containerStyle, hostConfig.Get(), button.Get());

                ABI::AdaptiveNamespace::ActionType actionType;
                THROW_IF_FAILED(action->get_ActionType(&actionType));

                // If this is a show card action and we're rendering the actions inline, render the card that will be shown
                ComPtr<IUIElement> uiShowCard;
                if (actionType == ABI::AdaptiveNamespace::ActionType::ShowCard && 
                    showCardActionMode == ABI::AdaptiveNamespace::ActionMode::Inline)
                {
                    BuildShowCard(strongRenderer.Get(), showCardActionConfig.Get(), action.Get(), strongRenderContext.Get(), uiShowCard.GetAddressOf());
                    allShowCards->push_back(uiShowCard);

                    ComPtr<IPanel> showCardsPanel;
                    THROW_IF_FAILED(showCardsStackPanel.As(&showCardsPanel));
                    XamlHelpers::AppendXamlElementToPanel(uiShowCard.Get(), showCardsPanel.Get());
                }
                
                // Add click handler
                ComPtr<IButtonBase> buttonBase;
                THROW_IF_FAILED(button.As(&buttonBase));
                ComPtr<IAdaptiveActionInvoker> actionInvoker;
                THROW_IF_FAILED(strongRenderContext->get_ActionInvoker(&actionInvoker));
                EventRegistrationToken clickToken;
                THROW_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>([action, actionType, showCardActionMode, uiShowCard, allShowCards, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT
                {
                    if (actionType == ABI::AdaptiveNamespace::ActionType::ShowCard &&
                        showCardActionMode != ABI::AdaptiveNamespace::ActionMode_Popup)
                    {
                        // Check if this show card is currently visible
                        Visibility currentVisibility;
                        THROW_IF_FAILED(uiShowCard->get_Visibility(&currentVisibility));

                        // Collapse all cards to make sure that no other show cards are visible
                        for (std::vector<ComPtr<IUIElement>>::iterator it = allShowCards->begin(); it != allShowCards->end(); ++it)
                        {
                            THROW_IF_FAILED((*it)->put_Visibility(Visibility_Collapsed));
                        }

                        // If the card had been collapsed before, show it now
                        if (currentVisibility == Visibility_Collapsed)
                        {
                            THROW_IF_FAILED(uiShowCard->put_Visibility(Visibility_Visible));
                        }
                    }
                    else
                    {
                        THROW_IF_FAILED(actionInvoker->SendActionEvent(action.Get()));
                    }

                    return S_OK;
                }).Get(), &clickToken));

                THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Action", buttonFrameworkElement.Get()));

                XamlHelpers::AppendXamlElementToPanel(button.Get(), actionsPanel.Get());

                if (columnDefinitions != nullptr)
                {
                    // If using the equal width columns, we'll add a column and assign the column
                    ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                    THROW_IF_FAILED(columnDefinition->put_Width({ 1.0, GridUnitType::GridUnitType_Star }));
                    THROW_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

                    gridStatics->SetColumn(buttonFrameworkElement.Get(), currentAction);
                }
            }
            else
            {
                renderContext->AddWarning(
                   ABI::AdaptiveNamespace::WarningStatusCode::MaxActionsExceeded,
                    HStringReference(L"Some actions were not rendered due to exceeding the maximum number of actions allowed").Get());
                return;
            }
            currentAction++;
        });

        ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
        THROW_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Actions", actionsPanelAsFrameworkElement.Get()));

        // Buttons go into body panel, show cards go into outer panel so they're not inside the padding
        XamlHelpers::AppendXamlElementToPanel(actionsPanel.Get(), bodyPanel);
        XamlHelpers::AppendXamlElementToPanel(showCardsStackPanel.Get(), parentPanel);
    }

    _Use_decl_annotations_
    void XamlBuilder::ApplyMarginToXamlElement(
        IAdaptiveHostConfig* hostConfig,
        IFrameworkElement* element)
    {
        ComPtr<IFrameworkElement> localElement(element);
        ComPtr<IAdaptiveSpacingConfig> spacingConfig;
        THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

        UINT32 padding;
        spacingConfig->get_Padding(&padding);
        Thickness margin = { (double)padding, (double)padding, (double)padding, (double)padding };

        THROW_IF_FAILED(localElement->put_Margin(margin));
    }

    _Use_decl_annotations_
    void XamlBuilder::GetSeparationConfigForElement(
        IAdaptiveCardElement* cardElement,
        IAdaptiveHostConfig* hostConfig,
        UINT* spacing,
        UINT* separatorThickness,
        ABI::Windows::UI::Color* separatorColor,
        bool * needsSeparator)
    {
        ABI::AdaptiveNamespace::Spacing elementSpacing;
        THROW_IF_FAILED(cardElement->get_Spacing(&elementSpacing));

        UINT localSpacing;
        THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig, elementSpacing, &localSpacing));

        boolean hasSeparator;
        THROW_IF_FAILED(cardElement->get_Separator(&hasSeparator));

        ABI::Windows::UI::Color localColor = { 0 };
        UINT localThickness = 0; 
        if (hasSeparator)
        {
            ComPtr<IAdaptiveSeparatorConfig> separatorConfig;
            THROW_IF_FAILED(hostConfig->get_Separator(&separatorConfig));

            THROW_IF_FAILED(separatorConfig->get_LineColor(&localColor));
            THROW_IF_FAILED(separatorConfig->get_LineThickness(&localThickness));
        }
        
        *needsSeparator = hasSeparator ||
            (elementSpacing != ABI::AdaptiveNamespace::Spacing::None);

        *spacing = localSpacing;
        *separatorThickness = localThickness;
        *separatorColor = localColor;
    }

    _Use_decl_annotations_
    ComPtr<IBrush> XamlBuilder::GetSolidColorBrush(_In_ ABI::Windows::UI::Color color)
    {
        ComPtr<ISolidColorBrush> solidColorBrush = XamlHelpers::CreateXamlClass<ISolidColorBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_SolidColorBrush));
        THROW_IF_FAILED(solidColorBrush->put_Color(color));
        ComPtr<IBrush> solidColorBrushAsBrush;
        THROW_IF_FAILED(solidColorBrush.As(&solidColorBrushAsBrush));
        return solidColorBrushAsBrush;
    }

    _Use_decl_annotations_
    void XamlBuilder::StyleXamlTextBlock(
        ABI::AdaptiveNamespace::TextSize size,
        ABI::AdaptiveNamespace::ForegroundColor color,
        ABI::AdaptiveNamespace::ContainerStyle containerStyle,
        bool isSubtle,
        bool wrap,
        UINT32 maxWidth,
        ABI::AdaptiveNamespace::TextWeight weight,
        ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock,
        IAdaptiveHostConfig* hostConfig)
    {
        ComPtr<ITextBlock> localTextBlock(xamlTextBlock);

        ABI::Windows::UI::Color fontColor;
        THROW_IF_FAILED(GetColorFromAdaptiveColor(hostConfig, color, containerStyle, isSubtle, &fontColor));

        ComPtr<IBrush> fontColorBrush = GetSolidColorBrush(fontColor);
        THROW_IF_FAILED(localTextBlock->put_Foreground(fontColorBrush.Get()));

        // Retrieve the Font Size from Host Options
        ComPtr<IAdaptiveFontSizesConfig> fontSizesConfig;
        THROW_IF_FAILED(hostConfig->get_FontSizes(&fontSizesConfig));
        UINT32 fontSize;
        switch (size)
        {
        case ABI::AdaptiveNamespace::TextSize::Small:
            THROW_IF_FAILED(fontSizesConfig->get_Small(&fontSize));
            break;
        case ABI::AdaptiveNamespace::TextSize::Medium:
            THROW_IF_FAILED(fontSizesConfig->get_Medium(&fontSize));
            break;
        case ABI::AdaptiveNamespace::TextSize::Large:
            THROW_IF_FAILED(fontSizesConfig->get_Large(&fontSize));
            break;
        case ABI::AdaptiveNamespace::TextSize::ExtraLarge:
            THROW_IF_FAILED(fontSizesConfig->get_ExtraLarge(&fontSize));
            break;
        case ABI::AdaptiveNamespace::TextSize::Default:
        default:
            THROW_IF_FAILED(fontSizesConfig->get_Default(&fontSize));
            break;
        }
        THROW_IF_FAILED(localTextBlock->put_FontSize((double)fontSize));

        ComPtr<IAdaptiveFontWeightsConfig> fontWeightsConfig;
        THROW_IF_FAILED(hostConfig->get_FontWeights(&fontWeightsConfig));

        ABI::Windows::UI::Text::FontWeight xamlFontWeight;
        switch (weight)
        {
        case ABI::AdaptiveNamespace::TextWeight::Lighter:
            THROW_IF_FAILED(fontWeightsConfig->get_Lighter(&xamlFontWeight.Weight));
            break;
        case ABI::AdaptiveNamespace::TextWeight::Bolder:
            THROW_IF_FAILED(fontWeightsConfig->get_Bolder(&xamlFontWeight.Weight));
            break;
        case ABI::AdaptiveNamespace::TextWeight::Default:
        default:
            THROW_IF_FAILED(fontWeightsConfig->get_Default(&xamlFontWeight.Weight));
            break;
        }

        THROW_IF_FAILED(localTextBlock->put_FontWeight(xamlFontWeight));

        // Apply the wrap value to the xaml element
        THROW_IF_FAILED(localTextBlock->put_TextWrapping(wrap ? TextWrapping::TextWrapping_WrapWholeWords : TextWrapping::TextWrapping_NoWrap));
        THROW_IF_FAILED(localTextBlock->put_TextTrimming(TextTrimming::TextTrimming_CharacterEllipsis));

        //Apply font family
        HString fontFamilyName;
        THROW_IF_FAILED(hostConfig->get_FontFamily(fontFamilyName.GetAddressOf()));

        ComPtr<IInspectable> inspectable;
        ComPtr<IFontFamily> fontFamily;
        ComPtr<IFontFamilyFactory> fontFamilyFactory;
        THROW_IF_FAILED(Windows::Foundation::GetActivationFactory(HStringReference(L"Windows.UI.Xaml.Media.FontFamily").Get(), &fontFamilyFactory));
        THROW_IF_FAILED(fontFamilyFactory->CreateInstanceWithName(fontFamilyName.Get(), nullptr, inspectable.ReleaseAndGetAddressOf(), &fontFamily));
        THROW_IF_FAILED(xamlTextBlock->put_FontFamily(fontFamily.Get()));

        ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
        THROW_IF_FAILED(localTextBlock.As(&textBlockAsFrameworkElement));
        THROW_IF_FAILED(textBlockAsFrameworkElement->put_MaxWidth(maxWidth));
    }

    _Use_decl_annotations_
    void XamlBuilder::StyleXamlTextBlock(
        IAdaptiveTextConfig* textConfig,
        ABI::AdaptiveNamespace::ContainerStyle containerStyle,
        ITextBlock* xamlTextBlock,
        IAdaptiveHostConfig* hostConfig)
    {
        ABI::AdaptiveNamespace::TextWeight textWeight;
        THROW_IF_FAILED(textConfig->get_Weight(&textWeight));
        ABI::AdaptiveNamespace::ForegroundColor textColor;
        THROW_IF_FAILED(textConfig->get_Color(&textColor));
        ABI::AdaptiveNamespace::TextSize textSize;
        THROW_IF_FAILED(textConfig->get_Size(&textSize));
        boolean isSubtle;
        THROW_IF_FAILED(textConfig->get_IsSubtle(&isSubtle));
        boolean wrap;
        THROW_IF_FAILED(textConfig->get_Wrap(&wrap));
        UINT32 maxWidth;
        THROW_IF_FAILED(textConfig->get_MaxWidth(&maxWidth));
        StyleXamlTextBlock(textSize, textColor, containerStyle, Boolify(isSubtle), wrap, maxWidth, textWeight, xamlTextBlock, hostConfig);
    }

    HRESULT SetTextOnXamlTextBlock(
        IAdaptiveRenderContext* renderContext,
        HSTRING textIn,
        HSTRING language,
        ITextBlock * textBlock)
    {
        DateTimeParser parser(HStringToUTF8(language));
        auto textWithParsedDates = parser.GenerateString(HStringToUTF8(textIn));

        MarkDownParser markdownParser(textWithParsedDates);
        auto htmlString = markdownParser.TransformToHtml();

        HString htmlHString;
        UTF8ToHString(htmlString, htmlHString.GetAddressOf());
        
        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocument> xmlDocument = XamlHelpers::CreateXamlClass<ABI::Windows::Data::Xml::Dom::IXmlDocument>(HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument));

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocumentIO> xmlDocumentIO;
        RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentIO));
        
        HRESULT hr = xmlDocumentIO->LoadXml(htmlHString.Get());
        if (FAILED(hr))
        {
            RETURN_IF_FAILED(textBlock->put_Text(textIn));
        }
        else
        {
            ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
            RETURN_IF_FAILED(textBlock->get_Inlines(inlines.GetAddressOf()));

            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> xmlDocumentAsNode;
            RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentAsNode));

            RETURN_IF_FAILED(AddHtmlInlines(renderContext, xmlDocumentAsNode.Get(), inlines.Get()));
        }

        return S_OK;
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildTextBlock(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IUIElement** textBlockControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
        THROW_IF_FAILED(cardElement.As(&adaptiveTextBlock));

        ComPtr<ITextBlock> xamlTextBlock = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

        // ITextBlock2 will be used later on
        ComPtr<ITextBlock2> xamlTextBlock2;
        THROW_IF_FAILED(xamlTextBlock.As(&xamlTextBlock2));

        HString text;
        THROW_IF_FAILED(adaptiveTextBlock->get_Text(text.GetAddressOf()));
        HString language;
        THROW_IF_FAILED(adaptiveTextBlock->get_Language(language.GetAddressOf()));
        THROW_IF_FAILED(SetTextOnXamlTextBlock(renderContext, text.Get(), language.Get(), xamlTextBlock.Get()));

        ABI::AdaptiveNamespace::ForegroundColor textColor;
        THROW_IF_FAILED(adaptiveTextBlock->get_Color(&textColor));
        boolean isSubtle = false;
        THROW_IF_FAILED(adaptiveTextBlock->get_IsSubtle(&isSubtle));

        // The subtle boolean is rendered by setting the opacity on the text block, so retrieve
        // that value from the resource dictionary and set the Opacity
        if (isSubtle)
        {
            ComPtr<IResourceDictionary> resourceDictionary;
            THROW_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
            ComPtr<IInspectable> subtleOpacityInspectable;
            if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IInspectable>(resourceDictionary.Get(), c_TextBlockSubtleOpacityKey, &subtleOpacityInspectable)))
            {
                ComPtr<IReference<double>> subtleOpacityReference;
                if (SUCCEEDED(subtleOpacityInspectable.As(&subtleOpacityReference)))
                {
                    double subtleOpacity;
                    subtleOpacityReference.Get()->get_Value(&subtleOpacity);

                    ComPtr<IUIElement> textBlockAsUIElement;
                    THROW_IF_FAILED(xamlTextBlock.As(&textBlockAsUIElement));
                    textBlockAsUIElement->put_Opacity(subtleOpacity);
                }
            }
        }

        // Set the maximum number of lines the text block should show
        UINT maxLines;
        THROW_IF_FAILED(adaptiveTextBlock->get_MaxLines(&maxLines));
        THROW_IF_FAILED(xamlTextBlock2->put_MaxLines(maxLines));

        ABI::AdaptiveNamespace::HAlignment adaptiveHorizontalAlignment;
        THROW_IF_FAILED(adaptiveTextBlock->get_HorizontalAlignment(&adaptiveHorizontalAlignment));

        // Set the horizontal alignment of the text
        switch (adaptiveHorizontalAlignment)
        {
            case ABI::AdaptiveNamespace::HAlignment::Left:
                THROW_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Left));
                break;
            case ABI::AdaptiveNamespace::HAlignment::Right:
                THROW_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Right));
                break;
            case ABI::AdaptiveNamespace::HAlignment::Center:
                THROW_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Center));
                break;
        }
        ABI::AdaptiveNamespace::TextSize textblockSize;
        THROW_IF_FAILED(adaptiveTextBlock->get_Size(&textblockSize));

        ABI::AdaptiveNamespace::TextWeight textWeight;
        THROW_IF_FAILED(adaptiveTextBlock->get_Weight(&textWeight));

        boolean shouldWrap = false;
        THROW_IF_FAILED(adaptiveTextBlock->get_Wrap(&shouldWrap));

        // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
        // are flush on the left edge of the card by enabling TrimSideBearings
        THROW_IF_FAILED(xamlTextBlock2->put_OpticalMarginAlignment(OpticalMarginAlignment_TrimSideBearings));

        //Style the TextBlock using Host config
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));
        StyleXamlTextBlock(textblockSize, textColor, containerStyle, isSubtle, shouldWrap, MAXUINT32, textWeight, xamlTextBlock.Get(), hostConfig.Get());

        ComPtr<IFrameworkElement> frameworkElement;
        THROW_IF_FAILED(xamlTextBlock.As(&frameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", frameworkElement.Get()));

        THROW_IF_FAILED(xamlTextBlock.CopyTo(textBlockControl));
    }

    _Use_decl_annotations_
    HRESULT XamlBuilder::SetAutoImageSize(IFrameworkElement* imageControl, IInspectable* parentElement, IBitmapSource* imageSource)
    {
        INT32 pixelHeight;
        RETURN_IF_FAILED(imageSource->get_PixelHeight(&pixelHeight));
        INT32 pixelWidth;
        RETURN_IF_FAILED(imageSource->get_PixelWidth(&pixelWidth));
        DOUBLE parentHeight;
        DOUBLE parentWidth;
        ComPtr<IInspectable> localParentElement(parentElement);
        ComPtr<IFrameworkElement> localElement(imageControl);
        ComPtr<IColumnDefinition> parentAsColumnDefinition;
        ComPtr<IFrameworkElement> parentAsFrameworkElement;
        if (SUCCEEDED(localParentElement.As(&parentAsColumnDefinition)))
        {
            RETURN_IF_FAILED(parentAsColumnDefinition->get_ActualWidth(&parentWidth));
            if (pixelWidth <= parentWidth)
            {
                RETURN_IF_FAILED(localElement->put_Width(pixelWidth));
            }
        }
        else if (SUCCEEDED(localParentElement.As(&parentAsFrameworkElement)))
        {
            RETURN_IF_FAILED(parentAsFrameworkElement->get_ActualWidth(&parentWidth));
            RETURN_IF_FAILED(parentAsFrameworkElement->get_ActualHeight(&parentHeight));
            if (pixelHeight <= parentHeight && pixelWidth <= parentWidth)
            {
                RETURN_IF_FAILED(localElement->put_Height(pixelHeight));
                RETURN_IF_FAILED(localElement->put_Width(pixelWidth));
            }
        }

        ComPtr<IUIElement> frameworkElementAsUIElement;
        RETURN_IF_FAILED(localElement.As(&frameworkElementAsUIElement));
        RETURN_IF_FAILED(frameworkElementAsUIElement->put_Visibility(Visibility::Visibility_Visible));
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlBuilder::SetImageSizeAsTextBlockSize(IFrameworkElement* imageControl, ITextBlock* textBlock)
    {
        ComPtr<ITextBlock> localTextBlock(textBlock);
        ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
        RETURN_IF_FAILED(localTextBlock.As(&textBlockAsFrameworkElement));
        DOUBLE textBlockHeight;
        RETURN_IF_FAILED(textBlockAsFrameworkElement->get_ActualHeight(&textBlockHeight));
        
        ComPtr<IFrameworkElement> localElement(imageControl);
        RETURN_IF_FAILED(localElement->put_Height(textBlockHeight));
        RETURN_IF_FAILED(localElement->put_Width(textBlockHeight));

        ComPtr<IUIElement> frameworkElementAsUIElement;
        RETURN_IF_FAILED(localElement.As(&frameworkElementAsUIElement));
        RETURN_IF_FAILED(frameworkElementAsUIElement->put_Visibility(Visibility::Visibility_Visible));
        return S_OK;
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildImage(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IUIElement** imageControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(cardElement.As(&adaptiveImage));

        ComPtr<IUriRuntimeClass> imageUri;
        THROW_IF_FAILED(adaptiveImage->get_Url(imageUri.GetAddressOf()));

        // Get the image's size and style
        ABI::AdaptiveNamespace::ImageSize size;
        THROW_IF_FAILED(adaptiveImage->get_Size(&size));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (size == ABI::AdaptiveNamespace::ImageSize::None)
        {
            ComPtr<IAdaptiveImageConfig> imageConfig;
            THROW_IF_FAILED(hostConfig->get_Image(&imageConfig));
            THROW_IF_FAILED(imageConfig->get_ImageSize(&size));
        }

        ABI::AdaptiveNamespace::ImageStyle imageStyle;
        THROW_IF_FAILED(adaptiveImage->get_Style(&imageStyle));
        ComPtr<IAdaptiveCardResourceResolvers> resourceResolvers;
        THROW_IF_FAILED(renderContext->get_ResourceResolvers(&resourceResolvers));

        ComPtr<IFrameworkElement> frameworkElement;
        if (imageStyle == ImageStyle_Person)
        {
            ComPtr<IEllipse> ellipse = XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));
            SetImageOnUIElement(imageUri.Get(), ellipse.Get(), resourceResolvers.Get());

            ComPtr<IShape> ellipseAsShape;
            THROW_IF_FAILED(ellipse.As(&ellipseAsShape));
            // Set Auto, None, and Stretch to Stretch_UniformToFill. An ellipse set to Stretch_Uniform ends up with size 0.
            if (size == ABI::AdaptiveNamespace::ImageSize::None ||
                size == ABI::AdaptiveNamespace::ImageSize::Stretch ||
                size == ABI::AdaptiveNamespace::ImageSize::Auto)
            {
                THROW_IF_FAILED(ellipseAsShape->put_Stretch(Stretch::Stretch_UniformToFill));
            }

            ComPtr<IInspectable> parentElement;
            THROW_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
            THROW_IF_FAILED(ellipse.As(&frameworkElement));

            // Check if the image source fits in the parent container, if so, set the framework element's size to match the original image.
            if (size == ABI::AdaptiveNamespace::ImageSize::Auto &&
                parentElement != nullptr &&
                m_enableXamlImageHandling)
            {
                ComPtr<IBrush> ellipseBrush;
                THROW_IF_FAILED(ellipseAsShape->get_Fill(&ellipseBrush));
                ComPtr<IImageBrush> brushAsImageBrush;
                THROW_IF_FAILED(ellipseBrush.As(&brushAsImageBrush));

                ComPtr<IUIElement> ellipseAsUIElement;
                THROW_IF_FAILED(ellipse.As(&ellipseAsUIElement));

                ComPtr<IImageSource> imageSource;
                THROW_IF_FAILED(brushAsImageBrush->get_ImageSource(&imageSource));
                ComPtr<IBitmapSource> imageSourceAsBitmap;
                THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));
                // Collapse the Ellipse while the image loads, so that resizing is not noticeable
                THROW_IF_FAILED(ellipseAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));
                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                EventRegistrationToken eventToken;
                THROW_IF_FAILED(brushAsImageBrush->add_ImageOpened(Callback<IRoutedEventHandler>(
                    [frameworkElement, parentElement, imageSourceAsBitmap](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT
                {
                    return SetAutoImageSize(frameworkElement.Get(), parentElement.Get(), imageSourceAsBitmap.Get());
                }).Get(), &eventToken));
            }
        }
        else
        {
            ComPtr<IImage> xamlImage = XamlHelpers::CreateXamlClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));
            SetImageOnUIElement(imageUri.Get(), xamlImage.Get(), resourceResolvers.Get());
            THROW_IF_FAILED(xamlImage.As(&frameworkElement));

            ComPtr<IInspectable> parentElement;
            THROW_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
            if (parentElement != nullptr &&
                size == ABI::AdaptiveNamespace::ImageSize::Auto &&
                m_enableXamlImageHandling)
            {
                ComPtr<IImageSource> imageSource;
                THROW_IF_FAILED(xamlImage->get_Source(&imageSource));
                ComPtr<IBitmapSource> imageSourceAsBitmap;
                THROW_IF_FAILED(imageSource.As(&imageSourceAsBitmap));

                ComPtr<IUIElement> imageAsUIElement;
                THROW_IF_FAILED(xamlImage.As(&imageAsUIElement));

                //Collapse the Image control while the image loads, so that resizing is not noticeable
                THROW_IF_FAILED(imageAsUIElement->put_Visibility(Visibility::Visibility_Collapsed));

                // Handle ImageOpened event so we can check the imageSource's size to determine if it fits in its parent
                EventRegistrationToken eventToken;
                THROW_IF_FAILED(xamlImage->add_ImageOpened(Callback<IRoutedEventHandler>(
                    [frameworkElement, parentElement, imageSourceAsBitmap](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT
                {
                    return SetAutoImageSize(frameworkElement.Get(), parentElement.Get(), imageSourceAsBitmap.Get());
                }).Get(), &eventToken));
            }
        }

        ComPtr<IAdaptiveImageSizesConfig> sizeOptions;
        THROW_IF_FAILED(hostConfig->get_ImageSizes(sizeOptions.GetAddressOf()));

        switch (size)
        {
            case ABI::AdaptiveNamespace::ImageSize::Small:
            {
                UINT32 imageSize;
                THROW_IF_FAILED(sizeOptions->get_Small(&imageSize));

                THROW_IF_FAILED(frameworkElement->put_Width(imageSize));
                THROW_IF_FAILED(frameworkElement->put_Height(imageSize));
                break;
            }

            case ABI::AdaptiveNamespace::ImageSize::Medium:
            {
                UINT32 imageSize;
                THROW_IF_FAILED(sizeOptions->get_Medium(&imageSize));

                THROW_IF_FAILED(frameworkElement->put_Width(imageSize));
                THROW_IF_FAILED(frameworkElement->put_Height(imageSize));
                break;
            }

            case ABI::AdaptiveNamespace::ImageSize::Large:
            {
                UINT32 imageSize;
                THROW_IF_FAILED(sizeOptions->get_Large(&imageSize));

                THROW_IF_FAILED(frameworkElement->put_Width(imageSize));
                THROW_IF_FAILED(frameworkElement->put_Height(imageSize));
                break;
            }
        }

        ABI::AdaptiveNamespace::HAlignment adaptiveHorizontalAlignment;
        THROW_IF_FAILED(adaptiveImage->get_HorizontalAlignment(&adaptiveHorizontalAlignment));

        switch (adaptiveHorizontalAlignment)
        {
            case ABI::AdaptiveNamespace::HAlignment::Left:
                THROW_IF_FAILED(frameworkElement->put_HorizontalAlignment(HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveNamespace::HAlignment::Right:
                THROW_IF_FAILED(frameworkElement->put_HorizontalAlignment(HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveNamespace::HAlignment::Center:
                THROW_IF_FAILED(frameworkElement->put_HorizontalAlignment(HorizontalAlignment_Center));
                break;
        }

        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Image", frameworkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        THROW_IF_FAILED(adaptiveImage->get_SelectAction(&selectAction));

        ComPtr<IUIElement> imageAsUIElement;
        THROW_IF_FAILED(frameworkElement.As(&imageAsUIElement));

        HandleSelectAction(adaptiveCardElement, selectAction.Get(), renderContext, imageAsUIElement.Get(), SupportsInteractivity(hostConfig.Get()), true, imageControl);
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildContainer(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IUIElement** containerControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveContainer> adaptiveContainer;
        THROW_IF_FAILED(cardElement.As(&adaptiveContainer));

        ComPtr<WholeItemsPanel> containerPanel;
        THROW_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&containerPanel));

        ComPtr<IFrameworkElement> containerPanelAsFrameWorkElement;
        THROW_IF_FAILED(containerPanel.As(&containerPanelAsFrameWorkElement));
        // Assign vertical alignment to the top so that on fixed height cards, the content
        // still renders at the top even if the content is shorter than the full card
        THROW_IF_FAILED(containerPanelAsFrameWorkElement->put_VerticalAlignment(VerticalAlignment_Top));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        THROW_IF_FAILED(adaptiveContainer->get_Style(&containerStyle));

        ABI::AdaptiveNamespace::ContainerStyle parentContainerStyle;
        THROW_IF_FAILED(renderArgs->get_ContainerStyle(&parentContainerStyle));

        bool hasExplicitContainerStyle = true;
        if (containerStyle == ABI::AdaptiveNamespace::ContainerStyle::None)
        {
            hasExplicitContainerStyle = false;
            containerStyle = parentContainerStyle;
        }
        ComPtr<IFrameworkElement> parentElement;
        THROW_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
        ComPtr<IAdaptiveRenderArgs> newRenderArgs;
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&newRenderArgs, containerStyle, parentElement.Get()));

        ComPtr<IPanel> containerPanelAsPanel;
        THROW_IF_FAILED(containerPanel.As(&containerPanelAsPanel));
        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        THROW_IF_FAILED(adaptiveContainer->get_Items(&childItems));
        BuildPanelChildren(childItems.Get(), containerPanelAsPanel.Get(), renderContext, newRenderArgs.Get(), [](IUIElement*) {});

        ComPtr<IBorder> containerBorder = XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        // If container style was explicitly assigned, apply background
        if (hasExplicitContainerStyle)
        {
            ABI::Windows::UI::Color backgroundColor;
            THROW_IF_FAILED(GetBackgroundColorFromStyle(containerStyle, hostConfig.Get(), &backgroundColor));
            ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
            THROW_IF_FAILED(containerBorder->put_Background(backgroundColorBrush.Get()));

            // If the container style doesn't match its parent, apply padding.
            if (containerStyle != parentContainerStyle)
            {
                ComPtr<IAdaptiveSpacingConfig> spacingConfig;
                THROW_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

                UINT32 padding;
                THROW_IF_FAILED(spacingConfig->get_Padding(&padding));
                DOUBLE paddingAsDouble = static_cast<DOUBLE>(padding);

                Thickness paddingThickness = {paddingAsDouble, paddingAsDouble, paddingAsDouble, paddingAsDouble};
                THROW_IF_FAILED(containerBorder->put_Padding(paddingThickness));
            }
        }

        ComPtr<IUIElement> containerPanelAsUIElement;
        THROW_IF_FAILED(containerPanel.As(&containerPanelAsUIElement));
        THROW_IF_FAILED(containerBorder->put_Child(containerPanelAsUIElement.Get()));

        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Container", containerPanelAsFrameWorkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        THROW_IF_FAILED(adaptiveContainer->get_SelectAction(&selectAction));

        ComPtr<IUIElement> containerBorderAsUIElement;
        THROW_IF_FAILED(containerBorder.As(&containerBorderAsUIElement));

        HandleSelectAction(adaptiveCardElement, selectAction.Get(), renderContext, containerBorderAsUIElement.Get(), SupportsInteractivity(hostConfig.Get()), true, containerControl);
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildColumn(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IUIElement** ColumnControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumn> adaptiveColumn;
        THROW_IF_FAILED(cardElement.As(&adaptiveColumn));

        ComPtr<WholeItemsPanel> columnPanel;
        THROW_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&columnPanel));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        THROW_IF_FAILED(adaptiveColumn->get_Style(&containerStyle));
        bool hasExplicitContainerStyle = true;
        if (containerStyle == ABI::AdaptiveNamespace::ContainerStyle::None)
        {
            hasExplicitContainerStyle = false;
            ABI::AdaptiveNamespace::ContainerStyle parentContainerStyle;
            THROW_IF_FAILED(renderArgs->get_ContainerStyle(&parentContainerStyle));
            containerStyle = parentContainerStyle;
        }

        ComPtr<IFrameworkElement> parentElement;
        THROW_IF_FAILED(renderArgs->get_ParentElement(&parentElement));
        ComPtr<IAdaptiveRenderArgs> newRenderArgs;
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&newRenderArgs, containerStyle, parentElement.Get()));

        // If container style was explicitly assigned, apply background
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ABI::Windows::UI::Color backgroundColor;
        if (hasExplicitContainerStyle && SUCCEEDED(GetBackgroundColorFromStyle(containerStyle, hostConfig.Get(), &backgroundColor)))
        {
            ComPtr<IPanel> columnAsPanel;
            THROW_IF_FAILED(columnPanel.As(&columnAsPanel));

            ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
            THROW_IF_FAILED(columnAsPanel->put_Background(backgroundColorBrush.Get()));
        }

        ComPtr<IPanel> columnPanelAsPanel;
        THROW_IF_FAILED(columnPanel.As(&columnPanelAsPanel));
        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        THROW_IF_FAILED(adaptiveColumn->get_Items(&childItems));
        BuildPanelChildren(childItems.Get(), columnPanelAsPanel.Get(), renderContext, newRenderArgs.Get(), [](IUIElement*) {});

        // Assign vertical alignment to the top so that on fixed height cards, the content
        // still renders at the top even if the content is shorter than the full card
        ComPtr<IFrameworkElement> columnPanelAsFrameworkElement;
        THROW_IF_FAILED(columnPanel.As(&columnPanelAsFrameworkElement));
        THROW_IF_FAILED(columnPanelAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));

        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Column", columnPanelAsFrameworkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        THROW_IF_FAILED(adaptiveColumn->get_SelectAction(&selectAction));

        ComPtr<IUIElement> columnAsUIElement;
        THROW_IF_FAILED(columnPanel.As(&columnAsUIElement));

        HandleSelectAction(adaptiveCardElement, selectAction.Get(), renderContext, columnAsUIElement.Get(), SupportsInteractivity(hostConfig.Get()), false, ColumnControl);
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildColumnSet(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IUIElement** columnSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumnSet> adaptiveColumnSet;
        THROW_IF_FAILED(cardElement.As(&adaptiveColumnSet));

        ComPtr<IGrid> xamlGrid = XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IVector<IAdaptiveColumn*>> columns;
        THROW_IF_FAILED(adaptiveColumnSet->get_Columns(&columns));
        int currentColumn = 0;
        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        ComPtr<IAdaptiveElementRenderer> columnRenderer;
        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Column").Get(), &columnRenderer));
        
        if (columnRenderer == nullptr)
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                HStringReference(L"No renderer found for type: Column").Get());
            *columnSetControl = nullptr;
            return;
        }

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        XamlHelpers::IterateOverVector<IAdaptiveColumn>(columns.Get(), [xamlGrid, gridStatics, &currentColumn, renderContext, renderArgs, columnRenderer, hostConfig](IAdaptiveColumn* column)
        {
            ComPtr<IAdaptiveCardElement> columnAsCardElement;
            ComPtr<IAdaptiveColumn> localColumn(column);
            THROW_IF_FAILED(localColumn.As(&columnAsCardElement));
            ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
            THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
            ComPtr<IPanel> gridAsPanel;
            THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));

            // If not the first column
            if (currentColumn > 0)
            {
                // Add Separator to the columnSet
                bool needsSeparator;
                UINT spacing;
                UINT separatorThickness;
                ABI::Windows::UI::Color separatorColor;
                GetSeparationConfigForElement(columnAsCardElement.Get(), hostConfig.Get(), &spacing, &separatorThickness, &separatorColor, &needsSeparator);

                if (needsSeparator)
                {
                    //Create a new ColumnDefinition for the separator
                    ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                    THROW_IF_FAILED(separatorColumnDefinition->put_Width({ 1.0, GridUnitType::GridUnitType_Auto }));
                    THROW_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

                    auto separator = CreateSeparator(renderContext, spacing, separatorThickness, separatorColor, false);
                    ComPtr<IFrameworkElement> separatorAsFrameworkElement;
                    THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));
                    gridStatics->SetColumn(separatorAsFrameworkElement.Get(), currentColumn++);
                    XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());
                }
            }

            // Determine if the column is auto, stretch, or percentage width, and set the column width appropriately
            ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));

            HString adaptiveColumnWidth;
            THROW_IF_FAILED(column->get_Width(adaptiveColumnWidth.GetAddressOf()));

            INT32 isStretchResult;
            THROW_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"stretch").Get(), &isStretchResult));

            INT32 isAutoResult;
            THROW_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"auto").Get(), &isAutoResult));

            double widthAsDouble = _wtof(adaptiveColumnWidth.GetRawBuffer(nullptr));

            GridLength columnWidth;
            if (isAutoResult == 0)
            {
                // If auto specified, use auto width
                columnWidth.GridUnitType = GridUnitType::GridUnitType_Auto;
                columnWidth.Value = 0;
            }
            else if (isStretchResult == 0 || !adaptiveColumnWidth.IsValid() || (widthAsDouble <= 0))
            {
                // If stretch specified, or column size invalid or set to non-positive, use stretch with default of 1
                columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
                columnWidth.Value = 1;
            }
            else
            {
                // If user specified specific valid size, use that star size
                columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
                columnWidth.Value = _wtof(adaptiveColumnWidth.GetRawBuffer(nullptr));
            }

            THROW_IF_FAILED(columnDefinition->put_Width(columnWidth));
            THROW_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

            ComPtr<IAdaptiveRenderArgs> columnRenderArgs;
            ABI::AdaptiveNamespace::ContainerStyle style;
            THROW_IF_FAILED(renderArgs->get_ContainerStyle(&style));
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&columnRenderArgs, style, columnDefinition.Get()));

            // Build the Column
            ComPtr<IUIElement> xamlColumn;
            columnRenderer->Render(columnAsCardElement.Get(), renderContext, columnRenderArgs.Get(), &xamlColumn);

            // Mark the column container with the current column
            ComPtr<IFrameworkElement> columnAsFrameworkElement;
            THROW_IF_FAILED(xamlColumn.As(&columnAsFrameworkElement));
            gridStatics->SetColumn(columnAsFrameworkElement.Get(), currentColumn++);

            // Finally add the column container to the grid
            XamlHelpers::AppendXamlElementToPanel(xamlColumn.Get(), gridAsPanel.Get());
        });

        ComPtr<IFrameworkElement> columnSetAsFrameworkElement;
        THROW_IF_FAILED(xamlGrid.As(&columnSetAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.ColumnSet", columnSetAsFrameworkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        THROW_IF_FAILED(adaptiveColumnSet->get_SelectAction(&selectAction));

        ComPtr<IUIElement> gridAsUIElement;
        THROW_IF_FAILED(xamlGrid.As(&gridAsUIElement));

        HandleSelectAction(adaptiveCardElement, selectAction.Get(), renderContext, gridAsUIElement.Get(), SupportsInteractivity(hostConfig.Get()), true, columnSetControl);
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildFactSet(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IUIElement** factSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveFactSet> adaptiveFactSet;

        THROW_IF_FAILED(cardElement.As(&adaptiveFactSet));

        ComPtr<IGrid> xamlGrid = XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IColumnDefinition> titleColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        ComPtr<IColumnDefinition> valueColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        GridLength factSetGridLength = { 0, GridUnitType::GridUnitType_Auto };

        THROW_IF_FAILED(titleColumn->put_Width(factSetGridLength));
        THROW_IF_FAILED(valueColumn->put_Width(factSetGridLength));
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
        THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
        THROW_IF_FAILED(columnDefinitions->Append(titleColumn.Get()));
        THROW_IF_FAILED(columnDefinitions->Append(valueColumn.Get()));

        ComPtr<IVector<IAdaptiveFact*>> facts;
        THROW_IF_FAILED(adaptiveFactSet->get_Facts(&facts));
        int currentFact = 0;
        XamlHelpers::IterateOverVector<IAdaptiveFact>(facts.Get(), [xamlGrid, gridStatics, factSetGridLength, &currentFact, renderContext, renderArgs](IAdaptiveFact* fact)
        {
            ComPtr<IRowDefinition> factRow = XamlHelpers::CreateXamlClass<IRowDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
            THROW_IF_FAILED(factRow->put_Height(factSetGridLength));

            ComPtr<IVector<RowDefinition*>> rowDefinitions;
            THROW_IF_FAILED(xamlGrid->get_RowDefinitions(&rowDefinitions));
            THROW_IF_FAILED(rowDefinitions->Append(factRow.Get()));

            ComPtr<IAdaptiveFact> localFact(fact);
            ComPtr<IAdaptiveHostConfig> hostConfig;
            THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
            ComPtr<IAdaptiveFactSetConfig> factSetConfig;
            THROW_IF_FAILED(hostConfig->get_FactSet(&factSetConfig));

            // Create the title xaml textblock and style it from Host options
            ComPtr<ITextBlock> titleTextBlock = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            HString factTitle;
            THROW_IF_FAILED(localFact->get_Title(factTitle.GetAddressOf()));
            THROW_IF_FAILED(titleTextBlock->put_Text(factTitle.Get()));
            ComPtr<IAdaptiveTextConfig> titleTextConfig;
            THROW_IF_FAILED(factSetConfig->get_Title(&titleTextConfig));

            ABI::AdaptiveNamespace::ContainerStyle containerStyle;
            THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));
            StyleXamlTextBlock(titleTextConfig.Get(), containerStyle, titleTextBlock.Get(), hostConfig.Get());

            // Create the value xaml textblock and style it from Host options
            ComPtr<ITextBlock> valueTextBlock = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            HString factValue;
            THROW_IF_FAILED(localFact->get_Value(factValue.GetAddressOf()));
            THROW_IF_FAILED(valueTextBlock->put_Text(factValue.Get()));
            ComPtr<IAdaptiveTextConfig> valueTextConfig;
            THROW_IF_FAILED(factSetConfig->get_Value(&valueTextConfig));
            StyleXamlTextBlock(valueTextConfig.Get(), containerStyle, valueTextBlock.Get(), hostConfig.Get());

            // Mark the column container with the current column
            ComPtr<IFrameworkElement> titleTextBlockAsFrameWorkElement;
            THROW_IF_FAILED(titleTextBlock.As(&titleTextBlockAsFrameWorkElement));
            ComPtr<IFrameworkElement> valueTextBlockAsFrameWorkElement;
            THROW_IF_FAILED(valueTextBlock.As(&valueTextBlockAsFrameWorkElement));

            UINT32 spacing;
            THROW_IF_FAILED(factSetConfig->get_Spacing(&spacing));
            //Add spacing from hostconfig to right margin of title.
            titleTextBlockAsFrameWorkElement->put_Margin({ 0, 0, (double)spacing, 0 });

            THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Fact.Title", titleTextBlockAsFrameWorkElement.Get()));
            THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Fact.Value", valueTextBlockAsFrameWorkElement.Get()));

            THROW_IF_FAILED(gridStatics->SetColumn(titleTextBlockAsFrameWorkElement.Get(), 0));
            THROW_IF_FAILED(gridStatics->SetRow(titleTextBlockAsFrameWorkElement.Get(), currentFact));

            THROW_IF_FAILED(gridStatics->SetColumn(valueTextBlockAsFrameWorkElement.Get(), 1));
            THROW_IF_FAILED(gridStatics->SetRow(valueTextBlockAsFrameWorkElement.Get(), currentFact));

            // Finally add the column container to the grid, and increment the column count
            ComPtr<IPanel> gridAsPanel;
            THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));
            ComPtr<IUIElement> titleUIElement;
            THROW_IF_FAILED(titleTextBlockAsFrameWorkElement.As(&titleUIElement));
            ComPtr<IUIElement> valueUIElement;
            THROW_IF_FAILED(valueTextBlockAsFrameWorkElement.As(&valueUIElement));

            XamlHelpers::AppendXamlElementToPanel(titleUIElement.Get(), gridAsPanel.Get());
            XamlHelpers::AppendXamlElementToPanel(valueUIElement.Get(), gridAsPanel.Get());
            ++currentFact;
        });

        ComPtr<IFrameworkElement> factSetAsFrameworkElement;
        THROW_IF_FAILED(xamlGrid.As(&factSetAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.FactSet", factSetAsFrameworkElement.Get()));

        THROW_IF_FAILED(xamlGrid.CopyTo(factSetControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildImageSet(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* renderArgs,
        IUIElement** imageSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImageSet> adaptiveImageSet;
        THROW_IF_FAILED(cardElement.As(&adaptiveImageSet));

        ComPtr<IVariableSizedWrapGrid> xamlGrid = XamlHelpers::CreateXamlClass<IVariableSizedWrapGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_VariableSizedWrapGrid));

        THROW_IF_FAILED(xamlGrid->put_Orientation(Orientation_Horizontal));

        ComPtr<IVector<IAdaptiveImage*>> images;
        THROW_IF_FAILED(adaptiveImageSet->get_Images(&images));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveImageSetConfig> imageSetConfig;
        THROW_IF_FAILED(hostConfig->get_ImageSet(&imageSetConfig));

        ABI::AdaptiveNamespace::ImageSize imageSize;
        THROW_IF_FAILED(adaptiveImageSet->get_ImageSize(&imageSize));

        if (imageSize == ABI::AdaptiveNamespace::ImageSize::None)
        {
            THROW_IF_FAILED(imageSetConfig->get_ImageSize(&imageSize));
        }

        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        ComPtr<IAdaptiveElementRenderer> imageRenderer;
        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &imageRenderer));
        if (imageRenderer != nullptr)
        {
            ABI::AdaptiveNamespace::ContainerStyle containerStyle;
            THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

            ComPtr<AdaptiveRenderArgs> childRenderArgs;
            THROW_IF_FAILED(MakeAndInitialize<AdaptiveRenderArgs>(&childRenderArgs, containerStyle, xamlGrid.Get()));

            XamlHelpers::IterateOverVector<IAdaptiveImage>(images.Get(), [imageSize, xamlGrid, renderContext, childRenderArgs, imageRenderer, imageSetConfig](IAdaptiveImage* adaptiveImage)
            {
                ComPtr<IUIElement> uiImage;
                ComPtr<IAdaptiveImage> localAdaptiveImage(adaptiveImage);
                THROW_IF_FAILED(localAdaptiveImage->put_Size(imageSize));

                ComPtr<IAdaptiveCardElement> adaptiveElementImage;
                localAdaptiveImage.As(&adaptiveElementImage);
                THROW_IF_FAILED(imageRenderer->Render(adaptiveElementImage.Get(), renderContext, childRenderArgs.Get(), &uiImage));

                ComPtr<IFrameworkElement> imageAsFrameworkElement;
                THROW_IF_FAILED(uiImage.As(&imageAsFrameworkElement));

                UINT32 maxImageHeight;
                THROW_IF_FAILED(imageSetConfig->get_MaxImageHeight(&maxImageHeight));
                THROW_IF_FAILED(imageAsFrameworkElement->put_MaxHeight(maxImageHeight));

                ComPtr<IPanel> gridAsPanel;
                THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));

                XamlHelpers::AppendXamlElementToPanel(uiImage.Get(), gridAsPanel.Get());
            });
        }
        else
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                HStringReference(L"No renderer found for type: Image").Get());
            *imageSetControl = nullptr;
            return;
        }

        ComPtr<IFrameworkElement> imageSetAsFrameworkElement;
        THROW_IF_FAILED(xamlGrid.As(&imageSetAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.ImageSet", imageSetAsFrameworkElement.Get()));

        THROW_IF_FAILED(xamlGrid.CopyTo(imageSetControl));
    }

    std::vector<std::string> GetChoiceSetValueVector(
        IAdaptiveChoiceSetInput* adaptiveChoiceSetInput)
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

    bool IsChoiceSelected(
        std::vector<std::string> selectedValues,
        IAdaptiveChoiceInput* choice)
    {
        HString value;
        THROW_IF_FAILED(choice->get_Value(value.GetAddressOf()));
        std::string stdValue = HStringToUTF8(value.Get());
        return std::find(selectedValues.begin(), selectedValues.end(), stdValue) != selectedValues.end();
    }

    void XamlBuilder::BuildCompactChoiceSetInput(
        IAdaptiveRenderContext* renderContext,
        IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
        IUIElement** choiceInputSet)
    {
        ComPtr<IComboBox> comboBox = XamlHelpers::CreateXamlClass<IComboBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBox));

        // Set HorizontalAlignment to Stretch (defaults to Left for combo boxes)
        ComPtr<IFrameworkElement> comboBoxAsFrameworkElement;
        THROW_IF_FAILED(comboBox.As(&comboBoxAsFrameworkElement));
        THROW_IF_FAILED(comboBoxAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));

        ComPtr<IItemsControl> itemsControl;
        THROW_IF_FAILED(comboBox.As(&itemsControl));

        ComPtr<IObservableVector<IInspectable*>> items;
        THROW_IF_FAILED(itemsControl->get_Items(items.GetAddressOf()));

        ComPtr<IVector<IInspectable*>> itemsVector;
        THROW_IF_FAILED(items.As(&itemsVector));

        ComPtr<IVector<IAdaptiveChoiceInput*>> choices;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        int currentIndex = 0;
        int selectedIndex = -1;
        XamlHelpers::IterateOverVector<IAdaptiveChoiceInput>(choices.Get(), [&currentIndex, &selectedIndex, itemsVector, values](IAdaptiveChoiceInput* adaptiveChoiceInput)
        {
            HString title;
            THROW_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));

            ComPtr<IComboBoxItem> comboBoxItem = XamlHelpers::CreateXamlClass<IComboBoxItem>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBoxItem));

            XamlHelpers::SetContent(comboBoxItem.Get(), title.Get());

            if (IsChoiceSelected(values, adaptiveChoiceInput))
            {
                selectedIndex = currentIndex;
            }

            ComPtr<IInspectable> inspectable;
            THROW_IF_FAILED(comboBoxItem.As(&inspectable));

            THROW_IF_FAILED(itemsVector->Append(inspectable.Get()));
            currentIndex++;
        });

        ComPtr<ISelector> selector;
        THROW_IF_FAILED(comboBox.As(&selector));
        THROW_IF_FAILED(selector->put_SelectedIndex(selectedIndex));

        ComPtr<IUIElement> comboBoxAsUIElement;
        THROW_IF_FAILED(comboBox.As(&comboBoxAsUIElement));
        THROW_IF_FAILED(AddHandledTappedEvent(comboBoxAsUIElement.Get()));

        SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.ChoiceSet.Compact", comboBoxAsFrameworkElement.Get());

        THROW_IF_FAILED(comboBoxAsUIElement.CopyTo(choiceInputSet));
    }

    void XamlBuilder::BuildExpandedChoiceSetInput(
        IAdaptiveRenderContext* renderContext,
        IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
        boolean isMultiSelect,
        IUIElement** choiceInputSet)
    {
        ComPtr<IVector<IAdaptiveChoiceInput*>> choices;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        ComPtr<IStackPanel> stackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        stackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IPanel> panel;
        THROW_IF_FAILED(stackPanel.As(&panel));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);

        XamlHelpers::IterateOverVector<IAdaptiveChoiceInput>(choices.Get(), [panel, isMultiSelect, renderContext, values](IAdaptiveChoiceInput* adaptiveChoiceInput)
        {
            ComPtr<IUIElement> choiceItem;
            if (isMultiSelect)
            {
                ComPtr<ICheckBox> checkBox = XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));
                THROW_IF_FAILED(checkBox.As(&choiceItem));

                ComPtr<IFrameworkElement> frameworkElement;
                THROW_IF_FAILED(checkBox.As(&frameworkElement));
                SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Choice.Multiselect", frameworkElement.Get());
            }
            else
            {
                ComPtr<IRadioButton> radioButton = XamlHelpers::CreateXamlClass<IRadioButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RadioButton));
                THROW_IF_FAILED(radioButton.As(&choiceItem));

                ComPtr<IFrameworkElement> frameworkElement;
                THROW_IF_FAILED(radioButton.As(&frameworkElement));
                SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Choice.SingleSelect", frameworkElement.Get());
            }

            HString title;
            THROW_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));
            XamlHelpers::SetContent(choiceItem.Get(), title.Get());

            XamlHelpers::SetToggleValue(choiceItem.Get(), IsChoiceSelected(values, adaptiveChoiceInput));

            THROW_IF_FAILED(AddHandledTappedEvent(choiceItem.Get()));
            
            XamlHelpers::AppendXamlElementToPanel(choiceItem.Get(), panel.Get());
        });

        ComPtr<IFrameworkElement> choiceSetAsFrameworkElement;
        THROW_IF_FAILED(stackPanel.As(&choiceSetAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.ChoiceSet.Expanded", choiceSetAsFrameworkElement.Get()));

        THROW_IF_FAILED(stackPanel.CopyTo(choiceInputSet));
    }

    void AddInputValueToContext(
        IAdaptiveRenderContext* renderContext, 
        IAdaptiveCardElement* adaptiveCardElement, 
        IUIElement* inputUiElement)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveInputElement> inputElement;
        THROW_IF_FAILED(cardElement.As(&inputElement));

        ComPtr<InputValue> input;
        THROW_IF_FAILED(MakeAndInitialize<InputValue>(&input, inputElement.Get(), inputUiElement));
        THROW_IF_FAILED(renderContext->AddInputValue(input.Get()));
    }

    void XamlBuilder::BuildChoiceSetInput(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* /*renderArgs*/,
        IUIElement** choiceInputSet)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"ChoiceSet was stripped from card because interactivity is not supported").Get());
            return;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveChoiceSetInput> adaptiveChoiceSetInput;
        THROW_IF_FAILED(cardElement.As(&adaptiveChoiceSetInput));

        ABI::AdaptiveNamespace::ChoiceSetStyle choiceSetStyle;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_ChoiceSetStyle(&choiceSetStyle));

        boolean isMultiSelect;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));

        if (choiceSetStyle == ABI::AdaptiveNamespace::ChoiceSetStyle_Compact &&
            !isMultiSelect)
        {
            BuildCompactChoiceSetInput(renderContext, adaptiveChoiceSetInput.Get(), choiceInputSet);
        }
        else
        {
            BuildExpandedChoiceSetInput(renderContext, adaptiveChoiceSetInput.Get(), isMultiSelect, choiceInputSet);
        }

        AddInputValueToContext(renderContext, adaptiveCardElement, *choiceInputSet);
    }

    void XamlBuilder::BuildDateInput(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* /*renderArgs*/,
        IUIElement** dateInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Date input was stripped from card because interactivity is not supported").Get());
            return;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveDateInput> adaptiveDateInput;
        THROW_IF_FAILED(cardElement.As(&adaptiveDateInput));

        ComPtr<ICalendarDatePicker> datePicker = XamlHelpers::CreateXamlClass<ICalendarDatePicker>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CalendarDatePicker));

        HString placeHolderText;
        THROW_IF_FAILED(adaptiveDateInput->get_Placeholder(placeHolderText.GetAddressOf()));
        THROW_IF_FAILED(datePicker->put_PlaceholderText(placeHolderText.Get()));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> datePickerAsFrameworkElement;
        THROW_IF_FAILED(datePicker.As(&datePickerAsFrameworkElement));
        THROW_IF_FAILED(datePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));

        THROW_IF_FAILED(datePicker.CopyTo(dateInputControl));
        
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Date", datePickerAsFrameworkElement.Get()));
        
        AddInputValueToContext(renderContext, adaptiveCardElement, *dateInputControl);

        // TODO: Handle parsing dates for min/max and value
    }

    void XamlBuilder::BuildNumberInput(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* /*renderArgs*/,
        IUIElement** numberInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Number input was stripped from card because interactivity is not supported").Get());
            return;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveNumberInput> adaptiveNumberInput;
        THROW_IF_FAILED(cardElement.As(&adaptiveNumberInput));

        ComPtr<ITextBox> textBox = XamlHelpers::CreateXamlClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

        ComPtr<IInputScopeName> inputScopeName = XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
        THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Number));

        ComPtr<IInputScope> inputScope = XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
        ComPtr<IVector<InputScopeName*>> names;
        THROW_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
        THROW_IF_FAILED(names->Append(inputScopeName.Get()));

        THROW_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

        INT32 value;
        THROW_IF_FAILED(adaptiveNumberInput->get_Value(&value));

        std::wstring stringValue = std::to_wstring(value);
        THROW_IF_FAILED(textBox->put_Text(HStringReference(stringValue.c_str()).Get()));

        ComPtr<ITextBox2> textBox2;
        THROW_IF_FAILED(textBox.As(&textBox2));

        HString placeHolderText;
        THROW_IF_FAILED(adaptiveNumberInput->get_Placeholder(placeHolderText.GetAddressOf()));
        THROW_IF_FAILED(textBox2->put_PlaceholderText(placeHolderText.Get()));

        ComPtr<IFrameworkElement> frameworkElement;
        THROW_IF_FAILED(textBox.As(&frameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Number", frameworkElement.Get()));

        // TODO: Handle max and min?
        THROW_IF_FAILED(textBox.CopyTo(numberInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *numberInputControl);
    }

    void XamlBuilder::BuildTextInput(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* /*renderArgs*/,
        IUIElement** textInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Text Input was stripped from card because interactivity is not supported").Get());
            return;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextInput> adaptiveTextInput;
        THROW_IF_FAILED(cardElement.As(&adaptiveTextInput));

        ComPtr<ITextBox> textBox = XamlHelpers::CreateXamlClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

        boolean isMultiLine;
        THROW_IF_FAILED(adaptiveTextInput->get_IsMultiline(&isMultiLine));
        THROW_IF_FAILED(textBox->put_AcceptsReturn(isMultiLine));

        HString textValue;
        THROW_IF_FAILED(adaptiveTextInput->get_Value(textValue.GetAddressOf()));
        THROW_IF_FAILED(textBox->put_Text(textValue.Get()));

        UINT32 maxLength;
        THROW_IF_FAILED(adaptiveTextInput->get_MaxLength(&maxLength));
        THROW_IF_FAILED(textBox->put_MaxLength(maxLength));

        ComPtr<ITextBox2> textBox2;
        THROW_IF_FAILED(textBox.As(&textBox2));

        HString placeHolderText;
        THROW_IF_FAILED(adaptiveTextInput->get_Placeholder(placeHolderText.GetAddressOf()));
        THROW_IF_FAILED(textBox2->put_PlaceholderText(placeHolderText.Get()));

        ABI::AdaptiveNamespace::TextInputStyle textInputStyle;
        THROW_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));

        ComPtr<IInputScopeName> inputScopeName = XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
        switch (textInputStyle)
        {
            case ABI::AdaptiveNamespace::TextInputStyle::Email:
                THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_EmailSmtpAddress));
                break;

            case ABI::AdaptiveNamespace::TextInputStyle::Tel:
                THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_TelephoneNumber));
                break;

            case ABI::AdaptiveNamespace::TextInputStyle::Url:
                THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Url));
                break;
        }

        ComPtr<IInputScope> inputScope = XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
        ComPtr<IVector<InputScopeName*>> names;
        THROW_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
        THROW_IF_FAILED(names->Append(inputScopeName.Get()));

        THROW_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

        ComPtr<IFrameworkElement> frameworkElement;
        THROW_IF_FAILED(textBox.As(&frameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", frameworkElement.Get()));

        THROW_IF_FAILED(textBox.CopyTo(textInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *textInputControl);
    }

    void XamlBuilder::BuildTimeInput(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* /*renderArgs*/,
        IUIElement** timeInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Time Input was stripped from card because interactivity is not supported").Get());
            return;
        }

        ComPtr<ITimePicker> timePicker = XamlHelpers::CreateXamlClass<ITimePicker>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TimePicker));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> timePickerAsFrameworkElement;
        THROW_IF_FAILED(timePicker.As(&timePickerAsFrameworkElement));
        THROW_IF_FAILED(timePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));

        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Time", timePickerAsFrameworkElement.Get()));

        // TODO: Handle placeholder text and parsing times for min/max and value

        THROW_IF_FAILED(timePicker.CopyTo(timeInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *timeInputControl);
    }

    void XamlBuilder::BuildToggleInput(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveRenderContext* renderContext,
        IAdaptiveRenderArgs* /*renderArgs*/,
        IUIElement** toggleInputControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
               ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"Toggle Input was stripped from card because interactivity is not supported").Get());
            return;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveToggleInput> adaptiveToggleInput;
        THROW_IF_FAILED(cardElement.As(&adaptiveToggleInput));

        ComPtr<ICheckBox> checkBox = XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));

        HString title;
        THROW_IF_FAILED(adaptiveToggleInput->get_Title(title.GetAddressOf()));

        XamlHelpers::SetContent(checkBox.Get(), title.Get());

        HString value;
        THROW_IF_FAILED(adaptiveToggleInput->get_Value(value.GetAddressOf()));

        HString valueOn;
        THROW_IF_FAILED(adaptiveToggleInput->get_ValueOn(valueOn.GetAddressOf()));

        INT32 compareValueOn;
        THROW_IF_FAILED(WindowsCompareStringOrdinal(value.Get(), valueOn.Get(), &compareValueOn));

        XamlHelpers::SetToggleValue(checkBox.Get(), (compareValueOn == 0));

        ComPtr<IUIElement> checkboxAsUIElement;
        THROW_IF_FAILED(checkBox.As(&checkboxAsUIElement));
        THROW_IF_FAILED(AddHandledTappedEvent(checkboxAsUIElement.Get()));

        ComPtr<IFrameworkElement> frameworkElement;
        THROW_IF_FAILED(checkBox.As(&frameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", frameworkElement.Get()));

        THROW_IF_FAILED(checkboxAsUIElement.CopyTo(toggleInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *toggleInputControl);
    }

    bool XamlBuilder::SupportsInteractivity(IAdaptiveHostConfig* hostConfig)
    {
        boolean supportsInteractivity;
        THROW_IF_FAILED(hostConfig->get_SupportsInteractivity(&supportsInteractivity));
        return Boolify(supportsInteractivity);
    }

    void XamlBuilder::WrapInTouchTarget(
        IAdaptiveCardElement* adaptiveCardElement,
        IUIElement* elementToWrap,
        IAdaptiveActionElement* action,
        IAdaptiveRenderContext* renderContext,
        bool fullWidth,
        IUIElement** finalElement)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ABI::AdaptiveNamespace::ActionType actionType;
        THROW_IF_FAILED(action->get_ActionType(&actionType));

        // TODO: In future should support inline ShowCard, but that's complicated for inline elements
        if (actionType == ABI::AdaptiveNamespace::ActionType::ShowCard)
        {
            ComPtr<IAdaptiveActionsConfig> actionsConfig;
            THROW_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));
            ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
            THROW_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));
            ABI::AdaptiveNamespace::ActionMode showCardActionMode;
            THROW_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));
            if (showCardActionMode == ABI::AdaptiveNamespace::ActionMode::Inline)
            {
                // Was inline show card, so don't wrap the element and just return
                ComPtr<IUIElement> localElementToWrap(elementToWrap);
                localElementToWrap.CopyTo(finalElement);
                return;
            }
        }

        ComPtr<IButton> button = XamlHelpers::CreateXamlClass<IButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Button));

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

        // We want the hit target to equally split the vertical space above and below the current item.
        // However, all we know is the spacing of the current item, which only applies to the spacing above.
        // We don't know what the spacing of the NEXT element will be, so we can't calculate the correct spacing below.
        // For now, we'll simply assume the bottom spacing is the same as the top.
        ABI::AdaptiveNamespace::Spacing elementSpacing;
        THROW_IF_FAILED(adaptiveCardElement->get_Spacing(&elementSpacing));
        UINT spacingSize;
        THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), elementSpacing, &spacingSize));
        double topBottomPadding = spacingSize / 2.0;

        // For button padding, we apply the cardPadding and topBottomPadding (and then we negate these in the margin)
        ComPtr<IControl> buttonAsControl;
        THROW_IF_FAILED(button.As(&buttonAsControl));
        THROW_IF_FAILED(buttonAsControl->put_Padding({ (double)cardPadding, topBottomPadding, (double)cardPadding, topBottomPadding }));

        double negativeCardMargin = cardPadding * -1.0;
        double negativeTopBottomMargin = topBottomPadding * -1.0;

        ComPtr<IFrameworkElement> buttonAsFrameworkElement;
        THROW_IF_FAILED(button.As(&buttonAsFrameworkElement));
        THROW_IF_FAILED(buttonAsFrameworkElement->put_Margin({ negativeCardMargin, negativeTopBottomMargin, negativeCardMargin, negativeTopBottomMargin }));

        // Style the hit target button
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.SelectAction", buttonAsFrameworkElement.Get()));

        WireButtonClickToAction(button.Get(), action, renderContext);

        THROW_IF_FAILED(button.CopyTo(finalElement));
    }

    void XamlBuilder::HandleSelectAction(
        IAdaptiveCardElement* adaptiveCardElement,
        IAdaptiveActionElement* selectAction,
        IAdaptiveRenderContext* renderContext,
        IUIElement* uiElement,
        bool supportsInteractivity,
        bool fullWidthTouchTarget,
        IUIElement** outUiElement)
    {
        if (selectAction != nullptr && supportsInteractivity)
        {
            WrapInTouchTarget(adaptiveCardElement, uiElement, selectAction, renderContext, fullWidthTouchTarget, outUiElement);
        }
        else
        {
            if (!supportsInteractivity)
            {
                renderContext->AddWarning(
                    ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                    HStringReference(L"SelectAction present, but Interactivity is not supported").Get());
            }

            ComPtr<IUIElement> localUiElement(uiElement);
            THROW_IF_FAILED(localUiElement.CopyTo(outUiElement));
        }
    }

    void XamlBuilder::WireButtonClickToAction(
        IButton* button,
        IAdaptiveActionElement* action,
        IAdaptiveRenderContext* renderContext)
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
        THROW_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>([strongAction, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT
        {
            THROW_IF_FAILED(actionInvoker->SendActionEvent(strongAction.Get()));
            return S_OK;
        }).Get(), &clickToken));
    }

    HRESULT XamlBuilder::AddHandledTappedEvent(IUIElement* uiElement)
    {
        if (uiElement == nullptr)
        {
            return E_INVALIDARG;
        }

        EventRegistrationToken clickToken;
        // Add Tap handler that sets the event as handled so that it doesn't propagate to the parent containers.
        return uiElement->add_Tapped(Callback<ITappedEventHandler>([](IInspectable* /*sender*/, ITappedRoutedEventArgs* args) -> HRESULT
        {
            return args->put_Handled(TRUE);
        }).Get(), &clickToken);
    }
AdaptiveNamespaceEnd
