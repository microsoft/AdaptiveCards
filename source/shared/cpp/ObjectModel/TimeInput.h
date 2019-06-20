// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class TimeInput : public BaseInputElement
    {
    public:
        TimeInput();
        TimeInput(const TimeInput&) = default;
        TimeInput(TimeInput&&) = default;
        TimeInput& operator=(const TimeInput&) = default;
        TimeInput& operator=(TimeInput&&) = default;
        ~TimeInput() = default;

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
        void PopulateKnownPropertiesSet() override;

        std::string m_max;
        std::string m_min;
        std::string m_placeholder;
        std::string m_value;
    };

    class TimeInputParser : public BaseCardElementParser
    {
    public:
        TimeInputParser() = default;
        TimeInputParser(const TimeInputParser&) = default;
        TimeInputParser(TimeInputParser&&) = default;
        TimeInputParser& operator=(const TimeInputParser&) = default;
        TimeInputParser& operator=(TimeInputParser&&) = default;
        virtual ~TimeInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
