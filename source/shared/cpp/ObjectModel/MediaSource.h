// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ContentSource.h"

namespace AdaptiveCards
{
class MediaSource : public ContentSource
{
};

class MediaSourceParser
{
public:
    static std::shared_ptr<MediaSource> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<MediaSource> DeserializeFromString(ParseContext& context, const std::string& jsonString);
};
} // namespace AdaptiveCards
