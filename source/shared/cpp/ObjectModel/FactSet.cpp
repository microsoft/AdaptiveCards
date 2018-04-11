#include "pch.h"
#include "FactSet.h"
#include "ParseUtil.h"
#include "Fact.h"

using namespace AdaptiveSharedNamespace;

FactSet::FactSet() : BaseCardElement(CardElementType::FactSet)
{
    PopulateKnownPropertiesSet();
}

FactSet::FactSet(
    Spacing spacing,
    bool separation,
    std::vector<std::shared_ptr<Fact>>& facts) :
    BaseCardElement(CardElementType::FactSet, spacing, separation),
    m_facts(facts)
{
    PopulateKnownPropertiesSet();
}

FactSet::FactSet(
    Spacing spacing,
    bool separation) :
    BaseCardElement(CardElementType::FactSet, spacing, separation)
{
    PopulateKnownPropertiesSet();
}

const std::vector<std::shared_ptr<Fact>>& FactSet::GetFacts() const
{
    return m_facts;
}

std::vector<std::shared_ptr<Fact>>& FactSet::GetFacts()
{
    return m_facts;
}

Json::Value FactSet::SerializeToJsonValue()
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    std::string factsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Facts);
    root[factsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& fact : GetFacts())
    {
        root[factsPropertyName].append(fact->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> FactSetParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::FactSet);

    auto factSet = BaseCardElement::Deserialize<FactSet>(value);

    // Parse Facts
    auto facts = ParseUtil::GetElementCollectionOfSingleType<Fact>(elementParserRegistration, actionParserRegistration, value, AdaptiveCardSchemaKey::Facts, Fact::Deserialize, true);
    factSet->m_facts = std::move(facts);

    return factSet;
}

std::shared_ptr<BaseCardElement> FactSetParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return FactSetParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void FactSet::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Facts));
}
