#pragma once
#include <string>
#include <vector>

namespace AdaptiveCards
{
    enum class TextSectionFormat : uint16_t
    {
        RegularString = 0,
        Time,
        DateCompact,
        DateShort,
        DateLong
    };

    class TextSection
    {
    public:
        TextSection(); 
        TextSection(std::string text, TextSectionFormat format);

        std::string GetText() const;
        TextSectionFormat GetFormat() const;
        int GetDay() const;
        int GetMonth() const;
        int GetYear() const;
        int GetSecond() const;
        int GetMinute() const;
        int GetHour() const;

    private:
        std::vector<std::string> Split(const std::string& in, char delimiter) const;

        std::string m_text;
        TextSectionFormat m_format;
    };
    
    class TextBlockText
    {
    public:
        TextBlockText();
        std::vector<TextSection> GetString() const;
        void AddTextSection(std::string text, TextSectionFormat format);
        std::string Concatenate();

    private:
        std::vector<TextSection> m_fullString;
    };


}