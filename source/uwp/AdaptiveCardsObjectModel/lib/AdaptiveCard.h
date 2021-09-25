// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SharedAdaptiveCard.h"
#include "AdaptiveBackgroundImage.h"
#include "AdaptiveRefresh.h"
#include "AdaptiveAuthentication.h"
#include "AdaptiveRemoteResourceInformation.h"
#include "AdaptiveCard.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct DECLSPEC_UUID("ADF7ECAB-1405-4E42-83B0-ECEFFE7CE728") AdaptiveCard : AdaptiveCardT<AdaptiveCard, ITypePeek>
    {
        AdaptiveCard() : AdaptiveCard(std::make_shared<::AdaptiveCards::AdaptiveCard>()) {}
        AdaptiveCard(std::shared_ptr<::AdaptiveCards::AdaptiveCard> const& sharedAdaptiveCard);

        static winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult FromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson);
        static winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult
        FromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson,
                 winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementRegistration,
                 winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionRegistration);
        static winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult FromJsonString(hstring const& adaptiveJson);
        static winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult FromJsonString(
            hstring const& adaptiveJson,
            winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementRegistration,
            winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionRegistration);

        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement>> Body;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement>> Actions;

        property<Uwp::ElementType> ElementType;
        property<uint32_t> InternalId;
        property<hstring> Version;
        property<hstring> FallbackText;
        property<Uwp::AdaptiveBackgroundImage> BackgroundImage{nullptr};
        property<hstring> Language;
        property<hstring> Speak;
        property<Uwp::ContainerStyle> Style;
        property<Uwp::IAdaptiveActionElement> SelectAction;
        property<Uwp::VerticalContentAlignment> VerticalContentAlignment;
        property<Uwp::HeightType> Height;
        property<uint32_t> MinHeight;
        property<Uwp::AdaptiveRefresh> Refresh{nullptr};
        property<Uwp::AdaptiveAuthentication> Authentication{nullptr};

        winrt::Windows::Data::Json::JsonObject ToJson();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRemoteResourceInformation>
            GetResourceInformation();

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveCard : AdaptiveCardT<AdaptiveCard, implementation::AdaptiveCard>
    {
    };
}
