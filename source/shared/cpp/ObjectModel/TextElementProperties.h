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
        virtual ~TextElementProperties() = default;

        virtual Json::Value SerializeToJsonValue(Json::Value& root) const;

        std::string GetText() const;
        void SetText(const std::string& value);
        DateTimePreparser GetTextForDateParsing() const;

        TextSize GetTextSize() const;
        void SetTextSize(const TextSize value);

        TextWeight GetTextWeight() const;
        void SetTextWeight(const TextWeight value);

        FontType GetFontType() const;
        void SetFontType(const FontType value);

        ForegroundColor GetTextColor() const;
        void SetTextColor(const ForegroundColor value);

        bool GetIsSubtle() const;
        void SetIsSubtle(const bool value);

        void SetLanguage(const std::string& value);
        std::string GetLanguage() const;

        virtual void Deserialize(const ParseContext& context, const Json::Value& root);
        virtual void PopulateKnownPropertiesSet(std::unordered_set<std::string>& knownProperties);

    private:
        std::string m_text;
        TextSize m_textSize;
        TextWeight m_textWeight;
        FontType m_fontType;
        ForegroundColor m_textColor;
        bool m_isSubtle;
        std::string m_language;
    };
}
