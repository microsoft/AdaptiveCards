// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SharedAdaptiveCard.h"
#include "AdaptiveBackgroundImage.h"
#include "AdaptiveRefresh.h"
#include "AdaptiveAuthentication.h"
#include "AdaptiveRemoteResourceInformation.h"
#include "AdaptiveCard.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct DECLSPEC_UUID("ADF7ECAB-1405-4E42-83B0-ECEFFE7CE728") AdaptiveCard : AdaptiveCardT<AdaptiveCard, ITypePeek>
    {
        AdaptiveCard() : AdaptiveCard(std::make_shared<::AdaptiveCards::AdaptiveCard>()) {}
        AdaptiveCard(std::shared_ptr<::AdaptiveCards::AdaptiveCard> const& sharedAdaptiveCard);

        static winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveCardParseResult FromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson);
        static winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveCardParseResult
        FromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson,
                 winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveElementParserRegistration const& elementRegistration,
                 winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveActionParserRegistration const& actionRegistration);
        static winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveCardParseResult FromJsonString(hstring const& adaptiveJson);
        static winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveCardParseResult FromJsonString(
            hstring const& adaptiveJson,
            winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveElementParserRegistration const& elementRegistration,
            winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveActionParserRegistration const& actionRegistration);

        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveCardElement>> Body;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveActionElement>> Actions;

        property<Xaml_OM::ElementType> ElementType;
        property<uint32_t> InternalId;
        property<hstring> Version;
        property<hstring> FallbackText;
        property<Xaml_OM::AdaptiveBackgroundImage> BackgroundImage{nullptr};
        property<hstring> Language;
        property<hstring> Speak;
        property<Xaml_OM::ContainerStyle> Style;
        property<Xaml_OM::IAdaptiveActionElement> SelectAction;
        property<Xaml_OM::VerticalContentAlignment> VerticalContentAlignment;
        property<Xaml_OM::HeightType> Height;
        property<uint32_t> MinHeight;
        property<Xaml_OM::AdaptiveRefresh> Refresh{nullptr};
        property<Xaml_OM::AdaptiveAuthentication> Authentication{nullptr};
        property<winrt::Windows::Foundation::IReference<bool>> Rtl;

        winrt::Windows::Data::Json::JsonObject ToJson();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveRemoteResourceInformation>
            GetResourceInformation();

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveCard : AdaptiveCardT<AdaptiveCard, implementation::AdaptiveCard>
    {
    };
}
