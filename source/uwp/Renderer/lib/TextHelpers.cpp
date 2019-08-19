// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveTextRun.h"
#include "DateTimeParser.h"
#include "MarkDownParser.h"
#include "TextHelpers.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include <safeint.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace AdaptiveNamespace;
using namespace AdaptiveSharedNamespace;
using namespace msl::utilities;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml;
using namespace std::string_literals;

HRESULT StyleXamlTextBlockProperties(_In_ ABI::AdaptiveNamespace::IAdaptiveTextBlock* adaptiveTextBlock,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                                     _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                                     _In_ ITextBlock* xamlTextBlock)
{
    boolean wrap;
    RETURN_IF_FAILED(adaptiveTextBlock->get_Wrap(&wrap));
    RETURN_IF_FAILED(SetWrapProperties(xamlTextBlock, wrap));

    UINT32 maxLines;
    RETURN_IF_FAILED(adaptiveTextBlock->get_MaxLines(&maxLines));
    if (maxLines != MAXUINT32)
    {
        ComPtr<ITextBlock> localXamlTextBlock(xamlTextBlock);
        ComPtr<ITextBlock2> xamlTextBlock2;
        RETURN_IF_FAILED(localXamlTextBlock.As(&xamlTextBlock2));
        RETURN_IF_FAILED(xamlTextBlock2->put_MaxLines(maxLines));
    }

    RETURN_IF_FAILED(SetHorizontalAlignment(adaptiveTextBlock, xamlTextBlock));

    ComPtr<IAdaptiveTextBlock> localAdaptiveTextBlock(adaptiveTextBlock);
    ComPtr<IAdaptiveTextElement> adaptiveTextElement;
    RETURN_IF_FAILED(localAdaptiveTextBlock.As(&adaptiveTextElement));
    RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement.Get(), renderContext, renderArgs, TextRunStyleParameters(), xamlTextBlock));

    return S_OK;
}

HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties, _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock)
{
    ComPtr<ITextBlock> localTextBlock(textBlock);
    ComPtr<ITextBlock5> textBlock5;
    RETURN_IF_FAILED(localTextBlock.As(&textBlock5));

    ABI::Windows::UI::Text::TextDecorations textDecorations = ABI::Windows::UI::Text::TextDecorations::TextDecorations_None;
    if (styleProperties.IsStrikethrough())
    {
        textDecorations |= ABI::Windows::UI::Text::TextDecorations::TextDecorations_Strikethrough;
    }

    if (styleProperties.IsUnderline() || styleProperties.IsInHyperlink())
    {
        textDecorations |= ABI::Windows::UI::Text::TextDecorations::TextDecorations_Underline;
    }

    RETURN_IF_FAILED(textBlock5->put_TextDecorations(textDecorations));
    return S_OK;
}

HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties, _In_ ABI::Windows::UI::Xaml::Documents::ITextElement* textElement)
{
    ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> localTextElement(textElement);
    ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement4> textElement4;
    RETURN_IF_FAILED(localTextElement.As(&textElement4));

    ABI::Windows::UI::Text::TextDecorations textDecorations = ABI::Windows::UI::Text::TextDecorations::TextDecorations_None;
    if (styleProperties.IsStrikethrough())
    {
        textDecorations |= ABI::Windows::UI::Text::TextDecorations::TextDecorations_Strikethrough;
    }

    if (styleProperties.IsUnderline() || styleProperties.IsInHyperlink())
    {
        textDecorations |= ABI::Windows::UI::Text::TextDecorations::TextDecorations_Underline;
    }

    RETURN_IF_FAILED(textElement4->put_TextDecorations(textDecorations));
    return S_OK;
}

HRESULT SetXamlInlinesWithTextConfig(_In_ IAdaptiveRenderContext* renderContext,
                                     _In_ IAdaptiveRenderArgs* renderArgs,
                                     _In_ IAdaptiveTextConfig* textConfig,
                                     _In_ HSTRING language,
                                     _In_ HSTRING text,
                                     _In_ ITextBlock* textBlock)
{
    // Create an AdaptiveTextRun with the language, text, and configuration to pass to SetXamlInlines
    ComPtr<AdaptiveNamespace::AdaptiveTextRun> textRun;
    RETURN_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveTextRun>(&textRun));

    RETURN_IF_FAILED(textRun->put_Text(text));
    RETURN_IF_FAILED(textRun->put_Language(language));

    ABI::AdaptiveNamespace::TextWeight weight;
    RETURN_IF_FAILED(textConfig->get_Weight(&weight));
    RETURN_IF_FAILED(textRun->put_Weight(weight));

    ABI::AdaptiveNamespace::ForegroundColor color;
    RETURN_IF_FAILED(textConfig->get_Color(&color));
    RETURN_IF_FAILED(textRun->put_Color(color));

    ABI::AdaptiveNamespace::TextSize size;
    RETURN_IF_FAILED(textConfig->get_Size(&size));
    RETURN_IF_FAILED(textRun->put_Size(size));

    boolean isSubtle;
    RETURN_IF_FAILED(textConfig->get_IsSubtle(&isSubtle));
    RETURN_IF_FAILED(textRun->put_IsSubtle(isSubtle));

    ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
    RETURN_IF_FAILED(textBlock->get_Inlines(&inlines));

    // Style the text block with the properties from the TextRun
    RETURN_IF_FAILED(StyleTextElement(textRun.Get(), renderContext, renderArgs, TextRunStyleParameters(), textBlock));

    // Set the inlines
    RETURN_IF_FAILED(SetXamlInlines(textRun.Get(), renderContext, renderArgs, false, inlines.Get()));

    // Set wrap and maxwidth
    boolean wrap;
    RETURN_IF_FAILED(textConfig->get_Wrap(&wrap));
    RETURN_IF_FAILED(SetWrapProperties(textBlock, wrap));

    ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
    ComPtr<ITextBlock> localTextBlock(textBlock);
    RETURN_IF_FAILED(localTextBlock.As(&textBlockAsFrameworkElement));

    UINT32 maxWidth;
    RETURN_IF_FAILED(textConfig->get_MaxWidth(&maxWidth));
    textBlockAsFrameworkElement->put_MaxWidth(maxWidth);

    return S_OK;
}

HRESULT SetWrapProperties(_In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock, bool wrap)
{
    // Set whether the text wraps
    RETURN_IF_FAILED(xamlTextBlock->put_TextWrapping(wrap ? TextWrapping::TextWrapping_Wrap : TextWrapping::TextWrapping_NoWrap));
    RETURN_IF_FAILED(xamlTextBlock->put_TextTrimming(TextTrimming::TextTrimming_CharacterEllipsis));
    return S_OK;
}

HRESULT SetXamlInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                       bool isInHyperlink,
                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_opt_ UINT* characterLength)
{
    HString text;
    RETURN_IF_FAILED(adaptiveTextElement->get_Text(text.GetAddressOf()));

    HString language;
    RETURN_IF_FAILED(adaptiveTextElement->get_Language(language.GetAddressOf()));

    MarkDownParser markdownParser(HStringToUTF8(text.Get()));
    auto htmlString = markdownParser.TransformToHtml();

    bool handledAsHtml = false;
    UINT localCharacterLength = 0;
    if (markdownParser.HasHtmlTags())
    {
        HString htmlHString;
        // wrap html in <root></root> in case there's more than one toplevel element.
        UTF8ToHString("<root>"s + htmlString + "</root>"s, htmlHString.GetAddressOf());

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocument> xmlDocument =
            XamlHelpers::CreateXamlClass<ABI::Windows::Data::Xml::Dom::IXmlDocument>(
                HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument));

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocumentIO> xmlDocumentIO;
        RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentIO));

        if (SUCCEEDED(xmlDocumentIO->LoadXml(htmlHString.Get())))
        {
            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> xmlDocumentAsNode;
            RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentAsNode));

            RETURN_IF_FAILED(
                AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, xmlDocumentAsNode.Get(), isInHyperlink, inlines, &localCharacterLength));
            handledAsHtml = true;
        }
    }

    if (!handledAsHtml)
    {
        AddSingleTextInline(adaptiveTextElement,
                            renderContext,
                            renderArgs,
                            text.Get(),
                            TextRunStyleParameters(false, false, false, isInHyperlink),
                            inlines,
                            &localCharacterLength);
    }

    if (characterLength)
    {
        *characterLength = localCharacterLength;
    }

    return S_OK;
}

static HRESULT GetTextFromXmlNode(_In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node, _In_ HSTRING* text)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> localNode = node;
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNodeSerializer> textNodeSerializer;
    RETURN_IF_FAILED(localNode.As(&textNodeSerializer));

    RETURN_IF_FAILED(textNodeSerializer->get_InnerText(text));
    return S_OK;
}

HRESULT AddListInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       bool isListOrdered,
                       bool isInHyperlink,
                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_ UINT* characterLength)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));

    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> startNode;
    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"start").Get(), &startNode));

    unsigned long iteration = 1;
    if (startNode != nullptr)
    {
        // Get the starting value for this list
        HString start;
        RETURN_IF_FAILED(GetTextFromXmlNode(startNode.Get(), start.GetAddressOf()));
        try
        {
            iteration = std::stoul(HStringToUTF8(start.Get()));

            // Check that we can iterate the entire list without overflowing.
            // If the list values are too big to store in an unsigned int, start
            // the list at 1.
            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNodeList> children;
            RETURN_IF_FAILED(node->get_ChildNodes(&children));

            UINT32 childrenLength;
            RETURN_IF_FAILED(children->get_Length(&childrenLength));

            unsigned long result;
            if (!SafeAdd(iteration, childrenLength - 1, result))
            {
                iteration = 1;
            }
        }
        catch (const std::out_of_range&)
        {
            // If stoul throws out_of_range, start the numbered list at 1.
        }
    }

    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> listChild;
    RETURN_IF_FAILED(node->get_FirstChild(&listChild));

    UINT totalCharacterLength = 0;
    bool isFirstListElement = true;
    while (listChild != nullptr)
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

        HString listElementHString;
        RETURN_IF_FAILED(listElementHString.Set(listElementString.c_str()));

        totalCharacterLength += WindowsGetStringLen(listElementHString.Get());

        ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> run =
            XamlHelpers::CreateXamlClass<ABI::Windows::UI::Xaml::Documents::IRun>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));
        RETURN_IF_FAILED(run->put_Text(listElementHString.Get()));

        ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> runAsTextElement;
        RETURN_IF_FAILED(run.As(&runAsTextElement));

        // Make sure the bullet or list number is styled correctly
        RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement,
                                          renderContext,
                                          renderArgs,
                                          TextRunStyleParameters(false, false, false, isInHyperlink),
                                          runAsTextElement.Get()));

        ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> runAsInline;
        RETURN_IF_FAILED(run.As(&runAsInline));

        RETURN_IF_FAILED(inlines->Append(runAsInline.Get()));

        UINT textCharacterLength = 0;
        RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
                                        renderContext,
                                        renderArgs,
                                        listChild.Get(),
                                        TextRunStyleParameters(false, false, false, isInHyperlink),
                                        inlines,
                                        &textCharacterLength));
        totalCharacterLength += textCharacterLength;

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextListChild;
        RETURN_IF_FAILED(listChild->get_NextSibling(&nextListChild));

        iteration++;
        listChild = nextListChild;
        isFirstListElement = false;
    }

    *characterLength = totalCharacterLength;
    return S_OK;
}

HRESULT AddLinkInline(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                      _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                      _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                      _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                      bool isStrikethrough,
                      bool isItalic,
                      bool isUnderline,
                      _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                      _Out_ UINT* characterLength)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));

    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> hrefNode;
    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"href").Get(), &hrefNode));

    if (hrefNode == nullptr)
    {
        return E_INVALIDARG;
    }

    HString href;
    RETURN_IF_FAILED(GetTextFromXmlNode(hrefNode.Get(), href.GetAddressOf()));

    ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), &uriActivationFactory));

    ComPtr<IUriRuntimeClass> uri;
    RETURN_IF_FAILED(uriActivationFactory->CreateUri(href.Get(), uri.GetAddressOf()));

    ComPtr<ABI::Windows::UI::Xaml::Documents::IHyperlink> hyperlink =
        XamlHelpers::CreateXamlClass<ABI::Windows::UI::Xaml::Documents::IHyperlink>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Hyperlink));
    RETURN_IF_FAILED(hyperlink->put_NavigateUri(uri.Get()));

    ComPtr<ABI::Windows::UI::Xaml::Documents::ISpan> hyperlinkAsSpan;
    RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsSpan));

    ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> hyperlinkInlines;
    RETURN_IF_FAILED(hyperlinkAsSpan->get_Inlines(hyperlinkInlines.GetAddressOf()));

    RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
                                    renderContext,
                                    renderArgs,
                                    node,
                                    TextRunStyleParameters(isStrikethrough, isItalic, isUnderline, true),
                                    hyperlinkInlines.Get(),
                                    characterLength));

    ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> hyperLinkAsInline;
    RETURN_IF_FAILED(hyperlink.As(&hyperLinkAsInline));
    RETURN_IF_FAILED(inlines->Append(hyperLinkAsInline.Get()));

    return S_OK;
}

HRESULT AddSingleTextInline(_In_ IAdaptiveTextElement* adaptiveTextElement,
                            _In_ IAdaptiveRenderContext* renderContext,
                            _In_ IAdaptiveRenderArgs* renderArgs,
                            _In_ HSTRING string,
                            const TextRunStyleParameters& styleParameters,
                            _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                            _Out_ UINT* characterLength)
{
    ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> run = XamlHelpers::CreateXamlClass<ABI::Windows::UI::Xaml::Documents::IRun>(
        HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));

    HString language;
    RETURN_IF_FAILED(adaptiveTextElement->get_Language(language.GetAddressOf()));

    DateTimeParser parser(HStringToUTF8(language.Get()));
    const auto textWithParsedDates = parser.GenerateString(HStringToUTF8(string));

    HString textWithParsedDatesHString;
    UTF8ToHString(textWithParsedDates, textWithParsedDatesHString.GetAddressOf());

    RETURN_IF_FAILED(run->put_Text(textWithParsedDatesHString.Get()));

    ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> runAsTextElement;
    RETURN_IF_FAILED(run.As(&runAsTextElement));

    RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement, renderContext, renderArgs, styleParameters, runAsTextElement.Get()));

    ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> runAsInline;
    RETURN_IF_FAILED(run.As(&runAsInline));

    RETURN_IF_FAILED(inlines->Append(runAsInline.Get()));
    *characterLength = WindowsGetStringLen(string);

    return S_OK;
}

HRESULT AddTextInlines(_In_ IAdaptiveTextElement* adaptiveTextElement,
                       _In_ IAdaptiveRenderContext* renderContext,
                       _In_ IAdaptiveRenderArgs* renderArgs,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       const TextRunStyleParameters& styleParameters,
                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_ UINT* characterLength)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
    RETURN_IF_FAILED(node->get_FirstChild(&childNode));

    UINT totalCharacterLength = 0;
    while (childNode != nullptr)
    {
        HString nodeName;
        RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));

        INT32 isLinkResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"a").Get(), &isLinkResult));

        INT32 isBoldResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"strong").Get(), &isBoldResult));

        INT32 isItalicResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"em").Get(), &isItalicResult));

        INT32 isTextResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"#text").Get(), &isTextResult));

        UINT nodeCharacterLength = 0;
        if (isLinkResult == 0)
        {
            RETURN_IF_FAILED(AddLinkInline(adaptiveTextElement,
                                           renderContext,
                                           renderArgs,
                                           childNode.Get(),
                                           styleParameters.IsStrikethrough(),
                                           styleParameters.IsItalic(),
                                           styleParameters.IsUnderline(),
                                           inlines,
                                           &nodeCharacterLength));
        }
        else if (isTextResult == 0)
        {
            HString text;
            RETURN_IF_FAILED(GetTextFromXmlNode(childNode.Get(), text.GetAddressOf()));
            RETURN_IF_FAILED(
                AddSingleTextInline(adaptiveTextElement, renderContext, renderArgs, text.Get(), styleParameters, inlines, &nodeCharacterLength));
        }
        else
        {
            ComPtr<IAdaptiveTextElement> textElementToUse(adaptiveTextElement);
            if ((isBoldResult == 0) || (isItalicResult == 0))
            {
                // Make a copy of the element so we can apply bold or italics
                RETURN_IF_FAILED(CopyTextElement(adaptiveTextElement, &textElementToUse));

                if (isBoldResult == 0)
                {
                    RETURN_IF_FAILED(textElementToUse->put_Weight(ABI::AdaptiveNamespace::TextWeight::Bolder));
                }
            }

            RETURN_IF_FAILED(AddTextInlines(textElementToUse.Get(),
                                            renderContext,
                                            renderArgs,
                                            childNode.Get(),
                                            TextRunStyleParameters(styleParameters.IsStrikethrough(),
                                                                   styleParameters.IsItalic() || (isItalicResult == 0),
                                                                   styleParameters.IsUnderline(),
                                                                   styleParameters.IsInHyperlink()),
                                            inlines,
                                            &nodeCharacterLength));
        }

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
        RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
        childNode = nextChildNode;
        totalCharacterLength += nodeCharacterLength;
    }

    *characterLength = totalCharacterLength;

    return S_OK;
}

HRESULT AddHtmlInlines(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
                       bool isInHyperlink,
                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
                       _Out_ UINT* characterLength)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
    RETURN_IF_FAILED(node->get_FirstChild(&childNode));

    // We *might* be looking at a toplevel chunk of HTML that we've wrapped with <root></root> (see SetXamlInlines())
    // If so, strip that off.
    {
        HString childNodeName;
        RETURN_IF_FAILED(childNode->get_NodeName(childNodeName.GetAddressOf()));
        INT32 isRoot;
        if (SUCCEEDED(WindowsCompareStringOrdinal(childNodeName.Get(), HStringReference(L"root").Get(), &isRoot)) && isRoot == 0)
        {
            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> actualChildNode;
            RETURN_IF_FAILED(childNode->get_FirstChild(&actualChildNode));
            childNode = actualChildNode;
        }
    }

    UINT totalCharacterLength = 0;
    while (childNode != nullptr)
    {
        HString nodeName;
        RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));

        INT32 isOrderedListResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ol").Get(), &isOrderedListResult));

        INT32 isUnorderedListResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ul").Get(), &isUnorderedListResult));

        INT32 isParagraphResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"p").Get(), &isParagraphResult));

        UINT nodeCharacterLength = 0;
        if ((isOrderedListResult == 0) || (isUnorderedListResult == 0))
        {
            RETURN_IF_FAILED(AddListInlines(
                adaptiveTextElement, renderContext, renderArgs, childNode.Get(), (isOrderedListResult == 0), isInHyperlink, inlines, &nodeCharacterLength));
        }
        else if (isParagraphResult == 0)
        {
            RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
                                            renderContext,
                                            renderArgs,
                                            childNode.Get(),
                                            TextRunStyleParameters(false, false, false, isInHyperlink),
                                            inlines,
                                            &nodeCharacterLength));

            // end of paragraph. check to see if there's more content. if there is, insert a line break
            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextSibling;
            if (SUCCEEDED(childNode->get_NextSibling(&nextSibling)) && nextSibling)
            {
                // there's more content... need a linebreak.
                ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> lineBreak =
                    XamlHelpers::CreateXamlClass<ABI::Windows::UI::Xaml::Documents::IInline>(
                        HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_LineBreak));
                if (lineBreak)
                {
                    RETURN_IF_FAILED(inlines->Append(lineBreak.Get()));
                }
            }
        }
        else
        {
            RETURN_IF_FAILED(
                AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, childNode.Get(), isInHyperlink, inlines, &nodeCharacterLength));
        }

        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
        RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
        childNode = nextChildNode;
        totalCharacterLength += nodeCharacterLength;
    }

    *characterLength = totalCharacterLength;
    return S_OK;
}
