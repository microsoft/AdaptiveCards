// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "ColumnSet.h"
#include "Container.h"
#include "FactSet.h"
#include "RichTextBlock.h"
#include "ShowCardAction.h"
#include "TextBlock.h"
#include "Util.h"

using namespace AdaptiveCards;

std::string ValidateColor(const std::string& backgroundColor, std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings)
{
    constexpr auto lengthRGB = sizeof("#RRGGBB") - 1;    // -1 for null terminator
    constexpr auto lengthRGBA = sizeof("#RRGGBBAA") - 1; // ^
    if (backgroundColor.empty())
    {
        return backgroundColor;
    }

    const auto backgroundColorLength = backgroundColor.length();
    bool isValidColor = ((backgroundColor.at(0) == '#') && (backgroundColorLength == lengthRGB || backgroundColorLength == lengthRGBA));
    for (size_t i = 1; i < backgroundColorLength && isValidColor; ++i)
    {
        isValidColor = (isxdigit(backgroundColor.at(i)) != 0);
    }

    if (!isValidColor)
    {
        warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidColorFormat,
                                                                         "Image background color specified, but doesn't follow #AARRGGBB or #RRGGBB format"));
        return "#00000000";
    }

    std::string validBackgroundColor;
    // If format given was #RRGGBB
    if (backgroundColorLength == lengthRGB)
    {
        validBackgroundColor = "#FF" + backgroundColor.substr(1, lengthRGB-1); // -1 because we skipped '#'
    }
    else
    {
        validBackgroundColor = backgroundColor;
    }

    return validBackgroundColor;
}

void ValidateUserInputForDimensionWithUnit(const std::string& unit,
                                           const std::string& requestedDimension,
                                           std::optional<int>& parsedDimension,
                                           std::vector<std::shared_ptr<AdaptiveCardParseWarning>>* warnings)
{
    constexpr auto warningMessage = R"(expected input argument to be specified as '\d+(\.\d+)?px' with no spaces, but received )";
    std::string stringPattern = R"(^([1-9]+\d*)(\.\d+)?)";
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
            if (warnings != nullptr)
            {
                warnings->emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidDimensionSpecified,
                                                                                  warningMessage + requestedDimension));
            }
        }
        catch (const std::out_of_range&)
        {
            if (warnings != nullptr)
            {
                warnings->emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidDimensionSpecified,
                                                                                  "out of range: " + requestedDimension));
            }
        }
    }
    else
    {
        if (warnings != nullptr)
        {
            warnings->emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::InvalidDimensionSpecified,
                                                                              warningMessage + requestedDimension));
        }
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
        if (hasDigit != 0 && ((isalpha(ch) != 0) || '.' == ch))
        {
            return true;
        }
    }
    return false;
}

std::optional<int> ParseSizeForPixelSize(const std::string& sizeString, std::vector<std::shared_ptr<AdaptiveCardParseWarning>>* warnings)
{
    std::optional<int> parsedSize{};
    if (ShouldParseForExplicitDimension(sizeString))
    {
        const std::string unit = "px";
        ValidateUserInputForDimensionWithUnit(unit, sizeString, parsedSize, warnings);
    }
    return parsedSize;
}

void EnsureShowCardVersions(const std::vector<std::shared_ptr<BaseActionElement>>& actions, const std::string& version)
{
    for (const auto& action : actions)
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

void HandleUnknownProperties(const Json::Value& json, const std::unordered_set<std::string>& knownProperties, Json::Value& unknownProperties)
{
    for (auto it = json.begin(); it != json.end(); ++it)
    {
        std::string key = it.key().asCString();
        if (knownProperties.find(key) == knownProperties.end())
        {
            unknownProperties[key] = *it;
        }
    }
}
