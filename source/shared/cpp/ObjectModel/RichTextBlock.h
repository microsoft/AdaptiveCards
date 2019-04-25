#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include "Paragraph.h"

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

        bool GetWrap() const;
        void SetWrap(const bool value);

        unsigned int GetMaxLines() const;
        void SetMaxLines(const unsigned int value);

        HorizontalAlignment GetHorizontalAlignment() const;
        void SetHorizontalAlignment(const HorizontalAlignment value);

        std::vector<std::shared_ptr<Paragraph>>& GetParagraphs();
        const std::vector<std::shared_ptr<Paragraph>>& GetParagraphs() const;

    private:
        bool m_wrap;
        unsigned int m_maxLines;
        HorizontalAlignment m_hAlignment;
        void PopulateKnownPropertiesSet() override;

        std::vector<std::shared_ptr<Paragraph>> m_paragraphs;
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
