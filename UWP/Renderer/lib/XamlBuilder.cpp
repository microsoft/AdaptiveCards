#include "pch.h"
#include "XamlBuilder.h"

#include "XamlHelpers.h"
#include "XamlStyleKeyGenerators.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml::Media::Imaging;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    XamlBuilder::XamlBuilder()
    {
        // Populate the map of element types to their builder methods
        m_adaptiveElementBuilder[ElementType::TextBlock] = std::bind(&XamlBuilder::BuildTextBlock, this, std::placeholders::_1, std::placeholders::_2);
        m_adaptiveElementBuilder[ElementType::Image] = std::bind(&XamlBuilder::BuildImage, this, std::placeholders::_1, std::placeholders::_2);
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildXamlTreeFromAdaptiveCard(IAdaptiveCard* adaptiveCard, IUIElement** xamlTreeRoot)
    {
        *xamlTreeRoot = nullptr;

        ComPtr<IPanel> rootContainer = CreateRootPanelFromAdaptiveCard(adaptiveCard);

        // Enumerate the child items of the card and build xaml for them
        ComPtr<IVector<IAdaptiveCardElement*>> items;
        THROW_IF_FAILED(adaptiveCard->get_Items(&items));
        XamlHelpers::IterateOverVector<IAdaptiveCardElement>(items, [&](IAdaptiveCardElement* element)
        {
            ElementType elementType;
            THROW_IF_FAILED(element->get_ElementType(&elementType));
            if (m_adaptiveElementBuilder.find(elementType) != m_adaptiveElementBuilder.end())
            {
                m_adaptiveElementBuilder[elementType](element, rootContainer.Get());
            }
        });

        THROW_IF_FAILED(rootContainer.CopyTo(xamlTreeRoot));

        // Now that we're returning, make sure any outstanding image loads are no longer tracked
        // since the tracker is going out of scope.
        //m_imageLoadTracker.AbandonOutstandingImages();
    }

    void XamlBuilder::EnsurePropertyValueStatics()
    {
        if (!m_propertyValueStatics)
        {
            THROW_IF_FAILED(RoGetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(),
                __uuidof(IPropertyValueStatics), reinterpret_cast<void**>(m_propertyValueStatics.GetAddressOf())));
        }
    }

    _Use_decl_annotations_
    bool XamlBuilder::TryGetStyleFromResourceDictionaries(std::wstring styleName, IStyle** style)
    {
        *style = nullptr;
        EnsurePropertyValueStatics();

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
                ComPtr<IStyle> styleToReturn;
                if (SUCCEEDED(dictionaryValue.As(&styleToReturn)))
                {
                    THROW_IF_FAILED(styleToReturn.CopyTo(style));
                    return true;
                }
            }
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
    ComPtr<IImageSource> XamlBuilder::LoadImageFromUrl(IUriRuntimeClass* imageUri)
    {
        ComPtr<IBitmapImage> bitmapImage = XamlHelpers::CreateXamlClass<IBitmapImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Media_Imaging_BitmapImage));
        m_imageLoadTracker.TrackBitmapImage(bitmapImage.Get());

        THROW_IF_FAILED(bitmapImage->put_UriSource(imageUri));
        ComPtr<IImageSource> imageSourceToReturn;
        THROW_IF_FAILED(bitmapImage.As(&imageSourceToReturn));
        return imageSourceToReturn;
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildTextBlock(IAdaptiveCardElement* adaptiveCardElement, IPanel* parentPanel)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveTextBlock> adaptiveTextBlock;
        THROW_IF_FAILED(cardElement.As(&adaptiveTextBlock));

        ComPtr<ITextBlock> xamlTextBlock = XamlHelpers::CreateXamlClass<ITextBlock>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_TextBlock));

        HString text;
        adaptiveTextBlock->get_Text(text.GetAddressOf());
        xamlTextBlock->put_Text(text.Get());

        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForTextBlock(adaptiveTextBlock.Get());
        if (SUCCEEDED(TryGetStyleFromResourceDictionaries(styleName, &style)))
        {
            // TODO: MSFT:10826544 - Programmatic xaml style generation
        }

        XamlHelpers::AppendXamlElementToPanel(xamlTextBlock, parentPanel);
    }

    _Use_decl_annotations_
    void XamlBuilder::BuildImage(IAdaptiveCardElement* adaptiveCardElement, IPanel* parentPanel)
    {
        ComPtr<IAdaptiveCardElement> cardElement(adaptiveCardElement);
        ComPtr<IAdaptiveImage> adaptiveImage;
        THROW_IF_FAILED(cardElement.As(&adaptiveImage));

        ComPtr<IImage> xamlImage = XamlHelpers::CreateXamlClass<IImage>(HStringReference(RuntimeClass_Windows_UI_Xaml_Controls_Image));

        ComPtr<IUriRuntimeClass> imageUri;
        THROW_IF_FAILED(adaptiveImage->get_Uri(imageUri.GetAddressOf()));
        ComPtr<IImageSource> imageSource = LoadImageFromUrl(imageUri.Get());
        THROW_IF_FAILED(xamlImage->put_Source(imageSource.Get()));

        ABI::AdaptiveCards::XamlCardRenderer::CardElementSize size;
        THROW_IF_FAILED(cardElement->get_Size(&size));
        THROW_IF_FAILED(xamlImage->put_Stretch(size == ABI::AdaptiveCards::XamlCardRenderer::CardElementSize::Stretch ? Stretch::Stretch_UniformToFill : Stretch::Stretch_None));

        ComPtr<IStyle> style;
        std::wstring styleName = XamlStyleKeyGenerators::GenerateKeyForImage(adaptiveImage.Get());
        if (SUCCEEDED(TryGetStyleFromResourceDictionaries(styleName, &style)))
        {
            ComPtr<IFrameworkElement> imageAsFrameworkElement;
            THROW_IF_FAILED(xamlImage.As(&imageAsFrameworkElement));
            THROW_IF_FAILED(imageAsFrameworkElement->put_Style(style.Get()));
        }

        XamlHelpers::AppendXamlElementToPanel(xamlImage, parentPanel);
    }
}}