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

uint32_t AddHtmlInlines(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                        winrt::AdaptiveRenderContext const& renderContext,
                        winrt::AdaptiveRenderArgs const& renderArgs,
                        winrt::IXmlNode const& node,
                        bool isInHyperlink,
                        winrt::IVector<winrt::Inline> inlines);

uint32_t AddTextInlines(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                        winrt::AdaptiveRenderContext const& renderContext,
                        winrt::AdaptiveRenderArgs const& renderArgs,
                        winrt::IXmlNode const& node,
                        TextRunStyleParameters const& styleParameters,
                        winrt::IVector<winrt::Inline> const& inlines);

uint32_t AddSingleTextInline(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                             winrt::AdaptiveRenderContext const& renderContext,
                             winrt::AdaptiveRenderArgs const& renderArgs,
                             winrt::hstring const& stringToParse,
                             TextRunStyleParameters const& styleParameters,
                             winrt::IVector<winrt::Inline> const& inlines);

uint32_t SetXamlInlines(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                        winrt::AdaptiveRenderContext const& renderContext,
                        winrt::AdaptiveRenderArgs const& renderArgs,
                        bool isInHyperlink,
                        winrt::IVector<winrt::Inline> const& inlines);

void SetXamlInlinesWithTextStyleConfig(winrt::IAdaptiveTextElement const& textElement,
                                       winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveRenderArgs const& renderArgs,
                                       winrt::AdaptiveTextStyleConfig const& textStyleConfig,
                                       winrt::TextBlock const& textBlock);

void SetXamlInlinesWithTextStyleConfig(winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveRenderArgs const& renderArgs,
                                       winrt::AdaptiveTextStyleConfig const& textStyle,
                                       winrt::IAdaptiveTextElement const& textElement,
                                       winrt::hstring const& language,
                                       winrt::hstring const& text,
                                       winrt::TextBlock const& textBlock);

void SetXamlInlinesWithFactSetTextConfig(winrt::AdaptiveRenderContext const& renderContext,
                                         winrt::AdaptiveRenderArgs const& renderArgs,
                                         winrt::AdaptiveFactSetTextConfig const& factSetTextConfig,
                                         winrt::hstring const& language,
                                         winrt::hstring const& text,
                                         winrt::TextBlock const& textBlock);

void SetWrapProperties(winrt::TextBlock const& xamlTextBlock, bool wrap);

void StyleXamlTextBlockProperties(winrt::AdaptiveTextBlock const& adaptiveTextBlock,
                                  winrt::AdaptiveRenderContext const& renderContext,
                                  winrt::AdaptiveRenderArgs const& renderArgs,
                                  winrt::TextBlock const& xamlTextBlock);

template<typename TAdaptiveType, typename TXamlTextBlockType>
void SetHorizontalAlignment(TAdaptiveType const& adaptiveTextBlock,
                            winrt::AdaptiveRenderContext const& renderContext,
                            TXamlTextBlockType const& xamlTextBlock)
{
    auto adaptiveHorizontalAlignmentReference = adaptiveTextBlock.HorizontalAlignment();

    // If the text block doesn't have horizontal alignment set, check the render args for a parent value
    if (adaptiveHorizontalAlignmentReference == nullptr)
    {
        adaptiveHorizontalAlignmentReference = renderContext.HorizontalContentAlignment();
    }

    winrt::HAlignment horizontalAlignment = GetValueFromRef(adaptiveHorizontalAlignmentReference, winrt::HAlignment::Left);

    switch (horizontalAlignment)
    {
    case winrt::HAlignment::Left:
        // text block stretches to both ends of its parent horizontally if its horizontal alignment is not set,
        // this can lead to unexpected behavior such as hyper link being active in the streched space
        // setting the horizontal alignment, aligns the textblock instead of stretching
        xamlTextBlock.HorizontalAlignment(winrt::HorizontalAlignment::Left);
        xamlTextBlock.TextAlignment(winrt::TextAlignment::Left);
        break;
    case winrt::HAlignment::Right:
        xamlTextBlock.HorizontalAlignment(winrt::HorizontalAlignment::Right);
        xamlTextBlock.TextAlignment(winrt::TextAlignment::Right);
        break;
    case winrt::HAlignment::Center:
        xamlTextBlock.HorizontalAlignment(winrt::HorizontalAlignment::Center);
        xamlTextBlock.TextAlignment(winrt::TextAlignment::Center);
        break;
    }
}
void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties, winrt::TextBlock const& textBlock);

void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties, winrt::TextElement const& textBlock);

template<typename TXamlTextBlockType>
void StyleTextElement(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                      winrt::AdaptiveRenderContext const& renderContext,
                      winrt::AdaptiveRenderArgs const& renderArgs,
                      TextRunStyleParameters const& styleProperties,
                      TXamlTextBlockType const& xamlTextElement)
{
    auto hostConfig = renderContext.HostConfig();

    SetStrikethroughAndUnderline(styleProperties, xamlTextElement);

    if (styleProperties.IsItalic())
    {
        xamlTextElement.FontStyle(winrt::Windows::UI::Text::FontStyle::Italic);
    }

    // Retrieve the desired Foreground, FontFamily, FontSize, and FontWeight values
    winrt::ForegroundColor adaptiveTextColor = GetValueFromRef(adaptiveTextElement.Color(), winrt::ForegroundColor::Default);
    winrt::TextSize adaptiveTextSize = GetValueFromRef(adaptiveTextElement.Size(), winrt::TextSize::Default);
    winrt::TextWeight adaptiveTextWeight = GetValueFromRef(adaptiveTextElement.Weight(), winrt::TextWeight::Default);
    winrt::FontType fontType = GetValueFromRef(adaptiveTextElement.FontType(), winrt::FontType::Default);

    // If the card author set the default color and we're in a hyperlink, don't change the color and lose the hyperlink styling
    if (adaptiveTextColor != winrt::ForegroundColor::Default || !styleProperties.IsInHyperlink())
    {
        bool isSubtle = GetValueFromRef(adaptiveTextElement.IsSubtle(), false);

        auto containerStyle = renderArgs.ContainerStyle();

        auto fontColor = GetColorFromAdaptiveColor(hostConfig, adaptiveTextColor, containerStyle, isSubtle, false);

        xamlTextElement.Foreground(winrt::SolidColorBrush{fontColor});
    }

    uint32_t fontSize = GetFontSizeFromFontType(hostConfig, fontType, adaptiveTextSize);
    winrt::hstring fontFamilyName = GetFontFamilyFromFontType(hostConfig, fontType);
    winrt::Windows::UI::Text::FontWeight xamlFontWeight = GetFontWeightFromStyle(hostConfig, fontType, adaptiveTextWeight);

    // Apply font size
    xamlTextElement.FontSize((double)fontSize);

    // Apply font weight
    xamlTextElement.FontWeight(xamlFontWeight);

    // Apply font family
    xamlTextElement.FontFamily(winrt::FontFamily{fontFamilyName});
}
