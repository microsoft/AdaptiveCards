#include "pch.h"
#include "AdaptiveChoicesData.h"
#include "AdaptiveChoicesData.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
AdaptiveChoicesData::AdaptiveChoicesData(const std::shared_ptr<::AdaptiveCards::ChoicesData>& sharedChoicesData)
{
    ChoicesDataType = UTF8ToHString(sharedChoicesData->GetChoicesDataType());
    Dataset = UTF8ToHString(sharedChoicesData->GetDataset());
}

std::shared_ptr<::AdaptiveCards::ChoicesData> AdaptiveChoicesData::GetSharedModel()
{
    auto choicesData = std::make_shared<::AdaptiveCards::ChoicesData>();
    choicesData->SetChoicesDataType(HStringToUTF8(ChoicesDataType));
    choicesData->SetDataset(HStringToUTF8(Dataset));
    return choicesData;
}
} // namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
