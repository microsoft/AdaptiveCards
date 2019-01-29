#include "pch.h"
#include <locale>
#include <codecvt>
#include <string>
#include <regex>

#include "AdaptiveActionSet.h"
#include "AdaptiveColumn.h"
#include "AdaptiveColumnSet.h"
#include "AdaptiveContainer.h"
#include "AdaptiveChoiceInput.h"
#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveDateInput.h"
#include "AdaptiveFact.h"
#include "AdaptiveFactSet.h"
#include "AdaptiveImage.h"
#include "AdaptiveImageSet.h"
#include "AdaptiveMedia.h"
#include "AdaptiveMediaSource.h"
#include "AdaptiveNumberInput.h"
#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveSeparator.h"
#include "AdaptiveShowCardAction.h"
#include "AdaptiveSubmitAction.h"
#include "AdaptiveTextBlock.h"
#include "AdaptiveTextInput.h"
#include "AdaptiveTimeInput.h"
#include "AdaptiveToggleInput.h"
#include "AdaptiveToggleVisibilityTarget.h"
#include "AdaptiveToggleVisibilityAction.h"
#include "AdaptiveUnsupportedElement.h"
#include "AdaptiveWarning.h"
#include "CustomActionWrapper.h"
#include "CustomElementWrapper.h"
#include "enums.h"
#include "util.h"
#include <windows.foundation.collections.h>
#include "XamlHelpers.h"

using namespace AdaptiveCards;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::UI;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

HRESULT WStringToHString(const std::wstring& in, _Outptr_ HSTRING* out)
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    return WindowsCreateString(in.c_str(), static_cast<UINT32>(in.length()), out);
}

HRESULT UTF8ToHString(const std::string& in, _Outptr_ HSTRING* out)
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(in);
    return WindowsCreateString(wide.c_str(), static_cast<UINT32>(wide.length()), out);
}

HRESULT HStringToUTF8(const HSTRING& in, std::string& out)
{
    if (in == nullptr)
    {
        return E_INVALIDARG;
    }
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    out = converter.to_bytes(WindowsGetStringRawBuffer(in, nullptr));
    return S_OK;
}

std::string HStringToUTF8(const HSTRING& in)
{
    std::string typeAsKey;
    HRESULT hr = HStringToUTF8(in, typeAsKey);
    return FAILED(hr) ? "" : typeAsKey;
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

HRESULT GenerateSharedElements(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* items,
                               std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::IAdaptiveCardElement>(items, [&](ABI::AdaptiveNamespace::IAdaptiveCardElement* item) {
        ABI::AdaptiveNamespace::ElementType elementType;
        RETURN_IF_FAILED(item->get_ElementType(&elementType));

        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> baseCardElement;
        switch (elementType)
        {
        case ABI::AdaptiveNamespace::ElementType::ActionSet:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveActionSet>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::ChoiceSetInput:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveChoiceSetInput>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::ColumnSet:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveColumnSet>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::Container:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveContainer>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::DateInput:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveDateInput>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::FactSet:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveFactSet>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::Image:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveImage>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::ImageSet:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveImageSet>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::NumberInput:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveNumberInput>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::Media:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveMedia>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::TextBlock:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveTextBlock>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::TextInput:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveTextInput>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::TimeInput:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveTimeInput>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::ToggleInput:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveToggleInput>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::Unsupported:
            baseCardElement =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveUnsupportedElement>(
                    item);
            break;
        case ABI::AdaptiveNamespace::ElementType::Custom:
            baseCardElement = std::make_shared<CustomElementWrapper>(item);
            break;
        }

        if (baseCardElement == nullptr)
        {
            return E_INVALIDARG;
        }

        containedElements.push_back(baseCardElement);

        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateSharedAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                             std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedAction)
{
    ABI::AdaptiveNamespace::ActionType actionType;
    RETURN_IF_FAILED(action->get_ActionType(&actionType));

    switch (actionType)
    {
    case ABI::AdaptiveNamespace::ActionType::OpenUrl:
        sharedAction =
            GetSharedModel<AdaptiveSharedNamespace::BaseActionElement, ABI::AdaptiveNamespace::IAdaptiveActionElement, AdaptiveNamespace::AdaptiveOpenUrlAction>(
                action);
        break;
    case ABI::AdaptiveNamespace::ActionType::ShowCard:
        sharedAction =
            GetSharedModel<AdaptiveSharedNamespace::BaseActionElement, ABI::AdaptiveNamespace::IAdaptiveActionElement, AdaptiveNamespace::AdaptiveShowCardAction>(
                action);
        break;
    case ABI::AdaptiveNamespace::ActionType::Submit:
        sharedAction =
            GetSharedModel<AdaptiveSharedNamespace::BaseActionElement, ABI::AdaptiveNamespace::IAdaptiveActionElement, AdaptiveNamespace::AdaptiveSubmitAction>(
                action);
        break;
    case ABI::AdaptiveNamespace::ActionType::ToggleVisibility:
        sharedAction =
            GetSharedModel<AdaptiveSharedNamespace::BaseActionElement, ABI::AdaptiveNamespace::IAdaptiveActionElement, AdaptiveNamespace::AdaptiveToggleVisibilityAction>(
                action);
        break;
    case ABI::AdaptiveNamespace::ActionType::Custom:
        sharedAction = std::make_shared<CustomActionWrapper>(action);
        break;
    }

    return S_OK;
}

HRESULT GenerateSharedActions(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* actions,
                              std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::IAdaptiveActionElement>(actions, [&](ABI::AdaptiveNamespace::IAdaptiveActionElement* action) {
        std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> baseActionElement;
        GenerateSharedAction(action, baseActionElement);
        containedElements.push_back(baseActionElement);
        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateSharedImages(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveImage*>* images,
                             std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveImage, ABI::AdaptiveNamespace::IAdaptiveImage>(
        images, [&](ABI::AdaptiveNamespace::IAdaptiveImage* image) {
            ComPtr<ABI::AdaptiveNamespace::IAdaptiveImage> localImage = image;
            ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> imageAsElement;
            localImage.As(&imageAsElement);

            std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedImage =
                GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveImage>(
                    imageAsElement.Get());
            containedElements.push_back(std::AdaptivePointerCast<AdaptiveSharedNamespace::Image>(sharedImage));

            return S_OK;
        });

    return S_OK;
}

HRESULT GenerateSharedFacts(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveFact*>* facts,
                            std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveFact, ABI::AdaptiveNamespace::IAdaptiveFact>(
        facts, [&](ABI::AdaptiveNamespace::IAdaptiveFact* fact) {
            ComPtr<AdaptiveNamespace::AdaptiveFact> adaptiveElement = PeekInnards<AdaptiveNamespace::AdaptiveFact>(fact);
            if (adaptiveElement == nullptr)
            {
                return E_INVALIDARG;
            }

            std::shared_ptr<AdaptiveSharedNamespace::Fact> sharedFact;
            RETURN_IF_FAILED(adaptiveElement->GetSharedModel(sharedFact));
            containedElements.push_back(std::AdaptivePointerCast<AdaptiveSharedNamespace::Fact>(sharedFact));
            return S_OK;
        });

    return S_OK;
}

HRESULT GenerateSharedChoices(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput*>* choices,
                              std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput, ABI::AdaptiveNamespace::IAdaptiveChoiceInput>(
        choices, [&](ABI::AdaptiveNamespace::IAdaptiveChoiceInput* choice) {
            ComPtr<AdaptiveNamespace::AdaptiveChoiceInput> adaptiveElement =
                PeekInnards<AdaptiveNamespace::AdaptiveChoiceInput>(choice);
            if (adaptiveElement == nullptr)
            {
                return E_INVALIDARG;
            }

            std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput> sharedChoice;
            RETURN_IF_FAILED(adaptiveElement->GetSharedModel(sharedChoice));
            containedElements.push_back(std::AdaptivePointerCast<AdaptiveSharedNamespace::ChoiceInput>(sharedChoice));
            return S_OK;
        });

    return S_OK;
}

HRESULT GenerateSharedMediaSources(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveMediaSource*>* sources,
                                   std::vector<std::shared_ptr<AdaptiveSharedNamespace::MediaSource>>& containedElements)
{
    containedElements.clear();

    ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveMediaSource*>> localSources(sources);
    ComPtr<IIterable<ABI::AdaptiveNamespace::AdaptiveMediaSource*>> vectorIterable;
    THROW_IF_FAILED(localSources.As<IIterable<ABI::AdaptiveNamespace::AdaptiveMediaSource*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<IIterator<ABI::AdaptiveNamespace::AdaptiveMediaSource*>> vectorIterator;
    HRESULT hr = vectorIterable->First(&vectorIterator);

    boolean hasCurrent;
    THROW_IF_FAILED(vectorIterator->get_HasCurrent(&hasCurrent));

    while (SUCCEEDED(hr) && hasCurrent)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveMediaSource> source;
        THROW_IF_FAILED(vectorIterator->get_Current(&source));

        ComPtr<AdaptiveNamespace::AdaptiveMediaSource> adaptiveElement =
            PeekInnards<AdaptiveNamespace::AdaptiveMediaSource>(source);
        if (adaptiveElement == nullptr)
        {
            return E_INVALIDARG;
        }

        std::shared_ptr<AdaptiveSharedNamespace::MediaSource> sharedSource;
        RETURN_IF_FAILED(adaptiveElement->GetSharedModel(sharedSource));
        containedElements.push_back(std::AdaptivePointerCast<AdaptiveSharedNamespace::MediaSource>(sharedSource));

        hr = vectorIterator->MoveNext(&hasCurrent);
    }

    return S_OK;
}

HRESULT GenerateSharedToggleElements(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>* targets,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>>& containedElements)
{
    containedElements.clear();

    ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>> localTargets(targets);
    ComPtr<IIterable<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>> vectorIterable;
    THROW_IF_FAILED(localTargets.As<IIterable<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<IIterator<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>> vectorIterator;
    HRESULT hr = vectorIterable->First(&vectorIterator);

    boolean hasCurrent;
    THROW_IF_FAILED(vectorIterator->get_HasCurrent(&hasCurrent));

    while (SUCCEEDED(hr) && hasCurrent)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveToggleVisibilityTarget> target;
        THROW_IF_FAILED(vectorIterator->get_Current(&target));

        ComPtr<AdaptiveNamespace::AdaptiveToggleVisibilityTarget> adaptiveElement =
            PeekInnards<AdaptiveNamespace::AdaptiveToggleVisibilityTarget>(target);
        if (adaptiveElement == nullptr)
        {
            return E_INVALIDARG;
        }

        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget> sharedTarget;
        RETURN_IF_FAILED(adaptiveElement->GetSharedModel(sharedTarget));
        containedElements.push_back(std::AdaptivePointerCast<AdaptiveSharedNamespace::ToggleVisibilityTarget>(sharedTarget));

        hr = vectorIterator->MoveNext(&hasCurrent);
    }

    return S_OK;
}

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> projectedContainedElement;
        switch (containedElement->GetElementType())
        {
        case CardElementType::TextBlock:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveTextBlock>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::TextBlock>(containedElement)));
            break;
        case CardElementType::Image:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveImage>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::Image>(containedElement)));
            break;
        case CardElementType::Container:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveContainer>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::Container>(containedElement)));
            break;
        case CardElementType::ColumnSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveColumnSet>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::ColumnSet>(containedElement)));
            break;
        case CardElementType::FactSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveFactSet>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::FactSet>(containedElement)));
            break;
        case CardElementType::ImageSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveImageSet>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::ImageSet>(containedElement)));
            break;
        case CardElementType::ChoiceSetInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveChoiceSetInput>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::ChoiceSetInput>(containedElement)));
            break;
        case CardElementType::DateInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveDateInput>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::DateInput>(containedElement)));
            break;
        case CardElementType::Media:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveMedia>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::Media>(containedElement)));
            break;
        case CardElementType::NumberInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveNumberInput>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::NumberInput>(containedElement)));
            break;
        case CardElementType::TextInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveTextInput>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::TextInput>(containedElement)));
            break;
        case CardElementType::TimeInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveTimeInput>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::TimeInput>(containedElement)));
            break;
        case CardElementType::ToggleInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveToggleInput>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::ToggleInput>(containedElement)));
            break;
        case CardElementType::ActionSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveActionSet>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveCards::ActionSet>(containedElement)));
            break;
        case CardElementType::Custom:
            RETURN_IF_FAILED(std::AdaptivePointerCast<CustomElementWrapper>(containedElement)->GetWrappedElement(&projectedContainedElement));
            break;
        case CardElementType::Unknown:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveUnsupportedElement>(
                &projectedContainedElement, std::AdaptivePointerCast<AdaptiveSharedNamespace::UnknownElement>(containedElement)));
            break;
        }

        if (projectedContainedElement != nullptr)
        {
            RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
        }
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& containedActions,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedAction : containedActions)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> projectedContainedAction;
        RETURN_IF_FAILED(GenerateActionProjection(containedAction, &projectedContainedAction));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedAction.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateActionProjection(const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> action,
                                 _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** projectedAction) noexcept try
{
    if (action == nullptr)
    {
        *projectedAction = nullptr;
        return S_OK;
    }

    switch (action->GetElementType())
    {
    case ActionType::OpenUrl:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveOpenUrlAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveSharedNamespace::OpenUrlAction>(action)));
        break;
    case ActionType::ShowCard:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveShowCardAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveSharedNamespace::ShowCardAction>(action)));
        break;
    case ActionType::Submit:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveSubmitAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveSharedNamespace::SubmitAction>(action)));
        break;
    case ActionType::ToggleVisibility:
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveToggleVisibilityAction>(
            projectedAction, std::AdaptivePointerCast<AdaptiveSharedNamespace::ToggleVisibilityAction>(action)));
        break;
    case ActionType::Custom:
        RETURN_IF_FAILED(std::AdaptivePointerCast<CustomActionWrapper>(action)->GetWrappedElement(projectedAction));
        break;
    default:
        return E_UNEXPECTED;
        break;
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateColumnsProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Column>>& containedElements,
                                  _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveColumn*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveColumn> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveColumn>(
            &projectedContainedElement, std::static_pointer_cast<AdaptiveSharedNamespace::Column>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateFactsProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveFact*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveFact> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveFact>(
            &projectedContainedElement, std::static_pointer_cast<AdaptiveSharedNamespace::Fact>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateImagesProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements,
                                 _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveImage*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveImage> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveImage>(
            &projectedContainedElement, std::static_pointer_cast<AdaptiveSharedNamespace::Image>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveChoiceInput> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveChoiceInput>(
            &projectedContainedElement, std::static_pointer_cast<AdaptiveSharedNamespace::ChoiceInput>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateMediaSourcesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::MediaSource>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveMediaSource*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveMediaSource> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveMediaSource>(
            &projectedContainedElement, std::static_pointer_cast<AdaptiveSharedNamespace::MediaSource>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateToggleTargetProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveToggleVisibilityTarget> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveToggleVisibilityTarget>(
            &projectedContainedElement, std::static_pointer_cast<AdaptiveSharedNamespace::ToggleVisibilityTarget>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateSeparatorProjection(std::shared_ptr<AdaptiveSharedNamespace::Separator> sharedSeparator,
                                    _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveSeparator** projectedSeparator) noexcept try
{
    *projectedSeparator = nullptr;
    if (sharedSeparator != nullptr)
    {
        return MakeAndInitialize<::AdaptiveNamespace::AdaptiveSeparator>(projectedSeparator, sharedSeparator);
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GenerateSharedSeparator(_In_ ABI::AdaptiveNamespace::IAdaptiveSeparator* separator,
                                _Out_ std::shared_ptr<AdaptiveSharedNamespace::Separator>* sharedSeparatorOut) noexcept try
{
    ABI::AdaptiveNamespace::ForegroundColor color;
    RETURN_IF_FAILED(separator->get_Color(&color));

    ABI::AdaptiveNamespace::SeparatorThickness thickness;
    RETURN_IF_FAILED(separator->get_Thickness(&thickness));

    auto sharedSeparator = std::make_shared<Separator>();
    sharedSeparator->SetColor(static_cast<AdaptiveSharedNamespace::ForegroundColor>(color));
    sharedSeparator->SetThickness(static_cast<AdaptiveSharedNamespace::SeparatorThickness>(thickness));

    *sharedSeparatorOut = sharedSeparator;
    return S_OK;
}
CATCH_RETURN;

// Get a Color object from color string
// Expected formats are "#AARRGGBB" (with alpha channel) and "#RRGGBB" (without alpha channel)
HRESULT GetColorFromString(const std::string& colorString, _Out_ ABI::Windows::UI::Color* color) noexcept try
{
    if (colorString.front() == '#')
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

HRESULT GetColorFromAdaptiveColor(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveNamespace::ForegroundColor adaptiveColor,
                                  ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                  bool isSubtle,
                                  _Out_ ABI::Windows::UI::Color* uiColor) noexcept try
{
    ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition> styles;
    RETURN_IF_FAILED(hostConfig->get_ContainerStyles(&styles));

    ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> styleDefinition;
    if (containerStyle == ABI::AdaptiveNamespace::ContainerStyle_Default)
    {
        RETURN_IF_FAILED(styles->get_Default(&styleDefinition));
    }
    else
    {
        RETURN_IF_FAILED(styles->get_Emphasis(&styleDefinition));
    }

    ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorsConfig> colorsConfig;
    RETURN_IF_FAILED(styleDefinition->get_ForegroundColors(&colorsConfig));

    ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> colorConfig;
    switch (adaptiveColor)
    {
    case ABI::AdaptiveNamespace::ForegroundColor::Accent:
        RETURN_IF_FAILED(colorsConfig->get_Accent(&colorConfig));
        break;
    case ABI::AdaptiveNamespace::ForegroundColor::Dark:
        RETURN_IF_FAILED(colorsConfig->get_Dark(&colorConfig));
        break;
    case ABI::AdaptiveNamespace::ForegroundColor::Light:
        RETURN_IF_FAILED(colorsConfig->get_Light(&colorConfig));
        break;
    case ABI::AdaptiveNamespace::ForegroundColor::Good:
        RETURN_IF_FAILED(colorsConfig->get_Good(&colorConfig));
        break;
    case ABI::AdaptiveNamespace::ForegroundColor::Warning:
        RETURN_IF_FAILED(colorsConfig->get_Warning(&colorConfig));
        break;
    case ABI::AdaptiveNamespace::ForegroundColor::Attention:
        RETURN_IF_FAILED(colorsConfig->get_Attention(&colorConfig));
        break;
    case ABI::AdaptiveNamespace::ForegroundColor::Default:
    default:
        RETURN_IF_FAILED(colorsConfig->get_Default(&colorConfig));
        break;
    }

    RETURN_IF_FAILED(isSubtle ? colorConfig->get_Subtle(uiColor) : colorConfig->get_Default(uiColor));

    return S_OK;
}
CATCH_RETURN;

HRESULT GetSpacingSizeFromSpacing(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveNamespace::Spacing spacing,
                                  _Out_ UINT* spacingSize) noexcept try
{
    ComPtr<ABI::AdaptiveNamespace::IAdaptiveSpacingConfig> spacingConfig;
    RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

    switch (spacing)
    {
    case ABI::AdaptiveNamespace::Spacing::None:
        *spacingSize = 0;
        break;
    case ABI::AdaptiveNamespace::Spacing::Small:
        RETURN_IF_FAILED(spacingConfig->get_Small(spacingSize));
        break;
    case ABI::AdaptiveNamespace::Spacing::Medium:
        RETURN_IF_FAILED(spacingConfig->get_Medium(spacingSize));
        break;
    case ABI::AdaptiveNamespace::Spacing::Large:
        RETURN_IF_FAILED(spacingConfig->get_Large(spacingSize));
        break;
    case ABI::AdaptiveNamespace::Spacing::ExtraLarge:
        RETURN_IF_FAILED(spacingConfig->get_ExtraLarge(spacingSize));
        break;
    case ABI::AdaptiveNamespace::Spacing::Padding:
        RETURN_IF_FAILED(spacingConfig->get_Padding(spacingSize));
        break;
    case ABI::AdaptiveNamespace::Spacing::Default:
    default:
        RETURN_IF_FAILED(spacingConfig->get_Default(spacingSize));
        break;
    }

    return S_OK;
}
CATCH_RETURN;

HRESULT GetBackgroundColorFromStyle(ABI::AdaptiveNamespace::ContainerStyle style,
                                    _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept try
{
    ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition> containerStyles;
    RETURN_IF_FAILED(hostConfig->get_ContainerStyles(&containerStyles));

    ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> styleDefinition;
    if (style == ABI::AdaptiveNamespace::ContainerStyle::Default)
    {
        RETURN_IF_FAILED(containerStyles->get_Default(&styleDefinition));
    }
    else
    {
        RETURN_IF_FAILED(containerStyles->get_Emphasis(&styleDefinition));
    }

    RETURN_IF_FAILED(styleDefinition->get_BackgroundColor(backgroundColor));

    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontDataFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                             ABI::AdaptiveNamespace::FontStyle style,
                             ABI::AdaptiveNamespace::TextSize desiredSize,
                             ABI::AdaptiveNamespace::TextWeight desiredWeight,
                             _Outptr_ HSTRING* resultFontFamilyName,
                             _Out_ UINT32* resultSize,
                             _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept try
{
    RETURN_IF_FAILED(GetFontFamilyFromStyle(hostConfig, style, resultFontFamilyName));
    RETURN_IF_FAILED(GetFontSizeFromStyle(hostConfig, style, desiredSize, resultSize));
    RETURN_IF_FAILED(GetFontWeightFromStyle(hostConfig, style, desiredWeight, resultWeight));
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontFamilyFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                               ABI::AdaptiveNamespace::FontStyle style,
                               _Outptr_ HSTRING* resultFontFamilyName) noexcept try
{
    HString result;
    ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* styleDefinition;

    // get FontFamily from desired style
    RETURN_IF_FAILED(GetFontStyle(hostConfig, style, &styleDefinition));
    RETURN_IF_FAILED(styleDefinition->get_FontFamily(result.GetAddressOf()));
    if (result == NULL)
    {
        // get FontFamily from Default style
        RETURN_IF_FAILED(GetFontStyle(hostConfig, ABI::AdaptiveNamespace::FontStyle::Default, &styleDefinition));
        RETURN_IF_FAILED(styleDefinition->get_FontFamily(result.GetAddressOf()));

        if (result == NULL)
        {
            // get deprecated FontFamily
            RETURN_IF_FAILED(hostConfig->get_FontFamily(result.GetAddressOf()));

            if (result == NULL)
            {
                // set system default FontFamily based on desired style
                switch (style)
                {
                case ABI::AdaptiveNamespace::FontStyle::Monospace:
                    RETURN_IF_FAILED(UTF8ToHString("Courier New", result.GetAddressOf()));
                    break;
                case ABI::AdaptiveNamespace::FontStyle::Display:
                case ABI::AdaptiveNamespace::FontStyle::Default:
                default:
                    RETURN_IF_FAILED(UTF8ToHString("Segoe UI", result.GetAddressOf()));
                    break;
                }
            }
        }
    }
    return result.CopyTo(resultFontFamilyName);
}
CATCH_RETURN;

HRESULT GetFontSizeFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                             ABI::AdaptiveNamespace::FontStyle style,
                             ABI::AdaptiveNamespace::TextSize desiredSize,
                             _Out_ UINT32* resultSize) noexcept try
{
    UINT32 result;
    ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* styleDefinition;
    ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* sizesConfig;

    // get FontSize from desired style
    RETURN_IF_FAILED(GetFontStyle(hostConfig, style, &styleDefinition));
    RETURN_IF_FAILED(styleDefinition->get_FontSizes(&sizesConfig));
    RETURN_IF_FAILED(GetFontSize(sizesConfig, desiredSize, &result));

    if (result == MAXUINT32)
    {
        // get FontSize from Default style
        RETURN_IF_FAILED(GetFontStyle(hostConfig, ABI::AdaptiveNamespace::FontStyle::Default, &styleDefinition));
        RETURN_IF_FAILED(styleDefinition->get_FontSizes(&sizesConfig));
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
                case ABI::AdaptiveNamespace::TextSize::Small:
                    result = 10;
                    break;
                case ABI::AdaptiveNamespace::TextSize::Medium:
                    result = 14;
                    break;
                case ABI::AdaptiveNamespace::TextSize::Large:
                    result = 17;
                    break;
                case ABI::AdaptiveNamespace::TextSize::ExtraLarge:
                    result = 20;
                    break;
                case ABI::AdaptiveNamespace::TextSize::Default:
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

HRESULT GetFontWeightFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                               ABI::AdaptiveNamespace::FontStyle style,
                               ABI::AdaptiveNamespace::TextWeight desiredWeight,
                               _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept try
{
    UINT16 result;
    ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* styleDefinition;
    ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* weightConfig;

    // get FontWeight from desired style
    RETURN_IF_FAILED(GetFontStyle(hostConfig, style, &styleDefinition));
    RETURN_IF_FAILED(styleDefinition->get_FontWeights(&weightConfig));
    RETURN_IF_FAILED(GetFontWeight(weightConfig, desiredWeight, &result));

    if (result == MAXUINT16)
    {
        // get FontWeight from Default style
        RETURN_IF_FAILED(GetFontStyle(hostConfig, ABI::AdaptiveNamespace::FontStyle::Default, &styleDefinition));
        RETURN_IF_FAILED(styleDefinition->get_FontWeights(&weightConfig));
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
                case ABI::AdaptiveNamespace::TextWeight::Lighter:
                    result = 200;
                    break;
                case ABI::AdaptiveNamespace::TextWeight::Bolder:
                    result = 800;
                    break;
                case ABI::AdaptiveNamespace::TextWeight::Default:
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

HRESULT GetFontStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                     ABI::AdaptiveNamespace::FontStyle style,
                     _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** styleDefinition) noexcept try
{
    ABI::AdaptiveNamespace::IAdaptiveFontStylesDefinition* fontStyles;
    RETURN_IF_FAILED(hostConfig->get_FontStyles(&fontStyles));

    switch (style)
    {
    case ABI::AdaptiveNamespace::FontStyle::Display:
        RETURN_IF_FAILED(fontStyles->get_Display(styleDefinition));
        break;
    case ABI::AdaptiveNamespace::FontStyle::Monospace:
        RETURN_IF_FAILED(fontStyles->get_Monospace(styleDefinition));
        break;
    case ABI::AdaptiveNamespace::FontStyle::Default:
    default:
        RETURN_IF_FAILED(fontStyles->get_Default(styleDefinition));
        break;
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontSize(_In_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* sizesConfig,
                    ABI::AdaptiveNamespace::TextSize desiredSize,
                    _Out_ UINT32* resultSize) noexcept try
{
    switch (desiredSize)
    {
    case ABI::AdaptiveNamespace::TextSize::Small:
        RETURN_IF_FAILED(sizesConfig->get_Small(resultSize));
        break;
    case ABI::AdaptiveNamespace::TextSize::Medium:
        RETURN_IF_FAILED(sizesConfig->get_Medium(resultSize));
        break;
    case ABI::AdaptiveNamespace::TextSize::Large:
        RETURN_IF_FAILED(sizesConfig->get_Large(resultSize));
        break;
    case ABI::AdaptiveNamespace::TextSize::ExtraLarge:
        RETURN_IF_FAILED(sizesConfig->get_ExtraLarge(resultSize));
        break;
    case ABI::AdaptiveNamespace::TextSize::Default:
    default:
        RETURN_IF_FAILED(sizesConfig->get_Default(resultSize));
        break;
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT GetFontWeight(_In_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* weightsConfig,
                      ABI::AdaptiveNamespace::TextWeight desiredWeight,
                      _Out_ UINT16* resultWeight) noexcept try
{
    switch (desiredWeight)
    {
    case ABI::AdaptiveNamespace::TextWeight::Lighter:
        RETURN_IF_FAILED(weightsConfig->get_Lighter(resultWeight));
        break;
    case ABI::AdaptiveNamespace::TextWeight::Bolder:
        RETURN_IF_FAILED(weightsConfig->get_Bolder(resultWeight));
        break;
    case ABI::AdaptiveNamespace::TextWeight::Default:
    default:
        RETURN_IF_FAILED(weightsConfig->get_Default(resultWeight));
        break;
    }
    return S_OK;
}
CATCH_RETURN;

HRESULT StringToJsonObject(const std::string& inputString, _COM_Outptr_ IJsonObject** result)
{
    std::wstring asWstring = StringToWstring(inputString);
    return HStringToJsonObject(HStringReference(asWstring.c_str()).Get(), result);
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
    std::wstring asWstring = StringToWstring(inputString);
    return HStringToJsonValue(HStringReference(asWstring.c_str()).Get(), result);
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
    Json::FastWriter fastWriter;
    std::string jsonString = fastWriter.write(jsonCppValue);
    return StringToJsonObject(jsonString, result);
}

HRESULT JsonObjectToJsonCpp(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject, _Out_ Json::Value* jsonCppValue)
{
    std::string jsonString;
    RETURN_IF_FAILED(JsonObjectToString(jsonObject, jsonString));

    Json::Value value = ParseUtil::GetJsonValueFromString(jsonString);
    *jsonCppValue = value;

    return S_OK;
}

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveNamespace::ActionType projectedActionType, _Outptr_ HSTRING* result)
{
    ActionType sharedActionType = static_cast<ActionType>(projectedActionType);
    return UTF8ToHString(ActionTypeToString(sharedActionType), result);
}

HRESULT ProjectedElementTypeToHString(ABI::AdaptiveNamespace::ElementType projectedElementType, _Outptr_ HSTRING* result)
{
    CardElementType sharedElementType = static_cast<CardElementType>(projectedElementType);
    return UTF8ToHString(CardElementTypeToString(sharedElementType), result);
}

std::wstring StringToWstring(const std::string& in)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utfConverter;
    return utfConverter.from_bytes(in);
}

std::string WstringToString(const std::wstring& input)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utfConverter;
    return utfConverter.to_bytes(input);
}

void RemoteResourceElementToRemoteResourceInformationVector(_In_ ABI::AdaptiveNamespace::IAdaptiveElementWithRemoteResources* remoteResourceElement,
                                                            std::vector<RemoteResourceInformation>& resourceUris)
{
    ComPtr<ABI::Windows::Foundation::Collections::IVectorView<ABI::AdaptiveNamespace::AdaptiveRemoteResourceInformation*>> remoteResources;
    THROW_IF_FAILED(remoteResourceElement->GetResourceInformation(remoteResources.GetAddressOf()));

    ComPtr<IIterable<ABI::AdaptiveNamespace::AdaptiveRemoteResourceInformation*>> vectorIterable;
    THROW_IF_FAILED(remoteResources.As<IIterable<ABI::AdaptiveNamespace::AdaptiveRemoteResourceInformation*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<IIterator<ABI::AdaptiveNamespace::AdaptiveRemoteResourceInformation*>> vectorIterator;
    HRESULT hr = vectorIterable->First(&vectorIterator);

    boolean hasCurrent;
    THROW_IF_FAILED(vectorIterator->get_HasCurrent(&hasCurrent));

    while (SUCCEEDED(hr) && hasCurrent)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveRemoteResourceInformation> resourceInformation;
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

void GetUrlFromString(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
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
        HSTRING imageBaseUrl;
        THROW_IF_FAILED(hostConfig->get_ImageBaseUrl(&imageBaseUrl));

        if (imageBaseUrl != nullptr)
        {
            THROW_IF_FAILED(uriActivationFactory->CreateWithRelativeUri(imageBaseUrl, urlString, localUrl.GetAddressOf()));
        }
    }

    THROW_IF_FAILED(localUrl.CopyTo(url));
}

HRESULT SharedWarningsToAdaptiveWarnings(std::vector<std::shared_ptr<AdaptiveCardParseWarning>> sharedWarnings,
                                         _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings)
{
    for (auto sharedWarning : sharedWarnings)
    {
        HString warningMessage;
        RETURN_IF_FAILED(UTF8ToHString(sharedWarning->GetReason(), warningMessage.GetAddressOf()));

        ABI::AdaptiveNamespace::WarningStatusCode statusCode =
            static_cast<ABI::AdaptiveNamespace::WarningStatusCode>(sharedWarning->GetStatusCode());

        ComPtr<ABI::AdaptiveNamespace::IAdaptiveWarning> adaptiveWarning;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveWarning>(&adaptiveWarning, statusCode, warningMessage.Get()));

        RETURN_IF_FAILED(adaptiveWarnings->Append(adaptiveWarning.Get()));
    }

    return S_OK;
}

HRESULT AdaptiveWarningsToSharedWarnings(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
                                         std::vector<std::shared_ptr<AdaptiveCardParseWarning>> sharedWarnings)
{
    ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>> localAdaptiveWarnings{adaptiveWarnings};
    ComPtr<IIterable<ABI::AdaptiveNamespace::AdaptiveWarning*>> vectorIterable;
    RETURN_IF_FAILED(localAdaptiveWarnings.As<IIterable<ABI::AdaptiveNamespace::AdaptiveWarning*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<IIterator<ABI::AdaptiveNamespace::AdaptiveWarning*>> vectorIterator;
    HRESULT hr = vectorIterable->First(&vectorIterator);

    boolean hasCurrent;
    THROW_IF_FAILED(vectorIterator->get_HasCurrent(&hasCurrent));

    while (SUCCEEDED(hr) && hasCurrent)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveWarning> adaptiveWarning;
        RETURN_IF_FAILED(vectorIterator->get_Current(&adaptiveWarning));

        HString message;
        RETURN_IF_FAILED(adaptiveWarning->get_Message(message.GetAddressOf()));

        ABI::AdaptiveNamespace::WarningStatusCode statusCode;
        RETURN_IF_FAILED(adaptiveWarning->get_StatusCode(&statusCode));

        sharedWarnings.push_back(
            std::make_shared<AdaptiveCardParseWarning>(static_cast<AdaptiveSharedNamespace::WarningStatusCode>(statusCode),
                                                       HStringToUTF8(message.Get())));

        hr = vectorIterator->MoveNext(&hasCurrent);
    }

    return S_OK;
}

Color GenerateLighterColor(const Color& originalColor)
{
    const double lightIncrement = 0.25;

    Color lighterColor;
    lighterColor.A = originalColor.A;
    lighterColor.R = originalColor.R + static_cast<int>((255 - originalColor.R) * lightIncrement);
    lighterColor.G = originalColor.G + static_cast<int>((255 - originalColor.G) * lightIncrement);
    lighterColor.B = originalColor.B + static_cast<int>((255 - originalColor.B) * lightIncrement);
    return lighterColor;
}
