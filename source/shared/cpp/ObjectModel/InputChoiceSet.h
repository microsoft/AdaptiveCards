#pragma once

#include "pch.h"
#include "Enums.h"
#include "InputChoice.h"
#include "BaseInputElement.h"

namespace AdaptiveCards
{
class BaseInputElement;
class InputChoiceSet : public BaseInputElement
{
public:
    InputChoiceSet();
    InputChoiceSet(SeparationStyle separation, std::string speak);
    InputChoiceSet(SeparationStyle separation, std::string speak, std::vector<std::shared_ptr<InputChoice>>& choices);

    virtual std::string Serialize();

    bool GetIsMultiSelect() const;
    void SetIsMultiSelect(const bool isMultiSelect);

    bool GetIsRequired() const;
    void SetIsRequired(const bool isRequired);

    ChoiceSetStyle GetChoiceSetStyle() const;
    void SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle);

    std::vector<std::shared_ptr<InputChoice>>& GetChoices();
    const std::vector<std::shared_ptr<InputChoice>>& GetChoices() const;

    static std::shared_ptr<InputChoiceSet> Deserialize(const Json::Value& root);
    static std::shared_ptr<InputChoiceSet> DeserializeFromString(const std::string& jsonString);

private:
    bool m_isMultiSelect;
    bool m_isRequired;
    ChoiceSetStyle m_choiceSetStyle;

    std::vector<std::shared_ptr<InputChoice>> m_choices; 
};
}