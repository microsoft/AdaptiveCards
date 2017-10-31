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
    return m_text;
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

std::string TextBlock::scanForDateAndTime(const std::string text)
{
	std::string::const_iterator begin, end = text.end();

    for(auto itr = text.begin(); itr != text.end(); itr++)
    {
		if (*itr == '{')
		{
			itr++;
			if (itr != text.end() && *itr++ == '{')
			{
				if (itr != text.end() && (*itr == 'D' || *itr == 'T'))
				{
					begin = itr;
					while (itr != text.end() && *itr != ')')
					{
						itr++;
					}

					if (itr != text.end())
					{
						return text.substr(begin - text.begin(), itr - begin + 1);
					}
					else
					{
						return "";
					}
				}
			}
		}
	}

	return "";
}

bool TextBlock::scanForISO8601(std::string::const_iterator &itr, 
        std::string::const_iterator &end, bool &isDate, std::ostringstream &ostr)
{
    enum  ParsingState
    {
        NoneParsed = 0x1,
        PassedBracketTest = 0x4,
        DateAndTimeDetected = 0x8,
        FinalCheck = 0x10,
        DoneCheck = 0x20,
    };
    const int cnts = 3;
    int idx = 0, gateKeeper = NoneParsed;
    const char* patterns[] = {"IME", "ATE"}; 
    for(; itr != end && gateKeeper != DoneCheck; itr++)
    {
        ostr << *itr;
		if (*itr == '{')
		{
            gateKeeper <<= 1;
            continue;
        }

        if(gateKeeper & PassedBracketTest && (*itr == 'D' || *itr == 'T'))
        {
            if(*itr == 'D')
            {
                isDate = true;
            }
            gateKeeper <<= 1;
            continue;
        }

        if(gateKeeper & DateAndTimeDetected) 
        {
            if(idx < cnts && patterns[(int) isDate][idx++] == toupper(*itr))
            {
                if(idx == cnts)
                {
					gateKeeper = FinalCheck;
                }
                continue;
            }
        }

        if((gateKeeper & FinalCheck) && *itr == '(')
        {
            gateKeeper = DoneCheck;
            continue;
        }

        gateKeeper = NoneParsed;
        isDate = false;
        idx = 0;
	}

    return gateKeeper == DoneCheck;
}

bool TextBlock::ISO8601ToTm(std::string::const_iterator &begin, 
        std::string::const_iterator &end, struct tm* result, std::ostringstream &ostr)
{
	std::vector<std::string> tempValueHolders(8);
	unsigned int idxMap[] = { 4, 2, 2, 2, 2, 2, 2, 2 };
	unsigned int idx = 0;
	int factor = 1, hr = 0, mn = 0;
	time_t offset = 0; 
	struct tm parsedTm = { 0 };
    int *addrs[]  = { &parsedTm.tm_year, &parsedTm.tm_mon, 
        &parsedTm.tm_mday, &parsedTm.tm_hour, &parsedTm.tm_min, 
        &parsedTm.tm_sec, &hr, &mn}; 

	while (begin != end && idx < tempValueHolders.size())
	{
        ostr << *begin;

		if (isdigit(*begin))
		{
			tempValueHolders[idx] += *begin;

			if (--idxMap[idx] == 0)
			{
                *addrs[idx] = stoi(tempValueHolders[idx]);
				++idx;
			}
		}

		if (*begin == 'Z')
		{
			factor = 0;
		}

		if (*begin == '+')
		{
			factor = -1;
		}

		if (*begin == ',' || *begin == ')')
		{
            begin++;
            break;
		}

		begin++;
	}

	parsedTm.tm_year -= 1900;
	parsedTm.tm_mon  -= 1;
    hr *= 3600;
    mn *= 60;
    offset = (hr + mn) * factor;

	time_t utc;
    // converts to ticks
	utc = mktime(&parsedTm);
    if(utc == -1)
    {
        return false;
    }

	char tzOffsetBuff[6] = { 0 };
    // gets local time zone offset
	strftime(tzOffsetBuff, 6, "%z", &parsedTm);
	std::string localTimeZoneOffsetStr(tzOffsetBuff);
	int nTzOffset = std::stoi(localTimeZoneOffsetStr);
	offset += ((nTzOffset / 100) * 3600 + (nTzOffset % 100) * 60);
    // add offset to utc
	utc += offset;
    // converts to local time from utc
	if(!localtime_s(result, &utc))
	{
        // localtime_s double counts daylight saving time
		if(result->tm_isdst == 1)
			result->tm_hour -= 1;
		return true;
	}

    return false;
}

bool TextBlock::completeParsing(std::string::const_iterator &begin, 
        std::string::const_iterator &end, bool &isShort, std::ostringstream &ostr) 
{
    enum  ParsingState
    {
        NoneParsed = 0x1,
        ShortAndLongDetected = 0x2,
        ParenthesisCheck = 0x4,
        FirstBracketCheck = 0x8,
        SecondBracketCheck = 0x10,
        DoneCheck = 0x20,
        FailedCheck = 0x40,
    };

    unsigned int idx = 0; 
    int gateKeeper = NoneParsed;
    const std::vector<std::string> patterns = {"ONG", "HORT"}; 

    for(; begin != end && !(gateKeeper & (DoneCheck | FailedCheck)); begin++)
    {
        ostr << *begin;

        if(gateKeeper & NoneParsed) 
        {
            if(toupper(*begin) == 'S' || toupper(*begin) =='L')
            {
                isShort = (toupper(*begin) == 'S')? true : false;
                gateKeeper <<= 1;
                continue;

            }

            if(*begin == '}')
            {
                gateKeeper = SecondBracketCheck;
                continue;
            }

            if(isspace(*begin))
            {
                continue;
            }
        }

        if(gateKeeper & ShortAndLongDetected) 
        {
            if(idx < patterns[(int) isShort].size() && patterns[(int) isShort][idx] == toupper(*begin))
            {
                if(++idx == patterns[(int) isShort].size())
                {
					gateKeeper <<= 1;
                }
                continue;
            }
        }

        if((gateKeeper & ParenthesisCheck) && *begin == ')')
        {
            gateKeeper <<= 1;
            continue;
        }

        if((gateKeeper & (FirstBracketCheck | SecondBracketCheck)) && (*begin == '}'))
        {
			if (gateKeeper & SecondBracketCheck)
			{
				gateKeeper = DoneCheck;
			}
            else
            {
                gateKeeper <<= 1;
                continue;
            }
        }
	}

    return gateKeeper == DoneCheck;
}

std::string TextBlock::parseISO8601(std::string::const_iterator &begin, std::string::const_iterator &end)
{
    bool isDate = false, isShort = true;
    std::string newText;
    static char tzOffsetBuff[50];
    enum TransformState
    { 
        NoneParsed = 0x1,
        ISO8601Detected = 0x2,
        ISO8601Parsed = 0x4,
    };

    int state = NoneParsed;
	struct tm result = {0};
    std::ostringstream ostr, parsedostr;

    while(begin != end)
    {
        if(state == NoneParsed && scanForISO8601(begin, end, isDate, ostr))
        { 
            state = ISO8601Detected;
            continue;
        }

        if(state == ISO8601Detected && ISO8601ToTm(begin, end, &result, ostr))
        {
            state = ISO8601Parsed;
            continue;
        }

        if(state == ISO8601Parsed && completeParsing(begin, end, isShort, ostr))
        {
            if(isDate)
            {
                if(isShort)
                {
                    strftime(tzOffsetBuff, 50, "%m/%d/%Y", &result);
                }
                else
                {
                    strftime(tzOffsetBuff, 50, "%A, %B %e, %Y", &result);
                }
            }
            else
            {
                strftime(tzOffsetBuff, 50, "%I:%M %p", &result);
            }

            ostr.str("");
            ostr.clear();
            ostr << std::string(tzOffsetBuff);
			result = {0};
        }

        state = NoneParsed;
        parsedostr << ostr.str();
        ostr.str("");
        ostr.clear();
    }

	return parsedostr.str();
}
