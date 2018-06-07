#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "ChoiceInput.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace {
class BaseInputElement;
class ChoiceSetInput : public BaseInputElement
{
friend class ChoiceSetInputParser;
public:
    ChoiceSetInput();

    virtual Json::Value SerializeToJsonValue() const override;

    bool GetIsMultiSelect() const;
    void SetIsMultiSelect(const bool isMultiSelect);

    ChoiceSetStyle GetChoiceSetStyle() const;
    void SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle);

    std::vector<std::shared_ptr<ChoiceInput>>& GetChoices();
    const std::vector<std::shared_ptr<ChoiceInput>>& GetChoices() const;

    std::string GetValue() const;
    void SetValue(const std::string &value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_value;
    bool m_isMultiSelect;
    ChoiceSetStyle m_choiceSetStyle;

    std::vector<std::shared_ptr<ChoiceInput>> m_choices;
};

class ChoiceSetInputParser : public BaseCardElementParser
{
public:
    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& root) override;

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
