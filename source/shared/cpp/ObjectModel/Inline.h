// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"

namespace AdaptiveSharedNamespace
{
    class Inline
    {
    public:
        Inline(InlineElementType type);
        Inline() = default;
        Inline(const Inline&) = default;
        Inline(Inline&&) = default;
        Inline& operator=(const Inline&) = default;
        Inline& operator=(Inline&&) = default;
        virtual ~Inline() = default;

        virtual Json::Value SerializeToJsonValue() const;

        // Element type
        virtual InlineElementType GetInlineType() const;
        std::string GetInlineTypeString() const;

        static std::shared_ptr<Inline> Deserialize(ParseContext& context, const Json::Value& root);

        Json::Value GetAdditionalProperties() const;
        void SetAdditionalProperties(Json::Value&& additionalProperties);
        void SetAdditionalProperties(const Json::Value& additionalProperties);

    protected:
        void PopulateKnownPropertiesSet();
        std::unordered_set<std::string> m_knownProperties;
        Json::Value m_additionalProperties;

    private:
        InlineElementType m_type;
    };
}
