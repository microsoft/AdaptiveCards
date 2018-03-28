#include "pch.h"
#include "FrameTranslator.h"
#include "Enums.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

void ApplyFrame(
    const Json::Value& sourceCard, 
    const Json::Value& frame, 
    Json::Value& result)
{
    // Walk the frame and plug in results from the source card
    auto elementArray = ParseUtil::GetArray(frame, AdaptiveCardSchemaKey::Body, true);

    Json::Value localResult;

    // Walk all properties and put any unknown ones in the additional properties json
    for (Json::Value::const_iterator it = frame.begin(); it != frame.end(); it++)
    {
        std::string key = it.key().asCString();
        localResult[key] = *it;
    }
}