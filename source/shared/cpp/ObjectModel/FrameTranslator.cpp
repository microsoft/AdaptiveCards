#include "pch.h"
#include "FrameTranslator.h"
#include "Enums.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

void DataBindStringFromSource(
    const Json::Value& sourceCard,
    const Json::Value& frame,
    Json::Value& result
)
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
            DataBindStringFromSource(sourceCard, frame, localResult);
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
            if (frame.isArray())
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
}