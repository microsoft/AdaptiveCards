// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "AdaptiveCardParseException.h"
#include "ParseContext.h"

namespace AdaptiveSharedNamespace
{
    class BaseCardElement;
    class BaseActionElement;
    class BackgroundImage;

    namespace ParseUtil
    {
        std::string JsonToString(const Json::Value& json);

        void ThrowIfNotJsonObject(const Json::Value& json);

        std::string GetTypeAsString(const Json::Value& json);

        std::string TryGetTypeAsString(const Json::Value& json);

        std::string GetString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

        std::string GetString(const Json::Value& json, AdaptiveCardSchemaKey key, const std::string& defaultValue, bool isRequired = false);

        std::string TryGetString(const Json::Value& json, AdaptiveCardSchemaKey key);

        // Gets the specified property and returns a JSON string of the value
        std::string GetJsonString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

        std::string GetValueAsString(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

        std::shared_ptr<BackgroundImage> GetBackgroundImage(const Json::Value& json);

        bool GetBool(const Json::Value& json, AdaptiveCardSchemaKey key, bool defaultValue, bool isRequired = false);

        unsigned int GetUInt(const Json::Value& json, AdaptiveCardSchemaKey key, unsigned int defaultValue, bool isRequired = false);

        int GetInt(const Json::Value& json, AdaptiveCardSchemaKey key, int defaultValue, bool isRequired = false);

        CardElementType GetCardElementType(const Json::Value& json);

        CardElementType TryGetCardElementType(const Json::Value& json);

        ActionType GetActionType(const Json::Value& json);

        ActionType TryGetActionType(const Json::Value& json);

        Json::Value GetArray(const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

        Json::Value GetJsonValueFromString(const std::string& jsonString);

        Json::Value ExtractJsonValue(const Json::Value& jsonRoot, AdaptiveCardSchemaKey key, bool isRequired = false);

        template<typename T>
        T GetEnumValue(const Json::Value& json,
                       AdaptiveCardSchemaKey key,
                       T defaultEnumValue,
                       std::function<T(const std::string& name)> enumConverter,
                       bool isRequired = false);

        template<typename T>
        std::shared_ptr<T> GetElementOfType(ParseContext& context,
                                            const Json::Value& json,
                                            AdaptiveCardSchemaKey key,
                                            const std::function<std::shared_ptr<T>(ParseContext& context, const Json::Value&)>& deserializer);

        template<typename T>
        std::vector<std::shared_ptr<T>> GetElementCollection(bool isTopToBottomContainer,
                                                             ParseContext& context,
                                                             const Json::Value& json,
                                                             AdaptiveCardSchemaKey key,
                                                             bool isRequired = false,
                                                             const std::string& impliedType = std::string());

        template<typename T>
        std::vector<std::shared_ptr<T>> GetElementCollectionOfSingleType(
            ParseContext& context,
            const Json::Value& json,
            AdaptiveCardSchemaKey key,
            const std::function<std::shared_ptr<T>(ParseContext& context, const Json::Value&)>& deserializer,
            bool isRequired = false);

        std::vector<std::shared_ptr<BaseActionElement>> GetActionCollection(ParseContext& context,
                                                                            const Json::Value& json,
                                                                            AdaptiveCardSchemaKey key,
                                                                            bool isRequired = false);

        std::shared_ptr<BaseActionElement>
        GetAction(ParseContext& context, const Json::Value& json, AdaptiveCardSchemaKey key, bool isRequired = false);

        template<typename T>
        T ExtractJsonValueAndMergeWithDefault(const Json::Value& rootJson,
                                              AdaptiveCardSchemaKey key,
                                              const T& defaultValue,
                                              const std::function<T(const Json::Value&, const T&)>& deserializer);

        std::shared_ptr<BaseActionElement> GetActionFromJsonValue(ParseContext& context, const Json::Value& json);

        void ExpectTypeString(const Json::Value& json, CardElementType bodyType);
        void ExpectTypeString(const Json::Value& json, const std::string& expectedTypeStr);

        // throws if the key is missing or the value mapped to the key is the wrong type
        void ExpectKeyAndValueType(const Json::Value& json, const char* expectedKey, std::function<void(const Json::Value&)> throwIfWrongType);

        std::string ToLowercase(const std::string& value);

        std::shared_ptr<BaseCardElement> GetLabel(ParseContext& context, const Json::Value& json, AdaptiveCardSchemaKey key);

        std::shared_ptr<BaseCardElement> GetLabelFromJsonValue(ParseContext& context, const Json::Value& json);
    };

    template<typename T>
    T ParseUtil::GetEnumValue(const Json::Value& json,
                              AdaptiveCardSchemaKey key,
                              T defaultEnumValue,
                              std::function<T(const std::string& name)> enumConverter,
                              bool isRequired)
    {
        std::string propertyValueStr = "";
        try
        {
            const std::string propertyName = AdaptiveCardSchemaKeyToString(key);
            auto const& propertyValue = json.get(propertyName, Json::Value());
            if (propertyValue.empty())
            {
                if (isRequired)
                {
                    throw AdaptiveCardParseException(ErrorStatusCode::RequiredPropertyMissing,
                                                     "Property is required but was found empty: " + propertyName);
                }
                else
                {
                    return defaultEnumValue;
                }
            }

            if (!propertyValue.isString())
            {
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Enum type was invalid. Expected type string.");
            }

            propertyValueStr = propertyValue.asString();
            return enumConverter(propertyValueStr);
        }
        catch (const std::out_of_range&)
        {
            // TODO: Uncomment and add to warnings instead of throwing.
            // throw AdaptiveCardParseException("Enum type was out of range. Actual: " + propertyValueStr);
            return defaultEnumValue;
        }
    }

    template<typename T>
    std::shared_ptr<T> ParseUtil::GetElementOfType(
        ParseContext& context,
        const Json::Value& json,
        AdaptiveCardSchemaKey key,
        const std::function<std::shared_ptr<T>(ParseContext& context, const Json::Value&)>& V)
    {
        auto el = deserializer(context, json);
        return el;
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> ParseUtil::GetElementCollectionOfSingleType(
        ParseContext& context,
        const Json::Value& json,
        AdaptiveCardSchemaKey key,
        const std::function<std::shared_ptr<T>(ParseContext& context, const Json::Value&)>& deserializer,
        bool isRequired)
    {
        auto elementArray = GetArray(json, key, isRequired);

        std::vector<std::shared_ptr<T>> elements;
        if (elementArray.empty())
        {
            return elements;
        }

        elements.reserve(elementArray.size());

        // Deserialize every element in the array
        for (const Json::Value& curJsonValue : elementArray)
        {
            // Parse the element
            auto el = deserializer(context, curJsonValue);
            if (el != nullptr)
            {
                elements.push_back(el);
            }
        }

        return elements;
    }

    template<typename T>
    T ParseUtil::ExtractJsonValueAndMergeWithDefault(const Json::Value& rootJson,
                                                     AdaptiveCardSchemaKey key,
                                                     const T& defaultValue,
                                                     const std::function<T(const Json::Value&, const T&)>& deserializer)
    {
        auto jsonObject = ParseUtil::ExtractJsonValue(rootJson, key);
        T result = jsonObject.empty() ? defaultValue : deserializer(jsonObject, defaultValue);
        return result;
    }
    
    // Element [de]serialization
    
    // A little template jiu-jitsu here -- given the provided parameters, we need BaseElement::ParseJsonObject to
    // call either BaseCardElement::ParseJsonObject or BaseActionElement::ParseJsonObject.
    template<typename T>
    static void ParseJsonObject(AdaptiveSharedNamespace::ParseContext& context,
                                const Json::Value& json,
                                std::shared_ptr<BaseElement>& baseElement)
    {
        T::ParseJsonObject(context, json, baseElement);
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> ParseUtil::GetElementCollection(bool isTopToBottomContainer,
                                                                    ParseContext& context,
                                                                    const Json::Value& json,
                                                                    AdaptiveCardSchemaKey key,
                                                                    bool isRequired,
                                                                    const std::string& impliedType)
    {
        auto elementArray = GetArray(json, key, isRequired);

        std::vector<std::shared_ptr<T>> elements;
        if (elementArray.empty())
        {
            return std::move(elements);
        }

        const size_t elemSize = elementArray.size();
        elements.reserve(elemSize);

        const ContainerBleedDirection previousBleedState = context.GetBleedDirection();

        size_t currentIndex = 0;
        for (auto& curJsonValue : elementArray)
        {
            ContainerBleedDirection currentBleedState = previousBleedState;

            if (currentIndex != 0)
            {
                // In a top to bottom container (Container, Column) only the first item can bleed up, in a left
                // to right container (ColumnSet) only the first item can bleed left. If we're not the first item,
                // turn off the relevant bit.
                currentBleedState &= isTopToBottomContainer ? ~ContainerBleedDirection::BleedUp : ~ContainerBleedDirection::BleedLeft;
            }

            if (currentIndex != (elemSize - 1))
            {
                // In a top to bottom container (Container, Column) only the last item can bleed down, in a left
                // to right container (ColumnSet) only the last item can bleed right. If we're not the last item,
                // turn off the relevant bit.
                currentBleedState &=
                    isTopToBottomContainer ? ~ContainerBleedDirection::BleedDown : ~ContainerBleedDirection::BleedRight;
            }

            context.PushBleedDirection(currentBleedState);

            // If all items in this collection have the same implied type (i.e. Columns), verify
            // that if set it is set correctly and set it if it isn't
            if (!impliedType.empty())
            {
                const std::string typeString = ParseUtil::GetString(curJsonValue, AdaptiveCardSchemaKey::Type, impliedType, false);
                if (typeString.compare(impliedType) != 0)
                {
                    throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                     "Unable to parse element of type " + typeString);
                }

                curJsonValue[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = typeString;
            }

            std::shared_ptr<BaseElement> curElement;
            ParseJsonObject<T>(context, curJsonValue, curElement);
            elements.push_back(std::static_pointer_cast<T>(curElement));

            // restores the parent's bleed state
            context.PopBleedDirection();

            currentIndex++;
        }

        return std::move(elements);
    }
}
