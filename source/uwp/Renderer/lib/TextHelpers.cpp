// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "DateTimeParser.h"
#include "MarkDownParser.h"
#include "TextHelpers.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include <safeint.h>

using namespace AdaptiveCards::Rendering::Uwp;
using namespace AdaptiveCards;
using namespace msl::utilities;
using namespace std::string_literals;

void StyleXamlTextBlockProperties(rtom::AdaptiveTextBlock const& adaptiveTextBlock,
                                  rtrender::AdaptiveRenderContext const& renderContext,
                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                  rtxaml::Controls::TextBlock const& xamlTextBlock)
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

// TODO: should it be const TextRunStyleParameters&?
void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties, rtxaml::Controls::TextBlock const& textBlock)
{
    winrt::Windows::UI::Text::TextDecorations textDecorations = winrt::Windows::UI::Text::TextDecorations::None;
    if (styleProperties.IsStrikethrough())
    {
        // TODO: what is this operator doing for enums? Figure out how to use it properly in winrt
        // TODO: find a better way to do it? May be static cast right here?
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Strikethrough);
    }

    if (styleProperties.IsUnderline() || styleProperties.IsInHyperlink())
    {
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Underline);
    }

    textBlock.TextDecorations(textDecorations);
}

// TODO: this function repeats - shoudl I template it?
void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties,
                                  winrt::Windows::UI::Xaml::Documents::TextElement const& textElement)
{
    winrt::Windows::UI::Text::TextDecorations textDecorations = winrt::Windows::UI::Text::TextDecorations::None;
    if (styleProperties.IsStrikethrough())
    {
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Strikethrough);
    }

    if (styleProperties.IsUnderline() || styleProperties.IsInHyperlink())
    {
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Underline);
    }
    textElement.TextDecorations(textDecorations);
}

void SetXamlInlinesWithTextStyleConfig(rtom::IAdaptiveTextElement const& textElement,
                                       rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs,
                                       rtrender::AdaptiveTextStyleConfig const& textStyleConfig,
                                       rtxaml::Controls::TextBlock const& textBlock)
{
    SetXamlInlinesWithTextStyleConfig(
        renderContext, renderArgs, textStyleConfig, textElement, textElement.Language(), textElement.Text(), textBlock);
}

void SetXamlInlinesWithTextStyleConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs,
                                       rtrender::AdaptiveTextStyleConfig const& textStyle,
                                       rtom::IAdaptiveTextElement const& textElement, // TODO: optional?
                                       winrt::hstring const& language,
                                       winrt::hstring const& text,
                                       rtxaml::Controls::TextBlock const& textBlock)
{
    // Create an AdaptiveTextRun with the language, text, and configuration to pass to SetXamlInlines
    rtom::AdaptiveTextRun textRun{};
    textRun.Text(text);
    textRun.Language(language);

    // For weight, color, size, fontType, and isSubtle, use the value from the text element if there is one, otherwise use the value from the text style
    winrt::Windows::Foundation::IReference<rtom::TextWeight> weightToSet{textStyle.Weight()};
    winrt::Windows::Foundation::IReference<rtom::ForegroundColor> colorToSet{textStyle.Color()};
    winrt::Windows::Foundation::IReference<rtom::TextSize> sizeToSet{textStyle.Size()};
    winrt::Windows::Foundation::IReference<rtom::FontType> fontTypeToSet{textStyle.FontType()};
    winrt::Windows::Foundation::IReference<bool> isSubtleToSet{textStyle.IsSubtle()};

    if (textElement)
    {
        // TODO: is it better then: weightToSet = textElement.Weigth() ? textElement.Weight() : weightToSet;
        // TODO: may be create a helper for this purpose?
        // TODO: I'm using references instead of the values here so we don't have to go from ref -> value and then from
        // value -> ref again when using the resulting values
        // TODO: Instead I could either operate with values instead of refs and use GetValueFromRef
        // TODO: Or I can simply operate with refs and use GetValueFromRef like this : weightToSet =
        // GetValueFromRef(textElement.Weight(), textStyle.Weight())
        // TODO: It will convert from ref -> val -> ref again. That's the drawback
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

void SetXamlInlinesWithFactSetTextConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                         rtrender::AdaptiveRenderArgs const& renderArgs,
                                         rtrender::AdaptiveFactSetTextConfig const& factSetTextConfig,
                                         winrt::hstring const& language,
                                         winrt::hstring const& text,
                                         rtxaml::Controls::TextBlock const& textBlock)
{
    auto factSetTextConfigAsTextStyleConfig = factSetTextConfig.as<rtrender::AdaptiveTextStyleConfig>();

    SetXamlInlinesWithTextStyleConfig(renderContext, renderArgs, factSetTextConfigAsTextStyleConfig, nullptr, language, text, textBlock);

    // Set wrap and maxwidth
    SetWrapProperties(textBlock, factSetTextConfig.Wrap());
    textBlock.MaxWidth(factSetTextConfig.MaxWidth());
}

void SetWrapProperties(rtxaml::Controls::TextBlock const& xamlTextBlock, bool wrap)
{
    // Set whether the text wraps
    xamlTextBlock.TextWrapping(wrap ? rtxaml::TextWrapping::Wrap : rtxaml::TextWrapping::NoWrap);
    xamlTextBlock.TextTrimming(rtxaml::TextTrimming::CharacterEllipsis);
}

uint32_t SetXamlInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines)
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

        winrt::Windows::Data::Xml::Dom::XmlDocument xmlDocument{};
        xmlDocument.LoadXml(htmlHString);

        characterLength = AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, xmlDocument, isInHyperlink, inlines);
    }

    if (!handledAsHtml)
    {
        characterLength = AddSingleTextInline(
            adaptiveTextElement, renderContext, renderArgs, text, TextRunStyleParameters(false, false, false, isInHyperlink), inlines);
    }

    return characterLength;
}

static winrt::hstring GetTextFromXmlNode(winrt::Windows::Data::Xml::Dom::IXmlNode const& node)
{
    // TODO: is this correct?
    return node.InnerText();
}

uint32_t AddListInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        bool isListOrdered,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Documents::Inline> const& inlines)
{
    auto attributeMap = node.Attributes();
    auto startNode = attributeMap.GetNamedItem(L"start");

    // TODO: should we leave unsigned long? can we use uint64_t = unsigned long long?
    unsigned long iteration = 1;
    if (startNode)
    {
        // Get the starting value for this list
        auto start = GetTextFromXmlNode(startNode);
        try
        {
            // TODO: I don't fully understand this
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
            // TODO: not sure what's happening here...
            // If stoul throws out_of_range, start the numbered list at 1.
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

        rtxaml::Documents::Run run{};
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

uint32_t AddLinkInline(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                       rtrender::AdaptiveRenderContext const& renderContext,
                       rtrender::AdaptiveRenderArgs const& renderArgs,
                       winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                       bool isStrikethrough,
                       bool isItalic,
                       bool isUnderline,
                       winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> inlines)
{
    auto attributeMap = node.Attributes();
    auto hrefNode = attributeMap.GetNamedItem(L"href");

    if (hrefNode == nullptr)
    {
        // TODO: do we need to throw here?
        return 0;
    }

    auto href = GetTextFromXmlNode(hrefNode);

    winrt::Windows::Foundation::Uri uri{href};

    rtxaml::Documents::Hyperlink hyperlink{};
    hyperlink.NavigateUri(uri);

    auto hyperlinkInlines = hyperlink.Inlines();

    auto characterLength = AddTextInlines(adaptiveTextElement,
                                          renderContext,
                                          renderArgs,
                                          node,
                                          TextRunStyleParameters(isStrikethrough, isItalic, isUnderline, true),
                                          hyperlinkInlines);
    return characterLength;
}

uint32_t AddSingleTextInline(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs,
                             winrt::hstring const& stringToParse,
                             // TODO: should it be const TextRunStyleParameters& ?
                             TextRunStyleParameters const& styleParameters,
                             winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines)
{
    rtxaml::Documents::Run run{};

    winrt::hstring language = adaptiveTextElement.Language();

    DateTimeParser parser(HStringToUTF8(language));
    const auto textWithParsedDates = parser.GenerateString(HStringToUTF8(stringToParse));

    winrt::hstring textWithParsedDatesHString = UTF8ToHString(textWithParsedDates);

    run.Text(textWithParsedDatesHString);

    StyleTextElement(adaptiveTextElement, renderContext, renderArgs, styleParameters, run);

    inlines.Append(run);

    // TODO: are we sure we do not want to return the size of text that we assigned to run? (textWithParsedDatesHString)
    return stringToParse.size();
}

uint32_t AddTextInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        // TODO: should it be const& or const TextRunStyleParameters&??
                        TextRunStyleParameters const& styleParameters,
                        winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines)
{
    auto childNode = node.FirstChild();

    uint32_t totalCharacterLength = 0;
    while (childNode)
    {
        winrt::hstring nodeName = childNode.NodeName();

        bool isLinkResult = nodeName == L"A";
        bool isBoldResult = nodeName == L"strong";
        bool isItalicResult = nodeName == L"em";
        bool isTextResult = nodeName == L"#text";

        // TODO: would it be better to use 'switch'?
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
            rtom::IAdaptiveTextElement textElementToUse = adaptiveTextElement;
            if (isBoldResult || isItalicResult)
            {
                // Make a copy of the element so we can apply bold or italics
                // TODO: weird stuff..
                textElementToUse = CopyTextElement(adaptiveTextElement);

                if (isBoldResult)
                {
                    // TODO: no need to box it, right?
                    textElementToUse.Weight(rtom::TextWeight::Bolder);
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

    return totalCharacterLength;
}

uint32_t AddHtmlInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Documents::Inline> inlines)
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
        if (isOrderedListResult || isUnorderedListResult == 0)
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
                // there's more content... need a linebreak.
                // TODO: Can I do it this way?
                // TODO: Do we need to check for presnence of the API?
                inlines.Append(rtxaml::Documents::LineBreak{});
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
