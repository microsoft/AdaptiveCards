#include "pch.h"
#include "Util.h"
#include "ColumnSet.h"
#include "Container.h"
#include "TextBlock.h"

void PropagateLanguage(const std::string& language, std::vector<std::shared_ptr<BaseCardElement>>& m_body)
{
    for (auto& bodyElement : m_body)
    {
        const CardElementType elementType = bodyElement->GetElementType();

        if (elementType == CardElementType::ColumnSet)
        {
            auto columnSet = std::static_pointer_cast<ColumnSet>(bodyElement);
            if (columnSet != nullptr)
            {
                columnSet->SetLanguage(language);
            }
        }
        else if (elementType == CardElementType::Container)
        {
            auto container = std::static_pointer_cast<Container>(bodyElement);
            if (container != nullptr)
            {
                container->SetLanguage(language);
            }
        }
        else if (bodyElement->GetElementType() == CardElementType::TextBlock)
        {
            auto textBlock = std::static_pointer_cast<TextBlock>(bodyElement);
            if (textBlock != nullptr)
            {
                textBlock->SetLanguage(language);
            }
        }
    }
}

std::string ValidateColor(const std::string& backgroundColor,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings)
{
    if (backgroundColor.empty())
    {
        return backgroundColor;
    }

    const size_t backgroundColorLength = backgroundColor.length();
    bool isValidColor = ((backgroundColor.at(0) == '#') && (backgroundColorLength == 7 || backgroundColorLength == 9));
    for (size_t i = 1; i < backgroundColorLength && isValidColor; ++i)
    {
        isValidColor = isxdigit(backgroundColor.at(i));
    }

    if (!isValidColor)
    {
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                AdaptiveSharedNamespace::WarningStatusCode::InvalidColorFormat,
                "Image background color specified, but doesn't follow #AARRGGBB or #RRGGBB format"));
        return "#00000000";
    }

    std::string validBackgroundColor;
    // If format given was #RRGGBB
    if (backgroundColorLength == 7)
    {
        validBackgroundColor = "#FF" + backgroundColor.substr(1, 6);
    }
    else
    {
        validBackgroundColor = backgroundColor;
    }

    return validBackgroundColor;
}

void ValidateUserInputForDimensionWithUnit(const std::string &unit, const std::string &requestedDimension,
    int &parsedDimension, std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings)
{
    const std::string warningMessage = "expected input arugment to be specified as \\d+(\\.\\d+)?px with no spaces, but received ";
    int parsedVal = 0;
    parsedDimension = 0;
    if (requestedDimension.empty()) 
    { 
        return;
    }

    const char ch = requestedDimension.at(0);
    if (isspace(ch))
    { 
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                warningMessage + requestedDimension)); 
        return;
    }

    if (requestedDimension.length() <= unit.length()) 
    {
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                warningMessage + requestedDimension)); 
        return;
    }

    // verify unit
    const size_t pos = requestedDimension.length() - unit.length();
    int bresult = requestedDimension.compare(pos, unit.length(), unit);
    if (bresult != 0)
    {
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                warningMessage + requestedDimension)); 
        return;
    }

    try
    {
        size_t idx;
        // stoi will get integral value upto non digit char indexed by idx
        parsedVal = std::stoi(requestedDimension, &idx);
        if (parsedVal < 0)
        {
            warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                    AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                    warningMessage + requestedDimension)); 
            parsedVal = 0;
        }

        const size_t startIndexOfUnit = requestedDimension.length() - unit.size();
        // if it's decimal point, there should be at least one digit and digits only between decimal point and unit
        if (unit.length() && requestedDimension.at(idx) == '.' && isdigit(requestedDimension.at(idx + 1)))
        {
            // advance idx up to first non digit char
            while (idx < startIndexOfUnit && isdigit(requestedDimension.at(++idx)));
        }
        // non digit char pointed by idx should be the start index of unit
        if (idx != startIndexOfUnit)
        {
            warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                    AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                    warningMessage + requestedDimension)); 
            parsedVal = 0;
        }
        parsedDimension = parsedVal;
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                warningMessage + requestedDimension)); 
    }
    catch (const std::out_of_range &e)
    {
        (void)e;
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                "out of range: " + requestedDimension));
    }
}

bool ShouldParseForExplicitDimension(const std::string &input)
{
    if (input.empty())
    {
        return false;
    }

    char ch = input.at(0);

    if ('-' == ch || '.' == ch)
    {
        return true;
    }

    size_t index = 0;
    int hasDigit = 0;
    while (index < input.length())
    {
        ch = input.at(index++);
        hasDigit |= isdigit(ch); 
        if (hasDigit && (isalpha(ch) || '.' == ch))
        {
            return true;
        }
    }
    return false;
}
