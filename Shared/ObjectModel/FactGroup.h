#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "Fact.h"
#include "Enums.h"

namespace AdaptiveCards
{
    class Fact;
    class FactGroup : BaseCardElement
    {
    public:
        FactGroup();
        FactGroup(std::shared_ptr<Container> container, HorizontalAlignment horizontalAlignment, CardElementSize size, std::string speak,
            std::vector<std::shared_ptr<Fact>>& facts = std::vector<std::shared_ptr<Fact>>());

        std::vector<std::shared_ptr<Fact>>& GetFacts();

        static std::shared_ptr<FactGroup> Deserialize(const Json::Value& root);

        virtual std::string Serialize();

    private:
        std::vector<std::shared_ptr<Fact>> m_facts;
    };
}