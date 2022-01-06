// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseInputElement.h"

namespace AdaptiveCards
{
class DateInput : public BaseInputElement
{
public:
    DateInput();
    DateInput(const DateInput&) = default;
    DateInput(DateInput&&) = default;
    DateInput& operator=(const DateInput&) = default;
    DateInput& operator=(DateInput&&) = default;
    ~DateInput() = default;

    Json::Value SerializeToJsonValue() const override;

    std::string GetMax() const;
    void SetMax(const std::string& value);

    std::string GetMin() const;
    void SetMin(const std::string& value);

    std::string GetPlaceholder() const;
    void SetPlaceholder(const std::string& value);

    std::string GetValue() const;
    void SetValue(const std::string& value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_max;
    std::string m_min;
    std::string m_placeholder;
    std::string m_value;
};

class DateInputParser : public BaseCardElementParser
{
public:
    DateInputParser() = default;
    DateInputParser(const DateInputParser&) = default;
    DateInputParser(DateInputParser&&) = default;
    DateInputParser& operator=(const DateInputParser&) = default;
    DateInputParser& operator=(DateInputParser&&) = default;
    virtual ~DateInputParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
