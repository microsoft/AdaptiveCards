// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class UnknownElement : public BaseCardElement
{
public:
    UnknownElement();
    Json::Value SerializeToJsonValue() const override;
};

class UnknownElementParser : public BaseCardElementParser
{
public:
    UnknownElementParser() = default;
    UnknownElementParser(const UnknownElementParser&) = default;
    UnknownElementParser(UnknownElementParser&&) = default;
    UnknownElementParser& operator=(const UnknownElementParser&) = default;
    UnknownElementParser& operator=(UnknownElementParser&&) = default;
    virtual ~UnknownElementParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
