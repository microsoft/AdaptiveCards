// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "XamlBuilder.h"

class TextRunStyleParameters
{
public:
    TextRunStyleParameters() : m_isStrikethrough(false), m_isItalic(false), m_isUnderline(false), m_isInHyperlink(false)
    {
    }

    TextRunStyleParameters(bool isStrikethrough, bool isItalic, bool isUnderline, bool isInHyperlink) :
        m_isStrikethrough(isStrikethrough), m_isItalic(isItalic), m_isUnderline(isUnderline), m_isInHyperlink(isInHyperlink)
    {
    }

    bool IsStrikethrough() const { return m_isStrikethrough; }
    bool IsItalic() const { return m_isItalic; }
    bool IsUnderline() const { return m_isUnderline; }
    bool IsInHyperlink() const { return m_isInHyperlink; }

private:
    bool m_isStrikethrough{};
    bool m_isItalic{};
    bool m_isUnderline{};
    bool m_isInHyperlink{};
};

uint32_t AddHtmlInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Documents::Inline> inlines);

HRESULT AddHtmlInlines(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       bool isInHyperlink,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_ UINT* characterLength);

uint32_t AddTextInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        // TODO: should it be const& or const TextRunStyleParameters&??
                        TextRunStyleParameters const& styleParameters,
                        winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines);

HRESULT AddTextInlines(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       const TextRunStyleParameters& styleParameters,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_ UINT* characterLength);

uint32_t AddSingleTextInline(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs,
                             winrt::hstring const& stringToParse,
                             // TODO: should it be const TextRunStyleParameters& ?
                             TextRunStyleParameters const& styleParameters,
                             winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines);

HRESULT AddSingleTextInline(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                            _In_ HSTRING string,
                            const TextRunStyleParameters& styleParameters,
                            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                            _Out_ UINT* characterLength);

HRESULT SetXamlInlines(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                       bool isInHyperlink,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_opt_ UINT* characterLength = nullptr);

uint32_t SetXamlInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines);

void SetXamlInlinesWithTextStyleConfig(rtom::IAdaptiveTextElement const& textElement,
                                       rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs,
                                       rtrender::AdaptiveTextStyleConfig const& textStyleConfig,
                                       rtxaml::Controls::TextBlock const& textBlock);

HRESULT SetXamlInlinesWithTextStyleConfig(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* textElement,
                                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveTextStyleConfig* textConfig,
                                          _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock);

void SetXamlInlinesWithTextStyleConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs,
                                       rtrender::AdaptiveTextStyleConfig const& textStyle,
                                       rtom::IAdaptiveTextElement const& textElement, // TODO: optional?
                                       winrt::hstring const& language,
                                       winrt::hstring const& text,
                                       rtxaml::Controls::TextBlock const& textBlock);

HRESULT SetXamlInlinesWithTextStyleConfig(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveTextStyleConfig* textStyle,
                                          _In_opt_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* textElement,
                                          _In_ HSTRING language,
                                          _In_ HSTRING text,
                                          _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock);

void SetXamlInlinesWithFactSetTextConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                         rtrender::AdaptiveRenderArgs const& renderArgs,
                                         rtrender::AdaptiveFactSetTextConfig const& factSetTextConfig,
                                         winrt::hstring const& language,
                                         winrt::hstring const& text,
                                         rtxaml::Controls::TextBlock const& textBlock);

HRESULT SetXamlInlinesWithFactSetTextConfig(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                                            _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig* textConfig,
                                            _In_ HSTRING language,
                                            _In_ HSTRING text,
                                            _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock);

void SetWrapProperties(rtxaml::Controls::TextBlock const& xamlTextBlock, bool wrap);

HRESULT SetWrapProperties(_In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock, bool wrap);

void StyleXamlTextBlockProperties(rtom::AdaptiveTextBlock const& adaptiveTextBlock,
                                  rtrender::AdaptiveRenderContext const& renderContext,
                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                  rtxaml::Controls::TextBlock const& xamlTextBlock);

HRESULT StyleXamlTextBlockProperties(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextBlock* adaptiveTextBlock,
                                     _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                                     _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                                     _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock);

template<typename TAdaptiveType, typename TXamlTextBlockType>
HRESULT SetHorizontalAlignment(_In_ TAdaptiveType* adaptiveTextBlock,
                               _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                               _In_ TXamlTextBlockType* xamlTextBlock)
{
    ComPtr<IReference<HAlignment>> adaptiveHorizontalAlignmentReference;
    RETURN_IF_FAILED(adaptiveTextBlock->get_HorizontalAlignment(&adaptiveHorizontalAlignmentReference));

    // If the text block doesn't have horizontal alignment set, check the render args for a parent value
    if (adaptiveHorizontalAlignmentReference == nullptr)
    {
        RETURN_IF_FAILED(renderContext->get_HorizontalContentAlignment(&adaptiveHorizontalAlignmentReference));
    }

    HAlignment horizontalAlignment = ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment::Left;
    if (adaptiveHorizontalAlignmentReference != nullptr)
    {
        RETURN_IF_FAILED(adaptiveHorizontalAlignmentReference->get_Value(&horizontalAlignment));
    }

    ComPtr<TXamlTextBlockType> xamlTextBlockComptr(xamlTextBlock);
    ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> xamlTextBlockAsFrameworkElement;
    RETURN_IF_FAILED(xamlTextBlockComptr.As(&xamlTextBlockAsFrameworkElement));

    switch (horizontalAlignment)
    {
    case ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment::Left:
        // text block stretches to both ends of its parent horizontally if its horizontal alignment is not set,
        // this can lead to unexpected behavior such as hyper link being active in the streched space
        // setting the horizontal alignment, aligns the textblock instead of stretching
        RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
            ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Left));
        RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Left));
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment::Right:
        RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
            ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Right));
        RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Right));
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::HAlignment::Center:
        RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
            ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Center));
        RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Center));
        break;
    }

    return S_OK;
}

template<typename TAdaptiveType, typename TXamlTextBlockType>
void SetHorizontalAlignment(TAdaptiveType const& adaptiveTextBlock,
                            rtrender::AdaptiveRenderContext const& renderContext,
                            TXamlTextBlockType const& xamlTextBlock)
{
    /* ComPtr<IReference<HAlignment>> adaptiveHorizontalAlignmentReference;
     RETURN_IF_FAILED(adaptiveTextBlock->get_HorizontalAlignment(&adaptiveHorizontalAlignmentReference));*/
    auto adaptiveHorizontalAlignmentReference = adaptiveTextBlock.HorizontalAlignment();

    // If the text block doesn't have horizontal alignment set, check the render args for a parent value
    if (adaptiveHorizontalAlignmentReference == nullptr)
    {
        adaptiveHorizontalAlignmentReference = renderContext.HorizontalContentAlignment();
    }

    rtom::HAlignment horizontalAlignment = rtom::HAlignment::Left;
    if (adaptiveHorizontalAlignmentReference != nullptr)
    {
        horizontalAlignment = adaptiveHorizontalAlignmentReference.Value();
    }

    /*ComPtr<TXamlTextBlockType> xamlTextBlockComptr(xamlTextBlock);
    ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> xamlTextBlockAsFrameworkElement;
    RETURN_IF_FAILED(xamlTextBlockComptr.As(&xamlTextBlockAsFrameworkElement));*/
    // TODO: I shouldn't need this cast, right?

    switch (horizontalAlignment)
    {
    case rtom::HAlignment::Left:
        // text block stretches to both ends of its parent horizontally if its horizontal alignment is not set,
        // this can lead to unexpected behavior such as hyper link being active in the streched space
        // setting the horizontal alignment, aligns the textblock instead of stretching
        /* RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
             ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Left));
         RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Left));*/
        xamlTextBlock.HorizontalAlignment(rtxaml::HorizontalAlignment::Left);
        xamlTextBlock.TextAlignment(rtxaml::TextAlignment::Left);
        break;
    case rtom::HAlignment::Right:
        /*RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
            ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Right));
        RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Right));*/
        xamlTextBlock.HorizontalAlignment(rtxaml::HorizontalAlignment::Right);
        xamlTextBlock.TextAlignment(rtxaml::TextAlignment::Right);
        break;
    case rtom::HAlignment::Center:
        /* RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
             ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Center));
         RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Center));*/
        xamlTextBlock.HorizontalAlignment(rtxaml::HorizontalAlignment::Center);
        xamlTextBlock.TextAlignment(rtxaml::TextAlignment::Center);
        break;
    }
}

HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties,
                                     _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock);
HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties,
                                     _In_ ABI::Windows::UI::Xaml::Documents::ITextElement* textBlock);

void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties,
                                  winrt::Windows::UI::Xaml::Controls::TextBlock const& textBlock);

void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties,
                                  winrt::Windows::UI::Xaml::Documents::TextElement const& textBlock);

template<typename TXamlTextBlockType>
HRESULT StyleTextElement(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
                         _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                         _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                         const TextRunStyleParameters& styleProperties,
                         _In_ TXamlTextBlockType* xamlTextElement)
{
    Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig> hostConfig;
    RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

    RETURN_IF_FAILED(SetStrikethroughAndUnderline(styleProperties, xamlTextElement));

    if (styleProperties.IsItalic())
    {
        RETURN_IF_FAILED(xamlTextElement->put_FontStyle(ABI::Windows::UI::Text::FontStyle::FontStyle_Italic));
    }

    // Get the forground color based on text color, subtle, and container style
    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor>> adaptiveTextColorRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_Color(&adaptiveTextColorRef));

    ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor adaptiveTextColor =
        ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor::Default;
    if (adaptiveTextColorRef != nullptr)
    {
        adaptiveTextColorRef->get_Value(&adaptiveTextColor);
    }

    // If the card author set the default color and we're in a hyperlink, don't change the color and lose the hyperlink styling
    if (adaptiveTextColor != ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor::Default || !styleProperties.IsInHyperlink())
    {
        ComPtr<IReference<bool>> isSubtleRef;
        RETURN_IF_FAILED(adaptiveTextElement->get_IsSubtle(&isSubtleRef));

        boolean isSubtle = false;
        if (isSubtleRef != nullptr)
        {
            isSubtleRef->get_Value(&isSubtle);
        }

        ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

        ABI::Windows::UI::Color fontColor;
        RETURN_IF_FAILED(GetColorFromAdaptiveColor(hostConfig.Get(), adaptiveTextColor, containerStyle, isSubtle, false, &fontColor));

        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> fontColorBrush =
            AdaptiveCards::Rendering::WinUI3::XamlHelpers::GetSolidColorBrush(fontColor);
        RETURN_IF_FAILED(xamlTextElement->put_Foreground(fontColorBrush.Get()));
    }

    // Retrieve the desired FontFamily, FontSize, and FontWeight values
    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize>> adaptiveTextSizeRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_Size(&adaptiveTextSizeRef));

    ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize adaptiveTextSize = ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize::Default;
    if (adaptiveTextSizeRef != nullptr)
    {
        adaptiveTextSizeRef->get_Value(&adaptiveTextSize);
    }

    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>> adaptiveTextWeightRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_Weight(&adaptiveTextWeightRef));

    ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight adaptiveTextWeight =
        ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight::Default;
    if (adaptiveTextWeightRef != nullptr)
    {
        adaptiveTextWeightRef->get_Value(&adaptiveTextWeight);
    }

    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::FontType>> fontTypeRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_FontType(&fontTypeRef));

    ABI::AdaptiveCards::ObjectModel::WinUI3::FontType fontType = ABI::AdaptiveCards::ObjectModel::WinUI3::FontType::Default;
    if (fontTypeRef != nullptr)
    {
        fontTypeRef->get_Value(&fontType);
    }

    UINT32 fontSize;
    Microsoft::WRL::Wrappers::HString fontFamilyName;
    ABI::Windows::UI::Text::FontWeight xamlFontWeight;
    RETURN_IF_FAILED(GetFontDataFromFontType(
        hostConfig.Get(), fontType, adaptiveTextSize, adaptiveTextWeight, fontFamilyName.GetAddressOf(), &fontSize, &xamlFontWeight));

    // Apply font size
    RETURN_IF_FAILED(xamlTextElement->put_FontSize((double)fontSize));

    // Apply font weight
    RETURN_IF_FAILED(xamlTextElement->put_FontWeight(xamlFontWeight));

    // Apply font family
    Microsoft::WRL::ComPtr<IInspectable> inspectable;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IFontFamily> fontFamily;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IFontFamilyFactory> fontFamilyFactory;
    RETURN_IF_FAILED(Windows::Foundation::GetActivationFactory(
        Microsoft::WRL::Wrappers::HStringReference(L"Windows.UI.Xaml.Media.FontFamily").Get(), &fontFamilyFactory));

    RETURN_IF_FAILED(
        fontFamilyFactory->CreateInstanceWithName(fontFamilyName.Get(), nullptr, inspectable.ReleaseAndGetAddressOf(), &fontFamily));
    RETURN_IF_FAILED(xamlTextElement->put_FontFamily(fontFamily.Get()));

    return S_OK;
}
template<typename TXamlTextBlockType>
void StyleTextElement(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                      rtrender::AdaptiveRenderContext const& renderContext,
                      rtrender::AdaptiveRenderArgs const& renderArgs,
                      const TextRunStyleParameters& styleProperties,
                      TXamlTextBlockType const& xamlTextElement)
{
    /*Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig> hostConfig;
    RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));*/

    auto hostConfig = renderContext.HostConfig();

    // RETURN_IF_FAILED(SetStrikethroughAndUnderline(styleProperties, xamlTextElement));

    SetStrikethroughAndUnderline(styleProperties, xamlTextElement);

    if (styleProperties.IsItalic())
    {
        /*RETURN_IF_FAILED(xamlTextElement->put_FontStyle(ABI::Windows::UI::Text::FontStyle::FontStyle_Italic));*/
        xamlTextElement.FontStyle(winrt::Windows::UI::Text::FontStyle::Italic);
    }

    // Get the forground color based on text color, subtle, and container style
    /*ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor>> adaptiveTextColorRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_Color(&adaptiveTextColorRef));*/
    auto adaptiveTextColorRef = adaptiveTextElement.Color();

    /* ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor adaptiveTextColor =
         ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor::Default;*/
    // TODO: do I need this assignment?
    rtom::ForegroundColor adaptiveTextColor = rtom::ForegroundColor::Default;
    if (adaptiveTextColorRef != nullptr)
    {
        // adaptiveTextColorRef->get_Value(&adaptiveTextColor);
        adaptiveTextColor = adaptiveTextColorRef.Value();
    }

    // If the card author set the default color and we're in a hyperlink, don't change the color and lose the hyperlink styling
    if (adaptiveTextColor != rtom::ForegroundColor::Default || !styleProperties.IsInHyperlink())
    {
        /*ComPtr<IReference<bool>> isSubtleRef;
        RETURN_IF_FAILED(adaptiveTextElement->get_IsSubtle(&isSubtleRef));*/

        auto isSubtleRef = adaptiveTextElement.IsSubtle();

        boolean isSubtle = false;
        if (isSubtleRef != nullptr)
        {
            // isSubtleRef->get_Value(&isSubtle);
            isSbutle = isSubtleRef.Value();
        }

        /*ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));*/
        auto containerStyle = renderArgs.ContainerStyle();

        /*ABI::Windows::UI::Color fontColor;
        RETURN_IF_FAILED(GetColorFromAdaptiveColor(hostConfig.Get(), adaptiveTextColor, containerStyle, isSubtle, false, &fontColor));*/
        auto fontColor = GetColorFromAdaptiveColor(hostConfig, adaptiveTextColor, containerStyle, isSubtle, false);

        auto fontColorBrush = ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::GetSolidColorBrush(fontColor);
        // RETURN_IF_FAILED(xamlTextElement->put_Foreground(fontColorBrush.Get()));
        xamlTextElement.Foreground(fontColorBrush);
    }

    // Retrieve the desired FontFamily, FontSize, and FontWeight values
    /*ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize>> adaptiveTextSizeRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_Size(&adaptiveTextSizeRef));*/

    /* ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize adaptiveTextSize = ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize::Default;*/
    // TODO: do I need this assignment?
    rtom::TextSize adaptiveTextSize = rtom::TextSize::Default;
    rtom::TextWeight adaptiveTextWeight = rtom::TextWeight::Default;
    rtom::FontType fontType = rtom::FontType::Default;

    if (const auto textSizeRef = adaptiveTextElement.Size())
    {
        adaptiveTextSize = textSizeRef.Value();
    }
    if (const auto textWeightRef = adaptiveTextElement.Weight())
    {
        adaptiveTextWeight = textWeightRef.Value();
    }
    if (const auto fontTypeRef = adaptiveTextElement.FontType())
    {
        fontType = fontTypeRef.Value();
    }

    uint32_t fontSize = GetFontSizeFromFontType(hostConfig, fontType, adaptiveTextSize);
    // winrt::Microsoft::WRL::Wrappers::HString fontFamilyName;
    // ABI::Windows::UI::Text::FontWeight xamlFontWeight;
    winrt::hstring fontFamilyName = GetFontFamilyFromFontType(hostConfig, fontType);
    winrt::Windows::UI::Text::FontWeight xamlFontWeight = GetFontWeightFromStyle(hostConfig, fontType, adaptiveTextWeight);

    /*RETURN_IF_FAILED(GetFontDataFromFontType(
        hostConfig.Get(), fontType, adaptiveTextSize, adaptiveTextWeight, fontFamilyName.GetAddressOf(), &fontSize, &xamlFontWeight));*/

    // RETURN_IF_FAILED(GetFontFamilyFromFontType(hostConfig, fontType, resultFontFamilyName));
    //    RETURN_IF_FAILED(GetFontSizeFromFontType(hostConfig, fontType, desiredSize, resultSize));
    //    RETURN_IF_FAILED(GetFontWeightFromStyle(hostConfig, fontType, desiredWeight, resultWeight));
    /*std::tie(fontSize, xamlFontWeight) =
        GetFontDataFromFontType(hostConfig, fontType, adaptiveTextSize, adaptiveTextWeight, fontFamilyName);*/

    // Apply font size
    /* RETURN_IF_FAILED(xamlTextElement->put_FontSize((double)fontSize));*/
    xamlTextElement.FontSize((double)fontSize);

    // Apply font weight
    // RETURN_IF_FAILED(xamlTextElement->put_FontWeight(xamlFontWeight));
    xamlTextElement.FontWeight(xamlFontWeight);

    // Apply font family
    /*Microsoft::WRL::ComPtr<IInspectable> inspectable;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IFontFamily> fontFamily;
    Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IFontFamilyFactory> fontFamilyFactory;
    RETURN_IF_FAILED(Windows::Foundation::GetActivationFactory(
        Microsoft::WRL::Wrappers::HStringReference(L"Windows.UI.Xaml.Media.FontFamily").Get(), &fontFamilyFactory));

    RETURN_IF_FAILED(
        fontFamilyFactory->CreateInstanceWithName(fontFamilyName.Get(), nullptr, inspectable.ReleaseAndGetAddressOf(),
    &fontFamily)); RETURN_IF_FAILED(xamlTextElement->put_FontFamily(fontFamily.Get()));*/
    // TODO: I can just pass hstring to fontFamily setter, it should construct the object right?
    rtxaml::Media::FontFamily fontFamily{fontFamilyName};
    xamlTextElement.FontFamily(fontFamily);
}
