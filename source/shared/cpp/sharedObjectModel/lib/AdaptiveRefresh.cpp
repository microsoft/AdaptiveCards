#include "pch.h"
#include "AdaptiveRefresh.h"
#include "AdaptiveRefresh.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    AdaptiveRefresh::AdaptiveRefresh(std::shared_ptr<::AdaptiveCards::Refresh> const& sharedRefresh)
    {
        std::vector<winrt::hstring> ids;
        for (auto&& id : sharedRefresh->GetUserIds())
        {
            ids.emplace_back(UTF8ToHString(id));
        }

        Action = GenerateActionProjection(sharedRefresh->GetAction());
        UserIds = winrt::single_threaded_vector<hstring>(std::move(ids));
    }

    std::shared_ptr<::AdaptiveCards::Refresh> AdaptiveRefresh::GetSharedModel()
    {
        auto refresh = std::make_shared<::AdaptiveCards::Refresh>();

        if (Action.get())
        {
            refresh->SetAction(GenerateSharedAction(Action));
        }

        for (auto&& id : UserIds.get())
        {
            refresh->GetUserIds().emplace_back(HStringToUTF8(id));
        }

        return refresh;
    }
}
