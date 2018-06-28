#pragma once

#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "BaseActionElement.h"
#include "Enums.h"
#include "ActionParserRegistration.h"

namespace AdaptiveSharedNamespace {
class ShowCardAction : public BaseActionElement
{
public:
    ShowCardAction();

    virtual Json::Value SerializeToJsonValue() const override;

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
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& value) override;

    std::shared_ptr<BaseActionElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
        std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
