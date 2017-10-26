#include "TextBlock.h"
#include "ParseUtil.h"
#include <time.h>

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
std::vector<std::string> TextBlock::localizeDate(std::string::const_iterator begin, std::string::const_iterator end)
{
	std::vector<std::string> tempValueHolders(4);
    unsigned int idxMap[] ={4, 2, 2}; 
    unsigned int idx = 0;
	const std::vector<std::string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	const std::vector<std::string> months = {"January", "Feburary", "March", "April", "May", "June", "July", "August", 
											 "September", "October", "November", "December"};
    while(begin != end && *begin != 'T')
    { 
        if(isdigit(*begin) && idx < 4)
        {
            tempValueHolders[idx] += *begin;

            if(--idxMap[idx] == 0)
            {
                idx++;
            }
        }
        begin++;
    }

	struct tm parsedTm = { 0 }, localTm = { 0 };

	parsedTm.tm_year = std::stoi(tempValueHolders[0]) - 1900;
	parsedTm.tm_mon  = std::stoi(tempValueHolders[1]) - 1;
	parsedTm.tm_mday = std::stoi(tempValueHolders[2]) - 1;
	time_t convertedTime = mktime(&parsedTm);
	if (convertedTime != -1)
	{
        std::vector<std::string> outputs;
        localtime_s(&localTm, &convertedTime);
        std::ostringstream strstream, longstream;
        strstream << localTm.tm_mon + 1 << "/" << localTm.tm_mday + 1 << "/" << localTm.tm_year + 1900;
        output.push_back(strstream.str()); 
        longstream << days[localTm.tm_mday] <<", " << months[localTm.tm_mon] << 
	}
    return "";
}
