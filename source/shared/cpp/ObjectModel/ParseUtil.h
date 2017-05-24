#pragma once

#include "pch.h"
#include "AdaptiveCardParseException.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{

class ParseUtil
{

public:

    static void ThrowIfNotJsonObject(const Json::Value& json);

    static void ExpectString(const Json::Value& json);

    static std::string GetTypeAsString(const Json::Value& json);

    static std::string TryGetTypeAsString(const Json::Value& json);

    static std::string GetString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

    static std::string GetValueAsString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

    static bool GetBool(const Json::Value& json, AdaptiveCardSchemaKey key, bool defaultValue, bool isRequired = false);

    static unsigned int GetUInt(const Json::Value& json, AdaptiveCardSchemaKey key, unsigned int defaultValue, bool isRequired = false);

    static int GetInt(const Json::Value& json, AdaptiveCardSchemaKey key, int defaultValue, bool isRequired = false);

    static CardElementType GetCardElementType(const Json::Value& json);

    static CardElementType TryGetCardElementType(const Json::Value& json);

    static ActionType GetActionType(const Json::Value& json);

    static ActionType TryGetActionType(const Json::Value& json);

    static Json::Value GetArray(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

    static Json::Value GetJsonValueFromString(const std::string jsonString);

    template <typename T>
    static T GetEnumValue(
        const Json::Value& json,
        AdaptiveCardSchemaKey key,
        T defaultEnumValue,
        std::function<T(const std::string& name)> enumConverter,
        bool isRequired = false);

    template <typename T>
    static std::vector<std::shared_ptr<T>> GetElementCollection(
        const Json::Value& json,
        AdaptiveCardSchemaKey key,
        const std::unordered_map<CardElementType, std::function<std::shared_ptr<T>(const Json::Value&)>, EnumHash>& parsers,
        bool isRequired = false);

    template <typename T>
    static std::vector<std::shared_ptr<T>> GetActionCollection(
        const Json::Value& json,
        AdaptiveCardSchemaKey key,
        const std::unordered_map<ActionType, std::function<std::shared_ptr<T>(const Json::Value&)>, EnumHash>& parsers,
        bool isRequired = false);

    static void ExpectTypeString(const Json::Value& json, CardElementType bodyType);

    // throws if the key is missing or the value mapped to the key is the wrong type
    static void ExpectKeyAndValueType(const Json::Value& json, const char* expectedKey, std::function<void(const Json::Value&)> throwIfWrongType);


private:
    ParseUtil();
    ~ParseUtil();

};

template <typename T>
T ParseUtil::GetEnumValue(const Json::Value& json, AdaptiveCardSchemaKey key, T defaultEnumValue, std::function<T(const std::string& name)> enumConverter, bool isRequired)
{
    std::string propertyValueStr = "";
    try
    {
        const std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            if (isRequired)
            {
                throw AdaptiveCardParseException("Property is required but was found empty: " + propertyName);
            }
            else
            {
                return defaultEnumValue;
            }
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
    const std::unordered_map<CardElementType, std::function<std::shared_ptr<T>(const Json::Value&)>, EnumHash>& parsers,
    bool isRequired)
{
    auto elementArray = GetArray(json, key, isRequired);

    std::vector<std::shared_ptr<T>> elements;
    if (elementArray.empty())
    {
        return elements;
    }

    elements.reserve(elementArray.size());

    for (const auto& curJsonValue : elementArray)
    {
        // Get the element's type
        CardElementType curElementType = ParseUtil::TryGetCardElementType(curJsonValue);

        //Parse it if it's allowed by the current parsers
        if (parsers.find(curElementType) != parsers.end())
        {
            // Use the parser that maps to the type
            elements.push_back(parsers.at(curElementType)(curJsonValue));
        }
    }

    return elements;
}

template <typename T>
std::vector<std::shared_ptr<T>> ParseUtil::GetActionCollection(
    const Json::Value& json,
    AdaptiveCardSchemaKey key,
    const std::unordered_map<ActionType, std::function<std::shared_ptr<T>(const Json::Value&)>, EnumHash>& parsers,
    bool isRequired)
{
    auto elementArray = GetArray(json, key, isRequired);

    std::vector<std::shared_ptr<T>> elements;

    if (elementArray.empty())
    {
        return elements;
    }

    elements.reserve(elementArray.size());

    for (const auto& curJsonValue : elementArray)
    {
        // Get the element's type
        ActionType curActionType = ParseUtil::TryGetActionType(curJsonValue);

        //Parse it if it's allowed by the current parsers
        if (parsers.find(curActionType) != parsers.end())
        {
            // Use the parser that maps to the type
            elements.push_back(parsers.at(curActionType)(curJsonValue));
        }
    }

    return elements;
}

}
