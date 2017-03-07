#include "pch.h"
#include "XamlBuilder.h"

#include "DefaultResourceDictionary.h"
#include "XamlHelpers.h"
#include "XamlStyleKeyGenerators.h"
#include <windows.foundation.collections.h>
#include <windows.storage.h>
#include <windows.ui.xaml.markup.h>
#include <windows.web.http.h>
#include <windows.web.http.filters.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::Storage;
using namespace ABI::Windows::Storage::Streams;
using namespace ABI::Windows::UI::Text;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Markup;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;
using namespace ABI::Windows::Web::Http;
using namespace ABI::Windows::Web::Http::Filters;

const PCWSTR c_TextBlockSubtleOpacityKey = L"TextBlock.SubtleOpacity";

namespace AdaptiveCards { namespace XamlCardRenderer
{
    XamlBuilder::XamlBuilder()
    {
        // Populate the map of element types to their builder methods
        m_adaptiveElementBuilder[ElementType::TextBlock] = std::bind(&XamlBuilder::BuildTextBlock, this, std::placeholders::_1, std::placeholders::_2);
        m_adaptiveElementBuilder[ElementType::Image] = std::bind(&XamlBuilder::BuildImage, this, std::placeholders::_1, std::placeholders::_2);
        m_adaptiveElementBuilder[ElementType::Container] = std::bind(&XamlBuilder::BuildContainer, this, std::placeholders::_1, std::placeholders::_2);
        m_adaptiveElementBuilder[ElementType::ColumnSet] = std::bind(&XamlBuilder::BuildColumnSet, this, std::placeholders::_1, std::placeholders::_2);

        m_imageLoadTracker.AddListener(this);

        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Storage_Streams_RandomAccessStream).Get(), &m_randomAccessStreamStatics));
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(), &m_propertyValueStatics));

        InitializeDefaultResourceDictionary();
    }

    HRESULT XamlBuilder::AllImagesLoaded()
    {
        FireAllImagesLoaded();
        return S_OK;
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildXamlTreeFromAdaptiveCard(IAdaptiveCard* adaptiveCard, IUIElement** xamlTreeRoot)
    {
        *xamlTreeRoot = nullptr;

        ComPtr<IPanel> rootContainer = CreateRootPanelFromAdaptiveCard(adaptiveCard);

        // Enumerate the child items of the card and build xaml for them
        ComPtr<IVector<IAdaptiveCardElement*>> items;
        THROW_IF_FAILED(adaptiveCard->get_Items(&items));
        BuildPanelChildren(items.Get(), rootContainer.Get(), [](IUIElement*) {});

        THROW_IF_FAILED(rootContainer.CopyTo(xamlTreeRoot));

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

    HRESULT XamlBuilder::AddListener(IXamlBuilderListener* listener) try
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

    HRESULT XamlBuilder::RemoveListener(IXamlBuilderListener* listener) try
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

    void XamlBuilder::InitializeDefaultResourceDictionary()
    {
        ComPtr<IXamlReaderStatics> xamlReaderStatics;
        THROW_IF_FAILED(RoGetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Markup_XamlReader).Get(),
            __uuidof(IXamlReaderStatics), reinterpret_cast<void**>(xamlReaderStatics.GetAddressOf())));

        ComPtr<IInspectable> resourceDictionaryInspectable;
        THROW_IF_FAILED(xamlReaderStatics->Load(HStringReference(c_defaultResourceDictionary).Get(), &resourceDictionaryInspectable));
        ComPtr<IResourceDictionary> resourceDictionary;
        THROW_IF_FAILED(resourceDictionaryInspectable.As(&resourceDictionary));

        m_resourceDictionaries.push_back(resourceDictionary);
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

            // Search for the named resource in all known distionaries
            ComPtr<IInspectable> dictionaryValue;
            for (auto& resourceDictionary : m_resourceDictionaries)
            {
                ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;
                if (SUCCEEDED(resourceDictionary.As(&resourceDictionaryMap)) &&
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
        }
        catch (...)
        {
        }
        return E_FAIL;
    }

    template<typename T>
    bool XamlBuilder::TryGetValueResoureFromResourceDictionaries(
        _In_ std::wstring styleName,
        _Out_ T* valueResource)
    {
        try
        {
            // Get a resource key for the requested style that we can use for ResourceDistionary Lookups
            ComPtr<IInspectable> resourceKey;
            THROW_IF_FAILED(m_propertyValueStatics->CreateString(HStringReference(styleName.c_str()).Get(), resourceKey.GetAddressOf()));

            // Search for the named resource in all known distionaries
            ComPtr<IInspectable> dictionaryValue;
            for (auto& resourceDictionary : m_resourceDictionaries)
            {
                ComPtr<IMap<IInspectable*, IInspectable*>> resourceDictionaryMap;
                if (SUCCEEDED(resourceDictionary.As(&resourceDictionaryMap)) &&
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
        }
        catch (...)
        {
        }
        return false;
    }

    _Use_decl_annotations_
    ComPtr<IPanel> XamlBuilder::CreateRootPanelFromAdaptiveCard(IAdaptiveCard* /*adaptiveCard*/)
    {
        // We use a StackPanel as the panel type for the root adaptive card
        ComPtr<IStackPanel> stackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));

        ComPtr<IPanel> stackPanelAsPanel;
        THROW_IF_FAILED(stackPanel.As(&stackPanelAsPanel));
        return stackPanelAsPanel;
    }

    _Use_decl_annotations_
    void XamlBuilder::PopulateImageFromUrlAsync(IUriRuntimeClass* imageUri, ABI::Windows::UI::Xaml::Controls::IImage* imageControl)
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
        httpClient->GetInputStreamAsync(imageUri, &getStreamOperation);

        getStreamOperation->put_Completed(Callback<Implements<RuntimeClassFlags<WinRtClassicComMix>, IAsyncOperationWithProgressCompletedHandler<IInputStream*, HttpProgress>>>
            ([this, bitmapSource, imageControl](IAsyncOperationWithProgress<IInputStream*, HttpProgress>* operation, AsyncStatus /*status*/) -> HRESULT
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
                ([this, bitmapSource, randomAccessStream, imageControl](IAsyncOperationWithProgress<UINT64, UINT64>* /*operation*/, AsyncStatus /*status*/) -> HRESULT
            {
                randomAccessStream->Seek(0);
                RETURN_IF_FAILED(bitmapSource->SetSource(randomAccessStream.Get()));

                ComPtr<IImageSource> imageSource;
                RETURN_IF_FAILED(bitmapSource.As(&imageSource));
                imageControl->put_Source(imageSource.Get());
                return S_OK;
            }).Get());
        }).Get());
    }

    void XamlBuilder::FireAllImagesLoaded()
    {
        for (auto& listener : m_listeners)
        {
            listener->AllImagesLoaded();
        }
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildPanelChildren(
        IVector<IAdaptiveCardElement*>* children,
        IPanel* parentPanel,
        std::function<void(IUIElement* child)> childCreatedCallback)
    {
        XamlHelpers::IterateOverVector<IAdaptiveCardElement>(children, [&](IAdaptiveCardElement* element)
        {
            ElementType elementType;
            THROW_IF_FAILED(element->get_ElementType(&elementType));
            if (m_adaptiveElementBuilder.find(elementType) != m_adaptiveElementBuilder.end())
            {
                ComPtr<IUIElement> newControl;
                m_adaptiveElementBuilder[elementType](element, &newControl);
                XamlHelpers::AppendXamlElementToPanel(newControl.Get(), parentPanel);
                childCreatedCallback(newControl.Get());
            }
        });
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildTextBlock(
        IAdaptiveCardElement* adaptiveCardElement, 
        IUIElement** textBlockControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
        THROW_IF_FAILED(cardElement.As(&adaptiveTextBlock));

        ComPtr<ITextBlock> xamlTextBlock = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

        HString text;
        adaptiveTextBlock->get_Text(text.GetAddressOf());
        xamlTextBlock->put_Text(text.Get());

        // Generate the style name from the adaptive element and apply it to the xaml
        // element it it exists in the resource dictionaries
        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForTextBlock(adaptiveTextBlock.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IStyle>(styleName, &style)))
        {
            ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
            THROW_IF_FAILED(xamlTextBlock.As(&textBlockAsFrameworkElement));
            THROW_IF_FAILED(textBlockAsFrameworkElement->put_Style(style.Get()));
        }

        // Translate the font weight into a resource key and apply the value if it exists
        ComPtr<IInspectable> fontWeightInspectable;
        std::wstring fontWeightResourceName = XamlStyleKeyGenerators::GenerateKeyForTextBlockWeight(adaptiveTextBlock.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IInspectable>(fontWeightResourceName, &fontWeightInspectable)))
        {
            ComPtr<IReference<FontWeight>> fontWeightReference;
            if (SUCCEEDED(fontWeightInspectable.As(&fontWeightReference)))
            {
                FontWeight fontWeight;
                fontWeightReference.Get()->get_Value(&fontWeight);
                THROW_IF_FAILED(xamlTextBlock->put_FontWeight(fontWeight));
            }
        }

        // Translate the font color into a resource key and apply the value if it exists
        ComPtr<IBrush> fontColorBrush;
        std::wstring fontColorResourceName = XamlStyleKeyGenerators::GenerateKeyForTextBlockColor(adaptiveTextBlock.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IBrush>(fontColorResourceName, &fontColorBrush)))
        {
            THROW_IF_FAILED(xamlTextBlock->put_Foreground(fontColorBrush.Get()));
        }

        // The subtle boolean is rendered by setting the opacity on the text block, so retrieve
        // that value from the resource dictionary and set the Opacity
        boolean isSubtle = false;
        THROW_IF_FAILED(adaptiveTextBlock->get_IsSubtle(&isSubtle));
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

        THROW_IF_FAILED(xamlTextBlock.CopyTo(textBlockControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildImage(
        IAdaptiveCardElement* adaptiveCardElement, 
        IUIElement** imageControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(cardElement.As(&adaptiveImage));

        ComPtr<IImage> xamlImage = XamlHelpers::CreateXamlClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));

        ComPtr<IUriRuntimeClass> imageUri;
        THROW_IF_FAILED(adaptiveImage->get_Uri(imageUri.GetAddressOf()));
        PopulateImageFromUrlAsync(imageUri.Get(), xamlImage.Get());

        // Set the image to UniformToFill if the card element's size is stretch
        ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size;
        THROW_IF_FAILED(cardElement->get_Size(&size));
        THROW_IF_FAILED(xamlImage->put_Stretch(size == ABI::AdaptiveCards::XamlCardRenderer::CardElementSize::Stretch ? Stretch::Stretch_UniformToFill : Stretch::Stretch_None));

        // Generate the style name from the adaptive element and apply it to the xaml
        // element it it exists in the resource dictionaries
        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForImage(adaptiveImage.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IStyle>(styleName, &style)))
        {
            ComPtr<IFrameworkElement> imageAsFrameworkElement;
            THROW_IF_FAILED(xamlImage.As(&imageAsFrameworkElement));
            THROW_IF_FAILED(imageAsFrameworkElement->put_Style(style.Get()));
        }

        THROW_IF_FAILED(xamlImage.CopyTo(imageControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildContainer(
        IAdaptiveCardElement* adaptiveCardElement, 
        IUIElement** containerControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveContainer> adaptiveContainer;
        THROW_IF_FAILED(cardElement.As(&adaptiveContainer));

        ComPtr<IStackPanel> xamlStackPanel = XamlHelpers::CreateXamlClass<IStackPanel>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_StackPanel));
        xamlStackPanel->put_Orientation(Orientation::Orientation_Vertical);

        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForContainer(adaptiveContainer.Get());
        if (SUCCEEDED(TryGetResoureFromResourceDictionaries<IStyle>(styleName, &style)))
        {
            ComPtr<IFrameworkElement> stackPanelAsFrameworkElement;
            THROW_IF_FAILED(xamlStackPanel.As(&stackPanelAsFrameworkElement));
            THROW_IF_FAILED(stackPanelAsFrameworkElement->put_Style(style.Get()));
        }

        ComPtr<IPanel> stackPanelAsPanel;
        THROW_IF_FAILED(xamlStackPanel.As(&stackPanelAsPanel));
        ComPtr<IVector<IAdaptiveCardElement*>> childItems;
        THROW_IF_FAILED(adaptiveContainer->get_Items(&childItems));
        BuildPanelChildren(childItems.Get(), stackPanelAsPanel.Get(), [](IUIElement*) {});

        THROW_IF_FAILED(xamlStackPanel.CopyTo(containerControl));
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildColumnSet(
         IAdaptiveCardElement* adaptiveCardElement,
        IUIElement** columnSetControl)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveColumnSet> adaptiveColumnSet;
        THROW_IF_FAILED(cardElement.As(&adaptiveColumnSet));

        ComPtr<IGrid> xamlGrid = XamlHelpers::CreateXamlClass<IGrid>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid));
        ComPtr<IGridStatics> gridStatics;
        THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Grid).Get(), &gridStatics));

        // Create 
        ComPtr<IVector<IAdaptiveColumn*>> columns;
        THROW_IF_FAILED(adaptiveColumnSet->get_Columns(&columns));
        int currentColumn = 0;
        XamlHelpers::IterateOverVector<IAdaptiveColumn>(columns.Get(), [this, xamlGrid, gridStatics, &currentColumn](IAdaptiveColumn* column)
        {
            HString adaptiveColumnSize;
            THROW_IF_FAILED(column->get_ColumnSize(adaptiveColumnSize.GetAddressOf()));
            INT32 isAutoResult;
            THROW_IF_FAILED(WindowsCompareStringOrdinal(adaptiveColumnSize.Get(), HStringReference(L"Auto").Get(), &isAutoResult));

            // Determine if the column is auto or percentage width, and set the column width appropriately
            ComPtr<IColumnDefinition> columnDefinition = XamlHelpers::CreateXamlClass<IColumnDefinition>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition));
            GridLength columnWidth;
            columnWidth.GridUnitType = (isAutoResult == 0) ? GridUnitType::GridUnitType_Auto : GridUnitType::GridUnitType_Star;
            if (isAutoResult != 0)
            {
                columnWidth.Value = _wtof(adaptiveColumnSize.GetRawBuffer(nullptr));
            }
            THROW_IF_FAILED(columnDefinition->put_Width(columnWidth));
            ComPtr<IVector<ColumnDefinition*>> columnDefinitions;
            THROW_IF_FAILED(xamlGrid->get_ColumnDefinitions(&columnDefinitions));
            THROW_IF_FAILED(columnDefinitions->Append(columnDefinition.Get()));

            // The column is a container, so build it
            ComPtr<IAdaptiveCardElement> columnAsCardElement;
            ComPtr<IAdaptiveColumn> localColumn(column);
            THROW_IF_FAILED(localColumn.As(&columnAsCardElement));
            ComPtr<IUIElement> xamlColumn;
            BuildContainer(columnAsCardElement.Get(), &xamlColumn);

            // Mark the column container with the current column
            ComPtr<IFrameworkElement> columnAsFrameworkElement;
            THROW_IF_FAILED(xamlColumn.As(&columnAsFrameworkElement));
            gridStatics->SetColumn(columnAsFrameworkElement.Get(), currentColumn);

            // Finally add the column container to the grid, and increment the column count
            ComPtr<IPanel> gridAsPanel;
            THROW_IF_FAILED(xamlGrid.As(&gridAsPanel));
            XamlHelpers::AppendXamlElementToPanel(xamlColumn.Get(), gridAsPanel.Get());
            ++currentColumn;
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
}}