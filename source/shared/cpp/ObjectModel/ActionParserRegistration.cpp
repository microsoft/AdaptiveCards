#include "ActionParserRegistration.h"
#include "OpenUrlAction.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"

namespace AdaptiveCards
{
    ActionParserRegistration::ActionParserRegistration()
    {
    }

    std::shared_ptr<ActionParserRegistration> ActionParserRegistration::GetDefault()
    {
        std::shared_ptr<ActionParserRegistration> defaultParserRegistration = std::make_shared<ActionParserRegistration>();
        defaultParserRegistration->m_cardElementParsers.insert({
            { ActionTypeToString(ActionType::OpenUrl), std::make_shared<OpenUrlActionParser>() },
            { ActionTypeToString(ActionType::ShowCard), std::make_shared<ShowCardActionParser>() },
            { ActionTypeToString(ActionType::Submit), std::make_shared<SubmitActionParser>() }
        });

        return defaultParserRegistration;
    }

    void ActionParserRegistration::AddParser(std::string elementType, std::shared_ptr<IBaseActionElementParser> parser)
    {
        ActionParserRegistration::m_cardElementParsers[elementType] = parser;
    }

    void ActionParserRegistration::RemoveParser(std::string elementType)
    {
        ActionParserRegistration::m_cardElementParsers.erase(elementType);
    }

    std::shared_ptr<IBaseActionElementParser> ActionParserRegistration::GetParser(std::string elementType)
    {
        auto parser = m_cardElementParsers.find(elementType);
        if (parser != ActionParserRegistration::m_cardElementParsers.end())
        {
            return parser->second; 
        }
        else
        {
            return std::shared_ptr<IBaseActionElementParser>(nullptr);
        }
    }
}
