#include "TextBlockText.h"

using namespace AdaptiveCards;

TextSection::TextSection() : m_text(""), m_format(TextSectionFormat::RegularString)
{
}

TextSection::TextSection(std::string text, TextSectionFormat format) : m_text(text), m_format(format)
{
}

std::string TextSection::GetText() const
{
    return m_text;
}

TextSectionFormat TextSection::GetFormat() const
{
    return m_format;
}

int TextSection::GetDay() const
{
    int day{};
    if (m_format == TextSectionFormat::DateShort || 
        m_format == TextSectionFormat::DateLong || 
        m_format == TextSectionFormat::DateCompact)
    {
        day = std::stoi(Split(m_text, '/').at(1));
    }
    return day;
}

int TextSection::GetMonth() const
{
    int minute{};
    if (m_format == TextSectionFormat::DateShort ||
        m_format == TextSectionFormat::DateLong ||
        m_format == TextSectionFormat::DateCompact)
    {
        minute = std::stoi(Split(m_text, '/').at(0));
    }
    return minute;
}

int TextSection::GetYear() const
{
    int year{};
    if (m_format == TextSectionFormat::DateShort ||
        m_format == TextSectionFormat::DateLong ||
        m_format == TextSectionFormat::DateCompact)
    {
        year = std::stoi(Split(m_text, '/').at(2));
    }
    return year;
}

int TextSection::GetSecond() const
{
    int second{};
    if (m_format == TextSectionFormat::Time)
    {
        second = std::stoi(Split(m_text, ':').at(2));
    }
    return second;
}

int TextSection::GetMinute() const
{
    int minute{};
    if (m_format == TextSectionFormat::Time)
    {
        minute = std::stoi(Split(m_text, ':').at(1));
    }
    return minute;
}

int TextSection::GetHour() const
{
    int hour{};
    if (m_format == TextSectionFormat::Time)
    {
        hour = std::stoi(Split(m_text, ':').at(0));
    }
    return hour;
}

std::vector<std::string> TextSection::Split(const std::string& in, char delimiter) const
{
    std::vector<std::string> tokens;
    size_t startIndex{};
    size_t endIndex = in.find(delimiter, startIndex);

    while (std::string::npos != endIndex)
    {
        std::string token = in.substr(startIndex, endIndex - startIndex);
        tokens.emplace_back(token);
        startIndex = endIndex + 1;
        endIndex = in.find(delimiter, startIndex);
    }

    tokens.emplace_back(in.substr(startIndex));
    return tokens;
}

TextBlockText::TextBlockText()
{
}

std::vector<TextSection> TextBlockText::GetString() const
{
    return m_fullString;
}

void TextBlockText::AddTextSection(std::string text, TextSectionFormat format)
{
    m_fullString.emplace_back(TextSection(text, format));
}

std::string TextBlockText::Concatenate()
{
    std::string formedString;
    for (const auto& piece : m_fullString)
    {
        formedString += piece.GetText();
    }
    return formedString;
}