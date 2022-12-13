// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveChoicesData.h"
#include "AdaptiveChoicesData.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
AdaptiveChoicesData::AdaptiveChoicesData(const std::shared_ptr<::AdaptiveCards::ChoicesData>& sharedChoicesData) :
    m_sharedChoicesData(sharedChoicesData)
{
}

hstring AdaptiveChoicesData::ChoicesDataType()
{
    return UTF8ToHString(m_sharedChoicesData->GetChoicesDataType());
}

void AdaptiveChoicesData::ChoicesData(hstring const& choicesDataType)
{
    m_sharedChoicesData->SetChoicesDataType(HStringToUTF8(choicesDataType));
}

hstring AdaptiveChoicesData::Dataset()
{
    return UTF8ToHString(m_sharedChoicesData->GetDataset());
}

void AdaptiveChoicesData::Dataset(hstring const& dataset)
{
    m_sharedChoicesData->SetDataset(HStringToUTF8(dataset));
}

std::shared_ptr<::AdaptiveCards::ChoicesData> AdaptiveChoicesData::GetSharedModel()
{
    return m_sharedChoicesData;
}
} // namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
