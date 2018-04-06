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
Json::Value DataBindJson(const Json::Value& sourceCard, const Json::Value& frame);

// Find a key between start and end markers. For example pull out the foo in:
// "This is some text with a {{foo}} in it." 
// Takes strings for the type of braces ({{}} or []) and returns the positions 
// of the beginning and end of the braces surrounding the key.
// This function will return the first instance after the passed in startPosition.
std::string GetKey(
    std::string string,
    size_t startPosition,
    const char * openBraces,
    const char * closeBraces, 
    size_t * keyStartPosition,
    size_t * keyEndPosition)
{
    std::string bracesStart(openBraces);
    std::string bracesEnd(closeBraces);

    size_t bracesStartPosition = string.find(bracesStart, startPosition);
    size_t bracesEndPosition = string.find(bracesEnd, startPosition);

    std::string key;
    if (bracesStartPosition != std::string::npos &&
        bracesEndPosition != std::string::npos)
    {
        key = string.substr(bracesStartPosition + bracesStart.length(), bracesEndPosition - bracesStartPosition - bracesStart.length());
        *keyStartPosition = bracesStartPosition;
        *keyEndPosition = bracesEndPosition + bracesEnd.length() - 1;
    }

    return key;
}

// Given a key, return the value from the source json. Handles dot notation "foo.bar", indices 
// "foo[bar]" and combinations thereof "foo.bar[stuff.blah]"
Json::Value GetValue(
    std::string key,
    const Json::Value& sourceValue)
{
    Json::FastWriter fastWriter;
    std::string sourceString = fastWriter.write(sourceValue);

    std::string dot(".");
    size_t dotPosition = key.find(dot, 0);

    std::string openBrace("[");
    size_t openBracePosition = key.find(openBrace, 0);

    // Handle dot notation {{foo.bar.stuff}} by looping through the dots to get the last subkey 
    // and it's corresponding scope
    Json::Value currentSourceScope = sourceValue;
    std::string currentKey = key;
    while ((dotPosition != std::string::npos) && (dotPosition < openBracePosition))
    {
        std::string beforeDotKey = key.substr(0, dotPosition);
        std::string afterDotKey = key.substr(dotPosition + 1, key.length() - dotPosition);
        
        currentSourceScope = sourceValue[beforeDotKey];
        currentKey = afterDotKey;
        dotPosition = afterDotKey.find(dot, 0);
    }

    if (openBracePosition == std::string::npos)
    {
        // If there are no indices[], use the current key as is
        return currentSourceScope[currentKey];
    }
    else
    {
        // Handle indices such as {{foo[5]}} or {{foo[bar]}}
        Json::Value result;

        // Get the index
        size_t closeBracePosition;
        std::string indexString = GetKey(currentKey, 0, "[", "]", &openBracePosition, &closeBracePosition);

        // Get the key for the array name and look it up in the current scope
        std::string arrayKey = currentKey.substr(0, openBracePosition);
        Json::Value arrayValue = currentSourceScope[arrayKey];
        if (arrayValue.isArray())
        {
            try
            {
                // See if the array index is a number {{foo[5]}}
                result = arrayValue[Json::ArrayIndex(std::stoul(indexString))];
            }
            catch (...)
            {
                // Check if it's part of the data {{foo[bar]}}
                Json::Value indexValue = GetValue(indexString, sourceValue);
                if (!indexValue.empty() && indexValue.isIntegral())
                {
                    result = arrayValue[Json::ArrayIndex(indexValue.asUInt())];
                }
            }

            return result;
        }
    }
    return Json::Value();
}

Json::Value DataBindString(
    const Json::Value& sourceCard,
    const Json::Value& frame)
{
    std::string frameString = frame.asString();

    // Look for any data binding keys surrounded in double curly braces
    size_t bracesStartPosition, bracesEndPosition;
    std::string key = GetKey(frameString, 0, "{{", "}}", &bracesStartPosition, &bracesEndPosition);

    if (!key.empty() && 
        bracesStartPosition == 0 &&
        bracesEndPosition == frameString.length() - 1)
    {
        // If the entire string is a data binding element, return the result of GetValue, which may be of any type.
        // If the result is empty, just return the frame as is.
        Json::Value result = GetValue(key, sourceCard);
        return result.empty() ? frame : result;
    }
    else if (!key.empty())
    {
        // If we have a data binding element, but it's not the entire string, do substring binding
        // For example: "This is a string with some {{stuff}} in it"
        std::string resultString;
        size_t currentFrameStartPosition = 0;

        while (!key.empty())
        {
            // Append the portion before the data binding element
            resultString += frameString.substr(currentFrameStartPosition, bracesStartPosition - currentFrameStartPosition);

            // Get the value of the data binding element
            Json::Value result = GetValue(key, sourceCard);

            if (result.empty() || !result.isString())
            {
                // If the result wasn't found or wasn't a string, leave the data binding element in place
                resultString += frameString.substr(bracesStartPosition, bracesEndPosition - bracesStartPosition + 1);
            }
            resultString += result.asString();

            // Advance the start position on the frame string, and find the next data binding element
            currentFrameStartPosition = bracesEndPosition + 1;
            key = GetKey(frameString, currentFrameStartPosition, "{{", "}}", &bracesStartPosition, &bracesEndPosition);
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

Json::Value DataBindArray(
    const Json::Value& sourceCard,
    const Json::Value& frame
)
{
    // Loop through the sub elements of the array and bind each one
    Json::Value result;
    for (Json::Value::const_iterator it = frame.begin(); it != frame.end(); it++)
    {
        Json::Value elementResult = DataBindJson(sourceCard, *it);
        if (elementResult.empty())
        {
            // If the result is empty, don't add it to the json
            continue;
        }
        result.append(elementResult);
    }

    return result;
}

Json::Value DataBindObject(
    const Json::Value& sourceCard,
    const Json::Value& frame)
{
    // Loop through the sub elements of the object and bind each one
    Json::Value result;
    for (Json::Value::const_iterator it = frame.begin(); it != frame.end(); it++)
    {
        Json::Value elementResult = DataBindJson(sourceCard, *it);

        if (elementResult.empty())
        {
            // If the result is empty, don't add it to the json
            continue;
        }
        std::string key = it.key().asCString();
        result[key] = elementResult;
    }

    // Check if the object should be pruned. If so, return an empty result
    if (ShouldJsonObjectBePruned(result))
    {
        result = Json::Value();
    }

    Json::FastWriter fastWriter;
    std::string resultString = fastWriter.write(result);

    return result;
}

Json::Value DataBindJson(
    const Json::Value& sourceCard,
    const Json::Value& frame)
{
    Json::FastWriter fastWriter;
    std::string sourceString = fastWriter.write(sourceCard);
    std::string frameString = fastWriter.write(frame);

    // Handle data binding depending on the type of the json value
    if (frame.isString())
    {
        return DataBindString(sourceCard, frame);
    }
    else if (frame.isObject())
    {
        return DataBindObject(sourceCard, frame);
    }
    else if (frame.isArray())
    {
        return DataBindArray(sourceCard, frame);
    }
    else
    {
        // All other types return as is
        return frame;
    }
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