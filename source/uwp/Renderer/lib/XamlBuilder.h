#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include "XamlCardRendererComponent.h"
#include <windows.storage.h>
#include "InputItem.h"

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
        STDMETHODIMP ImagesLoadingHadError();

        void BuildXamlTreeFromAdaptiveCard(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard, 
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** xamlTreeRoot, 
            AdaptiveCards::XamlCardRenderer::XamlCardRenderer* renderer,
            boolean isOuterCard = true);
        HRESULT AddListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT RemoveListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT SetFixedDimensions(_In_ UINT width, _In_ UINT height) noexcept;
        HRESULT SetRenderOptions(_In_ ABI::AdaptiveCards::XamlCardRenderer::RenderOptions renderOptions) noexcept;
        HRESULT SetEnableXamlImageHandling(_In_ bool enableXamlImageHandling) noexcept;
        HRESULT SetOverrideDictionary(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary) noexcept;
        HRESULT SetHostConfig(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* hostConfig) noexcept;

    private:
        std::unordered_map<ABI::AdaptiveCards::XamlCardRenderer::ElementType, 
            std::function<void(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*,
                std::shared_ptr<std::vector<InputItem>> inputElements,
                ABI::Windows::UI::Xaml::IUIElement**)>> m_adaptiveElementBuilder;

        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IPropertyValueStatics> m_propertyValueStatics;
        ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*, ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT64, UINT64>>> m_copyStreamOperations;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_mergedResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_defaultResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Text::IFontWeightsStatics> m_fontWeightsStatics;

        UINT m_fixedWidth = 0;
        UINT m_fixedHeight = 0;
        bool m_fixedDimensions = false;
        ABI::AdaptiveCards::XamlCardRenderer::RenderOptions m_renderOptions = ABI::AdaptiveCards::XamlCardRenderer::RenderOptions::None;
        bool m_enableXamlImageHandling = false;

        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateSeparator(
            UINT spacing, UINT separatorThickness, ABI::Windows::UI::Color separatorColor, bool isHorizontal = true);
        static void ApplyMarginToXamlElement(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition* spacingDefinition,
            _Inout_ ABI::Windows::UI::Xaml::IFrameworkElement* element);
        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> GetSolidColorBrush(_In_ ABI::Windows::UI::Color color);
        static ABI::Windows::UI::Xaml::Thickness ThicknessFromSpacingDefinition(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition* spacingDefinition);
        void StyleXamlTextBlock(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::TextSize size,
            _In_ ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor color,
            _In_ bool isSubtle,
            _In_ ABI::AdaptiveCards::XamlCardRenderer::TextWeight weight,
            _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock);
        void StyleXamlTextBlock(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig* textConfig,
            _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock);
        void InitializeDefaultResourceDictionary();
        template<typename T>
        HRESULT TryGetResoureFromResourceDictionaries(
            _In_ std::wstring resourceName,
            _COM_Outptr_result_maybenull_ T** resource);
        template<typename T>
        bool TryGetValueResourceFromResourceDictionaries(
            _In_ std::wstring styleName,
            _Out_ T* valueResource);
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateRootCardElement(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** childElementContainer);
        void ApplyBackgroundToRoot(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel, _In_ ABI::Windows::Foundation::IUriRuntimeClass* uri);
        template<typename T>
        void SetImageSource(T* destination, ABI::Windows::UI::Xaml::Media::IImageSource* imageSource);
        template<typename T>
        void SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, T* uiElement);
        template<typename T>
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, T* imageControl);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
        void BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _In_ std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback);
        void BuildShowCard(
            AdaptiveCards::XamlCardRenderer::XamlCardRenderer* renderer,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardActionConfig* showCardActionConfig,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement* action,
            ABI::Windows::UI::Xaml::IUIElement** uiShowCard);
        void BuildActions(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*>* children,
            AdaptiveCards::XamlCardRenderer::XamlCardRenderer* renderer,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ bool insertSeparator);
        void GetSeparationConfigForElement(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* element,
            _Out_ UINT* spacing,
            _Out_ UINT* separatorThickness,
            _Out_ ABI::Windows::UI::Color* separatorColor,
            _Out_ bool* needsSeparator);

        template<typename T>
        void AddInputItemToVector(
            std::shared_ptr<std::vector<InputItem>> inputElements,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* cardElement,
            T* tElement);

        void BuildTextBlock(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBlockControl);
        void BuildImage(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);
        void BuildContainer(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** containerControl);
        void BuildColumn(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnControl);
        void BuildColumnSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnSetControl);
        void BuildFactSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** factSetControl);
        void BuildImageSet(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageSetControl);
        void BuildCompactChoiceSetInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSetControl);
        void BuildExpandedChoiceSetInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceSetInput* adaptiveChoiceInputSet,
            boolean isMultiSelect,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        void BuildChoiceSetInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        void BuildDateInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** dateInputControl);
        void BuildNumberInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** numberInputControl);
        void BuildTextInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textInputControl);
        void BuildTimeInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** timeInputControl);
        void BuildToggleInput(
            _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement* adaptiveCardElement,
            std::shared_ptr<std::vector<InputItem>> inputElements,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** toggleInputControl);
        bool SupportsInteractivity();
    };
}}