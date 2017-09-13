#include "pch.h"

#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveImage.h"
#include "AdaptiveActionEventArgs.h"
#include "DefaultResourceDictionary.h"
#include <windows.foundation.collections.h>
#include <windows.storage.h>
#include <windows.ui.xaml.markup.h>
#include <windows.ui.xaml.shapes.h>
#include <windows.web.http.h>
#include <windows.web.http.filters.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "XamlStyleKeyGenerators.h"
#include "json/json.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage;
using namespace ABI::Windows::Storage::Streams;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Text;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;
using namespace ABI::Windows::UI::Xaml::Shapes;
using namespace ABI::Windows::UI::Xaml::Input;
using namespace ABI::Windows::Web::Http;
using namespace ABI::Windows::Web::Http::Filters;

const PCWSTR c_TextBlockSubtleOpacityKey = L"TextBlock.SubtleOpacity";
const PCWSTR c_BackgroundImageOverlayBrushKey = L"AdaptiveCard.BackgroundOverlayBrush";

namespace AdaptiveCards { namespace XamlCardRenderer
{
    XamlBuilder::XamlBuilder()
    {
        // Populate the map of element types to their builder methods
        m_adaptiveElementBuilder[ElementType::TextBlock] = std::bind(&XamlBuilder::BuildTextBlock, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::Image] = std::bind(&XamlBuilder::BuildImage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::Container] = std::bind(&XamlBuilder::BuildContainer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::ColumnSet] = std::bind(&XamlBuilder::BuildColumnSet, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::FactSet] = std::bind(&XamlBuilder::BuildFactSet, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::ImageSet] = std::bind(&XamlBuilder::BuildImageSet, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::ChoiceSetInput] = std::bind(&XamlBuilder::BuildChoiceSetInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::DateInput] = std::bind(&XamlBuilder::BuildDateInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::NumberInput] = std::bind(&XamlBuilder::BuildNumberInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::TextInput] = std::bind(&XamlBuilder::BuildTextInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::TimeInput] = std::bind(&XamlBuilder::BuildTimeInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_adaptiveElementBuilder[ElementType::ToggleInput] = std::bind(&XamlBuilder::BuildToggleInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

        m_hostConfig = Make<AdaptiveHostConfig>();

        m_imageLoadTracker.AddListener(dynamic_cast<IImageLoadTrackerListener*>(this));

        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_RandomAccessStream).Get(), &m_randomAccessStreamStatics));
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(), &m_propertyValueStatics));
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Text_FontWeights).Get(), &m_fontWeightsStatics));

        InitializeDefaultResourceDictionary();
    }

    _Use_decl_annotations_
    ComPtr<IUIElement> XamlBuilder::CreateSeparator(
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
        IUIElement** xamlTreeRoot, 
        XamlCardRenderer* renderer,
        boolean isOuterCard)
    {
        *xamlTreeRoot = nullptr;

        ComPtr<IPanel> childElementContainer;
        ComPtr<IUIElement> rootElement = CreateRootCardElement(adaptiveCard, &childElementContainer);

        // Enumerate the child items of the card and build xaml for them
        ComPtr<IVector<IAdaptiveCardElement*>> body;
        THROW_IF_FAILED(adaptiveCard->get_Body(&body));

        std::shared_ptr<std::vector<InputItem>> inputElements = std::make_shared<std::vector<InputItem>>();
        BuildPanelChildren(body.Get(), childElementContainer.Get(), inputElements, [](IUIElement*) {});

        if (this->SupportsInteractivity())
        {
            ComPtr<IVector<IAdaptiveActionElement*>> actions;
            THROW_IF_FAILED(adaptiveCard->get_Actions(&actions));
            unsigned int bodyCount;
            THROW_IF_FAILED(body->get_Size(&bodyCount));
            BuildActions(actions.Get(), renderer, inputElements, childElementContainer.Get(), bodyCount > 0);
        }

        THROW_IF_FAILED(rootElement.CopyTo(xamlTreeRoot));

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

    HRESULT XamlBuilder::SetRenderOptions(_In_ RenderOptions renderOptions) noexcept
    {
        m_renderOptions = renderOptions;
        return S_OK;
    }

    HRESULT XamlBuilder::SetEnableXamlImageHandling(_In_ bool enableXamlImageHandling) noexcept
    {
        m_enableXamlImageHandling = enableXamlImageHandling;
        return S_OK;
    }

    HRESULT XamlBuilder::SetOverrideDictionary(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary) noexcept try
    {
        if (overrideDictionary != nullptr)
        {
            m_mergedResourceDictionary = overrideDictionary;
            ComPtr<IVector<ResourceDictionary*>> mergedDictionaries;
            m_mergedResourceDictionary->get_MergedDictionaries(&mergedDictionaries);
            mergedDictionaries->Append(m_defaultResourceDictionary.Get());
        }
        return S_OK;
    } CATCH_RETURN;

    HRESULT XamlBuilder::SetHostConfig(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* hostConfig) noexcept try
    {
        m_hostConfig = hostConfig;
        return S_OK;
    } CATCH_RETURN;

    void XamlBuilder::InitializeDefaultResourceDictionary()
    {
        ComPtr<IXamlReaderStatics> xamlReaderStatics;
        THROW_IF_FAILED(RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Markup_XamlReader).Get(),
            __uuidof(IXamlReaderStatics), reinterpret_cast<void**>(xamlReaderStatics.GetAddressOf())));

        ComPtr<IInspectable> resourceDictionaryInspectable;
        THROW_IF_FAILED(xamlReaderStatics->Load(HStringReference(c_defaultResourceDictionary).Get(), &resourceDictionaryInspectable));
        ComPtr<IResourceDictionary> resourceDictionary;
        THROW_IF_FAILED(resourceDictionaryInspectable.As(&resourceDictionary));

        m_defaultResourceDictionary = resourceDictionary;
        m_mergedResourceDictionary = resourceDictionary;
    }

    _Use_decl_annotations_
    template<typename T>
    HRESULT XamlBuilder::TryGetResoureFromResourceDictionaries(std::wstring resourceName, T** style)
    {
        *style = nullptr;
        try
        {
            // Get a resource key for the requested style that we can use for ResourceDistionary Lookups
            ComPtr<IInspectable> resourceKey;
            THROW_IF_FAILED(m_propertyValueStatics->CreateString(HStringReference(resourceName.c_str()).Get(), resourceKey.GetAddressOf()));

            // Search for the named resource
            ComPtr<IInspectable> dictionaryValue;
            ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;
            if (SUCCEEDED(m_mergedResourceDictionary.As(&resourceDictionaryMap)) &&
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

    template<typename T>
    bool XamlBuilder::TryGetValueResourceFromResourceDictionaries(
        _In_ std::wstring styleName,
        _Out_ T* valueResource)
    {
        try
        {
            // Get a resource key for the requested style that we can use for ResourceDictionary Lookups
            ComPtr<IInspectable> resourceKey;
            THROW_IF_FAILED(m_propertyValueStatics->CreateString(HStringReference(styleName.c_str()).Get(), resourceKey.GetAddressOf()));

            // Search for the named resource
            ComPtr<IInspectable> dictionaryValue;
            ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;
            if (SUCCEEDED(m_mergedResourceDictionary.As(&resourceDictionaryMap)) &&
                SUCCEEDED(resourceDictionaryMap->Lookup(resourceKey.Get(), dictionaryValue.GetAddressOf())))
            {
                ComPtr<T> resourceToReturn;
                if (SUCCEEDED(dictionaryValue.As(&styleToReturn)))
                {
                    THROW_IF_FAILED(styleToReturn.CopyTo(style));
                    return true;
                }
            }
        }
        catch (...)
        {
        }
        return false;
    }

    _Use_decl_annotations_
    ComPtr<IUIElement> XamlBuilder::CreateRootCardElement(IAdaptiveCard* adaptiveCard, IPanel** childElementContainer)
    {
        // The root of an adaptive card is a composite of several elements, depending on the card
        // properties.  From back to fron these are:
        // Grid - Root element, used to enable children to stack above each other and size to fit
        // Image (optional) - Holds the background image if one is set
        // Shape (optional) - Provides the background image overlay, if one is set
        // StackPanel - The container for all the card's body elements
        ComPtr<IGrid> rootElement = XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IAdaptiveCardConfig> adaptiveCardConfig;
        THROW_IF_FAILED(m_hostConfig->get_AdaptiveCard(&adaptiveCardConfig));

        ComPtr<IPanel> rootAsPanel;
        THROW_IF_FAILED(rootElement.As(&rootAsPanel));
        ABI::Windows::UI::Color backgroundColor;
        if (SUCCEEDED(adaptiveCardConfig->get_BackgroundColor(&backgroundColor)))
        {
            ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
            THROW_IF_FAILED(rootAsPanel->put_Background(backgroundColorBrush.Get()));
        }

        ComPtr<IUriRuntimeClass> backgroundImageUrl;
        if (SUCCEEDED(adaptiveCard->get_BackgroundImage(&backgroundImageUrl)))
        {
            ApplyBackgroundToRoot(rootAsPanel.Get(), backgroundImageUrl.Get());
        }

        // Now create the inner stack panel to serve as the root host for all the 
        // body elements and apply padding from host configuration
        ComPtr<IStackPanel> bodyElementHost = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        ComPtr<IFrameworkElement> bodyElementHostAsElement;
        THROW_IF_FAILED(bodyElementHost.As(&bodyElementHostAsElement));
        ComPtr<IAdaptiveSpacingDefinition> cardPadding;
        THROW_IF_FAILED(adaptiveCardConfig->get_Padding(&cardPadding));
        ApplyMarginToXamlElement(cardPadding.Get(), bodyElementHostAsElement.Get());

        XamlHelpers::AppendXamlElementToPanel(bodyElementHost.Get(), rootAsPanel.Get());
        THROW_IF_FAILED(bodyElementHost.CopyTo(childElementContainer));

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
    void XamlBuilder::ApplyBackgroundToRoot(ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel, ABI::Windows::Foundation::IUriRuntimeClass* url)
    {
        // In order to reuse the image creation code paths, we simply create an adaptive card
        // image element and then build that into xaml and apply to the root.
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveImage>(&adaptiveImage));
        adaptiveImage->put_Url(url);
        adaptiveImage->put_Size(ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Auto);

        ComPtr<IAdaptiveCardElement> adaptiveCardElement;
        THROW_IF_FAILED(adaptiveImage.As(&adaptiveCardElement));
        ComPtr<IUIElement> backgroundImage;
        BuildImage(adaptiveCardElement.Get(), nullptr, &backgroundImage);
        XamlHelpers::AppendXamlElementToPanel(backgroundImage.Get(), rootPanel);

        // The overlay applied to the background image is determined by a resouce, so create
        // the overlay if that resources exists
        ComPtr<IBrush> backgroundOverlayBrush;
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IBrush>(c_BackgroundImageOverlayBrushKey, &backgroundOverlayBrush)))
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
    void XamlBuilder::SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUri, T* uiElement)
    {
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
        std::shared_ptr<std::vector<InputItem>> inputElements,
        std::function<void(IUIElement* child)> childCreatedCallback)
    {
        int currentElement = 0;
        unsigned int childrenSize;
        THROW_IF_FAILED(children->get_Size(&childrenSize));
        XamlHelpers::IterateOverVector<IAdaptiveCardElement>(children, [&](IAdaptiveCardElement* element)
        {
            ElementType elementType;
            THROW_IF_FAILED(element->get_ElementType(&elementType));
            if (m_adaptiveElementBuilder.find(elementType) != m_adaptiveElementBuilder.end())
            {
                // First element does not need a separator added
                if (currentElement++ > 0)
                {
                    bool needsSeparator;
                    UINT spacing;
                    UINT separatorThickness;
                    ABI::Windows::UI::Color separatorColor;
                    GetSeparationConfigForElement(element, &spacing, &separatorThickness, &separatorColor, &needsSeparator);
                    if (needsSeparator)
                    {
                        auto separator = CreateSeparator(spacing, separatorThickness, separatorColor);
                        XamlHelpers::AppendXamlElementToPanel(separator.Get(), parentPanel);
                    }
                }
                ComPtr<IUIElement> newControl;
                m_adaptiveElementBuilder[elementType](element, inputElements, &newControl);
                XamlHelpers::AppendXamlElementToPanel(newControl.Get(), parentPanel);
                childCreatedCallback(newControl.Get());
            }
        });
    }

    void XamlBuilder::BuildShowCard(
        XamlCardRenderer* renderer,
        IAdaptiveShowCardActionConfig* showCardActionConfig,
        IAdaptiveActionElement* action,
        IUIElement** uiShowCard)
    {
        ComPtr<IAdaptiveActionElement> localAction(action);
        ComPtr<IAdaptiveShowCardAction> showCardAction;
        THROW_IF_FAILED(localAction.As(&showCardAction));

        ComPtr<IAdaptiveCard> showCard;
        THROW_IF_FAILED(showCardAction->get_Card(showCard.GetAddressOf()));

        ComPtr<IUIElement> localUiShowCard;
        BuildXamlTreeFromAdaptiveCard(showCard.Get(), localUiShowCard.GetAddressOf(), renderer, false);

        ComPtr<IGrid2> showCardGrid;
        THROW_IF_FAILED(localUiShowCard.As(&showCardGrid));

        // Set the padding
        ComPtr<IAdaptiveSpacingDefinition> cardPadding;
        THROW_IF_FAILED(showCardActionConfig->get_Padding(&cardPadding));

        UINT32 top, bottom;
        THROW_IF_FAILED(cardPadding->get_Top(&top));
        THROW_IF_FAILED(cardPadding->get_Bottom(&bottom));

        ABI::AdaptiveCards::XamlCardRenderer::ActionMode showCardActionMode;
        THROW_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        UINT32 left = 0;
        UINT32 right = 0;
        if (showCardActionMode != ActionMode_InlineEdgeToEdge)
        {
            THROW_IF_FAILED(cardPadding->get_Left(&left));
            THROW_IF_FAILED(cardPadding->get_Right(&right));
        }

        Thickness padding = { (double)left, (double)top, (double)right, (double)bottom };
        THROW_IF_FAILED(showCardGrid->put_Padding(padding));

        // Set the top margin
        ComPtr<IFrameworkElement> showCardFrameworkElement;
        THROW_IF_FAILED(localUiShowCard.As(&showCardFrameworkElement));

        UINT32 inlineTopMargin;
        THROW_IF_FAILED(showCardActionConfig->get_InlineTopMargin(&inlineTopMargin));
        Thickness margin = { 0, (double)inlineTopMargin, 0, 0 };
        THROW_IF_FAILED(showCardFrameworkElement->put_Margin(margin));

        // Set the background color
        ABI::Windows::UI::Color backgroundColor;
        THROW_IF_FAILED(showCardActionConfig->get_BackgroundColor(&backgroundColor));
        ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
        ComPtr<IPanel> showCardAsPanel;
        THROW_IF_FAILED(localUiShowCard.As(&showCardAsPanel));
        THROW_IF_FAILED(showCardAsPanel->put_Background(backgroundColorBrush.Get()));

        // Set the visibility as Collapsed until the action is triggered
        THROW_IF_FAILED(localUiShowCard->put_Visibility(Visibility_Collapsed));

        *uiShowCard = localUiShowCard.Detach();
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildActions(
        IVector<IAdaptiveActionElement*>* children,
        XamlCardRenderer* renderer,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IPanel* parentPanel,
        bool insertSeparator)
    {
        ComPtr<IAdaptiveActionsConfig> actionsConfig;
        THROW_IF_FAILED(m_hostConfig->get_Actions(actionsConfig.GetAddressOf()));

        // Create a separator between the body and the actions
        if (insertSeparator)
        {
            ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing;
            THROW_IF_FAILED(actionsConfig->get_Spacing(&spacing)); 

            UINT spacingSize;
            THROW_IF_FAILED(GetSpacingSizeFromSpacing(m_hostConfig.Get(), spacing, &spacingSize));

            ABI::Windows::UI::Color color = { 0 };
            auto separator = CreateSeparator(spacingSize, 0, color);
            XamlHelpers::AppendXamlElementToPanel(separator.Get(), parentPanel);
        }

        ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment actionAlignment;
        THROW_IF_FAILED(actionsConfig->get_ActionAlignment(&actionAlignment));

        ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation actionsOrientation;
        THROW_IF_FAILED(actionsConfig->get_ActionsOrientation(&actionsOrientation));

        // Declare the panel that will host the buttons
        ComPtr<IPanel> actionsPanel;
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;

        if (actionAlignment == ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Stretch &&
            actionsOrientation == ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation::Horizontal)
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

            auto uiOrientation = (actionsOrientation == ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation::Horizontal) ?
                Orientation::Orientation_Horizontal :
                Orientation::Orientation_Vertical;

            THROW_IF_FAILED(actionStackPanel->put_Orientation(uiOrientation));

            ComPtr<IFrameworkElement> actionsFrameworkElement;
            THROW_IF_FAILED(actionStackPanel.As(&actionsFrameworkElement));

            switch (actionAlignment)
            {
            case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Center:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Center));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Left:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Right:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Stretch:
                THROW_IF_FAILED(actionsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
                break;
            }

            // Add the action buttons to the stack panel
            THROW_IF_FAILED(actionStackPanel.As(&actionsPanel));
        }

        UINT32 buttonSpacing;
        THROW_IF_FAILED(actionsConfig->get_ButtonSpacing(&buttonSpacing));

        Thickness buttonMargin = { 0, 0, 0, 0 };
        if (actionsOrientation == ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation::Horizontal)
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

        ABI::AdaptiveCards::XamlCardRenderer::ActionMode showCardActionMode;
        THROW_IF_FAILED(showCardActionConfig->get_ActionMode(&showCardActionMode));

        UINT currentAction = 0;

        ComPtr<XamlCardRenderer> strongRenderer(renderer);
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

                if (actionsOrientation == ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation::Horizontal)
                {
                    // For horizontal alignment, we always use stretch
                    THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Stretch));
                }
                else
                {
                    switch (actionAlignment)
                    {
                    case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Center:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Center));
                        break;
                    case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Left:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Left));
                        break;
                    case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Right:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Right));
                        break;
                    case ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment::Stretch:
                        THROW_IF_FAILED(buttonFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));
                        break;
                    }
                }

                HString title;
                THROW_IF_FAILED(action->get_Title(title.GetAddressOf()));
                XamlHelpers::SetContent(button.Get(), title.Get());

                ABI::AdaptiveCards::XamlCardRenderer::ActionType actionType;
                THROW_IF_FAILED(action->get_ActionType(&actionType));

                // If this is a show card action and we're rendering the actions inline, render the card that will be shown
                ComPtr<IUIElement> uiShowCard;
                if (actionType == ABI::AdaptiveCards::XamlCardRenderer::ActionType::ShowCard && 
                    showCardActionMode != ABI::AdaptiveCards::XamlCardRenderer::ActionMode_Popup)
                {
                    BuildShowCard(strongRenderer.Get(), showCardActionConfig.Get(), action.Get(), uiShowCard.GetAddressOf());
                    allShowCards->push_back(uiShowCard);

                    ComPtr<IPanel> showCardsPanel;
                    THROW_IF_FAILED(showCardsStackPanel.As(&showCardsPanel));
                    XamlHelpers::AppendXamlElementToPanel(uiShowCard.Get(), showCardsPanel.Get());
                }
                
                // Add click handler
                ComPtr<IButtonBase> buttonBase;
                THROW_IF_FAILED(button.As(&buttonBase));

                EventRegistrationToken clickToken;
                THROW_IF_FAILED(buttonBase->add_Click(Callback<IRoutedEventHandler>([action, actionType, showCardActionMode, uiShowCard, allShowCards, strongRenderer, inputElements](IInspectable* /*sender*/, IRoutedEventArgs* /*args*/) -> HRESULT
                {
                    if (actionType == ABI::AdaptiveCards::XamlCardRenderer::ActionType::ShowCard &&
                        showCardActionMode != ABI::AdaptiveCards::XamlCardRenderer::ActionMode_Popup)
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
                        // Serialize the inputElements into Json.
                        Json::Value jsonValue;
                        for (auto& inputElement : *inputElements)
                        {
                            inputElement.Serialize(jsonValue);
                        }

                        Json::StyledWriter writer;
                        std::string inputString = writer.write(jsonValue);

                        HString inputHString;
                        THROW_IF_FAILED(UTF8ToHString(inputString, inputHString.GetAddressOf()));

                        // TODO: Data binding for inputs 
                        ComPtr<IAdaptiveActionEventArgs> eventArgs;
                        THROW_IF_FAILED(MakeAndInitialize<AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs>(&eventArgs, action.Get(), inputHString.Get()));
                        THROW_IF_FAILED(strongRenderer->SendActionEvent(eventArgs.Get()));
                    }

                    return S_OK;
                }).Get(), &clickToken));

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
            currentAction++;
        });

        XamlHelpers::AppendXamlElementToPanel(actionsPanel.Get(), parentPanel);

        // TODO: EdgeToEdge show cards should not go in "parentPanel", which has margins applied to it from the adaptive card options
        XamlHelpers::AppendXamlElementToPanel(showCardsStackPanel.Get(), parentPanel);
    }

    _Use_decl_annotations_
    void XamlBuilder::ApplyMarginToXamlElement(
        IAdaptiveSpacingDefinition* spacingDefinition,
        IFrameworkElement* element)
    {
        ComPtr<IFrameworkElement> localElement(element);
        Thickness margin = ThicknessFromSpacingDefinition(spacingDefinition);
        THROW_IF_FAILED(localElement->put_Margin(margin));
    }

    _Use_decl_annotations_
    void XamlBuilder::GetSeparationConfigForElement(
        IAdaptiveCardElement* cardElement,
        UINT* spacing,
        UINT* separatorThickness,
        ABI::Windows::UI::Color* separatorColor,
        bool * needsSeparator)
    {
        ABI::AdaptiveCards::XamlCardRenderer::Spacing elementSpacing;
        THROW_IF_FAILED(cardElement->get_Spacing(&elementSpacing));

        UINT localSpacing;
        THROW_IF_FAILED(GetSpacingSizeFromSpacing(m_hostConfig.Get(), elementSpacing, &localSpacing));

        ComPtr<IAdaptiveSeparator> elementSeparator;
        THROW_IF_FAILED(cardElement->get_Separator(&elementSeparator));

        ABI::Windows::UI::Color localColor = { 0 };
        UINT localThickness = 0;
        if (elementSeparator != nullptr)
        {
            ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor elementSeparatorColor;
            elementSeparator->get_Color(&elementSeparatorColor);

            THROW_IF_FAILED(GetColorFromAdaptiveColor(m_hostConfig.Get(), elementSeparatorColor, false, &localColor));

            ComPtr<IAdaptiveSeparatorThicknessConfig> separatorThicknessConfig;
            THROW_IF_FAILED(m_hostConfig->get_SeparatorThickness(&separatorThicknessConfig));

            ABI::AdaptiveCards::XamlCardRenderer::SeparatorThickness elementSeparatorThickness;
            elementSeparator->get_Thickness(&elementSeparatorThickness);

            switch (elementSeparatorThickness)
            {
            case ABI::AdaptiveCards::XamlCardRenderer::SeparatorThickness::Default:
                THROW_IF_FAILED(separatorThicknessConfig->get_Default(&localThickness));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::SeparatorThickness::Thick:
                THROW_IF_FAILED(separatorThicknessConfig->get_Thick(&localThickness));
                break;
            }
        }

        *needsSeparator = 
            (elementSeparator != nullptr) || 
            (elementSpacing != ABI::AdaptiveCards::XamlCardRenderer::Spacing::None);

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
    Thickness XamlBuilder::ThicknessFromSpacingDefinition(IAdaptiveSpacingDefinition* spacingDefinition)
    {
        UINT32 left;
        THROW_IF_FAILED(spacingDefinition->get_Left(&left));
        UINT32 top;
        THROW_IF_FAILED(spacingDefinition->get_Top(&top));
        UINT32 right;
        THROW_IF_FAILED(spacingDefinition->get_Right(&right));
        UINT32 bottom;
        THROW_IF_FAILED(spacingDefinition->get_Bottom(&bottom));
        Thickness margin = { (double)left, (double)top, (double)right, (double)bottom };
        return margin;
    }

    _Use_decl_annotations_
    void XamlBuilder::StyleXamlTextBlock(
        ABI::AdaptiveCards::XamlCardRenderer::TextSize size,
        ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor color,
        bool isSubtle,
        ABI::AdaptiveCards::XamlCardRenderer::TextWeight weight,
        ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock)
    {
        ComPtr<ITextBlock> localTextBlock(xamlTextBlock);

        ABI::Windows::UI::Color fontColor;
        THROW_IF_FAILED(GetColorFromAdaptiveColor(m_hostConfig.Get(), color, isSubtle, &fontColor));

        ComPtr<IBrush> fontColorBrush = GetSolidColorBrush(fontColor);
        THROW_IF_FAILED(localTextBlock->put_Foreground(fontColorBrush.Get()));

        // Retrieve the Font Size from Host Options
        ComPtr<IAdaptiveFontSizesConfig> fontSizesConfig;
        THROW_IF_FAILED(m_hostConfig->get_FontSizes(&fontSizesConfig));
        UINT32 fontSize;
        switch (size)
        {
        case ABI::AdaptiveCards::XamlCardRenderer::TextSize::Small:
            THROW_IF_FAILED(fontSizesConfig->get_Small(&fontSize));
            break;
        case ABI::AdaptiveCards::XamlCardRenderer::TextSize::Normal:
            THROW_IF_FAILED(fontSizesConfig->get_Normal(&fontSize));
            break;
        case ABI::AdaptiveCards::XamlCardRenderer::TextSize::Medium:
            THROW_IF_FAILED(fontSizesConfig->get_Medium(&fontSize));
            break;
        case ABI::AdaptiveCards::XamlCardRenderer::TextSize::Large:
            THROW_IF_FAILED(fontSizesConfig->get_Large(&fontSize));
            break;
        case ABI::AdaptiveCards::XamlCardRenderer::TextSize::ExtraLarge:
            THROW_IF_FAILED(fontSizesConfig->get_ExtraLarge(&fontSize));
            break;
        default:
            THROW_IF_FAILED(fontSizesConfig->get_Normal(&fontSize));
            break;
        }
        THROW_IF_FAILED(localTextBlock->put_FontSize((double)fontSize));

        ABI::Windows::UI::Text::FontWeight xamlFontWeight;
        switch (weight)
        {
        case ABI::AdaptiveCards::XamlCardRenderer::TextWeight::Lighter:
            THROW_IF_FAILED(m_fontWeightsStatics->get_Light(&xamlFontWeight));
            break;
        case ABI::AdaptiveCards::XamlCardRenderer::TextWeight::Normal:
            THROW_IF_FAILED(m_fontWeightsStatics->get_Normal(&xamlFontWeight));
            break;
        case ABI::AdaptiveCards::XamlCardRenderer::TextWeight::Bolder:
            THROW_IF_FAILED(m_fontWeightsStatics->get_Bold(&xamlFontWeight));
            break;
        default:
            THROW_IF_FAILED(m_fontWeightsStatics->get_Normal(&xamlFontWeight));
            break;
        }
        THROW_IF_FAILED(localTextBlock->put_FontWeight(xamlFontWeight));
    }

    _Use_decl_annotations_
    void XamlBuilder::StyleXamlTextBlock(
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig* options,
        ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock)
    {
        ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight;
        THROW_IF_FAILED(options->get_Weight(&textWeight));
        ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor textColor;
        THROW_IF_FAILED(options->get_Color(&textColor));
        ABI::AdaptiveCards::XamlCardRenderer::TextSize textSize;
        THROW_IF_FAILED(options->get_Size(&textSize));
        boolean isSubtle;
        THROW_IF_FAILED(options->get_IsSubtle(&isSubtle));
        StyleXamlTextBlock(textSize, textColor, Boolify(isSubtle), textWeight, xamlTextBlock);
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildTextBlock(
        IAdaptiveCardElement* adaptiveCardElement, 
        std::shared_ptr<std::vector<InputItem>> inputElements,
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
        adaptiveTextBlock->get_Text(text.GetAddressOf());
        xamlTextBlock->put_Text(text.Get());

        // Retrieve the Text Color from Host Options.
        ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor textColor;
        THROW_IF_FAILED(adaptiveTextBlock->get_Color(&textColor));
        boolean isSubtle = false;
        THROW_IF_FAILED(adaptiveTextBlock->get_IsSubtle(&isSubtle));

        // The subtle boolean is rendered by setting the opacity on the text block, so retrieve
        // that value from the resource dictionary and set the Opacity
        if (isSubtle)
        {
            ComPtr<IInspectable> subtleOpacityInspectable;
            if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IInspectable>(c_TextBlockSubtleOpacityKey, &subtleOpacityInspectable)))
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

        // Apply the wrap value to the xaml element
        boolean shouldWrap = false;
        THROW_IF_FAILED(adaptiveTextBlock->get_Wrap(&shouldWrap));
        THROW_IF_FAILED(xamlTextBlock->put_TextWrapping(shouldWrap ? TextWrapping::TextWrapping_WrapWholeWords : TextWrapping::TextWrapping_NoWrap));
        THROW_IF_FAILED(xamlTextBlock->put_TextTrimming(TextTrimming::TextTrimming_CharacterEllipsis));

        // Set the maximum number of lines the text block should show in cases where wrapping is enabled.
        if (shouldWrap)
        {
            UINT maxLines;
            THROW_IF_FAILED(adaptiveTextBlock->get_MaxLines(&maxLines));
            THROW_IF_FAILED(xamlTextBlock2->put_MaxLines(maxLines));
        }

        ABI::AdaptiveCards::XamlCardRenderer::HAlignment adaptiveHorizontalAlignment;
        THROW_IF_FAILED(adaptiveTextBlock->get_HorizontalAlignment(&adaptiveHorizontalAlignment));

        // Set the horizontal alignment of the text
        switch (adaptiveHorizontalAlignment)
        {
            case ABI::AdaptiveCards::XamlCardRenderer::HAlignment::Left:
                THROW_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Left));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::HAlignment::Right:
                THROW_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Right));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::HAlignment::Center:
                THROW_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Center));
                break;
        }
        ABI::AdaptiveCards::XamlCardRenderer::TextSize textblockSize;
        THROW_IF_FAILED(adaptiveTextBlock->get_Size(&textblockSize));

        ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight;
        THROW_IF_FAILED(adaptiveTextBlock->get_Weight(&textWeight));

        // Ensure left edge of text is consistent regardless of font size, so both small and large fonts
        // are flush on the left edge of the card by enabling TrimSideBearings
        THROW_IF_FAILED(xamlTextBlock2->put_OpticalMarginAlignment(OpticalMarginAlignment_TrimSideBearings));

        //Style the TextBlock using Host Options
        StyleXamlTextBlock(textblockSize, textColor, isSubtle, textWeight, xamlTextBlock.Get());

        THROW_IF_FAILED(xamlTextBlock.CopyTo(textBlockControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildImage(
        IAdaptiveCardElement* adaptiveCardElement, 
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** imageControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(cardElement.As(&adaptiveImage));

        ComPtr<IUriRuntimeClass> imageUri;
        THROW_IF_FAILED(adaptiveImage->get_Url(imageUri.GetAddressOf()));

        // Get the image's size and style
        ABI::AdaptiveCards::XamlCardRenderer::ImageSize size;
        THROW_IF_FAILED(adaptiveImage->get_Size(&size));

        ABI::AdaptiveCards::XamlCardRenderer::ImageStyle imageStyle;
        THROW_IF_FAILED(adaptiveImage->get_Style(&imageStyle));

        ComPtr<IFrameworkElement> frameworkElement;
        if (imageStyle == ImageStyle_Person)
        {
            ComPtr<IEllipse> ellipse = XamlHelpers::CreateXamlClass<IEllipse>(HStringReference(RuntimeClass_Windows_UI_Xaml_Shapes_Ellipse));
            SetImageOnUIElement(imageUri.Get(), ellipse.Get());

            // Set both Auto, Default, and Stretch to Stretch_UniformToFill.  An ellipse set to Stretch_Uniform ends up with size 0.
            if (size == ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Auto ||
                size == ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Default ||
                size == ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Stretch)
            {
                ComPtr<IShape> ellipseAsShape;
                THROW_IF_FAILED(ellipse.As(&ellipseAsShape));

                THROW_IF_FAILED(ellipseAsShape->put_Stretch(Stretch::Stretch_UniformToFill));
            }

            THROW_IF_FAILED(ellipse.As(&frameworkElement));
        }
        else
        {
            ComPtr<IImage> xamlImage = XamlHelpers::CreateXamlClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));
            SetImageOnUIElement(imageUri.Get(), xamlImage.Get());

            switch (size)
            {
                case ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Auto:
                case ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Default:
                    THROW_IF_FAILED(xamlImage->put_Stretch(Stretch::Stretch_UniformToFill));
                    break;

                case ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Stretch:
                    THROW_IF_FAILED(xamlImage->put_Stretch(Stretch::Stretch_Uniform));
                    break;
            }

            THROW_IF_FAILED(xamlImage.As(&frameworkElement));
        }

        ComPtr<IAdaptiveImageSizesConfig> sizeOptions;
        THROW_IF_FAILED(m_hostConfig->get_ImageSizes(sizeOptions.GetAddressOf()));

        switch (size)
        {
            case ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Small:
            {
                UINT32 imageSize;
                THROW_IF_FAILED(sizeOptions->get_Small(&imageSize));

                THROW_IF_FAILED(frameworkElement->put_Width(imageSize));
                THROW_IF_FAILED(frameworkElement->put_Height(imageSize));
                break;
            }

            case ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Medium:
            {
                UINT32 imageSize;
                THROW_IF_FAILED(sizeOptions->get_Medium(&imageSize));

                THROW_IF_FAILED(frameworkElement->put_Width(imageSize));
                THROW_IF_FAILED(frameworkElement->put_Height(imageSize));
                break;
            }

            case ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Large:
            {
                UINT32 imageSize;
                THROW_IF_FAILED(sizeOptions->get_Large(&imageSize));

                THROW_IF_FAILED(frameworkElement->put_Width(imageSize));
                THROW_IF_FAILED(frameworkElement->put_Height(imageSize));
                break;
            }
        }

        ABI::AdaptiveCards::XamlCardRenderer::HAlignment adaptiveHorizontalAlignment;
        THROW_IF_FAILED(adaptiveImage->get_HorizontalAlignment(&adaptiveHorizontalAlignment));

        switch (adaptiveHorizontalAlignment)
        {
            case ABI::AdaptiveCards::XamlCardRenderer::HAlignment::Left:
                THROW_IF_FAILED(frameworkElement->put_HorizontalAlignment(HorizontalAlignment_Left));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::HAlignment::Right:
                THROW_IF_FAILED(frameworkElement->put_HorizontalAlignment(HorizontalAlignment_Right));
                break;
            case ABI::AdaptiveCards::XamlCardRenderer::HAlignment::Center:
                THROW_IF_FAILED(frameworkElement->put_HorizontalAlignment(HorizontalAlignment_Center));
                break;
        }

        // Generate the style name from the adaptive element and apply it to the xaml
        // element if it exists in the resource dictionaries
        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForImage(adaptiveImage.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IStyle>(styleName, &style)))
        {
            THROW_IF_FAILED(frameworkElement->put_Style(style.Get()));
        }

        THROW_IF_FAILED(frameworkElement.CopyTo(imageControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildContainer(
        IAdaptiveCardElement* adaptiveCardElement, 
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** containerControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveContainer> adaptiveContainer;
        THROW_IF_FAILED(cardElement.As(&adaptiveContainer));

        ComPtr<IStackPanel> xamlStackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        xamlStackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IPanel> stackPanelAsPanel;
        THROW_IF_FAILED(xamlStackPanel.As(&stackPanelAsPanel));
        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        THROW_IF_FAILED(adaptiveContainer->get_Items(&childItems));
        BuildPanelChildren(childItems.Get(), stackPanelAsPanel.Get(), inputElements, [](IUIElement*) {});

        // Add Border to container and style it from HostConfig
        ComPtr<IAdaptiveContainerConfig> containerConfig;
        THROW_IF_FAILED(m_hostConfig->get_Container(&containerConfig));
        ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle containerStyle;
        THROW_IF_FAILED(adaptiveContainer->get_Style(&containerStyle));
        ComPtr<IAdaptiveContainerStyleConfig> containerStyleConfig;
        THROW_IF_FAILED(containerStyle == ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle::Normal ?
            containerConfig->get_Normal(&containerStyleConfig) :
            containerConfig->get_Emphasis(&containerStyleConfig));

        ComPtr<IBorder> containerBorder = XamlHelpers::CreateXamlClass<IBorder>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Border));
        ABI::Windows::UI::Color borderColor;
        THROW_IF_FAILED(containerStyleConfig->get_BorderColor(&borderColor));
        ComPtr<IBrush> borderColorBrush = GetSolidColorBrush(borderColor);
        THROW_IF_FAILED(containerBorder->put_BorderBrush(borderColorBrush.Get()));
        ABI::Windows::UI::Color backgroundColor;
        THROW_IF_FAILED(containerStyleConfig->get_BackgroundColor(&backgroundColor));
        ComPtr<IBrush> backgroundColorBrush = GetSolidColorBrush(backgroundColor);
        THROW_IF_FAILED(containerBorder->put_Background(backgroundColorBrush.Get()));

        ComPtr<IAdaptiveSpacingDefinition> hostBorderOptions;
        THROW_IF_FAILED(containerStyleConfig->get_BorderThickness(&hostBorderOptions));
        Thickness borderThickness = ThicknessFromSpacingDefinition(hostBorderOptions.Get());
        THROW_IF_FAILED(containerBorder->put_BorderThickness(borderThickness));

        ComPtr<IUIElement> stackPanelAsUIElement;
        THROW_IF_FAILED(xamlStackPanel.As(&stackPanelAsUIElement));
        THROW_IF_FAILED(containerBorder->put_Child(stackPanelAsUIElement.Get()));

        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForContainer(adaptiveContainer.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IStyle>(styleName, &style)))
        {
            ComPtr<IFrameworkElement> stackPanelAsFrameworkElement;
            THROW_IF_FAILED(xamlStackPanel.As(&stackPanelAsFrameworkElement));
            THROW_IF_FAILED(stackPanelAsFrameworkElement->put_Style(style.Get()));
        }

        THROW_IF_FAILED(containerBorder.CopyTo(containerControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildColumn(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** ColumnControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumn> adaptiveColumn;
        THROW_IF_FAILED(cardElement.As(&adaptiveColumn));

        ComPtr<IStackPanel> xamlStackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        xamlStackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IPanel> stackPanelAsPanel;
        THROW_IF_FAILED(xamlStackPanel.As(&stackPanelAsPanel));
        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        THROW_IF_FAILED(adaptiveColumn->get_Items(&childItems));
        BuildPanelChildren(childItems.Get(), stackPanelAsPanel.Get(), inputElements, [](IUIElement*) {});

        THROW_IF_FAILED(xamlStackPanel.CopyTo(ColumnControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildColumnSet(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
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
        XamlHelpers::IterateOverVector<IAdaptiveColumn>(columns.Get(), [this, xamlGrid, gridStatics, &currentColumn, inputElements](IAdaptiveColumn* column)
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
                GetSeparationConfigForElement(columnAsCardElement.Get(), &spacing, &separatorThickness, &separatorColor, &needsSeparator);

                if (needsSeparator)
                {
                    //Create a new ColumnDefinition for the separator
                    ComPtr<IColumnDefinition> separatorColumnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
                    THROW_IF_FAILED(separatorColumnDefinition->put_Width({ 1.0, GridUnitType::GridUnitType_Auto }));
                    THROW_IF_FAILED(columnDefinitions->Append(separatorColumnDefinition.Get()));

                    auto separator = CreateSeparator(spacing, separatorThickness, separatorColor, false);
                    ComPtr<IFrameworkElement> separatorAsFrameworkElement;
                    THROW_IF_FAILED(separator.As(&separatorAsFrameworkElement));
                    gridStatics->SetColumn(separatorAsFrameworkElement.Get(), currentColumn++);
                    XamlHelpers::AppendXamlElementToPanel(separator.Get(), gridAsPanel.Get());
                }
            }

            // Determine if the column is auto, stretch, or percentage width, and set the column width appropriately
            ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));

            HString adaptiveColumnSize;
            THROW_IF_FAILED(column->get_Size(adaptiveColumnSize.GetAddressOf()));

            INT32 isStretchResult;
            THROW_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnSize.Get(), HStringReference(L"stretch").Get(), &isStretchResult));

            INT32 isAutoResult;
            THROW_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnSize.Get(), HStringReference(L"auto").Get(), &isAutoResult));

            double sizeAsDouble = _wtof(adaptiveColumnSize.GetRawBuffer(nullptr));

            GridLength columnWidth;
            if (isAutoResult == 0)
            {
                // If auto specified, use auto width
                columnWidth.GridUnitType = GridUnitType::GridUnitType_Auto;
                columnWidth.Value = 0;
            }
            else if (isStretchResult == 0 || !adaptiveColumnSize.IsValid() || (sizeAsDouble <= 0))
            {
                // If stretch specified, or column size invalid or set to non-positive, use stretch with default of 1
                columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
                columnWidth.Value = 1;
            }
            else
            {
                // If user specified specific valid size, use that star size
                columnWidth.GridUnitType = GridUnitType::GridUnitType_Star;
                columnWidth.Value = _wtof(adaptiveColumnSize.GetRawBuffer(nullptr));
            }

            THROW_IF_FAILED(columnDefinition->put_Width(columnWidth));
            THROW_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

            // Build the Column
            ComPtr<IUIElement> xamlColumn;
            BuildColumn(columnAsCardElement.Get(), inputElements, &xamlColumn);

            // Mark the column container with the current column
            ComPtr<IFrameworkElement> columnAsFrameworkElement;
            THROW_IF_FAILED(xamlColumn.As(&columnAsFrameworkElement));
            gridStatics->SetColumn(columnAsFrameworkElement.Get(), currentColumn++);

            // Finally add the column container to the grid
            XamlHelpers::AppendXamlElementToPanel(xamlColumn.Get(), gridAsPanel.Get());
        });

        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForColumnSet(adaptiveColumnSet.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IStyle>(styleName, &style)))
        {
            ComPtr<IFrameworkElement> gridAsFrameworkElement;
            THROW_IF_FAILED(xamlGrid.As(&gridAsFrameworkElement));
            THROW_IF_FAILED(gridAsFrameworkElement->put_Style(style.Get()));
        }

        THROW_IF_FAILED(xamlGrid.CopyTo(columnSetControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildFactSet(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
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
        GridLength factSetGridLength = { 1, GridUnitType::GridUnitType_Star };

        THROW_IF_FAILED(titleColumn->put_Width(factSetGridLength));
        THROW_IF_FAILED(valueColumn->put_Width(factSetGridLength));
        ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
        THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
        THROW_IF_FAILED(columnDefinitions->Append(titleColumn.Get()));
        THROW_IF_FAILED(columnDefinitions->Append(valueColumn.Get()));

        // Create 
        ComPtr<IVector<IAdaptiveFact*>> facts;
        THROW_IF_FAILED(adaptiveFactSet->get_Facts(&facts));
        int currentFact = 0;
        XamlHelpers::IterateOverVector<IAdaptiveFact>(facts.Get(), [this, xamlGrid, gridStatics, factSetGridLength, &currentFact](IAdaptiveFact* fact)
        {
            ComPtr<IRowDefinition> factRow = XamlHelpers::CreateXamlClass<IRowDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition));
            THROW_IF_FAILED(factRow->put_Height(factSetGridLength));

            ComPtr<IVector<RowDefinition*>> rowDefinitions;
            THROW_IF_FAILED(xamlGrid->get_RowDefinitions(&rowDefinitions));
            THROW_IF_FAILED(rowDefinitions->Append(factRow.Get()));

            ComPtr<IAdaptiveFact> localFact(fact);
            ComPtr<IAdaptiveFactSetConfig> factSetConfig;
            THROW_IF_FAILED(m_hostConfig->get_FactSet(&factSetConfig));

            // Create the title xaml textblock and style it from Host options
            ComPtr<ITextBlock> titleTextBlock = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            HString factTitle;
            THROW_IF_FAILED(localFact->get_Title(factTitle.GetAddressOf()));
            THROW_IF_FAILED(titleTextBlock->put_Text(factTitle.Get()));
            ComPtr<IAdaptiveTextConfig> titleTextConfig;
            THROW_IF_FAILED(factSetConfig->get_Title(&titleTextConfig));

            StyleXamlTextBlock(titleTextConfig.Get(), titleTextBlock.Get());

            // Create the value xaml textblock and style it from Host options
            ComPtr<ITextBlock> valueTextBlock = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));
            HString factValue;
            THROW_IF_FAILED(localFact->get_Value(factValue.GetAddressOf()));
            THROW_IF_FAILED(valueTextBlock->put_Text(factValue.Get()));
            ComPtr<IAdaptiveTextConfig> valueTextConfig;
            THROW_IF_FAILED(factSetConfig->get_Value(&valueTextConfig));
            StyleXamlTextBlock(valueTextConfig.Get(), valueTextBlock.Get());

            // Mark the column container with the current column
            ComPtr<IFrameworkElement> titleTextBlockAsFrameWorkElement;
            THROW_IF_FAILED(titleTextBlock.As(&titleTextBlockAsFrameWorkElement));
            UINT32 spacing;
            THROW_IF_FAILED(factSetConfig->get_Spacing(&spacing));
            //Add spacing from hostconfig to right margin of title.
            titleTextBlockAsFrameWorkElement->put_Margin({ 0, 0, (double)spacing, 0 });
            THROW_IF_FAILED(gridStatics->SetColumn(titleTextBlockAsFrameWorkElement.Get(), 0));
            THROW_IF_FAILED(gridStatics->SetRow(titleTextBlockAsFrameWorkElement.Get(), currentFact));

            ComPtr<IFrameworkElement> valueTextBlockAsFrameWorkElement;
            THROW_IF_FAILED(valueTextBlock.As(&valueTextBlockAsFrameWorkElement));
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

        THROW_IF_FAILED(xamlGrid.CopyTo(factSetControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildImageSet(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** imageSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImageSet> adaptiveImageSet;
        THROW_IF_FAILED(cardElement.As(&adaptiveImageSet));

        ComPtr<IVariableSizedWrapGrid> xamlGrid = XamlHelpers::CreateXamlClass<IVariableSizedWrapGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_VariableSizedWrapGrid));

        xamlGrid->put_Orientation(Orientation_Horizontal);

        ComPtr<IVector<IAdaptiveImage*>> images;
        THROW_IF_FAILED(adaptiveImageSet->get_Images(&images));

        ABI::AdaptiveCards::XamlCardRenderer::ImageSize imageSize;
        THROW_IF_FAILED(adaptiveImageSet->get_ImageSize(&imageSize));

        if (imageSize == ABI::AdaptiveCards::XamlCardRenderer::ImageSize::Default)
        {
            ComPtr<IAdaptiveImageSetConfig> imageSetConfig;
            THROW_IF_FAILED(m_hostConfig->get_ImageSet(&imageSetConfig));
            THROW_IF_FAILED(imageSetConfig->get_ImageSize(&imageSize));
        }

        XamlHelpers::IterateOverVector<IAdaptiveImage>(images.Get(), [this, imageSize, xamlGrid, inputElements](IAdaptiveImage* adaptiveImage)
        {
            ComPtr<IAdaptiveImage> localAdaptiveImage(adaptiveImage);
            THROW_IF_FAILED(localAdaptiveImage->put_Size(imageSize));

            ComPtr<IAdaptiveCardElement> adaptiveElementImage;
            localAdaptiveImage.As(&adaptiveElementImage);

            ComPtr<IUIElement> uiImage;
            BuildImage(adaptiveElementImage.Get(), inputElements, &uiImage);

            ComPtr<IPanel> gridAsPanel;
            THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));

            XamlHelpers::AppendXamlElementToPanel(uiImage.Get(), gridAsPanel.Get());
        });

        // TODO: 11508861
        THROW_IF_FAILED(xamlGrid.CopyTo(imageSetControl));
    }

    template<typename T>
    void XamlBuilder::AddInputItemToVector(
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IAdaptiveCardElement* cardElement,
        T* tElement)
    {
        ComPtr<IAdaptiveCardElement> localCardElement(cardElement);
        ComPtr<IAdaptiveInputElement> inputElement;
        THROW_IF_FAILED(localCardElement.As(&inputElement));

        ComPtr<T> localTElement(tElement);
        ComPtr<IUIElement> uiElement;
        THROW_IF_FAILED(localTElement.As(&uiElement));

        InputItem item(inputElement.Get(), uiElement.Get());
        inputElements->push_back(item);
    }

    void XamlBuilder::BuildCompactChoiceSetInput(
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

        int currentIndex = 0;
        int selectedIndex = -1;
        XamlHelpers::IterateOverVector<IAdaptiveChoiceInput>(choices.Get(), [this, &currentIndex, &selectedIndex, itemsVector](IAdaptiveChoiceInput* adaptiveChoiceInput)
        {
            HString title;
            THROW_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));

            ComPtr<IComboBoxItem> comboBoxItem = XamlHelpers::CreateXamlClass<IComboBoxItem>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ComboBoxItem));

            XamlHelpers::SetContent(comboBoxItem.Get(), title.Get());

            boolean isSelected;
            THROW_IF_FAILED(adaptiveChoiceInput->get_IsSelected(&isSelected));
            if (isSelected)
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

        // TODO: 11508861
        THROW_IF_FAILED(comboBox.CopyTo(choiceInputSet));
    }

    void XamlBuilder::BuildExpandedChoiceSetInput(
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

        XamlHelpers::IterateOverVector<IAdaptiveChoiceInput>(choices.Get(), [this, panel, isMultiSelect](IAdaptiveChoiceInput* adaptiveChoiceInput)
        {
            ComPtr<IInspectable> choiceItem;
            if (isMultiSelect)
            {
                ComPtr<ICheckBox> checkBox = XamlHelpers::CreateXamlClass<ICheckBox>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_CheckBox));
                THROW_IF_FAILED(checkBox.As(&choiceItem));
            }
            else
            {
                ComPtr<IRadioButton> radioButton = XamlHelpers::CreateXamlClass<IRadioButton>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_RadioButton));
                THROW_IF_FAILED(radioButton.As(&choiceItem));
            }

            HString title;
            THROW_IF_FAILED(adaptiveChoiceInput->get_Title(title.GetAddressOf()));
            XamlHelpers::SetContent(choiceItem.Get(), title.Get());

            boolean isSelected;
            THROW_IF_FAILED(adaptiveChoiceInput->get_IsSelected(&isSelected));
            XamlHelpers::SetToggleValue(choiceItem.Get(), isSelected);

            XamlHelpers::AppendXamlElementToPanel(choiceItem.Get(), panel.Get());
        });

        // TODO: 11508861
        THROW_IF_FAILED(stackPanel.CopyTo(choiceInputSet));
    }

    void XamlBuilder::BuildChoiceSetInput(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** choiceInputSet)
    {
        if (!this->SupportsInteractivity())
        {
            return;
        }

        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveChoiceSetInput> adaptiveChoiceSetInput;
        THROW_IF_FAILED(cardElement.As(&adaptiveChoiceSetInput));

        ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle choiceSetStyle;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_ChoiceSetStyle(&choiceSetStyle));

        boolean isMultiSelect;
        THROW_IF_FAILED(adaptiveChoiceSetInput->get_IsMultiSelect(&isMultiSelect));

        if (choiceSetStyle == ABI::AdaptiveCards::XamlCardRenderer::ChoiceSetStyle_Compact &&
            !isMultiSelect)
        {
            BuildCompactChoiceSetInput(adaptiveChoiceSetInput.Get(), choiceInputSet);
        }
        else
        {
            BuildExpandedChoiceSetInput(adaptiveChoiceSetInput.Get(), isMultiSelect, choiceInputSet);
        }

        AddInputItemToVector(inputElements, adaptiveCardElement, *choiceInputSet);
    }

    void XamlBuilder::BuildDateInput(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** dateInputControl)
    {
        if (!this->SupportsInteractivity())
        {
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

        AddInputItemToVector(inputElements, adaptiveCardElement, datePicker.Get());
            
        // TODO: Handle parsing dates for min/max and value

        // TODO: 11508861
        THROW_IF_FAILED(datePicker.CopyTo(dateInputControl));
    }

    void XamlBuilder::BuildNumberInput(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** numberInputControl)
    {
        if (!this->SupportsInteractivity())
        {
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

        AddInputItemToVector(inputElements, adaptiveCardElement, textBox.Get());

        // TODO: Handle max and min?

        THROW_IF_FAILED(textBox.CopyTo(numberInputControl));
    }

    void XamlBuilder::BuildTextInput(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** textInputControl)
    {
        if (!this->SupportsInteractivity())
        {
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

        ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle textInputStyle;
        THROW_IF_FAILED(adaptiveTextInput->get_TextInputStyle(&textInputStyle));

        ComPtr<IInputScopeName> inputScopeName = XamlHelpers::CreateXamlClass<IInputScopeName>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScopeName));
        switch (textInputStyle)
        {
            case ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle::Email:
                THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_EmailSmtpAddress));
                break;

            case ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle::Tel:
                THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_TelephoneNumber));
                break;

            case ABI::AdaptiveCards::XamlCardRenderer::TextInputStyle::Url:
                THROW_IF_FAILED(inputScopeName->put_NameValue(InputScopeNameValue::InputScopeNameValue_Url));
                break;
        }

        ComPtr<IInputScope> inputScope = XamlHelpers::CreateXamlClass<IInputScope>(HStringReference(RuntimeClass_Windows_UI_Xaml_Input_InputScope));
        ComPtr<IVector<InputScopeName*>> names;
        THROW_IF_FAILED(inputScope->get_Names(names.GetAddressOf()));
        THROW_IF_FAILED(names->Append(inputScopeName.Get()));

        THROW_IF_FAILED(textBox->put_InputScope(inputScope.Get()));

        AddInputItemToVector(inputElements, adaptiveCardElement, textBox.Get());

        // TODO: 11508861
        THROW_IF_FAILED(textBox.CopyTo(textInputControl));
    }

    void XamlBuilder::BuildTimeInput(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** timeInputControl)
    {
        if (!this->SupportsInteractivity())
        {
            return;
        }

        ComPtr<ITimePicker> timePicker = XamlHelpers::CreateXamlClass<ITimePicker>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TimePicker));

        // Make the picker stretch full width
        ComPtr<IFrameworkElement> timePickerAsFrameworkElement;
        THROW_IF_FAILED(timePicker.As(&timePickerAsFrameworkElement));
        THROW_IF_FAILED(timePickerAsFrameworkElement->put_HorizontalAlignment(HorizontalAlignment_Stretch));

        AddInputItemToVector(inputElements, adaptiveCardElement, timePicker.Get());

        // TODO: Handle placeholder text and parsing times for min/max and value

        // TODO: 11508861
        THROW_IF_FAILED(timePicker.CopyTo(timeInputControl));
    }

    void XamlBuilder::BuildToggleInput(
        IAdaptiveCardElement* adaptiveCardElement,
        std::shared_ptr<std::vector<InputItem>> inputElements,
        IUIElement** toggleInputControl)
    {
        if (!this->SupportsInteractivity())
        {
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

        AddInputItemToVector(inputElements, adaptiveCardElement, checkBox.Get());

        // TODO: 11508861
        THROW_IF_FAILED(checkBox.CopyTo(toggleInputControl));
    }

    bool XamlBuilder::SupportsInteractivity()
    {
        boolean supportsInteractivity;
        THROW_IF_FAILED(m_hostConfig->get_SupportsInteractivity(&supportsInteractivity));
        return Boolify(supportsInteractivity);
    }
}}