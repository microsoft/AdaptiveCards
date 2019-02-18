#include "pch.h"

#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveImage.h"
#include <windows.foundation.collections.h>
#include <windows.storage.h>
#include <windows.ui.xaml.markup.h>
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
#include "MediaHelpers.h"
#include "AdaptiveBase64Util.h"
#include <robuffer.h>

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
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::UI::Xaml::Automation;
using namespace ABI::Windows::Web::Http;
using namespace ABI::Windows::Web::Http::Filters;

const PCWSTR c_TextBlockSubtleOpacityKey = L"TextBlock.SubtleOpacity";
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

        ComPtr<IBrush> lineColorBrush = GetSolidColorBrush(separatorColor);
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

    void XamlBuilder::BuildXamlTreeFromAdaptiveCard(_In_ IAdaptiveCard* adaptiveCard,
                                                    _Outptr_ IFrameworkElement** xamlTreeRoot,
                                                    _In_ IAdaptiveRenderContext* renderContext,
                                                    std::shared_ptr<XamlBuilder> xamlBuilder,
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

            ComPtr<IPanel> bodyElementContainer;
            ComPtr<IUIElement> rootElement =
                CreateRootCardElement(adaptiveCard, renderContext, renderArgs.Get(), xamlBuilder, &bodyElementContainer);
            ComPtr<IFrameworkElement> rootAsFrameworkElement;
            THROW_IF_FAILED(rootElement.As(&rootAsFrameworkElement));

            ComPtr<IAdaptiveActionElement> selectAction;
            THROW_IF_FAILED(adaptiveCard->get_SelectAction(&selectAction));

            // Create a new IUIElement pointer to house the root element decorated with select action
            ComPtr<IUIElement> rootSelectActionElement;
            HandleSelectAction(nullptr,
                               selectAction.Get(),
                               renderContext,
                               rootElement.Get(),
                               SupportsInteractivity(hostConfig.Get()),
                               true,
                               &rootSelectActionElement);
            THROW_IF_FAILED(rootSelectActionElement.As(&rootAsFrameworkElement));

            ComPtr<AdaptiveNamespace::AdaptiveRenderContext> contextImpl =
                PeekInnards<AdaptiveNamespace::AdaptiveRenderContext>(renderContext);

            THROW_IF_FAILED(contextImpl->put_CardFrameworkElement(rootAsFrameworkElement.Get()));

            // Enumerate the child items of the card and build xaml for them
            ComPtr<IVector<IAdaptiveCardElement*>> body;
            THROW_IF_FAILED(adaptiveCard->get_Body(&body));
            ComPtr<IAdaptiveRenderArgs> bodyRenderArgs;
            THROW_IF_FAILED(
                MakeAndInitialize<AdaptiveRenderArgs>(&bodyRenderArgs, containerStyle, rootAsFrameworkElement.Get()));
            BuildPanelChildren(body.Get(), bodyElementContainer.Get(), renderContext, bodyRenderArgs.Get(), [](IUIElement*) {});

            ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment;
            THROW_IF_FAILED(adaptiveCard->get_VerticalContentAlignment(&verticalContentAlignment));
            XamlBuilder::SetVerticalContentAlignmentToChildren(bodyElementContainer.Get(), verticalContentAlignment);

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
                    BuildActions(actions.Get(), bodyElementContainer.Get(), bodyCount > 0, renderContext, containerStyle);
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
                THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Card", rootAsFrameworkElement.Get()));
            }
            else
            {
                THROW_IF_FAILED(
                    SetStyleFromResourceDictionary(renderContext, L"Adaptive.ShowCard.Card", rootAsFrameworkElement.Get()));
            }

            THROW_IF_FAILED(rootAsFrameworkElement.CopyTo(xamlTreeRoot));

            if (isOuterCard && (xamlBuilder != nullptr))
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
    }

    HRESULT XamlBuilder::AddListener(_In_ IXamlBuilderListener* listener) noexcept try
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

    HRESULT XamlBuilder::RemoveListener(_In_ IXamlBuilderListener* listener) noexcept try
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
                                                          std::shared_ptr<XamlBuilder> xamlBuilder,
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
            ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
            THROW_IF_FAILED(rootAsPanel->put_Background(backgroundColorBrush.Get()));
        }

        HSTRING backgroundImage;
        THROW_IF_FAILED(adaptiveCard->get_BackgroundImage(&backgroundImage));
        if (backgroundImage != nullptr)
        {
            ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImage, renderContext, renderArgs);
        }

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
            rootAsFrameworkElement->put_VerticalAlignment(VerticalAlignment::VerticalAlignment_Stretch);
        }

        ComPtr<IUIElement> rootAsUIElement;
        THROW_IF_FAILED(rootElement.As(&rootAsUIElement));
        return rootAsUIElement;
    }

    void XamlBuilder::ApplyBackgroundToRoot(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
                                            _In_ HSTRING url,
                                            _In_ IAdaptiveRenderContext* renderContext,
                                            _In_ IAdaptiveRenderArgs* renderArgs)
    {
        // In order to reuse the image creation code paths, we simply create an adaptive card
        // image element and then build that into xaml and apply to the root.
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));
        adaptiveImage->put_Url(url);

        ComPtr<IAdaptiveCardElement> adaptiveCardElement;
        THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
        ComPtr<IUIElement> backgroundImage;

        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));

        ComPtr<IAdaptiveElementRenderer> elementRenderer;
        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Image").Get(), &elementRenderer));
        if (elementRenderer != nullptr)
        {
            elementRenderer->Render(adaptiveCardElement.Get(), renderContext, renderArgs, &backgroundImage);
            if (backgroundImage == nullptr)
            {
                return;
            }
        }

        // All background images should be stretched to fill the whole card.
        ComPtr<IImage> xamlImage;
        THROW_IF_FAILED(backgroundImage.As(&xamlImage));
        THROW_IF_FAILED(xamlImage->put_Stretch(Stretch::Stretch_UniformToFill));

        ComPtr<IFrameworkElement> backgroundAsFrameworkElement;
        THROW_IF_FAILED(xamlImage.As(&backgroundAsFrameworkElement));
        THROW_IF_FAILED(backgroundAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));

        XamlHelpers::AppendXamlElementToPanel(backgroundImage.Get(), rootPanel);

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

    void XamlBuilder::BuildPanelChildren(_In_ IVector<IAdaptiveCardElement*>* children,
                                         _In_ IPanel* parentPanel,
                                         _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                         _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                         std::function<void(IUIElement* child)> childCreatedCallback)
    {
        int currentElement = 0;
        unsigned int childrenSize;
        THROW_IF_FAILED(children->get_Size(&childrenSize));
        XamlHelpers::IterateOverVector<IAdaptiveCardElement>(children, [&](IAdaptiveCardElement* element) {
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

                if (newControl != nullptr)
                {
                    boolean isVisible;
                    THROW_IF_FAILED(element->get_IsVisible(&isVisible));

                    if (!isVisible)
                    {
                        THROW_IF_FAILED(newControl->put_Visibility(Visibility_Collapsed));
                    }

                    HString id;
                    THROW_IF_FAILED(element->get_Id(id.GetAddressOf()));

                    if (id.IsValid())
                    {
                        ComPtr<IFrameworkElement> newControlAsFrameworkElement;
                        THROW_IF_FAILED(newControl.As(&newControlAsFrameworkElement));
                        THROW_IF_FAILED(newControlAsFrameworkElement->put_Name(id.Get()));
                    }

                    ABI::AdaptiveNamespace::HeightType heightType{};
                    THROW_IF_FAILED(element->get_Height(&heightType));
                    XamlHelpers::AppendXamlElementToPanel(newControl.Get(), parentPanel, heightType);

                    childCreatedCallback(newControl.Get());
                }
            }
            else
            {
                std::wstring errorString = L"No Renderer found for type: ";
                errorString += elementType.GetRawBuffer(nullptr);
                renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                                          HStringReference(errorString.c_str()).Get());
            }
        });
    }

    void XamlBuilder::BuildShowCard(_In_ IAdaptiveShowCardActionConfig* showCardActionConfig,
                                    _In_ IAdaptiveActionElement* action,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    bool isBottomActionBar,
                                    _Outptr_ IUIElement** uiShowCard)
    {
        ComPtr<IAdaptiveActionElement> localAction(action);
        ComPtr<IAdaptiveRenderContext> localRenderContext(renderContext);
        ComPtr<IAdaptiveShowCardAction> showCardAction;
        THROW_IF_FAILED(localAction.As(&showCardAction));

        ABI::AdaptiveNamespace::ContainerStyle showCardConfigStyle;
        THROW_IF_FAILED(showCardActionConfig->get_Style(&showCardConfigStyle));

        ComPtr<IAdaptiveCard> showCard;
        THROW_IF_FAILED(showCardAction->get_Card(showCard.GetAddressOf()));

        ComPtr<IFrameworkElement> localUiShowCard;
        BuildXamlTreeFromAdaptiveCard(showCard.Get(), localUiShowCard.GetAddressOf(), localRenderContext.Get(), nullptr, false, showCardConfigStyle);

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

        double sideMargin = (double)padding * -1;
        double topMargin = isBottomActionBar ? inlineTopMargin + padding : inlineTopMargin;
        double bottomMargin = isBottomActionBar ? (double)padding * -1 : 0;

        Thickness margin = {sideMargin, topMargin, sideMargin, bottomMargin};
        THROW_IF_FAILED(showCardFrameworkElement->put_Margin(margin));

        ComPtr<IUIElement> showCardUIElement;
        THROW_IF_FAILED(localUiShowCard.As(&showCardUIElement));

        // Set the visibility as Collapsed until the action is triggered
        THROW_IF_FAILED(showCardUIElement->put_Visibility(Visibility_Collapsed));

        *uiShowCard = showCardUIElement.Detach();
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
            adaptiveImage->put_HorizontalAlignment(HAlignment_Center);

            ComPtr<IAdaptiveCardElement> adaptiveCardElement;
            THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
            ComPtr<AdaptiveRenderArgs> childRenderArgs;
            THROW_IF_FAILED(
                MakeAndInitialize<AdaptiveRenderArgs>(&childRenderArgs, containerStyle, buttonContentsStackPanel.Get()));

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
                    })
                        .Get(),
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

    HRESULT XamlBuilder::HandleToggleVisibilityClick(_In_ IAdaptiveRenderContext* renderContext, _In_ IAdaptiveActionElement* action)
    {
        ComPtr<IAdaptiveActionElement> localAction(action);
        ComPtr<IAdaptiveToggleVisibility> toggleAction;
        RETURN_IF_FAILED(localAction.As(&toggleAction));

        ComPtr<IFrameworkElement> cardFrameworkElement;
        RETURN_IF_FAILED(renderContext->get_CardFrameworkElement(&cardFrameworkElement));

        ComPtr<IVector<AdaptiveToggleVisibilityTarget*>> targets;
        RETURN_IF_FAILED(toggleAction->get_TargetElements(&targets));

        ComPtr<IIterable<AdaptiveToggleVisibilityTarget*>> targetsIterable;
        RETURN_IF_FAILED(targets.As<IIterable<AdaptiveToggleVisibilityTarget*>>(&targetsIterable));

        boolean hasCurrent;
        ComPtr<IIterator<AdaptiveToggleVisibilityTarget*>> targetIterator;
        HRESULT hr = targetsIterable->First(&targetIterator);
        RETURN_IF_FAILED(targetIterator->get_HasCurrent(&hasCurrent));

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

                Visibility visibilityToSet;
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
                    Visibility currentVisibility;
                    RETURN_IF_FAILED(toggleElementAsUIElement->get_Visibility(&currentVisibility));
                    visibilityToSet = (currentVisibility == Visibility_Collapsed) ? Visibility_Visible : Visibility_Collapsed;
                }

                RETURN_IF_FAILED(toggleElementAsUIElement->put_Visibility(visibilityToSet));
            }

            hr = targetIterator->MoveNext(&hasCurrent);
        }

        return S_OK;
    }

    void XamlBuilder::BuildActionSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ IUIElement** actionSetControl)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        if (!SupportsInteractivity(hostConfig.Get()))
        {
            renderContext->AddWarning(
                ABI::AdaptiveNamespace::WarningStatusCode::InteractivityNotSupported,
                HStringReference(L"ActionSet was stripped from card because interactivity is not supported").Get());
            return;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveActionSet> adaptiveActionSet;
        THROW_IF_FAILED(cardElement.As(&adaptiveActionSet));

        ComPtr<IVector<IAdaptiveActionElement*>> actions;
        THROW_IF_FAILED(adaptiveActionSet->get_Actions(&actions));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        renderArgs->get_ContainerStyle(&containerStyle);

        BuildActionSetHelper(actions.Get(), renderContext, false, actionSetControl, containerStyle);
    }

    void XamlBuilder::BuildActions(_In_ IVector<IAdaptiveActionElement*>* children,
                                   _In_ IPanel* bodyPanel,
                                   bool insertSeparator,
                                   _In_ IAdaptiveRenderContext* renderContext,
                                   ABI::AdaptiveNamespace::ContainerStyle containerStyle)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        THROW_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        // Create a separator between the body and the actions
        if (insertSeparator)
        {
            ABI::AdaptiveNamespace::Spacing spacing;
            THROW_IF_FAILED(actionsConfig->get_Spacing(&spacing));

            UINT spacingSize;
            THROW_IF_FAILED(GetSpacingSizeFromSpacing(hostConfig.Get(), spacing, &spacingSize));

            ABI::Windows::UI::Color color = {0};
            auto separator = CreateSeparator(renderContext, spacingSize, 0, color);
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), bodyPanel);
        }

        ComPtr<IUIElement> actionSetControl;
        BuildActionSetHelper(children, renderContext, true, &actionSetControl, containerStyle);

        XamlHelpers::AppendXamlElementToPanel(actionSetControl.Get(), bodyPanel);
    }

    void XamlBuilder::BuildActionSetHelper(IVector<IAdaptiveActionElement*>* children,
                                           IAdaptiveRenderContext* renderContext,
                                           bool isBottomActionBar,
                                           IUIElement** actionSetControl,
                                           ABI::AdaptiveNamespace::ContainerStyle containerStyle)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        THROW_IF_FAILED(hostConfig->get_Actions(actionsConfig.GetAddressOf()));
        ComPtr<IAdaptiveRenderContext> strongRenderContext(renderContext);

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
            // If stretch alignment and orientation is horizontal, we use a grid with equal column widths to achieve
            // stretch behavior. For vertical orientation, we'll still just use a stack panel since the concept of
            // stretching buttons height isn't really valid, especially when the height of cards are typically dynamic.
            ComPtr<IGrid> actionsGrid =
                XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
            THROW_IF_FAILED(actionsGrid->get_ColumnDefinitions(&columnDefinitions));
            THROW_IF_FAILED(actionsGrid.As(&actionsPanel));
        }

        else
        {
            // Create a stack panel for the action buttons
            ComPtr<IStackPanel> actionStackPanel =
                XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

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

        Thickness buttonMargin = {0, 0, 0, 0};
        if (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
        {
            buttonMargin.Left = buttonMargin.Right = buttonSpacing / 2;

            // Negate the spacing on the sides so the left and right buttons are flush on the side.
            // We do NOT remove the margin from the individual button itself, since that would cause
            // the equal columns stretch behavior to not have equal columns (since the first and last
            // button would be narrower without the same margins as its peers).
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            THROW_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            THROW_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({buttonMargin.Left * -1, 0, buttonMargin.Right * -1, 0}));
        }
        else
        {
            buttonMargin.Top = buttonMargin.Bottom = buttonSpacing / 2;

            // Negate the spacing on the top and bottom so the first and last buttons don't have extra padding
            ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
            THROW_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
            THROW_IF_FAILED(actionsPanelAsFrameworkElement->put_Margin({0, buttonMargin.Top * -1, 0, buttonMargin.Bottom * -1}));
        }

        UINT32 maxActions;
        THROW_IF_FAILED(actionsConfig->get_MaxActions(&maxActions));

        ComPtr<IAdaptiveShowCardActionConfig> showCardActionConfig;
        THROW_IF_FAILED(actionsConfig->get_ShowCard(&showCardActionConfig));

        ABI::AdaptiveNamespace::ActionMode showCardActionMode;
        THROW_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        bool allActionsHaveIcons{true};
        XamlHelpers::IterateOverVector<IAdaptiveActionElement>(children, [&](IAdaptiveActionElement* child) {
            HSTRING iconUrl;
            THROW_IF_FAILED(child->get_IconUrl(&iconUrl));

            bool iconUrlIsEmpty = WindowsIsStringEmpty(iconUrl);
            if (iconUrlIsEmpty)
            {
                allActionsHaveIcons = false;
            }
        });

        UINT currentAction = 0;

        std::shared_ptr<std::vector<ComPtr<IUIElement>>> allShowCards = std::make_shared<std::vector<ComPtr<IUIElement>>>();
        ComPtr<IStackPanel> showCardsStackPanel =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));
        XamlHelpers::IterateOverVector<IAdaptiveActionElement>(children, [&](IAdaptiveActionElement* child) {
            if (currentAction < maxActions)
            {
                // Render a button for each action
                ComPtr<IAdaptiveActionElement> action(child);
                ComPtr<IButton> button =
                    XamlHelpers::CreateXamlClass<IButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Button));

                ComPtr<IFrameworkElement> buttonFrameworkElement;
                THROW_IF_FAILED(button.As(&buttonFrameworkElement));

                THROW_IF_FAILED(buttonFrameworkElement->put_Margin(buttonMargin));

                if (actionsOrientation == ABI::AdaptiveNamespace::ActionsOrientation::Horizontal)
                {
                    // For horizontal alignment, we always use stretch
                    THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(
                        ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Stretch));
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

                ArrangeButtonContent(action.Get(),
                                     actionsConfig.Get(),
                                     renderContext,
                                     containerStyle,
                                     hostConfig.Get(),
                                     allActionsHaveIcons,
                                     button.Get());

                ABI::AdaptiveNamespace::ActionType actionType;
                THROW_IF_FAILED(action->get_ActionType(&actionType));

                // If this is a show card action and we're rendering the actions inline, render the card that will be shown
                ComPtr<IUIElement> uiShowCard;
                if (actionType == ABI::AdaptiveNamespace::ActionType::ShowCard &&
                    showCardActionMode == ABI::AdaptiveNamespace::ActionMode::Inline)
                {
                    BuildShowCard(showCardActionConfig.Get(),
                                  action.Get(),
                                  strongRenderContext.Get(),
                                  isBottomActionBar,
                                  uiShowCard.GetAddressOf());
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
                THROW_IF_FAILED(buttonBase->add_Click(
                    Callback<IRoutedEventHandler>([action, actionType, showCardActionMode, uiShowCard, allShowCards, actionInvoker, strongRenderContext](
                                                      IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                        if (actionType == ABI::AdaptiveNamespace::ActionType::ShowCard &&
                            showCardActionMode != ABI::AdaptiveNamespace::ActionMode_Popup)
                        {
                            // Check if this show card is currently visible
                            Visibility currentVisibility;
                            RETURN_IF_FAILED(uiShowCard->get_Visibility(&currentVisibility));

                            // Collapse all cards to make sure that no other show cards are visible
                            for (std::vector<ComPtr<IUIElement>>::iterator it = allShowCards->begin();
                                 it != allShowCards->end();
                                 ++it)
                            {
                                RETURN_IF_FAILED((*it)->put_Visibility(Visibility_Collapsed));
                            }

                            // If the card had been collapsed before, show it now
                            if (currentVisibility == Visibility_Collapsed)
                            {
                                RETURN_IF_FAILED(uiShowCard->put_Visibility(Visibility_Visible));
                            }
                        }
                        else if (actionType == ABI::AdaptiveNamespace::ActionType::ToggleVisibility)
                        {
                            RETURN_IF_FAILED(HandleToggleVisibilityClick(strongRenderContext.Get(), action.Get()));
                        }
                        else
                        {
                            RETURN_IF_FAILED(actionInvoker->SendActionEvent(action.Get()));
                        }

                        return S_OK;
                    })
                        .Get(),
                    &clickToken));

                HString actionSentiment;
                THROW_IF_FAILED(action->get_Sentiment(actionSentiment.GetAddressOf()));

                INT32 isSentimentPositive{}, isSentimentDestructive{}, isSentimentDefault{};

                ComPtr<AdaptiveNamespace::AdaptiveRenderContext> contextImpl =
                    PeekInnards<AdaptiveNamespace::AdaptiveRenderContext>(renderContext);

                ComPtr<IResourceDictionary> resourceDictionary;
                THROW_IF_FAILED(renderContext->get_OverrideStyles(&resourceDictionary));
                ComPtr<IStyle> styleToApply;

                if ((SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"default").Get(), &isSentimentDefault))
                    && (isSentimentDefault == 0))
                    || WindowsIsStringEmpty(actionSentiment.Get()))
                {
                    THROW_IF_FAILED(
                        SetStyleFromResourceDictionary(renderContext, L"Adaptive.Action", buttonFrameworkElement.Get()));
                }
                else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"positive").Get(), &isSentimentPositive))
                    && (isSentimentPositive == 0))
                {
                    if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(),
                        L"Adaptive.Action.Positive",
                        &styleToApply)))
                    {
                        THROW_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                    }
                    else
                    {
                        // By default, set the action background color to accent color
                        ComPtr<IResourceDictionary> actionSentimentDictionary =
                            contextImpl->GetDefaultActionSentimentDictionary();

                        if (SUCCEEDED(TryGetResourceFromResourceDictionaries(actionSentimentDictionary.Get(),
                            L"PositiveActionDefaultStyle",
                            styleToApply.GetAddressOf())))
                        {
                            THROW_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                        }
                    }
                }
                else if (SUCCEEDED(WindowsCompareStringOrdinal(actionSentiment.Get(), HStringReference(L"destructive").Get(), &isSentimentDestructive))
                         && (isSentimentDestructive == 0))
                {
                    if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IStyle>(resourceDictionary.Get(),
                        L"Adaptive.Action.Destructive",
                        &styleToApply)))
                    {
                        THROW_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                    }
                    else
                    {
                        // By default, set the action text color to attention color
                        ComPtr<IResourceDictionary> actionSentimentDictionary =
                            contextImpl->GetDefaultActionSentimentDictionary();

                        if (SUCCEEDED(TryGetResourceFromResourceDictionaries(actionSentimentDictionary.Get(),
                            L"DestructiveActionDefaultStyle",
                            styleToApply.GetAddressOf())))
                        {
                            THROW_IF_FAILED(buttonFrameworkElement->put_Style(styleToApply.Get()));
                        }
                    }
                }
                else
                {
                    HString actionSentimentStyle;
                    THROW_IF_FAILED(WindowsConcatString(HStringReference(L"Adaptive.Action.").Get(), actionSentiment.Get(), actionSentimentStyle.GetAddressOf()));
                    THROW_IF_FAILED(
                        SetStyleFromResourceDictionary(renderContext, StringToWstring(HStringToUTF8(actionSentimentStyle.Get())), buttonFrameworkElement.Get()));
                }

                XamlHelpers::AppendXamlElementToPanel(button.Get(), actionsPanel.Get());

                if (columnDefinitions != nullptr)
                {
                    // If using the equal width columns, we'll add a column and assign the column
                    ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                    THROW_IF_FAILED(columnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Star}));
                    THROW_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

                    gridStatics->SetColumn(buttonFrameworkElement.Get(), currentAction);
                }
            }
            else
            {
                renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::MaxActionsExceeded,
                                          HStringReference(L"Some actions were not rendered due to exceeding the maximum number of actions allowed")
                                              .Get());
                return;
            }
            currentAction++;
        });

        ComPtr<IFrameworkElement> actionsPanelAsFrameworkElement;
        THROW_IF_FAILED(actionsPanel.As(&actionsPanelAsFrameworkElement));
        THROW_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Actions", actionsPanelAsFrameworkElement.Get()));

        ComPtr<IStackPanel> actionSet =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IPanel> actionSetAsPanel;
        actionSet.As(&actionSetAsPanel);

        // Add buttons and show cards to panel
        XamlHelpers::AppendXamlElementToPanel(actionsPanel.Get(), actionSetAsPanel.Get());
        XamlHelpers::AppendXamlElementToPanel(showCardsStackPanel.Get(), actionSetAsPanel.Get());

        THROW_IF_FAILED(actionSetAsPanel.CopyTo(actionSetControl));
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

    ComPtr<IBrush> XamlBuilder::GetSolidColorBrush(ABI::Windows::UI::Color color)
    {
        ComPtr<ISolidColorBrush> solidColorBrush =
            XamlHelpers::CreateXamlClass<ISolidColorBrush>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_SolidColorBrush));
        THROW_IF_FAILED(solidColorBrush->put_Color(color));
        ComPtr<IBrush> solidColorBrushAsBrush;
        THROW_IF_FAILED(solidColorBrush.As(&solidColorBrushAsBrush));
        return solidColorBrushAsBrush;
    }

    void XamlBuilder::StyleXamlTextBlock(ABI::AdaptiveNamespace::FontStyle fontStyle,
                                         ABI::AdaptiveNamespace::TextSize size,
                                         ABI::AdaptiveNamespace::ForegroundColor color,
                                         ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                         bool isSubtle,
                                         bool wrap,
                                         UINT32 maxWidth,
                                         ABI::AdaptiveNamespace::TextWeight weight,
                                         _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock,
                                         _In_ IAdaptiveHostConfig* hostConfig)
    {
        ComPtr<ITextBlock> localTextBlock(xamlTextBlock);

        ABI::Windows::UI::Color fontColor;
        THROW_IF_FAILED(GetColorFromAdaptiveColor(hostConfig, color, containerStyle, isSubtle, &fontColor));

        ComPtr<IBrush> fontColorBrush = GetSolidColorBrush(fontColor);
        THROW_IF_FAILED(localTextBlock->put_Foreground(fontColorBrush.Get()));

        HString fontFamilyName;
        UINT32 fontSize;
        ABI::Windows::UI::Text::FontWeight xamlFontWeight;

        // Retrieve the desired FontFamily, FontSize, and FontWeight values
        THROW_IF_FAILED(GetFontDataFromStyle(hostConfig, fontStyle, size, weight, fontFamilyName.GetAddressOf(), &fontSize, &xamlFontWeight));

        // Apply font size
        THROW_IF_FAILED(localTextBlock->put_FontSize((double)fontSize));

        // Apply font weight
        THROW_IF_FAILED(localTextBlock->put_FontWeight(xamlFontWeight));

        // Apply the wrap value to the xaml element
        THROW_IF_FAILED(localTextBlock->put_TextWrapping(wrap ? TextWrapping::TextWrapping_WrapWholeWords :
                                                                TextWrapping::TextWrapping_NoWrap));
        THROW_IF_FAILED(localTextBlock->put_TextTrimming(TextTrimming::TextTrimming_CharacterEllipsis));

        // Apply font family
        ComPtr<IInspectable> inspectable;
        ComPtr<IFontFamily> fontFamily;
        ComPtr<IFontFamilyFactory> fontFamilyFactory;
        THROW_IF_FAILED(Windows::Foundation::GetActivationFactory(HStringReference(L"Windows.UI.Xaml.Media.FontFamily").Get(),
                                                                  &fontFamilyFactory));
        THROW_IF_FAILED(
            fontFamilyFactory->CreateInstanceWithName(fontFamilyName.Get(), nullptr, inspectable.ReleaseAndGetAddressOf(), &fontFamily));
        THROW_IF_FAILED(xamlTextBlock->put_FontFamily(fontFamily.Get()));

        ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
        THROW_IF_FAILED(localTextBlock.As(&textBlockAsFrameworkElement));
        THROW_IF_FAILED(textBlockAsFrameworkElement->put_MaxWidth(maxWidth));
    }

    void XamlBuilder::StyleXamlTextBlock(_In_ IAdaptiveTextConfig* textConfig,
                                         ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                         _In_ ITextBlock* xamlTextBlock,
                                         _In_ IAdaptiveHostConfig* hostConfig)
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

        StyleXamlTextBlock(ABI::AdaptiveNamespace::FontStyle::Default,
                           textSize,
                           textColor,
                           containerStyle,
                           Boolify(isSubtle),
                           wrap,
                           maxWidth,
                           textWeight,
                           xamlTextBlock,
                           hostConfig);
    }

    static HRESULT SetTextOnXamlTextBlock(_In_ IAdaptiveRenderContext* renderContext,
                                          _In_ HSTRING textIn,
                                          ABI::AdaptiveNamespace::FontStyle fontStyle,
                                          _In_ HSTRING language,
                                          _In_ ITextBlock* textBlock)
    {
        ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
        RETURN_IF_FAILED(textBlock->get_Inlines(inlines.GetAddressOf()));

        DateTimeParser parser(HStringToUTF8(language));
        auto textWithParsedDates = parser.GenerateString(HStringToUTF8(textIn));

        MarkDownParser markdownParser(textWithParsedDates);
        auto htmlString = markdownParser.TransformToHtml();

        bool handledAsHtml = false;
        if (markdownParser.HasHtmlTags())
        {
            HString htmlHString;
            UTF8ToHString(htmlString, htmlHString.GetAddressOf());

            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocument> xmlDocument =
                XamlHelpers::CreateXamlClass<ABI::Windows::Data::Xml::Dom::IXmlDocument>(
                    HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument));

            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocumentIO> xmlDocumentIO;
            RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentIO));

            HRESULT hr = xmlDocumentIO->LoadXml(htmlHString.Get());
            if (SUCCEEDED(hr))
            {
                ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> xmlDocumentAsNode;
                RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentAsNode));

                RETURN_IF_FAILED(AddHtmlInlines(renderContext, xmlDocumentAsNode.Get(), inlines.Get(), fontStyle));
                handledAsHtml = true;
            }
        }

        if (!handledAsHtml)
        {
            HString hString;
            UTF8ToHString(textWithParsedDates, hString.GetAddressOf());
            AddSingleTextInline(renderContext, hString.Get(), fontStyle, false, false, inlines.Get());
        }

        return S_OK;
    }

    void XamlBuilder::BuildTextBlock(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ IUIElement** textBlockControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
        THROW_IF_FAILED(cardElement.As(&adaptiveTextBlock));

        ComPtr<ITextBlock> xamlTextBlock =
            XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

        // ITextBlock2 will be used later on
        ComPtr<ITextBlock2> xamlTextBlock2;
        THROW_IF_FAILED(xamlTextBlock.As(&xamlTextBlock2));

        HString text;
        THROW_IF_FAILED(adaptiveTextBlock->get_Text(text.GetAddressOf()));
        HString language;
        THROW_IF_FAILED(adaptiveTextBlock->get_Language(language.GetAddressOf()));
        ABI::AdaptiveNamespace::FontStyle fontStyle;
        THROW_IF_FAILED(adaptiveTextBlock->get_FontStyle(&fontStyle));
        THROW_IF_FAILED(SetTextOnXamlTextBlock(renderContext, text.Get(), fontStyle, language.Get(), xamlTextBlock.Get()));

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
            if (SUCCEEDED(TryGetResourceFromResourceDictionaries<IInspectable>(resourceDictionary.Get(),
                                                                               c_TextBlockSubtleOpacityKey,
                                                                               &subtleOpacityInspectable)))
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

        // Style the TextBlock using Host config
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));
        StyleXamlTextBlock(fontStyle,
                           textblockSize,
                           textColor,
                           containerStyle,
                           isSubtle,
                           shouldWrap,
                           MAXUINT32,
                           textWeight,
                           xamlTextBlock.Get(),
                           hostConfig.Get());

        ComPtr<IFrameworkElement> frameworkElement;
        THROW_IF_FAILED(xamlTextBlock.As(&frameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.TextBlock", frameworkElement.Get()));

        THROW_IF_FAILED(xamlTextBlock.CopyTo(textBlockControl));
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
                THROW_IF_FAILED(brushAsImageBrush->add_ImageOpened(
                    Callback<IRoutedEventHandler>([ellipseAsUIElement, isVisible](IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                    // Don't set the AutoImageSize on the ellipse as it makes the ellipse grow bigger than
                    // what it would be otherwise, just set the visibility when we get the image
                    if (isVisible)
                    {
                        RETURN_IF_FAILED(ellipseAsUIElement->put_Visibility(Visibility::Visibility_Visible));
                    }
                    return S_OK;
                })
                    .Get(),
                    &eventToken));
            }
        }
    }

    template<typename T>
    void XamlBuilder::SetAutoSize(T* destination, IInspectable* parentElement, IInspectable* imageContainer, bool isVisible, bool imageFiresOpenEvent)
    {
        if (parentElement != nullptr && m_enableXamlImageHandling)
        {
            ComPtr<IInspectable> container(imageContainer);
            ComPtr<IFrameworkElement> frameworkElement;
            THROW_IF_FAILED(container.As(&frameworkElement));

            ComPtr<IImage> xamlImage(destination);
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
                ComPtr<IInspectable> strongParentElement(parentElement);
                EventRegistrationToken eventToken;
                THROW_IF_FAILED(xamlImage->add_ImageOpened(
                    Callback<IRoutedEventHandler>([frameworkElement, strongParentElement, imageSourceAsBitmap, isVisible](IInspectable* /*sender*/, IRoutedEventArgs *
                        /*args*/) -> HRESULT {
                    return SetAutoImageSize(frameworkElement.Get(), strongParentElement.Get(), imageSourceAsBitmap.Get(), isVisible);
                })
                    .Get(),
                    &eventToken));
            }
            else
            {
                SetAutoImageSize(frameworkElement.Get() , parentElement, imageSourceAsBitmap.Get(), isVisible);
            }
        }
    }

    void XamlBuilder::BuildImage(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                 _In_ IAdaptiveRenderContext* renderContext,
                                 _In_ IAdaptiveRenderArgs* renderArgs,
                                 _Outptr_ IUIElement** imageControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(cardElement.As(&adaptiveImage));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        HSTRING url;
        THROW_IF_FAILED(adaptiveImage->get_Url(&url));

        ComPtr<IUriRuntimeClass> imageUrl;
        GetUrlFromString(hostConfig.Get(), url, imageUrl.GetAddressOf());

        if (imageUrl == nullptr)
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::AssetLoadFailed,
                                      HStringReference(L"Image not found").Get());
            *imageControl = nullptr;
            return;
        }

        UINT32 pixelWidth = 0, pixelHeight = 0;
        THROW_IF_FAILED(adaptiveImage->get_PixelWidth(&pixelWidth));
        THROW_IF_FAILED(adaptiveImage->get_PixelHeight(&pixelHeight));
        bool hasExplicitMeasurements = (pixelWidth || pixelHeight);
        bool isAspectRatioNeeded = (pixelWidth && pixelHeight);

        // Get the image's size and style
        ABI::AdaptiveNamespace::ImageSize size = ABI::AdaptiveNamespace::ImageSize::None;
        if (!hasExplicitMeasurements)
        {
            THROW_IF_FAILED(adaptiveImage->get_Size(&size));
        }

        if (size == ABI::AdaptiveNamespace::ImageSize::None && !hasExplicitMeasurements)
        {
            ComPtr<IAdaptiveImageConfig> imageConfig;
            THROW_IF_FAILED(hostConfig->get_Image(&imageConfig));
            THROW_IF_FAILED(imageConfig->get_ImageSize(&size));
        }

        ABI::AdaptiveNamespace::ImageStyle imageStyle;
        THROW_IF_FAILED(adaptiveImage->get_Style(&imageStyle));
        ComPtr<IAdaptiveCardResourceResolvers> resourceResolvers;
        THROW_IF_FAILED(renderContext->get_ResourceResolvers(&resourceResolvers));

        HSTRING backgroundColor;
        THROW_IF_FAILED(adaptiveImage->get_BackgroundColor(&backgroundColor));

        boolean isVisible;
        THROW_IF_FAILED(adaptiveCardElement->get_IsVisible(&isVisible));

        ComPtr<IFrameworkElement> frameworkElement;
        if (imageStyle == ImageStyle_Person)
        {
            ComPtr<IEllipse> ellipse =
                XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));
            ComPtr<IEllipse> backgroundEllipse =
                XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));

            Stretch stretch = (isAspectRatioNeeded) ? Stretch::Stretch_Fill : Stretch::Stretch_UniformToFill;
            bool mustHideElement{true};

            ComPtr<IInspectable> parentElement;
            THROW_IF_FAILED(renderArgs->get_ParentElement(&parentElement));

            ComPtr<IShape> ellipseAsShape;
            THROW_IF_FAILED(ellipse.As(&ellipseAsShape));

            SetImageOnUIElement(imageUrl.Get(), ellipse.Get(), resourceResolvers.Get(),
                               (size == ABI::AdaptiveNamespace::ImageSize_Auto),
                               parentElement.Get(), ellipseAsShape.Get(), isVisible, &mustHideElement, stretch);

            ComPtr<IShape> backgroundEllipseAsShape;
            THROW_IF_FAILED(backgroundEllipse.As(&backgroundEllipseAsShape));

            // Set Auto, None, and Stretch to Stretch_UniformToFill. An ellipse set to Stretch_Uniform ends up with size 0.
            if (size == ABI::AdaptiveNamespace::ImageSize::None || size == ABI::AdaptiveNamespace::ImageSize::Stretch ||
                size == ABI::AdaptiveNamespace::ImageSize::Auto || hasExplicitMeasurements)
            {
                THROW_IF_FAILED(ellipseAsShape->put_Stretch(stretch));
                THROW_IF_FAILED(backgroundEllipseAsShape->put_Stretch(stretch));
            }
            
            if (backgroundColor != nullptr)
            {
                // Fill the background ellipse with solid color brush
                ABI::Windows::UI::Color color;
                THROW_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor), &color));
                ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(color);
                THROW_IF_FAILED(backgroundEllipseAsShape->put_Fill(backgroundColorBrush.Get()));

                // Create a grid to contain the background color ellipse and the image ellipse
                ComPtr<IGrid> imageGrid =
                    XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));

                ComPtr<IPanel> panel;
                THROW_IF_FAILED(imageGrid.As(&panel));

                XamlHelpers::AppendXamlElementToPanel(backgroundEllipse.Get(), panel.Get());
                XamlHelpers::AppendXamlElementToPanel(ellipse.Get(), panel.Get());

                THROW_IF_FAILED(imageGrid.As(&frameworkElement));
            }
            else
            {
                THROW_IF_FAILED(ellipse.As(&frameworkElement));
            }
        }
        else
        {
            ComPtr<IImage> xamlImage =
                XamlHelpers::CreateXamlClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));

            
            if (backgroundColor != nullptr)
            {
                // Create a surronding border with solid color background to contain the image
                ComPtr<IBorder> border =
                    XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));

                ABI::Windows::UI::Color color;
                THROW_IF_FAILED(GetColorFromString(HStringToUTF8(backgroundColor), &color));
                ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(color);
                THROW_IF_FAILED(border->put_Background(backgroundColorBrush.Get()));

                ComPtr<IUIElement> imageAsUiElement;
                THROW_IF_FAILED(xamlImage.CopyTo(imageAsUiElement.GetAddressOf()));
                THROW_IF_FAILED(border->put_Child(imageAsUiElement.Get()));

                THROW_IF_FAILED(border.As(&frameworkElement));
            }
            else
            {
                THROW_IF_FAILED(xamlImage.As(&frameworkElement));
            }

            if (isAspectRatioNeeded)
            {
                xamlImage->put_Stretch(Stretch::Stretch_Fill);
            }

            ComPtr<IInspectable> parentElement;
            THROW_IF_FAILED(renderArgs->get_ParentElement(&parentElement));

            bool mustHideElement{true};
            SetImageOnUIElement(imageUrl.Get(), xamlImage.Get(), resourceResolvers.Get(),
                                (size == ABI::AdaptiveNamespace::ImageSize_Auto),
                                parentElement.Get(), frameworkElement.Get(), isVisible, &mustHideElement);
        }

        ComPtr<IAdaptiveImageSizesConfig> sizeOptions;
        THROW_IF_FAILED(hostConfig->get_ImageSizes(sizeOptions.GetAddressOf()));

        if (hasExplicitMeasurements)
        {
            if (pixelWidth)
            {
                THROW_IF_FAILED(frameworkElement->put_Width(pixelWidth));
            }

            if (pixelHeight)
            {
                THROW_IF_FAILED(frameworkElement->put_Height(pixelHeight));
            }
        }
        else
        {
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

        THROW_IF_FAILED(frameworkElement->put_VerticalAlignment(VerticalAlignment_Top));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Image", frameworkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        THROW_IF_FAILED(adaptiveImage->get_SelectAction(&selectAction));

        ComPtr<IUIElement> imageAsUIElement;
        THROW_IF_FAILED(frameworkElement.As(&imageAsUIElement));

        HString altText;
        THROW_IF_FAILED(adaptiveImage->get_AltText(altText.GetAddressOf()));

        ComPtr<IDependencyObject> imageAsDependencyObject;
        THROW_IF_FAILED(imageAsUIElement.As(&imageAsDependencyObject));

        ComPtr<IAutomationPropertiesStatics> automationPropertiesStatics;
        THROW_IF_FAILED(
            GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Automation_AutomationProperties).Get(),
                                 &automationPropertiesStatics));

        THROW_IF_FAILED(automationPropertiesStatics->SetName(imageAsDependencyObject.Get(), altText.Get()));

        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           imageAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           true,
                           imageControl);
    }

    void XamlBuilder::BuildContainer(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ IUIElement** containerControl)
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
        ABI::AdaptiveNamespace::HeightType containerHeightType{};
        THROW_IF_FAILED(cardElement->get_Height(&containerHeightType));
        if (containerHeightType == ABI::AdaptiveNamespace::HeightType::Auto)
        {
            THROW_IF_FAILED(containerPanelAsFrameWorkElement->put_VerticalAlignment(VerticalAlignment_Top));
        }

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        THROW_IF_FAILED(adaptiveContainer->get_Style(&containerStyle));

        ABI::AdaptiveNamespace::ContainerStyle parentContainerStyle;
        THROW_IF_FAILED(renderArgs->get_ContainerStyle(&parentContainerStyle));

        bool hasExplicitContainerStyle{true};
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

        ComPtr<IBorder> containerBorder =
            XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));
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

        ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment;
        THROW_IF_FAILED(adaptiveContainer->get_VerticalContentAlignment(&verticalContentAlignment));

        XamlBuilder::SetVerticalContentAlignmentToChildren(containerPanel.Get(), verticalContentAlignment);

        ComPtr<IUIElement> containerPanelAsUIElement;
        THROW_IF_FAILED(containerPanel.As(&containerPanelAsUIElement));
        THROW_IF_FAILED(containerBorder->put_Child(containerPanelAsUIElement.Get()));

        THROW_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Container", containerPanelAsFrameWorkElement.Get()));

        ComPtr<IAdaptiveActionElement> selectAction;
        THROW_IF_FAILED(adaptiveContainer->get_SelectAction(&selectAction));

        ComPtr<IUIElement> containerBorderAsUIElement;
        THROW_IF_FAILED(containerBorder.As(&containerBorderAsUIElement));

        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           containerBorderAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           true,
                           containerControl);
    }

    void XamlBuilder::BuildColumn(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                  _In_ IAdaptiveRenderContext* renderContext,
                                  _In_ IAdaptiveRenderArgs* renderArgs,
                                  _Outptr_ IUIElement** ColumnControl)
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

        ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment;
        THROW_IF_FAILED(adaptiveColumn->get_VerticalContentAlignment(&verticalContentAlignment));

        XamlBuilder::SetVerticalContentAlignmentToChildren(columnPanel.Get(), verticalContentAlignment);

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

        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           columnAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           false,
                           ColumnControl);
    }

    void XamlBuilder::BuildColumnSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ IUIElement** columnSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumnSet> adaptiveColumnSet;
        THROW_IF_FAILED(cardElement.As(&adaptiveColumnSet));

        ComPtr<WholeItemsPanel> gridContainer;
        THROW_IF_FAILED(MakeAndInitialize<WholeItemsPanel>(&gridContainer));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        THROW_IF_FAILED(adaptiveColumnSet->get_Style(&containerStyle));
        bool hasExplicitContainerStyle{ true };
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
            ComPtr<IPanel> columnSetAsPanel;
            THROW_IF_FAILED(gridContainer.As(&columnSetAsPanel));

            ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
            THROW_IF_FAILED(columnSetAsPanel->put_Background(backgroundColorBrush.Get()));
        }

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IVector<AdaptiveColumn*>> columns;
        THROW_IF_FAILED(adaptiveColumnSet->get_Columns(&columns));
        int currentColumn{};
        ComPtr<IAdaptiveElementRendererRegistration> elementRenderers;
        THROW_IF_FAILED(renderContext->get_ElementRenderers(&elementRenderers));
        ComPtr<IAdaptiveElementRenderer> columnRenderer;
        THROW_IF_FAILED(elementRenderers->Get(HStringReference(L"Column").Get(), &columnRenderer));

        if (columnRenderer == nullptr)
        {
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                                      HStringReference(L"No renderer found for type: Column").Get());
            *columnSetControl = nullptr;
            return;
        }
        
        XamlHelpers::IterateOverVector<AdaptiveColumn, IAdaptiveColumn>(
            columns.Get(),
            [xamlGrid, gridStatics, &currentColumn, renderContext, renderArgs, columnRenderer, hostConfig](IAdaptiveColumn* column) {
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
                    GetSeparationConfigForElement(
                        columnAsCardElement.Get(), hostConfig.Get(), &spacing, &separatorThickness, &separatorColor, &needsSeparator);

                    if (needsSeparator)
                    {
                        // Create a new ColumnDefinition for the separator
                        ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                        THROW_IF_FAILED(separatorColumnDefinition->put_Width({1.0, GridUnitType::GridUnitType_Auto}));
                        THROW_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

                        auto separator = CreateSeparator(renderContext, spacing, separatorThickness, separatorColor, false);
                        ComPtr<IFrameworkElement> separatorAsFrameworkElement;
                        THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));
                        gridStatics->SetColumn(separatorAsFrameworkElement.Get(), currentColumn++);
                        XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());
                    }
                }

                // Determine if the column is auto, stretch, or percentage width, and set the column width appropriately
                ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));

                HString adaptiveColumnWidth;
                THROW_IF_FAILED(column->get_Width(adaptiveColumnWidth.GetAddressOf()));

                INT32 isStretchResult;
                THROW_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"stretch").Get(), &isStretchResult));

                INT32 isAutoResult;
                THROW_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnWidth.Get(), HStringReference(L"auto").Get(), &isAutoResult));

                double widthAsDouble = _wtof(adaptiveColumnWidth.GetRawBuffer(nullptr));
                UINT32 pixelWidth = 0;
                THROW_IF_FAILED(localColumn->get_PixelWidth(&pixelWidth));

                GridLength columnWidth;
                if (pixelWidth)
                {
                    // If pixel width specified, use pixel width
                    columnWidth.GridUnitType = GridUnitType::GridUnitType_Pixel;
                    columnWidth.Value = pixelWidth;
                }
                else if (isStretchResult == 0 || !adaptiveColumnWidth.IsValid())
                {
                    // If stretch specified, use stretch with default of 1
                    columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
                    columnWidth.Value = 1;
                }
                else if ((isAutoResult == 0) || (widthAsDouble <= 0))
                {
                    // If auto specified or column width invalid or set to non-positive, use auto width
                    columnWidth.GridUnitType = GridUnitType::GridUnitType_Auto;
                    columnWidth.Value = 0;
                }
                else
                {
                    // If user specified specific valid width, use that star width
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
        THROW_IF_FAILED(columnSetAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Stretch));

        ComPtr<IAdaptiveActionElement> selectAction;
        THROW_IF_FAILED(adaptiveColumnSet->get_SelectAction(&selectAction));

        ComPtr<IPanel> gridContainerAsPanel;
        THROW_IF_FAILED(gridContainer.As(&gridContainerAsPanel));
        ComPtr<IUIElement> gridContainerAsUIElement;
        THROW_IF_FAILED(gridContainer.As(&gridContainerAsUIElement));

        ComPtr<IUIElement> gridAsUIElement;
        THROW_IF_FAILED(xamlGrid.As(&gridAsUIElement));

        ComPtr<IAdaptiveCardElement> columnSetAsCardElement;
        THROW_IF_FAILED(adaptiveColumnSet.As(&columnSetAsCardElement));

        ABI::AdaptiveNamespace::HeightType columnSetHeightType;
        THROW_IF_FAILED(columnSetAsCardElement->get_Height(&columnSetHeightType));

        XamlHelpers::AppendXamlElementToPanel(xamlGrid.Get(), gridContainerAsPanel.Get(), columnSetHeightType);
        HandleSelectAction(adaptiveCardElement,
                           selectAction.Get(),
                           renderContext,
                           gridContainerAsUIElement.Get(),
                           SupportsInteractivity(hostConfig.Get()),
                           true,
                           columnSetControl);
    }

    void XamlBuilder::BuildFactSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ IAdaptiveRenderContext* renderContext,
                                   _In_ IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ IUIElement** factSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveFactSet> adaptiveFactSet;

        THROW_IF_FAILED(cardElement.As(&adaptiveFactSet));

        ComPtr<IGrid> xamlGrid =
            XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        ComPtr<IColumnDefinition> titleColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        ComPtr<IColumnDefinition> valueColumn = XamlHelpers::CreateXamlClass<IColumnDefinition>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
        GridLength factSetGridTitleLength = {0, GridUnitType::GridUnitType_Auto};
        GridLength factSetGridValueLength = {1, GridUnitType::GridUnitType_Star};

        THROW_IF_FAILED(titleColumn->put_Width(factSetGridTitleLength));
        THROW_IF_FAILED(valueColumn->put_Width(factSetGridValueLength));
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
        THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
        THROW_IF_FAILED(columnDefinitions->Append(titleColumn.Get()));
        THROW_IF_FAILED(columnDefinitions->Append(valueColumn.Get()));

        GridLength factSetGridHeight = {0, GridUnitType::GridUnitType_Auto};
        ABI::AdaptiveNamespace::HeightType heightType;
        THROW_IF_FAILED(cardElement->get_Height(&heightType));
        if (heightType == ABI::AdaptiveNamespace::HeightType::Stretch)
        {
            factSetGridHeight = {1, GridUnitType::GridUnitType_Star};
        }

        ComPtr<IVector<AdaptiveFact*>> facts;
        THROW_IF_FAILED(adaptiveFactSet->get_Facts(&facts));
        int currentFact = 0;
        XamlHelpers::IterateOverVector<AdaptiveFact, IAdaptiveFact>(
            facts.Get(), [xamlGrid, gridStatics, factSetGridHeight, &currentFact, renderContext, renderArgs](IAdaptiveFact* fact) {
                ComPtr<IRowDefinition> factRow = XamlHelpers::CreateXamlClass<IRowDefinition>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
                THROW_IF_FAILED(factRow->put_Height(factSetGridHeight));

                ComPtr<IVector<RowDefinition*>> rowDefinitions;
                THROW_IF_FAILED(xamlGrid->get_RowDefinitions(&rowDefinitions));
                THROW_IF_FAILED(rowDefinitions->Append(factRow.Get()));

                ComPtr<IAdaptiveFact> localFact(fact);
                ComPtr<IAdaptiveHostConfig> hostConfig;
                THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));
                ComPtr<IAdaptiveFactSetConfig> factSetConfig;
                THROW_IF_FAILED(hostConfig->get_FactSet(&factSetConfig));

                // Get Language
                HString language;
                THROW_IF_FAILED(localFact->get_Language(language.GetAddressOf()));

                // Create the title xaml textblock and style it from Host options
                ComPtr<ITextBlock> titleTextBlock =
                    XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
                HString factTitle;
                THROW_IF_FAILED(localFact->get_Title(factTitle.GetAddressOf()));
                THROW_IF_FAILED(SetTextOnXamlTextBlock(renderContext,
                                                       factTitle.Get(),
                                                       ABI::AdaptiveNamespace::FontStyle::Default,
                                                       language.Get(),
                                                       titleTextBlock.Get()));

                ComPtr<IAdaptiveTextConfig> titleTextConfig;
                THROW_IF_FAILED(factSetConfig->get_Title(&titleTextConfig));

                ABI::AdaptiveNamespace::ContainerStyle containerStyle;
                THROW_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));
                StyleXamlTextBlock(titleTextConfig.Get(), containerStyle, titleTextBlock.Get(), hostConfig.Get());

                // Create the value xaml textblock and style it from Host options
                ComPtr<ITextBlock> valueTextBlock =
                    XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
                HString factValue;
                THROW_IF_FAILED(localFact->get_Value(factValue.GetAddressOf()));
                THROW_IF_FAILED(SetTextOnXamlTextBlock(renderContext,
                                                       factValue.Get(),
                                                       ABI::AdaptiveNamespace::FontStyle::Default,
                                                       language.Get(),
                                                       valueTextBlock.Get()));

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
                // Add spacing from hostconfig to right margin of title.
                titleTextBlockAsFrameWorkElement->put_Margin({0, 0, (double)spacing, 0});

                THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext,
                                                               L"Adaptive.Fact.Title",
                                                               titleTextBlockAsFrameWorkElement.Get()));
                THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext,
                                                               L"Adaptive.Fact.Value",
                                                               valueTextBlockAsFrameWorkElement.Get()));

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

    void XamlBuilder::BuildImageSet(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                    _In_ IAdaptiveRenderContext* renderContext,
                                    _In_ IAdaptiveRenderArgs* renderArgs,
                                    _Outptr_ IUIElement** imageSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImageSet> adaptiveImageSet;
        THROW_IF_FAILED(cardElement.As(&adaptiveImageSet));

        ComPtr<IVariableSizedWrapGrid> xamlGrid = XamlHelpers::CreateXamlClass<IVariableSizedWrapGrid>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_VariableSizedWrapGrid));

        THROW_IF_FAILED(xamlGrid->put_Orientation(Orientation_Horizontal));

        ComPtr<IVector<ABI::AdaptiveNamespace::AdaptiveImage*>> images;
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

            XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveImage, ABI::AdaptiveNamespace::IAdaptiveImage>(
                images.Get(),
                [imageSize, xamlGrid, renderContext, childRenderArgs, imageRenderer, imageSetConfig](IAdaptiveImage* adaptiveImage) {
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
            renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::NoRendererForType,
                                      HStringReference(L"No renderer found for type: Image").Get());
            *imageSetControl = nullptr;
            return;
        }

        ComPtr<IFrameworkElement> imageSetAsFrameworkElement;
        THROW_IF_FAILED(xamlGrid.As(&imageSetAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.ImageSet", imageSetAsFrameworkElement.Get()));

        THROW_IF_FAILED(xamlGrid.CopyTo(imageSetControl));
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

    void XamlBuilder::BuildCompactChoiceSetInput(_In_ IAdaptiveRenderContext* renderContext,
                                                 _In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                 _Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IComboBox> comboBox =
            XamlHelpers::CreateXamlClass<IComboBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBox));

        // Set HorizontalAlignment to Stretch (defaults to Left for combo boxes)
        ComPtr<IFrameworkElement> comboBoxAsFrameworkElement;
        THROW_IF_FAILED(comboBox.As(&comboBoxAsFrameworkElement));
        THROW_IF_FAILED(comboBoxAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));

        ComPtr<IItemsControl> itemsControl;
        THROW_IF_FAILED(comboBox.As(&itemsControl));

        ComPtr< IObservableVector<IInspectable*> > items;
        THROW_IF_FAILED(itemsControl->get_Items(items.GetAddressOf()));

        ComPtr< IVector<IInspectable*> > itemsVector;
        THROW_IF_FAILED(items.As(&itemsVector));

        ComPtr<IVector< ABI::AdaptiveNamespace::AdaptiveChoiceInput*> > choices;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        std::vector<std::string> values = GetChoiceSetValueVector(adaptiveChoiceSetInput);
        boolean wrap;
        adaptiveChoiceSetInput->get_Wrap(&wrap);

        int currentIndex = 0;
        int selectedIndex = -1;
        XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput, IAdaptiveChoiceInput>(
            choices.Get(), [&currentIndex, &selectedIndex, itemsVector, values, wrap](IAdaptiveChoiceInput* adaptiveChoiceInput) {
                HString title;
                THROW_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));

                ComPtr<IComboBoxItem> comboBoxItem = XamlHelpers::CreateXamlClass<IComboBoxItem>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBoxItem));

                XamlHelpers::SetContent(comboBoxItem.Get(), title.Get(), wrap);

                // If multiple values are specified, no option is selected
                if (values.size() == 1 && IsChoiceSelected(values, adaptiveChoiceInput))
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

    void XamlBuilder::BuildExpandedChoiceSetInput(_In_ IAdaptiveRenderContext* renderContext,
                                                  _In_ IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                                  boolean isMultiSelect,
                                                  _Outptr_ IUIElement** choiceInputSet)
    {
        ComPtr<IVector<AdaptiveChoiceInput*>> choices;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_Choices(&choices));

        ComPtr<IStackPanel> stackPanel =
            XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        stackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IPanel> panel;
        THROW_IF_FAILED(stackPanel.As(&panel));

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
                THROW_IF_FAILED(checkBox.As(&choiceItem));

                ComPtr<IFrameworkElement> frameworkElement;
                THROW_IF_FAILED(checkBox.As(&frameworkElement));
                SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Choice.Multiselect", frameworkElement.Get());

                XamlHelpers::SetToggleValue(choiceItem.Get(), IsChoiceSelected(values, adaptiveChoiceInput));
            }
            else
            {
                ComPtr<IRadioButton> radioButton = XamlHelpers::CreateXamlClass<IRadioButton>(
                    HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RadioButton));
                THROW_IF_FAILED(radioButton.As(&choiceItem));

                ComPtr<IFrameworkElement> frameworkElement;
                THROW_IF_FAILED(radioButton.As(&frameworkElement));
                SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Choice.SingleSelect", frameworkElement.Get());

                if (values.size() == 1)
                {
                    // When isMultiSelect is false, only 1 specified value is accepted.
                    // Otherwise, leave all options unset
                    XamlHelpers::SetToggleValue(choiceItem.Get(), IsChoiceSelected(values, adaptiveChoiceInput));
                }
            }

            HString title;
            THROW_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));
            XamlHelpers::SetContent(choiceItem.Get(), title.Get(), wrap);

            THROW_IF_FAILED(AddHandledTappedEvent(choiceItem.Get()));

            XamlHelpers::AppendXamlElementToPanel(choiceItem.Get(), panel.Get());
        });

        ComPtr<IFrameworkElement> choiceSetAsFrameworkElement;
        THROW_IF_FAILED(stackPanel.As(&choiceSetAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext,
                                                       L"Adaptive.Input.ChoiceSet.Expanded",
                                                       choiceSetAsFrameworkElement.Get()));

        THROW_IF_FAILED(stackPanel.CopyTo(choiceInputSet));
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

    void XamlBuilder::BuildChoiceSetInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                          _In_ IAdaptiveRenderContext* renderContext,
                                          _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                          _Outptr_ IUIElement** choiceInputSet)
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

        if (choiceSetStyle == ABI::AdaptiveNamespace::ChoiceSetStyle_Compact && !isMultiSelect)
        {
            BuildCompactChoiceSetInput(renderContext, adaptiveChoiceSetInput.Get(), choiceInputSet);
        }
        else
        {
            BuildExpandedChoiceSetInput(renderContext, adaptiveChoiceSetInput.Get(), isMultiSelect, choiceInputSet);
        }

        AddInputValueToContext(renderContext, adaptiveCardElement, *choiceInputSet);
    }

    void XamlBuilder::BuildDateInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                     _Outptr_ IUIElement** dateInputControl)
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

        ComPtr<ICalendarDatePicker> datePicker = XamlHelpers::CreateXamlClass<ICalendarDatePicker>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CalendarDatePicker));

        HString placeHolderText;
        THROW_IF_FAILED(adaptiveDateInput->get_Placeholder(placeHolderText.GetAddressOf()));
        THROW_IF_FAILED(datePicker->put_PlaceholderText(placeHolderText.Get()));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> datePickerAsFrameworkElement;
        THROW_IF_FAILED(datePicker.As(&datePickerAsFrameworkElement));
        THROW_IF_FAILED(datePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
        THROW_IF_FAILED(datePickerAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Top));

        THROW_IF_FAILED(datePicker.CopyTo(dateInputControl));

        THROW_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Date", datePickerAsFrameworkElement.Get()));

        AddInputValueToContext(renderContext, adaptiveCardElement, *dateInputControl);

        // TODO: Handle parsing dates for min/max and value
    }

    void XamlBuilder::BuildNumberInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                       _In_ IAdaptiveRenderContext* renderContext,
                                       _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                       _Outptr_ IUIElement** numberInputControl)
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

        ComPtr<ITextBox> textBox =
            XamlHelpers::CreateXamlClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

        ComPtr<IInputScopeName> inputScopeName =
            XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
        THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Number));

        ComPtr<IInputScope> inputScope =
            XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
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
        THROW_IF_FAILED(frameworkElement->put_VerticalAlignment(VerticalAlignment_Top));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Number", frameworkElement.Get()));

        // TODO: Handle max and min?
        THROW_IF_FAILED(textBox.CopyTo(numberInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *numberInputControl);
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
                                      _In_ IAdaptiveHostConfig* hostConfig,
                                      _In_ IAdaptiveActionElement* action,
                                      const std::wstring& warning)
    {
        if (action != nullptr)
        {
            ABI::AdaptiveNamespace::ActionType actionType;
            THROW_IF_FAILED(action->get_ActionType(&actionType));

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
                    THROW_IF_FAILED(renderContext->AddWarning(ABI::AdaptiveNamespace::WarningStatusCode::UnsupportedValue,
                                                              HStringReference(warning.c_str()).Get()));
                    return true;
                }
            }
        }

        return false;
    }

    void XamlBuilder::HandleInlineAcion(_In_ IAdaptiveRenderContext* renderContext,
                                        _In_ IAdaptiveRenderArgs* renderArgs,
                                        _In_ ITextBox* textBox,
                                        _In_ IAdaptiveActionElement* inlineAction,
                                        _Outptr_ IUIElement** textBoxWithInlineAction)
    {
        ComPtr<ITextBox> localTextBox(textBox);
        ComPtr<IAdaptiveActionElement> localInlineAction(inlineAction);

        ABI::AdaptiveNamespace::ActionType actionType;
        THROW_IF_FAILED(localInlineAction->get_ActionType(&actionType));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        // Inline ShowCards are not supported for inline actions
        if (WarnForInlineShowCard(renderContext, hostConfig.Get(), localInlineAction.Get(), L"Inline ShowCard not supported for InlineAction"))
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
            THROW_IF_FAILED(textBlockAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Center));

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
            Callback<IRoutedEventHandler>(
                [actionUIElement, textBoxAsFrameworkElement](IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                    ComPtr<IFrameworkElement> actionFrameworkElement;
                    RETURN_IF_FAILED(actionUIElement.As(&actionFrameworkElement));

                    return SetMatchingHeight(actionFrameworkElement.Get(), textBoxAsFrameworkElement.Get());
                })
                .Get(),
            &eventToken));

        // Wrap the action in a button
        ComPtr<IUIElement> touchTargetUIElement;
        WrapInTouchTarget(nullptr, actionUIElement.Get(), localInlineAction.Get(), renderContext, false, L"Adaptive.Input.Text.InlineAction", &touchTargetUIElement);

        ComPtr<IFrameworkElement> touchTargetFrameworkElement;
        THROW_IF_FAILED(touchTargetUIElement.As(&touchTargetFrameworkElement));

        // Align to bottom so the icon stays with the bottom of the text box as it grows in the multiline case
        THROW_IF_FAILED(touchTargetFrameworkElement->put_VerticalAlignment(VerticalAlignment_Bottom));

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
                })
                    .Get(),
                &keyDownEventToken));
        }

        THROW_IF_FAILED(xamlGrid.CopyTo(textBoxWithInlineAction));
    }

    void XamlBuilder::BuildTextInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ IUIElement** textInputControl)
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

        ComPtr<ITextBox> textBox =
            XamlHelpers::CreateXamlClass<ITextBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBox));

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

        ComPtr<IInputScopeName> inputScopeName =
            XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
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

        ComPtr<IInputScope> inputScope =
            XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
        ComPtr<IVector<InputScopeName*>> names;
        THROW_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
        THROW_IF_FAILED(names->Append(inputScopeName.Get()));

        THROW_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

        ComPtr<IUIElement> textBoxAsUIElement;
        textBox.As(&textBoxAsUIElement);
        AddInputValueToContext(renderContext, adaptiveCardElement, textBoxAsUIElement.Get());

        ComPtr<IAdaptiveActionElement> inlineAction;
        THROW_IF_FAILED(adaptiveTextInput->get_InlineAction(&inlineAction));

        ComPtr<IFrameworkElement> textBoxAsFrameworkElement;
        THROW_IF_FAILED(textBox.As(&textBoxAsFrameworkElement));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Text", textBoxAsFrameworkElement.Get()));

        if (inlineAction != nullptr)
        {
            ComPtr<IUIElement> textBoxWithInlineAction;
            HandleInlineAcion(renderContext, renderArgs, textBox.Get(), inlineAction.Get(), &textBoxWithInlineAction);
            if (!isMultiLine)
            {
                THROW_IF_FAILED(textBoxWithInlineAction.As(&textBoxAsFrameworkElement));
                THROW_IF_FAILED(textBoxAsFrameworkElement->put_VerticalAlignment(VerticalAlignment::VerticalAlignment_Top));
            }

            THROW_IF_FAILED(textBoxWithInlineAction.CopyTo(textInputControl));
        }
        else
        {
            if (!isMultiLine)
            {
                THROW_IF_FAILED(textBoxAsFrameworkElement->put_VerticalAlignment(VerticalAlignment::VerticalAlignment_Top));
            }

            THROW_IF_FAILED(textBox.CopyTo(textInputControl));
        }
    }

    void XamlBuilder::BuildTimeInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                     _Outptr_ IUIElement** timeInputControl)
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

        ComPtr<ITimePicker> timePicker =
            XamlHelpers::CreateXamlClass<ITimePicker>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TimePicker));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> timePickerAsFrameworkElement;
        THROW_IF_FAILED(timePicker.As(&timePickerAsFrameworkElement));
        THROW_IF_FAILED(timePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
        THROW_IF_FAILED(timePickerAsFrameworkElement->put_VerticalAlignment(VerticalAlignment_Top));

        THROW_IF_FAILED(
            SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Time", timePickerAsFrameworkElement.Get()));

        // TODO: Handle placeholder text and parsing times for min/max and value

        THROW_IF_FAILED(timePicker.CopyTo(timeInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *timeInputControl);
    }

    void XamlBuilder::BuildToggleInput(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                       _In_ IAdaptiveRenderContext* renderContext,
                                       _In_ IAdaptiveRenderArgs* /*renderArgs*/,
                                       _Outptr_ IUIElement** toggleInputControl)
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

        ComPtr<ICheckBox> checkBox =
            XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));

        HString title;
        THROW_IF_FAILED(adaptiveToggleInput->get_Title(title.GetAddressOf()));

        boolean wrap;
        adaptiveToggleInput->get_Wrap(&wrap);

        XamlHelpers::SetContent(checkBox.Get(), title.Get(), wrap);

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
        THROW_IF_FAILED(frameworkElement->put_VerticalAlignment(VerticalAlignment_Top));
        THROW_IF_FAILED(SetStyleFromResourceDictionary(renderContext, L"Adaptive.Input.Toggle", frameworkElement.Get()));

        THROW_IF_FAILED(checkboxAsUIElement.CopyTo(toggleInputControl));
        AddInputValueToContext(renderContext, adaptiveCardElement, *toggleInputControl);
    }

    void XamlBuilder::BuildMedia(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                 _In_ IAdaptiveRenderContext* renderContext,
                                 _In_ IAdaptiveRenderArgs* renderArgs,
                                 _Outptr_ IUIElement** mediaControl)
    {
        ComPtr<IAdaptiveCardElement> localCardElement{adaptiveCardElement};
        ComPtr<IAdaptiveMedia> adaptiveMedia;
        THROW_IF_FAILED(localCardElement.As(&adaptiveMedia));

        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

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
                THROW_IF_FAILED(posterImage.CopyTo(mediaControl));
            }

            return;
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
        THROW_IF_FAILED(mediaStackPanel.As(&mediaPanel));

        XamlHelpers::AppendXamlElementToPanel(touchTargetUIElement.Get(), mediaPanel.Get());

        // Check if this host allows inline playback
        ComPtr<IAdaptiveMediaConfig> mediaConfig;
        THROW_IF_FAILED(hostConfig->get_Media(&mediaConfig));

        boolean allowInlinePlayback;
        THROW_IF_FAILED(mediaConfig->get_AllowInlinePlayback(&allowInlinePlayback));

        ComPtr<IAdaptiveMediaEventInvoker> mediaInvoker;
        THROW_IF_FAILED(renderContext->get_MediaEventInvoker(&mediaInvoker));

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
                return;
            }

            // Configure Auto Play and Controls
            THROW_IF_FAILED(mediaElement->put_AutoPlay(false));

            ComPtr<IMediaElement2> mediaElement2;
            THROW_IF_FAILED(mediaElement.As(&mediaElement2));
            THROW_IF_FAILED(mediaElement2->put_AreTransportControlsEnabled(true));

            ComPtr<IUIElement> mediaUIElement;
            THROW_IF_FAILED(mediaElement.As(&mediaUIElement));

            if (posterImage != nullptr)
            {
                // Set the poster on the media element
                ComPtr<IImageSource> posterImageSource;
                THROW_IF_FAILED(posterImage->get_Source(&posterImageSource));
                THROW_IF_FAILED(mediaElement->put_PosterSource(posterImageSource.Get()));
            }

            // Make the media element collapsed until the user clicks
            THROW_IF_FAILED(mediaUIElement->put_Visibility(Visibility_Collapsed));

            XamlHelpers::AppendXamlElementToPanel(mediaElement.Get(), mediaPanel.Get());
        }

        ComPtr<IUIElement> mediaPanelAsUIElement;
        THROW_IF_FAILED(mediaPanel.As(&mediaPanelAsUIElement));

        ComPtr<IButtonBase> touchTargetAsButtonBase;
        THROW_IF_FAILED(touchTargetUIElement.As(&touchTargetAsButtonBase));

        // Take a reference to the mime type string for the lambda
        HSTRING lambdaMimeType;
        WindowsDuplicateString(mimeType.Get(), &lambdaMimeType);
        ComPtr<IAdaptiveRenderContext> lambdaRenderContext{renderContext};

        EventRegistrationToken clickToken;
        THROW_IF_FAILED(touchTargetAsButtonBase->add_Click(
            Callback<IRoutedEventHandler>(
                [touchTargetUIElement, lambdaRenderContext, adaptiveMedia, mediaElement, mediaSourceUrl, lambdaMimeType, mediaInvoker](
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
                })
                .Get(),
            &clickToken));

        THROW_IF_FAILED(mediaPanelAsUIElement.CopyTo(mediaControl));
    }

    bool XamlBuilder::SupportsInteractivity(_In_ IAdaptiveHostConfig* hostConfig)
    {
        boolean supportsInteractivity;
        THROW_IF_FAILED(hostConfig->get_SupportsInteractivity(&supportsInteractivity));
        return Boolify(supportsInteractivity);
    }

    void XamlBuilder::WrapInTouchTarget(_In_ IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ IUIElement* elementToWrap,
                                        _In_ IAdaptiveActionElement* action,
                                        _In_ IAdaptiveRenderContext* renderContext,
                                        bool fullWidth,
                                        const std::wstring& style,
                                        _Outptr_ IUIElement** finalElement)
    {
        ComPtr<IAdaptiveHostConfig> hostConfig;
        THROW_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

        if (WarnForInlineShowCard(renderContext, hostConfig.Get(), action, L"Inline ShowCard not supported for SelectAction"))
        {
            // Was inline show card, so don't wrap the element and just return
            ComPtr<IUIElement> localElementToWrap(elementToWrap);
            localElementToWrap.CopyTo(finalElement);
            return;
        }

        ComPtr<IButton> button =
            XamlHelpers::CreateXamlClass<IButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Button));

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
                                         _Outptr_ IUIElement** outUiElement)
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
        THROW_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>(
                                                  [strongAction, actionInvoker](IInspectable* /*sender*/, IRoutedEventArgs * /*args*/) -> HRESULT {
                                                      THROW_IF_FAILED(actionInvoker->SendActionEvent(strongAction.Get()));
                                                      return S_OK;
                                                  })
                                                  .Get(),
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
                                     })
                                         .Get(),
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
