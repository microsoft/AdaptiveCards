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

    static unsigned int GetUInt(const Json::Value& json, AdaptiveCardSchemaKey key, unsigned int defaultValue);

    static CardElementType GetCardElementType(const Json::Value& json);

    static CardElementType TryGetCardElementType(const Json::Value& json);

    template <typename T>
    static T GetEnumValue(const Json::Value& json, AdaptiveCardSchemaKey key, T defaultEnumValue, std::function<T(const std::string& name)> enumConverter);

    template <typename T>
    static std::vector<std::shared_ptr<T>> GetElementCollection(const Json::Value& json, AdaptiveCardSchemaKey key, const std::unordered_map<CardElementType, std::function<std::shared_ptr<T>(const Json::Value&)>, EnumHash>& parsers);

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

template <typename T>
std::vector<std::shared_ptr<T>> ParseUtil::GetElementCollection(
    const Json::Value& json,
    AdaptiveCardSchemaKey key,
    const std::unordered_map<CardElementType, std::function<std::shared_ptr<T>(const Json::Value&)>, EnumHash>& parsers)
{
    std::string propertyName = AdaptiveCardSchemaKeyToString(key);
    auto elementArray = json.get(propertyName, Json::Value());

    if (!elementArray.isArray() || elementArray.empty())
    {
        throw AdaptiveCardParseException("Could not parse specified key " + propertyName + ". It was not an array");
    }

    std::vector<std::shared_ptr<T>> elements;
    if (elementArray.empty())
    {
        return elements;
    }

    // Make sure the container fits the elements in the json file
    elements.resize(elementArray.size());

    std::transform(elementArray.begin(), elementArray.end(), elements.begin(), [&parsers](const Json::Value& cur)
    {
        // Get the element's type
        CardElementType curElementType = ParseUtil::TryGetCardElementType(cur);

        //Parse it if it's allowed by the current parsers
        if (parsers.find(curElementType) != parsers.end())
        {
            // Use the parser that maps to the type
            std::shared_ptr<T> element = parsers.at(curElementType)(cur);
            return element;
        }
        return std::shared_ptr<T>();
    });

    return elements;
}
}
