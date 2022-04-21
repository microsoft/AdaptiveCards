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
    Json::Value SerializeToJsonValue() const override;

    std::string GetLabel() const;
    void SetLabel(const std::string& value);

private:
    std::string m_label;
};

class CaptionSourceParser
{
public:
    static std::shared_ptr<CaptionSource> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<CaptionSource> DeserializeFromString(ParseContext& context, const std::string& jsonString);
};
} // namespace AdaptiveCards
