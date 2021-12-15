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

uint32_t AddTextInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        // TODO: should it be const& or const TextRunStyleParameters&??
                        TextRunStyleParameters const& styleParameters,
                        winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines);

uint32_t AddSingleTextInline(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs,
                             winrt::hstring const& stringToParse,
                             // TODO: should it be const TextRunStyleParameters& ?
                             const TextRunStyleParameters& styleParameters,
                             winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines);

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

void SetXamlInlinesWithTextStyleConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs,
                                       rtrender::AdaptiveTextStyleConfig const& textStyle,
                                       rtom::IAdaptiveTextElement const& textElement, // TODO: optional?
                                       winrt::hstring const& language,
                                       winrt::hstring const& text,
                                       rtxaml::Controls::TextBlock const& textBlock);

void SetXamlInlinesWithFactSetTextConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                         rtrender::AdaptiveRenderArgs const& renderArgs,
                                         rtrender::AdaptiveFactSetTextConfig const& factSetTextConfig,
                                         winrt::hstring const& language,
                                         winrt::hstring const& text,
                                         rtxaml::Controls::TextBlock const& textBlock);

void SetWrapProperties(rtxaml::Controls::TextBlock const& xamlTextBlock, bool wrap);

void StyleXamlTextBlockProperties(rtom::AdaptiveTextBlock const& adaptiveTextBlock,
                                  rtrender::AdaptiveRenderContext const& renderContext,
                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                  rtxaml::Controls::TextBlock const& xamlTextBlock);

template<typename TAdaptiveType, typename TXamlTextBlockType>
void SetHorizontalAlignment(TAdaptiveType const& adaptiveTextBlock,
                            rtrender::AdaptiveRenderContext const& renderContext,
                            TXamlTextBlockType const& xamlTextBlock)
{
    auto adaptiveHorizontalAlignmentReference = adaptiveTextBlock.HorizontalAlignment();

    // If the text block doesn't have horizontal alignment set, check the render args for a parent value
    if (adaptiveHorizontalAlignmentReference == nullptr)
    {
        adaptiveHorizontalAlignmentReference = renderContext.HorizontalContentAlignment();
    }

    rtom::HAlignment horizontalAlignment = GetValueFromRef(adaptiveHorizontalAlignmentReference, rtom::HAlignment::Left);
    
    switch (horizontalAlignment)
    {
    case rtom::HAlignment::Left:
        // text block stretches to both ends of its parent horizontally if its horizontal alignment is not set,
        // this can lead to unexpected behavior such as hyper link being active in the streched space
        // setting the horizontal alignment, aligns the textblock instead of stretching
        xamlTextBlock.HorizontalAlignment(rtxaml::HorizontalAlignment::Left);
        xamlTextBlock.TextAlignment(rtxaml::TextAlignment::Left);
        break;
    case rtom::HAlignment::Right:
        xamlTextBlock.HorizontalAlignment(rtxaml::HorizontalAlignment::Right);
        xamlTextBlock.TextAlignment(rtxaml::TextAlignment::Right);
        break;
    case rtom::HAlignment::Center:
        xamlTextBlock.HorizontalAlignment(rtxaml::HorizontalAlignment::Center);
        xamlTextBlock.TextAlignment(rtxaml::TextAlignment::Center);
        break;
    }
}
void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties,
                                  winrt::Windows::UI::Xaml::Controls::TextBlock const& textBlock);

void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties,
                                  winrt::Windows::UI::Xaml::Documents::TextElement const& textBlock);

template<typename TXamlTextBlockType>
void StyleTextElement(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                      rtrender::AdaptiveRenderContext const& renderContext,
                      rtrender::AdaptiveRenderArgs const& renderArgs,
                      const TextRunStyleParameters& styleProperties,
                      TXamlTextBlockType const& xamlTextElement)
{
    auto hostConfig = renderContext.HostConfig();

    SetStrikethroughAndUnderline(styleProperties, xamlTextElement);

    if (styleProperties.IsItalic())
    {
        xamlTextElement.FontStyle(winrt::Windows::UI::Text::FontStyle::Italic);
    }

    // Retrieve the desired Foreground, FontFamily, FontSize, and FontWeight values
    rtom::ForegroundColor adaptiveTextColor = GetValueFromRef(adaptiveTextElement.Color(), rtom::ForegroundColor::Default);
    rtom::TextSize adaptiveTextSize = GetValueFromRef(adaptiveTextElement.Size(), rtom::TextSize::Default);
    rtom::TextWeight adaptiveTextWeight = GetValueFromRef(adaptiveTextElement.Weight(), rtom::TextWeight::Default);
    rtom::FontType fontType = GetValueFromRef(adaptiveTextElement.FontType(), rtom::FontType::Default);

    // If the card author set the default color and we're in a hyperlink, don't change the color and lose the hyperlink styling
    if (adaptiveTextColor != rtom::ForegroundColor::Default || !styleProperties.IsInHyperlink())
    {
        bool isSubtle = GetValueFromRef(adaptiveTextElement.IsSubtle(), false);

        auto containerStyle = renderArgs.ContainerStyle();

        auto fontColor = GetColorFromAdaptiveColor(hostConfig, adaptiveTextColor, containerStyle, isSubtle, false);

        auto fontColorBrush = ::AdaptiveCards::Rendering::Uwp::XamlHelpers::GetSolidColorBrush(fontColor);

        xamlTextElement.Foreground(fontColorBrush);
    }

    uint32_t fontSize = GetFontSizeFromFontType(hostConfig, fontType, adaptiveTextSize);
    winrt::hstring fontFamilyName = GetFontFamilyFromFontType(hostConfig, fontType);
    winrt::Windows::UI::Text::FontWeight xamlFontWeight = GetFontWeightFromStyle(hostConfig, fontType, adaptiveTextWeight);

    // Apply font size
    xamlTextElement.FontSize((double)fontSize);

    // Apply font weight
    xamlTextElement.FontWeight(xamlFontWeight);

    // Apply font family
    xamlTextElement.FontFamily(rtxaml::Media::FontFamily{fontFamilyName});
}
