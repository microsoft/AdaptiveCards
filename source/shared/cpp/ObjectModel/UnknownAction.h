// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class UnknownAction : public BaseActionElement
    {
    public:
        UnknownAction();
        Json::Value SerializeToJsonValue() const override;
    };

    class UnknownActionParser : public ActionElementParser
    {
    public:
        UnknownActionParser() = default;
        UnknownActionParser(const UnknownActionParser&) = default;
        UnknownActionParser(UnknownActionParser&&) = default;
        UnknownActionParser& operator=(const UnknownActionParser&) = default;
        UnknownActionParser& operator=(UnknownActionParser&&) = default;
        virtual ~UnknownActionParser() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
