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

HRESULT AddHtmlInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       bool isInHyperlink,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_ UINT* characterLength);

HRESULT AddTextInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       const TextRunStyleParameters& styleParameters,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_ UINT* characterLength);

HRESULT AddSingleTextInline(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                            _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                            _In_ HSTRING string,
                            const TextRunStyleParameters& styleParameters,
                            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                            _Out_ UINT* characterLength);

HRESULT SetXamlInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                       bool isInHyperlink,
                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_opt_ UINT* characterLength = nullptr);

HRESULT SetXamlInlinesWithTextConfig(_In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveTextConfig* textConfig,
                                     _In_ HSTRING language,
                                     _In_ HSTRING text,
                                     _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock);

HRESULT SetWrapProperties(_In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock, bool wrap);
HRESULT StyleXamlTextBlockProperties(_In_ ABI::AdaptiveNamespace::IAdaptiveTextBlock* adaptiveTextBlock,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                     _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock);

template<typename TAdaptiveType, typename TXamlTextBlockType>
HRESULT SetHorizontalAlignment(_In_ TAdaptiveType* adaptiveTextBlock, _In_ TXamlTextBlockType* xamlTextBlock)
{
    HAlignment horizontalAlignment;
    RETURN_IF_FAILED(adaptiveTextBlock->get_HorizontalAlignment(&horizontalAlignment));

    ComPtr<TXamlTextBlockType> xamlTextBlockComptr(xamlTextBlock);
    ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> xamlTextBlockAsFrameworkElement;
    RETURN_IF_FAILED(xamlTextBlockComptr.As(&xamlTextBlockAsFrameworkElement));

    switch (horizontalAlignment)
    {
    case ABI::AdaptiveNamespace::HAlignment::Left:
        // text block stretches to both ends of its parent horizontally if its horizontal alignment is not set,
        // this can lead to unexpected behavior such as hyper link being active in the streched space
        // setting the horizontal alignment, aligns the textblock instead of stretching
        RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
            ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Left));
        RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Left));
        break;
    case ABI::AdaptiveNamespace::HAlignment::Right:
        RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
            ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Right));
        RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Right));
        break;
    case ABI::AdaptiveNamespace::HAlignment::Center:
        RETURN_IF_FAILED(xamlTextBlockAsFrameworkElement->put_HorizontalAlignment(
            ABI::Windows::UI::Xaml::HorizontalAlignment::HorizontalAlignment_Center));
        RETURN_IF_FAILED(xamlTextBlock->put_TextAlignment(TextAlignment::TextAlignment_Center));
        break;
    }

    return S_OK;
}

HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties,
                                     _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock);
HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties,
                                     _In_ ABI::Windows::UI::Xaml::Documents::ITextElement* textBlock);

template<typename TXamlTextBlockType>
HRESULT StyleTextElement(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                         _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                         _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                         const TextRunStyleParameters& styleProperties,
                         _In_ TXamlTextBlockType* xamlTextElement)
{
    Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveHostConfig> hostConfig;
    RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

    RETURN_IF_FAILED(SetStrikethroughAndUnderline(styleProperties, xamlTextElement));

    if (styleProperties.IsItalic())
    {
        RETURN_IF_FAILED(xamlTextElement->put_FontStyle(ABI::Windows::UI::Text::FontStyle::FontStyle_Italic));
    }

    // Get the forground color based on text color, subtle, and container style
    ABI::AdaptiveNamespace::ForegroundColor adaptiveTextColor;
    RETURN_IF_FAILED(adaptiveTextElement->get_Color(&adaptiveTextColor));

    // If the card author set the default color and we're in a hyperlink, don't change the color and lose the hyperlink styling
    if (adaptiveTextColor != ABI::AdaptiveNamespace::ForegroundColor::Default || !styleProperties.IsInHyperlink())
    {
        boolean isSubtle = false;
        RETURN_IF_FAILED(adaptiveTextElement->get_IsSubtle(&isSubtle));

        ABI::AdaptiveNamespace::ContainerStyle containerStyle;
        RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

        ABI::Windows::UI::Color fontColor;
        RETURN_IF_FAILED(GetColorFromAdaptiveColor(hostConfig.Get(), adaptiveTextColor, containerStyle, isSubtle, false, &fontColor));

        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::Media::IBrush> fontColorBrush =
            AdaptiveNamespace::XamlHelpers::GetSolidColorBrush(fontColor);
        RETURN_IF_FAILED(xamlTextElement->put_Foreground(fontColorBrush.Get()));
    }

    // Retrieve the desired FontFamily, FontSize, and FontWeight values
    ABI::AdaptiveNamespace::TextSize adaptiveTextSize;
    RETURN_IF_FAILED(adaptiveTextElement->get_Size(&adaptiveTextSize));

    ABI::AdaptiveNamespace::TextWeight adaptiveTextWeight;
    RETURN_IF_FAILED(adaptiveTextElement->get_Weight(&adaptiveTextWeight));

    ABI::AdaptiveNamespace::FontType fontType;
    RETURN_IF_FAILED(adaptiveTextElement->get_FontType(&fontType));

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
