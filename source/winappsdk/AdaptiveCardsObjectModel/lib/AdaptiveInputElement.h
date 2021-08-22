// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "BaseInputElement.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveInputElementBase : AdaptiveCardElementBase
    {
        AdaptiveInputElementBase(ElementType element) : AdaptiveCardElementBase(element) {}
        void InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseInputElement>& sharedModel);

        property<bool> IsRequired;
        property<hstring> ErrorMessage;
        property<hstring> Label;

        void CopySharedElementProperties(AdaptiveCards::BaseInputElement& sharedCardElement);
    };
}
