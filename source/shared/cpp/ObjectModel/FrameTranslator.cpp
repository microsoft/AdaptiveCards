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
// Takes strings for the type of braces ({{}}, [], etc.) and returns the positions of the beginning
// and end of the braces surrounding the key. This function will return the first instance after
// the passed in startPosition.
std::string GetKey(std::string string, size_t startPosition, const char* openBraces, const char* closeBraces, size_t* keyStartPosition, size_t* keyEndPosition)
{
    std::string bracesStart(openBraces);
    std::string bracesEnd(closeBraces);

    size_t bracesStartPosition = string.find(bracesStart, startPosition);
    size_t bracesEndPosition = string.find(bracesEnd, startPosition);

    std::string key;
    if (bracesStartPosition != std::string::npos && bracesEndPosition != std::string::npos)
    {
        key = string.substr(bracesStartPosition + bracesStart.length(),
                            bracesEndPosition - bracesStartPosition - bracesStart.length());
        *keyStartPosition = bracesStartPosition;
        *keyEndPosition = bracesEndPosition + bracesEnd.length() - 1;
    }

    return key;
}

std::string GetArgument(std::string& key, unsigned int startPosition)
{
    size_t argumentStart = key.find_first_not_of(" ", startPosition);
    if (argumentStart != std::string::npos)
    {
        return key.substr(argumentStart, key.length() - argumentStart);
    }
    return std::string();
}

std::string GetDataBindingKey(std::string string, size_t startPosition, size_t* keyStartPosition, size_t* keyEndPosition, bool* includeOnlyIfExists)
{
    std::string key = GetKey(string, startPosition, "{{", "}}", keyStartPosition, keyEndPosition);

    // If the databinding key includes the existential operator ("{{#? stuff}}"), set the boolean indicating it should
    // only be included if it exits, and return just the argument ("stuff") as the key
    *includeOnlyIfExists = false;
    std::string existentialString = "#?";
    if (!key.compare(0, existentialString.length(), existentialString))
    {
        *includeOnlyIfExists = true;
        key = GetArgument(key, existentialString.length());
    }

    return key;
}

// Given a key, return the value from the source json. Handles dot notation "foo.bar", indices
// "foo[bar]" and combinations thereof "foo.bar[stuff.blah]"
Json::Value GetValue(std::string key, const Json::Value& sourceValue)
{
    Json::FastWriter fastWriter;
    std::string sourceString = fastWriter.write(sourceValue);

    std::string dot(".");
    size_t dotPosition = key.find(dot, 0);

    std::string openBrace("[");
    size_t openBracePosition = key.find(openBrace, 0);

    // Handle dot notation {{foo.bar.stuff}} by looping through the dots to get the last subkey
    // and it's corresponding Json::Value scope
    Json::Value currentSourceScope = sourceValue;
    std::string currentKey = key;
    while ((dotPosition != std::string::npos) && (dotPosition < openBracePosition))
    {
        std::string beforeDotKey = currentKey.substr(0, dotPosition);
        std::string afterDotKey = currentKey.substr(dotPosition + 1, currentKey.length() - dotPosition);

        currentSourceScope = currentSourceScope[beforeDotKey];
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

            // Check if we are trying to index something into an array:
            // foo[0].bar for example, the call if the result is an array
            // and we have a . following the close brace, index into it.
            dotPosition = currentKey.find(dot, closeBracePosition);
            if (dotPosition == closeBracePosition + 1)
            {
                result = GetValue(currentKey.substr(dotPosition + dot.length()), result);
            }
            return result;
        }
    }
    return Json::Value();
}

Json::Value DataBindString(const Json::Value& sourceCard, const Json::Value& frame)
{
    std::string frameString = frame.asString();

    // Look for any data binding keys surrounded in double curly braces
    bool includeOnlyIfExists;
    size_t bracesStartPosition, bracesEndPosition;
    std::string key = GetDataBindingKey(frameString, 0, &bracesStartPosition, &bracesEndPosition, &includeOnlyIfExists);

    if (!key.empty() && bracesStartPosition == 0 && bracesEndPosition == frameString.length() - 1)
    {
        // If the entire string is a data binding element, return the result of GetValue, which may be of any type.
        Json::Value value = GetValue(key, sourceCard);
        if (value.empty() && !includeOnlyIfExists)
        {
            // If we didn't find a match, return the frame as is
            value = frame;
        }
        return value;
    }
    else if (!key.empty())
    {
        // If we have a data binding element, but it's not the entire string, do substring binding
        // For example: "This is a string with some {{stuff}} and {{things}} in it."
        std::string resultString;
        size_t currentFrameStartPosition = 0;

        while (!key.empty())
        {
            // Append the portion before the data binding element
            resultString += frameString.substr(currentFrameStartPosition, bracesStartPosition - currentFrameStartPosition);

            // Get the value of the data binding element
            Json::Value result = GetValue(key, sourceCard);

            // If the result wasn't found or wasn't a string, leave the data binding element in
            // place. Otherwise append the result.
            if ((result.empty() || !result.isString()))
            {
                if (!includeOnlyIfExists)
                {
                    resultString += frameString.substr(bracesStartPosition, bracesEndPosition - bracesStartPosition + 1);
                }
            }
            else
            {
                resultString += result.asString();
            }

            // Advance the start position on the frame string, and find the next data binding element
            currentFrameStartPosition = bracesEndPosition + 1;
            key = GetDataBindingKey(frameString, currentFrameStartPosition, &bracesStartPosition, &bracesEndPosition, &includeOnlyIfExists);
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

Json::Value DataBindArray(const Json::Value& sourceCard, const Json::Value& frame)
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
        else if (elementResult.isArray())
        {
            // If we get an array back (from an {{#each}} element, for example), append the
            // elements of that array to this one.
            for (Json::Value::const_iterator itElement = elementResult.begin(); itElement != elementResult.end(); itElement++)
            {
                result.append(*itElement);
            }
        }
        else
        {
            result.append(elementResult);
        }
    }

    return result;
}

// Handles #each arrays with syntax such as the following:
// {{#each myArray}} : {"type" : "TextBlock, "text" : "{{foo}}"}
// where "myArray" is an array of objects each with a "foo" property
Json::Value DataBindAsEachObject(const Json::Value& sourceCard, const Json::Value& frame)
{
    Json::Value result;
    if (frame.size() == 1)
    {
        auto memberNames = frame.getMemberNames();
        std::string jsonKey = memberNames[0];

        size_t startPosition, endPosition;
        std::string dataBindingKey = GetKey(jsonKey, 0, "{{", "}}", &startPosition, &endPosition);

        if (!dataBindingKey.empty())
        {
            std::string eachString("#each");
            if (!dataBindingKey.compare(0, eachString.length(), eachString))
            {
                // Get the name of the array
                std::string arrayName = GetArgument(dataBindingKey, eachString.length());
                Json::Value eachArray = sourceCard;
                if (!arrayName.empty())
                {
                    eachArray = sourceCard[arrayName];
                }

                if (eachArray.isArray())
                {
                    // Iterate throught the array and data bind, using each element of the array
                    // as the source and the value of the key as the frame
                    for (Json::Value::const_iterator itArray = eachArray.begin(); itArray != eachArray.end(); itArray++)
                    {
                        result.append(DataBindJson(*itArray, frame[jsonKey]));
                    }
                }
            }
        }
    }
    return result;
}

Json::Value DataBindObject(const Json::Value& sourceCard, const Json::Value& frame)
{
    Json::Value result;

    // Check if this is a #each object.
    result = DataBindAsEachObject(sourceCard, frame);
    if (!result.empty())
    {
        return result;
    }
    else
    {
        // Loop through the sub elements of the object and bind each one
        for (Json::Value::const_iterator it = frame.begin(); it != frame.end(); it++)
        {
            std::string key = it.key().asCString();
            // Data bind the json value in "key" : "value" and add it to the result;
            Json::Value elementResult = DataBindJson(sourceCard, *it);
            if (elementResult.empty())
            {
                // If the result is empty, don't add it to the json
                continue;
            }
            result[key] = elementResult;
        }
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

Json::Value DataBindJson(const Json::Value& sourceCard, const Json::Value& frame)
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

Json::Value ApplyFrame(const Json::Value& sourceCard, const Json::Value& frame)
{
    Json::Value dataBoundCard;

    // First bind the card to its data if present
    try
    {
        Json::Value data = sourceCard["data"];
        dataBoundCard = DataBindJson(data, sourceCard);
    }
    catch (...)
    {
        dataBoundCard = sourceCard;
    }

    // Create a data source for the frame binding which has the card stored as "card"
    // (and someday the runtime object stored as "runtime")
    Json::Value dataSource;
    dataSource["card"] = dataBoundCard;

    // Then bind the bound card to its frame
    return DataBindJson(dataSource, frame);
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
