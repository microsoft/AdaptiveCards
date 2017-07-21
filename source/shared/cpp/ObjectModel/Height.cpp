#include "Height.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Height Height::Deserialize(const Json::Value& json, const Height& defaultValue)
{
    Height result;

    if (!json.isString())
    {
        throw AdaptiveCardParseException("Height property type was invalid. Expected type string.");
    }

    result.heightType = HeightTypeFromString(json.asString());

    return result;
}

std::string Height::SerializeToString(const Height& defaultValue)
{
    return HeightTypeToString(defaultValue.heightType);
}