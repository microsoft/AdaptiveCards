#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"
#include "AdaptiveCardParseWarning.h"

namespace AdaptiveSharedNamespace
{
    class BaseActionElement;
    class ElementParserRegistration;
    class ActionParserRegistration;

    class ActionElementParser
    {
    public:
        virtual std::shared_ptr<BaseActionElement>
        Deserialize(std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration> elementParserRegistration,
                    std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration> actionParserRegistration,
                    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                    const Json::Value& value) = 0;
    };

    class ActionParserRegistration
    {
    public:
        ActionParserRegistration();

        void AddParser(std::string const& elementType, std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser> parser);
        void RemoveParser(std::string const& elementType);
        std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser> GetParser(std::string const& elementType);

    private:
        std::unordered_set<std::string> m_knownElements;
        std::unordered_map<std::string, std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser>, CaseInsensitiveHash, CaseInsensitiveEqualTo> m_cardElementParsers;
    };
}
