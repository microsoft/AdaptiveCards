// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include <regex>

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
#include "AdaptiveFeatureRegistration.h"
#include "AdaptiveImage.h"
#include "AdaptiveImageSet.h"
#include "AdaptiveMedia.h"
#include "AdaptiveMediaSource.h"
#include "AdaptiveNumberInput.h"
#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveRequirement.h"
#include "AdaptiveRichTextBlock.h"
#include "AdaptiveSeparator.h"
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
#include "XamlHelpers.h"

using namespace AdaptiveCards;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::UI;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

HRESULT WStringToHString(std::wstring_view in, _Outptr_ HSTRING* out) noexcept
try
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    else if (in.empty())
    {
        return WindowsCreateString(L"", 0, out);
    }
    else
    {
        return WindowsCreateString(in.data(), static_cast<UINT32>(in.length()), out);
    }
}
CATCH_RETURN;

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
CATCH_RETURN;

HRESULT HStringToUTF8(HSTRING in, std::string& out) noexcept
try
{
    UINT32 length = 0U;
    const auto* ptr_wide = WindowsGetStringRawBuffer(in, &length);
    out = WStringToString(std::wstring_view(ptr_wide, length));

    return S_OK;
}
CATCH_RETURN;

std::string HStringToUTF8(HSTRING in)
{
    std::string typeAsKey;
    if (SUCCEEDED(HStringToUTF8(in, typeAsKey)))
    {
        return typeAsKey;
    }

    return {};
}

template<typename TSharedBaseType, typename TAdaptiveBaseType, typename TAdaptiveType>
std::shared_ptr<TSharedBaseType> GetSharedModel(_In_ TAdaptiveBaseType* item)
{
    ComPtr<TAdaptiveType> adaptiveElement = PeekInnards<TAdaptiveType>(item);

    std::shared_ptr<TSharedBaseType> sharedModelElement;
    if (adaptiveElement && SUCCEEDED(adaptiveElement->GetSharedModel(sharedModelElement)))
    {
        return sharedModelElement;
    }
    else
    {
        return nullptr;
    }
}

HRESULT GenerateSharedElement(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* item,
                              std::shared_ptr<AdaptiveCards::BaseCardElement>& baseCardElement)
{
    ABI::AdaptiveCards::Rendering::Uwp::ElementType elementType;
    RETURN_IF_FAILED(item->get_ElementType(&elementType));

    switch (elementType)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::ActionSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveActionSet>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::ChoiceSetInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveChoiceSetInput>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::Column:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveColumn>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::ColumnSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveColumnSet>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::Container:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveContainer>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::DateInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveDateInput>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::FactSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveFactSet>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::Image:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveImage>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::ImageSet:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveImageSet>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::NumberInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveNumberInput>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::Media:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveMedia>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::RichTextBlock:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveRichTextBlock>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::TextBlock:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveTextBlock>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::TextInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveTextInput>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::TimeInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveTimeInput>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::ToggleInput:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveToggleInput>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::Table:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveTable>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::Unsupported:
        baseCardElement =
            GetSharedModel<AdaptiveCards::BaseCardElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement, AdaptiveCards::Rendering::Uwp::AdaptiveUnsupportedElement>(
                item);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ElementType::Custom:
        baseCardElement = std::make_shared<CustomElementWrapper>(item);
        break;
    }

    if (baseCardElement == nullptr)
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT GenerateSharedElements(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement*>* items,
                               std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements)
{
    containedElements.clear();

    IterateOverVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement>(
        items, [&](ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* item) {
            std::shared_ptr<AdaptiveCards::BaseCardElement> baseCardElement;
            RETURN_IF_FAILED(GenerateSharedElement(item, baseCardElement));
            containedElements.push_back(std::move(baseCardElement));

            return S_OK;
        });

    return S_OK;
}

HRESULT GenerateSharedAction(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* action,
                             std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedAction)
{
    ABI::AdaptiveCards::Rendering::Uwp::ActionType actionType;
    RETURN_IF_FAILED(action->get_ActionType(&actionType));

    switch (actionType)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::ActionType::OpenUrl:
        sharedAction =
            GetSharedModel<AdaptiveCards::BaseActionElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement, AdaptiveCards::Rendering::Uwp::AdaptiveOpenUrlAction>(
                action);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ActionType::ShowCard:
        sharedAction =
            GetSharedModel<AdaptiveCards::BaseActionElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement, AdaptiveCards::Rendering::Uwp::AdaptiveShowCardAction>(
                action);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ActionType::Submit:
        sharedAction =
            GetSharedModel<AdaptiveCards::BaseActionElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement, AdaptiveCards::Rendering::Uwp::AdaptiveSubmitAction>(
                action);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ActionType::ToggleVisibility:
        sharedAction =
            GetSharedModel<AdaptiveCards::BaseActionElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement, AdaptiveCards::Rendering::Uwp::AdaptiveToggleVisibilityAction>(
                action);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ActionType::Execute:
        sharedAction =
            GetSharedModel<AdaptiveCards::BaseActionElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement, AdaptiveCards::Rendering::Uwp::AdaptiveExecuteAction>(
                action);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ActionType::Custom:
        sharedAction = std::make_shared<CustomActionWrapper>(action);
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ActionType::Unsupported:
        sharedAction =
            GetSharedModel<AdaptiveCards::BaseActionElement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement, AdaptiveCards::Rendering::Uwp::AdaptiveUnsupportedAction>(
                action);
    }

    return S_OK;
}

HRESULT GenerateSharedActions(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement*>* actions,
                              std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedElements)
{
    containedElements.clear();

    IterateOverVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement>(
        actions, [&](ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* action) {
            std::shared_ptr<AdaptiveCards::BaseActionElement> baseActionElement;
            GenerateSharedAction(action, baseActionElement);
            containedElements.push_back(baseActionElement);
            return S_OK;
        });

    return S_OK;
}

HRESULT GenerateSharedRequirements(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRequirement*>* adaptiveRequirements,
    std::unordered_map<std::string, AdaptiveCards::SemanticVersion>& sharedRequirements) noexcept
try
{
    sharedRequirements.clear();

    IterateOverVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRequirement, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRequirement>(
        adaptiveRequirements, [&](ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRequirement* requirement) {
            HString nameHString;
            RETURN_IF_FAILED(requirement->get_Name(nameHString.GetAddressOf()));

            HString versionHString;
            RETURN_IF_FAILED(requirement->get_Version(versionHString.GetAddressOf()));

            std::string nameString;
            RETURN_IF_FAILED(HStringToUTF8(nameHString.Get(), nameString));

            std::string versionString;
            RETURN_IF_FAILED(HStringToUTF8(versionHString.Get(), versionString));

            if (versionString == "*")
            {
                sharedRequirements.emplace(std::move(nameString), "0");
            }
            else
            {
                sharedRequirements.emplace(std::move(nameString), std::move(versionString));
            }

            return S_OK;
        });

    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateSharedInlines(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline*>* inlines,
                              std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements)
{
    containedElements.clear();

    IterateOverVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline>(
        inlines, [&](ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline* thisInline) {
            // We only support text runs for now
            ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveTextRun> adaptiveTextRun =
                PeekInnards<AdaptiveCards::Rendering::Uwp::AdaptiveTextRun>(thisInline);
            if (adaptiveTextRun == nullptr)
            {
                return E_INVALIDARG;
            }

            std::shared_ptr<AdaptiveCards::TextRun> sharedTextRun;
            RETURN_IF_FAILED(adaptiveTextRun->GetSharedModel(sharedTextRun));
            containedElements.push_back(std::AdaptivePointerCast<AdaptiveCards::Inline>(sharedTextRun));
            return S_OK;
        });

    return S_OK;
}

HRESULT GenerateElementProjection(_In_ const std::shared_ptr<AdaptiveCards::BaseCardElement>& baseElement,
                                  _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** projectedElement) noexcept
try
{
    *projectedElement = nullptr;
    switch (baseElement->GetElementType())
    {
    case CardElementType::TextBlock:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveTextBlock>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::TextBlock>(baseElement)));
        break;
    case CardElementType::Image:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveImage>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::Image>(baseElement)));
        break;
    case CardElementType::Container:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveContainer>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::Container>(baseElement)));
        break;
    case CardElementType::ColumnSet:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveColumnSet>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::ColumnSet>(baseElement)));
        break;
    case CardElementType::FactSet:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveFactSet>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::FactSet>(baseElement)));
        break;
    case CardElementType::ImageSet:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveImageSet>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::ImageSet>(baseElement)));
        break;
    case CardElementType::ChoiceSetInput:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveChoiceSetInput>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::ChoiceSetInput>(baseElement)));
        break;
    case CardElementType::DateInput:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveDateInput>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::DateInput>(baseElement)));
        break;
    case CardElementType::Media:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveMedia>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::Media>(baseElement)));
        break;
    case CardElementType::NumberInput:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveNumberInput>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::NumberInput>(baseElement)));
        break;
    case CardElementType::TextInput:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveTextInput>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::TextInput>(baseElement)));
        break;
    case CardElementType::TimeInput:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveTimeInput>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::TimeInput>(baseElement)));
        break;
    case CardElementType::ToggleInput:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveToggleInput>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::ToggleInput>(baseElement)));
        break;
    case CardElementType::ActionSet:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveActionSet>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::ActionSet>(baseElement)));
        break;
    case CardElementType::RichTextBlock:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveRichTextBlock>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::RichTextBlock>(baseElement)));
        break;
    case CardElementType::Column:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveColumn>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::Column>(baseElement)));
        break;
    case CardElementType::Table:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveTable>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::Table>(baseElement)));
        break;
    case CardElementType::Custom:
        RETURN_IF_FAILED(
            std::AdaptivePointerCast<::AdaptiveCards::Rendering::Uwp::CustomElementWrapper>(baseElement)->GetWrappedElement(projectedElement));
        break;
    case CardElementType::Unknown:
    default:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveUnsupportedElement>(
            projectedElement, std::AdaptivePointerCast<AdaptiveCards::UnknownElement>(baseElement)));
        break;
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement*>* projectedParentContainer) noexcept
try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement> projectedContainedElement;
        GenerateElementProjection(containedElement, &projectedContainedElement);
        if (projectedContainedElement != nullptr)
        {
            RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
        }
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedActions,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement*>* projectedParentContainer) noexcept
try
{
    for (auto& containedAction : containedActions)
    {
        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement> projectedContainedAction;
        RETURN_IF_FAILED(GenerateActionProjection(containedAction, &projectedContainedAction));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedAction.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateActionProjection(const std::shared_ptr<AdaptiveCards::BaseActionElement>& action,
                                 _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement** projectedAction) noexcept
try
{
    if (action == nullptr)
    {
        *projectedAction = nullptr;
        return S_OK;
    }

    switch (action->GetElementType())
    {
    case ActionType::OpenUrl:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveOpenUrlAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveCards::OpenUrlAction>(action)));
        break;
    case ActionType::ShowCard:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveShowCardAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveCards::ShowCardAction>(action)));
        break;
    case ActionType::Submit:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveSubmitAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveCards::SubmitAction>(action)));
        break;
    case ActionType::ToggleVisibility:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveToggleVisibilityAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveCards::ToggleVisibilityAction>(action)));
        break;
    case ActionType::Execute:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveExecuteAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveCards::ExecuteAction>(action)));
        break;
    case ActionType::Custom:
        RETURN_IF_FAILED(std::AdaptivePointerCast<CustomActionWrapper>(action)->GetWrappedElement(projectedAction));
        break;
    case ActionType::UnknownAction:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveUnsupportedAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveCards::UnknownAction>(action)));
        break;
    default:
        return E_UNEXPECTED;
        break;
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateInlinesProjection(const std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements,
                                  ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline*>* projectedParentContainer) noexcept
try
{
    for (auto& containedElement : containedElements)
    {
        // Only support text runs for now
        if (containedElement->GetInlineType() != InlineElementType::TextRun)
        {
            return E_NOTIMPL;
        }

        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveTextRun>(
            &projectedContainedElement, std::static_pointer_cast<AdaptiveCards::TextRun>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateRequirementsProjection(
    const std::unordered_map<std::string, SemanticVersion>& sharedRequirements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRequirement*>* projectedRequirementVector) noexcept
try
{
    for (const auto& sharedRequirement : sharedRequirements)
    {
        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRequirement> projectedRequirement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Rendering::Uwp::AdaptiveRequirement>(&projectedRequirement, sharedRequirement));
        RETURN_IF_FAILED(projectedRequirementVector->Append(projectedRequirement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

// Get a Color object from color string
// Expected formats are "#AARRGGBB" (with alpha channel) and "#RRGGBB" (without alpha channel)
HRESULT GetColorFromString(const std::string& colorString, _Out_ ABI::Windows::UI::Color* color) noexcept
try
{
    if (colorString.length() > 0 && colorString.front() == '#')
    {
        // Get the pure hex value (without #)
        std::string hexColorString = colorString.substr(1, std::string::npos);

        std::regex colorWithAlphaRegex("[0-9a-f]{8}", std::regex_constants::icase);
        if (regex_match(hexColorString, colorWithAlphaRegex))
        {
            // If color string has alpha channel, extract and set to color
            std::string alphaString = hexColorString.substr(0, 2);
            INT32 alpha = strtol(alphaString.c_str(), nullptr, 16);

            color->A = static_cast<BYTE>(alpha);

            hexColorString = hexColorString.substr(2, std::string::npos);
        }
        else
        {
            // Otherwise, set full opacity
            std::string alphaString = "FF";
            INT32 alpha = strtol(alphaString.c_str(), nullptr, 16);
            color->A = static_cast<BYTE>(alpha);
        }

        // A valid string at this point should have 6 hex characters (RRGGBB)
        std::regex colorWithoutAlphaRegex("[0-9a-f]{6}", std::regex_constants::icase);
        if (regex_match(hexColorString, colorWithoutAlphaRegex))
        {
            // Then set all other Red, Green, and Blue channels
            std::string redString = hexColorString.substr(0, 2);
            INT32 red = strtol(redString.c_str(), nullptr, 16);

            std::string greenString = hexColorString.substr(2, 2);
            INT32 green = strtol(greenString.c_str(), nullptr, 16);

            std::string blueString = hexColorString.substr(4, 2);
            INT32 blue = strtol(blueString.c_str(), nullptr, 16);

            color->R = static_cast<BYTE>(red);
            color->G = static_cast<BYTE>(green);
            color->B = static_cast<BYTE>(blue);

            return S_OK;
        }
    }

    // All other formats are ignored (set alpha to 0)
    color->A = static_cast<BYTE>(0);

    return S_OK;
}
CATCH_RETURN;

HRESULT GetContainerStyleDefinition(ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle style,
                                    _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                    _Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** styleDefinition) noexcept
try
{
    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStylesDefinition> containerStyles;
    RETURN_IF_FAILED(hostConfig->get_ContainerStyles(&containerStyles));

    switch (style)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle::Accent:
        RETURN_IF_FAILED(containerStyles->get_Accent(styleDefinition));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle::Attention:
        RETURN_IF_FAILED(containerStyles->get_Attention(styleDefinition));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle::Emphasis:
        RETURN_IF_FAILED(containerStyles->get_Emphasis(styleDefinition));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle::Good:
        RETURN_IF_FAILED(containerStyles->get_Good(styleDefinition));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle::Warning:
        RETURN_IF_FAILED(containerStyles->get_Warning(styleDefinition));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle::Default:
    default:
        RETURN_IF_FAILED(containerStyles->get_Default(styleDefinition));
        break;
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GetColorFromAdaptiveColor(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor adaptiveColor,
                                  ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle containerStyle,
                                  bool isSubtle,
                                  bool highlight,
                                  _Out_ ABI::Windows::UI::Color* uiColor) noexcept
try
{
    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> styleDefinition;
    GetContainerStyleDefinition(containerStyle, hostConfig, &styleDefinition);

    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorsConfig> colorsConfig;
    RETURN_IF_FAILED(styleDefinition->get_ForegroundColors(&colorsConfig));

    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> colorConfig;
    switch (adaptiveColor)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Accent:
        RETURN_IF_FAILED(colorsConfig->get_Accent(&colorConfig));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Dark:
        RETURN_IF_FAILED(colorsConfig->get_Dark(&colorConfig));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Light:
        RETURN_IF_FAILED(colorsConfig->get_Light(&colorConfig));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Good:
        RETURN_IF_FAILED(colorsConfig->get_Good(&colorConfig));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Warning:
        RETURN_IF_FAILED(colorsConfig->get_Warning(&colorConfig));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Attention:
        RETURN_IF_FAILED(colorsConfig->get_Attention(&colorConfig));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Default:
    default:
        RETURN_IF_FAILED(colorsConfig->get_Default(&colorConfig));
        break;
    }

    if (highlight)
    {
        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHighlightColorConfig> highlightColorConfig;
        RETURN_IF_FAILED(colorConfig->get_HighlightColors(&highlightColorConfig));
        RETURN_IF_FAILED(isSubtle ? highlightColorConfig->get_Subtle(uiColor) : highlightColorConfig->get_Default(uiColor));
    }
    else
    {
        RETURN_IF_FAILED(isSubtle ? colorConfig->get_Subtle(uiColor) : colorConfig->get_Default(uiColor));
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT GetHighlighter(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                       _Out_ ABI::Windows::UI::Xaml::Documents::ITextHighlighter** textHighlighter) noexcept
{
    ComPtr<ABI::Windows::UI::Xaml::Documents::ITextHighlighter> localTextHighlighter =
        XamlHelpers::CreateXamlClass<ABI::Windows::UI::Xaml::Documents::ITextHighlighter>(
            HStringReference(RuntimeClass_Windows_UI_Xaml_Documents_TextHighlighter));

    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig> hostConfig;
    RETURN_IF_FAILED(renderContext->get_HostConfig(&hostConfig));

    ComPtr<IReference<ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor>> adaptiveForegroundColorRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_Color(&adaptiveForegroundColorRef));

    ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor adaptiveForegroundColor =
        ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor::Default;
    if (adaptiveForegroundColorRef != nullptr)
    {
        adaptiveForegroundColorRef->get_Value(&adaptiveForegroundColor);
    }

    ComPtr<IReference<bool>> isSubtleRef;
    RETURN_IF_FAILED(adaptiveTextElement->get_IsSubtle(&isSubtleRef));

    boolean isSubtle = false;
    if (isSubtleRef != nullptr)
    {
        isSubtleRef->get_Value(&isSubtle);
    }

    ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle containerStyle;
    RETURN_IF_FAILED(renderArgs->get_ContainerStyle(&containerStyle));

    ABI::Windows::UI::Color backgroundColor;
    RETURN_IF_FAILED(GetColorFromAdaptiveColor(hostConfig.Get(), adaptiveForegroundColor, containerStyle, isSubtle, true, &backgroundColor));

    ABI::Windows::UI::Color foregroundColor;
    RETURN_IF_FAILED(GetColorFromAdaptiveColor(hostConfig.Get(), adaptiveForegroundColor, containerStyle, isSubtle, false, &foregroundColor));

    RETURN_IF_FAILED(localTextHighlighter->put_Background(XamlHelpers::GetSolidColorBrush(backgroundColor).Get()));
    RETURN_IF_FAILED(localTextHighlighter->put_Foreground(XamlHelpers::GetSolidColorBrush(foregroundColor).Get()));

    localTextHighlighter.CopyTo(textHighlighter);
    return S_OK;
}

HRESULT GetSpacingSizeFromSpacing(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing,
                                  _Out_ UINT* spacingSize) noexcept
try
{
    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSpacingConfig> spacingConfig;
    RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

    switch (spacing)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::Spacing::None:
        *spacingSize = 0;
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::Spacing::Small:
        RETURN_IF_FAILED(spacingConfig->get_Small(spacingSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::Spacing::Medium:
        RETURN_IF_FAILED(spacingConfig->get_Medium(spacingSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::Spacing::Large:
        RETURN_IF_FAILED(spacingConfig->get_Large(spacingSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::Spacing::ExtraLarge:
        RETURN_IF_FAILED(spacingConfig->get_ExtraLarge(spacingSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::Spacing::Padding:
        RETURN_IF_FAILED(spacingConfig->get_Padding(spacingSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::Spacing::Default:
    default:
        RETURN_IF_FAILED(spacingConfig->get_Default(spacingSize));
        break;
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT GetBackgroundColorFromStyle(ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle style,
                                    _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept
try
{
    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> styleDefinition;
    RETURN_IF_FAILED(GetContainerStyleDefinition(style, hostConfig, &styleDefinition));
    RETURN_IF_FAILED(styleDefinition->get_BackgroundColor(backgroundColor));

    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontDataFromFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                                ABI::AdaptiveCards::Rendering::Uwp::TextSize desiredSize,
                                ABI::AdaptiveCards::Rendering::Uwp::TextWeight desiredWeight,
                                _Outptr_ HSTRING* resultFontFamilyName,
                                _Out_ UINT32* resultSize,
                                _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept
try
{
    RETURN_IF_FAILED(GetFontFamilyFromFontType(hostConfig, fontType, resultFontFamilyName));
    RETURN_IF_FAILED(GetFontSizeFromFontType(hostConfig, fontType, desiredSize, resultSize));
    RETURN_IF_FAILED(GetFontWeightFromStyle(hostConfig, fontType, desiredWeight, resultWeight));
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontFamilyFromFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                                  _Outptr_ HSTRING* resultFontFamilyName) noexcept
try
{
    HString result;
    ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypeDefinition* typeDefinition;

    // get FontFamily from desired style
    RETURN_IF_FAILED(GetFontType(hostConfig, fontType, &typeDefinition));
    RETURN_IF_FAILED(typeDefinition->get_FontFamily(result.GetAddressOf()));
    if (result == NULL)
    {
        if (fontType == ABI::AdaptiveCards::Rendering::Uwp::FontType::Monospace)
        {
            // fallback to system default monospace FontFamily
            RETURN_IF_FAILED(UTF8ToHString("Courier New", result.GetAddressOf()));
        }
        else
        {
            // fallback to deprecated FontFamily
            RETURN_IF_FAILED(hostConfig->get_FontFamily(result.GetAddressOf()));
            if (result == NULL)
            {
                // fallback to system default FontFamily
                RETURN_IF_FAILED(UTF8ToHString("Segoe UI", result.GetAddressOf()));
            }
        }
    }
    return result.CopyTo(resultFontFamilyName);
}
CATCH_RETURN;

HRESULT GetFontSizeFromFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                                ABI::AdaptiveCards::Rendering::Uwp::TextSize desiredSize,
                                _Out_ UINT32* resultSize) noexcept
try
{
    UINT32 result;
    ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypeDefinition* fontTypeDefinition;
    ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontSizesConfig* sizesConfig;

    // get FontSize from desired style
    RETURN_IF_FAILED(GetFontType(hostConfig, fontType, &fontTypeDefinition));
    RETURN_IF_FAILED(fontTypeDefinition->get_FontSizes(&sizesConfig));
    RETURN_IF_FAILED(GetFontSize(sizesConfig, desiredSize, &result));

    if (result == MAXUINT32)
    {
        // get FontSize from Default style
        RETURN_IF_FAILED(GetFontType(hostConfig, ABI::AdaptiveCards::Rendering::Uwp::FontType::Default, &fontTypeDefinition));
        RETURN_IF_FAILED(fontTypeDefinition->get_FontSizes(&sizesConfig));
        RETURN_IF_FAILED(GetFontSize(sizesConfig, desiredSize, &result));

        if (result == MAXUINT32)
        {
            // get deprecated FontSize
            RETURN_IF_FAILED(hostConfig->get_FontSizes(&sizesConfig));
            RETURN_IF_FAILED(GetFontSize(sizesConfig, desiredSize, &result));

            if (result == MAXUINT32)
            {
                // set system default FontSize based on desired style
                switch (desiredSize)
                {
                case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Small:
                    result = 10;
                    break;
                case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Medium:
                    result = 14;
                    break;
                case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Large:
                    result = 17;
                    break;
                case ABI::AdaptiveCards::Rendering::Uwp::TextSize::ExtraLarge:
                    result = 20;
                    break;
                case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Default:
                default:
                    result = 12;
                    break;
                }
            }
        }
    }
    *resultSize = result;
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontWeightFromStyle(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                               ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                               ABI::AdaptiveCards::Rendering::Uwp::TextWeight desiredWeight,
                               _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept
try
{
    UINT16 result;
    ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypeDefinition* typeDefinition;
    ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontWeightsConfig* weightConfig;

    // get FontWeight from desired fontType
    RETURN_IF_FAILED(GetFontType(hostConfig, fontType, &typeDefinition));
    RETURN_IF_FAILED(typeDefinition->get_FontWeights(&weightConfig));
    RETURN_IF_FAILED(GetFontWeight(weightConfig, desiredWeight, &result));

    if (result == MAXUINT16)
    {
        // get FontWeight from Default style
        RETURN_IF_FAILED(GetFontType(hostConfig, ABI::AdaptiveCards::Rendering::Uwp::FontType::Default, &typeDefinition));
        RETURN_IF_FAILED(typeDefinition->get_FontWeights(&weightConfig));
        RETURN_IF_FAILED(GetFontWeight(weightConfig, desiredWeight, &result));

        if (result == MAXUINT16)
        {
            // get deprecated FontWeight
            RETURN_IF_FAILED(hostConfig->get_FontWeights(&weightConfig));
            RETURN_IF_FAILED(GetFontWeight(weightConfig, desiredWeight, &result));

            if (result == MAXUINT16)
            {
                // set system default FontWeight based on desired style
                switch (desiredWeight)
                {
                case ABI::AdaptiveCards::Rendering::Uwp::TextWeight::Lighter:
                    result = 200;
                    break;
                case ABI::AdaptiveCards::Rendering::Uwp::TextWeight::Bolder:
                    result = 800;
                    break;
                case ABI::AdaptiveCards::Rendering::Uwp::TextWeight::Default:
                default:
                    result = 400;
                    break;
                }
            }
        }
    }
    resultWeight->Weight = result;
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                    ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                    _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypeDefinition** fontTypeDefinition) noexcept
try
{
    ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypesDefinition* fontTypes;
    RETURN_IF_FAILED(hostConfig->get_FontTypes(&fontTypes));

    switch (fontType)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::FontType::Monospace:
        RETURN_IF_FAILED(fontTypes->get_Monospace(fontTypeDefinition));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::FontType::Default:
    default:
        RETURN_IF_FAILED(fontTypes->get_Default(fontTypeDefinition));
        break;
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontSize(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontSizesConfig* sizesConfig,
                    ABI::AdaptiveCards::Rendering::Uwp::TextSize desiredSize,
                    _Out_ UINT32* resultSize) noexcept
try
{
    switch (desiredSize)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Small:
        RETURN_IF_FAILED(sizesConfig->get_Small(resultSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Medium:
        RETURN_IF_FAILED(sizesConfig->get_Medium(resultSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Large:
        RETURN_IF_FAILED(sizesConfig->get_Large(resultSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::TextSize::ExtraLarge:
        RETURN_IF_FAILED(sizesConfig->get_ExtraLarge(resultSize));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::TextSize::Default:
    default:
        RETURN_IF_FAILED(sizesConfig->get_Default(resultSize));
        break;
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontWeight(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontWeightsConfig* weightsConfig,
                      ABI::AdaptiveCards::Rendering::Uwp::TextWeight desiredWeight,
                      _Out_ UINT16* resultWeight) noexcept
try
{
    switch (desiredWeight)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::TextWeight::Lighter:
        RETURN_IF_FAILED(weightsConfig->get_Lighter(resultWeight));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::TextWeight::Bolder:
        RETURN_IF_FAILED(weightsConfig->get_Bolder(resultWeight));
        break;
    case ABI::AdaptiveCards::Rendering::Uwp::TextWeight::Default:
    default:
        RETURN_IF_FAILED(weightsConfig->get_Default(resultWeight));
        break;
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT StringToJsonObject(const std::string& inputString, _COM_Outptr_ IJsonObject** result)
{
    HString asHstring;
    RETURN_IF_FAILED(UTF8ToHString(inputString, asHstring.GetAddressOf()));
    return HStringToJsonObject(asHstring.Get(), result);
}

HRESULT HStringToJsonObject(const HSTRING& inputHString, _COM_Outptr_ IJsonObject** result)
{
    ComPtr<IJsonObjectStatics> jObjectStatics;
    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Data_Json_JsonObject).Get(), &jObjectStatics));
    ComPtr<IJsonObject> jObject;
    HRESULT hr = jObjectStatics->Parse(inputHString, &jObject);
    if (FAILED(hr))
    {
        RETURN_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Data_Json_JsonObject).Get(), &jObject));
    }
    *result = jObject.Detach();
    return S_OK;
}

HRESULT JsonObjectToString(_In_ IJsonObject* inputJson, std::string& result)
{
    HString asHstring;
    RETURN_IF_FAILED(JsonObjectToHString(inputJson, asHstring.GetAddressOf()));
    return HStringToUTF8(asHstring.Get(), result);
}

HRESULT JsonObjectToHString(_In_ IJsonObject* inputJson, _Outptr_ HSTRING* result)
{
    if (!inputJson)
    {
        return E_INVALIDARG;
    }
    ComPtr<IJsonObject> localInputJson(inputJson);
    ComPtr<IJsonValue> asJsonValue;
    RETURN_IF_FAILED(localInputJson.As(&asJsonValue));
    return (asJsonValue->Stringify(result));
}

HRESULT StringToJsonValue(const std::string inputString, _COM_Outptr_ IJsonValue** result)
{
    HString asHstring;
    RETURN_IF_FAILED(UTF8ToHString(inputString, asHstring.GetAddressOf()));
    return HStringToJsonValue(asHstring.Get(), result);
}

HRESULT HStringToJsonValue(const HSTRING& inputHString, _COM_Outptr_ IJsonValue** result)
{
    ComPtr<IJsonValueStatics> jValueStatics;
    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Data_Json_JsonValue).Get(), &jValueStatics));
    ComPtr<IJsonValue> jValue;
    HRESULT hr = jValueStatics->Parse(inputHString, &jValue);
    if (FAILED(hr))
    {
        RETURN_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Data_Json_JsonValue).Get(), &jValue));
    }
    *result = jValue.Detach();
    return S_OK;
}

HRESULT JsonValueToString(_In_ IJsonValue* inputValue, std::string& result)
{
    HString asHstring;
    RETURN_IF_FAILED(JsonValueToHString(inputValue, asHstring.GetAddressOf()));
    return HStringToUTF8(asHstring.Get(), result);
}

HRESULT JsonValueToHString(_In_ IJsonValue* inputJsonValue, _Outptr_ HSTRING* result)
{
    if (!inputJsonValue)
    {
        return E_INVALIDARG;
    }
    ComPtr<IJsonValue> localInputJsonValue(inputJsonValue);
    return (localInputJsonValue->Stringify(result));
}

HRESULT JsonCppToJsonObject(const Json::Value& jsonCppValue, _COM_Outptr_ IJsonObject** result)
{
    std::string jsonString = ParseUtil::JsonToString(jsonCppValue);
    return StringToJsonObject(jsonString, result);
}

HRESULT JsonObjectToJsonCpp(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject, _Out_ Json::Value* jsonCppValue)
{
    std::string jsonString;
    RETURN_IF_FAILED(JsonObjectToString(jsonObject, jsonString));

    *jsonCppValue = ParseUtil::GetJsonValueFromString(jsonString);

    return S_OK;
}

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveCards::Rendering::Uwp::ActionType projectedActionType, _Outptr_ HSTRING* result)
{
    ActionType sharedActionType = static_cast<ActionType>(projectedActionType);
    return UTF8ToHString(ActionTypeToString(sharedActionType), result);
}

HRESULT ProjectedElementTypeToHString(ABI::AdaptiveCards::Rendering::Uwp::ElementType projectedElementType, _Outptr_ HSTRING* result)
{
    CardElementType sharedElementType = static_cast<CardElementType>(projectedElementType);
    return UTF8ToHString(CardElementTypeToString(sharedElementType), result);
}

HRESULT MeetsRequirements(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* cardElement,
                          _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration* featureRegistration,
                          _Out_ bool* meetsRequirements)
{
    std::shared_ptr<AdaptiveCards::BaseCardElement> sharedElement;
    RETURN_IF_FAILED(GenerateSharedElement(cardElement, sharedElement));

    ComPtr<AdaptiveFeatureRegistration> featureRegistrationImpl = PeekInnards<AdaptiveFeatureRegistration>(featureRegistration);
    const std::shared_ptr<AdaptiveCards::FeatureRegistration>& sharedFeatureRegistration =
        featureRegistrationImpl->GetSharedFeatureRegistration();

    *meetsRequirements = sharedElement->MeetsRequirements(*sharedFeatureRegistration);
    return S_OK;
}

HRESULT IsBackgroundImageValid(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveBackgroundImage* backgroundImageElement,
                               _Out_ BOOL* isValid)
{
    *isValid = FALSE;
    ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveBackgroundImage> backgroundImage(backgroundImageElement);
    if (backgroundImage != NULL)
    {
        HString url;
        RETURN_IF_FAILED(backgroundImage->get_Url(url.GetAddressOf()));
        *isValid = url.IsValid();
    }
    return S_OK;
}

void RemoteResourceElementToRemoteResourceInformationVector(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementWithRemoteResources* remoteResourceElement,
                                                            std::vector<RemoteResourceInformation>& resourceUris)
{
    ComPtr<ABI::Windows::Foundation::Collections::IVectorView<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRemoteResourceInformation*>> remoteResources;
    THROW_IF_FAILED(remoteResourceElement->GetResourceInformation(remoteResources.GetAddressOf()));

    ComPtr<IIterable<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRemoteResourceInformation*>> vectorIterable;
    THROW_IF_FAILED(remoteResources.As<IIterable<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRemoteResourceInformation*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<IIterator<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRemoteResourceInformation*>> vectorIterator;
    HRESULT hr = vectorIterable->First(&vectorIterator);

    boolean hasCurrent;
    THROW_IF_FAILED(vectorIterator->get_HasCurrent(&hasCurrent));

    while (SUCCEEDED(hr) && hasCurrent)
    {
        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRemoteResourceInformation> resourceInformation;
        THROW_IF_FAILED(vectorIterator->get_Current(&resourceInformation));

        HString url;
        THROW_IF_FAILED(resourceInformation->get_Url(url.GetAddressOf()));

        RemoteResourceInformation uriInfo;
        THROW_IF_FAILED(HStringToUTF8(url.Get(), uriInfo.url));

        HString mimeType;
        THROW_IF_FAILED(resourceInformation->get_MimeType(mimeType.GetAddressOf()));

        uriInfo.mimeType = HStringToUTF8(mimeType.Get());

        resourceUris.push_back(uriInfo);

        hr = vectorIterator->MoveNext(&hasCurrent);
    }
}

void GetUrlFromString(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                      _In_ HSTRING urlString,
                      _Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** url)
{
    ComPtr<ABI::Windows::Foundation::IUriRuntimeClassFactory> uriActivationFactory;
    THROW_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), &uriActivationFactory));

    ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> localUrl;

    // Try to treat URI as absolute
    boolean isUrlRelative = FAILED(uriActivationFactory->CreateUri(urlString, localUrl.GetAddressOf()));

    // Otherwise, try to treat URI as relative
    if (isUrlRelative)
    {
        HString imageBaseUrl;
        THROW_IF_FAILED(hostConfig->get_ImageBaseUrl(imageBaseUrl.GetAddressOf()));

        if (imageBaseUrl.Get() != nullptr)
        {
            THROW_IF_FAILED(uriActivationFactory->CreateWithRelativeUri(imageBaseUrl.Get(), urlString, localUrl.GetAddressOf()));
        }
    }

    THROW_IF_FAILED(localUrl.CopyTo(url));
}

HRESULT SharedWarningsToAdaptiveWarnings(
    const std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings)
{
    for (const auto& sharedWarning : sharedWarnings)
    {
        HString warningMessage;
        RETURN_IF_FAILED(UTF8ToHString(sharedWarning->GetReason(), warningMessage.GetAddressOf()));

        ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode statusCode =
            static_cast<ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode>(sharedWarning->GetStatusCode());

        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveWarning> adaptiveWarning;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveWarning>(&adaptiveWarning, statusCode, warningMessage.Get()));

        RETURN_IF_FAILED(adaptiveWarnings->Append(adaptiveWarning.Get()));
    }

    return S_OK;
}

HRESULT AdaptiveWarningsToSharedWarnings(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
    std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& sharedWarnings)
{
    ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>> localAdaptiveWarnings{
        adaptiveWarnings};
    ComPtr<IIterable<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>> vectorIterable;
    RETURN_IF_FAILED(localAdaptiveWarnings.As<IIterable<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<IIterator<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>> vectorIterator;
    HRESULT hr = vectorIterable->First(&vectorIterator);

    boolean hasCurrent;
    THROW_IF_FAILED(vectorIterator->get_HasCurrent(&hasCurrent));

    while (SUCCEEDED(hr) && hasCurrent)
    {
        ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveWarning> adaptiveWarning;
        RETURN_IF_FAILED(vectorIterator->get_Current(&adaptiveWarning));

        HString message;
        RETURN_IF_FAILED(adaptiveWarning->get_Message(message.GetAddressOf()));

        ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode statusCode;
        RETURN_IF_FAILED(adaptiveWarning->get_StatusCode(&statusCode));

        sharedWarnings.push_back(std::make_shared<AdaptiveCardParseWarning>(static_cast<AdaptiveCards::WarningStatusCode>(statusCode),
                                                                            HStringToUTF8(message.Get())));

        hr = vectorIterator->MoveNext(&hasCurrent);
    }

    return S_OK;
}

Color GenerateLHoverColor(const Color& originalColor)
{
    const double hoverIncrement = 0.25;

    Color hoverColor;
    hoverColor.A = originalColor.A;
    hoverColor.R = originalColor.R - static_cast<BYTE>(originalColor.R * hoverIncrement);
    hoverColor.G = originalColor.G - static_cast<BYTE>(originalColor.G * hoverIncrement);
    hoverColor.B = originalColor.B - static_cast<BYTE>(originalColor.B * hoverIncrement);
    return hoverColor;
}

DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day)
{
    SYSTEMTIME systemTime = {(WORD)year, (WORD)month, 0, (WORD)day};

    // Convert to UTC
    TIME_ZONE_INFORMATION timeZone;
    GetTimeZoneInformation(&timeZone);
    TzSpecificLocalTimeToSystemTime(&timeZone, &systemTime, &systemTime);

    // Convert to ticks
    FILETIME fileTime;
    SystemTimeToFileTime(&systemTime, &fileTime);
    DateTime dateTime{(INT64)fileTime.dwLowDateTime + (((INT64)fileTime.dwHighDateTime) << 32)};

    return dateTime;
}

HRESULT GetDateTimeReference(unsigned int year, unsigned int month, unsigned int day, _COM_Outptr_ IReference<DateTime>** dateTimeReference)
{
    DateTime dateTime = GetDateTime(year, month, day);

    ComPtr<IPropertyValueStatics> factory;
    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_PropertyValue).Get(), &factory));

    ComPtr<IInspectable> inspectable;
    RETURN_IF_FAILED(factory->CreateDateTime(dateTime, &inspectable));

    ComPtr<IReference<DateTime>> localDateTimeReference;
    RETURN_IF_FAILED(inspectable.As(&localDateTimeReference));

    *dateTimeReference = localDateTimeReference.Detach();

    return S_OK;
}

ABI::AdaptiveCards::Rendering::Uwp::FallbackType MapSharedFallbackTypeToUwp(const AdaptiveCards::FallbackType type)
{
    switch (type)
    {
    case FallbackType::Drop:
    {
        return ABI::AdaptiveCards::Rendering::Uwp::FallbackType::Drop;
    }

    case FallbackType::Content:
    {
        return ABI::AdaptiveCards::Rendering::Uwp::FallbackType::Content;
    }

    case FallbackType::None:
    default:
    {
        return ABI::AdaptiveCards::Rendering::Uwp::FallbackType::None;
    }
    }
}

AdaptiveCards::FallbackType MapUwpFallbackTypeToShared(const ABI::AdaptiveCards::Rendering::Uwp::FallbackType type)
{
    switch (type)
    {
    case ABI::AdaptiveCards::Rendering::Uwp::FallbackType::Drop:
    {
        return FallbackType::Drop;
    }

    case ABI::AdaptiveCards::Rendering::Uwp::FallbackType::Content:
    {
        return FallbackType::Content;
    }

    case ABI::AdaptiveCards::Rendering::Uwp::FallbackType::None:
    default:
    {
        return FallbackType::None;
    }
    }
}

HRESULT CopyTextElement(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextElement* textElement,
                        _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextElement** copiedTextElement)
{
    ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveTextElement> localCopiedTextElement;
    RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCards::Rendering::Uwp::AdaptiveTextRun>(&localCopiedTextElement));

    ComPtr<IReference<ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor>> color;
    RETURN_IF_FAILED(textElement->get_Color(&color));
    RETURN_IF_FAILED(localCopiedTextElement->put_Color(color.Get()));

    ComPtr<IReference<ABI::AdaptiveCards::Rendering::Uwp::FontType>> fontType;
    RETURN_IF_FAILED(textElement->get_FontType(&fontType));
    RETURN_IF_FAILED(localCopiedTextElement->put_FontType(fontType.Get()));

    ComPtr<IReference<bool>> isSubtle;
    RETURN_IF_FAILED(textElement->get_IsSubtle(&isSubtle));
    RETURN_IF_FAILED(localCopiedTextElement->put_IsSubtle(isSubtle.Get()));

    HString language;
    RETURN_IF_FAILED(textElement->get_Language(language.GetAddressOf()));
    RETURN_IF_FAILED(localCopiedTextElement->put_Language(language.Get()));

    ComPtr<IReference<ABI::AdaptiveCards::Rendering::Uwp::TextSize>> size;
    RETURN_IF_FAILED(textElement->get_Size(&size));
    RETURN_IF_FAILED(localCopiedTextElement->put_Size(size.Get()));

    ComPtr<IReference<ABI::AdaptiveCards::Rendering::Uwp::TextWeight>> weight;
    RETURN_IF_FAILED(textElement->get_Weight(&weight));
    RETURN_IF_FAILED(localCopiedTextElement->put_Weight(weight.Get()));

    HString text;
    RETURN_IF_FAILED(textElement->get_Text(text.GetAddressOf()));
    RETURN_IF_FAILED(localCopiedTextElement->put_Text(text.Get()));

    RETURN_IF_FAILED(localCopiedTextElement.CopyTo(copiedTextElement));
    return S_OK;
}

HRESULT GetAdaptiveActionParserRegistrationFromSharedModel(
    const std::shared_ptr<ActionParserRegistration>& sharedActionParserRegistration,
    _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration** adaptiveActionParserRegistration)
{
    // Look up the well known action parser registration to see if we've got a custom action registration to pass
    std::shared_ptr<ActionElementParser> sharedActionParser =
        sharedActionParserRegistration->GetParser(c_upwActionParserRegistration);

    if (sharedActionParser != nullptr)
    {
        // The shared model wraps the passed in parsers. Get our SharedModelActionParser from it so we can retrieve the
        // IAdaptiveActionParserRegistration
        std::shared_ptr<ActionElementParserWrapper> parserWrapper =
            std::static_pointer_cast<ActionElementParserWrapper>(sharedActionParser);

        std::shared_ptr<SharedModelActionParser> sharedModelParser =
            std::static_pointer_cast<SharedModelActionParser>(parserWrapper->GetActualParser());

        RETURN_IF_FAILED(sharedModelParser->GetAdaptiveParserRegistration(adaptiveActionParserRegistration));
    }
    else
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCards::Rendering::Uwp::AdaptiveActionParserRegistration>(adaptiveActionParserRegistration));
    }

    return S_OK;
}

HRESULT GetAdaptiveElementParserRegistrationFromSharedModel(
    const std::shared_ptr<ElementParserRegistration>& sharedElementParserRegistration,
    _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration** adaptiveElementParserRegistration)
{
    // Look up the well known Element parser registration to see if we've got a custom Element registration to pass
    std::shared_ptr<BaseCardElementParser> sharedElementParser =
        sharedElementParserRegistration->GetParser(c_uwpElementParserRegistration);

    if (sharedElementParser != nullptr)
    {
        // The shared model wraps the passed in parsers. Get our SharedModelElementParser from it so we can retrieve the
        // IAdaptiveElementParserRegistration
        std::shared_ptr<BaseCardElementParserWrapper> parserWrapper =
            std::static_pointer_cast<BaseCardElementParserWrapper>(sharedElementParser);

        std::shared_ptr<SharedModelElementParser> sharedModelParser =
            std::static_pointer_cast<SharedModelElementParser>(parserWrapper->GetActualParser());

        RETURN_IF_FAILED(sharedModelParser->GetAdaptiveParserRegistration(adaptiveElementParserRegistration));
    }
    else
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCards::Rendering::Uwp::AdaptiveElementParserRegistration>(adaptiveElementParserRegistration));
    }

    return S_OK;
}
