// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ContentSource.h"

namespace AdaptiveCards
{
class CaptionSource : public ContentSource
{
public:
    std::string GetLanguage() const;
    void SetLanguage(const std::string& value);

private:
    std::string m_language;
};

class CaptionSourceParser
{
public:
    static std::shared_ptr<CaptionSource> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<CaptionSource> DeserializeFromString(ParseContext& context, const std::string& jsonString);
};
} // namespace AdaptiveCards
