#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

AdaptiveSharedNamespaceStart
class SubmitAction : public BaseActionElement
{
public:
    SubmitAction();

    std::string GetDataJson() const;
    void SetDataJson(const std::string &value);

    virtual Json::Value SerializeToJsonValue() const override;

private:
    void PopulateKnownPropertiesSet();

    std::string m_dataJson;
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
AdaptiveSharedNamespaceEnd
