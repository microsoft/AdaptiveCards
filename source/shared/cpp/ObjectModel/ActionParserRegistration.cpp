// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ActionParserRegistration.h"

#include "AdaptiveCardParseException.h"
#include "BaseElement.h"
#include "OpenUrlAction.h"
#include "ShowCardAction.h"
#include "SubmitAction.h"
#include "ToggleVisibilityAction.h"
#include "UnknownAction.h"

namespace AdaptiveSharedNamespace
{
    ActionElementParserWrapper::ActionElementParserWrapper(std::shared_ptr<ActionElementParser> parserToWrap) :
        m_parser{parserToWrap}
    {
    }

    std::shared_ptr<BaseActionElement> ActionElementParserWrapper::Deserialize(ParseContext& context, const Json::Value& value)
    {
        const auto& idProperty = ParseUtil::GetString(value, AdaptiveCardSchemaKey::Id);
        const AdaptiveSharedNamespace::InternalId internalId = AdaptiveSharedNamespace::InternalId::Next();
        context.PushElement(idProperty, internalId);
        std::shared_ptr<BaseActionElement> element = m_parser->Deserialize(context, value);
        context.PopElement();

        return element;
    }

    std::shared_ptr<BaseActionElement> ActionElementParserWrapper::DeserializeFromString(ParseContext& context, const std::string& value)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(value));
    }

    ActionParserRegistration::ActionParserRegistration()
    {
        m_knownElements.insert({
            ActionTypeToString(ActionType::OpenUrl),
            ActionTypeToString(ActionType::ShowCard),
            ActionTypeToString(ActionType::Submit),
            ActionTypeToString(ActionType::ToggleVisibility),
            ActionTypeToString(ActionType::UnknownAction),
        });

        m_cardElementParsers.insert(
            {{ActionTypeToString(ActionType::OpenUrl), std::make_shared<OpenUrlActionParser>()},
             {ActionTypeToString(ActionType::ShowCard), std::make_shared<ShowCardActionParser>()},
             {ActionTypeToString(ActionType::Submit), std::make_shared<SubmitActionParser>()},
             {ActionTypeToString(ActionType::ToggleVisibility), std::make_shared<ToggleVisibilityActionParser>()},
             {ActionTypeToString(ActionType::UnknownAction), std::make_shared<UnknownActionParser>()}});
    }

    void ActionParserRegistration::AddParser(std::string const& elementType, std::shared_ptr<ActionElementParser> parser)
    {
        // make sure caller isn't attempting to overwrite a known element's parser
        if (m_knownElements.find(elementType) == m_knownElements.end())
        {
            ActionParserRegistration::m_cardElementParsers[elementType] = parser;
        }
        else
        {
            throw AdaptiveCardParseException(ErrorStatusCode::UnsupportedParserOverride, "Overriding known action parsers is unsupported");
        }
    }

    void ActionParserRegistration::RemoveParser(std::string const& elementType)
    {
        // make sure caller isn't attempting to remove a known element's parser
        if (m_knownElements.find(elementType) == m_knownElements.end())
        {
            ActionParserRegistration::m_cardElementParsers.erase(elementType);
        }
        else
        {
            throw AdaptiveCardParseException(ErrorStatusCode::UnsupportedParserOverride, "Removing known action parsers is unsupported");
        }
    }

    std::shared_ptr<ActionElementParser> ActionParserRegistration::GetParser(std::string const& elementType) const
    {
        auto parser = m_cardElementParsers.find(elementType);
        if (parser != ActionParserRegistration::m_cardElementParsers.end())
        {
            // Why do we wrap the parser? As we parse elements, we need to push and pop state from the stack for ID
            // collision detection. We *could* do this within the implementation of parsers themselves, but that would
            // mean having to explain all of this to custom element parser implementors. Instead, we wrap every parser
            // we hand out with a helper class that performs the push/pop on behalf of the element parser. For more
            // details, refer to the giant comment on ID collision detection in ParseContext.cpp.
            std::shared_ptr<ActionElementParser> wrappedParser = std::make_shared<ActionElementParserWrapper>(parser->second);
            return wrappedParser;
        }
        else
        {
            return std::shared_ptr<ActionElementParser>(nullptr);
        }
    }
}
