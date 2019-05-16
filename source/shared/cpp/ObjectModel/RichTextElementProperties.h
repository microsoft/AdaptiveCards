// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextElementProperties.h"

namespace AdaptiveSharedNamespace
{
    class RichTextElementProperties : public TextElementProperties
    {
    public:
        RichTextElementProperties();
        RichTextElementProperties(const TextConfig&, const std::string&, const std::string&);
        RichTextElementProperties(const RichTextElementProperties&) = default;
        RichTextElementProperties(RichTextElementProperties&&) = default;
        RichTextElementProperties& operator=(const RichTextElementProperties&) = default;
        RichTextElementProperties& operator=(RichTextElementProperties&&) = default;
        ~RichTextElementProperties() = default;

        Json::Value SerializeToJsonValue(Json::Value& root) const override;
        void Deserialize(const ParseContext& context, const Json::Value& root) override;
        void PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties) override;
    };
}
