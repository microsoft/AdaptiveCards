#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"

namespace AdaptiveCards
{
class Container;
class BaseCardElement
{
public:
    BaseCardElement(CardElementType type, std::shared_ptr<Container> parent, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak);
    BaseCardElement(CardElementType type);

    virtual ~BaseCardElement();

    std::shared_ptr<Container> GetParent() const;
    void SetContainer(std::shared_ptr<Container> container);

    HorizontalAlignment GetHorizontalAlignment() const;
    void SetHorizontalAlignment(const HorizontalAlignment value);

    CardElementSize GetSize() const;
    void SetSize(const CardElementSize value);

    std::string GetSpeak() const;
    void SetSpeak(const std::string value);

    const CardElementType GetElementType() const;

    virtual std::string Serialize() = 0;

    template <typename T>
    static std::shared_ptr<T> Deserialize(const Json::Value& json);

private:
    std::weak_ptr<Container> m_parent;
    HorizontalAlignment m_horizontalAlignment;
    CardElementSize m_size;
    std::string m_speak;
    CardElementType m_type;
};

template <typename T>
std::shared_ptr<T> BaseCardElement::Deserialize(const Json::Value& json)
{
    std::shared_ptr<T> cardElement = std::make_shared<T>();
    std::shared_ptr<BaseCardElement> baseCardElement = cardElement;

    ParseUtil::ThrowIfNotJsonObject(json);

    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);
    baseCardElement->SetSpeak(speak);

    CardElementSize size = ParseUtil::GetEnumValue<CardElementSize>(json, AdaptiveCardSchemaKey::CardElementSize, CardElementSize::Auto, SizeFromString);
    baseCardElement->SetSize(size);

    HorizontalAlignment horAlignment = ParseUtil::GetEnumValue<HorizontalAlignment>(json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString);
    baseCardElement->SetHorizontalAlignment(horAlignment);

    return cardElement;
}


}

