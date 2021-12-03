// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ParseUtil.h"
#include "RemoteResourceInformation.h"
#include "BaseElement.h"

void HandleUnknownProperties(const Json::Value& json, const std::unordered_set<std::string>& knownProperties, Json::Value& unknownProperties);

namespace AdaptiveCards
{
    class BaseActionElement : public BaseElement
    {
    public:
        BaseActionElement(ActionType type);

        BaseActionElement() = default;
        BaseActionElement(const BaseActionElement&) = default;
        BaseActionElement(BaseActionElement&&) = default;
        BaseActionElement& operator=(const BaseActionElement&) = default;
        BaseActionElement& operator=(BaseActionElement&&) = default;
        ~BaseActionElement() = default;

        const std::string& GetTitle() const;

        virtual void SetTitle(std::string&& value);
        virtual void SetTitle(const std::string& value);

        const std::string& GetIconUrl() const;

        void SetIconUrl(std::string&& value);
        void SetIconUrl(const std::string& value);

        const std::string& GetStyle() const;

        void SetStyle(std::string&& value);
        void SetStyle(const std::string& value);

        const std::string& GetTooltip() const;

        virtual void SetTooltip(std::string&& value);
        virtual void SetTooltip(const std::string& value);

        ActionType GetElementType() const;

        Mode GetMode() const;
        void SetMode(const Mode mode);

        bool GetIsEnabled() const;
        void SetIsEnabled(const bool isEnabled);

        void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceUris) override;
        Json::Value SerializeToJsonValue() const override;

        template<typename T> static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& json);

        static std::shared_ptr<BaseActionElement> DeserializeBasePropertiesFromString(ParseContext& context,
                                                                                      const std::string& jsonString);
        static std::shared_ptr<BaseActionElement> DeserializeBaseProperties(ParseContext& context, const Json::Value& json);

        static void ParseJsonObject(AdaptiveCards::ParseContext& context, const Json::Value& json, std::shared_ptr<BaseElement>& element);

    private:
        void PopulateKnownPropertiesSet();
        static void DeserializeBaseProperties(ParseContext& context, const Json::Value& json, std::shared_ptr<BaseActionElement>& element);

        static constexpr const char* const defaultStyle = "default";

        std::string m_title;
        std::string m_iconUrl;
        std::string m_style;
        std::string m_tooltip;

        bool m_isEnabled;

        ActionType m_type;
        Mode m_mode;
    };

    template<typename T>
    std::shared_ptr<T> BaseActionElement::Deserialize(ParseContext& context, const Json::Value& json)
    {
        std::shared_ptr<T> cardElement = std::make_shared<T>();
        std::shared_ptr<BaseActionElement> baseActionElement = std::static_pointer_cast<BaseActionElement>(cardElement);
        DeserializeBaseProperties(context, json, baseActionElement);

        // Walk all properties and put any unknown ones in the additional properties json
        HandleUnknownProperties(json, baseActionElement->m_knownProperties, baseActionElement->m_additionalProperties);

        return cardElement;
    }
}
