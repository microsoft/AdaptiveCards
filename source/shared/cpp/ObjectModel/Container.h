// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "StyledCollectionElement.h"

namespace AdaptiveCards
{
class BaseActionElement;

class Container : public StyledCollectionElement
{
    friend class ContainerParser;

public:
    Container();
    Container(CardElementType derivedType);
    Container(const Container&) = default;
    Container(Container&&) = default;
    Container& operator=(const Container&) = default;
    Container& operator=(Container&&) = default;
    ~Container() = default;

    Json::Value SerializeToJsonValue() const override;
    void DeserializeChildren(ParseContext& context, const Json::Value& value) override;

    std::vector<std::shared_ptr<BaseCardElement>>& GetItems();
    const std::vector<std::shared_ptr<BaseCardElement>>& GetItems() const;

    std::optional<bool> GetRtl() const;
    void SetRtl(const std::optional<bool>& value);

    void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo) override;

private:
    void PopulateKnownPropertiesSet();

    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> m_items;
    std::optional<bool> m_rtl;
};

class ContainerParser : public BaseCardElementParser
{
public:
    ContainerParser() = default;
    ContainerParser(const ContainerParser&) = default;
    ContainerParser(ContainerParser&&) = default;
    ContainerParser& operator=(const ContainerParser&) = default;
    ContainerParser& operator=(ContainerParser&&) = default;
    virtual ~ContainerParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
