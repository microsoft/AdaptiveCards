// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "DateTimeParser.h"
#include "MarkDownParser.h"
#include "TextHelpers.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include <safeint.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace AdaptiveCards::Rendering::WinUI3;
using namespace AdaptiveCards;
using namespace msl::utilities;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Media;
using namespace ABI::Windows::UI::Xaml;
using namespace std::string_literals;

//HRESULT StyleXamlTextBlockProperties(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextBlock* adaptiveTextBlock,
//                                     _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
//                                     _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
//                                     _In_ ITextBlock* xamlTextBlock)
//{
//    boolean wrap;
//    RETURN_IF_FAILED(adaptiveTextBlock->get_Wrap(&wrap));
//    RETURN_IF_FAILED(SetWrapProperties(xamlTextBlock, wrap));
//
//    UINT32 maxLines;
//    RETURN_IF_FAILED(adaptiveTextBlock->get_MaxLines(&maxLines));
//    if (maxLines != MAXUINT32)
//    {
//        ComPtr<ITextBlock> localXamlTextBlock(xamlTextBlock);
//        ComPtr<ITextBlock2> xamlTextBlock2;
//        RETURN_IF_FAILED(localXamlTextBlock.As(&xamlTextBlock2));
//        RETURN_IF_FAILED(xamlTextBlock2->put_MaxLines(maxLines));
//    }
//
//    RETURN_IF_FAILED(SetHorizontalAlignment(adaptiveTextBlock, renderContext, xamlTextBlock));
//
//    ComPtr<IAdaptiveTextBlock> localAdaptiveTextBlock(adaptiveTextBlock);
//    ComPtr<IAdaptiveTextElement> adaptiveTextElement;
//    RETURN_IF_FAILED(localAdaptiveTextBlock.As(&adaptiveTextElement));
//    RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement.Get(), renderContext, renderArgs, TextRunStyleParameters(), xamlTextBlock));
//
//    return S_OK;
//}

void StyleXamlTextBlockProperties(rtom::AdaptiveTextBlock const& adaptiveTextBlock,
                                  rtrender::AdaptiveRenderContext const& renderContext,
                                  rtrender::AdaptiveRenderArgs const& renderArgs,
                                  rtxaml::Controls::TextBlock const& xamlTextBlock)
{
    bool wrap = adaptiveTextBlock.Wrap();
    SetWrapProperties(xamlTextBlock, wrap);
    // RETURN_IF_FAILED(adaptiveTextBlock->get_Wrap(&wrap));
    // RETURN_IF_FAILED(SetWrapProperties(xamlTextBlock, wrap));

    /*   UINT32 maxLines;
       RETURN_IF_FAILED(adaptiveTextBlock->get_MaxLines(&maxLines));*/
    uint32_t maxLines = adaptiveTextBlock.MaxLines();
    if (maxLines != MAXUINT32)
    {
        /*ComPtr<ITextBlock> localXamlTextBlock(xamlTextBlock);
        ComPtr<ITextBlock2> xamlTextBlock2;
        RETURN_IF_FAILED(localXamlTextBlock.As(&xamlTextBlock2));
        RETURN_IF_FAILED(xamlTextBlock2->put_MaxLines(maxLines));*/
        xamlTextBlock.MaxLines(maxLines);
    }

    /* RETURN_IF_FAILED(SetHorizontalAlignment(adaptiveTextBlock, renderContext, xamlTextBlock));

     ComPtr<IAdaptiveTextBlock> localAdaptiveTextBlock(adaptiveTextBlock);
     ComPtr<IAdaptiveTextElement> adaptiveTextElement;
     RETURN_IF_FAILED(localAdaptiveTextBlock.As(&adaptiveTextElement));
     RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement.Get(), renderContext, renderArgs, TextRunStyleParameters(), xamlTextBlock));*/
    SetHorizontalAlignment(adaptiveTextBlock, renderContext, xamlTextBlock);
    auto size = adaptiveTextBlock.Size();

    StyleTextElement(adaptiveTextBlock, renderContext, renderArgs, TextRunStyleParameters(), xamlTextBlock);
}

HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties,
                                     _In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* textBlock)
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

// TODO: should it be const TextRunStyleParameters&?
void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties,
                                    rtxaml::Controls::TextBlock const& textBlock)
{
   /* ComPtr<ITextBlock> localTextBlock(textBlock);
    ComPtr<ITextBlock5> textBlock5;
    RETURN_IF_FAILED(localTextBlock.As(&textBlock5));*/

    winrt::Windows::UI::Text::TextDecorations textDecorations = winrt::Windows::UI::Text::TextDecorations::None;
    if (styleProperties.IsStrikethrough())
    {
        // TODO: what is this operator doing for enums? Figure out how to use it properly in winrt
        // TODO: find a better way to do it?
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Strikethrough);
    }

    if (styleProperties.IsUnderline() || styleProperties.IsInHyperlink())
    {
        textDecorations = EnumBitwiseOR(textDecorations, winrt::Windows::UI::Text::TextDecorations::Underline);
    }

    /*RETURN_IF_FAILED(textBlock5->put_TextDecorations(textDecorations));*/
    textBlock.TextDecorations(textDecorations);
}

HRESULT SetStrikethroughAndUnderline(const TextRunStyleParameters& styleProperties,
                                     _In_ ABI::Windows::UI::Xaml::Documents::ITextElement* textElement)
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

void SetStrikethroughAndUnderline(TextRunStyleParameters const& styleProperties,
                                     winrt::Windows::UI::Xaml::Documents::TextElement const& textElement)
{
   /* ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> localTextElement(textElement);
    ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement4> textElement4;
    RETURN_IF_FAILED(localTextElement.As(&textElement4));*/

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

//HRESULT SetXamlInlinesWithTextStyleConfig(_In_ IAdaptiveTextElement* textElement,
//                                          _In_ IAdaptiveRenderContext* renderContext,
//                                          _In_ IAdaptiveRenderArgs* renderArgs,
//                                          _In_ IAdaptiveTextStyleConfig* textStyleConfig,
//                                          _In_ ITextBlock* textBlock)
//{
//    HString language;
//    RETURN_IF_FAILED(textElement->get_Language(language.GetAddressOf()));
//
//    HString text;
//    RETURN_IF_FAILED(textElement->get_Text(text.GetAddressOf()));
//
//    RETURN_IF_FAILED(
//        SetXamlInlinesWithTextStyleConfig(renderContext, renderArgs, textStyleConfig, textElement, language.Get(), text.Get(), textBlock));
//
//    return S_OK;
//}

void SetXamlInlinesWithTextStyleConfig(rtom::IAdaptiveTextElement const& textElement,
                                       rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs,
                                       rtrender::AdaptiveTextStyleConfig const& textStyleConfig,
                                       rtxaml::Controls::TextBlock const& textBlock)
{
    /*HString language;
    RETURN_IF_FAILED(textElement->get_Language(language.GetAddressOf()));

    HString text;
    RETURN_IF_FAILED(textElement->get_Text(text.GetAddressOf()));*/

    auto language = textElement.Language();
    auto text = textElement.Text();

    /*RETURN_IF_FAILED(
        SetXamlInlinesWithTextStyleConfig(renderContext, renderArgs, textStyleConfig, textElement, language.Get(), text.Get(), textBlock));*/
    SetXamlInlinesWithTextStyleConfig(renderContext, renderArgs, textStyleConfig, textElement, language, text, textBlock);
}

//HRESULT SetXamlInlinesWithTextStyleConfig(_In_ IAdaptiveRenderContext* renderContext,
//                                          _In_ IAdaptiveRenderArgs* renderArgs,
//                                          _In_ IAdaptiveTextStyleConfig* textStyle,
//                                          _In_opt_ IAdaptiveTextElement* textElement,
//                                          _In_ HSTRING language,
//                                          _In_ HSTRING text,
//                                          _In_ ITextBlock* textBlock)
//{
//    // Create an AdaptiveTextRun with the language, text, and configuration to pass to SetXamlInlines
//    ComPtr<IAdaptiveTextRun> textRun = XamlHelpers::CreateABIClass<IAdaptiveTextRun>(
//        HStringReference(RuntimeClass_AdaptiveCards_ObjectModel_WinUI3_AdaptiveTextRun));
//
//    ComPtr<IAdaptiveTextElement> textRunAsTextElement;
//    RETURN_IF_FAILED(textRun.As(&textRunAsTextElement));
//
//    RETURN_IF_FAILED(textRunAsTextElement->put_Text(text));
//    RETURN_IF_FAILED(textRunAsTextElement->put_Language(language));
//
//    // For weight, color, size, fontType, and isSubtle, use the value from the text element if there is one, otherwise use the value from the text style
//
//    // TextWeight
//    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>> weightToSet;
//    if (textElement != nullptr)
//    {
//        ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>> elementWeight;
//        RETURN_IF_FAILED(textElement->get_Weight(&elementWeight));
//        if (elementWeight != nullptr)
//        {
//            weightToSet = elementWeight;
//        }
//    }
//    if (weightToSet == nullptr)
//    {
//        ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight weight;
//        RETURN_IF_FAILED(textStyle->get_Weight(&weight));
//
//        weightToSet = winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::TextWeight>(weight))
//                          .as<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>>()
//                          .get();
//    }
//    RETURN_IF_FAILED(textRunAsTextElement->put_Weight(weightToSet.Get()));
//
//    // ForegroundColor
//    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor>> colorToSet;
//    if (textElement != nullptr)
//    {
//        ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor>> elementColor;
//        RETURN_IF_FAILED(textElement->get_Color(&elementColor));
//        if (elementColor != nullptr)
//        {
//            colorToSet = elementColor;
//        }
//    }
//    if (colorToSet == nullptr)
//    {
//        ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor color;
//        RETURN_IF_FAILED(textStyle->get_Color(&color));
//
//        colorToSet = winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor>(color))
//                         .as<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor>>()
//                         .get();
//    }
//    RETURN_IF_FAILED(textRunAsTextElement->put_Color(colorToSet.Get()));
//
//    // TextSize
//    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize>> sizeToSet;
//    if (textElement != nullptr)
//    {
//        ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize>> elementSize;
//        RETURN_IF_FAILED(textElement->get_Size(&elementSize));
//        if (elementSize != nullptr)
//        {
//            sizeToSet = elementSize;
//        }
//    }
//    if (sizeToSet == nullptr)
//    {
//        ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize size;
//        RETURN_IF_FAILED(textStyle->get_Size(&size));
//
//        sizeToSet = winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::TextSize>(size))
//                        .as<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize>>()
//                        .get();
//    }
//    RETURN_IF_FAILED(textRunAsTextElement->put_Size(sizeToSet.Get()));
//
//    // FontType
//    ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::FontType>> fontTypeToSet;
//    if (textElement != nullptr)
//    {
//        ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::FontType>> elementFontType;
//        RETURN_IF_FAILED(textElement->get_FontType(&elementFontType));
//        if (elementFontType != nullptr)
//        {
//            fontTypeToSet = elementFontType;
//        }
//    }
//    if (fontTypeToSet == nullptr)
//    {
//        ABI::AdaptiveCards::ObjectModel::WinUI3::FontType fontType;
//        RETURN_IF_FAILED(textStyle->get_FontType(&fontType));
//
//        fontTypeToSet = winrt::box_value(static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::FontType>(fontType))
//                            .as<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::FontType>>()
//                            .get();
//    }
//    RETURN_IF_FAILED(textRunAsTextElement->put_FontType(fontTypeToSet.Get()));
//
//    // IsSubtle
//    ComPtr<IReference<bool>> isSubtleToSet;
//    if (textElement != nullptr)
//    {
//        ComPtr<IReference<bool>> elementIsSubtle;
//        RETURN_IF_FAILED(textElement->get_IsSubtle(&elementIsSubtle));
//        if (elementIsSubtle != nullptr)
//        {
//            isSubtleToSet = elementIsSubtle;
//        }
//    }
//    if (isSubtleToSet == nullptr)
//    {
//        boolean isSubtle;
//        RETURN_IF_FAILED(textStyle->get_IsSubtle(&isSubtle));
//
//        isSubtleToSet = winrt::box_value(static_cast<bool>(isSubtle)).as<IReference<bool>>().get();
//    }
//    RETURN_IF_FAILED(textRunAsTextElement->put_IsSubtle(isSubtleToSet.Get()));
//
//    ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
//    RETURN_IF_FAILED(textBlock->get_Inlines(&inlines));
//
//    // Style the text block with the properties from the TextRun
//    RETURN_IF_FAILED(StyleTextElement(textRunAsTextElement.Get(), renderContext, renderArgs, TextRunStyleParameters(), textBlock));
//
//    // Set the inlines
//    RETURN_IF_FAILED(SetXamlInlines(textRunAsTextElement.Get(), renderContext, renderArgs, false, inlines.Get()));
//
//    return S_OK;
//}

void SetXamlInlinesWithTextStyleConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                       rtrender::AdaptiveRenderArgs const& renderArgs,
                                       rtrender::AdaptiveTextStyleConfig const& textStyle,
                                       rtom::IAdaptiveTextElement const& textElement, // TODO: optional?
                                       winrt::hstring const& language,
                                       winrt::hstring const& text,
                                       rtxaml::Controls::TextBlock const& textBlock)
{
    // Create an AdaptiveTextRun with the language, text, and configuration to pass to SetXamlInlines
    /*ComPtr<IAdaptiveTextRun> textRun = XamlHelpers::CreateABIClass<IAdaptiveTextRun>(
        HStringReference(RuntimeClass_AdaptiveCards_ObjectModel_WinUI3_AdaptiveTextRun));*/
    rtom::AdaptiveTextRun textRun{};

    /* ComPtr<IAdaptiveTextElement> textRunAsTextElement;
     RETURN_IF_FAILED(textRun.As(&textRunAsTextElement));*/

    /* RETURN_IF_FAILED(textRunAsTextElement->put_Text(text));
     RETURN_IF_FAILED(textRunAsTextElement->put_Language(language));*/
    textRun.Text(text);
    textRun.Language(language);

    // For weight, color, size, fontType, and isSubtle, use the value from the text element if there is one, otherwise use the value from the text style

    // TextWeight
    /* ComPtr<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>> weightToSet;*/

    // if (textElement != nullptr)
    //{
    //    auto elementWeight = textElement.Weight();
    //    /*RETURN_IF_FAILED(textElement->get_Weight(&elementWeight));*/
    //    if (elementWeight != nullptr)
    //    {
    //        weightToSet = elementWeight;
    //    }
    //}

    winrt::Windows::Foundation::IReference<rtom::TextWeight> weightToSet{textStyle.Weight()};
    winrt::Windows::Foundation::IReference<rtom::ForegroundColor> colorToSet{textStyle.Color()};
    winrt::Windows::Foundation::IReference<rtom::TextSize> sizeToSet{textStyle.Size()};
    winrt::Windows::Foundation::IReference<rtom::FontType> fontTypeToSet{textStyle.FontType()};
    winrt::Windows::Foundation::IReference<bool> isSubtleToSet{textStyle.IsSubtle()};

    if (textElement != nullptr)
    {
        // TODO: is it better then: weightToSet = textElement.Weigth() != nullptr ? textElement.Weight() : weightToSet;
        // TODO: may be create a helper for this purpose?
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

    /*ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> inlines;
    RETURN_IF_FAILED(textBlock->get_Inlines(&inlines));*/
    auto inlines = textBlock.Inlines();

    // Style the text block with the properties from the TextRun
    /* RETURN_IF_FAILED(StyleTextElement(textRunAsTextElement.Get(), renderContext, renderArgs, TextRunStyleParameters(), textBlock));*/
    StyleTextElement(textRun, renderContext, renderArgs, TextRunStyleParameters(), textBlock);

    // Set the inlines
    // RETURN_IF_FAILED(SetXamlInlines(textRunAsTextElement.Get(), renderContext, renderArgs, false, inlines.Get()));
    SetXamlInlines(textRun, renderContext, renderArgs, false, inlines);
}

//HRESULT SetXamlInlinesWithFactSetTextConfig(_In_ IAdaptiveRenderContext* renderContext,
//                                            _In_ IAdaptiveRenderArgs* renderArgs,
//                                            _In_ IAdaptiveFactSetTextConfig* factSetTextConfig,
//                                            _In_ HSTRING language,
//                                            _In_ HSTRING text,
//                                            _In_ ITextBlock* textBlock)
//{
//    ComPtr<IAdaptiveFactSetTextConfig> factSetTextConfigLocal(factSetTextConfig);
//    ComPtr<IAdaptiveTextStyleConfig> factSetTextConfigAsTextStyleConfig;
//    RETURN_IF_FAILED(factSetTextConfigLocal.As(&factSetTextConfigAsTextStyleConfig));
//
//    RETURN_IF_FAILED(SetXamlInlinesWithTextStyleConfig(
//        renderContext, renderArgs, factSetTextConfigAsTextStyleConfig.Get(), nullptr, language, text, textBlock));
//
//    // Set wrap and maxwidth
//    boolean wrap;
//    RETURN_IF_FAILED(factSetTextConfig->get_Wrap(&wrap));
//    RETURN_IF_FAILED(SetWrapProperties(textBlock, wrap));
//
//    ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
//    ComPtr<ITextBlock> localTextBlock(textBlock);
//    RETURN_IF_FAILED(localTextBlock.As(&textBlockAsFrameworkElement));
//
//    UINT32 maxWidth;
//    RETURN_IF_FAILED(factSetTextConfig->get_MaxWidth(&maxWidth));
//    textBlockAsFrameworkElement->put_MaxWidth(maxWidth);
//
//    return S_OK;
//}

void SetXamlInlinesWithFactSetTextConfig(rtrender::AdaptiveRenderContext const& renderContext,
                                         rtrender::AdaptiveRenderArgs const& renderArgs,
                                         rtrender::AdaptiveFactSetTextConfig const& factSetTextConfig,
                                         winrt::hstring const& language,
                                         winrt::hstring const& text,
                                         rtxaml::Controls::TextBlock const& textBlock)
{
    /* ComPtr<IAdaptiveFactSetTextConfig> factSetTextConfigLocal(factSetTextConfig);
     ComPtr<IAdaptiveTextStyleConfig> factSetTextConfigAsTextStyleConfig;
     RETURN_IF_FAILED(factSetTextConfigLocal.As(&factSetTextConfigAsTextStyleConfig));

     RETURN_IF_FAILED(SetXamlInlinesWithTextStyleConfig(
         renderContext, renderArgs, factSetTextConfigAsTextStyleConfig.Get(), nullptr, language, text, textBlock));*/
    /*auto factSetTextConfigAsTextStyleConfig = factSetTextConfig.as<*/
    if (const auto factSetTextConfigAsTextStyleConfig = factSetTextConfig.try_as<rtrender::AdaptiveTextStyleConfig>())
    {
        SetXamlInlinesWithTextStyleConfig(renderContext, renderArgs, factSetTextConfigAsTextStyleConfig, nullptr, language, text, textBlock);
    }

    // Set wrap and maxwidth
    /*boolean wrap;
    RETURN_IF_FAILED(factSetTextConfig->get_Wrap(&wrap));
    RETURN_IF_FAILED(SetWrapProperties(textBlock, wrap));*/
    SetWrapProperties(textBlock, factSetTextConfig.Wrap());

    /*ComPtr<IFrameworkElement> textBlockAsFrameworkElement;
    ComPtr<ITextBlock> localTextBlock(textBlock);
    RETURN_IF_FAILED(localTextBlock.As(&textBlockAsFrameworkElement));*/

    /*UINT32 maxWidth;
    RETURN_IF_FAILED(factSetTextConfig->get_MaxWidth(&maxWidth));
    textBlockAsFrameworkElement->put_MaxWidth(maxWidth);*/
    textBlock.MaxWidth(factSetTextConfig.MaxWidth());
}

HRESULT SetWrapProperties(_In_ ABI::Windows::UI::Xaml::Controls::ITextBlock* xamlTextBlock, bool wrap)
{
    // Set whether the text wraps
    RETURN_IF_FAILED(xamlTextBlock->put_TextWrapping(wrap ? TextWrapping::TextWrapping_Wrap : TextWrapping::TextWrapping_NoWrap));
    RETURN_IF_FAILED(xamlTextBlock->put_TextTrimming(TextTrimming::TextTrimming_CharacterEllipsis));
    return S_OK;
}

void SetWrapProperties(rtxaml::Controls::TextBlock const& xamlTextBlock, bool wrap)
{
    // Set whether the text wraps
    xamlTextBlock.TextWrapping(wrap ? rtxaml::TextWrapping::Wrap : rtxaml::TextWrapping::NoWrap);
    xamlTextBlock.TextTrimming(rtxaml::TextTrimming::CharacterEllipsis);
}

//HRESULT SetXamlInlines(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
//                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
//                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
//                       bool isInHyperlink,
//                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
//                       _Out_opt_ UINT* characterLength)
//{
//    HString text;
//    RETURN_IF_FAILED(adaptiveTextElement->get_Text(text.GetAddressOf()));
//
//    HString language;
//    RETURN_IF_FAILED(adaptiveTextElement->get_Language(language.GetAddressOf()));
//
//    MarkDownParser markdownParser(HStringToUTF8(text.Get()));
//    auto htmlString = markdownParser.TransformToHtml();
//
//    bool handledAsHtml = false;
//    UINT localCharacterLength = 0;
//    if (markdownParser.HasHtmlTags())
//    {
//        HString htmlHString;
//        // wrap html in <root></root> in case there's more than one toplevel element.
//        UTF8ToHString("<root>"s + htmlString + "</root>"s, htmlHString.GetAddressOf());
//
//        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocument> xmlDocument =
//            XamlHelpers::CreateABIClass<ABI::Windows::Data::Xml::Dom::IXmlDocument>(
//                HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument));
//
//        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocumentIO> xmlDocumentIO;
//        RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentIO));
//
//        if (SUCCEEDED(xmlDocumentIO->LoadXml(htmlHString.Get())))
//        {
//            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> xmlDocumentAsNode;
//            RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentAsNode));
//
//            RETURN_IF_FAILED(
//                AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, xmlDocumentAsNode.Get(), isInHyperlink, inlines, &localCharacterLength));
//            handledAsHtml = true;
//        }
//    }
//
//    if (!handledAsHtml)
//    {
//        AddSingleTextInline(adaptiveTextElement,
//                            renderContext,
//                            renderArgs,
//                            text.Get(),
//                            TextRunStyleParameters(false, false, false, isInHyperlink),
//                            inlines,
//                            &localCharacterLength);
//    }
//
//    if (characterLength)
//    {
//        *characterLength = localCharacterLength;
//    }
//
//    return S_OK;
//}

uint32_t SetXamlInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines)
{
    /*HString text;
    RETURN_IF_FAILED(adaptiveTextElement->get_Text(text.GetAddressOf()));

    HString language;
    RETURN_IF_FAILED(adaptiveTextElement->get_Language(language.GetAddressOf()));*/

    auto text = adaptiveTextElement.Text();
    auto langugae = adaptiveTextElement.Language();

    MarkDownParser markdownParser(HStringToUTF8(text));
    auto htmlString = markdownParser.TransformToHtml();

    bool handledAsHtml = false;
    uint32_t localCharacterLength = 0;
    if (markdownParser.HasHtmlTags())
    {
        // wrap html in <root></root> in case there's more than one toplevel element.
        winrt::hstring htmlHString = UTF8ToHString("<root>"s + htmlString + "</root>"s);

        /* ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocument> xmlDocument =
             XamlHelpers::CreateABIClass<ABI::Windows::Data::Xml::Dom::IXmlDocument>(
                 HStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument));

         ComPtr<ABI::Windows::Data::Xml::Dom::IXmlDocumentIO> xmlDocumentIO;
         RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentIO));*/

        winrt::Windows::Data::Xml::Dom::XmlDocument xmlDocument{};
        xmlDocument.LoadXml(htmlHString);

        localCharacterLength = AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, xmlDocument, isInHyperlink, inlines);

        /* if (SUCCEEDED(xmlDocumentIO->LoadXml(htmlHString.Get())))
         {*/
        /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> xmlDocumentAsNode;
        RETURN_IF_FAILED(xmlDocument.As(&xmlDocumentAsNode));

        RETURN_IF_FAILED(
            AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, xmlDocumentAsNode.Get(), isInHyperlink,
        inlines, &localCharacterLength)); handledAsHtml = true;*/
        //}
    }

    if (!handledAsHtml)
    {
        localCharacterLength = AddSingleTextInline(
            adaptiveTextElement, renderContext, renderArgs, text, TextRunStyleParameters(false, false, false, isInHyperlink), inlines);
    }

    /*if (characterLength)
    {
        *characterLength = localCharacterLength;
    }*/

    // return S_OK;
    return localCharacterLength;
}

static HRESULT GetTextFromXmlNode(_In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node, _In_ HSTRING* text)
{
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> localNode = node;
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNodeSerializer> textNodeSerializer;
    RETURN_IF_FAILED(localNode.As(&textNodeSerializer));

    RETURN_IF_FAILED(textNodeSerializer->get_InnerText(text));
    return S_OK;
}

static winrt::hstring GetTextFromXmlNode(winrt::Windows::Data::Xml::Dom::IXmlNode const& node)
{
    /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> localNode = node;
    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNodeSerializer> textNodeSerializer;
    RETURN_IF_FAILED(localNode.As(&textNodeSerializer));

    RETURN_IF_FAILED(textNodeSerializer->get_InnerText(text));
    return S_OK;*/

    return node.InnerText();
}

//HRESULT AddListInlines(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
//                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
//                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
//                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
//                       bool isListOrdered,
//                       bool isInHyperlink,
//                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
//                       _Out_ UINT* characterLength)
//{
//    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
//    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));
//
//    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> startNode;
//    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"start").Get(), &startNode));
//
//    unsigned long iteration = 1;
//    if (startNode != nullptr)
//    {
//        // Get the starting value for this list
//        HString start;
//        RETURN_IF_FAILED(GetTextFromXmlNode(startNode.Get(), start.GetAddressOf()));
//        try
//        {
//            iteration = std::stoul(HStringToUTF8(start.Get()));
//
//            // Check that we can iterate the entire list without overflowing.
//            // If the list values are too big to store in an unsigned int, start
//            // the list at 1.
//            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNodeList> children;
//            RETURN_IF_FAILED(node->get_ChildNodes(&children));
//
//            UINT32 childrenLength;
//            RETURN_IF_FAILED(children->get_Length(&childrenLength));
//
//            unsigned long result;
//            if (!SafeAdd(iteration, childrenLength - 1, result))
//            {
//                iteration = 1;
//            }
//        }
//        catch (const std::out_of_range&)
//        {
//            // If stoul throws out_of_range, start the numbered list at 1.
//        }
//    }
//
//    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> listChild;
//    RETURN_IF_FAILED(node->get_FirstChild(&listChild));
//
//    UINT totalCharacterLength = 0;
//    bool isFirstListElement = true;
//    while (listChild != nullptr)
//    {
//        std::wstring listElementString = isFirstListElement ? L"" : L"\n";
//        if (!isListOrdered)
//        {
//            // Add a bullet
//            listElementString += L"\x2022 ";
//        }
//        else
//        {
//            listElementString += std::to_wstring(iteration);
//            listElementString += L". ";
//        }
//
//        HString listElementHString;
//        RETURN_IF_FAILED(listElementHString.Set(listElementString.c_str()));
//
//        totalCharacterLength += WindowsGetStringLen(listElementHString.Get());
//
//        ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> run =
//            XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IRun>(
//                HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));
//        RETURN_IF_FAILED(run->put_Text(listElementHString.Get()));
//
//        ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> runAsTextElement;
//        RETURN_IF_FAILED(run.As(&runAsTextElement));
//
//        // Make sure the bullet or list number is styled correctly
//        RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement,
//                                          renderContext,
//                                          renderArgs,
//                                          TextRunStyleParameters(false, false, false, isInHyperlink),
//                                          runAsTextElement.Get()));
//
//        ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> runAsInline;
//        RETURN_IF_FAILED(run.As(&runAsInline));
//
//        RETURN_IF_FAILED(inlines->Append(runAsInline.Get()));
//
//        UINT textCharacterLength = 0;
//        RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
//                                        renderContext,
//                                        renderArgs,
//                                        listChild.Get(),
//                                        TextRunStyleParameters(false, false, false, isInHyperlink),
//                                        inlines,
//                                        &textCharacterLength));
//        totalCharacterLength += textCharacterLength;
//
//        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextListChild;
//        RETURN_IF_FAILED(listChild->get_NextSibling(&nextListChild));
//
//        iteration++;
//        listChild = nextListChild;
//        isFirstListElement = false;
//    }
//
//    *characterLength = totalCharacterLength;
//    return S_OK;
//}

uint32_t AddListInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        bool isListOrdered,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Documents::Inline> const& inlines)
{
    /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));*/
    auto attributeMap = node.Attributes();

    /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> startNode;
    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"start").Get(), &startNode));*/
    auto startNode = attributeMap.GetNamedItem(L"start");

    unsigned long iteration = 1;
    if (startNode != nullptr)
    {
        // Get the starting value for this list
        /*HString start;
        RETURN_IF_FAILED(GetTextFromXmlNode(startNode.Get(), start.GetAddressOf()));*/
        auto start = GetTextFromXmlNode(startNode);
        try
        {
            iteration = std::stoul(HStringToUTF8(start));

            // Check that we can iterate the entire list without overflowing.
            // If the list values are too big to store in an unsigned int, start
            // the list at 1.
            /* ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNodeList> children;
             RETURN_IF_FAILED(node->get_ChildNodes(&children));*/
            auto children = node.ChildNodes();

            uint32_t childrenLength = children.Length();
            // RETURN_IF_FAILED(children->get_Length(&childrenLength));

            // TODO: can we do it in another way? store it in a bigger data type? like int64?
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

    /* ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> listChild;
     RETURN_IF_FAILED(node->get_FirstChild(&listChild));*/
    auto listChild = node.FirstChild();

    uint32_t totalCharacterLength = 0;
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

        /* HString listElementHString;
        RETURN_IF_FAILED(listElementHString.Set(listElementString.c_str()));*/
        /*totalCharacterLength += WindowsGetStringLen(listElementHString.Get());*/

        winrt::hstring listElementHString{listElementString};
        totalCharacterLength = listElementHString.size();

        /*ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> run =
            XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IRun>(
                HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));
        RETURN_IF_FAILED(run->put_Text(listElementHString.Get()));*/
        rtxaml::Documents::Run run{};
        run.Text(listElementHString);

        /*ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> runAsTextElement;
        RETURN_IF_FAILED(run.As(&runAsTextElement));*/

        // Make sure the bullet or list number is styled correctly
        /* RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement,
                                           renderContext,
                                           renderArgs,
                                           TextRunStyleParameters(false, false, false, isInHyperlink),
                                           runAsTextElement.Get()));*/
        StyleTextElement(adaptiveTextElement, renderContext, renderArgs, TextRunStyleParameters(false, false, false, isInHyperlink), run);

        /*ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> runAsInline;
        RETURN_IF_FAILED(run.As(&runAsInline));

        RETURN_IF_FAILED(inlines->Append(runAsInline.Get()));*/

        inlines.Append(run);

        /*UINT textCharacterLength = 0;
        RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
                                        renderContext,
                                        renderArgs,
                                        listChild.Get(),
                                        TextRunStyleParameters(false, false, false, isInHyperlink),
                                        inlines,
                                        &textCharacterLength));*/
        uint32_t textCharacterLength = AddTextInlines(adaptiveTextElement,
                                                      renderContext,
                                                      renderArgs,
                                                      listChild,
                                                      TextRunStyleParameters(false, false, false, isInHyperlink),
                                                      inlines);

        totalCharacterLength += textCharacterLength;

        /* ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextListChild;
         RETURN_IF_FAILED(listChild->get_NextSibling(&nextListChild));*/

        iteration++;
        /*listChild = nextListChild*/;
        listChild = listChild.NextSibling();
        isFirstListElement = false;
    }

    //*characterLength = totalCharacterLength;
    // return S_OK;
    return totalCharacterLength;
}

//HRESULT AddLinkInline(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
//                      _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
//                      _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
//                      _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
//                      bool isStrikethrough,
//                      bool isItalic,
//                      bool isUnderline,
//                      _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
//                      _Out_ UINT* characterLength)
//{
//    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
//    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));
//
//    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> hrefNode;
//    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"href").Get(), &hrefNode));
//
//    if (hrefNode == nullptr)
//    {
//        return E_INVALIDARG;
//    }
//
//    HString href;
//    RETURN_IF_FAILED(GetTextFromXmlNode(hrefNode.Get(), href.GetAddressOf()));
//
//    ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
//    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), &uriActivationFactory));
//
//    ComPtr<IUriRuntimeClass> uri;
//    RETURN_IF_FAILED(uriActivationFactory->CreateUri(href.Get(), uri.GetAddressOf()));
//
//    ComPtr<ABI::Windows::UI::Xaml::Documents::IHyperlink> hyperlink =
//        XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IHyperlink>(
//            HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Hyperlink));
//    RETURN_IF_FAILED(hyperlink->put_NavigateUri(uri.Get()));
//
//    ComPtr<ABI::Windows::UI::Xaml::Documents::ISpan> hyperlinkAsSpan;
//    RETURN_IF_FAILED(hyperlink.As(&hyperlinkAsSpan));
//
//    ComPtr<IVector<ABI::Windows::UI::Xaml::Documents::Inline*>> hyperlinkInlines;
//    RETURN_IF_FAILED(hyperlinkAsSpan->get_Inlines(hyperlinkInlines.GetAddressOf()));
//
//    RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
//                                    renderContext,
//                                    renderArgs,
//                                    node,
//                                    TextRunStyleParameters(isStrikethrough, isItalic, isUnderline, true),
//                                    hyperlinkInlines.Get(),
//                                    characterLength));
//
//    ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> hyperLinkAsInline;
//    RETURN_IF_FAILED(hyperlink.As(&hyperLinkAsInline));
//    RETURN_IF_FAILED(inlines->Append(hyperLinkAsInline.Get()));
//
//    return S_OK;
//}

uint32_t AddLinkInline(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                       rtrender::AdaptiveRenderContext const& renderContext,
                       rtrender::AdaptiveRenderArgs const& renderArgs,
                       winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                       bool isStrikethrough,
                       bool isItalic,
                       bool isUnderline,
                       winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> inlines)
{
    /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNamedNodeMap> attributeMap;
    RETURN_IF_FAILED(node->get_Attributes(&attributeMap));*/
    auto attributeMap = node.Attributes();

    /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> hrefNode;
    RETURN_IF_FAILED(attributeMap->GetNamedItem(HStringReference(L"href").Get(), &hrefNode));*/

    auto hrefNode = attributeMap.GetNamedItem(L"href");

    if (hrefNode == nullptr)
    {
        // TODO: do we need to throw here?
        return 0;
    }

    /*HString href;
    RETURN_IF_FAILED(GetTextFromXmlNode(hrefNode.Get(), href.GetAddressOf()));*/
    auto href = GetTextFromXmlNode(hrefNode);

    /* ComPtr<IUriRuntimeClassFactory> uriActivationFactory;
     RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), &uriActivationFactory));

     ComPtr<IUriRuntimeClass> uri;
     RETURN_IF_FAILED(uriActivationFactory->CreateUri(href.Get(), uri.GetAddressOf()));*/

    winrt::Windows::Foundation::Uri uri{href};

    /*ComPtr<ABI::Windows::UI::Xaml::Documents::IHyperlink> hyperlink =
        XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IHyperlink>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Hyperlink));
    RETURN_IF_FAILED(hyperlink->put_NavigateUri(uri.Get()));*/

    rtxaml::Documents::Hyperlink hyperlink{};
    hyperlink.NavigateUri(uri);

    /* ComPtr<ABI::Windows::UI::Xaml::Documents::ISpan> hyperlinkAsSpan;
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
     RETURN_IF_FAILED(inlines->Append(hyperLinkAsInline.Get()));*/

    auto hyperlinkInlines = hyperlink.Inlines();

    auto characterLength = AddTextInlines(adaptiveTextElement,
                                          renderContext,
                                          renderArgs,
                                          node,
                                          TextRunStyleParameters(isStrikethrough, isItalic, isUnderline, true),
                                          hyperlinkInlines);
    return characterLength;
}

//HRESULT AddSingleTextInline(_In_ IAdaptiveTextElement* adaptiveTextElement,
//                            _In_ IAdaptiveRenderContext* renderContext,
//                            _In_ IAdaptiveRenderArgs* renderArgs,
//                            _In_ HSTRING string,
//                            const TextRunStyleParameters& styleParameters,
//                            _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
//                            _Out_ UINT* characterLength)
//{
//    ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> run = XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IRun>(
//        HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));
//
//    HString language;
//    RETURN_IF_FAILED(adaptiveTextElement->get_Language(language.GetAddressOf()));
//
//    DateTimeParser parser(HStringToUTF8(language.Get()));
//    const auto textWithParsedDates = parser.GenerateString(HStringToUTF8(string));
//
//    HString textWithParsedDatesHString;
//    UTF8ToHString(textWithParsedDates, textWithParsedDatesHString.GetAddressOf());
//
//    RETURN_IF_FAILED(run->put_Text(textWithParsedDatesHString.Get()));
//
//    ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> runAsTextElement;
//    RETURN_IF_FAILED(run.As(&runAsTextElement));
//
//    RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement, renderContext, renderArgs, styleParameters, runAsTextElement.Get()));
//
//    ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> runAsInline;
//    RETURN_IF_FAILED(run.As(&runAsInline));
//
//    RETURN_IF_FAILED(inlines->Append(runAsInline.Get()));
//    *characterLength = WindowsGetStringLen(string);
//
//    return S_OK;
//}

uint32_t AddSingleTextInline(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                             rtrender::AdaptiveRenderContext const& renderContext,
                             rtrender::AdaptiveRenderArgs const& renderArgs,
                             winrt::hstring const& stringToParse,
                             // TODO: should it be const TextRunStyleParameters& ?
                             TextRunStyleParameters const& styleParameters,
                             winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines)
{ /*
     ComPtr<ABI::Windows::UI::Xaml::Documents::IRun> run = XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IRun>(
         HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_Run));

     HString language;
     RETURN_IF_FAILED(adaptiveTextElement->get_Language(language.GetAddressOf()));*/

    rtxaml::Documents::Run run{};

    winrt::hstring language = adaptiveTextElement.Language();

    DateTimeParser parser(HStringToUTF8(language));
    const auto textWithParsedDates = parser.GenerateString(HStringToUTF8(stringToParse));

    winrt::hstring textWithParsedDatesHString = UTF8ToHString(textWithParsedDates);

    // RETURN_IF_FAILED(run->put_Text(textWithParsedDatesHString.Get()));
    run.Text(textWithParsedDatesHString);

    /*ComPtr<ABI::Windows::UI::Xaml::Documents::ITextElement> runAsTextElement;
    RETURN_IF_FAILED(run.As(&runAsTextElement));

    RETURN_IF_FAILED(StyleTextElement(adaptiveTextElement, renderContext, renderArgs, styleParameters, runAsTextElement.Get()));

    ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> runAsInline;
    RETURN_IF_FAILED(run.As(&runAsInline));

    RETURN_IF_FAILED(inlines->Append(runAsInline.Get()));
    *characterLength = WindowsGetStringLen(string);*/
    StyleTextElement(adaptiveTextElement, renderContext, renderArgs, styleParameters, run);

    inlines.Append(run);

    // TODO: are we sure not the size of text that we assigned to run?
    return stringToParse.size();
}

//HRESULT AddTextInlines(_In_ IAdaptiveTextElement* adaptiveTextElement,
//                       _In_ IAdaptiveRenderContext* renderContext,
//                       _In_ IAdaptiveRenderArgs* renderArgs,
//                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
//                       const TextRunStyleParameters& styleParameters,
//                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
//                       _Out_ UINT* characterLength)
//{
//    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
//    RETURN_IF_FAILED(node->get_FirstChild(&childNode));
//
//    UINT totalCharacterLength = 0;
//    while (childNode != nullptr)
//    {
//        HString nodeName;
//        RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));
//
//        INT32 isLinkResult;
//        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"a").Get(), &isLinkResult));
//
//        INT32 isBoldResult;
//        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"strong").Get(), &isBoldResult));
//
//        INT32 isItalicResult;
//        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"em").Get(), &isItalicResult));
//
//        INT32 isTextResult;
//        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"#text").Get(), &isTextResult));
//
//        UINT nodeCharacterLength = 0;
//        if (isLinkResult == 0)
//        {
//            RETURN_IF_FAILED(AddLinkInline(adaptiveTextElement,
//                                           renderContext,
//                                           renderArgs,
//                                           childNode.Get(),
//                                           styleParameters.IsStrikethrough(),
//                                           styleParameters.IsItalic(),
//                                           styleParameters.IsUnderline(),
//                                           inlines,
//                                           &nodeCharacterLength));
//        }
//        else if (isTextResult == 0)
//        {
//            HString text;
//            RETURN_IF_FAILED(GetTextFromXmlNode(childNode.Get(), text.GetAddressOf()));
//            RETURN_IF_FAILED(
//                AddSingleTextInline(adaptiveTextElement, renderContext, renderArgs, text.Get(), styleParameters, inlines, &nodeCharacterLength));
//        }
//        else
//        {
//            ComPtr<IAdaptiveTextElement> textElementToUse(adaptiveTextElement);
//            if ((isBoldResult == 0) || (isItalicResult == 0))
//            {
//                // Make a copy of the element so we can apply bold or italics
//                RETURN_IF_FAILED(CopyTextElement(adaptiveTextElement, &textElementToUse));
//
//                if (isBoldResult == 0)
//                {
//                    RETURN_IF_FAILED(textElementToUse->put_Weight(
//                        winrt::box_value(winrt::AdaptiveCards::ObjectModel::WinUI3::TextWeight::Bolder)
//                            .as<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>>()
//                            .get()));
//                }
//            }
//
//            RETURN_IF_FAILED(AddTextInlines(textElementToUse.Get(),
//                                            renderContext,
//                                            renderArgs,
//                                            childNode.Get(),
//                                            TextRunStyleParameters(styleParameters.IsStrikethrough(),
//                                                                   styleParameters.IsItalic() || (isItalicResult == 0),
//                                                                   styleParameters.IsUnderline(),
//                                                                   styleParameters.IsInHyperlink()),
//                                            inlines,
//                                            &nodeCharacterLength));
//        }
//
//        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
//        RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
//        childNode = nextChildNode;
//        totalCharacterLength += nodeCharacterLength;
//    }
//
//    *characterLength = totalCharacterLength;
//
//    return S_OK;
//}

uint32_t AddTextInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        // TODO: should it be const& or const TextRunStyleParameters&??
                        TextRunStyleParameters const& styleParameters,
                        winrt::Windows::Foundation::Collections::IVector<rtxaml::Documents::Inline> const& inlines)
{
    /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
    RETURN_IF_FAILED(node->get_FirstChild(&childNode));*/
    auto childNode = node.FirstChild();

    uint32_t totalCharacterLength = 0;
    while (childNode != nullptr)
    {
        /*HString nodeName;
        RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));

        INT32 isLinkResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"a").Get(), &isLinkResult));

        INT32 isBoldResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"strong").Get(), &isBoldResult));

        INT32 isItalicResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"em").Get(), &isItalicResult));

        INT32 isTextResult;
        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"#text").Get(), &isTextResult));*/

        auto nodeName = childNode.NodeName();

        bool isLinkResult = nodeName == L"A";
        bool isBoldResult = nodeName == L"strong";
        bool isItalicResult = nodeName == L"em";
        bool isTextResult = nodeName == L"#text";

        uint32_t nodeCharacterLength = 0;
        if (isLinkResult)
        {
            /*RETURN_IF_FAILED(AddLinkInline(adaptiveTextElement,
                                           renderContext,
                                           renderArgs,
                                           childNode.Get(),
                                           styleParameters.IsStrikethrough(),
                                           styleParameters.IsItalic(),
                                           styleParameters.IsUnderline(),
                                           inlines,
                                           &nodeCharacterLength));*/
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
            /*HString text;
            RETURN_IF_FAILED(GetTextFromXmlNode(childNode.Get(), text.GetAddressOf()));
            RETURN_IF_FAILED(
                AddSingleTextInline(adaptiveTextElement, renderContext, renderArgs, text.Get(), styleParameters, inlines, &nodeCharacterLength));*/
            auto text = GetTextFromXmlNode(childNode);
            nodeCharacterLength =
                AddSingleTextInline(adaptiveTextElement, renderContext, renderArgs, text, styleParameters, inlines);
        }
        else
        {
            /*ComPtr<IAdaptiveTextElement> textElementToUse(adaptiveTextElement);*/
            rtom::IAdaptiveTextElement textElementToUse = adaptiveTextElement;
            if (isBoldResult || isItalicResult)
            {
                // Make a copy of the element so we can apply bold or italics
                // RETURN_IF_FAILED(CopyTextElement(adaptiveTextElement, &textElementToUse));
                CopyTextElement(adaptiveTextElement);

                if (isBoldResult)
                {
                    /* RETURN_IF_FAILED(textElementToUse->put_Weight(
                         winrt::box_value(winrt::AdaptiveCards::ObjectModel::WinUI3::TextWeight::Bolder)
                             .as<IReference<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>>()
                             .get()));*/
                    textElementToUse.Weight(rtom::TextWeight::Bolder);
                }
            }

            /*RETURN_IF_FAILED(AddTextInlines(textElementToUse.Get(),
                                            renderContext,
                                            renderArgs,
                                            childNode.Get(),
                                            TextRunStyleParameters(styleParameters.IsStrikethrough(),
                                                                   styleParameters.IsItalic() || (isItalicResult == 0),
                                                                   styleParameters.IsUnderline(),
                                                                   styleParameters.IsInHyperlink()),
                                            inlines,
                                            &nodeCharacterLength));*/
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

        /* ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
         RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
         childNode = nextChildNode;
         totalCharacterLength += nodeCharacterLength;*/
        childNode = childNode.NextSibling();
        totalCharacterLength += nodeCharacterLength;
    }

    return totalCharacterLength;
}

//HRESULT AddHtmlInlines(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
//                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
//                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
//                       _In_ ABI::Windows::Data::Xml::Dom::IXmlNode* node,
//                       bool isInHyperlink,
//                       _In_ IVector<ABI::Windows::UI::Xaml::Documents::Inline*>* inlines,
//                       _Out_ UINT* characterLength)
//{
//    ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
//    RETURN_IF_FAILED(node->get_FirstChild(&childNode));
//
//    // We *might* be looking at a toplevel chunk of HTML that we've wrapped with <root></root> (see SetXamlInlines())
//    // If so, strip that off.
//    {
//        HString childNodeName;
//        RETURN_IF_FAILED(childNode->get_NodeName(childNodeName.GetAddressOf()));
//        INT32 isRoot;
//        if (SUCCEEDED(WindowsCompareStringOrdinal(childNodeName.Get(), HStringReference(L"root").Get(), &isRoot)) && isRoot == 0)
//        {
//            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> actualChildNode;
//            RETURN_IF_FAILED(childNode->get_FirstChild(&actualChildNode));
//            childNode = actualChildNode;
//        }
//    }
//
//    UINT totalCharacterLength = 0;
//    while (childNode != nullptr)
//    {
//        HString nodeName;
//        RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));
//
//        INT32 isOrderedListResult;
//        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ol").Get(), &isOrderedListResult));
//
//        INT32 isUnorderedListResult;
//        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ul").Get(), &isUnorderedListResult));
//
//        INT32 isParagraphResult;
//        RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"p").Get(), &isParagraphResult));
//
//        UINT nodeCharacterLength = 0;
//        if ((isOrderedListResult == 0) || (isUnorderedListResult == 0))
//        {
//            RETURN_IF_FAILED(AddListInlines(
//                adaptiveTextElement, renderContext, renderArgs, childNode.Get(), (isOrderedListResult == 0), isInHyperlink, inlines, &nodeCharacterLength));
//        }
//        else if (isParagraphResult == 0)
//        {
//            RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
//                                            renderContext,
//                                            renderArgs,
//                                            childNode.Get(),
//                                            TextRunStyleParameters(false, false, false, isInHyperlink),
//                                            inlines,
//                                            &nodeCharacterLength));
//
//            // end of paragraph. check to see if there's more content. if there is, insert a line break
//            ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextSibling;
//            if (SUCCEEDED(childNode->get_NextSibling(&nextSibling)) && nextSibling)
//            {
//                // there's more content... need a linebreak.
//                ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> lineBreak =
//                    XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IInline>(
//                        HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_LineBreak));
//                if (lineBreak)
//                {
//                    RETURN_IF_FAILED(inlines->Append(lineBreak.Get()));
//                }
//            }
//        }
//        else
//        {
//            RETURN_IF_FAILED(
//                AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, childNode.Get(), isInHyperlink, inlines, &nodeCharacterLength));
//        }
//
//        ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
//        RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
//        childNode = nextChildNode;
//        totalCharacterLength += nodeCharacterLength;
//    }
//
//    *characterLength = totalCharacterLength;
//    return S_OK;
//}

uint32_t AddHtmlInlines(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                        rtrender::AdaptiveRenderContext const& renderContext,
                        rtrender::AdaptiveRenderArgs const& renderArgs,
                        winrt::Windows::Data::Xml::Dom::IXmlNode const& node,
                        bool isInHyperlink,
                        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Documents::Inline> inlines)
{
    /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> childNode;
    RETURN_IF_FAILED(node->get_FirstChild(&childNode));*/
    auto childNode = node.FirstChild();

    // We *might* be looking at a toplevel chunk of HTML that we've wrapped with <root></root> (see SetXamlInlines())
    // If so, strip that off.
    {
        /* HString childNodeName;
         RETURN_IF_FAILED(childNode->get_NodeName(childNodeName.GetAddressOf()));
         INT32 isRoot;*/
        auto childNodeName = childNode.NodeName();
        // if (SUCCEEDED(WindowsCompareStringOrdinal(childNodeName.Get(), HStringReference(L"root").Get(), &isRoot)) && isRoot == 0)
        if (childNodeName == L"root")
        {
            /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> actualChildNode;
            RETURN_IF_FAILED(childNode->get_FirstChild(&actualChildNode));
            childNode = actualChildNode;*/

            childNode = childNode.FirstChild();
        }
    }

    uint32_t totalCharacterLength = 0;
    while (childNode != nullptr)
    {
        /* HString nodeName;
         RETURN_IF_FAILED(childNode->get_NodeName(nodeName.GetAddressOf()));

         INT32 isOrderedListResult;
         RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ol").Get(), &isOrderedListResult));

         INT32 isUnorderedListResult;
         RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"ul").Get(), &isUnorderedListResult));

         INT32 isParagraphResult;
         RETURN_IF_FAILED(WindowsCompareStringOrdinal(nodeName.Get(), HStringReference(L"p").Get(), &isParagraphResult));*/
        auto nodeName = childNode.NodeName();

        auto isOrderedListResult = nodeName == L"ol";
        auto isUnorderedListResult = nodeName == L"ul";
        auto isParagraphResult = nodeName == L"p";

        uint32_t nodeCharacterLength = 0;
        if (isOrderedListResult || isUnorderedListResult == 0)
        {
            /*RETURN_IF_FAILED(AddListInlines(
                adaptiveTextElement, renderContext, renderArgs, childNode.Get(), (isOrderedListResult == 0),
               isInHyperlink, inlines, &nodeCharacterLength));*/
            nodeCharacterLength =
                // AddListInlines(adaptiveTextElement, renderContext, renderArgs, childNode, isOrderedListResult, isInHyperlink, inlines);
                AddListInlines(adaptiveTextElement, renderContext, renderArgs, childNode, isOrderedListResult, isInHyperlink, inlines);
        }
        else if (isParagraphResult)
        {
            /*RETURN_IF_FAILED(AddTextInlines(adaptiveTextElement,
                                            renderContext,
                                            renderArgs,
                                            childNode.Get(),
                                            TextRunStyleParameters(false, false, false, isInHyperlink),
                                            inlines,
                                            &nodeCharacterLength));*/

            nodeCharacterLength = AddTextInlines(adaptiveTextElement,
                                                 renderContext,
                                                 renderArgs,
                                                 childNode,
                                                 TextRunStyleParameters(false, false, false, isInHyperlink),
                                                 inlines);

            // end of paragraph. check to see if there's more content. if there is, insert a line break
            // ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextSibling;
            auto nextSibling = childNode.NextSibling();
            // if (SUCCEEDED(childNode->get_NextSibling(&nextSibling)) && nextSibling)
            if (nextSibling != nullptr)
            {
                // there's more content... need a linebreak.
                /* ComPtr<ABI::Windows::UI::Xaml::Documents::IInline> lineBreak =
                     XamlHelpers::CreateABIClass<ABI::Windows::UI::Xaml::Documents::IInline>(
                         HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_LineBreak));
                 if (lineBreak)
                 {
                     RETURN_IF_FAILED(inlines->Append(lineBreak.Get()));
                 }*/
                // TODO: Can I do it this way?
                inlines.Append(rtxaml::Documents::LineBreak{});
            }
        }
        else
        {
            /*RETURN_IF_FAILED(
                AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, childNode.Get(), isInHyperlink, inlines, &nodeCharacterLength));*/
            nodeCharacterLength = AddHtmlInlines(adaptiveTextElement, renderContext, renderArgs, childNode, isInHyperlink, inlines);
        }

        /*ComPtr<ABI::Windows::Data::Xml::Dom::IXmlNode> nextChildNode;
        RETURN_IF_FAILED(childNode->get_NextSibling(&nextChildNode));
        childNode = nextChildNode;*/
        childNode = childNode.NextSibling();
        totalCharacterLength += nodeCharacterLength;
    }

    //*characterLength = totalCharacterLength;
    // return S_OK;
    return totalCharacterLength;
}
