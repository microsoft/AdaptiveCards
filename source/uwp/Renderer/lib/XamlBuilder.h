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
        InspectableClass(L"AdaptiveCards.XamlCardRenderer.XamlBuilder", BaseTrust)
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        STDMETHODIMP AllImagesLoaded();

        void BuildXamlTreeFromAdaptiveCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard, _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** xamlTreeRoot);
        HRESULT AddListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT RemoveListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT SetFixedDimensions(_In_ UINT width, _In_ UINT height) noexcept;
        HRESULT SetRenderOptions(_In_ ABI::AdaptiveCards::XamlCardRenderer::RenderOptions renderOptions) noexcept;
        HRESULT SetEnableXamlImageHandling(_In_ bool enableXamlImageHandling) noexcept;
        HRESULT SetBackgroundImageUri(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUri) noexcept;
        HRESULT SetOverrideDictionary(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary) noexcept;
        HRESULT SetHostOptions(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostOptions* hostOptions) noexcept;

    private:
        std::unordered_map<ABI::AdaptiveCards::XamlCardRenderer::ElementType, 
            std::function<void(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*,
                ABI::Windows::UI::Xaml::IUIElement**)>> m_adaptiveElementBuilder;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IPropertyValueStatics> m_propertyValueStatics;
        ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;
std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*, ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT64, UINT64>>> m_copyStreamOperations;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> m_backgroundImageUri;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_mergedResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_defaultResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostOptions> m_hostOptions;

        UINT m_fixedWidth = 0;
        UINT m_fixedHeight = 0;
        bool m_fixedDimensions = false;
        ABI::AdaptiveCards::XamlCardRenderer::RenderOptions m_renderOptions = ABI::AdaptiveCards::XamlCardRenderer::RenderOptions::None;
        bool m_enableXamlImageHandling = false;

        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateSeparator(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* separationOptions,
            _In_ bool isHorizontal = true);

        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> GetFontColorFromHostOptions(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextColor textColor, bool isSubtle);
        void InitializeDefaultResourceDictionary();
        template<typename T>
        HRESULT TryGetResoureFromResourceDictionaries(
            _In_ std::wstring resourceName,
            _COM_Outptr_result_maybenull_ T** resource);
        template<typename T>
        bool TryGetValueResourceFromResourceDictionaries(
            _In_ std::wstring styleName,
            _Out_ T* valueResource);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateRootCardElement(_COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** childElementContainer);
        void ApplyBackgroundToRoot(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel);
        template<typename T>
        void SetImageSource(T* destination, ABI::Windows::UI::Xaml::Media::IImageSource* imageSource);
        template<typename T>
        void SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, T* uiElement);
        template<typename T>
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, T* imageControl);
        void FireAllImagesLoaded();
        void BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback);
        void GetSeparationOptionsForElement(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* element,
            _In_ ABI::AdaptiveCards::XamlCardRenderer::SeparationStyle separation,
            _COM_Outptr_result_maybenull_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions** separationOptions);
        void AppendSeparatorToPanel(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* separation,
            _Inout_ ABI::Windows::UI::Xaml::Controls::IPanel* panel,
            _In_ bool isHorizontalSeparator = true);
        template<typename T>
        void SetContent(T* item, HSTRING contentString);
        template<typename T>
        void SetToggleValue(T* item, boolean isChecked);

        void BuildTextBlock(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBlockControl);
        void BuildImage(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);
        void BuildContainer(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** containerControl);
        void BuildColumnSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnControl);
        void BuildFactSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** factSetControl);
        void BuildImageSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageSetControl);
        void BuildCompactInputChoiceSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputChoiceSet* adaptiveInputChoiceSet,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputChoiceSetControl);
        void BuildExpandedInputChoiceSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveInputChoiceSet* adaptiveInputChoiceSet,
            boolean isMultiSelect,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputChoiceSetControl);
        void BuildInputChoiceSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputChoiceSetControl);
        void BuildInputDate(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputDateControl);
        void BuildInputNumber(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputDateControl);
        void BuildInputText(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputTextControl);
        void BuildInputTime(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputTimeControl);
        void BuildInputToggle(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** inputToggleControl);
    };
}}