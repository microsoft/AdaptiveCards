#include "pch.h"
#include "ParseUtil.h"
#include "AdaptiveCardParseException.h"
#include "ElementParserRegistration.h"
#include "ActionParserRegistration.h"
#include "TextBlock.h"
#include "Container.h"
#include "ShowCardAction.h"

namespace AdaptiveSharedNamespace
{
    void ParseUtil::ThrowIfNotJsonObject(const Json::Value& json)
    {
        if (!json.isObject())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidJson, "Expected JSON Object\n");
        }
    }

    void ParseUtil::ExpectString(const Json::Value& json)
    {
        if (!json.isString())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "The JSON element did not have the expected type 'string'");
        }
    }

    std::string ParseUtil::GetTypeAsString(const Json::Value& json)
    {
        std::string typeKey = "type";
        if (!json.isMember(typeKey))
        {
            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                             "The JSON element is missing the following value: " + typeKey);
        }

        return json.get(typeKey, Json::Value()).asString();
    }

    std::string ParseUtil::TryGetTypeAsString(const Json::Value& json)
    {
        try
        {
            return GetTypeAsString(json);
        }
        catch (const AdaptiveCardParseException&)
        {
            return "";
        }
    }

    std::string ParseUtil::GetString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            if (isRequired)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                                 "Property is required but was found empty: " + propertyName);
            }
            else
            {
                return "";
            }
        }

        if (!propertyValue.isString())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Value for property " + propertyName + " was invalid. Expected type string.");
        }

        return propertyValue.asString();
    }

    std::string ParseUtil::GetString(const Json::Value& json, AdaptiveCardSchemaKey key, const std::string& defaultValue, bool isRequired)
    {
        std::string parseResult = GetString(json, key, isRequired);

        if (parseResult.empty())
        {
            return defaultValue;
        }

        return parseResult;
    }

    std::string ParseUtil::GetJsonString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            if (isRequired)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                                 "Property is required but was found empty: " + propertyName);
            }
            else
            {
                return "";
            }
        }

        return propertyValue.toStyledString();
    }

    std::string ParseUtil::GetValueAsString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            if (isRequired)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                                 "Property is required but was found empty: " + propertyName);
            }
            else
            {
                return "";
            }
        }

        return propertyValue.asString();
    }

    bool ParseUtil::GetBool(const Json::Value& json, AdaptiveCardSchemaKey key, bool defaultValue, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            if (isRequired)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                                 "Property is required but was found empty: " + propertyName);
            }
            else
            {
                return defaultValue;
            }
        }

        if (!propertyValue.isBool())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Value for property " + propertyName + " was invalid. Expected type bool.");
        }

        return propertyValue.asBool();
    }

    unsigned int ParseUtil::GetUInt(const Json::Value& json, AdaptiveCardSchemaKey key, unsigned int defaultValue, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            if (isRequired)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                                 "Property is required but was found empty: " + propertyName);
            }
            else
            {
                return defaultValue;
            }
        }

        if (!propertyValue.isUInt())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Value for property " + propertyName + " was invalid. Expected type uInt.");
        }

        return propertyValue.asUInt();
    }

    int ParseUtil::GetInt(const Json::Value& json, AdaptiveCardSchemaKey key, int defaultValue, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            if (isRequired)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                                 "Property is required but was found empty: " + propertyName);
            }
            else
            {
                return defaultValue;
            }
        }

        if (!propertyValue.isInt())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Value for property " + propertyName + " was invalid. Expected type int.");
        }

        return propertyValue.asInt();
    }

    void ParseUtil::ExpectTypeString(const Json::Value& json, CardElementType bodyType)
    {
        std::string actualType = GetTypeAsString(json);
        std::string expectedTypeStr = CardElementTypeToString(bodyType);
        const bool isTypeCorrect = expectedTypeStr.compare(actualType) == 0;
        if (!isTypeCorrect)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "The JSON element did not have the correct type. Expected: " + expectedTypeStr +
                                                 ", Actual: " + actualType);
        }
    }

    // throws if the key is missing or the value mapped to the key is the wrong type
    void ParseUtil::ExpectKeyAndValueType(const Json::Value& json,
                                          const char* expectedKey,
                                          std::function<void(const Json::Value&)> throwIfWrongType)
    {
        if (expectedKey == nullptr)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "null expectedKey");
        }

        if (!json.isMember(expectedKey))
        {
            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                             "The JSON element is missing the following key: " + std::string(expectedKey));
        }

        auto value = json.get(expectedKey, Json::Value());
        throwIfWrongType(value);
    }

    CardElementType ParseUtil::GetCardElementType(const Json::Value& json)
    {
        return CardElementTypeFromString(GetTypeAsString(json));
    }

    CardElementType ParseUtil::TryGetCardElementType(const Json::Value& json)
    {
        try
        {
            return GetCardElementType(json);
        }
        catch (const AdaptiveCardParseException&)
        {
            return CardElementType::Unknown;
        }
    }

    ActionType ParseUtil::GetActionType(const Json::Value& json) { return ActionTypeFromString(GetTypeAsString(json)); }

    ActionType ParseUtil::TryGetActionType(const Json::Value& json)
    {
        try
        {
            return GetActionType(json);
        }
        catch (const AdaptiveCardParseException&)
        {
            return ActionType::Unsupported;
        }
    }

    Json::Value ParseUtil::GetArray(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto elementArray = json.get(propertyName, Json::Value());
        if (isRequired && elementArray.empty())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                             "Could not parse required key: " + propertyName + ". It was not found");
        }

        if (!elementArray.empty() && !elementArray.isArray())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Could not parse specified key: " + propertyName + ". It was not an array");
        }
        return elementArray;
    }

    Json::Value ParseUtil::GetJsonValueFromString(const std::string& jsonString)
    {
        Json::Reader reader;
        Json::Value jsonValue;
        if (!reader.parse(jsonString.c_str(), jsonValue))
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidJson, "Expected JSON Object");
        }
        return jsonValue;
    }

    Json::Value ParseUtil::ExtractJsonValue(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        std::string propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (isRequired && propertyValue.empty())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                             "Could not extract required key: " + propertyName + ".");
        }
        return propertyValue;
    }

    std::string ParseUtil::ToLowercase(std::string const& value)
    {
        std::string new_value;
        new_value.resize(value.size());
        auto new_end = std::transform(value.begin(), value.end(), new_value.begin(), [](char c) {
            return std::tolower(c, std::locale());
        });
        return new_value;
    }

    template<typename T> static void AddId(const T& element, std::unordered_set<std::string>& ids)
    {
        auto id = element.GetId();
        if (!id.empty())
        {
            auto search = ids.find(id);
            if (search == ids.end())
            {
                ids.emplace(id);
            }
            else
            {
                throw AdaptiveCardParseException(ErrorStatusCode::IdCollision, "Duplicate identifier encountered: id = '" + id + "'");
            }
        }
    }

    std::vector<std::shared_ptr<BaseCardElement>> ParseUtil::GetElementCollection(ParseContext& context,
                                                                                  const Json::Value& json,
                                                                                  AdaptiveCardSchemaKey key,
                                                                                  bool isRequired)
    {
        auto elementArray = GetArray(json, key, isRequired);

        std::vector<std::shared_ptr<BaseCardElement>> elements;
        if (elementArray.empty())
        {
            return std::move(elements);
        }

        elements.reserve(elementArray.size());

        for (const auto& curJsonValue : elementArray)
        {
            // Get the element's type
            std::string typeString = GetTypeAsString(curJsonValue);

            // Use the parser that maps to the type
            std::shared_ptr<BaseCardElementParser> parser = context.elementParserRegistration->GetParser(typeString);

            if (parser == nullptr)
            {
                parser = context.elementParserRegistration->GetParser("Unknown");
            }

            auto element = parser->Deserialize(context, curJsonValue);
            if (element != nullptr)
            {
                AddId(*element, *(context.elementIds));
                elements.push_back(element);
            }
        }

        return std::move(elements);
    }

    std::shared_ptr<BaseActionElement> ParseUtil::GetActionFromJsonValue(ParseContext& context, const Json::Value& json)
    {
        if (json.empty() || !json.isObject())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Expected a Json object to extract Action element");
        }

        // Get the element's type
        std::string typeString = GetTypeAsString(json);

        auto parser = context.actionParserRegistration->GetParser(typeString);

        // Parse it if it's allowed by the current parsers
        if (parser != nullptr)
        {
            // Use the parser that maps to the type
            return parser->Deserialize(context, json);
        }

        return nullptr;
    }

    std::vector<std::shared_ptr<BaseActionElement>> ParseUtil::GetActionCollection(ParseContext& context,
                                                                                   const Json::Value& json,
                                                                                   AdaptiveCardSchemaKey key,
                                                                                   bool isRequired)
    {
        auto elementArray = GetArray(json, key, isRequired);

        std::vector<std::shared_ptr<BaseActionElement>> elements;

        if (elementArray.empty())
        {
            return elements;
        }

        elements.reserve(elementArray.size());

        for (const auto& curJsonValue : elementArray)
        {
            auto action = ParseUtil::GetActionFromJsonValue(context, curJsonValue);
            if (action != nullptr)
            {
                AddId(*action, *(context.elementIds));
                elements.push_back(action);
            }
        }

        return elements;
    }

    std::shared_ptr<BaseActionElement>
    ParseUtil::GetAction(ParseContext& context, const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        auto selectAction = ParseUtil::ExtractJsonValue(json, key, isRequired);

        if (!selectAction.empty())
        {
            return ParseUtil::GetActionFromJsonValue(context, selectAction);
        }

        return nullptr;
    }
}
