// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CaptionSource.h"

using namespace AdaptiveCards;

std::string CaptionSource::GetLabel() const
{
    return m_label;
}

void CaptionSource::SetLabel(const std::string& value)
{
    m_label = value;
}

std::shared_ptr<CaptionSource> CaptionSourceParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<CaptionSource> captionSource = std::make_shared<CaptionSource>();

    captionSource->SetMimeType(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MimeType, false));
    captionSource->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, false));
    captionSource->SetLabel(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Label, false));

    return captionSource;
}

std::shared_ptr<CaptionSource> CaptionSourceParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return CaptionSourceParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
