#pragma once

#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

AdaptiveSharedNamespaceStart
class ShowCardAction : public BaseActionElement
{
public:
    ShowCardAction();

    virtual Json::Value SerializeToJsonValue() override;

    std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard> GetCard() const;
    void SetCard(const std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCard>);

    void SetLanguage(const std::string& value);

    virtual void GetResourceUris(std::vector<std::string>& resourceUris) override;

private:
    void PopulateKnownPropertiesSet();

    std::shared_ptr<AdaptiveCard> m_card;
};

class ShowCardActionParser : public ActionElementParser
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
