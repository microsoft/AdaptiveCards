// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"
#include "HostConfig.h"

namespace AdaptiveSharedNamespace
{
    class TextElementProperties
    {
    public:
        TextElementProperties();
        TextElementProperties(const TextConfig &, const std::string &, const std::string &);
        TextElementProperties(const TextElementProperties&) = default;
        TextElementProperties(TextElementProperties&&) = default;
        TextElementProperties& operator=(const TextElementProperties&) = default;
        TextElementProperties& operator=(TextElementProperties&&) = default;
        ~TextElementProperties() = default;

        Json::Value SerializeToJsonValue(Json::Value& root) const;

        std::string GetText() const;
        void SetText(const std::string& value);
        DateTimePreparser GetTextForDateParsing() const;

        TextSize GetTextSize() const;
        void SetTextSize(const TextSize value);

        TextWeight GetTextWeight() const;
        void SetTextWeight(const TextWeight value);

        FontStyle GetFontStyle() const;
        void SetFontStyle(const FontStyle value);

        ForegroundColor GetTextColor() const;
        void SetTextColor(const ForegroundColor value);

        bool GetIsSubtle() const;
        void SetIsSubtle(const bool value);

        bool GetItalic() const;
        void SetItalic(const bool value);

        bool GetStrikethrough() const;
        void SetStrikethrough(const bool value);

        void SetLanguage(const std::string& value);
        std::string GetLanguage() const;

        void Deserialize(const ParseContext& context, const Json::Value& root);
        void PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties);

    private:
        std::string m_text;
        TextSize m_textSize;
        TextWeight m_textWeight;
        FontStyle m_fontStyle;
        ForegroundColor m_textColor;
        bool m_isSubtle;
        bool m_italic;
        bool m_strikethrough;
        std::string m_language;
    };
}
