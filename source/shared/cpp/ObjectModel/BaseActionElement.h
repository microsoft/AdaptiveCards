#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"
#include "ParseUtil.h"
#include "RemoteResourceInformation.h"

namespace AdaptiveSharedNamespace
{
    class BaseActionElement
    {
    public:
        BaseActionElement(ActionType type);

        BaseActionElement(const BaseActionElement&) = default;
        BaseActionElement(BaseActionElement&&) = default;
        BaseActionElement& operator=(const BaseActionElement&) = default;
        BaseActionElement& operator=(BaseActionElement&&) = default;
        virtual ~BaseActionElement() = default;

        virtual std::string GetElementTypeString() const;
        virtual void SetElementTypeString(const std::string& value);

        virtual std::string GetTitle() const;
        virtual void SetTitle(const std::string& value);

        virtual std::string GetId() const;
        virtual void SetId(const std::string& value);

        virtual std::string GetIconUrl() const;
        virtual void SetIconUrl(const std::string& value);

        virtual std::string GetSentiment() const;
        virtual void SetSentiment(const std::string& value);

        virtual const ActionType GetElementType() const;

        std::string Serialize() const;
        virtual Json::Value SerializeToJsonValue() const;

        template<typename T> static std::shared_ptr<T> Deserialize(const Json::Value& json);

        Json::Value GetAdditionalProperties() const;
        void SetAdditionalProperties(Json::Value const& additionalProperties);

        virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceUris);

    private:
        virtual void PopulateKnownPropertiesSet();

        ActionType m_type;
        std::string m_typeString;
        std::string m_title;
        std::string m_id;
        std::string m_iconUrl;
        std::string m_sentiment;
        Json::Value m_additionalProperties;
        static constexpr const char defaultSentiment[] = "default";
        
    protected:
        std::unordered_set<std::string> m_knownProperties;
    };

    template<typename T> std::shared_ptr<T> BaseActionElement::Deserialize(const Json::Value& json)
    {
        std::shared_ptr<T> cardElement = std::make_shared<T>();
        std::shared_ptr<BaseActionElement> baseActionElement = cardElement;

        ParseUtil::ThrowIfNotJsonObject(json);

        baseActionElement->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title));
        baseActionElement->SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id));
        baseActionElement->SetIconUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::IconUrl));
        baseActionElement->SetSentiment(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Sentiment, defaultSentiment, false));

        // Walk all properties and put any unknown ones in the additional properties json
        for (auto it = json.begin(); it != json.end(); ++it)
        {
            std::string key = it.key().asCString();
            if (baseActionElement->m_knownProperties.find(key) == baseActionElement->m_knownProperties.end())
            {
                baseActionElement->m_additionalProperties[key] = *it;
            }
        }
        return cardElement;
    }
}
