// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseUtil.h"
#include "AdaptiveCardParseException.h"
#include "ElementParserRegistration.h"
#include "ActionParserRegistration.h"
#include "TextBlock.h"
#include "Container.h"
#include "ShowCardAction.h"

namespace
{
    Json::StreamWriterBuilder CreateJsonStreamWriter()
    {
        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "";

        return builder;
    }
}

namespace AdaptiveCards
{
    std::string ParseUtil::JsonToString(const Json::Value& json)
    {
        const thread_local Json::StreamWriterBuilder builder = ::CreateJsonStreamWriter();
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

        std::ostringstream outStream;
        writer->write(json, &outStream);
        outStream << std::endl;
        return outStream.str();
    }

    void ParseUtil::ThrowIfNotJsonObject(const Json::Value& json)
    {
        if (!json.isObject())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidJson, "Expected JSON Object\n");
        }
    }

    std::string ParseUtil::GetTypeAsString(const Json::Value& json)
    {
        const char typeKey[] = "type";

        if (!json.isMember(typeKey))
        {
            std::stringstream ss;

            ss << "The JSON element is missing the following value: ";
            ss << typeKey;

            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing, ss.str());
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

    std::string ParseUtil::TryGetString(const Json::Value& json, AdaptiveCardSchemaKey key)
    {
        try
        {
            return GetString(json, key);
        }
        catch (Json::Exception&)
        {
            return "";
        }
    }

    // Get value mapped to key. Validates that value is string JSON type.
    std::string ParseUtil::GetString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
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
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
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

    // Get value mapped to key as a string, regardless of value's JSON type.
    std::string ParseUtil::GetValueAsString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
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

    [[deprecated("Use generalized DeserializeValue<T> instead")]] std::shared_ptr<BackgroundImage>
    ParseUtil::GetBackgroundImage(const Json::Value& json)
    {
        return DeserializeValue<BackgroundImage>(json, AdaptiveCardSchemaKey::BackgroundImage, BackgroundImage::Deserialize);
    }

    bool ParseUtil::GetBool(const Json::Value& json, AdaptiveCardSchemaKey key, bool defaultValue, bool isRequired)
    {
        auto optionalBool = GetOptionalBool(json, key);

        if (isRequired && !optionalBool.has_value())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                             "Property is required but was found empty: " + AdaptiveCardSchemaKeyToString(key));
        }
        else
        {
            return optionalBool.value_or(defaultValue);
        }
    }

    // Get optional boolean value at given key. Validates that value is bool type, if present.
    std::optional<bool> ParseUtil::GetOptionalBool(const Json::Value& json, AdaptiveCardSchemaKey key)
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            return std::nullopt;
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
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
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
        auto optionalInt = GetOptionalInt(json, key);

        if (isRequired && !optionalInt.has_value())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                             "Property is required but was found empty: " + AdaptiveCardSchemaKeyToString(key));
        }
        else
        {
            return optionalInt.value_or(defaultValue);
        }
    }

    std::optional<int> ParseUtil::GetOptionalInt(const Json::Value& json, AdaptiveCardSchemaKey key)
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            return std::nullopt;
        }

        if (!propertyValue.isInt())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Value for property " + propertyName + " was invalid. Expected type int.");
        }

        return propertyValue.asInt();
    }

    std::optional<double> ParseUtil::GetOptionalDouble(const Json::Value& json, AdaptiveCardSchemaKey key)
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
        auto propertyValue = json.get(propertyName, Json::Value());
        if (propertyValue.empty())
        {
            return std::nullopt;
        }

        if (!propertyValue.isDouble())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Value for property " + propertyName + " was invalid. Expected type double.");
        }

        return propertyValue.asDouble();
    }

    void ParseUtil::ExpectTypeString(const Json::Value& json, const std::string& expectedTypeStr)
    {
        const std::string actualType = GetTypeAsString(json);

        if (expectedTypeStr != actualType)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "The JSON element did not have the correct type. Expected: " + expectedTypeStr +
                                                 ", Actual: " + actualType);
        }
    }

    void ParseUtil::ExpectTypeString(const Json::Value& json, CardElementType bodyType)
    {
        return ExpectTypeString(json, CardElementTypeToString(bodyType));
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

    Json::Value ParseUtil::GetArray(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
        auto elementArray = json.get(propertyName, Json::Value());

        if (!elementArray.isNull() && !elementArray.isArray())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Could not parse specified key: " + propertyName + ". It was not an array");
        }

        if (isRequired && elementArray.empty())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                             "Could not parse required key: " + propertyName + ". It was not found");
        }

        return elementArray;
    }

    std::vector<std::string> ParseUtil::GetStringArray(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        auto jsonArray = ParseUtil::GetArray(json, key, isRequired);
        std::vector<std::string> strings;

        strings.reserve(jsonArray.size());

        for (const auto& curJsonValue : jsonArray)
        {
            strings.push_back(curJsonValue.asString());
        }

        return strings;
    }

    Json::Value ParseUtil::GetJsonValueFromString(const std::string& jsonString)
    {
        const thread_local Json::CharReaderBuilder readerBuilder;
        std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());

        Json::Value jsonValue;
        std::string errors;
        if (!reader->parse(jsonString.data(), jsonString.data() + jsonString.size(), &jsonValue, &errors))
        {
            std::ostringstream exceptionMsg{};
            exceptionMsg << "Expected JSON Object (" << errors << ")";
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidJson, exceptionMsg.str());
        }

        return jsonValue;
    }

    Json::Value ParseUtil::ExtractJsonValue(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        const std::string& propertyName = AdaptiveCardSchemaKeyToString(key);
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
        std::transform(value.begin(), value.end(), new_value.begin(), [](char c) {
            return std::tolower(c, std::locale());
        });
        return new_value;
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
        if (parser == nullptr)
        {
            parser = context.actionParserRegistration->GetParser("UnknownAction");
        }

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
                elements.push_back(action);
            }
        }

        return elements;
    }

    std::shared_ptr<BaseActionElement> ParseUtil::GetAction(ParseContext& context, const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired)
    {
        auto selectAction = ParseUtil::ExtractJsonValue(json, key, isRequired);

        if (!selectAction.empty())
        {
            return ParseUtil::GetActionFromJsonValue(context, selectAction);
        }

        return nullptr;
    }

    std::shared_ptr<BaseCardElement> ParseUtil::GetLabelFromJsonValue(ParseContext& context, const Json::Value& json)
    {
        if (json.empty() || !json.isObject())
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Expected a Json object to extract Label element");
        }

        // Get the element's type
        std::string typeString = ToLowercase(GetTypeAsString(json));

        if ((typeString != ToLowercase(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TextBlock))) &&
            (typeString != ToLowercase(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::RichTextBlock))))
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                             "Element type is not a string, TextBlock or RichTextBlock");
        }

        auto parser = context.elementParserRegistration->GetParser(typeString);

        // Parse it if it's allowed by the current parsers
        if (parser != nullptr)
        {
            // Use the parser that maps to the type
            return parser->Deserialize(context, json);
        }

        return nullptr;
    }

    std::shared_ptr<BaseCardElement> ParseUtil::GetLabel(ParseContext& context, const Json::Value& json, AdaptiveCardSchemaKey key)
    {
        auto label = ParseUtil::ExtractJsonValue(json, key);

        if (!label.empty())
        {
            return ParseUtil::GetLabelFromJsonValue(context, label);
        }

        return nullptr;
    }
}
