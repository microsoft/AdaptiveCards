#include "ActionParserRegistration.h"
#include "OpenUrlAction.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"

namespace AdaptiveCards
{
    bool ActionParserRegistration::ParsersInitialized = false;
    std::unordered_map<std::string, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>, CaseInsensitiveHash, CaseInsensitiveEqualTo> ActionParserRegistration::CardElementParsers = {};

    void ActionParserRegistration::EnsureParsersInitialized()
    {
        if (!ActionParserRegistration::ParsersInitialized)
        {
            ActionParserRegistration::CardElementParsers.insert({
                { ActionTypeToString(ActionType::OpenUrl), OpenUrlAction::Deserialize },
                { ActionTypeToString(ActionType::ShowCard), ShowCardAction::Deserialize },
                { ActionTypeToString(ActionType::Submit), SubmitAction::Deserialize },
            });

            ActionParserRegistration::ParsersInitialized = true;
        }
    }

    void ActionParserRegistration::AddParser(std::string elementType, std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)> parserFunction)
    {
        ActionParserRegistration::EnsureParsersInitialized();
        ActionParserRegistration::CardElementParsers.erase(elementType); 
        ActionParserRegistration::CardElementParsers.insert({ { elementType, parserFunction } });
    }

    void ActionParserRegistration::RemoveParser(std::string elementType)
    {
        ActionParserRegistration::EnsureParsersInitialized();
        ActionParserRegistration::CardElementParsers.erase(elementType);
    }

    bool ActionParserRegistration::GetParser(
        std::string elementType,
        std::function<std::shared_ptr<BaseActionElement>(const Json::Value&)>* parserFunction)
    {
        ActionParserRegistration::EnsureParsersInitialized();
        if (ActionParserRegistration::CardElementParsers.find(elementType) != ActionParserRegistration::CardElementParsers.end())
        {
            *parserFunction = CardElementParsers.at(elementType);
            return true;
        }
        else
        {
            return false;
        }
    }
}
