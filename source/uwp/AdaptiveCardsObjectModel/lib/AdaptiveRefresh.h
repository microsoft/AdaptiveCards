#pragma once
#include "Refresh.h"
#include "AdaptiveRefresh.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct DECLSPEC_UUID("8D452985-D06B-4541-AEAF-DD7A3DC7CCD8") AdaptiveRefresh : AdaptiveRefreshT<AdaptiveRefresh, ITypePeek>
    {
        AdaptiveRefresh() : AdaptiveRefresh(std::make_shared<::AdaptiveCards::Refresh>()) {}
        AdaptiveRefresh(std::shared_ptr<::AdaptiveCards::Refresh> const& sharedRefresh);

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        std::shared_ptr<::AdaptiveCards::Refresh> GetSharedModel();

        property<WinUI3::IAdaptiveActionElement> Action;
        property<winrt::Windows::Foundation::Collections::IVector<hstring>> UserIds;
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveRefresh : AdaptiveRefreshT<AdaptiveRefresh, implementation::AdaptiveRefresh>
    {
    };
}
