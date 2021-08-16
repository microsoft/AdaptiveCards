// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ExecuteAction.h"
#include "AdaptiveActionElement.h"
#include "AdaptiveExecuteAction.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct DECLSPEC_UUID("05764D21-0053-4282-A254-10A93BA21D7B") AdaptiveExecuteAction : AdaptiveExecuteActionT < AdaptiveExecuteAction, ITypePeek>, AdaptiveActionElementBase
    {
    public:
        AdaptiveExecuteAction(const std::shared_ptr<::AdaptiveCards::ExecuteAction>& sharedExecuteAction =
                                  std::make_shared<::AdaptiveCards::ExecuteAction>());

        // IAdaptiveActionElement
        auto ActionType() { return WinUI3::ActionType::Execute; }

        std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        property<winrt::Windows::Data::Json::JsonValue> DataJson;
        property<WinUI3::AssociatedInputs> AssociatedInputs;
        property<hstring> Verb;
    };
}

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveExecuteAction : AdaptiveExecuteActionT<AdaptiveExecuteAction, implementation::AdaptiveExecuteAction>
    {
    };
}
