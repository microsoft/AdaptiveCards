// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "BaseElement.h"
#include "ElementParserRegistration.h"
#include "Separator.h"
#include "RemoteResourceInformation.h"

void HandleUnknownProperties(const Json::Value& json, const std::unordered_set<std::string>& knownProperties, Json::Value& unknownProperties);

namespace AdaptiveSharedNamespace
{
    class BaseCardElement : public BaseElement
    {
    public:
        BaseCardElement(CardElementType type, Spacing spacing, bool separator, HeightType height);
        BaseCardElement(CardElementType type);

        BaseCardElement() = default;
        BaseCardElement(const BaseCardElement&) = default;
        BaseCardElement(BaseCardElement&&) = default;
        BaseCardElement& operator=(const BaseCardElement&) = default;
        BaseCardElement& operator=(BaseCardElement&&) = default;
        ~BaseCardElement() = default;

        Json::Value SerializeToJsonValue() const override;

        virtual bool GetSeparator() const;
        virtual void SetSeparator(bool value);

        HeightType GetHeight() const;
        void SetHeight(HeightType value);

        virtual Spacing GetSpacing() const;
        virtual void SetSpacing(Spacing value);

        bool GetIsVisible() const;
        void SetIsVisible(bool value);

        CardElementType GetElementType() const;

        static std::shared_ptr<BaseCardElement> DeserializeBasePropertiesFromString(ParseContext& context, const std::string& jsonString);
        static std::shared_ptr<BaseCardElement> DeserializeBaseProperties(ParseContext& context, const Json::Value& json);       

        template<typename T> static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& json);

        static void ParseJsonObject(AdaptiveSharedNamespace::ParseContext& context, const Json::Value& json, std::shared_ptr<BaseElement>& element);

    protected:
        static Json::Value SerializeSelectAction(const std::shared_ptr<BaseActionElement>& selectAction);

    private:
        void PopulateKnownPropertiesSet();
        static void DeserializeBaseProperties(ParseContext& context, const Json::Value& json, std::shared_ptr<BaseCardElement>& element);

        CardElementType m_type;
        Spacing m_spacing;
        HeightType m_height;
        bool m_separator;
        bool m_isVisible;
    };

    template<typename T> std::shared_ptr<T> BaseCardElement::Deserialize(ParseContext& context, const Json::Value& json)
    {
        std::shared_ptr<T> cardElement = std::make_shared<T>();
        std::shared_ptr<BaseCardElement> baseCardElement = std::static_pointer_cast<BaseCardElement>(cardElement);
        DeserializeBaseProperties(context, json, baseCardElement);

        // Walk all properties and put any unknown ones in the additional properties json
        HandleUnknownProperties(json, baseCardElement->m_knownProperties, baseCardElement->m_additionalProperties);

        return cardElement;
    }
}
