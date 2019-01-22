#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "ImageLoadTracker.h"
#include "IXamlBuilderListener.h"
#include "IImageLoadTrackerListener.h"
#include <windows.storage.h>
#include "InputValue.h"
#include "RenderedAdaptiveCard.h"
#include "AdaptiveRenderContext.h"
#include <windows.ui.xaml.shapes.h>

namespace AdaptiveNamespace
{
    class AdaptiveCardRenderer;

    class XamlBuilder
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, Microsoft::WRL::FtmBase, AdaptiveNamespace::IImageLoadTrackerListener>
    {
        AdaptiveRuntimeStringClass(XamlBuilder);

    public:
        XamlBuilder();

        // IImageLoadTrackerListener
        STDMETHODIMP AllImagesLoaded();
        STDMETHODIMP ImagesLoadingHadError();

        static void BuildXamlTreeFromAdaptiveCard(
            _In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
            _Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** xamlTreeRoot,
            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
            std::shared_ptr<XamlBuilder> xamlBuilder,
            boolean isOuterCard = true,
            ABI::AdaptiveNamespace::ContainerStyle defaultContainerStyle = ABI::AdaptiveNamespace::ContainerStyle::Default);
        HRESULT AddListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT RemoveListener(_In_ IXamlBuilderListener* listener) noexcept;
        HRESULT SetFixedDimensions(UINT width, UINT height) noexcept;
        HRESULT SetEnableXamlImageHandling(bool enableXamlImageHandling) noexcept;

        void BuildImage(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                        _Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageControl);

        static void BuildTextBlock(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBlockControl);
        static void BuildContainer(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** containerControl);
        static void BuildColumn(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                _Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnControl);
        static void BuildColumnSet(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** columnSetControl);
        static void BuildFactSet(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                 _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                 _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                 _Outptr_ ABI::Windows::UI::Xaml::IUIElement** factSetControl);
        static void BuildImageSet(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                  _Outptr_ ABI::Windows::UI::Xaml::IUIElement** imageSetControl);
        static void BuildChoiceSetInput(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                        _Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        static void BuildDateInput(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** dateInputControl);
        static void BuildNumberInput(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ ABI::Windows::UI::Xaml::IUIElement** numberInputControl);
        static void BuildTextInput(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** textInputControl);
        static void BuildTimeInput(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** timeInputControl);
        static void BuildToggleInput(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                     _Outptr_ ABI::Windows::UI::Xaml::IUIElement** toggleInputControl);
        static void BuildMedia(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                               _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                               _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                               _Outptr_ ABI::Windows::UI::Xaml::IUIElement** mediaControl);
        static void BuildActionSet(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** containerControl);

        template<typename T>
        static HRESULT TryGetResourceFromResourceDictionaries(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* resourceDictionary,
                                                              std::wstring resourceName,
                                                              _COM_Outptr_result_maybenull_ T** resource);

        static HRESULT TryInsertResourceToResourceDictionaries(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* resourceDictionary,
                                                               std::wstring resourceName,
                                                               _In_ IInspectable* value);

        static HRESULT SetStyleFromResourceDictionary(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                                      std::wstring resourceName,
                                                      _In_ ABI::Windows::UI::Xaml::IFrameworkElement* frameworkElement);

        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> GetSolidColorBrush(_In_ ABI::Windows::UI::Color color);

    private:
        ImageLoadTracker m_imageLoadTracker;
        std::set<Microsoft::WRL::ComPtr<IXamlBuilderListener>> m_listeners;
        Microsoft::WRL::ComPtr<ABI::Windows::Storage::Streams::IRandomAccessStreamStatics> m_randomAccessStreamStatics;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<ABI::Windows::Storage::Streams::IInputStream*, ABI::Windows::Web::Http::HttpProgress>>> m_getStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT64, UINT64>>> m_copyStreamOperations;
        std::vector<Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncOperationWithProgress<UINT32, UINT32>>> m_writeAsyncOperations;

        UINT m_fixedWidth = 0;
        UINT m_fixedHeight = 0;
        bool m_fixedDimensions = false;
        bool m_enableXamlImageHandling = false;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers> m_resourceResolvers;

        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement>
        CreateRootCardElement(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                              std::shared_ptr<XamlBuilder> xamlBuilder,
                              _Outptr_ ABI::Windows::UI::Xaml::Controls::IPanel** bodyElementContainer);

        static void ApplyBackgroundToRoot(_In_ ABI::Windows::UI::Xaml::Controls::IPanel* rootPanel,
                                          _In_ HSTRING url,
                                          _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                          _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);

        template<typename T>
        void SetAutoSize(T* destination,
                         IInspectable* parentElement,
                         IInspectable* imageContainer,
                         bool isVisible,
                         bool imageFiresOpenEvent);

        template<typename T>
        void SetImageSource(T* destination,
                            ABI::Windows::UI::Xaml::Media::IImageSource* imageSource,
                            ABI::Windows::UI::Xaml::Media::Stretch stretch = Stretch_UniformToFill);
        template<typename T>
        void SetImageOnUIElement(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl,
                                 T* uiElement,
                                 ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers* resolvers,
                                 bool isSizeAuto,
                                 IInspectable* parentElement,
                                 IInspectable* imageContainer,
                                 bool isVisible,
                                 _Out_ bool* mustHideElement,
                                 ABI::Windows::UI::Xaml::Media::Stretch stretch = Stretch_UniformToFill);

        template<typename T>
        void PopulateImageFromUrlAsync(_In_ ABI::Windows::Foundation::IUriRuntimeClass* imageUrl, _In_ T* imageControl);
        void FireAllImagesLoaded();
        void FireImagesLoadingHadError();
        static void BuildShowCard(ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig* showCardActionConfig,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                  bool isBottomActionBar,
                                  _Outptr_ ABI::Windows::UI::Xaml::IUIElement** uiShowCard);

        static void ArrangeButtonContent(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                                         _In_ ABI::AdaptiveNamespace::IAdaptiveActionsConfig* actionsConfig,
                                         _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                         ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                         _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                         bool allActionsHaveIcons,
                                         _In_ ABI::Windows::UI::Xaml::Controls::IButton* button);

        static void BuildActions(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* children,
                                 _In_ ABI::Windows::UI::Xaml::Controls::IPanel* bodyPanel,
                                 bool insertSeparator,
                                 _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                 ABI::AdaptiveNamespace::ContainerStyle containerStyle);

        static void BuildActionSetHelper(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* children,
                                         ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                         bool isBottomActionBar,
                                         ABI::Windows::UI::Xaml::IUIElement** actionSetControl,
                                         ABI::AdaptiveNamespace::ContainerStyle containerStyle);

        static void XamlBuilder::HandleInlineAcion(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                                   _In_ ABI::Windows::UI::Xaml::Controls::ITextBox* textBox,
                                                   _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* inlineAction,
                                                   _Outptr_ ABI::Windows::UI::Xaml::IUIElement** textBoxWithInlineAction);

        static Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> CreateSeparator(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                                                                          UINT spacing,
                                                                                          UINT separatorThickness,
                                                                                          ABI::Windows::UI::Color separatorColor,
                                                                                          bool isHorizontal = true);
        static void ApplyMarginToXamlElement(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                             _In_ ABI::Windows::UI::Xaml::IFrameworkElement* element);
        static void StyleXamlTextBlock(ABI::AdaptiveNamespace::FontStyle fontStyle,
                                       ABI::AdaptiveNamespace::TextSize size,
                                       ABI::AdaptiveNamespace::ForegroundColor color,
                                       ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                       bool isSubtle,
                                       bool wrap,
                                       UINT32 maxWidth,
                                       ABI::AdaptiveNamespace::TextWeight weight,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig);
        static void StyleXamlTextBlock(_In_ ABI::AdaptiveNamespace::IAdaptiveTextConfig* textConfig,
                                       ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                       _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig);
        static void BuildPanelChildren(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* children,
                                       _In_ ABI::Windows::UI::Xaml::Controls::IPanel* parentPanel,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* context,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                       std::function<void(ABI::Windows::UI::Xaml::IUIElement* child)> childCreatedCallback);
        static void GetSeparationConfigForElement(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* element,
                                                  _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                                  _Out_ UINT* spacing,
                                                  _Out_ UINT* separatorThickness,
                                                  _Out_ ABI::Windows::UI::Color* separatorColor,
                                                  _Out_ bool* needsSeparator);
        static void BuildCompactChoiceSetInput(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                               _In_ ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput* adaptiveChoiceSetInput,
                                               _Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceInputSetControl);
        static void BuildExpandedChoiceSetInput(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                                _In_ ABI::AdaptiveNamespace::IAdaptiveChoiceSetInput* adaptiveChoiceInputSet,
                                                boolean isMultiSelect,
                                                _Outptr_ ABI::Windows::UI::Xaml::IUIElement** choiceSetInputControl);
        static bool SupportsInteractivity(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig);

        static void WrapInTouchTarget(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                      _In_ ABI::Windows::UI::Xaml::IUIElement* elementToWrap,
                                      _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                                      _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                      bool fullWidth,
                                      const std::wstring& style,
                                      _Outptr_ ABI::Windows::UI::Xaml::IUIElement** finalElement);

        void static HandleSelectAction(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* adaptiveCardElement,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* selectAction,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                       _In_ ABI::Windows::UI::Xaml::IUIElement* uiElement,
                                       bool supportsInteractivity,
                                       bool fullWidthTouchTarget,
                                       _Outptr_ ABI::Windows::UI::Xaml::IUIElement** outUiElement);

        static void WireButtonClickToAction(_In_ ABI::Windows::UI::Xaml::Controls::IButton* button,
                                            _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext);

        static HRESULT AddHandledTappedEvent(_In_ ABI::Windows::UI::Xaml::IUIElement* uiElement);

        static HRESULT SetAutoImageSize(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* imageControl,
                                        _In_ IInspectable* parentElement,
                                        _In_ ABI::Windows::UI::Xaml::Media::Imaging::IBitmapSource* imageSource,
                                        bool setVisible);

        static HRESULT SetMatchingHeight(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToChange,
                                         _In_ ABI::Windows::UI::Xaml::IFrameworkElement* elementToMatch);

        template<typename T>
        static void SetVerticalContentAlignmentToChildren(_In_ T* container,
                                                          _In_ ABI::AdaptiveNamespace::VerticalContentAlignment verticalContentAlignment);

        static HRESULT HandleToggleVisibilityClick(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                                   _In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action);
    };
}
