#include "pch.h"
#include "Util.h"
#include "ColumnSet.h"
#include "Container.h"
#include "FactSet.h"
#include "TextBlock.h"
#include "ShowCardAction.h"

using namespace AdaptiveSharedNamespace;

void PropagateLanguage(const std::string& language, const std::vector<std::shared_ptr<BaseCardElement>>& m_body)
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
        else if (bodyElement->GetElementType() == CardElementType::FactSet)
        {
            auto factset = std::static_pointer_cast<FactSet>(bodyElement);
            if (factset != nullptr)
            {
                factset->SetLanguage(language);
            }
        }
    }
}

std::string ValidateColor(const std::string& backgroundColor, std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings)
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
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidColorFormat,
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

void ValidateUserInputForDimensionWithUnit(const std::string& unit,
                                           const std::string& requestedDimension,
                                           int& parsedDimension,
                                           std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings)
{
    const std::string warningMessage = "expected input arugment to be specified as \\d+(\\.\\d+)?px with no spaces, but received ";
    parsedDimension = 0;
    std::string stringPattern = "^([1-9]+\\d*)(\\.\\d+)?";
    stringPattern += ("(" + unit + ")$");
    std::regex pattern(stringPattern);
    std::smatch matches;

    if (std::regex_search(requestedDimension, matches, pattern))
    {
        try
        {
            // stoi will get integral value upto non digit char indexed by idx
            parsedDimension = std::stoi(matches[0]);
        }
        catch (const std::invalid_argument&)
        {
            warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidDimensionSpecified,
                                                                             warningMessage + requestedDimension));
        }
        catch (const std::out_of_range&)
        {
            warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidDimensionSpecified,
                                                                             "out of range: " + requestedDimension));
        }
    }
    else
    {
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidDimensionSpecified,
                                                                         warningMessage + requestedDimension));
    }
}

bool ShouldParseForExplicitDimension(const std::string& input)
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

void EnsureShowCardVersions(const std::vector<std::shared_ptr<BaseActionElement>>& actions, const std::string& version)
{
    for (auto& action : actions)
    {
        if (action->GetElementType() == ActionType::ShowCard)
        {
            auto showCardAction = std::static_pointer_cast<ShowCardAction>(action);
            if (showCardAction->GetCard()->GetVersion().empty())
            {
                showCardAction->GetCard()->SetVersion(version);
            }
        }
    }
}
