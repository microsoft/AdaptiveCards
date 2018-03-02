#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
    class BaseActionElement;
    class ElementParserRegistration;
    class ActionParserRegistration;

    class ActionElementParser
    {
    public:
        virtual std::shared_ptr<BaseActionElement> Deserialize(
            std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
            std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
            const Json::Value& value) = 0;
    };

    class ActionParserRegistration
    {
    public:

        ActionParserRegistration();

        void AddParser(std::string elementType, std::shared_ptr<AdaptiveCards::ActionElementParser> parser);
        void RemoveParser(std::string elementType);
        std::shared_ptr<AdaptiveCards::ActionElementParser> GetParser(std::string elementType);

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveCards::ActionElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
}
