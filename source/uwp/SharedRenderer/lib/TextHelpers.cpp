// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "DateTimeParser.h"
#include "MarkDownParser.h"
#include "TextHelpers.h"
#include <safeint.h>

using namespace AdaptiveCards::Rendering::Xaml_Rendering;
using namespace AdaptiveCards;
using namespace msl::utilities;
using namespace std::string_literals;

void StyleXamlTextBlockProperties(winrt::AdaptiveTextBlock const& adaptiveTextBlock,
                                  winrt::AdaptiveRenderContext const& renderContext,
                                  winrt::AdaptiveRenderArgs const& renderArgs,
                                  winrt::TextBlock const& xamlTextBlock)
{
    SetWrapProperties(xamlTextBlock, adaptiveTextBlock.Wrap());

    uint32_t maxLines = adaptiveTextBlock.MaxLines();
    if (maxLines != MAXUINT32)
    {
        xamlTextBlock.MaxLines(maxLines);
    }

    SetHorizontalAlignment(adaptiveTextBlock, renderContext, xamlTextBlock);

    StyleTextElement(adaptiveTextBlock, renderContext, renderArgs, TextRunStyleParameters(), xamlTextBlock);
}

winrt::TextDecorations GetTextDecorations(TextRunStyleParameters const& styleProperties)
{
    winrt::TextDecorations textDecorations = winrt::TextDecorations::None;
    if (styleProperties.IsStrikethrough())
    {
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Strikethrough);
    }

    if (styleProperties.IsUnderline() || styleProperties.IsInHyperlink())
    {
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Underline);
    }
    return textDecorations;
}

void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties, winrt::TextBlock const& textBlock)
{
    textBlock.TextDecorations(GetTextDecorations(styleProperties));
}

void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties, winrt::TextElement const& textElement)
{
    textElement.TextDecorations(GetTextDecorations(styleProperties));
}

void SetXamlInlinesWithTextStyleConfig(winrt::IAdaptiveTextElement const& textElement,
                                       winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveRenderArgs const& renderArgs,
                                       winrt::AdaptiveTextStyleConfig const& textStyleConfig,
                                       winrt::TextBlock const& textBlock)
{
    SetXamlInlinesWithTextStyleConfig(
        renderContext, renderArgs, textStyleConfig, textElement, textElement.Language(), textElement.Text(), textBlock);
}

void SetXamlInlinesWithTextStyleConfig(winrt::AdaptiveRenderContext const& renderContext,
                                       winrt::AdaptiveRenderArgs const& renderArgs,
                                       winrt::AdaptiveTextStyleConfig const& textStyle,
                                       winrt::IAdaptiveTextElement const& textElement,
                                       winrt::hstring const& language,
                                       winrt::hstring const& text,
                                       winrt::TextBlock const& textBlock)
{
    // Create an AdaptiveTextRun with the language, text, and configuration to pass to SetXamlInlines
    winrt::AdaptiveTextRun textRun{};
    textRun.Text(text);
    textRun.Language(language);

    // For weight, color, size, fontType, and isSubtle, use the value from the text element if there is one, otherwise use the value from the text style
    winrt::IReference<winrt::TextWeight> weightToSet{textStyle.Weight()};
    winrt::IReference<winrt::ForegroundColor> colorToSet{textStyle.Color()};
    winrt::IReference<winrt::TextSize> sizeToSet{textStyle.Size()};
    winrt::IReference<winrt::FontType> fontTypeToSet{textStyle.FontType()};
    winrt::IReference<bool> isSubtleToSet{textStyle.IsSubtle()};

    if (textElement)
    {
        if (const auto weight = textElement.Weight())
        {
            weightToSet = weight;
        }
        if (const auto color = textElement.Color())
        {
            colorToSet = textElement.Color();
        }
        if (const auto size = textElement.Size())
        {
            sizeToSet = size;
        }
        if (const auto fontType = textElement.FontType())
        {
            fontTypeToSet = fontType;
        }
        if (const auto isSubtle = textElement.IsSubtle())
        {
            isSubtleToSet = isSubtle;
        }
    }

    textRun.Weight(weightToSet);
    textRun.Color(colorToSet);
    textRun.Size(sizeToSet);
    textRun.FontType(fontTypeToSet);
    textRun.IsSubtle(isSubtleToSet);

    auto inlines = textBlock.Inlines();

    // Style the text block with the properties from the TextRun
    StyleTextElement(textRun, renderContext, renderArgs, TextRunStyleParameters(), textBlock);

    // Set the inlines
    SetXamlInlines(textRun, renderContext, renderArgs, false, inlines);
}

void SetXamlInlinesWithFactSetTextConfig(winrt::AdaptiveRenderContext const& renderContext,
                                         winrt::AdaptiveRenderArgs const& renderArgs,
                                         winrt::AdaptiveFactSetTextConfig const& factSetTextConfig,
                                         winrt::hstring const& language,
                                         winrt::hstring const& text,
                                         winrt::TextBlock const& textBlock)
{
    auto factSetTextConfigAsTextStyleConfig = factSetTextConfig.as<winrt::AdaptiveTextStyleConfig>();

    SetXamlInlinesWithTextStyleConfig(renderContext, renderArgs, factSetTextConfigAsTextStyleConfig, nullptr, language, text, textBlock);

    // Set wrap and maxwidth
    SetWrapProperties(textBlock, factSetTextConfig.Wrap());
    textBlock.MaxWidth(factSetTextConfig.MaxWidth());
}

void SetWrapProperties(winrt::TextBlock const& xamlTextBlock, bool wrap)
{
    // Set whether the text wraps
    xamlTextBlock.TextWrapping(wrap ? winrt::TextWrapping::Wrap : winrt::TextWrapping::NoWrap);
    xamlTextBlock.TextTrimming(winrt::TextTrimming::CharacterEllipsis);
}

uint32_t SetXamlInlines(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                        winrt::AdaptiveRenderContext const& renderContext,
                        winrt::AdaptiveRenderArgs const& renderArgs,
                        bool isInHyperlink,
                        winrt::IVector<winrt::Inline> const& inlines)
{
    // auto langugae = adaptiveTextElement.Language();
    auto text = adaptiveTextElement.Text();
    MarkDownParser markdownParser(HStringToUTF8(text));
    auto htmlString = markdownParser.TransformToHtml();

    bool handledAsHtml = false;
    uint32_t characterLength = 0;
    if (markdownParser.HasHtmlTags())
    {
        // wrap html in <root></root> in case there's more than one toplevel element.
        winrt::hstring htmlHString = UTF8ToHString("<root>"s + htmlString + "</root>"s);

        winrt::XmlDocument xmlDocument{};
        xmlDocument.LoadXml(htmlHString);

        characterLength = AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, xmlDocument, isInHyperlink, inlines);
        handledAsHtml = true;
    }

    if (!handledAsHtml)
    {
        characterLength = AddSingleTextInline(
            adaptiveTextElement, renderContext, renderArgs, text, TextRunStyleParameters(false, false, false, isInHyperlink), inlines);
    }

    return characterLength;
}

static winrt::hstring GetTextFromXmlNode(winrt::IXmlNode const& node)
{
    return node.InnerText();
}

uint32_t AddListInlines(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                        winrt::AdaptiveRenderContext const& renderContext,
                        winrt::AdaptiveRenderArgs const& renderArgs,
                        winrt::IXmlNode const& node,
                        bool isListOrdered,
                        bool isInHyperlink,
                        winrt::IVector<winrt::Inline> const& inlines)
{
    auto attributeMap = node.Attributes();
    auto startNode = attributeMap.GetNamedItem(L"start");

    unsigned long iteration = 1;
    if (startNode)
    {
        // Get the starting value for this list
        auto start = GetTextFromXmlNode(startNode);
        try
        {
            iteration = std::stoul(HStringToUTF8(start));

            // Check that we can iterate the entire list without overflowing.
            // If the list values are too big to store in an unsigned int, start
            // the list at 1.
            auto children = node.ChildNodes();

            uint32_t childrenLength = children.Length();
            unsigned long result;
            if (!SafeAdd(iteration, childrenLength - 1, result))
            {
                iteration = 1;
            }
        }
        catch (const std::out_of_range&)
        {
            // If stoul throws out_of_range, start the numbered list at 1.
            iteration = 1;
        }
    }

    auto listChild = node.FirstChild();

    uint32_t totalCharacterLength = 0;
    bool isFirstListElement = true;
    while (listChild)
    {
        std::wstring listElementString = isFirstListElement ? L"" : L"\n";
        if (!isListOrdered)
        {
            // Add a bullet
            listElementString += L"\x2022 ";
        }
        else
        {
            listElementString += std::to_wstring(iteration);
            listElementString += L". ";
        }

        winrt::hstring listElementHString{listElementString};
        totalCharacterLength = listElementHString.size();

        winrt::Run run{};
        run.Text(listElementHString);

        // Make sure the bullet or list number is styled correctly
        StyleTextElement(adaptiveTextElement, renderContext, renderArgs, TextRunStyleParameters(false, false, false, isInHyperlink), run);

        inlines.Append(run);

        uint32_t textCharacterLength = AddTextInlines(adaptiveTextElement,
                                                      renderContext,
                                                      renderArgs,
                                                      listChild,
                                                      TextRunStyleParameters(false, false, false, isInHyperlink),
                                                      inlines);

        totalCharacterLength += textCharacterLength;

        iteration++;
        listChild = listChild.NextSibling();
        isFirstListElement = false;
    }

    return totalCharacterLength;
}

uint32_t AddLinkInline(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                       winrt::AdaptiveRenderContext const& renderContext,
                       winrt::AdaptiveRenderArgs const& renderArgs,
                       winrt::IXmlNode const& node,
                       bool isStrikethrough,
                       bool isItalic,
                       bool isUnderline,
                       winrt::IVector<winrt::Inline> inlines)
{
    auto attributeMap = node.Attributes();
    auto hrefNode = attributeMap.GetNamedItem(L"href");

    if (hrefNode == nullptr)
    {
        throw winrt::hresult_error(E_INVALIDARG);
    }

    auto href = GetTextFromXmlNode(hrefNode);

    winrt::Uri uri{href};

    winrt::Hyperlink hyperlink{};
    hyperlink.NavigateUri(uri);

    auto hyperlinkInlines = hyperlink.Inlines();

    auto characterLength = AddTextInlines(adaptiveTextElement,
                                          renderContext,
                                          renderArgs,
                                          node,
                                          TextRunStyleParameters(isStrikethrough, isItalic, isUnderline, true),
                                          hyperlinkInlines);

    inlines.Append(hyperlink);
    return characterLength;
}

uint32_t AddSingleTextInline(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                             winrt::AdaptiveRenderContext const& renderContext,
                             winrt::AdaptiveRenderArgs const& renderArgs,
                             winrt::hstring const& stringToParse,
                             const TextRunStyleParameters& styleParameters,
                             winrt::IVector<winrt::Inline> const& inlines)
{
    winrt::Run run{};

    winrt::hstring language = adaptiveTextElement.Language();

    DateTimeParser parser(HStringToUTF8(language));
    const auto textWithParsedDates = parser.GenerateString(HStringToUTF8(stringToParse));

    winrt::hstring textWithParsedDatesHString = UTF8ToHString(textWithParsedDates);

    run.Text(textWithParsedDatesHString);

    StyleTextElement(adaptiveTextElement, renderContext, renderArgs, styleParameters, run);

    inlines.Append(run);

    return stringToParse.size();
}

uint32_t AddTextInlines(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                        winrt::AdaptiveRenderContext const& renderContext,
                        winrt::AdaptiveRenderArgs const& renderArgs,
                        winrt::IXmlNode const& node,
                        TextRunStyleParameters const& styleParameters,
                        winrt::IVector<winrt::Inline> const& inlines)
{
    auto childNode = node.FirstChild();

    uint32_t totalCharacterLength = 0;
    try
    {
        while (childNode)
        {
            winrt::hstring nodeName = childNode.NodeName();

            bool isLinkResult = nodeName == L"a";
            bool isBoldResult = nodeName == L"strong";
            bool isItalicResult = nodeName == L"em";
            bool isTextResult = nodeName == L"#text";

            uint32_t nodeCharacterLength = 0;
            if (isLinkResult)
            {
                nodeCharacterLength = AddLinkInline(adaptiveTextElement,
                                                    renderContext,
                                                    renderArgs,
                                                    childNode,
                                                    styleParameters.IsStrikethrough(),
                                                    styleParameters.IsItalic(),
                                                    styleParameters.IsUnderline(),
                                                    inlines);
            }
            else if (isTextResult)
            {
                auto text = GetTextFromXmlNode(childNode);
                nodeCharacterLength =
                    AddSingleTextInline(adaptiveTextElement, renderContext, renderArgs, text, styleParameters, inlines);
            }
            else
            {
                winrt::IAdaptiveTextElement textElementToUse = adaptiveTextElement;
                if (isBoldResult || isItalicResult)
                {
                    // Make a copy of the element so we can apply bold or italics
                    textElementToUse = CopyTextElement(adaptiveTextElement);

                    if (isBoldResult)
                    {
                        textElementToUse.Weight(winrt::TextWeight::Bolder);
                    }
                }
                nodeCharacterLength = AddTextInlines(textElementToUse,
                                                     renderContext,
                                                     renderArgs,
                                                     childNode,
                                                     TextRunStyleParameters(styleParameters.IsStrikethrough(),
                                                                            styleParameters.IsItalic() || isItalicResult,
                                                                            styleParameters.IsUnderline(),
                                                                            styleParameters.IsInHyperlink()),
                                                     inlines);
            }
            childNode = childNode.NextSibling();
            totalCharacterLength += nodeCharacterLength;
        }
    }
    catch (...)
    {
        renderContext.AddWarning(winrt::WarningStatusCode::CustomWarning, L"Adding Text Inlines failed.");
    }

    return totalCharacterLength;
}

uint32_t AddHtmlInlines(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                        winrt::AdaptiveRenderContext const& renderContext,
                        winrt::AdaptiveRenderArgs const& renderArgs,
                        winrt::IXmlNode const& node,
                        bool isInHyperlink,
                        winrt::IVector<winrt::Inline> inlines)
{
    auto childNode = node.FirstChild();

    // We *might* be looking at a toplevel chunk of HTML that we've wrapped with <root></root> (see SetXamlInlines())
    // If so, strip that off.
    {
        auto childNodeName = childNode.NodeName();

        if (childNodeName == L"root")
        {
            childNode = childNode.FirstChild();
        }
    }

    uint32_t totalCharacterLength = 0;
    while (childNode)
    {
        auto nodeName = childNode.NodeName();

        auto isOrderedListResult = nodeName == L"ol";
        auto isUnorderedListResult = nodeName == L"ul";
        auto isParagraphResult = nodeName == L"p";

        uint32_t nodeCharacterLength = 0;
        if (isOrderedListResult || isUnorderedListResult)
        {
            nodeCharacterLength =
                AddListInlines(adaptiveTextElement, renderContext, renderArgs, childNode, isOrderedListResult, isInHyperlink, inlines);
        }
        else if (isParagraphResult)
        {
            nodeCharacterLength = AddTextInlines(adaptiveTextElement,
                                                 renderContext,
                                                 renderArgs,
                                                 childNode,
                                                 TextRunStyleParameters(false, false, false, isInHyperlink),
                                                 inlines);

            // End of paragraph. check to see if there's more content. if there is, insert a line break
            if (const auto nextSibling = childNode.NextSibling())
            {
                inlines.Append(winrt::LineBreak{});
            }
        }
        else
        {
            nodeCharacterLength = AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, childNode, isInHyperlink, inlines);
        }
        childNode = childNode.NextSibling();
        totalCharacterLength += nodeCharacterLength;
    }
    return totalCharacterLength;
}
