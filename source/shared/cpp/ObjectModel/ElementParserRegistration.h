#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class BaseCardElement;
    class ParseContext;

    class BaseCardElementParser
    {
    public:
        virtual std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& value) = 0;
        virtual std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& value) = 0;
    };

    class ElementParserRegistration
    {
    public:
        ElementParserRegistration();

        void AddParser(std::string const& elementType, std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser> parser);
        void RemoveParser(std::string const& elementType);
        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser> GetParser(std::string const& elementType);

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
}
