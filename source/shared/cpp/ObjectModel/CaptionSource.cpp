// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CaptionSource.h"

using namespace AdaptiveCards;

std::shared_ptr<CaptionSource> CaptionSourceParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<CaptionSource> captionSource = std::make_shared<CaptionSource>();

    captionSource->SetMimeType(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MimeType, false));
    captionSource->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, false));

    return captionSource;
}

std::shared_ptr<CaptionSource> CaptionSourceParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return CaptionSourceParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
