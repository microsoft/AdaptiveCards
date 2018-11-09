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

const char* c_whitespace = " \t";

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
    size_t bracesEndPosition = string.find(bracesEnd, bracesStartPosition + 1);

    std::string key;
    if (bracesStartPosition != std::string::npos && bracesEndPosition != std::string::npos)
    {
        key = string.substr(bracesStartPosition + bracesStart.length(),
                            bracesEndPosition - bracesStartPosition - bracesStart.length());

        if (keyStartPosition)
        {
            *keyStartPosition = bracesStartPosition;
        }
        if (keyEndPosition)
        {
            *keyEndPosition = bracesEndPosition + bracesEnd.length() - 1;
        }
    }

    return key;
}

// Determines if this string matches the given keyword, and returns any argument that may be present
bool IsKeyword(const std::string& string, size_t startPosition, const std::string& keyword, std::string& argument)
{
    std::string key = GetKey(string, startPosition, "{{", "}}", nullptr, nullptr);

    if (!key.compare(0, keyword.length(), keyword))
    {
        size_t argumentStart = key.find_first_not_of(c_whitespace, keyword.length());
        if (argumentStart != std::string::npos)
        {
            argument = key.substr(argumentStart, key.length() - argumentStart);
        }
        return true;
    }
    return false;
}

// Gets a databinding key between double curly braces {{key}} and checks for the existential operator.
std::string GetDataBindingKey(std::string string, size_t startPosition, size_t* keyStartPosition, size_t* keyEndPosition, bool* includeOnlyIfExists)
{
    std::string key = GetKey(string, startPosition, "{{", "}}", keyStartPosition, keyEndPosition);

    // If the databinding key includes the existential operator ("{{#? stuff}}"), set the boolean indicating it should
    // only be included if it exits, and return just the argument ("stuff") as the key
    *includeOnlyIfExists = IsKeyword(string, startPosition, "#?", key);
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

    // Handle this.stuff where "this" is the current scope
    std::string thisString = "this";
    std::string beforeDotKey = currentKey.substr(0, dotPosition);
    if (!beforeDotKey.compare(0, thisString.length(), thisString))
    {
        // Remove the "this" from the string without changing the scope
        currentKey = currentKey.substr(dotPosition + 1, currentKey.length() - dotPosition);
        dotPosition = currentKey.find(dot, 0);
    }

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

bool EvaluateAsInConditional(std::string conditional, const Json::Value& sourceCard)
{
    // Evaluates conditionals of the form {{#if 'foo' in bar}}

    // Find a variable in single quotes
    size_t startQuotePosition, endQuotePosition;
    std::string variable = GetKey(conditional, 0, "\'", "\'", &startQuotePosition, &endQuotePosition);
    if (startQuotePosition == 0 && !variable.empty())
    {
        std::string inString = "in";
        size_t inPositon = conditional.find_first_not_of(c_whitespace, endQuotePosition + 1);
        if (!conditional.compare(inPositon, inString.length(), inString))
        {
            // Find the scope after the whitespace after "in"
            size_t scopeStartPosition = conditional.find_first_not_of(c_whitespace, inPositon + inString.length());
            size_t scopeEndPosition = conditional.find_last_not_of(c_whitespace);
            std::string scope = conditional.substr(scopeStartPosition, scopeEndPosition - scopeStartPosition + 1);
            
            // For a conditional of the form {{#if 'foo' in bar}}, create a frame {{#? bar.foo}} to evaluate with
            // DataBindString. This will return empty if it doesn't exist, non-empty if it does.
            Json::Value frame("{{#? " + scope + "." + variable + "}}");
            Json::Value result = DataBindString(sourceCard, frame);
            return !result.empty();
        }
    }

    return false;
}

bool EvaluateConditional(std::string conditional, const Json::Value& sourceCard)
{
    if (!conditional.compare(0, conditional.length(), "true"))
    {
        return true;
    }
    else if (EvaluateAsInConditional(conditional, sourceCard))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DataBindIfElseArray(const Json::Value& sourceCard, const Json::Value& frame, Json::Value& resultOut)
{
    // Check if the first property of the first object is a #if
    Json::Value arrayElement = frame[0];
    if (arrayElement.isObject())
    {
        std::string conditional;
        std::string objectKey = arrayElement.getMemberNames()[0];
        if (IsKeyword(objectKey, 0, "#if", conditional))
        {
            Json::Value result;

            // This is a #if case, evaluate the conditional
            if (EvaluateConditional(conditional, sourceCard))
            {
                result = DataBindJson(sourceCard, arrayElement[objectKey]);
            }
            else
            {
                // Handle #elseif cases
                unsigned int frameIndex;
                for (frameIndex = 1; frameIndex < frame.size(); frameIndex++)
                {
                    arrayElement = frame[frameIndex];
                    if (arrayElement.isObject())
                    {
                        objectKey = arrayElement.getMemberNames()[0];

                        if (IsKeyword(objectKey, 0, "#elseif", conditional))
                        {
                            if (EvaluateConditional(conditional, sourceCard))
                            {
                                result = DataBindJson(sourceCard, arrayElement[objectKey]);
                                break;
                            }
                        }
                        else
                        {
                            // Break out of the loop if we see something other than #elseif
                            break;
                        }
                    }
                }

                // If we haven't found a result and there are still items left, check for #else
                if (result.empty() && frameIndex < frame.size())
                {
                    std::string arg;
                    if (IsKeyword(objectKey, 0, "#else", arg))
                    {
                        result = DataBindJson(sourceCard, arrayElement[objectKey]);
                    }
                }
            }

            resultOut = result;
            return true;
        }
    }
    return false;
}

Json::Value DataBindArray(const Json::Value& sourceCard, const Json::Value& frame)
{
    // Handle the case of a #if/#elseif/#else array
    Json::Value result;
    if (DataBindIfElseArray(sourceCard, frame, result))
    {
        return result;
    }

    // Loop through the sub elements of the array and bind each one
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
bool DataBindAsEachObject(const Json::Value& sourceCard, const Json::Value& frame, Json::Value& resultOut)
{
    // A #each object will have one value with a key that looks like
    // {{#each myArray}}
    if (frame.size() == 1)
    {
        auto memberNames = frame.getMemberNames();
        std::string jsonKey = memberNames[0];

        std::string arrayName;
        if (IsKeyword(jsonKey, 0, "#each", arrayName))
        {
            if (!arrayName.empty())
            {
                Json::Value eachArray = sourceCard;
                eachArray = sourceCard[arrayName];
                if (eachArray.isArray())
                {
                    // Iterate throught the array and data bind, using each element of the array
                    // as the source and the value of the key as the frame
                    Json::Value result;
                    for (Json::Value::const_iterator itArray = eachArray.begin(); itArray != eachArray.end(); itArray++)
                    {
                        result.append(DataBindJson(*itArray, frame[jsonKey]));
                    }
                    resultOut = result;
                    return true;
                }
            }
        }
    }
    return false;
}

Json::Value DataBindObject(const Json::Value& sourceCard, const Json::Value& frame)
{
    Json::Value result;

    // Check if this is a #each object.
    if (DataBindAsEachObject(sourceCard, frame, result))
    {
        return result;
    }

    // Loop through the sub elements of the object and bind each one
    for (Json::Value::const_iterator it = frame.begin(); it != frame.end(); it++)
    {
        std::string key = it.key().asCString();
        // Data bind the json value in "key" : "value" and add it to the result;
        result[key] = DataBindJson(sourceCard, *it);
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

Json::Value ApplyJsonTemplating(const Json::Value& sourceCard, const Json::Value& frame, const Json::Value& runtimeObject)
{
    // First bind the card to its data if present. This will also handle special keywords (#if, #each, etc).
    Json::Value dataBoundCard = DataBindJson(sourceCard["data"], sourceCard);

    Json::FastWriter fastWriter;
    std::string resultString = fastWriter.write(dataBoundCard);

    Json::Value result = dataBoundCard;
    if (!frame.empty())
    {
        // Create a data source for the frame binding which has the card stored as "card"
        // and the runtime object stored as "runtime"
        Json::Value dataSource;
        dataSource["card"] = dataBoundCard;
        dataSource["runtime"] = runtimeObject;

        // Then bind the bound card to its frame
        result = DataBindJson(dataSource, frame);
    }

    resultString = fastWriter.write(result);
    return result;
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
        // TODO - un-hardcode the strings and confirm these properties are right for pruning (spec issue)
        switch (elementType)
        {
        case CardElementType::ActionSet:
            return value["actions"].empty();

        case CardElementType::ChoiceSetInput:
            return value["choices"].empty();

        case CardElementType::Column:
        case CardElementType::Container:
            return value["items"].empty();

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

        case CardElementType::ColumnSet:
            // Existing cards support empty column sets so don't prune here for now
            // return value["columns"].empty();

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
        // Existing cards support empty action titles do don't prune here for now
        // return value["title"].empty();
        return false;
    }
    else
    {
        return false;
    }
}
