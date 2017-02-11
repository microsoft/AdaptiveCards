#include "Fact.h"

using namespace AdaptiveCards;

Fact::Fact()
{
}

Fact::Fact(std::shared_ptr<FactGroup> container, std::string speak, std::string name, std::string value) : m_parent(container), m_speak(speak), m_name(name), m_value(value)
{
}

std::shared_ptr<Fact> Fact::Deserialize(const Json::Value & root)
{
    return std::shared_ptr<Fact>();
}

std::string Fact::Serialize()
{
    return std::string();
}

std::string Fact::GetSpeak() const
{
    return m_speak;
}

void Fact::SetSpeak(const std::string value)
{
    m_speak = value;
}

std::string Fact::GetName() const
{
    return m_name;
}

void Fact::SetName(const std::string value)
{
    m_name = value;
}

std::string Fact::GetValue() const
{
    return m_value;
}

void Fact::SetValue(const std::string value)
{
    m_value = value;
}

std::weak_ptr<FactGroup> Fact::GetFactGroup() const
{
    return m_parent;
}

CardElementType Fact::GetType() const
{
    return CardElementType::Fact;
}
