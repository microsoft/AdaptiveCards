#include "pch.h"
#include "BaseCardElement.h"
#include "ShowCardAction.h"
#include "OpenUrlAction.h"
#include "ParseUtil.h"
#include "SubmitAction.h"

using namespace AdaptiveSharedNamespace;

BaseCardElement::BaseCardElement(
    CardElementType type,
    Spacing spacing,
    bool separator) :
    m_type(type),
    m_spacing(spacing),
    m_separator(separator),
    m_typeString(CardElementTypeToString(type))
{
    PopulateKnownPropertiesSet();
}

BaseCardElement::BaseCardElement(CardElementType type) :
    m_type(type), m_spacing(Spacing::Default), m_typeString(CardElementTypeToString(type))
{
    PopulateKnownPropertiesSet();
}

void BaseCardElement::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Spacing));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Separator));
}

BaseCardElement::~BaseCardElement()
{
}

std::string BaseCardElement::GetElementTypeString() const
{
    return m_typeString;
}

void BaseCardElement::SetElementTypeString(const std::string value)
{
    m_typeString = value;
}

bool BaseCardElement::GetSeparator() const
{
    return m_separator;
}

void BaseCardElement::SetSeparator(const bool value)
{
    m_separator = value;
}

Spacing BaseCardElement::GetSpacing() const
{
    return m_spacing;
}

void BaseCardElement::SetSpacing(const Spacing value)
{
    m_spacing = value;
}

std::string BaseCardElement::GetId() const
{
    return m_id;
}

void BaseCardElement::SetId(const std::string value)
{
    m_id = value;
}

const CardElementType BaseCardElement::GetElementType() const
{
    return m_type;
}

std::string BaseCardElement::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value BaseCardElement::SerializeToJsonValue()
 {
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = CardElementTypeToString(GetElementType());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Spacing)] = SpacingToString(GetSpacing());
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Separator)] = GetSeparator();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id)] = GetId();

    return root;
}

std::shared_ptr<BaseActionElement> BaseCardElement::DeserializeSelectAction(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& json,
    AdaptiveCardSchemaKey key)
{
    Json::Value selectActionValue = ParseUtil::ExtractJsonValue(json, key, false);
    if (!selectActionValue.empty())
    {
        return ParseUtil::GetActionFromJsonValue(elementParserRegistration, actionParserRegistration, selectActionValue);
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

Json::Value BaseCardElement::GetAdditionalProperties()
{
    return m_additionalProperties;
}

void BaseCardElement::SetAdditionalProperties(Json::Value value)
{
    m_additionalProperties = value;
}

void BaseCardElement::GetResourceUris(std::vector<std::string>&)
{
    return;
}