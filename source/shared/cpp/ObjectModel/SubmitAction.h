#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace {
class SubmitAction : public BaseActionElement
{
public:
    SubmitAction();

    std::string GetDataJson() const;
    Json::Value GetDataJsonAsValue() const;
    void SetDataJson(const Json::Value &value);

    virtual Json::Value SerializeToJsonValue() const override;

private:
    void PopulateKnownPropertiesSet();

    Json::Value m_dataJson;
};

class SubmitActionParser : public ActionElementParser
{
    std::shared_ptr<BaseActionElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& value) override;

    std::shared_ptr<BaseActionElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
