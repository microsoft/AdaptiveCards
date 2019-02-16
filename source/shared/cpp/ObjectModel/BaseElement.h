#pragma once

#include "pch.h"
#include "json/json.h"
#include "ParseContext.h"
#include "ParseUtil.h"
#include "SemanticVersion.h"
#include "RemoteResourceInformation.h"

namespace AdaptiveSharedNamespace
{
    // Used to uniquely identify a single BaseElement-derived object through the course of deserializing. For more
    // details, refer to the giant comment on ID collision detection in ParseContext.cpp.
    class InternalId
    {
    public:
        InternalId();

        static InternalId Next();
        static InternalId Current();
        static constexpr unsigned int Invalid = 0;

        bool operator==(const unsigned int other) const { return m_internalId == other; }
        bool operator!=(const unsigned int other) const { return m_internalId != other; }
        bool operator==(const InternalId& other) const { return m_internalId == other.m_internalId; }
        bool operator!=(const InternalId& other) const { return m_internalId != other.m_internalId; }

    private:
        static unsigned int s_currentInternalId;
        InternalId(const unsigned int id);
        unsigned int m_internalId;
    };

    class BaseElement
    {
    public:
        BaseElement() :
            m_additionalProperties{}, m_typeString{}, m_requires(0), m_fallbackContent(nullptr),
            m_fallbackType(FallbackType::None), m_id{}, m_internalId{InternalId::Current()}
        {
            PopulateKnownPropertiesSet();
        }

        BaseElement(const BaseElement&) = default;
        BaseElement(BaseElement&&) = default;
        BaseElement& operator=(const BaseElement&) = default;
        BaseElement& operator=(BaseElement&&) = default;
        virtual ~BaseElement() = default;

        // Element type and identity
        std::string GetElementTypeString() const;
        void SetElementTypeString(const std::string& value);
        virtual std::string GetId() const;
        virtual void SetId(const std::string& value);

        const InternalId GetInternalId() const { return m_internalId; }

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

        template<typename T> void DeserializeBase(ParseContext& context, const Json::Value& json);

        virtual std::string Serialize() const;
        virtual Json::Value SerializeToJsonValue() const;
        Json::Value GetAdditionalProperties() const;
        void SetAdditionalProperties(const Json::Value& additionalProperties);

        // Fallback and Requires support
        FallbackType GetFallbackType() const { return m_fallbackType; }
        std::shared_ptr<BaseElement> GetFallbackContent() const { return m_fallbackContent; }

        bool MeetsRequirements(const std::unordered_map<std::string, std::string>& hostProvides) const;

        // Misc.
        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceUris);

    protected:
        virtual void PopulateKnownPropertiesSet();
        void SetTypeString(const std::string& type) { m_typeString = type; }
        std::string m_typeString;
        std::unordered_set<std::string> m_knownProperties;
        Json::Value m_additionalProperties;

    private:
        template<typename T> void ParseFallback(ParseContext& context, const Json::Value& json);
        void ParseRequires(ParseContext& context, const Json::Value& json);

        std::unordered_map<std::string, SemanticVersion> m_requires;
        std::shared_ptr<BaseElement> m_fallbackContent;
        InternalId m_internalId;
        FallbackType m_fallbackType;
        std::string m_id;
    };

    template<typename T> void BaseElement::DeserializeBase(ParseContext& context, const Json::Value& json)
    {
        ParseUtil::ThrowIfNotJsonObject(json);

        // Order matters here -- we need to set the id property *prior* to parsing fallback so that we can detect id
        // collisions.
        SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id));
        ParseFallback<T>(context, json);
        ParseRequires(context, json);
    }

    template<typename T> void BaseElement::ParseFallback(ParseContext& context, const Json::Value& json)
    {
        const auto fallbackValue = ParseUtil::ExtractJsonValue(json, AdaptiveCardSchemaKey::Fallback, false);
        if (!fallbackValue.empty())
        {
            // Two possible valid json values for fallback -- either the string "drop", or a valid Adaptive Card
            // element.
            if (fallbackValue.isString())
            {
                auto fallbackStringValue = ParseUtil::ToLowercase(fallbackValue.asString());
                if (fallbackStringValue == "drop")
                {
                    m_fallbackType = FallbackType::Drop;
                    return;
                }
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                 "The only valid string value for the fallback property is 'drop'.");
            }
            else if (fallbackValue.isObject())
            {
                // fallback value is a JSON object. parse it and add it as fallback content. For more details, refer to
                // the giant comment on ID collision detection in ParseContext.cpp.
                context.PushElement(GetId(), GetInternalId(), true /*isFallback*/);
                std::shared_ptr<BaseElement> fallbackElement;
                T::ParseJsonObject(context, fallbackValue, fallbackElement);
                context.PopElement();

                if (fallbackElement)
                {
                    m_fallbackType = FallbackType::Content;
                    m_fallbackContent = fallbackElement;
                    return;
                }
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Fallback content did not parse correctly.");
            }
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Invalid value for fallback");
        }
    }
}
