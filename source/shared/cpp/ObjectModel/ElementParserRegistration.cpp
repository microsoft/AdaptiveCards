#include "ElementParserRegistration.h"
#include "ChoiceSetInput.h"
#include "ColumnSet.h"
#include "Container.h"
#include "DateInput.h"
#include "FactSet.h"
#include "Image.h"
#include "ImageSet.h"
#include "NumberInput.h"
#include "TextBlock.h"
#include "TextInput.h"
#include "TimeInput.h"
#include "ToggleInput.h"

namespace AdaptiveCards
{

    ElementParserRegistration::ElementParserRegistration()
    {
    }

    std::shared_ptr<ElementParserRegistration> ElementParserRegistration::GetDefault()
    {
        std::shared_ptr<ElementParserRegistration> defaultParserRegistration = std::make_shared<ElementParserRegistration>();
        defaultParserRegistration->m_cardElementParsers.insert({
            { CardElementTypeToString(CardElementType::Container), std::make_shared<ContainerParser>() },
            { CardElementTypeToString(CardElementType::ColumnSet), std::make_shared<ColumnSetParser>() },
            { CardElementTypeToString(CardElementType::FactSet), std::make_shared<FactSetParser>() },
            { CardElementTypeToString(CardElementType::Image),  std::make_shared<ImageParser>() },
            { CardElementTypeToString(CardElementType::ImageSet), std::make_shared<ImageSetParser>() },
            { CardElementTypeToString(CardElementType::ChoiceSetInput), std::make_shared<ChoiceSetInputParser>() },
            { CardElementTypeToString(CardElementType::DateInput), std::make_shared<DateInputParser>() },
            { CardElementTypeToString(CardElementType::NumberInput), std::make_shared<NumberInputParser>() },
            { CardElementTypeToString(CardElementType::TextBlock), std::make_shared<TextBlockParser>() },
            { CardElementTypeToString(CardElementType::TextInput),  std::make_shared<TextInputParser>() },
            { CardElementTypeToString(CardElementType::TimeInput), std::make_shared<TimeInputParser>() },
            { CardElementTypeToString(CardElementType::ToggleInput), std::make_shared<ToggleInputParser>() }
        });

        return defaultParserRegistration;
    }

    void ElementParserRegistration::AddParser(std::string elementType, std::shared_ptr<IBaseCardElementParser> parser)
    {
        ElementParserRegistration::m_cardElementParsers[elementType] = parser;
    }

    void ElementParserRegistration::RemoveParser(std::string elementType)
    {
        ElementParserRegistration::m_cardElementParsers.erase(elementType);
    }

    std::shared_ptr<IBaseCardElementParser> ElementParserRegistration::GetParser(std::string elementType)
    {
        auto parser = m_cardElementParsers.find(elementType);
        if (parser != ElementParserRegistration::m_cardElementParsers.end())
        {
            return parser->second;
        }
        else
        {
            return std::shared_ptr<IBaseCardElementParser>(nullptr);
        }
    }
}
