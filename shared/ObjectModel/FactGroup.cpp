#include "FactGroup.h"

using namespace AdaptiveCards;


FactGroup::FactGroup() : BaseCardElement(CardElementType::FactGroup, nullptr, HorizontalAlignment::Left, CardElementSize::Auto, "")
{
}

FactGroup::FactGroup(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak,
    std::vector<std::shared_ptr<Fact>>& facts) :
    BaseCardElement(CardElementType::FactGroup, container, horizontalAlignment, size, speak),
    m_facts(facts)
{
}

std::vector<std::shared_ptr<Fact>>& FactGroup::GetFacts()
{
    return m_facts;
}

std::shared_ptr<FactGroup> FactGroup::Deserialize(const Json::Value & root)
{
    return std::shared_ptr<FactGroup>();
}

std::string FactGroup::Serialize()
{
    return std::string();
}
