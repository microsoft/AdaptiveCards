// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class BaseCardElement;
    class ParseContext;
    class InternalId;

    class BaseCardElementParser
    {
    public:
        virtual std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value) = 0;
        virtual std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& value) = 0;
    };

    class BaseCardElementParserWrapper : public BaseCardElementParser
    {
    public:
        BaseCardElementParserWrapper(std::shared_ptr<BaseCardElementParser> parserToWrap);

        BaseCardElementParserWrapper(const BaseCardElementParserWrapper&) = delete;
        BaseCardElementParserWrapper(BaseCardElementParserWrapper&&) = delete;
        BaseCardElementParserWrapper& operator=(const BaseCardElementParserWrapper&) = delete;
        BaseCardElementParserWrapper& operator=(BaseCardElementParserWrapper&&) = delete;
        virtual ~BaseCardElementParserWrapper() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& value) override;
        std::shared_ptr<BaseCardElementParser> GetActualParser() const { return m_parser; }

    private:
        std::shared_ptr<BaseCardElementParser> m_parser;
    };

    class ElementParserRegistration
    {
    public:
        ElementParserRegistration();

        void AddParser(std::string const& elementType, std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser> parser);
        void RemoveParser(std::string const& elementType);
        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser> GetParser(std::string const& elementType) const;

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
}
