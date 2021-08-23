// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SharedAdaptiveCard.h"
#include "AdaptiveBackgroundImage.h"
#include "AdaptiveRefresh.h"
#include "AdaptiveAuthentication.h"
#include "AdaptiveRemoteResourceInformation.h"
#include "AdaptiveCard.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct DECLSPEC_UUID("ADF7ECAB-1405-4E42-83B0-ECEFFE7CE728") AdaptiveCard : AdaptiveCardT<AdaptiveCard, ITypePeek>
    {
        AdaptiveCard() : AdaptiveCard(std::make_shared<::AdaptiveCards::AdaptiveCard>()) {}
        AdaptiveCard(std::shared_ptr<::AdaptiveCards::AdaptiveCard> const& sharedAdaptiveCard);

        static winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCardParseResult FromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson);
        static winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCardParseResult
        FromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson,
                 winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& elementRegistration,
                 winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const& actionRegistration);
        static winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCardParseResult FromJsonString(hstring const& adaptiveJson);
        static winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveCardParseResult FromJsonString(
            hstring const& adaptiveJson,
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& elementRegistration,
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const& actionRegistration);

        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement>> Body;
        property<winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement>> Actions;

        property<WinUI3::ElementType> ElementType;
        property<uint32_t> InternalId;
        property<hstring> Version;
        property<hstring> FallbackText;
        property<WinUI3::AdaptiveBackgroundImage> BackgroundImage;
        property<hstring> Language;
        property<hstring> Speak;
        property<WinUI3::ContainerStyle> Style;
        property<WinUI3::IAdaptiveActionElement> SelectAction;
        property<WinUI3::VerticalContentAlignment> VerticalContentAlignment;
        property<WinUI3::HeightType> Height;
        property<uint32_t> MinHeight;
        property<WinUI3::AdaptiveRefresh> Refresh;
        property<WinUI3::AdaptiveAuthentication> Authentication;

        winrt::Windows::Data::Json::JsonObject ToJson();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRemoteResourceInformation>
            GetResourceInformation();

        std::shared_ptr<::AdaptiveCards::AdaptiveCard> GetSharedModel();

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }
    };
}

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveCard : AdaptiveCardT<AdaptiveCard, implementation::AdaptiveCard>
    {
    };
}
