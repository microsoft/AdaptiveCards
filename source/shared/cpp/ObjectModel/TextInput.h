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
        virtual ~TextInputParser() = default;

        std::shared_ptr<BaseCardElement> Deserialize(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                     std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                     std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                     const Json::Value& root) override;

        std::shared_ptr<BaseCardElement> DeserializeFromString(std::shared_ptr<ElementParserRegistration> elementParserRegistration,
                                                               std::shared_ptr<ActionParserRegistration> actionParserRegistration,
                                                               std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
                                                               const std::string& jsonString);
    };
}
