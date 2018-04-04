#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include <windows.storage.h>
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveRenderContext.h"

AdaptiveNamespaceStart
    class AdaptiveCardRenderer;

    class XamlBuilder : public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::FtmBase,
        AdaptiveNamespace::IImageLoadTrackerListener>
    {
        AdaptiveRuntimeStringClass(XamlBuilder)
    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        STDMETHODIMP AllImagesLoaded();
        STDMETHODIMP ImagesLoadingHadError();

        void BuildXamlTreeFromAdaptiveCard(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
            _Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** xamlTreeRoot,
            _In_ AdaptiveNamespace::AdaptiveCardRenderer* renderer,
            _In_ AdaptiveNamespace::AdaptiveRenderContext* renderContext,
            boolean isOuterCard = true,
            ABI::AdaptiveNamespace::ContainerStyle defaultContainerStyle = ABI::AdaptiveNamespace::ContainerStyle::Default);
        HRESULT AddListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT RemoveListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT SetFixedDimensions(_In_ UINT width, _In_ UINT height) noexcept;
        HRESULT SetEnableXamlImageHandling(_In_ bool enableXamlImageHandling) noexcept;

        void BuildImage(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);

        static void BuildTextBlock(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBlockControl);
        static void BuildContainer(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** containerControl);
        static void BuildColumn(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnControl);
        static void BuildColumnSet(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnSetControl);
        static void BuildFactSet(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** factSetControl);
        static void BuildImageSet(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageSetControl);
        static void BuildChoiceSetInput(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        static void BuildDateInput(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** dateInputControl);
        static void BuildNumberInput(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** numberInputControl);
        static void BuildTextInput(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** textInputControl);
        static void BuildTimeInput(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** timeInputControl);
        static void BuildToggleInput(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** toggleInputControl);
        template<typename T>
        static HRESULT TryGetResourceFromResourceDictionaries(
            _In_ ABI::Windows::UI::Xaml::IResourceDictionary* resourceDictionary,
            _In_ std::wstring resourceName,
            _COM_Outptr_result_maybenull_ T** resource);

        static HRESULT SetStyleFromResourceDictionary(
            ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            std::wstring resourceName,
            ABI::Windows::UI::Xaml::IFrameworkElement* frameworkElement);

    private:
        ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*, ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT64, UINT64>>> m_copyStreamOperations;

        UINT m_fixedWidth = 0;
        UINT m_fixedHeight = 0;
        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers> m_resourceResolvers;

        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateRootCardElement(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** outerElementContainer,
            _Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** bodyElementContainer);

        void ApplyBackgroundToRoot(
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
            _In_ ABI::Windows::Foundation::IUriRuntimeClass* uri,
            _Inout_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);
        template<typename T>
        void SetImageSource(T* destination, ABI::Windows::UI::Xaml::Media::IImageSource* imageSource);
        template<typename T>
        void SetImageOnUIElement(
            _In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl,
            T* uiElement,
            ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers* resolvers);
        template<typename T>
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, T* imageControl);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
        void BuildShowCard(
            AdaptiveNamespace::AdaptiveCardRenderer* renderer,
            ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig* showCardActionConfig,
            ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
            _Inout_ AdaptiveNamespace::AdaptiveRenderContext* renderContext,
            ABI::Windows::UI::Xaml::IUIElement** uiShowCard);

        void ArrangeButtonContent(
            _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
            _In_ ABI::AdaptiveNamespace::IAdaptiveActionsConfig* actionsConfig,
            _In_ AdaptiveNamespace::AdaptiveRenderContext* renderContext,
             ABI::AdaptiveNamespace::ContainerStyle containerStyle,
            _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
            _Inout_ ABI::Windows::UI::Xaml::Controls::IButton* button);
        void BuildActions(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* children,
            _In_ AdaptiveNamespace::AdaptiveCardRenderer* renderer,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* bodyPanel,
            _In_ bool insertSeparator,
            _Inout_ AdaptiveNamespace::AdaptiveRenderContext* renderContext,
            ABI::AdaptiveNamespace::ContainerStyle containerStyle);

        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateSeparator(
            _Inout_  ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            UINT spacing, UINT separatorThickness, ABI::Windows::UI::Color separatorColor, bool isHorizontal = true);
        static void ApplyMarginToXamlElement(
            _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
            _Inout_ ABI::Windows::UI::Xaml::IFrameworkElement* element);
        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> GetSolidColorBrush(_In_ ABI::Windows::UI::Color color);
        static void StyleXamlTextBlock(
            _In_ ABI::AdaptiveNamespace::TextSize size,
            _In_ ABI::AdaptiveNamespace::ForegroundColor color,
            ABI::AdaptiveNamespace::ContainerStyle containerStyle,
            _In_ bool isSubtle,
            bool wrap,
            UINT32 maxWidth,
            _In_ ABI::AdaptiveNamespace::TextWeight weight,
            _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock,
            _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig);
        static void StyleXamlTextBlock(
            _In_ ABI::AdaptiveNamespace::IAdaptiveTextConfig* textConfig,
            ABI::AdaptiveNamespace::ContainerStyle containerStyle,
            _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock,
            _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig);
        static void BuildPanelChildren(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* children,
            _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* context,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
            _In_ std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback);
        static void GetSeparationConfigForElement(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* element,
            _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
            _Out_ UINT* spacing,
            _Out_ UINT* separatorThickness,
            _Out_ ABI::Windows::UI::Color* separatorColor,
            _Out_ bool* needsSeparator);
        static void BuildCompactChoiceSetInput(
            ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSetControl);
        static void BuildExpandedChoiceSetInput(
            ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput* adaptiveChoiceInputSet,
            boolean isMultiSelect,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        static bool SupportsInteractivity(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig);

        static void WrapInTouchTarget(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::Windows::UI::Xaml::IUIElement* elementToWrap,
            _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
            _Inout_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            bool fullWidth,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** finalElement);

        void static HandleSelectAction(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
            _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* selectAction,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            _In_ ABI::Windows::UI::Xaml::IUIElement* uiElement,
            bool supportsInteractivity,
            bool fullWidthTouchTarget,
            _Outptr_ ABI::Windows::UI::Xaml::IUIElement** outUiElement);

        static void WireButtonClickToAction(
            _In_ ABI::Windows::UI::Xaml::Controls::IButton* button,
            _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
            _Inout_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext);

        static HRESULT AddHandledTappedEvent(_In_ ABI::Windows::UI::Xaml::IUIElement* uiElement);

        static HRESULT SetAutoImageSize(
            _In_ ABI::Windows::UI::Xaml::IFrameworkElement* imageControl,
            _In_ IInspectable* parentElement,
            _In_ ABI::Windows::UI::Xaml::Media::Imaging::IBitmapSource* imageSource);

        static HRESULT SetImageSizeAsTextBlockSize(
            _In_ ABI::Windows::UI::Xaml::IFrameworkElement* imageControl,
            _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock);

    };
AdaptiveNamespaceEnd