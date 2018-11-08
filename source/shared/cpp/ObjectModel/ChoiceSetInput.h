#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"

namespace AdaptiveSharedNamespace
{
    class ChoiceInput;

    class ChoiceSetInput : public BaseInputElement
    {
        friend class ChoiceSetInputParser;

    public:
        ChoiceSetInput();

        Json::Value SerializeToJsonValue() const override;

        bool GetIsMultiSelect() const;
        void SetIsMultiSelect(const bool isMultiSelect);

        ChoiceSetStyle GetChoiceSetStyle() const;
        void SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle);

        std::vector<std::shared_ptr<ChoiceInput>>& GetChoices();
        const std::vector<std::shared_ptr<ChoiceInput>>& GetChoices() const;

        std::string GetValue() const;
        void SetValue(const std::string& value);

    private:
        void PopulateKnownPropertiesSet() override;

        std::string m_value;
        bool m_isMultiSelect;
        ChoiceSetStyle m_choiceSetStyle;

        std::vector<std::shared_ptr<ChoiceInput>> m_choices;
    };

    class ChoiceSetInputParser : public BaseCardElementParser
    {
    public:
        ChoiceSetInputParser() = default;
        ChoiceSetInputParser(const ChoiceSetInputParser&) = default;
        ChoiceSetInputParser(ChoiceSetInputParser&&) = default;
        ChoiceSetInputParser& operator=(const ChoiceSetInputParser&) = default;
        ChoiceSetInputParser& operator=(ChoiceSetInputParser&&) = default;
        ~ChoiceSetInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
