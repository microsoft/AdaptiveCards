#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

AdaptiveSharedNamespaceStart
class OpenUrlAction : public BaseActionElement
{
public:
    OpenUrlAction();

    virtual Json::Value SerializeToJsonValue() const override;

    std::string GetUrl() const;
    void SetUrl(const std::string &value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_url;
};

class OpenUrlActionParser : public ActionElementParser
{
    std::shared_ptr<BaseActionElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const Json::Value& value);

    std::shared_ptr<BaseActionElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        const std::string& jsonString);
};
AdaptiveSharedNamespaceEnd
