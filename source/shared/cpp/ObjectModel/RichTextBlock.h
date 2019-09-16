// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include "Inline.h"

namespace AdaptiveSharedNamespace
{
    class RichTextBlock : public BaseCardElement
    {
        friend class RichTextBlockParser;

    public:
        RichTextBlock();
        RichTextBlock(const RichTextBlock&) = default;
        RichTextBlock(RichTextBlock&&) = default;
        RichTextBlock& operator=(const RichTextBlock&) = default;
        RichTextBlock& operator=(RichTextBlock&&) = default;
        ~RichTextBlock() = default;

        Json::Value SerializeToJsonValue() const override;

        HorizontalAlignment GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const HorizontalAlignment value);

        std::vector<std::shared_ptr<Inline>>& GetInlines();
        const std::vector<std::shared_ptr<Inline>>& GetInlines() const;

    private:
        HorizontalAlignment m_hAlignment;
        void PopulateKnownPropertiesSet() override;

        std::vector<std::shared_ptr<Inline>> m_inlines;
    };

    class RichTextBlockParser : public BaseCardElementParser
    {
    public:
        RichTextBlockParser() = default;
        RichTextBlockParser(const RichTextBlockParser&) = default;
        RichTextBlockParser(RichTextBlockParser&&) = default;
        RichTextBlockParser& operator=(const RichTextBlockParser&) = default;
        RichTextBlockParser& operator=(RichTextBlockParser&&) = default;
        virtual ~RichTextBlockParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
