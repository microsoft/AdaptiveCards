// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "MediaSource.h"

using namespace AdaptiveCards;

std::shared_ptr<MediaSource> MediaSourceParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<MediaSource> mediaSource = std::make_shared<MediaSource>();

    mediaSource->SetMimeType(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MimeType, false));
    mediaSource->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, false));

    return mediaSource;
}

std::shared_ptr<MediaSource> MediaSourceParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return MediaSourceParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
