// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "TextRun.h"

using namespace AdaptiveSharedNamespace;

TextRun::TextRun() :
    Inline(InlineElementType::TextRun), m_textElementProperties(std::make_shared<RichTextElementProperties>()),
    m_highlight(false)
{
    PopulateKnownPropertiesSet();
}

void TextRun::PopulateKnownPropertiesSet()
{
    m_textElementProperties->PopulateKnownPropertiesSet(m_knownProperties);
}

Json::Value TextRun::SerializeToJsonValue() const
{
    Json::Value root{};
    root = m_textElementProperties->SerializeToJsonValue(root);
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = GetInlineTypeString();

    if (m_highlight)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Highlight)] = true;
    }

    if (m_selectAction != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction)] = m_selectAction->SerializeToJsonValue();
    }

    return root;
}

std::string TextRun::GetText() const
{
    return m_textElementProperties->GetText();
}

void TextRun::SetText(const std::string& value)
{
    m_textElementProperties->SetText(value);
}

DateTimePreparser TextRun::GetTextForDateParsing() const
{
    return m_textElementProperties->GetTextForDateParsing();
}

TextSize TextRun::GetTextSize() const
{
    return m_textElementProperties->GetTextSize();
}

void TextRun::SetTextSize(const TextSize value)
{
    m_textElementProperties->SetTextSize(value);
}

TextWeight TextRun::GetTextWeight() const
{
    return m_textElementProperties->GetTextWeight();
}

void TextRun::SetTextWeight(const TextWeight value)
{
    m_textElementProperties->SetTextWeight(value);
}

FontType TextRun::GetFontType() const
{
    return m_textElementProperties->GetFontType();
}

void TextRun::SetFontType(const FontType value)
{
    m_textElementProperties->SetFontType(value);
}

ForegroundColor TextRun::GetTextColor() const
{
    return m_textElementProperties->GetTextColor();
}

void TextRun::SetTextColor(const ForegroundColor value)
{
    m_textElementProperties->SetTextColor(value);
}

bool TextRun::GetIsSubtle() const
{
    return m_textElementProperties->GetIsSubtle();
}

void TextRun::SetIsSubtle(const bool value)
{
    m_textElementProperties->SetIsSubtle(value);
}

bool TextRun::GetItalic() const
{
    return m_textElementProperties->GetItalic();
}

void TextRun::SetItalic(const bool value)
{
    m_textElementProperties->SetItalic(value);
}

bool TextRun::GetStrikethrough() const
{
    return m_textElementProperties->GetStrikethrough();
}

void TextRun::SetStrikethrough(const bool value)
{
    m_textElementProperties->SetStrikethrough(value);
}

bool TextRun::GetHighlight() const
{
    return m_highlight;
}

void TextRun::SetHighlight(const bool value)
{
    m_highlight = value;
}

std::string TextRun::GetLanguage() const
{
    return m_textElementProperties->GetLanguage();
}

void TextRun::SetLanguage(const std::string& value)
{
    m_textElementProperties->SetLanguage(value);
}

std::shared_ptr<BaseActionElement> TextRun::GetSelectAction() const
{
    return m_selectAction;
}

void TextRun::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

bool TextRun::GetUnderline() const
{
    return m_textElementProperties->GetUnderline();
}

void TextRun::SetUnderline(const bool value)
{
    m_textElementProperties->SetUnderline(value);
}

std::shared_ptr<Inline> TextRun::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<TextRun> inlineTextRun = std::make_shared<TextRun>();

    if (json.isString())
    {
        inlineTextRun->SetText(json.asString());
    }
    else
    {
        ParseUtil::ExpectTypeString(json, InlineElementTypeToString(InlineElementType::TextRun));
        inlineTextRun->m_textElementProperties->Deserialize(context, json);

        inlineTextRun->SetHighlight(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Highlight, false));
        inlineTextRun->SetUnderline(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Underline, false));
        inlineTextRun->SetSelectAction(ParseUtil::GetAction(context, json, AdaptiveCardSchemaKey::SelectAction, false));

        HandleUnknownProperties(json, inlineTextRun->m_knownProperties, inlineTextRun->m_additionalProperties);
    }

    return inlineTextRun;
}
