// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CaptionSource.h"

using namespace AdaptiveCards;

Json::Value CaptionSource::SerializeToJsonValue() const
{
    auto root = ContentSource::SerializeToJsonValue();
    if (!m_label.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Label)] = m_label;
    }

    return root;
}

std::string CaptionSource::GetLabel() const
{
    return m_label;
}

void CaptionSource::SetLabel(const std::string& value)
{
    m_label = value;
}

std::shared_ptr<CaptionSource> CaptionSourceParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<CaptionSource> captionSource = ContentSource::Deserialize<CaptionSource>(context, json);

    captionSource->SetLabel(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Label, false));

    return captionSource;
}

std::shared_ptr<CaptionSource> CaptionSourceParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return CaptionSourceParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
