#include "BaseCardElement.h"
#include "HttpAction.h"
#include "ShowCardAction.h"
#include "OpenUrlAction.h"
#include "SubmitAction.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

const std::unordered_map<ActionType, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>, EnumHash> BaseCardElement::ActionParsers =
{
    { ActionType::Http, HttpAction::Deserialize },
    { ActionType::OpenUrl, OpenUrlAction::Deserialize },
    { ActionType::ShowCard, ShowCardAction::Deserialize },
    { ActionType::Submit, SubmitAction::Deserialize },
};

BaseCardElement::BaseCardElement(
    CardElementType type,
    SeparationStyle separationStyle,
    std::string speak) :
    m_type(type),
    m_separationStyle(separationStyle),
    m_speak(speak)
{
}

BaseCardElement::BaseCardElement(CardElementType type) :
    m_type(type), m_separationStyle(SeparationStyle::Default), m_speak("")
{
}

AdaptiveCards::BaseCardElement::~BaseCardElement()
{
}

SeparationStyle BaseCardElement::GetSeparationStyle() const
{
    return m_separationStyle;
}

void BaseCardElement::SetSeparationStyle(const SeparationStyle value)
{
    m_separationStyle = value;
}

std::string BaseCardElement::GetSpeak() const
{
    return m_speak;
}

void BaseCardElement::SetSpeak(const std::string value)
{
    m_speak = value;
}

const CardElementType AdaptiveCards::BaseCardElement::GetElementType() const
{
    return m_type;
}

Json::Value BaseCardElement::SerializeToJsonValue()
 {
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = CardElementTypeToString(GetElementType());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Speak)] = GetSpeak();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Separation)] = SeparationStyleToString(GetSeparationStyle());
    return root;
}

std::shared_ptr<BaseActionElement> BaseCardElement::DeserializeSelectAction(const Json::Value & json, AdaptiveCardSchemaKey key)
{
    Json::Value selectActionValue = ParseUtil::ExtractJsonValue(json, key, false);
    if (!selectActionValue.empty())
    {
        return ParseUtil::GetActionFromJsonValue<BaseActionElement>(selectActionValue, BaseCardElement::ActionParsers);
    }
    return nullptr;
}

Json::Value BaseCardElement::SerializeSelectAction(const std::shared_ptr<BaseActionElement> selectAction)
{
    if (selectAction != nullptr)
    {
        return selectAction->SerializeToJsonValue();
    }
    return Json::Value();
}
