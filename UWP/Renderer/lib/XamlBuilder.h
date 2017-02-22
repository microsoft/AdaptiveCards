#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include <windows.storage.h>

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class XamlBuilder : public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::FtmBase,
        AdaptiveCards::XamlCardRenderer::IImageLoadTrackerListener>
    {
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        STDMETHODIMP AllImagesLoaded();

        void BuildXamlTreeFromAdaptiveCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard, _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** xamlTreeRoot);
        HRESULT AddListener(IXamlBuilderListener* listener);
        HRESULT RemoveListener(IXamlBuilderListener* listener);

    private:
        std::unordered_map<ABI::AdaptiveCards::XamlCardRenderer::ElementType, 
            std::function<void(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*,
                ABI::Windows::UI::Xaml::IUIElement**)>> m_adaptiveElementBuilder;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IPropertyValueStatics> m_propertyValueStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary>> m_resourceDictionaries;
        ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;

        void InitializeDefaultResourceDictionary();
        template<typename T>
        bool TryGetResoureFromResourceDictionaries(
            _In_ std::wstring styleName,
            _COM_Outptr_result_maybenull_ T** resource);
        template<typename T>
        bool TryGetValueResoureFromResourceDictionaries(
            _In_ std::wstring styleName,
            _Out_ T* valueResource);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Controls::IPanel> CreateRootPanelFromAdaptiveCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard);
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, ABI::Windows::UI::Xaml::Controls::IImage* imageControl);
        void FireAllImagesLoaded();
        void BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback);

        void BuildTextBlock(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBlockControl);
        void BuildImage(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);
        void BuildContainer(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** containerControl);
    };
}}