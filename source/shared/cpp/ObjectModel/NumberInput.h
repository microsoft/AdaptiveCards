// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class NumberInput : public BaseInputElement
    {
    public:
        NumberInput();
        NumberInput(const NumberInput&) = default;
        NumberInput(NumberInput&&) = default;
        NumberInput& operator=(const NumberInput&) = default;
        NumberInput& operator=(NumberInput&&) = default;
        ~NumberInput() = default;

        Json::Value SerializeToJsonValue() const override;

        std::string GetPlaceholder() const;
        void SetPlaceholder(const std::string& value);

        std::optional<int> GetValue() const;
        void SetValue(const std::optional<int>& value);

        std::optional<int> GetMax() const;
        void SetMax(const std::optional<int>& value);

        std::optional<int> GetMin() const;
        void SetMin(const std::optional<int>& value);

    private:
        void PopulateKnownPropertiesSet();

        std::string m_placeholder;
        std::optional<int> m_value;
        std::optional<int> m_max;
        std::optional<int> m_min;
    };

    class NumberInputParser : public BaseCardElementParser
    {
    public:
        NumberInputParser() = default;
        NumberInputParser(const NumberInputParser&) = default;
        NumberInputParser(NumberInputParser&&) = default;
        NumberInputParser& operator=(const NumberInputParser&) = default;
        NumberInputParser& operator=(NumberInputParser&&) = default;
        virtual ~NumberInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
