#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"

namespace AdaptiveCards
{
class ChoiceInput
{
public:
    ChoiceInput();

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::string GetTitle() const;
    void SetTitle(const std::string value);

    std::string GetValue() const;
    void SetValue(const std::string value);

    bool GetIsSelected() const;
    void SetIsSelected(const bool value);

    static std::shared_ptr<ChoiceInput> Deserialize(const Json::Value& root);
    static std::shared_ptr<ChoiceInput> DeserializeFromString(const std::string& jsonString);

private:
    std::string m_title;
    std::string m_value;
    bool m_isSelected;
};
}
