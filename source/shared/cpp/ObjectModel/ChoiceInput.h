#pragma once

#include "pch.h"
#include "Enums.h"
#include "json/json.h"
#include "ElementParserRegistration.h"

AdaptiveSharedNamespaceStart
class ChoiceInput
{
public:
    ChoiceInput();

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::string GetTitle() const;
    void SetTitle(const std::string &value);

    std::string GetValue() const;
    void SetValue(const std::string &value);

    static std::shared_ptr<ChoiceInput> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& root);

    static std::shared_ptr<ChoiceInput> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);

private:
    std::string m_title;
    std::string m_value;
};
AdaptiveSharedNamespaceEnd
