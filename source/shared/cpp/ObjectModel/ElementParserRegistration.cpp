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
    bool ElementParserRegistration::ParsersInitialized = false;
    std::unordered_map<std::string, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>, CaseInsensitiveHash, CaseInsensitiveEqualTo> ElementParserRegistration::CardElementParsers = {};

    void ElementParserRegistration::EnsureParsersInitialized()
    {
        if (!ElementParserRegistration::ParsersInitialized)
        {
            ElementParserRegistration::CardElementParsers.insert({
                { CardElementTypeToString(CardElementType::Container), Container::Deserialize },
                { CardElementTypeToString(CardElementType::ColumnSet), ColumnSet::Deserialize },
                { CardElementTypeToString(CardElementType::FactSet), FactSet::Deserialize },
                { CardElementTypeToString(CardElementType::Image), Image::Deserialize },
                { CardElementTypeToString(CardElementType::ImageSet), ImageSet::Deserialize },
                { CardElementTypeToString(CardElementType::TextBlock), TextBlock::Deserialize },
                { CardElementTypeToString(CardElementType::ChoiceSetInput), ChoiceSetInput::Deserialize },
                { CardElementTypeToString(CardElementType::DateInput), DateInput::Deserialize },
                { CardElementTypeToString(CardElementType::NumberInput), NumberInput::Deserialize },
                { CardElementTypeToString(CardElementType::TextInput), TextInput::Deserialize },
                { CardElementTypeToString(CardElementType::TimeInput), TimeInput::Deserialize },
                { CardElementTypeToString(CardElementType::ToggleInput), ToggleInput::Deserialize },
            });

            ElementParserRegistration::ParsersInitialized = true;
        }
    }

    void ElementParserRegistration::AddParser(std::string elementType, std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)> parserFunction)
    {
        ElementParserRegistration::EnsureParsersInitialized();
        ElementParserRegistration::CardElementParsers.erase(elementType);
        ElementParserRegistration::CardElementParsers.insert({ { elementType, parserFunction } });
    }

    void ElementParserRegistration::RemoveParser(std::string elementType)
    {
        ElementParserRegistration::EnsureParsersInitialized();
        ElementParserRegistration::CardElementParsers.erase(elementType);
    }

    bool ElementParserRegistration::GetParser(
        std::string elementType,
        std::function<std::shared_ptr<BaseCardElement>(const Json::Value&)>* parserFunction)
    {
        ElementParserRegistration::EnsureParsersInitialized();
        if (ElementParserRegistration::CardElementParsers.find(elementType) != ElementParserRegistration::CardElementParsers.end())
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
