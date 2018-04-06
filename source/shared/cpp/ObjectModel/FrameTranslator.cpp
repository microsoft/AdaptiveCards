#include "pch.h"
#include "FrameTranslator.h"
#include "Enums.h"
#include "ParseUtil.h"
#include "SharedAdaptiveCard.h"
#include "ActionSet.h"
#include "ChoiceSetInput.h"
#include "Column.h"
#include "ColumnSet.h"
#include "Container.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "TextBlock.h"

using namespace AdaptiveCards;

bool ShouldJsonObjectBePruned(Json::Value value);

Json::Value GetValue(
    std::string key,
    const Json::Value& sourceValue)
{
    std::string dot(".");
    size_t dotPosition = key.find(dot, 0);

    std::string openBrace("[");
    size_t openBracePosition = key.find(openBrace, 0);

    if (dotPosition == std::string::npos &&
        openBracePosition == std::string::npos)
    {
        return sourceValue[key];
    }
    else if (dotPosition < openBracePosition)
    {
        std::string subKey = key.substr(0, dotPosition);
        return GetValue(key.substr(dotPosition + 1, key.length()), sourceValue[subKey]);
    }
    else
    {
        std::string subKey = key.substr(0, openBracePosition);
        Json::Value arrayValue = sourceValue[key];
        if (arrayValue.isArray())
        {
            std::string closeBrace("]");
            size_t closeBracePosition = key.find(closeBrace, 0);
            std::string index = key.substr(openBracePosition + 1, closeBracePosition - openBracePosition - 1);

            try
            {
                auto indexAsUnsignedLong = std::stoul(index);
//                return arrayValue[indexAsUnsignedLong];

            }
            catch (...)
            {
                return Json::Value();
            }

        }
    }
    return Json::Value();
}

Json::Value DataBindFrameStringFromSource(
    const Json::Value& sourceCard,
    const Json::Value& frame)
{
    std::string bracesStart("{{");
    std::string bracesEnd("}}");

    std::string frameString = frame.asString();

    size_t bracesStartPosition = frameString.find(bracesStart, 0);
    size_t bracesEndPosition = frameString.find(bracesEnd, 0);

    if (bracesStartPosition == 0 &&
        bracesEndPosition == frameString.length() - bracesEnd.length())
    {
        // If the entire string is a data binding element, return the result of GetValue, which may be of any type
        std::string key = frameString.substr(bracesStartPosition + bracesStart.length(), bracesEndPosition - bracesStartPosition - bracesStart.length());
        return GetValue(key, sourceCard);
    }
    else if (bracesStartPosition != std::string::npos &&
             bracesEndPosition != std::string::npos)
    {
        // If we have a data binding element, but it's not the entire string, do substring binding
        std::string resultString;
        size_t currentFrameStartPosition = 0;

        while (bracesStartPosition != std::string::npos && 
               bracesEndPosition != std::string::npos)
        {
            // Append the portion before the data binding element
            resultString += frameString.substr(currentFrameStartPosition, bracesStartPosition - currentFrameStartPosition);

            // Get the value of the data binding element
            std::string key = frameString.substr(bracesStartPosition + bracesStart.length(), bracesEndPosition - bracesStartPosition - bracesStart.length());
            Json::Value result = GetValue(key, sourceCard);

            // This only works if everything binds to a string. If we find one that doesn't, 
            // give up and return the frame as is. Otherwise, append the value to the result
            // string.
            if (!result.isString())
            {
                return frame;
            }
            resultString += result.asString();

            // Advance the start position on the frame string, and find the next data binding element
            currentFrameStartPosition = bracesEndPosition + bracesEnd.length();
            bracesStartPosition = frameString.find(bracesStart, currentFrameStartPosition);
            bracesEndPosition = frameString.find(bracesEnd, currentFrameStartPosition);
        }

        // Append the portion of the frame string that is after the last data binding element and 
        // return the result string as a json value.
        resultString += frameString.substr(currentFrameStartPosition, frameString.length() - currentFrameStartPosition);
        return Json::Value(resultString);
    }
    else
    {
        // No data binding, return the frame as is.
        return frame;
    }
}

Json::Value DataBindJson(
    const Json::Value& sourceCard,
    const Json::Value& frame)
{
    Json::FastWriter fastWriter;
    std::string sourceString = fastWriter.write(sourceCard);
    std::string frameString = fastWriter.write(frame);

    Json::Value result;
    if (frame.isString())
    {
        // If it's a string, see if it needs to be data bound
        result = DataBindFrameStringFromSource(sourceCard, frame);
    }
    else if (frame.isArray() || frame.isObject())
    {
        // If it's an object or array, walk the sub elements
        for (Json::Value::const_iterator it = frame.begin(); it != frame.end(); it++)
        {
            Json::Value elementResult = DataBindJson(sourceCard, *it);

            if (elementResult.empty())
            {
                // If the result is empty, don't add it to the json
                continue;
            }
            else if (frame.isArray())
            {
                result.append(elementResult);
            }
            else if (frame.isObject())
            {
                std::string key = it.key().asCString();
                result[key] = elementResult;
            }
        }

        // Check if the object should be pruned. If so, return an empty result
        if (frame.isObject() && ShouldJsonObjectBePruned(result))
        {
            result = Json::Value();
        }
    }
    else
    {
        // All other types return as is
        result = frame;
    }

    std::string resultString = fastWriter.write(result);
    return result;
}

Json::Value ApplyFrame(
    const Json::Value& sourceCard,
    const Json::Value& frame)
{
    Json::Value result = DataBindJson(sourceCard, frame);

    Json::Value data = sourceCard["data"];
    return DataBindJson(data, result);
}

bool ShouldJsonObjectBePruned(Json::Value value)
{
    if (!value.isMember("type"))
    {
        return false;
    }

    auto elementType = CardElementTypeFromString(ParseUtil::GetTypeAsString(value));
    if (elementType != CardElementType::Unsupported)
    {
        // BECKYTODO - un-hardcode the strings and confirm these properties are right for pruning (spec issue)
        switch (elementType)
        {
            case CardElementType::ActionSet:
                return value["actions"].empty();

            case CardElementType::ChoiceSetInput:
                return value["choices"].empty();

            case CardElementType::Column:
            case CardElementType::Container:
                return value["items"].empty();

            case CardElementType::ColumnSet:
                return value["columns"].empty();

            case CardElementType::FactSet:
                return value["facts"].empty();

            case CardElementType::ImageSet:
                return value["images"].empty();

            case CardElementType::Image:
                return value["url"].empty();

            case CardElementType::TextBlock:
                return value["text"].empty();

            case CardElementType::ChoiceInput:
                return value["title"].empty();

            case CardElementType::Fact:
                return (value["title"].empty() || value["value"].empty());

            case CardElementType::DateInput:
            case CardElementType::NumberInput:
            case CardElementType::TextInput:
            case CardElementType::TimeInput:
            case CardElementType::ToggleInput:
            case CardElementType::Custom:
            case CardElementType::Unknown:
            default:
                return false;
        }
    }
    else if (ActionTypeFromString(ParseUtil::GetTypeAsString(value)) != ActionType::Unsupported)
    {
        return value["title"].empty();
    }
    else
    {
        return false;
    }
}