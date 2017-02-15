#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "ImageLoadTracker.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class XamlBuilder
    {
    public:
        XamlBuilder();

        void BuildXamlTreeFromAdaptiveCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard, _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** xamlTreeRoot);

    private:
        std::unordered_map<ABI::AdaptiveCards::XamlCardRenderer::ElementType, 
            std::function<void(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*,
                ABI::Windows::UI::Xaml::Controls::IPanel*)>> m_adaptiveElementBuilder;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IPropertyValueStatics> m_propertyValueStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary>> m_resourceDictionaries;
        ImageLoadTracker m_imageLoadTracker;

        void EnsurePropertyValueStatics();
        bool TryGetStyleFromResourceDictionaries(
            _In_ std::wstring styleName,
            _COM_Outptr_result_maybenull_ ABI::Windows::UI::Xaml::IStyle** style);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IPanel> CreateRootPanelFromAdaptiveCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IImageSource> LoadImageFromUrl(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl);

        void BuildTextBlock(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel);
        void BuildImage(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel);
    };
}}