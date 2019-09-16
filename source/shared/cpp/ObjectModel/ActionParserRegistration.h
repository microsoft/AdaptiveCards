// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "AdaptiveCardParseWarning.h"

namespace AdaptiveSharedNamespace
{
    class BaseActionElement;
    class ParseContext;

    class ActionElementParser
    {
    public:
        virtual std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) = 0;
        virtual std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& value) = 0;
    };

    class ActionElementParserWrapper : public ActionElementParser
    {
    public:
        ActionElementParserWrapper(std::shared_ptr<ActionElementParser> parserToWrap);

        ActionElementParserWrapper(const ActionElementParserWrapper&) = delete;
        ActionElementParserWrapper(ActionElementParserWrapper&&) = delete;
        ActionElementParserWrapper& operator=(const ActionElementParserWrapper&) = delete;
        ActionElementParserWrapper& operator=(ActionElementParserWrapper&&) = delete;
        virtual ~ActionElementParserWrapper() = default;

        std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& value) override;
        std::shared_ptr<ActionElementParser> GetActualParser() const { return m_parser; }

    private:
        std::shared_ptr<ActionElementParser> m_parser;
    };

    class ActionParserRegistration
    {
    public:
        ActionParserRegistration();

        void AddParser(std::string const& elementType, std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser> parser);
        void RemoveParser(std::string const& elementType);
        std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser> GetParser(std::string const& elementType) const;

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
}
