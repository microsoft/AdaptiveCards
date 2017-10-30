#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"
#include "BaseActionElement.h"
#include "ParseUtil.h"
#include "Separator.h"

namespace AdaptiveCards
{
class Container;
class BaseCardElement
{
public:
    BaseCardElement(CardElementType type, Spacing spacing, bool separator);
    BaseCardElement(CardElementType type);

    virtual ~BaseCardElement();

    /* Issue #629 to make separator an object
    std::shared_ptr<Separator> GetSeparator() const;
    void SetSeparator(const std::shared_ptr<Separator> value);
    */

    virtual bool GetSeparator() const;
    virtual void SetSeparator(const bool value);

    virtual Spacing GetSpacing() const;
    virtual void SetSpacing(const Spacing value);

    virtual std::string GetId() const;
    virtual void SetId(const std::string value);

    virtual const CardElementType GetElementType() const;

    std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

    template <typename T>
    static std::shared_ptr<T> Deserialize(const Json::Value& json);

    static std::shared_ptr<AdaptiveCards::BaseActionElement> DeserializeSelectAction(
        std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration, 
        const Json::Value& json, AdaptiveCardSchemaKey key);

protected:
    static Json::Value SerializeSelectAction(const std::shared_ptr<BaseActionElement> selectAction);

private:
    static const std::unordered_map<ActionType, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>, EnumHash> ActionParsers;
    CardElementType m_type;
    Spacing m_spacing;
    std::string m_id;
    //std::shared_ptr<Separator> m_separator; Issue #629 to make separator an object
    bool m_separator;
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
  
    /* Issue #629 to make separator an object
    Json::Value separatorJson = json.get(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Separator), Json::Value());
    if (!separatorJson.empty())
    {
        baseCardElement->SetSeparator(Separator::Deserialize(separatorJson));
    }
    */

    return cardElement;
}
}
