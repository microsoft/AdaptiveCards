#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"

namespace AdaptiveCards
{
    class BaseCardElement;
    class ElementParserRegistration;
    class ActionParserRegistration;

    class IBaseCardElementParser
    {
    public:
        virtual std::shared_ptr<BaseCardElement> Deserialize(
            std::shared_ptr<AdaptiveCards::ElementParserRegistration> elementParserRegistration,
            std::shared_ptr<AdaptiveCards::ActionParserRegistration> actionParserRegistration,
            const Json::Value& value) = 0;
    };

    class ElementParserRegistration
    {
    public:

        ElementParserRegistration();

        void AddParser(std::string elementType, std::shared_ptr<AdaptiveCards::IBaseCardElementParser> parser);
        void RemoveParser(std::string elementType);
        std::shared_ptr<AdaptiveCards::IBaseCardElementParser> GetParser(std::string elementType);

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveCards::IBaseCardElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
}