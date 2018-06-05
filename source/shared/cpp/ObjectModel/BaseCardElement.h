#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"
#include "BaseActionElement.h"
#include "ParseUtil.h"
#include "Separator.h"

namespace AdaptiveSharedNamespace {
class Container;
class BaseCardElement
{
public:
    BaseCardElement(CardElementType type, Spacing spacing, bool separator, HeightType height);
    BaseCardElement(CardElementType type);

    virtual ~BaseCardElement();

    virtual std::string GetElementTypeString() const;
    virtual void SetElementTypeString(const std::string &value);

    virtual bool GetSeparator() const;
    virtual void SetSeparator(const bool value);

    HeightType GetHeight() const;
    void SetHeight(const HeightType value);

    virtual Spacing GetSpacing() const;
    virtual void SetSpacing(const Spacing value);

    virtual std::string GetId() const;
    virtual void SetId(const std::string &value);

    virtual const CardElementType GetElementType() const;

    std::string Serialize() const;
    virtual Json::Value SerializeToJsonValue() const;

    template <typename T>
    static std::shared_ptr<T> Deserialize(const Json::Value& json);

    Json::Value GetAdditionalProperties() const;
    void SetAdditionalProperties(const Json::Value &additionalProperties);

    virtual void GetResourceUris(std::vector<std::string>& resourceUris);

protected:
    static Json::Value SerializeSelectAction(const std::shared_ptr<BaseActionElement> selectAction);

    std::unordered_set<std::string> m_knownProperties;

private:
    void PopulateKnownPropertiesSet();

    CardElementType m_type;
    Spacing m_spacing;
    std::string m_id;
    std::string m_typeString;
    bool m_separator;
    Json::Value m_additionalProperties;
    HeightType m_height;
};

template <typename T>
std::shared_ptr<T> BaseCardElement::Deserialize(const Json::Value& json)
{
    std::shared_ptr<T> cardElement = std::make_shared<T>();
    std::shared_ptr<BaseCardElement> baseCardElement = cardElement;

    ParseUtil::ThrowIfNotJsonObject(json);

    baseCardElement->SetSpacing(
            ParseUtil::GetEnumValue<Spacing>(json, AdaptiveCardSchemaKey::Spacing, Spacing::Default, SpacingFromString));
    baseCardElement->SetSeparator(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Separator, false));
    baseCardElement->SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id));
    baseCardElement->SetHeight(
        ParseUtil::GetEnumValue<HeightType>(json, AdaptiveCardSchemaKey::Height, HeightType::Auto, HeightTypeFromString));

    // Walk all properties and put any unknown ones in the additional properties json
    for (Json::Value::const_iterator it = json.begin(); it != json.end(); it++)
    {
        std::string key = it.key().asCString();
        if (baseCardElement->m_knownProperties.find(key) == baseCardElement->m_knownProperties.end())
        {
            baseCardElement->m_additionalProperties[key] = *it;
        }
    }

    return cardElement;
}
}
