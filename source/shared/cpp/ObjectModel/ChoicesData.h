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

    bool ShouldSerialize();
    std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::string GetChoicesDataType() const;
    void SetChoicesDataType(const std::string& type);

    std::string GetDataset() const;
    void SetDataset(const std::string& dataset);

    static std::shared_ptr<ChoicesData> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<ChoicesData> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::string m_type;
    std::string m_dataset;
};

} // namespace AdaptiveCards
