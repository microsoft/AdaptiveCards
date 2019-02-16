#include "pch.h"
#include "ChoiceInput.h"
#include "ParseContext.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

ChoiceInput::ChoiceInput()
{
}

std::shared_ptr<ChoiceInput> ChoiceInput::Deserialize(ParseContext &/*context*/, const Json::Value& json)
{
    auto choice = std::make_shared<ChoiceInput>();

    choice->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title, true));
    choice->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value, true));

    return choice;
}

std::shared_ptr<ChoiceInput> ChoiceInput::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ChoiceInput::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::string ChoiceInput::Serialize()
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

Json::Value ChoiceInput::SerializeToJsonValue()
{
    Json::Value root;

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = GetTitle();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = GetValue();

    return root;
}

std::string ChoiceInput::GetTitle() const
{
    return m_title;
}

void ChoiceInput::SetTitle(const std::string& title)
{
    m_title = title;
}

std::string ChoiceInput::GetValue() const
{
    return m_value;
}

void ChoiceInput::SetValue(const std::string& value)
{
    m_value = value;
}
