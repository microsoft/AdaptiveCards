#pragma once

#include "pch.h"
#include "FactGroup.h"
#include "Enums.h"

namespace AdaptiveCards
{
    class FactGroup;
    class Fact
    {
    public:
        Fact();
        Fact(std::shared_ptr<FactGroup> container, std::string speak, std::string name, std::string value);

        static std::shared_ptr<Fact> Deserialize(const Json::Value& root);

        std::string Serialize();

        std::string GetSpeak() const;
        void SetSpeak(const std::string value);

        std::string GetName() const;
        void SetName(const std::string value);

        std::string GetValue() const;
        void SetValue(const std::string value);

        std::weak_ptr<FactGroup> GetFactGroup() const;

        AdaptiveCards::CardElementType GetType() const;

    private:
        std::weak_ptr<FactGroup> m_parent;
        std::string m_speak;
        std::string m_name;
        std::string m_value;
    };
}