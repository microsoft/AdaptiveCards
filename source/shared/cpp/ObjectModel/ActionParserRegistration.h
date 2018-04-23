#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

AdaptiveSharedNamespaceStart
    class BaseActionElement;
    class ElementParserRegistration;
    class ActionParserRegistration;

    class ActionElementParser
    {
    public:
        virtual std::shared_ptr<BaseActionElement> Deserialize(
            std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> elementParserRegistration,
            std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration> actionParserRegistration,
            const Json::Value& value) = 0;
    };

    class ActionParserRegistration
    {
    public:

        ActionParserRegistration();

        void AddParser(std::string elementType, std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser> parser);
        void RemoveParser(std::string elementType);
        std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser> GetParser(std::string elementType);

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
AdaptiveSharedNamespaceEnd
