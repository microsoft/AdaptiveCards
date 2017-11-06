#if defined(__ANDROID__) || (__APPLE__)
#define LOCALTIME(X,Y) (nullptr == localtime_r(Y, X))
#else
#define LOCALTIME(X,Y) localtime_s(X,Y)
#endif

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
    return ParseISO8601();
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

std::string TextBlock::ParseISO8601() const
{
    std::regex pattern("\\{\\{(DATE|Date|TIME|Time)\\((\\d{4})-{1}(\\d{2})-{1}(\\d{2})T(\\d{2}):{1}(\\d{2}):{1}(\\d{2})(Z|([+-])(\\d{2}):{1}(\\d{2}))(\\)|,Short\\)|,SHORT\\)|,Long\\)|,LONG\\))\\}\\}");
    std::smatch matches;
    std::string text = m_text;
    std::ostringstream parsedostr;
    time_t offset = 0;
    bool isDate = false, isShort = true;
    enum MatchIndex
    {
        IsDate = 1,
        Year,
        Month,
        Day,
        Hour,
        Min,
        Sec,
        TimeZone,
        TimeZoneOffsetHours = 10,
        TimeZoneOffsetMinutes,
        Format,
    };
    int hours = 0, minutes = 0;
    struct tm parsedTm = { 0 };
    int *addrs[] = {&parsedTm.tm_year, &parsedTm.tm_mon,
        &parsedTm.tm_mday, &parsedTm.tm_hour, &parsedTm.tm_min,
        &parsedTm.tm_sec, &hours, &minutes};
    std::vector<int> indexer = {Year, Month, Day, Hour, Min, Sec, TimeZoneOffsetHours , TimeZoneOffsetMinutes};

    while (std::regex_search(text, matches, pattern))
    {
        parsedostr << matches.prefix().str();

        if (matches[IsDate].matched)
        {
            // Date is matched
            isDate = (matches[IsDate].str()[0] == 'D');
        }

        for (unsigned int idx = 0; idx < indexer.size(); idx++)
        {
            if (matches[indexer[idx]].matched)
            {
                // get indexes for time attributes to index into conrresponding matches
                // and covert it to string
                *addrs[idx] = stoi(matches[indexer[idx]]);
            }
        }

        // measured from year 1900
        parsedTm.tm_year -= 1900;
        parsedTm.tm_mon  -= 1;

        // converts to seconds
        hours *= 3600;
        minutes *= 60;

        // maches offset sign,
        // Z == UTC,
        // + == time added from UTC
        // - == time subtracted from UTC
        if (matches[TimeZone].matched)
        {

            char zone = matches[TimeZone].str()[0];
            if (zone == '-')
            {
                offset = (hours + minutes);
            }
            else if (zone == '+')
            {
                // time zone offset calculation
                offset = (hours + minutes) * (-1);
            }
        }

        time_t utc;
        // converts to ticks in UTC
        utc = mktime(&parsedTm);
        if (utc == -1)
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

        // match for long/short
        if (matches[Format].matched)
        {
           char format = matches[Format].str()[0];
           isShort = (format == ')' || matches[Format].str()[1] == 'S');
        }

        // converts to local time from utc
        if (!LOCALTIME(&result, &utc))
        {
            // localtime_s double counts daylight saving time
            if (result.tm_isdst == 1)
                result.tm_hour -= 1;

            if (isDate)
            {
                if (isShort)
                {
                    parsedostr << std::put_time(&result, "%Ex");
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
        offset = 0;
        hours = minutes = 0;
        isDate = false;
        isShort = true;
    }

    parsedostr << text;

    return parsedostr.str();
}
