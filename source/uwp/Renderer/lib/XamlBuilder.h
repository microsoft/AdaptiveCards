#pragma once

#include "AdaptiveCards.Uwp.h"
#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include "AdaptiveCardRendererComponent.h"
#include <windows.storage.h>
#include "InputItem.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveRenderContext.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveCardRenderer;

    class XamlBuilder : public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::FtmBase,
        AdaptiveCards::Uwp::IImageLoadTrackerListener>
    {
        InspectableClass(L"AdaptiveCards.Uwp.XamlBuilder", BaseTrust)
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        STDMETHODIMP AllImagesLoaded();
        STDMETHODIMP ImagesLoadingHadError();

        void BuildXamlTreeFromAdaptiveCard(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** xamlTreeRoot,
            _In_ AdaptiveCards::Uwp::AdaptiveCardRenderer* renderer,
            _In_ AdaptiveCards::Uwp::AdaptiveRenderContext* renderContext,
            boolean isOuterCard = true,
            ABI::AdaptiveCards::Uwp::ContainerStyle defaultContainerStyle = ABI::AdaptiveCards::Uwp::ContainerStyle::Default);
        HRESULT AddListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT RemoveListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT SetFixedDimensions(_In_ UINT width, _In_ UINT height) noexcept;
        HRESULT SetEnableXamlImageHandling(_In_ bool enableXamlImageHandling) noexcept;
        HRESULT SetOverrideDictionary(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary) noexcept;
        HRESULT SetHostConfig(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig) noexcept;

        void BuildTextBlock(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBlockControl);
        void BuildImage(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);
        void BuildContainer(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** containerControl);
        void BuildColumn(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnControl);
        void BuildColumnSet(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnSetControl);
        void BuildFactSet(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** factSetControl);
        void BuildImageSet(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageSetControl);
        void BuildChoiceSetInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        void BuildDateInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** dateInputControl);
        void BuildNumberInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** numberInputControl);
        void BuildTextInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** textInputControl);
        void BuildTimeInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** timeInputControl);
        void BuildToggleInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** toggleInputControl);

    private:

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardRenderer> m_renderer;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IPropertyValueStatics> m_propertyValueStatics;
        ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*, ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT64, UINT64>>> m_copyStreamOperations;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_mergedResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IResourceDictionary> m_defaultResourceDictionary;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig> m_hostConfig;

        UINT m_fixedWidth = 0;
        UINT m_fixedHeight = 0;
        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardResourceResolvers> m_resourceResolvers;

        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateSeparator(
            UINT spacing, UINT separatorThickness, ABI::Windows::UI::Color separatorColor, bool isHorizontal = true);
        void ApplyMarginToXamlElement(
            _Inout_ ABI::Windows::UI::Xaml::IFrameworkElement* element);
        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> GetSolidColorBrush(_In_ ABI::Windows::UI::Color color);
        void StyleXamlTextBlock(
            _In_ ABI::AdaptiveCards::Uwp::TextSize size,
            _In_ ABI::AdaptiveCards::Uwp::ForegroundColor color,
            ABI::AdaptiveCards::Uwp::ContainerStyle containerStyle,
            _In_ bool isSubtle,
            bool wrap,
            UINT32 maxWidth,
            _In_ ABI::AdaptiveCards::Uwp::TextWeight weight,
            _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock);
        void StyleXamlTextBlock(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveTextConfig* textConfig,
            ABI::AdaptiveCards::Uwp::ContainerStyle containerStyle,
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
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCard* adaptiveCard,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _COM_Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** childElementContainer);
        void ApplyBackgroundToRoot(
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
            _In_ ABI::Windows::Foundation::IUriRuntimeClass* uri,
            _In_ _Inout_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext);
        template<typename T>
        void SetImageSource(T* destination, ABI::Windows::UI::Xaml::Media::IImageSource* imageSource);
        template<typename T>
        void SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, T* uiElement);
        template<typename T>
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, T* imageControl);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
        void BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* context,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs* renderArgs,
            _In_ std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback);
        void BuildShowCard(
            AdaptiveCards::Uwp::AdaptiveCardRenderer* renderer,
            ABI::AdaptiveCards::Uwp::IAdaptiveShowCardActionConfig* showCardActionConfig,
            ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* action,
            _Inout_ AdaptiveCards::Uwp::AdaptiveRenderContext* renderContext,
            ABI::Windows::UI::Xaml::IUIElement** uiShowCard);
        void BuildActions(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement*>* children,
            _In_ AdaptiveCards::Uwp::AdaptiveCardRenderer* renderer,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ bool insertSeparator,
            _Inout_ AdaptiveCards::Uwp::AdaptiveRenderContext* renderContext);
        void GetSeparationConfigForElement(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* element,
            _Out_ UINT* spacing,
            _Out_ UINT* separatorThickness,
            _Out_ ABI::Windows::UI::Color* separatorColor,
            _Out_ bool* needsSeparator);
        void BuildCompactChoiceSetInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSetControl);
        void BuildExpandedChoiceSetInput(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveChoiceSetInput* adaptiveChoiceInputSet,
            boolean isMultiSelect,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        bool SupportsInteractivity();

        void WrapInFullWidthTouchTarget(
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::Windows::UI::Xaml::IUIElement* elementToWrap,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* action,
            _Inout_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** finalElement);

        void WireButtonClickToAction(
            _In_ ABI::Windows::UI::Xaml::Controls::IButton* button,
            _In_ ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* action,
            _Inout_ ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext* renderContext);

        HRESULT AddHandledTappedEvent(_In_ ABI::Windows::UI::Xaml::IUIElement* uiElement);
    };
}}