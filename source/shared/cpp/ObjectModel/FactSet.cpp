// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "FactSet.h"
#include "ParseUtil.h"
#include "Fact.h"
#include "Util.h"

using namespace AdaptiveCards;

FactSet::FactSet() : BaseCardElement(CardElementType::FactSet)
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

Json::Value FactSet::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    const std::string& factsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Facts);
    root[factsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& fact : GetFacts())
    {
        root[factsPropertyName].append(fact->SerializeToJsonValue());
    }

    return root;
}

std::shared_ptr<BaseCardElement> FactSetParser::Deserialize(ParseContext& context, const Json::Value& value)
{
    ParseUtil::ExpectTypeString(value, CardElementType::FactSet);

    auto factSet = BaseCardElement::Deserialize<FactSet>(context, value);

    // Parse Facts
    auto facts =
        ParseUtil::GetElementCollectionOfSingleType<Fact>(context, value, AdaptiveCardSchemaKey::Facts, Fact::Deserialize, false);

    if (facts.empty())
    {
        context.warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(WarningStatusCode::RequiredPropertyMissing,
                                                                                 "required property, \"fact\", is missing"));
    }

    factSet->m_facts = std::move(facts);

    return factSet;
}

std::shared_ptr<BaseCardElement> FactSetParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return FactSetParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void FactSet::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Facts)});
}
