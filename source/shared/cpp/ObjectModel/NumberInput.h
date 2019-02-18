#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
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

        int GetValue() const;
        void SetValue(const int value);

        int GetMax() const;
        void SetMax(const int value);

        int GetMin() const;
        void SetMin(const int value);

    private:
        void PopulateKnownPropertiesSet() override;

        std::string m_placeholder;
        int m_value;
        int m_max;
        int m_min;
    };

    class NumberInputParser : public BaseCardElementParser
    {
    public:
        NumberInputParser() = default;
        NumberInputParser(const NumberInputParser&) = default;
        NumberInputParser(NumberInputParser&&) = default;
        NumberInputParser& operator=(const NumberInputParser&) = default;
        NumberInputParser& operator=(NumberInputParser&&) = default;
        ~NumberInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
