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

        std::vector<std::shared_ptr<BaseActionElement>>& GetActions();
        const std::vector<std::shared_ptr<BaseActionElement>>& GetActions() const;

    private:
        void PopulateKnownPropertiesSet();
        std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> m_actions;
        ActionsOrientation m_orientation;
    };

    class ActionSetParser : public BaseCardElementParser
    {
    public:
        std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root);

        std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& contexts, const std::string& jsonString);
    };
}
