#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"

namespace AdaptiveCards
{
    class BaseActionElement;
    class ElementParserRegistration;
    class ActionParserRegistration;

    class IBaseActionElementParser
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

        static std::shared_ptr<ActionParserRegistration> GetDefault();

        void AddParser(std::string elementType, std::shared_ptr<IBaseActionElementParser> parser);
        void RemoveParser(std::string elementType);
        std::shared_ptr<IBaseActionElementParser> GetParser(std::string elementType);

    private:
        std::unordered_map<std::string, std::shared_ptr<IBaseActionElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
}