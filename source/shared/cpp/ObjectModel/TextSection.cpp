#include "TextSection.h"

using namespace AdaptiveCards;

TextSection::TextSection() : m_text(""), m_format(TextSectionFormat::RegularString)
{
}

TextSection::TextSection(std::string text, TextSectionFormat format) : m_text(text), m_format(format)
{
}

TextSection::TextSection(std::string text, std::string originalText, TextSectionFormat format) :
    m_text(text), m_originalText(originalText), m_format(format)
{

}

std::string TextSection::GetText() const
{
    return m_text;
}

std::string TextSection::GetOriginalText() const
{
    return m_originalText;
}

TextSectionFormat TextSection::GetFormat() const
{
    return m_format;
}

int TextSection::GetDay() const
{
    return GetDateSection(1);
}

int TextSection::GetMonth() const
{
    return GetDateSection(0);
}

int TextSection::GetYear() const
{
    return GetDateSection(2);
}

int TextSection::GetSecond() const
{
    return GetTimeSection(2);
}

int TextSection::GetMinute() const
{
    return GetTimeSection(1);
}

int TextSection::GetHour() const
{
    return GetTimeSection(0);
}

int TextSection::GetDateSection(int position) const
{
    int dateValue{};
    if (m_format == TextSectionFormat::DateShort ||
        m_format == TextSectionFormat::DateLong ||
        m_format == TextSectionFormat::DateCompact)
    {
        auto splittedDate = Split(m_text, dateDelimiter);
        if (splittedDate.size() > position)
        {
            dateValue = std::stoi(splittedDate.at(1));
        }
    }
    return dateValue;
}

int TextSection::GetTimeSection(int position) const
{
    int timeValue{};
    if (m_format == TextSectionFormat::Time)
    {
        auto splittedTime = Split(m_text, timeDelimiter);
        if (splittedTime.size() > position)
        {
            timeValue = std::stoi(splittedTime.at(0));
        }
    }
    return timeValue;
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