// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ChoicesData.h"
#include "AdaptiveChoicesData.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
struct DECLSPEC_UUID("C7B2DD8D-B84D-4DC1-991C-215DEF5689E3") AdaptiveChoicesData : AdaptiveChoicesDataT<AdaptiveChoicesData, ITypePeek>
{
    AdaptiveChoicesData() : AdaptiveChoicesData(std::make_shared<::AdaptiveCards::ChoicesData>())
    {
    }
    AdaptiveChoicesData(const std::shared_ptr<::AdaptiveCards::ChoicesData>& sharedChoicesData);

    // IAdaptiveChoiceInput
    hstring Dataset();
    void Dataset(hstring const& dataset);

    hstring ChoicesDataType();
    void ChoicesDataType(hstring const& choicesDataType);

    auto ElementType()
    {
        return Uwp::ElementType::ChoicesData;
    }

    std::shared_ptr<::AdaptiveCards::ChoicesData> GetSharedModel();

    // ITypePeek method
    void* PeekAt(REFIID riid) override
    {
        return PeekHelper(riid, this);
    }

private:
    std::shared_ptr<::AdaptiveCards::ChoicesData> m_sharedChoicesData;
};
} // namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
