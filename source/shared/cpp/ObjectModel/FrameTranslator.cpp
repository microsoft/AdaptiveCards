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

void DataBindFrameStringFromSource(
    const Json::Value& sourceCard,
    const Json::Value& frame,
    Json::Value& result)
{
    std::string valueStart("${");
    std::string valueEnd("}");

    auto frameString = frame.asString();

    Json::Value localResult;
    size_t valueStartPosition = frameString.find(valueStart, 0);
    size_t valueEndPosition = frameString.find(valueEnd, 0);

    if (valueStartPosition != std::string::npos && 
        valueStartPosition == 0 &&
        valueEndPosition == frameString.length() - 1)
    {
        std::string key = frameString.substr(2, frameString.length() - 3);
        result = sourceCard[key];
    }
    else
    {
        result = frame;
    }
}

void ApplyFrame(
    const Json::Value& sourceCard,
    const Json::Value& frame,
    Json::Value& result)
{
    Json::FastWriter fastWriter;
    std::string sourceString = fastWriter.write(sourceCard);
    std::string frameString = fastWriter.write(frame);

    Json::Value localResult;

    if (frame.isString())
    {
        DataBindFrameStringFromSource(sourceCard, frame, localResult);
    }
    else if (frame.isArray() || frame.isObject())
    {
        // Walk the frame and plug in results from the source card
        for (Json::Value::const_iterator it = frame.begin(); it != frame.end(); it++)
        {
            Json::Value elementResult;
            ApplyFrame(sourceCard, *it, elementResult);

            if (elementResult.empty())
            {
                // If this is empty, don't add it to the json
                continue;
            }
            else if (frame.isArray())
            {
                localResult.append(elementResult);
            }
            else if (frame.isObject())
            {
                std::string key = it.key().asCString();
                localResult[key] = elementResult;
            }
        }

        if (frame.isObject() && ShouldJsonObjectBePruned(localResult))
        {
            localResult = Json::Value();
        }
    }
    else
    {
        localResult = frame;
    }

    result = localResult;

    std::string resultString = fastWriter.write(result);
}

bool ShouldJsonObjectBePruned(Json::Value value)
{
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