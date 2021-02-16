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
        virtual ~RichTextElementProperties() = default;

        bool GetItalic() const;
        void SetItalic(const bool value);

        bool GetStrikethrough() const;
        void SetStrikethrough(const bool value);

        bool GetUnderline() const;
        void SetUnderline (const bool value);

        Json::Value SerializeToJsonValue(Json::Value& root) const override;
        void Deserialize(ParseContext& context, const Json::Value& root) override;
        void PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties) override;

    private:
        bool m_italic;
        bool m_strikethrough;
        bool m_underline;
    };
}
