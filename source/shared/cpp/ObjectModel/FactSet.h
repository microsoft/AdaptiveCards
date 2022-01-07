// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"

namespace AdaptiveCards
{
class Fact;

class FactSet : public BaseCardElement
{
    friend class FactSetParser;

public:
    FactSet();
    FactSet(const FactSet&) = default;
    FactSet(FactSet&&) = default;
    FactSet& operator=(const FactSet&) = default;
    FactSet& operator=(FactSet&&) = default;
    ~FactSet() = default;

    Json::Value SerializeToJsonValue() const override;

    std::vector<std::shared_ptr<Fact>>& GetFacts();
    const std::vector<std::shared_ptr<Fact>>& GetFacts() const;

private:
    void PopulateKnownPropertiesSet();

    std::vector<std::shared_ptr<Fact>> m_facts;
};

class FactSetParser : public BaseCardElementParser
{
public:
    FactSetParser() = default;
    FactSetParser(const FactSetParser&) = default;
    FactSetParser(FactSetParser&&) = default;
    FactSetParser& operator=(const FactSetParser&) = default;
    FactSetParser& operator=(FactSetParser&&) = default;
    virtual ~FactSetParser() = default;

    std::shared_ptr<BaseCardElement> Deserialize(ParseContext& context, const Json::Value& root) override;
    std::shared_ptr<BaseCardElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
