// Copyright (c) Microsoft Corporation. All rights reserved.

// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
class ChoicesData
{
public:
    ChoicesData();
    ChoicesData(std::string type, std::string dataset) :
        m_type(type), m_dataset(dataset)
    {
    }

    bool ShouldSerialize() const;
    std::string Serialize() const;
    Json::Value SerializeToJsonValue() const;

    std::string GetType() const;
    void SetType(const std::string& type);

    std::string GetDataset() const;
    void SetDataset(const std::string& dataset);

    static std::shared_ptr<ChoicesData> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<ChoicesData> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::string m_type;
    std::string m_dataset;
};

} // namespace AdaptiveCards
