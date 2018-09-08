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
                "expected input arugment to be specified as \\d+(.\\d+)?px with no spaces, but received " + requestedDimension)); 
        return;
    }

    if (requestedDimension.length() >= unit.length()) 
    {
        unsigned int cnts = 1;
        for (cnts; cnts <= unit.length(); cnts++)
        { 
            unsigned int offset = cnts;
            if (*(requestedDimension.end() - offset) != *(unit.end() - offset))
            {
                warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                        AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                        "expected input arugment to be specified as \\d+(.\\d+)?px with no spaces, but received " + requestedDimension)); 
                return;
            }
        }
    }

    try
    {
        size_t nonDigitIndex;
        parsedVal = std::stoi(requestedDimension, &nonDigitIndex);
        if (parsedVal < 0)
        {
            warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                    AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                    "expected input arugment to be specified as \\d+(.\\d+)?px with no spaces, but received " + requestedDimension)); 
            parsedVal = 0;
        }

        const size_t firstNonDigitIndex = requestedDimension.length() - unit.size();
        const size_t lastDigitIndex = firstNonDigitIndex - 1;
        bool bPass = true;
        // it's assumed that unit is included in the string
        if (nonDigitIndex != firstNonDigitIndex)
        { 
            // check if it's decimal point
            if (requestedDimension.at(nonDigitIndex) == '.')
            {
                // check it contains only digits after decimal point
                size_t numberIndex = nonDigitIndex + 1;
                while (numberIndex < firstNonDigitIndex && isdigit(requestedDimension.at(numberIndex)))
                {
                    numberIndex++;
                }
                if(numberIndex != firstNonDigitIndex)
                {
                    bPass = false;
                }
            } 
            else
            {
                bPass = false;
            }
        }

        if (!bPass)
        {
            warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                    AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                    "expected input arugment to be specified as \\d+(.\\d+)?px with no spaces, but received " + requestedDimension)); 
            parsedVal = 0;
        }
        parsedDimension = parsedVal;
    }
    catch (const std::invalid_argument &e)
    {
        (void)e;
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
                AdaptiveSharedNamespace::WarningStatusCode::InvalidDimensionSpecified,
                    "expected input arugment to be specified as \\d+(.\\d+)?px with no spaces, but received " + requestedDimension)); 
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
