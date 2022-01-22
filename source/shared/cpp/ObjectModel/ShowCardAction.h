// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "BaseActionElement.h"
#include "ActionParserRegistration.h"

namespace AdaptiveCards
{
class ShowCardAction : public BaseActionElement
{
public:
    ShowCardAction();
    ShowCardAction(const ShowCardAction&) = default;
    ShowCardAction(ShowCardAction&&) = default;
    ShowCardAction& operator=(const ShowCardAction&) = default;
    ShowCardAction& operator=(ShowCardAction&&) = default;
    ~ShowCardAction() = default;

    Json::Value SerializeToJsonValue() const override;

    std::shared_ptr<AdaptiveCards::AdaptiveCard> GetCard() const;
    void SetCard(const std::shared_ptr<AdaptiveCards::AdaptiveCard>);

    void SetLanguage(const std::string& value);

    void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

private:
    void PopulateKnownPropertiesSet();

    std::shared_ptr<AdaptiveCard> m_card;
};

class ShowCardActionParser : public ActionElementParser
{
public:
    ShowCardActionParser() = default;
    ShowCardActionParser(const ShowCardActionParser&) = default;
    ShowCardActionParser(ShowCardActionParser&&) = default;
    ShowCardActionParser& operator=(const ShowCardActionParser&) = default;
    ShowCardActionParser& operator=(ShowCardActionParser&&) = default;
    virtual ~ShowCardActionParser() = default;

    std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
    std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
