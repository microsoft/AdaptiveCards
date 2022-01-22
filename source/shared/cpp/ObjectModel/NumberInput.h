// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveCards
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

    std::optional<double> GetValue() const;
    void SetValue(const std::optional<double>& value);

    std::optional<double> GetMax() const;
    void SetMax(const std::optional<double>& value);

    std::optional<double> GetMin() const;
    void SetMin(const std::optional<double>& value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_placeholder;
    std::optional<double> m_value;
    std::optional<double> m_max;
    std::optional<double> m_min;
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
} // namespace AdaptiveCards
