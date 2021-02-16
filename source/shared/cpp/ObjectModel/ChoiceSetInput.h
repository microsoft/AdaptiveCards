// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseInputElement.h"

namespace AdaptiveSharedNamespace
{
    class ChoiceInput;

    class ChoiceSetInput : public BaseInputElement
    {
        friend class ChoiceSetInputParser;

    public:
        ChoiceSetInput();
        ChoiceSetInput(const ChoiceSetInput&) = default;
        ChoiceSetInput(ChoiceSetInput&&) = default;
        ChoiceSetInput& operator=(const ChoiceSetInput&) = default;
        ChoiceSetInput& operator=(ChoiceSetInput&&) = default;
        ~ChoiceSetInput() = default;

        Json::Value SerializeToJsonValue() const override;

        bool GetIsMultiSelect() const;
        void SetIsMultiSelect(const bool isMultiSelect);

        ChoiceSetStyle GetChoiceSetStyle() const;
        void SetChoiceSetStyle(const ChoiceSetStyle choiceSetStyle);

        std::vector<std::shared_ptr<ChoiceInput>>& GetChoices();
        const std::vector<std::shared_ptr<ChoiceInput>>& GetChoices() const;

        std::string GetValue() const;
        void SetValue(const std::string& value);

        bool GetWrap() const;
        void SetWrap(bool value);

        std::string GetPlaceholder() const;
        void SetPlaceholder(const std::string& value);

    private:
        void PopulateKnownPropertiesSet();

        bool m_wrap;
        bool m_isMultiSelect;
        std::string m_placeholder;

        std::string m_value;
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
        virtual ~ChoiceSetInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
