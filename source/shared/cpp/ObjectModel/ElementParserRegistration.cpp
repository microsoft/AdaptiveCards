// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ElementParserRegistration.h"
#include "ActionSet.h"
#include "ChoiceSetInput.h"
#include "ColumnSet.h"
#include "Column.h"
#include "Container.h"
#include "DateInput.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "Media.h"
#include "NumberInput.h"
#include "RichTextBlock.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"
#include "UnknownElement.h"

namespace AdaptiveSharedNamespace
{
    BaseCardElementParserWrapper::BaseCardElementParserWrapper(std::shared_ptr<BaseCardElementParser> parserToWrap) :
        m_parser{parserToWrap}
    {
    }

    std::shared_ptr<BaseCardElement> BaseCardElementParserWrapper::Deserialize(ParseContext& context, const Json::Value& value)
    {
        const auto& idProperty = ParseUtil::GetString(value, AdaptiveCardSchemaKey::Id);
        const InternalId internalId = InternalId::Next();

        context.PushElement(idProperty, internalId);
        std::shared_ptr<BaseCardElement> element = m_parser->Deserialize(context, value);
        context.PopElement();

        return element;
    }

    std::shared_ptr<BaseCardElement> BaseCardElementParserWrapper::DeserializeFromString(ParseContext& context, const std::string& value)
    {
        return Deserialize(context, ParseUtil::GetJsonValueFromString(value));
    }

    ElementParserRegistration::ElementParserRegistration()
    {
        m_knownElements.insert({
            CardElementTypeToString(CardElementType::ActionSet),
            CardElementTypeToString(CardElementType::Container),
            CardElementTypeToString(CardElementType::Column),
            CardElementTypeToString(CardElementType::ColumnSet),
            CardElementTypeToString(CardElementType::FactSet),
            CardElementTypeToString(CardElementType::Image),
            CardElementTypeToString(CardElementType::ImageSet),
            CardElementTypeToString(CardElementType::ChoiceSetInput),
            CardElementTypeToString(CardElementType::DateInput),
            CardElementTypeToString(CardElementType::Media),
            CardElementTypeToString(CardElementType::NumberInput),
            CardElementTypeToString(CardElementType::RichTextBlock),
            CardElementTypeToString(CardElementType::TextBlock),
            CardElementTypeToString(CardElementType::TextInput),
            CardElementTypeToString(CardElementType::TimeInput),
            CardElementTypeToString(CardElementType::ToggleInput),
            CardElementTypeToString(CardElementType::Unknown),
        });

        m_cardElementParsers.insert(
            {{CardElementTypeToString(CardElementType::ActionSet), std::make_shared<ActionSetParser>()},
             {CardElementTypeToString(CardElementType::Container), std::make_shared<ContainerParser>()},
             {CardElementTypeToString(CardElementType::Column), std::make_shared<ColumnParser>()},
             {CardElementTypeToString(CardElementType::ColumnSet), std::make_shared<ColumnSetParser>()},
             {CardElementTypeToString(CardElementType::FactSet), std::make_shared<FactSetParser>()},
             {CardElementTypeToString(CardElementType::Image), std::make_shared<ImageParser>()},
             {CardElementTypeToString(CardElementType::ImageSet), std::make_shared<ImageSetParser>()},
             {CardElementTypeToString(CardElementType::ChoiceSetInput), std::make_shared<ChoiceSetInputParser>()},
             {CardElementTypeToString(CardElementType::DateInput), std::make_shared<DateInputParser>()},
             {CardElementTypeToString(CardElementType::Media), std::make_shared<MediaParser>()},
             {CardElementTypeToString(CardElementType::NumberInput), std::make_shared<NumberInputParser>()},
             {CardElementTypeToString(CardElementType::RichTextBlock), std::make_shared<RichTextBlockParser>()},
             {CardElementTypeToString(CardElementType::TextBlock), std::make_shared<TextBlockParser>()},
             {CardElementTypeToString(CardElementType::TextInput), std::make_shared<TextInputParser>()},
             {CardElementTypeToString(CardElementType::TimeInput), std::make_shared<TimeInputParser>()},
             {CardElementTypeToString(CardElementType::ToggleInput), std::make_shared<ToggleInputParser>()},
             {CardElementTypeToString(CardElementType::Unknown), std::make_shared<UnknownElementParser>()}});
    }

    void ElementParserRegistration::AddParser(std::string const& elementType, std::shared_ptr<BaseCardElementParser> parser)
    {
        if (m_knownElements.find(elementType) == m_knownElements.end())
        {
            ElementParserRegistration::m_cardElementParsers[elementType] = parser;
        }
        else
        {
            throw AdaptiveCardParseException(ErrorStatusCode::UnsupportedParserOverride,
                                             "Overriding known element parsers is unsupported");
        }
    }

    void ElementParserRegistration::RemoveParser(std::string const& elementType)
    {
        if (m_knownElements.find(elementType) == m_knownElements.end())
        {
            ElementParserRegistration::m_cardElementParsers.erase(elementType);
        }
        else
        {
            throw AdaptiveCardParseException(ErrorStatusCode::UnsupportedParserOverride,
                                             "Overriding known element parsers is unsupported");
        }
    }

    std::shared_ptr<BaseCardElementParser> ElementParserRegistration::GetParser(std::string const& elementType) const
    {
        auto parser = m_cardElementParsers.find(elementType);
        if (parser != ElementParserRegistration::m_cardElementParsers.end())
        {
            // Why do we wrap the parser? As we parse elements, we need to push and pop state from the stack for ID
            // collision detection. We *could* do this within the implementation of parsers themselves, but that would
            // mean having to explain all of this to custom element parser implementors. Instead, we wrap every parser
            // we hand out with a helper class that performs the push/pop on behalf of the element parser. For more
            // details, refer to the giant comment on ID collision detection in ParseContext.cpp.
            std::shared_ptr<BaseCardElementParser> wrappedParser = std::make_shared<BaseCardElementParserWrapper>(parser->second);
            return wrappedParser;
        }
        else
        {
            return std::shared_ptr<BaseCardElementParser>(nullptr);
        }
    }
}
