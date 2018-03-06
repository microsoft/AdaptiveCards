#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Enums.h"
#include <time.h>
#include "ElementParserRegistration.h"
#include "DateTimePreparser.h"

namespace AdaptiveCards
{
class UnknownElement: public BaseCardElement
{
public:
    UnknownElement();
    UnknownElement(Json::Value const &paylaod);
        
    virtual Json::Value SerializeToJsonValue() override;
};

class UnknownElementParser : public BaseCardElementParser
{
public:
    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const Json::Value& root);

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const std::string& jsonString);
};
}
