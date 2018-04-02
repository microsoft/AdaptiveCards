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
    if (frame.begin() == frame.end())
    {
        if (frame.isString())
        {
            DataBindFrameStringFromSource(sourceCard, frame, localResult);
        }
        else
        {
            localResult = frame;
        }
    }
    else
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
            else
            {
                std::string key = it.key().asCString();
                localResult[key] = elementResult;
            }
        }
    }

    result = localResult;

    std::string resultString = fastWriter.write(result);
}

bool HasPrimaryValue(std::shared_ptr<BaseActionElement> cardElement);
bool HasPrimaryValue(std::shared_ptr<BaseCardElement> cardElement);
bool HasPrimaryValue(std::shared_ptr<ChoiceInput> cardElement);
bool HasPrimaryValue(std::shared_ptr<Fact> cardElement);

template<typename T>
bool PruneElementArray(std::vector<std::shared_ptr<T>>& elements)
{
    elements.erase(std::remove_if(elements.begin(), elements.end(), [](std::shared_ptr<T> element) {return !HasPrimaryValue(element); }), elements.end());
    return !elements.empty();
}

bool HasPrimaryValue(std::shared_ptr<BaseActionElement> action)
{
    return true;
}

bool HasPrimaryValue(std::shared_ptr<ChoiceInput> choiceInput)
{
    
    return !choiceInput->GetTitle().empty();
}

bool HasPrimaryValue(std::shared_ptr<Fact> fact)
{
    return !fact->GetTitle().empty() && !fact->GetValue().empty();
}

bool HasPrimaryValue(std::shared_ptr<BaseCardElement> cardElement)
{
    switch (cardElement->GetElementType())
    {
        case CardElementType::ActionSet:
            return PruneElementArray(std::dynamic_pointer_cast<AdaptiveCards::ActionSet>(cardElement)->GetActions());

        case CardElementType::ChoiceSetInput:
            return PruneElementArray(std::dynamic_pointer_cast<AdaptiveCards::ChoiceSetInput>(cardElement)->GetChoices());

        case CardElementType::Column:
            return PruneElementArray(std::dynamic_pointer_cast<AdaptiveCards::Column>(cardElement)->GetItems());

        case CardElementType::ColumnSet:
            return PruneElementArray(std::dynamic_pointer_cast<AdaptiveCards::ColumnSet>(cardElement)->GetColumns());

        case CardElementType::Container:
            return PruneElementArray(std::dynamic_pointer_cast<AdaptiveCards::Container>(cardElement)->GetItems());

        case CardElementType::FactSet:
            return PruneElementArray(std::dynamic_pointer_cast<AdaptiveCards::FactSet>(cardElement)->GetFacts());

        case CardElementType::ImageSet:
            return PruneElementArray(std::dynamic_pointer_cast<AdaptiveCards::ImageSet>(cardElement)->GetImages());

        case CardElementType::Image:
            return !std::dynamic_pointer_cast<AdaptiveCards::Image>(cardElement)->GetUrl().empty();

        case CardElementType::TextBlock:
            return !std::dynamic_pointer_cast<AdaptiveCards::TextBlock>(cardElement)->GetText().empty();

        case CardElementType::DateInput:
        case CardElementType::NumberInput:
        case CardElementType::TextInput:
        case CardElementType::TimeInput:
        case CardElementType::ToggleInput:
        case CardElementType::Custom:
        case CardElementType::Unknown:
            return true;
    }

    return true;
}

void PruneCard(std::shared_ptr<AdaptiveCard> card)
{
    PruneElementArray(card->GetBody());
}