#pragma once

#include "pch.h"
#include "AdaptiveCardParseException.h"
#include "Enums.h"
#include "json\json.h"

namespace AdaptiveCards
{

class ParseUtil
{

public:

    static void ThrowIfNotJsonObject(const Json::Value& json);

    static void ExpectString(const Json::Value& json);

    static std::string GetTypeAsString(const Json::Value& json);

    static std::string TryGetTypeAsString(const Json::Value& json);

    static std::string GetString(const Json::Value& json, AdaptiveCardSchemaKey key);

    static bool GetBool(const Json::Value& json, AdaptiveCardSchemaKey key, bool defaultValue);

    static CardElementType GetCardElementType(const Json::Value& json);

    static CardElementType TryGetCardElementType(const Json::Value& json);

    template <typename T>
    static T GetEnumValue(const Json::Value& json, AdaptiveCardSchemaKey key, T defaultEnumValue, std::function<T(const std::string& name)> enumConverter);

    static void ExpectTypeString(const Json::Value& json, CardElementType bodyType);

    // throws if the key is missing or the value mapped to the key is the wrong type
    static void ExpectKeyAndValueType(const Json::Value& json, const char* expectedKey, std::function<void(const Json::Value&)> throwIfWrongType);


private:
    ParseUtil();
    ~ParseUtil();

};

template <typename T>
T ParseUtil::GetEnumValue(const Json::Value& json, AdaptiveCardSchemaKey key, T defaultEnumValue, std::function<T(const std::string& name)> enumConverter)
{
    std::string propertyValueStr = "";
    try
    {
        const std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            return defaultEnumValue;
        }

        if (!propertyValue.isString())
        {
            throw AdaptiveCardParseException("Enum type was invalid. Expected type string.");
        }

        propertyValueStr = propertyValue.asString();
        return enumConverter(propertyValueStr);
    }
    catch (const std::out_of_range&)
    {
        throw AdaptiveCardParseException("Enum type was out of range. Actual: " + propertyValueStr);
    }
}
}
