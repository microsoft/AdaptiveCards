// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ChoicesData.h"
#include "ParseContext.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

ChoicesData::ChoicesData()
{
}

std::string ChoicesData::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value ChoicesData::SerializeToJsonValue() const
{
    Json::Value root;

    if (!m_type.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ChoicesDataType)] = GetChoicesDataType();
    }

    if (!m_dataset.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Dataset)] = GetDataset();
    }

    return root;
}

// Indicates non-default values have been set. If false, serialization can be safely skipped.
bool ChoicesData::ShouldSerialize() const
{
    return m_type.compare((AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::DataQuery))) != 0 && !m_dataset.empty();
}

std::shared_ptr<ChoicesData> ChoicesData::Deserialize(ParseContext& context, const Json::Value& json)
{
    auto choicesData = std::make_shared<ChoicesData>();
    if (json.isNull())
    {
        return choicesData;
    }

    auto type = ParseUtil::GetString(json, AdaptiveCardSchemaKey::ChoicesDataType, false);
    auto dataset = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Dataset, false);
    bool isValidChoicesData = true;
    if (type.empty())
    {
        isValidChoicesData = false;
        context.warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
            WarningStatusCode::RequiredPropertyMissing,
            "non-empty string has to be given for type in choices.data, none given"));
    }

    if (type.compare((AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::DataQuery))) != 0)
    {
        isValidChoicesData = false;
        context.warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
            WarningStatusCode::InvalidValue, "Invalid type for Choices.data, only Data.Query is supported"));
    }

    if (dataset.empty())
    {
        isValidChoicesData = false;
        context.warnings.emplace_back(std::make_shared<AdaptiveCardParseWarning>(
            WarningStatusCode::RequiredPropertyMissing,
            "non-empty string has to be given for dataset in choices.data, none given"));
    }

    if (isValidChoicesData)
    {
        choicesData->SetChoicesDataType(type);
        choicesData->SetDataset(dataset);
    }

    return choicesData;
}

std::shared_ptr<ChoicesData> ChoicesData::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return ChoicesData::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

std::string ChoicesData::GetChoicesDataType() const
{
    return m_type;
}

void ChoicesData::SetChoicesDataType(const std::string& type)
{
    m_type = type;
}

std::string ChoicesData::GetDataset() const
{
    return m_dataset;
}

void ChoicesData::SetDataset(const std::string& dataset)
{
    m_dataset = dataset;
}
