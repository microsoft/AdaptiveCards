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
using namespace Microsoft::WRL;
using namespace ABI::Windows::Data::Json;
using namespace Microsoft::WRL;
using namespace AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

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

        throw bad_string_conversion();
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

        throw bad_string_conversion();
    }

    return {};
}

HRESULT UTF8ToHString(std::string_view in, _Outptr_ HSTRING* out) noexcept
try
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    else
    {
        std::wstring wide = StringToWString(in);
        return WindowsCreateString(wide.c_str(), static_cast<UINT32>(wide.length()), out);
    }
}
CATCH_RETURN();

winrt::hstring UTF8ToHString(std::string_view in)
{
    return winrt::hstring{StringToWString(in)};
}

HRESULT HStringToUTF8(HSTRING in, std::string& out) noexcept
try
{
    UINT32 length = 0U;
    const auto* ptr_wide = WindowsGetStringRawBuffer(in, &length);
    out = WStringToString(std::wstring_view(ptr_wide, length));

    return S_OK;
}
CATCH_RETURN();

std::string HStringToUTF8(HSTRING in)
{
    std::string typeAsKey;
    if (SUCCEEDED(HStringToUTF8(in, typeAsKey)))
    {
        return typeAsKey;
    }

    return {};
}

std::string HStringToUTF8(winrt::hstring const& in)
{
    return WStringToString(static_cast<std::wstring_view>(in));
}

template<typename TSharedBaseType, typename TAdaptiveBaseType, typename TAdaptiveType>
std::shared_ptr<AdaptiveCards::BaseCardElement> GetSharedModel(_In_ TAdaptiveBaseType* item)
{
    if (auto adaptiveElement = PeekInnards<TAdaptiveType>(item))
    {
        return adaptiveElement->GetSharedModel();
    }

    return nullptr;
}

HRESULT GenerateSharedElement(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement* item,
                              std::shared_ptr<AdaptiveCards::BaseCardElement>& baseCardElement)
{
    ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType elementType;
    RETURN_IF_FAILED(item->get_ElementType(&elementType));

    switch (elementType)
    {
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::ActionSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionSet>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::ChoiceSetInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveChoiceSetInput>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::Column:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveColumn>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::ColumnSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveColumnSet>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::Container:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveContainer>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::DateInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveDateInput>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::FactSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveFactSet>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::Image:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveImage>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::ImageSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveImageSet>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::NumberInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveNumberInput>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::Media:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveMedia>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::RichTextBlock:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveRichTextBlock>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::TextBlock:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextBlock>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::TextInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveTextInput>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::TimeInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveTimeInput>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::ToggleInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveToggleInput>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::Table:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveTable>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::Unsupported:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement, AdaptiveCards::ObjectModel::WinUI3::AdaptiveUnsupportedElement>(
                item);
        break;
    case ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType::Custom:
        baseCardElement = std::make_shared<CustomElementWrapper>(copy_from_abi<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement>(item));
        break;
    }

    if (baseCardElement == nullptr)
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

std::shared_ptr<AdaptiveCards::BaseCardElement> GenerateSharedElement(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement const& item)
{
    std::shared_ptr<AdaptiveCards::BaseCardElement> returned;
    THROW_IF_FAILED(GenerateSharedElement(item.as<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement>().get(), returned));
    return returned;
}

std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> GenerateSharedElements(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> const& items)
{
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> containedElements;
    for (auto&& item : items)
    {
        containedElements.emplace_back(GenerateSharedElement(item));
    }
    return containedElements;
}

std::shared_ptr<AdaptiveCards::BaseActionElement> GenerateSharedAction(winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement const& action)
{
    namespace rtimpl = winrt::AdaptiveCards::ObjectModel::WinUI3::implementation;

    switch (action.ActionType())
    {
    case winrt::AdaptiveCards::ObjectModel::WinUI3::ActionType::OpenUrl:
        return peek_innards<rtimpl::AdaptiveOpenUrlAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::WinUI3::ActionType::ShowCard:
        return peek_innards<rtimpl::AdaptiveShowCardAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::WinUI3::ActionType::Submit:
        return peek_innards<rtimpl::AdaptiveSubmitAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::WinUI3::ActionType::ToggleVisibility:
        return peek_innards<rtimpl::AdaptiveToggleVisibilityAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::WinUI3::ActionType::Execute:
        return peek_innards<rtimpl::AdaptiveExecuteAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::WinUI3::ActionType::Custom:
        return peek_innards<rtimpl::AdaptiveExecuteAction>(action)->GetSharedModel();
    case winrt::AdaptiveCards::ObjectModel::WinUI3::ActionType::Unsupported:
        return peek_innards<rtimpl::AdaptiveUnsupportedAction>(action)->GetSharedModel();
    }

    return nullptr;
}

std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> GenerateSharedActions(
    _In_ winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> const& actions)
{
    std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> containedElements;
    for (auto&& action : actions)
    {
        containedElements.emplace_back(GenerateSharedAction(action));
    }
    return containedElements;
}


std::unordered_map<std::string, AdaptiveCards::SemanticVersion> GenerateSharedRequirements(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRequirement> const& adaptiveRequirements)
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

std::vector<std::shared_ptr<AdaptiveCards::Inline>> GenerateSharedInlines(winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInline> const& inlines)
{
    std::vector<std::shared_ptr<AdaptiveCards::Inline>> results;
    for (auto&& i : inlines)
    {
        if (auto run = peek_innards<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTextRun>(i))
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


winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement
GenerateElementProjection(const std::shared_ptr<AdaptiveCards::BaseCardElement>& baseElement)
{
    switch (baseElement->GetElementType())
    {
    case CardElementType::TextBlock:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTextBlock>(std::AdaptivePointerCast<AdaptiveCards::TextBlock>(baseElement));
    case CardElementType::Image:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveImage>(std::AdaptivePointerCast<AdaptiveCards::Image>(baseElement));
    case CardElementType::Container:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveContainer>(std::AdaptivePointerCast<AdaptiveCards::Container>(baseElement));
    case CardElementType::ColumnSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveColumnSet>(std::AdaptivePointerCast<AdaptiveCards::ColumnSet>(baseElement));
    case CardElementType::FactSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveFactSet>(
            std::AdaptivePointerCast<AdaptiveCards::FactSet>(baseElement));
    case CardElementType::ImageSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveImageSet>(
            std::AdaptivePointerCast<AdaptiveCards::ImageSet>(baseElement));
    case CardElementType::ChoiceSetInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveChoiceSetInput>(std::AdaptivePointerCast<AdaptiveCards::ChoiceSetInput>(baseElement));
    case CardElementType::DateInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveDateInput>(std::AdaptivePointerCast<AdaptiveCards::DateInput>(baseElement));
    case CardElementType::Media:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveMedia>(std::AdaptivePointerCast<AdaptiveCards::Media>(baseElement));
    case CardElementType::NumberInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveNumberInput>(
            std::AdaptivePointerCast<AdaptiveCards::NumberInput>(baseElement));
    case CardElementType::TextInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTextInput>(
            std::AdaptivePointerCast<AdaptiveCards::TextInput>(baseElement));
    case CardElementType::TimeInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTimeInput>(std::AdaptivePointerCast<AdaptiveCards::TimeInput>(baseElement));
    case CardElementType::ToggleInput:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveToggleInput>(std::AdaptivePointerCast<AdaptiveCards::ToggleInput>(baseElement));
    case CardElementType::ActionSet:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveActionSet>(std::AdaptivePointerCast<AdaptiveCards::ActionSet>(baseElement));
    case CardElementType::RichTextBlock:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveRichTextBlock>(
            std::AdaptivePointerCast<AdaptiveCards::RichTextBlock>(baseElement));
    case CardElementType::Column:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveColumn>(std::AdaptivePointerCast<AdaptiveCards::Column>(baseElement));
    case CardElementType::Table:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTable>(std::AdaptivePointerCast<AdaptiveCards::Table>(baseElement));
        break;
    case CardElementType::Custom:
        return std::AdaptivePointerCast<::AdaptiveCards::ObjectModel::WinUI3::CustomElementWrapper>(baseElement)->GetWrappedElement();
    case CardElementType::Unknown:
    default:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveUnsupportedElement>(
            std::AdaptivePointerCast<AdaptiveCards::UnknownElement>(baseElement));
    }
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> elements;
    for (auto&& containedElement : containedElements)
    {
        elements.emplace_back(GenerateElementProjection(containedElement));
    }
    return winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement>(std::move(elements));
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> GenerateActionsProjection(const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedActions)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement> actions;
    for (auto&& containedAction : containedActions)
    {
        actions.emplace_back(GenerateActionProjection(containedAction));
    }
    return winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement>(std::move(actions));
}

winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement GenerateActionProjection(
    const std::shared_ptr<AdaptiveCards::BaseActionElement>& action)
{
    if (!action)
    {
        return nullptr;
    }

    switch (action->GetElementType())
    {
    case ActionType::OpenUrl:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveOpenUrlAction>(
            std::AdaptivePointerCast<AdaptiveCards::OpenUrlAction>(action));
    case ActionType::ShowCard:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveShowCardAction>(
            std::AdaptivePointerCast<AdaptiveCards::ShowCardAction>(action));
    case ActionType::Submit:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveSubmitAction>(
            std::AdaptivePointerCast<AdaptiveCards::SubmitAction>(action));
    case ActionType::ToggleVisibility:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveToggleVisibilityAction>(
            std::AdaptivePointerCast<AdaptiveCards::ToggleVisibilityAction>(action));
    case ActionType::Execute:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveExecuteAction>(
            std::AdaptivePointerCast<AdaptiveCards::ExecuteAction>(action));
    case ActionType::Custom:
        return std::AdaptivePointerCast<CustomActionWrapper>(action)->GetWrappedElement();
    case ActionType::UnknownAction:
        return winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveUnsupportedAction>(
            std::AdaptivePointerCast<AdaptiveCards::UnknownAction>(action));
    default:
        throw winrt::hresult_error(E_UNEXPECTED);
    }
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInline>
    GenerateInlinesProjection(const std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInline> results;

    for (auto&& containedElement : containedElements)
    {
        // Only support text runs for now
        if (containedElement->GetInlineType() != InlineElementType::TextRun)
        {
            throw winrt::hresult_not_implemented();
        }

        results.emplace_back(winrt::make<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveTextRun>(containedElement));
    }

    return winrt::single_threaded_vector(std::move(results));
}


winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRequirement> GenerateRequirementsProjection(
    const std::unordered_map<std::string, SemanticVersion>& sharedRequirements)
{
    std::vector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRequirement> results;
    for (const auto& sharedRequirement : sharedRequirements)
    {
        auto requirement =
            winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveRequirement>(sharedRequirement);

        results.emplace_back(*requirement);
    }

    return winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveRequirement>(std::move(results));
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
        //      the activation factory does support calling ActivateInstance to get a fresh
        //      "empty" value.
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

void RemoteResourceElementToRemoteResourceInformationVector(_In_ winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveElementWithRemoteResources const& remoteResourceElement,
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


void SharedWarningsToAdaptiveWarnings(const std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings, winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const& toAddTo)
{
    for (const auto& sharedWarning : sharedWarnings)
    {
        auto warning = winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveWarning>(
            static_cast<winrt::AdaptiveCards::ObjectModel::WinUI3::WarningStatusCode>(sharedWarning->GetStatusCode()),
            UTF8ToHString(sharedWarning->GetReason()));
        toAddTo.Append(*warning);
    }
}


winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning>
SharedWarningsToAdaptiveWarnings(const std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings)
{
    auto result = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning>();
    SharedWarningsToAdaptiveWarnings(sharedWarnings, result);
    return result;
}

void AdaptiveWarningsToSharedWarnings(
    _In_ winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const& adaptiveWarnings,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings)
{
    for (auto&& adaptiveWarning : adaptiveWarnings)
    {
        sharedWarnings.emplace_back(
            std::make_shared<AdaptiveCardParseWarning>(static_cast<AdaptiveCards::WarningStatusCode>(adaptiveWarning.StatusCode()),
                                                       HStringToUTF8(adaptiveWarning.Message())));
    }
}

winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType MapSharedFallbackTypeToWinUI3(const AdaptiveCards::FallbackType type)
{
    switch (type)
    {
    case FallbackType::Drop:
    {
        return winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Drop;
    }

    case FallbackType::Content:
    {
        return winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content;
    }

    case FallbackType::None:
    default:
    {
        return winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::None;
    }
    }
}

AdaptiveCards::FallbackType MapWinUI3FallbackTypeToShared(const ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType type)
{
    switch (type)
    {
    case ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Drop:
    {
        return FallbackType::Drop;
    }

    case ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content:
    {
        return FallbackType::Content;
    }

    case ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType::None:
    default:
    {
        return FallbackType::None;
    }
    }
}


AdaptiveCards::FallbackType MapWinUI3FallbackTypeToShared(winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType const& type)
{
    switch (type)
    {
    case winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Drop:
    {
        return FallbackType::Drop;
    }

    case winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::Content:
    {
        return FallbackType::Content;
    }

    case winrt::AdaptiveCards::ObjectModel::WinUI3::FallbackType::None:
    default:
    {
        return FallbackType::None;
    }
    }
}

winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration GetAdaptiveActionParserRegistrationFromSharedModel(
    const std::shared_ptr<ActionParserRegistration>& sharedActionParserRegistration)
{
    // Look up the well known action parser registration to see if we've got a custom action registration to pass
    if (auto sharedActionParser = sharedActionParserRegistration->GetParser(c_upwActionParserRegistration))
    {
        // The shared model wraps the passed in parsers. Get our SharedModelActionParser from it so we can retrieve the
        // IAdaptiveActionParserRegistration
        auto parserWrapper = std::static_pointer_cast<ActionElementParserWrapper>(sharedActionParser);
        auto sharedModelParser = std::static_pointer_cast<SharedModelActionParser>(parserWrapper->GetActualParser());

        return sharedModelParser->GetAdaptiveParserRegistration();
    }
    else
    {
        return *winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveActionParserRegistration>();
    }
}

winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration GetAdaptiveElementParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ElementParserRegistration>& sharedElementParserRegistration)
{
    // Look up the well known Element parser registration to see if we've got a custom Element registration to pass
    if (auto sharedElementParser = sharedElementParserRegistration->GetParser(c_uwpElementParserRegistration))
    {
        // The shared model wraps the passed in parsers. Get our SharedModelElementParser from it so we can retrieve the
        // IAdaptiveElementParserRegistration
        auto parserWrapper = std::static_pointer_cast<BaseCardElementParserWrapper>(sharedElementParser);
        auto sharedModelParser = std::static_pointer_cast<SharedModelElementParser>(parserWrapper->GetActualParser());

        return sharedModelParser->GetAdaptiveParserRegistration();
    }
    else
    {
        return *winrt::make_self<winrt::AdaptiveCards::ObjectModel::WinUI3::implementation::AdaptiveElementParserRegistration>();
    }
}
