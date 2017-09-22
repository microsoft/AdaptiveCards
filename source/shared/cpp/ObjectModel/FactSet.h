#pragma once

#include "pch.h"
#include "Enums.h"
#include "Fact.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class BaseCardElement;
class FactSet : public BaseCardElement
{
public:
    FactSet();
    FactSet(Spacing spacing, std::shared_ptr<Separator> separation, std::string speak);
    FactSet(Spacing spacing, std::shared_ptr<Separator> separation, std::string speak, std::vector<std::shared_ptr<Fact>>& facts);

    virtual std::string Serialize();
    virtual Json::Value SerializeToJsonValue();

    std::vector<std::shared_ptr<Fact>>& GetFacts();
    const std::vector<std::shared_ptr<Fact>>& GetFacts() const;
    static std::shared_ptr<FactSet> Deserialize(const Json::Value& root);
    static std::shared_ptr<FactSet> DeserializeFromString(const std::string& jsonString);

private:
    std::vector<std::shared_ptr<Fact>> m_facts; 
};
}