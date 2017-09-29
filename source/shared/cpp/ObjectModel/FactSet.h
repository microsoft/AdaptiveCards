#pragma once

#include "pch.h"
#include "Enums.h"
#include "Fact.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveCards
{
class BaseCardElement;
class FactSet : public BaseCardElement
{
friend class FactSetParser;
public:
    FactSet();
    FactSet(Spacing spacing, bool separation);
    FactSet(Spacing spacing, bool separation, std::vector<std::shared_ptr<Fact>>& facts);

    virtual std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

    std::vector<std::shared_ptr<Fact>>& GetFacts();
    const std::vector<std::shared_ptr<Fact>>& GetFacts() const;

private:
    std::vector<std::shared_ptr<Fact>> m_facts; 
};

class FactSetParser : public IBaseCardElementParser
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