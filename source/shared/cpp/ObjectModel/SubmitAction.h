#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "Enums.h"

namespace AdaptiveCards
{
class SubmitAction : public BaseActionElement
{
public:
    SubmitAction();

    static std::shared_ptr<SubmitAction> Deserialize(const Json::Value& root);
    static std::shared_ptr<SubmitAction> DeserializeFromString(const std::string& jsonString);

    virtual std::string Serialize();
};
}