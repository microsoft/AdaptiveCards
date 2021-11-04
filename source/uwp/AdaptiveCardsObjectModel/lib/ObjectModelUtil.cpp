// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionParserRegistration.h"
#include "AdaptiveActionSet.h"
#include "AdaptiveColumn.h"
#include "AdaptiveColumnSet.h"
#include "AdaptiveContainer.h"
#include "AdaptiveChoiceInput.h"
#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveDateInput.h"
#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveExecuteAction.h"
#include "AdaptiveFact.h"
#include "AdaptiveFactSet.h"
#include "AdaptiveImage.h"
#include "AdaptiveImageSet.h"
#include "AdaptiveMedia.h"
#include "AdaptiveMediaSource.h"
#include "AdaptiveNumberInput.h"
#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveRequirement.h"
#include "AdaptiveRichTextBlock.h"
#include "AdaptiveShowCardAction.h"
#include "AdaptiveSubmitAction.h"
#include "AdaptiveTable.h"
#include "AdaptiveTextBlock.h"
#include "AdaptiveTextInput.h"
#include "AdaptiveTextRun.h"
#include "AdaptiveTimeInput.h"
#include "AdaptiveToggleInput.h"
#include "AdaptiveToggleVisibilityTarget.h"
#include "AdaptiveToggleVisibilityAction.h"
#include "AdaptiveUnsupportedAction.h"
#include "AdaptiveUnsupportedElement.h"
#include "AdaptiveWarning.h"
#include "CustomActionWrapper.h"
#include "CustomElementWrapper.h"
#include "winrt/Windows.Foundation.Collections.h"

using namespace AdaptiveCards;

std::string WStringToString(std::wstring_view in)
{
    const int length_in = static_cast<int>(in.length());

    if (length_in > 0)
    {
        const int length_out = ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, in.data(), length_in, NULL, 0, NULL, NULL);

        if (length_out > 0)
        {
            std::string out(length_out, '\0');

            const int length_written =
                ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, in.data(), length_in, out.data(), length_out, NULL, NULL);

            if (length_written == length_out)
            {
                return out;
            }
        }

        winrt::throw_last_error();
    }

    return {};
}

std::wstring StringToWString(std::string_view in)
{
    const int length_in = static_cast<int>(in.length());

    if (length_in > 0)
    {
        const int length_out = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, in.data(), length_in, NULL, 0);

        if (length_out > 0)
        {
            std::wstring out(length_out, L'\0');

            const int length_written =
                ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, in.data(), length_in, out.data(), length_out);

            if (length_written == length_out)
            {
                return out;
            }
        }

        winrt::throw_last_error();
    }

    return {};
}

winrt::hstring UTF8ToHString(std::string_view in)
{
    return winrt::hstring{StringToWString(in)};
}

std::string HStringToUTF8(winrt::hstring const& in)
{
    return WStringToString(static_cast<std::wstring_view>(in));
}

template<typename TImpl, typename TSrc> auto GetSharedModel(_In_ TSrc const& item)
{
    if (auto adaptiveElement = peek_innards<TImpl>(item))
    {
        return adaptiveElement->GetSharedModel();
    }
    else
    {
        return decltype(peek_innards<TImpl>(item)->GetSharedModel()){};
    }
}

std::shared_ptr<AdaptiveCards::BaseCardElement> GenerateSharedElement(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& item)
{
    namespace rtimpl = winrt::AdaptiveCards::ObjectModel::Uwp::implementation;

    switch (item.ElementType())
    {
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::ActionSet:
        return GetSharedModel<rtimpl::AdaptiveActionSet>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::ChoiceSetInput:
        return GetSharedModel<rtimpl::AdaptiveChoiceSetInput>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Column:
        return GetSharedModel<rtimpl::AdaptiveColumn>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::ColumnSet:
        return GetSharedModel<rtimpl::AdaptiveColumnSet>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Container:
        return GetSharedModel<rtimpl::AdaptiveContainer>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::DateInput:
        return GetSharedModel<rtimpl::AdaptiveDateInput>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::FactSet:
        return GetSharedModel<rtimpl::AdaptiveFactSet>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Image:
        return GetSharedModel<rtimpl::AdaptiveImage>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::ImageSet:
        return GetSharedModel<rtimpl::AdaptiveImageSet>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::NumberInput:
        return GetSharedModel<rtimpl::AdaptiveNumberInput>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Media:
        return GetSharedModel<rtimpl::AdaptiveMedia>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::RichTextBlock:
        return GetSharedModel<rtimpl::AdaptiveRichTextBlock>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::TextBlock:
        return GetSharedModel<rtimpl::AdaptiveTextBlock>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::TextInput:
        return GetSharedModel<rtimpl::AdaptiveTextInput>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::TimeInput:
        return GetSharedModel<rtimpl::AdaptiveTimeInput>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::ToggleInput:
        return GetSharedModel<rtimpl::AdaptiveToggleInput>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Table:
        return GetSharedModel<rtimpl::AdaptiveTable>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Unsupported:
        return GetSharedModel<rtimpl::AdaptiveUnsupportedElement>(item);
    case winrt::AdaptiveCards::ObjectModel::Uwp::ElementType::Custom:
        return std::make_shared<::AdaptiveCards::ObjectModel::Uwp::CustomElementWrapper>(item);
    default:
        throw winrt::hresult_invalid_argument();
    }
}

std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> GenerateSharedElements(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement> const& items)
{
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> containedElements;
    for (auto&& item : items)
    {
        containedElements.emplace_back(GenerateSharedElement(item));
    }
    return containedElements;
}

std::shared_ptr<AdaptiveCards::BaseActionElement> GenerateSharedAction(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action)
{
    namespace rtimpl = winrt::AdaptiveCards::ObjectModel::Uwp::implementation;

    switch (action.ActionType())
    {
    case winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::OpenUrl:
        return peek_innards<rtimpl::AdaptiveOpenUrlAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::ShowCard:
        return peek_innards<rtimpl::AdaptiveShowCardAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::Submit:
        return peek_innards<rtimpl::AdaptiveSubmitAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::ToggleVisibility:
        return peek_innards<rtimpl::AdaptiveToggleVisibilityAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::Execute:
        return peek_innards<rtimpl::AdaptiveExecuteAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::Custom:
        return peek_innards<rtimpl::AdaptiveExecuteAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::Uwp::ActionType::Unsupported:
        return peek_innards<rtimpl::AdaptiveUnsupportedAction>(action)->GetSharedModel();
    }

    return nullptr;
}

std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> GenerateSharedActions(
    _In_ winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> const& actions)
{
    std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> containedElements;
    for (auto&& action : actions)
    {
        containedElements.emplace_back(GenerateSharedAction(action));
    }
    return containedElements;
}

std::unordered_map<std::string, AdaptiveCards::SemanticVersion> GenerateSharedRequirements(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement> const& adaptiveRequirements)
{
    std::unordered_map<std::string, AdaptiveCards::SemanticVersion> sharedRequirements;

    for (auto&& requirement : adaptiveRequirements)
    {
        auto name = HStringToUTF8(requirement.Name());
        auto version = HStringToUTF8(requirement.Version());

        if (version == "*")
        {
            version = "0";
        }

        sharedRequirements.emplace(std::move(name), std::move(version));
    }

    return sharedRequirements;
}

std::vector<std::shared_ptr<AdaptiveCards::Inline>> GenerateSharedInlines(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline> const& inlines)
{
    std::vector<std::shared_ptr<AdaptiveCards::Inline>> results;
    for (auto&& i : inlines)
    {
        if (auto run = peek_innards<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveTextRun>(i))
        {
            results.emplace_back(run->GetSharedModel());
        }
        else
        {
            throw winrt::hresult_not_implemented();
        }
    }
    return results;
}

winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement GenerateElementProjection(const std::shared_ptr<AdaptiveCards::BaseCardElement>& baseElement)
{
    switch (baseElement->GetElementType())
    {
    case CardElementType::TextBlock:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveTextBlock>(
            std::AdaptivePointerCast<AdaptiveCards::TextBlock>(baseElement));
    case CardElementType::Image:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveImage>(
            std::AdaptivePointerCast<AdaptiveCards::Image>(baseElement));
    case CardElementType::Container:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveContainer>(
            std::AdaptivePointerCast<AdaptiveCards::Container>(baseElement));
    case CardElementType::ColumnSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveColumnSet>(
            std::AdaptivePointerCast<AdaptiveCards::ColumnSet>(baseElement));
    case CardElementType::FactSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveFactSet>(
            std::AdaptivePointerCast<AdaptiveCards::FactSet>(baseElement));
    case CardElementType::ImageSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveImageSet>(
            std::AdaptivePointerCast<AdaptiveCards::ImageSet>(baseElement));
    case CardElementType::ChoiceSetInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveChoiceSetInput>(
            std::AdaptivePointerCast<AdaptiveCards::ChoiceSetInput>(baseElement));
    case CardElementType::DateInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveDateInput>(
            std::AdaptivePointerCast<AdaptiveCards::DateInput>(baseElement));
    case CardElementType::Media:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveMedia>(
            std::AdaptivePointerCast<AdaptiveCards::Media>(baseElement));
    case CardElementType::NumberInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveNumberInput>(
            std::AdaptivePointerCast<AdaptiveCards::NumberInput>(baseElement));
    case CardElementType::TextInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveTextInput>(
            std::AdaptivePointerCast<AdaptiveCards::TextInput>(baseElement));
    case CardElementType::TimeInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveTimeInput>(
            std::AdaptivePointerCast<AdaptiveCards::TimeInput>(baseElement));
    case CardElementType::ToggleInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveToggleInput>(
            std::AdaptivePointerCast<AdaptiveCards::ToggleInput>(baseElement));
    case CardElementType::ActionSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveActionSet>(
            std::AdaptivePointerCast<AdaptiveCards::ActionSet>(baseElement));
    case CardElementType::RichTextBlock:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveRichTextBlock>(
            std::AdaptivePointerCast<AdaptiveCards::RichTextBlock>(baseElement));
    case CardElementType::Column:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveColumn>(
            std::AdaptivePointerCast<AdaptiveCards::Column>(baseElement));
    case CardElementType::Table:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveTable>(
            std::AdaptivePointerCast<AdaptiveCards::Table>(baseElement));
    case CardElementType::Custom:
        return std::AdaptivePointerCast<::AdaptiveCards::ObjectModel::Uwp::CustomElementWrapper>(baseElement)->GetWrappedElement();
    case CardElementType::Unknown:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveUnsupportedElement>(
            std::AdaptivePointerCast<AdaptiveCards::UnknownElement>(baseElement));
    default:
        // It should not be possible for an element represented by a CardElementType to not have a matching case here.
        // Either a new element has been introduced in the shared model without full support here in UWP, or there's a
        // bug in the shared model (see https://github.com/microsoft/AdaptiveCards/issues/6393).

        throw winrt::hresult_error(E_UNEXPECTED, L"CardElementType not supported");
    }
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement>
GenerateContainedElementsProjection(const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement> elements;
    for (auto&& containedElement : containedElements)
    {
        elements.emplace_back(GenerateElementProjection(containedElement));
    }
    return winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement>(std::move(elements));
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement>
GenerateActionsProjection(const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedActions)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> actions;
    for (auto&& containedAction : containedActions)
    {
        actions.emplace_back(GenerateActionProjection(containedAction));
    }
    return winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement>(std::move(actions));
}

winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement
GenerateActionProjection(const std::shared_ptr<AdaptiveCards::BaseActionElement>& action)
{
    if (!action)
    {
        return nullptr;
    }

    switch (action->GetElementType())
    {
    case ActionType::OpenUrl:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveOpenUrlAction>(
            std::AdaptivePointerCast<AdaptiveCards::OpenUrlAction>(action));
    case ActionType::ShowCard:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveShowCardAction>(
            std::AdaptivePointerCast<AdaptiveCards::ShowCardAction>(action));
    case ActionType::Submit:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveSubmitAction>(
            std::AdaptivePointerCast<AdaptiveCards::SubmitAction>(action));
    case ActionType::ToggleVisibility:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveToggleVisibilityAction>(
            std::AdaptivePointerCast<AdaptiveCards::ToggleVisibilityAction>(action));
    case ActionType::Execute:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveExecuteAction>(
            std::AdaptivePointerCast<AdaptiveCards::ExecuteAction>(action));
    case ActionType::Custom:
        return std::AdaptivePointerCast<::AdaptiveCards::ObjectModel::Uwp::CustomActionWrapper>(action)->GetWrappedElement();
    case ActionType::UnknownAction:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveUnsupportedAction>(
            std::AdaptivePointerCast<AdaptiveCards::UnknownAction>(action));
    default:
        throw winrt::hresult_error(E_UNEXPECTED);
    }
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline>
GenerateInlinesProjection(const std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline> results;

    for (auto&& containedElement : containedElements)
    {
        switch (containedElement->GetInlineType())
        {
        case InlineElementType::TextRun:
            results.emplace_back(winrt::make<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveTextRun>(
                std::dynamic_pointer_cast<::AdaptiveCards::TextRun>(containedElement)));
            break;
        default:
            throw winrt::hresult_not_implemented();
        }
    }

    return winrt::single_threaded_vector(std::move(results));
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement>
GenerateRequirementsProjection(const std::unordered_map<std::string, SemanticVersion>& sharedRequirements)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement> results;
    for (const auto& sharedRequirement : sharedRequirements)
    {
        auto requirement =
            winrt::make_self<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveRequirement>(sharedRequirement);

        results.emplace_back(*requirement);
    }

    return winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement>(std::move(results));
}

winrt::Windows::Data::Json::JsonObject StringToJsonObject(const std::string& inputString)
{
    return HStringToJsonObject(UTF8ToHString(inputString));
}

winrt::Windows::Data::Json::JsonObject HStringToJsonObject(winrt::hstring const& inputHString)
{
    winrt::Windows::Data::Json::JsonObject result{nullptr};
    if (!winrt::Windows::Data::Json::JsonObject::TryParse(inputHString, result))
    {
        result = winrt::Windows::Data::Json::JsonObject();
    }
    return result;
}

std::string JsonObjectToString(_In_ winrt::Windows::Data::Json::IJsonObject const& inputJson)
{
    return HStringToUTF8(JsonObjectToHString(inputJson));
}

winrt::hstring JsonObjectToHString(_In_ winrt::Windows::Data::Json::IJsonObject const& inputJson)
{
    if (!inputJson)
    {
        throw winrt::hresult_invalid_argument();
    }

    return inputJson.Stringify();
}

winrt::Windows::Data::Json::JsonValue StringToJsonValue(const std::string& inputString)
{
    return HStringToJsonValue(UTF8ToHString(inputString));
}

winrt::Windows::Data::Json::JsonValue HStringToJsonValue(winrt::hstring const& inputHString)
{
    winrt::Windows::Data::Json::JsonValue returned{nullptr};
    if (!winrt::Windows::Data::Json::JsonValue::TryParse(inputHString, returned))
    {
        // NB: While Windows.Data.Json.JsonValue does not have an exposed constructor,
        // the activation factory does support calling ActivateInstance to get a fresh
        // "empty" value.
        returned = winrt::get_activation_factory<decltype(returned)>().ActivateInstance<decltype(returned)>();
    }
    return returned;
}

std::string JsonValueToString(winrt::Windows::Data::Json::IJsonValue const& inputValue)
{
    return HStringToUTF8(JsonValueToHString(inputValue));
}

winrt::hstring JsonValueToHString(winrt::Windows::Data::Json::IJsonValue const& inputJsonValue)
{
    return inputJsonValue.Stringify();
}

winrt::Windows::Data::Json::JsonObject JsonCppToJsonObject(const Json::Value& jsonCppValue)
{
    return StringToJsonObject(ParseUtil::JsonToString(jsonCppValue));
}

Json::Value JsonObjectToJsonCpp(_In_ winrt::Windows::Data::Json::IJsonObject const& jsonObject)
{
    return ParseUtil::GetJsonValueFromString(JsonObjectToString(jsonObject));
}

void RemoteResourceElementToRemoteResourceInformationVector(
    _In_ winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementWithRemoteResources const& remoteResourceElement,
    std::vector<RemoteResourceInformation>& resourceUris)
{
    for (auto&& resourceInformation : remoteResourceElement.GetResourceInformation())
    {
        RemoteResourceInformation uriInfo;
        uriInfo.url = HStringToUTF8(resourceInformation.Url());
        uriInfo.mimeType = HStringToUTF8(resourceInformation.MimeType());
        resourceUris.emplace_back(std::move(uriInfo));
    }
}

void SharedWarningsToAdaptiveWarnings(
    const std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings,
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& toAddTo)
{
    for (const auto& sharedWarning : sharedWarnings)
    {
        auto warning = winrt::make_self<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveWarning>(
            static_cast<winrt::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode>(sharedWarning->GetStatusCode()),
            UTF8ToHString(sharedWarning->GetReason()));
        toAddTo.Append(*warning);
    }
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning>
SharedWarningsToAdaptiveWarnings(const std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings)
{
    auto result = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning>();
    SharedWarningsToAdaptiveWarnings(sharedWarnings, result);
    return result;
}

void AdaptiveWarningsToSharedWarnings(
    _In_ winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& adaptiveWarnings,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings)
{
    for (auto&& adaptiveWarning : adaptiveWarnings)
    {
        sharedWarnings.emplace_back(
            std::make_shared<AdaptiveCardParseWarning>(static_cast<AdaptiveCards::WarningStatusCode>(adaptiveWarning.StatusCode()),
                                                       HStringToUTF8(adaptiveWarning.Message())));
    }
}

winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType MapSharedFallbackTypeToUwp(const AdaptiveCards::FallbackType type)
{
    switch (type)
    {
    case FallbackType::Drop:
    {
        return winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Drop;
    }

    case FallbackType::Content:
    {
        return winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content;
    }

    case FallbackType::None:
    default:
    {
        return winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::None;
    }
    }
}

AdaptiveCards::FallbackType MapUwpFallbackTypeToShared(winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType const& type)
{
    switch (type)
    {
    case winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Drop:
    {
        return FallbackType::Drop;
    }

    case winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::Content:
    {
        return FallbackType::Content;
    }

    case winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType::None:
    default:
    {
        return FallbackType::None;
    }
    }
}

winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration
GetAdaptiveActionParserRegistrationFromSharedModel(const std::shared_ptr<ActionParserRegistration>& sharedActionParserRegistration)
{
    // Look up the well known action parser registration to see if we've got a custom action registration to pass
    if (auto sharedActionParser =
            sharedActionParserRegistration->GetParser(::AdaptiveCards::ObjectModel::Uwp::c_upwActionParserRegistration))
    {
        // The shared model wraps the passed in parsers. Get our SharedModelActionParser from it so we can retrieve the
        // IAdaptiveActionParserRegistration
        auto parserWrapper = std::static_pointer_cast<ActionElementParserWrapper>(sharedActionParser);
        auto sharedModelParser = std::static_pointer_cast<::AdaptiveCards::ObjectModel::Uwp::SharedModelActionParser>(
            parserWrapper->GetActualParser());

        return sharedModelParser->GetAdaptiveParserRegistration();
    }
    else
    {
        return *winrt::make_self<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveActionParserRegistration>();
    }
}

winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration GetAdaptiveElementParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ElementParserRegistration>& sharedElementParserRegistration)
{
    // Look up the well known Element parser registration to see if we've got a custom Element registration to pass
    if (auto sharedElementParser =
            sharedElementParserRegistration->GetParser(::AdaptiveCards::ObjectModel::Uwp::c_uwpElementParserRegistration))
    {
        // The shared model wraps the passed in parsers. Get our SharedModelElementParser from it so we can retrieve the
        // IAdaptiveElementParserRegistration
        auto parserWrapper = std::static_pointer_cast<BaseCardElementParserWrapper>(sharedElementParser);
        auto sharedModelParser = std::static_pointer_cast<::AdaptiveCards::ObjectModel::Uwp::SharedModelElementParser>(
            parserWrapper->GetActualParser());

        return sharedModelParser->GetAdaptiveParserRegistration();
    }
    else
    {
        return *winrt::make_self<winrt::AdaptiveCards::ObjectModel::Uwp::implementation::AdaptiveElementParserRegistration>();
    }
}
