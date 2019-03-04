#include "pch.h"
#include "TextRun.h"

using namespace AdaptiveSharedNamespace;

TextRun::TextRun() : Inline(InlineElementType::TextRun), m_textElementProperties(std::make_shared<TextElementProperties>())
{
    PopulateKnownPropertiesSet();
}

void TextRun::PopulateKnownPropertiesSet()
{
    m_textElementProperties->PopulateKnownPropertiesSet(m_knownProperties);
}

Json::Value TextRun::SerializeToJsonValue() const
{
    Json::Value root = Json::Value();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = GetInlineTypeString();
    m_textElementProperties->SerializeToJsonValue(root);

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

FontStyle TextRun::GetFontStyle() const
{
    return m_textElementProperties->GetFontStyle();
}

void TextRun::SetFontStyle(const FontStyle value)
{
    m_textElementProperties->SetFontStyle(value);
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

std::string TextRun::GetLanguage() const
{
    return m_textElementProperties->GetLanguage();
}

void TextRun::SetLanguage(const std::string& value)
{
    m_textElementProperties->SetLanguage(value);
}
std::shared_ptr<Inline> TextRun::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<TextRun> inlineTextRun = std::make_shared<TextRun>();

    ParseUtil::ExpectTypeString(json, InlineElementTypeToString(InlineElementType::TextRun));
    inlineTextRun->m_textElementProperties->Deserialize(context, json);

    HandleUnknownProperties(json, inlineTextRun->m_knownProperties, inlineTextRun->m_additionalProperties);

    return inlineTextRun;
}
