// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputElement.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    void AdaptiveInputElementBase::InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseInputElement>& sharedModel)
    {
        AdaptiveCardElementBase::InitializeBaseElement(sharedModel);
        IsRequired = sharedModel->GetIsRequired();
        ErrorMessage = UTF8ToHString(sharedModel->GetErrorMessage());
        Label = UTF8ToHString(sharedModel->GetLabel());
    }

    void AdaptiveInputElementBase::CopySharedElementProperties(::AdaptiveCards::BaseInputElement& sharedCardElement)
    {
        AdaptiveCardElementBase::CopySharedElementProperties(sharedCardElement);
        sharedCardElement.SetIsRequired(IsRequired);
        sharedCardElement.SetErrorMessage(HStringToUTF8(ErrorMessage));
        sharedCardElement.SetLabel(HStringToUTF8(Label));
    }
}
