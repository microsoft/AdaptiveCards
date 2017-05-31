#include "FactSet.h"
#include "ParseUtil.h"
#include "Fact.h"

using namespace AdaptiveCards;

FactSet::FactSet() : BaseCardElement(CardElementType::FactSet)
{
}

FactSet::FactSet(
    SeparationStyle separation,
    std::string speak,
    std::vector<std::shared_ptr<Fact>>& facts) :
    BaseCardElement(CardElementType::FactSet, separation, speak),
    m_facts(facts)
{
}

FactSet::FactSet(
    SeparationStyle separation,
    std::string speak) :
    BaseCardElement(CardElementType::FactSet, separation, speak)
{
}

const std::vector<std::shared_ptr<Fact>>& FactSet::GetFacts() const
{
    return m_facts;
}

std::vector<std::shared_ptr<Fact>>& FactSet::GetFacts()
{
    return m_facts;
}

std::string FactSet::Serialize()
{
    return "";
}

std::shared_ptr<FactSet> FactSet::Deserialize(const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::FactSet);

    auto factSet = BaseCardElement::Deserialize<FactSet>(value);

    // Parse Facts
    auto factsArray = ParseUtil::GetArray(value, AdaptiveCardSchemaKey::Facts, true);
    std::vector<std::shared_ptr<Fact>> facts;

    // Deserialize every fact in the array
    for (const Json::Value& element : factsArray)
    {
        auto fact = Fact::Deserialize(element);
        if (fact != nullptr)
        {
            facts.push_back(fact);
        }
    }

    factSet->m_facts = std::move(facts);
    return factSet;
}

std::shared_ptr<FactSet> FactSet::DeserializeFromString(const std::string& jsonString)
{
    return FactSet::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}