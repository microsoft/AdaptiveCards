// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseContext.h"
#include "RichTextElementProperties.h"

using namespace AdaptiveSharedNamespace;
RichTextElementProperties::RichTextElementProperties() : TextElementProperties()
{
}

RichTextElementProperties::RichTextElementProperties(const TextConfig& config, const std::string& text, const std::string& language) :
    TextElementProperties(config, text, language)
{
}

Json::Value RichTextElementProperties::SerializeToJsonValue(Json::Value& root) const
{
    (void)TextElementProperties::SerializeToJsonValue(root);
    if (GetItalic())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Italic)] = true;
    }

    if (GetStrikethrough())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Strikethrough)] = true;
    }

    return root;
}

void RichTextElementProperties::Deserialize(const ParseContext& context, const Json::Value& json)
{
    TextElementProperties::Deserialize(context, json);
    SetItalic(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Italic, false));
    SetStrikethrough(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Strikethrough, false));
}

void RichTextElementProperties::PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties)
{
    TextElementProperties::PopulateKnownPropertiesSet(knownProperties);
    knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Italic),
                            AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Strikethrough)});
}
