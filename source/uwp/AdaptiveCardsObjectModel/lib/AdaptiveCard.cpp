// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCard.h"
#include "AdaptiveCardParseResult.h"
#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveCardParseException.h"
#include "AdaptiveError.h"
#include "AdaptiveWarning.h"
#include <BaseCardElement.h>
#include "AdaptiveCard.g.cpp"

#include <json.h>

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult _FromJsonString(
        std::string const& jsonString,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementParserRegistration,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionParserRegistration)
    {
        std::shared_ptr<::AdaptiveCards::ElementParserRegistration> sharedModelElementParserRegistration;
        if (auto innerElementRegistration = peek_innards<implementation::AdaptiveElementParserRegistration>(elementParserRegistration))
        {
            sharedModelElementParserRegistration = innerElementRegistration->GetSharedParserRegistration();
        }

        std::shared_ptr<::AdaptiveCards::ActionParserRegistration> sharedModelActionParserRegistration;
        if (auto innerActionRegistration = peek_innards<implementation::AdaptiveActionParserRegistration>(actionParserRegistration))
        {
            sharedModelActionParserRegistration = innerActionRegistration->GetSharedParserRegistration();
        }

        auto adaptiveParseResult = winrt::make_self<implementation::AdaptiveCardParseResult>();
        try
        {
            ::AdaptiveCards::ParseContext context(sharedModelElementParserRegistration, sharedModelActionParserRegistration);
            const std::string c_rendererVersion = "1.5";
            auto sharedParseResult = ::AdaptiveCards::AdaptiveCard::DeserializeFromString(jsonString, c_rendererVersion, context);
            adaptiveParseResult->AdaptiveCard =
                *winrt::make_self<implementation::AdaptiveCard>(sharedParseResult->GetAdaptiveCard());
            adaptiveParseResult->Warnings = SharedWarningsToAdaptiveWarnings(sharedParseResult->GetWarnings());
        }
        catch(::AdaptiveCards::AdaptiveCardParseException const& e)
        {
            auto error = winrt::make_self<implementation::AdaptiveError>(
                static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode>(e.GetStatusCode()),
                UTF8ToHString(e.GetReason()));
            adaptiveParseResult->Errors().Append(*error);
        }

        return *adaptiveParseResult;
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult AdaptiveCard::FromJson(winrt::Windows::Data::Json::JsonObject const& adaptiveJson)
    {
        return FromJson(adaptiveJson, nullptr, nullptr);
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult AdaptiveCard::FromJson(
        winrt::Windows::Data::Json::JsonObject const& adaptiveJson,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementRegistration,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionRegistration)
    {
        return _FromJsonString(JsonObjectToString(adaptiveJson), elementRegistration, actionRegistration);
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult AdaptiveCard::FromJsonString(hstring const& adaptiveJson)
    {
        return FromJsonString(adaptiveJson, nullptr, nullptr);
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveCardParseResult AdaptiveCard::FromJsonString(
        hstring const& adaptiveJson,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementRegistration,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionRegistration)
    {
        return _FromJsonString(HStringToUTF8(adaptiveJson), elementRegistration, actionRegistration);
    }

    AdaptiveCard::AdaptiveCard(std::shared_ptr<::AdaptiveCards::AdaptiveCard> const& sharedAdaptiveCard) {
        Body = winrt::single_threaded_vector<Uwp::IAdaptiveCardElement>();
        Actions = winrt::single_threaded_vector<Uwp::IAdaptiveActionElement>();
        Body = GenerateContainedElementsProjection(sharedAdaptiveCard->GetBody());
        Actions = GenerateActionsProjection(sharedAdaptiveCard->GetActions());
        SelectAction = GenerateActionProjection(sharedAdaptiveCard->GetSelectAction());
        Version = UTF8ToHString(sharedAdaptiveCard->GetVersion());
        FallbackText = UTF8ToHString(sharedAdaptiveCard->GetFallbackText());
        Speak = UTF8ToHString(sharedAdaptiveCard->GetSpeak());
        Language = UTF8ToHString(sharedAdaptiveCard->GetLanguage());
        Style = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedAdaptiveCard->GetStyle());
        VerticalContentAlignment = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>(
            sharedAdaptiveCard->GetVerticalContentAlignment());
        Height = static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::HeightType>(sharedAdaptiveCard->GetHeight());
        MinHeight = sharedAdaptiveCard->GetMinHeight();

        auto backgroundImage = sharedAdaptiveCard->GetBackgroundImage();
        if (backgroundImage && !backgroundImage->GetUrl().empty())
        {
            BackgroundImage = *winrt::make_self<implementation::AdaptiveBackgroundImage>(backgroundImage);
        }

        if (auto refresh = sharedAdaptiveCard->GetRefresh())
        {
            Refresh = *winrt::make_self<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveRefresh>(refresh);
        }

        if (auto authentication = sharedAdaptiveCard->GetAuthentication())
        {
            Authentication =
                *winrt::make_self<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveAuthentication>(authentication);
        }

        InternalId = sharedAdaptiveCard->GetInternalId().Hash();
    }

    winrt::Windows::Data::Json::JsonObject AdaptiveCard::ToJson()
    {
        return StringToJsonObject(GetSharedModel()->Serialize());
    }

    std::shared_ptr<::AdaptiveCards::AdaptiveCard> AdaptiveCard::GetSharedModel()
    {
        auto adaptiveCard = std::make_shared<::AdaptiveCards::AdaptiveCard>();

        adaptiveCard->SetVersion(HStringToUTF8(Version));
        adaptiveCard->SetFallbackText(HStringToUTF8(FallbackText));
        adaptiveCard->SetSpeak(HStringToUTF8(Speak));
        adaptiveCard->SetHeight(static_cast<::AdaptiveCards::HeightType>(Height.get()));
        adaptiveCard->SetLanguage(HStringToUTF8(Language));
        adaptiveCard->SetMinHeight(MinHeight);

        auto adaptiveBackgroundImage =
            peek_innards<implementation::AdaptiveBackgroundImage>(BackgroundImage.get());
        std::shared_ptr<::AdaptiveCards::BackgroundImage> sharedBackgroundImage;
        if (adaptiveBackgroundImage && (sharedBackgroundImage = adaptiveBackgroundImage->GetSharedModel()))
        {
            adaptiveCard->SetBackgroundImage(std::move(sharedBackgroundImage));
        }

        adaptiveCard->SetStyle(static_cast<::AdaptiveCards::ContainerStyle>(Style.get()));
        adaptiveCard->SetVerticalContentAlignment(static_cast<::AdaptiveCards::VerticalContentAlignment>(VerticalContentAlignment.get()));

        if (SelectAction.get())
        {
            adaptiveCard->SetSelectAction(GenerateSharedAction(SelectAction));
        }

        adaptiveCard->GetBody() = GenerateSharedElements(Body);
        adaptiveCard->GetActions() = GenerateSharedActions(Actions);

        if (auto refresh = peek_innards<implementation::AdaptiveRefresh>(Refresh.get()))
        {
            adaptiveCard->SetRefresh(refresh->GetSharedModel());
        }

        if (auto authentication = peek_innards<implementation::AdaptiveAuthentication>(Authentication.get()))
        {
            adaptiveCard->SetAuthentication(authentication->GetSharedModel());
        }

        return adaptiveCard;
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRemoteResourceInformation>
    AdaptiveCard::GetResourceInformation()
    {
        std::vector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRemoteResourceInformation> resourceInformation;
        for (auto&& item : GetSharedModel()->GetResourceInformation())
        {
            auto resourceInfo = winrt::make_self<implementation::AdaptiveRemoteResourceInformation>(item);
            resourceInformation.push_back(*resourceInfo);
        }

        return winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRemoteResourceInformation>(
                   std::move(resourceInformation))
            .GetView();
    }
}
