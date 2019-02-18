#pragma once

#include "pch.h"
#include "BaseInputElement.h"
#include "Enums.h"
#include "ElementParserRegistration.h"

namespace AdaptiveSharedNamespace
{
    class TextInput : public BaseInputElement
    {
    public:
        TextInput();
        TextInput(const TextInput&) = default;
        TextInput(TextInput&&) = default;
        TextInput& operator=(const TextInput&) = default;
        TextInput& operator=(TextInput&&) = default;
        ~TextInput() = default;

        Json::Value SerializeToJsonValue() const override;

        std::string GetPlaceholder() const;
        void SetPlaceholder(const std::string& value);

        std::string GetValue() const;
        void SetValue(const std::string& value);

        bool GetIsMultiline() const;
        void SetIsMultiline(const bool value);

        unsigned int GetMaxLength() const;
        void SetMaxLength(const unsigned int value);

        TextInputStyle GetTextInputStyle() const;
        void SetTextInputStyle(const TextInputStyle value);

        std::shared_ptr<BaseActionElement> GetInlineAction() const;
        void SetInlineAction(const std::shared_ptr<BaseActionElement> action);

    private:
        void PopulateKnownPropertiesSet() override;

        std::string m_placeholder;
        std::string m_value;
        bool m_isMultiline;
        unsigned int m_maxLength;
        TextInputStyle m_style;
        std::shared_ptr<BaseActionElement> m_inlineAction;
    };

    class TextInputParser : public BaseCardElementParser
    {
    public:
        TextInputParser() = default;
        TextInputParser(const TextInputParser&) = default;
        TextInputParser(TextInputParser&&) = default;
        TextInputParser& operator=(const TextInputParser&) = default;
        TextInputParser& operator=(TextInputParser&&) = default;
        ~TextInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
    };
}
