#include <iomanip>
#include <regex>
#include <iostream>
#include "TextBlock.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

TextBlock::TextBlock() :
    BaseCardElement(CardElementType::TextBlock),
    m_textSize(TextSize::Default),
    m_textWeight(TextWeight::Default),
    m_textColor(ForegroundColor::Default),
    m_isSubtle(false),
    m_wrap(false),
    m_hAlignment(HorizontalAlignment::Left),
    m_maxLines(0)
{
}

TextBlock::TextBlock(
    Spacing spacing,
    bool separator,
    std::string text,
    TextSize textSize,
    TextWeight textWeight,
    ForegroundColor textColor,
    bool isSubtle,
    bool wrap,
    int maxLines,
    HorizontalAlignment hAlignment) :
    BaseCardElement(CardElementType::TextBlock, spacing, separator),
    m_text(text),
    m_textSize(textSize),
    m_textWeight(textWeight),
    m_textColor(textColor),
    m_isSubtle(isSubtle),
    m_wrap(wrap),
    m_maxLines(maxLines),
    m_hAlignment(hAlignment)
{
}

std::shared_ptr<TextBlock> TextBlock::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TextBlock);

    std::shared_ptr<TextBlock> textBlock = BaseCardElement::Deserialize<TextBlock>(json);

    textBlock->SetText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text, true));
    textBlock->SetTextSize(ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, TextSize::Default, TextSizeFromString));
    textBlock->SetTextColor(ParseUtil::GetEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, ForegroundColor::Default, ForegroundColorFromString));
    textBlock->SetTextWeight(ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeight::Default, TextWeightFromString));
    textBlock->SetWrap(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Wrap, false));
    textBlock->SetIsSubtle(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsSubtle, false));
    textBlock->SetMaxLines(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLines, 0));
    textBlock->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));

    return textBlock;
}

std::shared_ptr<TextBlock> TextBlock::DeserializeFromString(const std::string& jsonString)
{
    return TextBlock::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string TextBlock::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value TextBlock::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size)] = TextSizeToString(GetTextSize());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color)] = ForegroundColorToString(GetTextColor());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Weight)] = TextWeightToString(GetTextWeight());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] = 
        HorizontalAlignmentToString(GetHorizontalAlignment());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines)] = GetMaxLines();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle)] = GetIsSubtle();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)] = GetWrap();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text)] = GetText();

    return root;
}

std::string TextBlock::GetText() const
{
    return ParseISO8601UsingRegex();
}

void TextBlock::SetText(const std::string value)
{
    m_text = value;
}

TextSize TextBlock::GetTextSize() const
{
    return m_textSize;
}

void TextBlock::SetTextSize(const TextSize value)
{
    m_textSize = value;
}

TextWeight TextBlock::GetTextWeight() const
{
    return m_textWeight;
}

void TextBlock::SetTextWeight(const TextWeight value)
{
    m_textWeight = value;
}

ForegroundColor TextBlock::GetTextColor() const
{
    return m_textColor;
}

void TextBlock::SetTextColor(const ForegroundColor value)
{
    m_textColor = value;
}

bool TextBlock::GetWrap() const
{
    return m_wrap;
}

void TextBlock::SetWrap(const bool value)
{
    m_wrap = value;
}

bool TextBlock::GetIsSubtle() const
{
    return m_isSubtle;
}

void TextBlock::SetIsSubtle(const bool value)
{
    m_isSubtle = value;
}

unsigned int TextBlock::GetMaxLines() const
{
    return m_maxLines;
}

void TextBlock::SetMaxLines(const unsigned int value)
{
    m_maxLines = value;
}


HorizontalAlignment TextBlock::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void TextBlock::SetHorizontalAlignment(const HorizontalAlignment value)
{
    m_hAlignment = value;
}

std::string TextBlock::ParseISO8601UsingRegex() const
{
	std::regex pattern("\\{\\{(DATE|TIME)\\((\\d{4})-{1}(\\d{2})-{1}(\\d{2})T(\\d{2}):{1}(\\d{2}):{1}(\\d{2})(Z|([+-])(\\d{2}):{1}(\\d{2}))(\\)|, S[Hh][Oo][Rr][Tt]\\)|, L[Oo][Nn][Gg]\\))\\}\\}");
    std::smatch matches;
    std::string text = m_text;
    std::ostringstream parsedostr;
    time_t offset = 0; 
    bool isDate = false, isShort = true;
    int factor = 1, hr = 0, mn = 0;
    struct tm parsedTm = { 0 };
    int *addrs[]  = { 0, 0, &parsedTm.tm_year, &parsedTm.tm_mon, 
        &parsedTm.tm_mday, &parsedTm.tm_hour, &parsedTm.tm_min, 
        &parsedTm.tm_sec}; 
    enum MatchIndex
    {
        IsDate = 1,
        YEAR,
        Month,
        Day,
        Hour,
        Min,
        Sec,
        TimeZone,
		TZHr = 10,
		TZMn,
        Format,
    };

    while(std::regex_search (text, matches, pattern))
    {
		parsedostr << matches.prefix().str();

        if(matches[IsDate].matched)
        {
            isDate = (matches[IsDate].str()[0] == 'D')? true : false;
        }
        for(int idx = YEAR; idx < TimeZone; idx++)
        { 
            if(matches[idx].matched)
            {
                *addrs[idx] = stoi(matches[idx]);
            }
        }

        if(matches[TimeZone].matched)
        {
			char zone = matches[TimeZone].str()[0];
            if(zone == 'Z')
            {
                factor = 0;
            }
            else if(zone == '+')
            {
                factor = -1;
            }
        }

        parsedTm.tm_year -= 1900;
        parsedTm.tm_mon  -= 1;

		if(matches[TZHr].matched)
			hr = stoi(matches[TZHr]);
		if(matches[TZMn].matched)
			mn = stoi(matches[TZMn]);

        hr *= 3600;
        mn *= 60;
        offset = (hr + mn) * factor;

        time_t utc;
        // converts to ticks
        utc = mktime(&parsedTm);
        if(utc == -1)
        {
            parsedostr << matches[0];
        }

        char tzOffsetBuff[6] = { 0 };
        // gets local time zone offset
        strftime(tzOffsetBuff, 6, "%z", &parsedTm);
        std::string localTimeZoneOffsetStr(tzOffsetBuff);
        int nTzOffset = std::stoi(localTimeZoneOffsetStr);
        offset += ((nTzOffset / 100) * 3600 + (nTzOffset % 100) * 60);
        // add offset to utc
        utc += offset;
		struct tm result = {0};
        // converts to local time from utc
        if(matches[Format].matched)
        {
		   char format = matches[Format].str()[0];
           isShort = (format != ')' && matches[Format].str()[2] == 'L')? false : true;
        }
        if(!localtime_s(&result, &utc))
        {
            // localtime_s double counts daylight saving time
            if(result.tm_isdst == 1)
                result.tm_hour -= 1;

            if(isDate)
            {
                if(isShort)
                {
                    parsedostr << std::put_time(&result, "%x");
                }
                else
                {
                    parsedostr << std::put_time(&result, "%A, %B %e, %Y");
                }
            }
            else
            {
                parsedostr << std::put_time(&result, "%I:%M:%S %p");
            }
        }
		text = matches.suffix().str();
        parsedTm = {0};
        factor = 1;
        hr = mn = 0;
        isDate = false;
        isShort = true;
    }

    parsedostr << text;

	return parsedostr.str();
}
