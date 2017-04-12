#pragma once

#include "pch.h"
#include "Enums.h"
#include "json\json.h"

namespace AdaptiveCards
{
class Fact
{
public:
    Fact();
    Fact(std::string title, std::string value, std::string speak);

    std::string Serialize();

    std::string GetTitle() const;
    void SetTitle(const std::string value);

    std::string GetValue() const;
    void SetValue(const std::string value);

    std::string GetSpeak() const;
    void SetSpeak(const std::string value);

    static std::shared_ptr<Fact> Deserialize(const Json::Value& root);

private:
    std::string m_title;
    std::string m_value;
    std::string m_speak;
};
}