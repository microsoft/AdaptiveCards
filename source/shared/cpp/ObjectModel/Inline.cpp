// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Inline.h"
#include "TextRun.h"

using namespace AdaptiveSharedNamespace;

Inline::Inline(InlineElementType type) : m_type(type)
{
    PopulateKnownPropertiesSet();
}

Json::Value Inline::SerializeToJsonValue() const
{
    Json::Value root = Json::Value();

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = GetInlineTypeString();

    return root;
}

InlineElementType Inline::GetInlineType() const
{
    return m_type;
}

std::string Inline::GetInlineTypeString() const
{
    return InlineElementTypeToString(m_type);
}

Json::Value Inline::GetAdditionalProperties() const
{
    return m_additionalProperties;
}

void Inline::SetAdditionalProperties(Json::Value const& value)
{
    m_additionalProperties = value;
}

std::shared_ptr<Inline> Inline::Deserialize(ParseContext& context, const Json::Value& json)
{
    // Currently TextRuns are the only supported Inline
    return TextRun::Deserialize(context, json);
}

void Inline::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)});
}
