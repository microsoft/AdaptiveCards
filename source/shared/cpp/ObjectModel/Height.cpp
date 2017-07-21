#include "pch.h"
#include "Height.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Height Height::Deserialize(const Json::Value& json, const Height& defaultValue)
{
    Height result;
    ParseUtil::ThrowIfNotJsonObject(json);
    result.heightType = HeightTypeFromString(json.asString());
    return result;
}

std::string Height::SerializeToString(const Height& defaultValue)
{
    return HeightTypeToString(defaultValue.heightType);
}