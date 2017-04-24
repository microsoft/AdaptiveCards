#include "InputText.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

InputText::InputText() :
    BaseCardElement(CardElementType::InputText),
    m_isMultiline(false),
    m_maxLength(0)
{
}

std::shared_ptr<InputText> InputText::Deserialize(const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::InputText);

    std::shared_ptr<InputText> inputToggle = BaseCardElement::Deserialize<InputText>(json);

    inputToggle->SetPlaceholder(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Placeholder));
    inputToggle->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));
    inputToggle->SetIsMultiline(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsMultiline, false));
    inputToggle->SetMaxLength(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLength, 0));

    return inputToggle;
}

std::shared_ptr<InputText> InputText::DeserializeFromString(const std::string& jsonString)
{
    Json::Value jsonValue(jsonString);

    return InputText::Deserialize(jsonValue);
}

std::string InputText::Serialize()
{
    return "";
}

std::string InputText::GetPlaceholder() const
{
    return m_placeholder;
}

void InputText::SetPlaceholder(const std::string value)
{
    m_placeholder = value;
}

std::string InputText::GetValue() const
{
    return m_value;
}

void InputText::SetValue(const std::string value)
{
    m_value = value;
}

bool InputText::GetIsMultiline() const
{
    return m_isMultiline;
}

void InputText::SetIsMultiline(const bool value)
{
    m_isMultiline = value;
}

unsigned int InputText::GetMaxLength() const
{
    return m_maxLength;
}

void InputText::SetMaxLength(const unsigned int value)
{
    m_maxLength = value;
}