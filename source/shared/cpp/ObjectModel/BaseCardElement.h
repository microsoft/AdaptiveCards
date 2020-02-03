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
        virtual void SetSeparator(const bool value);

        HeightType GetHeight() const;
        void SetHeight(const HeightType value);

        virtual Spacing GetSpacing() const;
        virtual void SetSpacing(const Spacing value);

        virtual bool GetIsVisible() const;
        virtual void SetIsVisible(const bool value);

        virtual CardElementType GetElementType() const;

        template<typename T> static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& json);

        static void ParseJsonObject(AdaptiveSharedNamespace::ParseContext& context, const Json::Value& json, std::shared_ptr<BaseElement>& element);

    protected:
        static Json::Value SerializeSelectAction(const std::shared_ptr<BaseActionElement> selectAction);
        void PopulateKnownPropertiesSet();

    private:
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

        ParseUtil::ThrowIfNotJsonObject(json);

        baseCardElement->DeserializeBase<BaseCardElement>(context, json);
        baseCardElement->SetCanFallbackToAncestor(context.GetCanFallbackToAncestor());
        baseCardElement->SetHeight(
            ParseUtil::GetEnumValue<HeightType>(json, AdaptiveCardSchemaKey::Height, HeightType::Auto, HeightTypeFromString));
        baseCardElement->SetIsVisible(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsVisible, true));
        baseCardElement->SetSeparator(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Separator, false));
        baseCardElement->SetSpacing(
            ParseUtil::GetEnumValue<Spacing>(json, AdaptiveCardSchemaKey::Spacing, Spacing::Default, SpacingFromString));

        // Walk all properties and put any unknown ones in the additional properties json
        HandleUnknownProperties(json, baseCardElement->m_knownProperties, baseCardElement->m_additionalProperties);

        return cardElement;
    }
}
