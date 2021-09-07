// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleVisibilityAction.h"
#include "AdaptiveToggleVisibilityAction.g.cpp"
#include "AdaptiveToggleVisibilityTarget.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    template<typename TRtType, typename TRtImplType, typename TSharedClass>
    auto project_vector(std::vector<std::shared_ptr<TSharedClass>> const& elements)
    {
        std::vector<TRtType> converted;
        for (auto&& e : elements)
        {
            auto c = winrt::make<TRtImplType>(e);
            converted.emplace_back(c);
        }
        return winrt::single_threaded_vector(std::move(converted));
    }

    template<typename TShared, typename TRtImpl, typename TRtType>
    auto project_vector(winrt::Windows::Foundation::Collections::IVector<TRtType> const& elements)
    {
        std::vector<std::shared_ptr<TShared>> converted;
        for (auto&& e : elements)
        {
            auto impl = peek_innards<TRtImpl>(e);
            converted.emplace_back(std::AdaptivePointerCast<TShared>(impl->GetSharedModel()));
        }
        return converted;
    }

    AdaptiveToggleVisibilityAction::AdaptiveToggleVisibilityAction(const std::shared_ptr<::AdaptiveCards::ToggleVisibilityAction>& sharedToggleVisibilityAction)
    {
        TargetElements = project_vector<Uwp::AdaptiveToggleVisibilityTarget, implementation::AdaptiveToggleVisibilityTarget>(sharedToggleVisibilityAction->GetTargetElements());
        InitializeBaseElement(sharedToggleVisibilityAction);
    }

    Uwp::ActionType AdaptiveToggleVisibilityAction::ActionType()
    {
        return winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::ToggleVisibility;
    }

    std::shared_ptr<::AdaptiveCards::BaseActionElement> AdaptiveToggleVisibilityAction::GetSharedModel()
    {
        auto toggleVisibilityAction = std::make_shared<::AdaptiveCards::ToggleVisibilityAction>();
        CopySharedElementProperties(*toggleVisibilityAction);
        toggleVisibilityAction->GetTargetElements() =
            project_vector<::AdaptiveCards::ToggleVisibilityTarget, implementation::AdaptiveToggleVisibilityTarget>(
                TargetElements.get());

        return toggleVisibilityAction;
    }
}
