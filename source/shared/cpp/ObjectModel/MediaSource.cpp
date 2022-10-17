// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "MediaSource.h"

using namespace AdaptiveCards;

std::shared_ptr<MediaSource> MediaSourceParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<MediaSource> mediaSource = ContentSource::Deserialize<MediaSource>(context, json);

    return mediaSource;
}

std::shared_ptr<MediaSource> MediaSourceParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return MediaSourceParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
