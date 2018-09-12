#include "pch.h"
#include "Util.h"
#include "ColumnSet.h"
#include "Container.h"
#include "TextBlock.h"
#include "ShowCardAction.h"

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
    int &parsedDimension)
{
    if (requestedDimension.empty())
    {
        parsedDimension = 0;
    }
    else
    {
        const std::size_t foundIndex = requestedDimension.find(unit);
        if (std::string::npos == foundIndex || requestedDimension.size() != foundIndex + unit.size())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                "unit is either missing or inproper form: " + requestedDimension);
        }
        try
        {
            int parsedVal = std::stoi(requestedDimension.substr(0, foundIndex));
            if (parsedVal < 0)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                    "unsigned integer is accepted but received : " + requestedDimension);
            }
            parsedDimension = parsedVal;
        }
        catch (const std::invalid_argument &e)
        {
            (void)e;
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                "unsigned integer is accepted but received : " + requestedDimension);
        }
        catch (const std::out_of_range &e)
        {
            (void)e;
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                "out of range: " + requestedDimension);
        }
    }
}

void EnsureShowCardVersions(
    std::vector<std::shared_ptr<BaseActionElement>>& actions, 
    std::string& version)
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
