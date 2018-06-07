#pragma once

#include "pch.h"
#include "Enums.h"
#include "Fact.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace {
class BaseCardElement;
class FactSet : public BaseCardElement
{
friend class FactSetParser;
public:
    FactSet();

    virtual Json::Value SerializeToJsonValue() const override;

    std::vector<std::shared_ptr<Fact>>& GetFacts();
    const std::vector<std::shared_ptr<Fact>>& GetFacts() const;

private:
    void PopulateKnownPropertiesSet();

    std::vector<std::shared_ptr<Fact>> m_facts;
};

class FactSetParser : public BaseCardElementParser
{
public:
    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& root) override;

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
