#include "pch.h"
#include <locale>
#include <codecvt>
#include <string>

#include "AdaptiveColumn.h"
#include "AdaptiveColumnSet.h"
#include "AdaptiveContainer.h"
#include "AdaptiveChoiceInput.h"
#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveDateInput.h"
#include "AdaptiveFact.h"
#include "AdaptiveFactSet.h"
#include "AdaptiveHttpAction.h"
#include "AdaptiveImage.h"
#include "AdaptiveImageSet.h"
#include "AdaptiveNumberInput.h"
#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveShowCardAction.h"
#include "AdaptiveSubmitAction.h"
#include "AdaptiveTextBlock.h"
#include "AdaptiveTextInput.h"
#include "AdaptiveTimeInput.h"
#include "AdaptiveToggleInput.h"
#include "util.h"

using namespace AdaptiveCards;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::UI;
using namespace std;

HRESULT UTF8ToHString(const string& in, HSTRING* out)
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wide = converter.from_bytes(in);
    return WindowsCreateString(wide.c_str(), static_cast<UINT32>(wide.length()), out);
}

HRESULT HStringToUTF8(const HSTRING& in, string& out)
{
    if (in == nullptr)
    {
        return E_INVALIDARG;
    }
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    out = converter.to_bytes(WindowsGetStringRawBuffer(in, nullptr));
    return S_OK;
}

bool Boolify(const boolean value)
{
    return value > 0 ? true : false;
}

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement> projectedContainedElement;
        switch(containedElement->GetElementType())
        {
        case CardElementType::TextBlock:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveTextBlock>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::TextBlock>(containedElement)));
            break;
        case CardElementType::Image:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveImage>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::Image>(containedElement)));
            break;
        case CardElementType::Container:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveContainer>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::Container>(containedElement)));
            break;
        case CardElementType::ColumnSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveColumnSet>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::ColumnSet>(containedElement)));
            break;
        case CardElementType::FactSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveFactSet>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::FactSet>(containedElement)));
            break;
        case CardElementType::ImageSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveImageSet>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::ImageSet>(containedElement)));
            break;
        case CardElementType::ChoiceSetInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveChoiceSetInput>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::ChoiceSetInput>(containedElement)));
            break;
        case CardElementType::DateInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveDateInput>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::DateInput>(containedElement)));
            break;
        case CardElementType::NumberInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveNumberInput>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::NumberInput>(containedElement)));
            break;
        case CardElementType::TextInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveTextInput>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::TextInput>(containedElement)));
            break;
        case CardElementType::TimeInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveTimeInput>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::TimeInput>(containedElement)));
            break;
        case CardElementType::ToggleInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveToggleInput>(&projectedContainedElement,
                std::static_pointer_cast<AdaptiveCards::ToggleInput>(containedElement)));
            break;
        default:
            return E_UNEXPECTED;
            break;
        }
        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedActions,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedAction : containedActions)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement> projectedContainedAction;
        switch (containedAction->GetElementType())
        {
            case ActionType::Http:
                RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveHttpAction>(&projectedContainedAction,
                    std::static_pointer_cast<AdaptiveCards::HttpAction>(containedAction)));
                break;
            case ActionType::OpenUrl:
                RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveOpenUrlAction>(&projectedContainedAction,
                    std::static_pointer_cast<AdaptiveCards::OpenUrlAction>(containedAction)));
                break;
            case ActionType::ShowCard:
                RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveShowCardAction>(&projectedContainedAction,
                    std::static_pointer_cast<AdaptiveCards::ShowCardAction>(containedAction)));
                break;
            case ActionType::Submit:
                RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveSubmitAction>(&projectedContainedAction,
                    std::static_pointer_cast<AdaptiveCards::SubmitAction>(containedAction)));
                break;
            default:
                return E_UNEXPECTED;
                break;
        }
        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedAction.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateColumnsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Column>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveColumn>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Column>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateFactsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Fact>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveFact>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Fact>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateImagesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Image>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveImage>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Image>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::XamlCardRenderer::AdaptiveChoiceInput>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::ChoiceInput>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GetColorFromString(std::string colorString, Color *color) noexcept try
{
    std::string alphaString = colorString.substr(1, 2);
    INT32 alpha = strtol(alphaString.c_str(), nullptr, 16);

    std::string redString = colorString.substr(3, 2);
    INT32 red = strtol(redString.c_str(), nullptr, 16);

    std::string blueString = colorString.substr(5, 2);
    INT32 blue = strtol(blueString.c_str(), nullptr, 16);

    std::string greenString = colorString.substr(7, 2);
    INT32 green = strtol(greenString.c_str(), nullptr, 16);

    color->A = static_cast<BYTE>(alpha);
    color->R = static_cast<BYTE>(red);
    color->B = static_cast<BYTE>(blue);
    color->G = static_cast<BYTE>(green);

    return S_OK;
} CATCH_RETURN;