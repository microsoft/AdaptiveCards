#include "Fact.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

Fact::Fact()
{
}

Fact::Fact(std::string title, std::string value, std::string speak) : 
    m_title(title), m_value(value), m_speak(speak)
{
}

std::shared_ptr<Fact> Fact::Deserialize(const Json::Value& json)
{
    std::string title = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title, true);
    std::string value = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value, true);
    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);

    auto fact = std::make_shared<Fact>(title, value, speak);
    return fact;
}

std::shared_ptr<Fact> Fact::DeserializeFromString(const std::string& jsonString)
{
    return Fact::Deserialize(ParseUtil::GetJsonValueFromString(jsonString));
}

std::string Fact::Serialize()
{
    return "";
}

std::string Fact::GetTitle() const
{
    return m_title;
}

void Fact::SetTitle(const std::string value)
{
    m_title = value;
}

std::string Fact::GetValue() const
{
    return m_value;
}

void Fact::SetValue(const std::string value)
{
    m_value = value;
}

std::string Fact::GetSpeak() const
{
    return m_speak;
}

void Fact::SetSpeak(const std::string value)
{
    m_speak = value;
}
