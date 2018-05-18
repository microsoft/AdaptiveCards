#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

AdaptiveSharedNamespaceStart
    class BaseCardElement;
    class ElementParserRegistration;
    class ActionParserRegistration;

    class BaseCardElementParser
    {
    public:
        virtual std::shared_ptr<BaseCardElement> Deserialize(
            std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> elementParserRegistration,
            std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration> actionParserRegistration,
            const Json::Value& value) = 0;
    };

    class ElementParserRegistration
    {
    public:

        ElementParserRegistration();

        void AddParser(std::string const &elementType, std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser> parser);
        void RemoveParser(std::string const &elementType);
        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser> GetParser(std::string const &elementType);

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveSharedNamespace::BaseCardElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
AdaptiveSharedNamespaceEnd
