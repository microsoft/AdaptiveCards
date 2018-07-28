#pragma once

#include "Enums.h"
#include "pch.h"
#include "BaseActionElement.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveCards
{
class ActionSet : public BaseCardElement
{
friend class ActionSetParser;
public:
    ActionSet();
    ActionSet(std::vector<std::shared_ptr<BaseActionElement>>& actions);

    virtual Json::Value SerializeToJsonValue() const override;

    ActionsOrientation GetOrientation() const;
    void SetOrientation(const ActionsOrientation value);

    std::vector<std::shared_ptr<BaseActionElement>>& GetActions();

private:
    void PopulateKnownPropertiesSet();
    std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> m_actions;
    ActionsOrientation m_orientation;
};

class ActionSetParser : public BaseCardElementParser
{
public:
    std::shared_ptr<BaseCardElement> Deserialize(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
		std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const Json::Value& root);

    std::shared_ptr<BaseCardElement> DeserializeFromString(
        std::shared_ptr<ElementParserRegistration> elementParserRegistration,
        std::shared_ptr<ActionParserRegistration> actionParserRegistration,
		std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings,
        const std::string& jsonString);
};
}
