#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class ToggleInput : public BaseInputElement
    {
    public:
        ToggleInput();

        Json::Value SerializeToJsonValue() const override;

        std::string GetTitle() const;
        void SetTitle(const std::string& value);

        std::string GetValue() const;
        void SetValue(const std::string& value);

        std::string GetValueOff() const;
        void SetValueOff(const std::string& value);

        std::string GetValueOn() const;
        void SetValueOn(const std::string& value);

    private:
        void PopulateKnownPropertiesSet() override;

        std::string m_title;
        std::string m_value;
        std::string m_valueOff;
        std::string m_valueOn;
    };

    class ToggleInputParser : public BaseCardElementParser
    {
    public:
        ToggleInputParser() = default;
        ToggleInputParser(const ToggleInputParser&) = default;
        ToggleInputParser(ToggleInputParser&&) = default;
        ToggleInputParser& operator=(const ToggleInputParser&) = default;
        ToggleInputParser& operator=(ToggleInputParser&&) = default;
        ~ToggleInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
