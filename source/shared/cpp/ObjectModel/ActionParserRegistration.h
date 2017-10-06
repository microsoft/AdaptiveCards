#pragma once

#include "pch.h"
#include "BaseActionElement.h"

namespace AdaptiveCards
{
    class ActionParserRegistration
    {
    public:

        static void AddParser(std::string elementType, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)> parserFunction);
        static void RemoveParser(std::string elementType);

        static bool GetParser(
            std::string elementType,
            std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>* parserFunction);

    private:
        static std::unordered_map<std::string, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>, CaseInsensitiveHash, CaseInsensitiveEqualTo> CardElementParsers;
        static bool ParsersInitialized;
        static void EnsureParsersInitialized();
    };
}