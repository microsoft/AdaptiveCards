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
#include "AdaptiveImage.h"
#include "AdaptiveImageSet.h"
#include "AdaptiveNumberInput.h"
#include "AdaptiveOpenUrlAction.h"
#include "AdaptiveSeparator.h"
#include "AdaptiveShowCardAction.h"
#include "AdaptiveSubmitAction.h"
#include "AdaptiveTextBlock.h"
#include "AdaptiveTextInput.h"
#include "AdaptiveTimeInput.h"
#include "AdaptiveToggleInput.h"
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
using namespace std;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace AdaptiveCards::Uwp;
using namespace Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

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

std::string HStringToUTF8(const HSTRING &in)
{
    std::string typeAsKey;
    HRESULT hr = HStringToUTF8(in, typeAsKey);
    return FAILED(hr) ? "" : typeAsKey;
}


bool Boolify(const boolean value)
{
    return value > 0 ? true : false;
}

HRESULT SetSharedElementProperties(
    ABI::AdaptiveCards::Uwp::IAdaptiveCardElement * adaptiveCardElement,
    std::shared_ptr<AdaptiveCards::BaseCardElement> sharedCardElement)
{
    HString id;
    RETURN_IF_FAILED(adaptiveCardElement->get_Id(id.GetAddressOf()));
    sharedCardElement->SetId(HStringToUTF8(id.Get()));

    boolean separator;
    RETURN_IF_FAILED(adaptiveCardElement->get_Separator(&separator));
    sharedCardElement->SetSeparator(separator);

    ABI::AdaptiveCards::Uwp::Spacing spacing;
    RETURN_IF_FAILED(adaptiveCardElement->get_Spacing(&spacing));
    sharedCardElement->SetSpacing(static_cast<AdaptiveCards::Spacing>(spacing));

    return S_OK;
}

template <typename TSharedBaseType, typename TSharedType, typename TAdaptiveBaseType, typename TAdaptiveType>
std::shared_ptr<TSharedBaseType> GetSharedModel(TAdaptiveBaseType * item)
{
    ComPtr<TAdaptiveType> adaptiveElement = PeekInnards<TAdaptiveType>(item);

    std::shared_ptr<TSharedType> sharedModelElement;
    if (adaptiveElement && SUCCEEDED(adaptiveElement->GetSharedModel(sharedModelElement)))
        return sharedModelElement;
    else
        return nullptr;
}

HRESULT GenerateSharedElements(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>* items,
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement>(items, [&](ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* item)
    {
        ABI::AdaptiveCards::Uwp::ElementType elementType;
        RETURN_IF_FAILED(item->get_ElementType(&elementType));

        std::shared_ptr<AdaptiveCards::BaseCardElement> baseCardElement;
        switch (elementType)
        {
            case ABI::AdaptiveCards::Uwp::ElementType::ChoiceSetInput:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::ChoiceSetInput, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveChoiceSetInput>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::ColumnSet:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::ColumnSet, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveColumnSet>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::Container:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::Container, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveContainer>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::DateInput:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::DateInput, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveDateInput>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::FactSet:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::FactSet, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveFactSet>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::Image:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::Image, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveImage>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::ImageSet:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::ImageSet, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveImageSet>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::NumberInput:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::NumberInput, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveNumberInput>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::TextBlock:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::TextBlock, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveTextBlock>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::TextInput:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::TextInput, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveTextInput>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::TimeInput:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::TimeInput, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveTimeInput>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::ToggleInput:
                baseCardElement = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::ToggleInput, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveToggleInput>(item);
                break;
            case ABI::AdaptiveCards::Uwp::ElementType::Custom:
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

HRESULT GenerateSharedAction(
    ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* action,
    std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedAction)
{
    ABI::AdaptiveCards::Uwp::ActionType actionType;
    RETURN_IF_FAILED(action->get_ActionType(&actionType));

    switch (actionType)
    {
        case ABI::AdaptiveCards::Uwp::ActionType::OpenUrl:
            sharedAction = GetSharedModel<AdaptiveCards::BaseActionElement, AdaptiveCards::OpenUrlAction, ABI::AdaptiveCards::Uwp::IAdaptiveActionElement, AdaptiveCards::Uwp::AdaptiveOpenUrlAction>(action);
            break;
        case ABI::AdaptiveCards::Uwp::ActionType::ShowCard:
            sharedAction = GetSharedModel<AdaptiveCards::BaseActionElement, AdaptiveCards::ShowCardAction, ABI::AdaptiveCards::Uwp::IAdaptiveActionElement, AdaptiveCards::Uwp::AdaptiveShowCardAction>(action);
            break;
        case ABI::AdaptiveCards::Uwp::ActionType::Submit:
            sharedAction = GetSharedModel<AdaptiveCards::BaseActionElement, AdaptiveCards::SubmitAction, ABI::AdaptiveCards::Uwp::IAdaptiveActionElement, AdaptiveCards::Uwp::AdaptiveSubmitAction>(action);
            break;
        case ABI::AdaptiveCards::Uwp::ActionType::Custom:
            sharedAction = std::make_shared<CustomActionWrapper>(action);
            break;
    }

    return S_OK;
}

HRESULT GenerateSharedActions(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement*>* actions,
    std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement>(actions, [&](ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* action)
    {
        std::shared_ptr<AdaptiveCards::BaseActionElement> baseActionElement;
        GenerateSharedAction(action, baseActionElement);
        containedElements.push_back(baseActionElement);
        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateSharedImages(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveImage*>* images,
    std::vector<std::shared_ptr<AdaptiveCards::Image>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveCards::Uwp::IAdaptiveImage>(images, [&](ABI::AdaptiveCards::Uwp::IAdaptiveImage* image)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveImage> localImage = image;
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement> imageAsElement;
        localImage.As(&imageAsElement);

        std::shared_ptr<AdaptiveCards::BaseCardElement> sharedImage = GetSharedModel<AdaptiveCards::BaseCardElement, AdaptiveCards::Image, ABI::AdaptiveCards::Uwp::IAdaptiveCardElement, AdaptiveCards::Uwp::AdaptiveImage>(imageAsElement.Get());
        containedElements.push_back(std::dynamic_pointer_cast<AdaptiveCards::Image>(sharedImage));

        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateSharedFacts(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFact*>* facts,
    std::vector<std::shared_ptr<AdaptiveCards::Fact>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveCards::Uwp::IAdaptiveFact>(facts, [&](ABI::AdaptiveCards::Uwp::IAdaptiveFact* fact)
    {
        ComPtr<AdaptiveCards::Uwp::AdaptiveFact> adaptiveElement = PeekInnards<AdaptiveCards::Uwp::AdaptiveFact>(fact);
        if (adaptiveElement == nullptr)
        {
            return E_INVALIDARG;
        }
        
        std::shared_ptr<AdaptiveCards::Fact> sharedFact;
        RETURN_IF_FAILED(adaptiveElement->GetSharedModel(sharedFact));
        containedElements.push_back(std::dynamic_pointer_cast<AdaptiveCards::Fact>(sharedFact));
        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateSharedChoices(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput*>* choices,
    std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput>(choices, [&](ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput* choice)
    {
        ComPtr<AdaptiveCards::Uwp::AdaptiveChoiceInput> adaptiveElement = PeekInnards<AdaptiveCards::Uwp::AdaptiveChoiceInput>(choice);
        if (adaptiveElement == nullptr)
        {
            return E_INVALIDARG;
        }

        std::shared_ptr<AdaptiveCards::ChoiceInput> sharedChoice;
        RETURN_IF_FAILED(adaptiveElement->GetSharedModel(sharedChoice));
        containedElements.push_back(std::dynamic_pointer_cast<AdaptiveCards::ChoiceInput>(sharedChoice));
        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCardElement> projectedContainedElement;
        switch(containedElement->GetElementType())
        {
        case CardElementType::TextBlock:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveTextBlock>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::TextBlock>(containedElement)));
            break;
        case CardElementType::Image:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveImage>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::Image>(containedElement)));
            break;
        case CardElementType::Container:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveContainer>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::Container>(containedElement)));
            break;
        case CardElementType::ColumnSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveColumnSet>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::ColumnSet>(containedElement)));
            break;
        case CardElementType::FactSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveFactSet>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::FactSet>(containedElement)));
            break;
        case CardElementType::ImageSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveImageSet>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::ImageSet>(containedElement)));
            break;
        case CardElementType::ChoiceSetInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveChoiceSetInput>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::ChoiceSetInput>(containedElement)));
            break;
        case CardElementType::DateInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveDateInput>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::DateInput>(containedElement)));
            break;
        case CardElementType::NumberInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveNumberInput>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::NumberInput>(containedElement)));
            break;
        case CardElementType::TextInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveTextInput>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::TextInput>(containedElement)));
            break;
        case CardElementType::TimeInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveTimeInput>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::TimeInput>(containedElement)));
            break;
        case CardElementType::ToggleInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveToggleInput>(&projectedContainedElement,
                std::dynamic_pointer_cast<AdaptiveCards::ToggleInput>(containedElement)));
            break;
        case CardElementType::Custom:
            RETURN_IF_FAILED(std::dynamic_pointer_cast<CustomElementWrapper>(containedElement)->GetWrappedElement(&projectedContainedElement));
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
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedAction : containedActions)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement> projectedContainedAction;
        RETURN_IF_FAILED(GenerateActionProjection(containedAction, &projectedContainedAction));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedAction.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateActionProjection(
    const std::shared_ptr<AdaptiveCards::BaseActionElement> action,
    ABI::AdaptiveCards::Uwp::IAdaptiveActionElement** projectedAction) noexcept try
{
    if (action == nullptr)
    {
        *projectedAction = nullptr;
        return S_OK;
    }

    switch (action->GetElementType())
    {
        case ActionType::OpenUrl:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveOpenUrlAction>(projectedAction,
                std::dynamic_pointer_cast<AdaptiveCards::OpenUrlAction>(action)));
            break;
        case ActionType::ShowCard:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveShowCardAction>(projectedAction,
                std::dynamic_pointer_cast<AdaptiveCards::ShowCardAction>(action)));
            break;
        case ActionType::Submit:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveSubmitAction>(projectedAction,
                std::dynamic_pointer_cast<AdaptiveCards::SubmitAction>(action)));
            break;
        case ActionType::Custom:
            RETURN_IF_FAILED(std::dynamic_pointer_cast<CustomActionWrapper> (action)->GetWrappedElement(projectedAction));
            break;
        default:
            return E_UNEXPECTED;
            break;
    }

    return S_OK;
} CATCH_RETURN;

HRESULT GenerateColumnsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Column>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveColumn*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveColumn> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveColumn>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Column>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateFactsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Fact>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveFact*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveFact> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveFact>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Fact>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateImagesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Image>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveImage*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveImage> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveImage>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::Image>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveChoiceInput> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveChoiceInput>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveCards::ChoiceInput>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateSeparatorProjection(
    std::shared_ptr<AdaptiveCards::Separator> sharedSeparator,
    ABI::AdaptiveCards::Uwp::IAdaptiveSeparator** projectedSeparator) noexcept try
{
    *projectedSeparator = nullptr;
    if (sharedSeparator != nullptr)
    {
        return MakeAndInitialize<::AdaptiveCards::Uwp::AdaptiveSeparator>(projectedSeparator, sharedSeparator);
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateSharedSeparator(
    ABI::AdaptiveCards::Uwp::IAdaptiveSeparator* separator,
    std::shared_ptr<AdaptiveCards::Separator>* sharedSeparatorOut) noexcept try
{
    ABI::AdaptiveCards::Uwp::ForegroundColor color;
    RETURN_IF_FAILED(separator->get_Color(&color));

    ABI::AdaptiveCards::Uwp::SeparatorThickness thickness;
    RETURN_IF_FAILED(separator->get_Thickness(&thickness));

    auto sharedSeparator = std::make_shared<Separator>();
    sharedSeparator->SetColor(static_cast<AdaptiveCards::ForegroundColor>(color));
    sharedSeparator->SetThickness(static_cast<AdaptiveCards::SeparatorThickness>(thickness));

    *sharedSeparatorOut = sharedSeparator;
    return S_OK;
} CATCH_RETURN;

HRESULT GetColorFromString(std::string colorString, ABI::Windows::UI::Color *color) noexcept try
{
    std::string alphaString = colorString.substr(1, 2);
    INT32 alpha = strtol(alphaString.c_str(), nullptr, 16);

    std::string redString = colorString.substr(3, 2);
    INT32 red = strtol(redString.c_str(), nullptr, 16);

    std::string greenString = colorString.substr(5, 2);
    INT32 green = strtol(greenString.c_str(), nullptr, 16);

    std::string blueString = colorString.substr(7, 2);
    INT32 blue = strtol(blueString.c_str(), nullptr, 16);

    color->A = static_cast<BYTE>(alpha);
    color->R = static_cast<BYTE>(red);
    color->G = static_cast<BYTE>(green);
    color->B = static_cast<BYTE>(blue);

    return S_OK;
} CATCH_RETURN;

HRESULT GetColorFromAdaptiveColor(
    ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveCards::Uwp::ForegroundColor adaptiveColor,
    ABI::AdaptiveCards::Uwp::ContainerStyle containerStyle,
    bool isSubtle,
    ABI::Windows::UI::Color * uiColor) noexcept try
{
    ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveContainerStylesDefinition> styles;
    RETURN_IF_FAILED(hostConfig->get_ContainerStyles(&styles));

    ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition> styleDefinition;
    if (containerStyle == ABI::AdaptiveCards::Uwp::ContainerStyle_Default)
    {
        RETURN_IF_FAILED(styles->get_Default(&styleDefinition));
    }
    else
    {
        RETURN_IF_FAILED(styles->get_Emphasis(&styleDefinition));
    }

    ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveColorsConfig> colorsConfig;
    RETURN_IF_FAILED(styleDefinition->get_ForegroundColors(&colorsConfig)); 

    ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig> colorConfig;
    switch (adaptiveColor)
    {
    case ABI::AdaptiveCards::Uwp::ForegroundColor::Accent:
        RETURN_IF_FAILED(colorsConfig->get_Accent(&colorConfig));
        break;
    case ABI::AdaptiveCards::Uwp::ForegroundColor::Dark:
        RETURN_IF_FAILED(colorsConfig->get_Dark(&colorConfig));
        break;
    case ABI::AdaptiveCards::Uwp::ForegroundColor::Light:
        RETURN_IF_FAILED(colorsConfig->get_Light(&colorConfig));
        break;
    case ABI::AdaptiveCards::Uwp::ForegroundColor::Good:
        RETURN_IF_FAILED(colorsConfig->get_Good(&colorConfig));
        break;
    case ABI::AdaptiveCards::Uwp::ForegroundColor::Warning:
        RETURN_IF_FAILED(colorsConfig->get_Warning(&colorConfig));
        break;
    case ABI::AdaptiveCards::Uwp::ForegroundColor::Attention:
        RETURN_IF_FAILED(colorsConfig->get_Attention(&colorConfig));
        break;
    case ABI::AdaptiveCards::Uwp::ForegroundColor::Default:
    default:
        RETURN_IF_FAILED(colorsConfig->get_Default(&colorConfig));
        break;
    }

    RETURN_IF_FAILED(isSubtle ? colorConfig->get_Subtle(uiColor) : colorConfig->get_Default(uiColor));

    return S_OK;
} CATCH_RETURN;

HRESULT GetSpacingSizeFromSpacing(
    ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveCards::Uwp::Spacing spacing,
    UINT* spacingSize) noexcept try
{
    ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveSpacingConfig> spacingConfig;
    RETURN_IF_FAILED(hostConfig->get_Spacing(&spacingConfig));

    switch (spacing)
    {
    case ABI::AdaptiveCards::Uwp::Spacing::None:
        *spacingSize = 0;
        break;
    case ABI::AdaptiveCards::Uwp::Spacing::Small:
        RETURN_IF_FAILED(spacingConfig->get_Small(spacingSize));
        break;
    case ABI::AdaptiveCards::Uwp::Spacing::Medium:
        RETURN_IF_FAILED(spacingConfig->get_Medium(spacingSize));
        break;
    case ABI::AdaptiveCards::Uwp::Spacing::Large:
        RETURN_IF_FAILED(spacingConfig->get_Large(spacingSize));
        break;
    case ABI::AdaptiveCards::Uwp::Spacing::ExtraLarge:
        RETURN_IF_FAILED(spacingConfig->get_ExtraLarge(spacingSize));
        break;
    case ABI::AdaptiveCards::Uwp::Spacing::Padding:
        RETURN_IF_FAILED(spacingConfig->get_Padding(spacingSize));
        break;
    case ABI::AdaptiveCards::Uwp::Spacing::Default:
    default:
        RETURN_IF_FAILED(spacingConfig->get_Default(spacingSize));
        break;
    }

    return S_OK;
} CATCH_RETURN;

HRESULT GetBackgroundColorFromStyle(
    ABI::AdaptiveCards::Uwp::ContainerStyle style,
    _In_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig,
    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept try
{
    ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveContainerStylesDefinition> containerStyles;
    RETURN_IF_FAILED(hostConfig->get_ContainerStyles(&containerStyles));

    ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition> styleDefinition;
    if (style == ABI::AdaptiveCards::Uwp::ContainerStyle::Default)
    {
        RETURN_IF_FAILED(containerStyles->get_Default(&styleDefinition));
    }
    else
    {
        RETURN_IF_FAILED(containerStyles->get_Emphasis(&styleDefinition));
    }

    RETURN_IF_FAILED(styleDefinition->get_BackgroundColor(backgroundColor));

    return S_OK;
} CATCH_RETURN;

HRESULT StringToJsonObject(const string inputString, IJsonObject** result)
{
    HSTRING asHstring;
    RETURN_IF_FAILED(UTF8ToHString(inputString, &asHstring));
    return HStringToJsonObject(asHstring, result);
}

HRESULT HStringToJsonObject(const HSTRING& inputHString, IJsonObject** result)
{
    ComPtr<IJsonObjectStatics> jObjectStatics;
    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Data_Json_JsonObject).Get(), &jObjectStatics));
    ComPtr<IJsonObject> jObject;
    HRESULT hr = jObjectStatics->Parse(inputHString, &jObject);
    if (FAILED(hr))
    {
        RETURN_IF_FAILED(ActivateInstance(
            HStringReference(RuntimeClass_Windows_Data_Json_JsonObject).Get(),
            &jObject));
    }
    *result = jObject.Detach();
    return S_OK;
}

HRESULT JsonObjectToString(IJsonObject* inputJson, string& result)
{
    HSTRING asHstring;
    RETURN_IF_FAILED(JsonObjectToHString(inputJson, &asHstring));
    return HStringToUTF8(asHstring, result);
}

HRESULT JsonObjectToHString(IJsonObject* inputJson, HSTRING* result)
{
    if (!inputJson)
    {
        return E_INVALIDARG;
    }
    ComPtr<IJsonObject> localInputJson(inputJson);
    ComPtr<IJsonValue> asJsonValue;
    RETURN_IF_FAILED(localInputJson.As(&asJsonValue));
    return(asJsonValue->Stringify(result));
}

HRESULT JsonCppToJsonObject(Json::Value jsonCppValue, IJsonObject** result)
{
    Json::FastWriter fastWriter;
    std::string jsonString = fastWriter.write(jsonCppValue);
    return StringToJsonObject(jsonString, result);
}

HRESULT JsonObjectToJsonCpp(ABI::Windows::Data::Json::IJsonObject * jsonObject, Json::Value * jsonCppValue)
{
    std::string jsonString;
    RETURN_IF_FAILED(JsonObjectToString(jsonObject, jsonString));

    Json::Value value = ParseUtil::GetJsonValueFromString(jsonString);
    *jsonCppValue = value;

    return S_OK;
}

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveCards::Uwp::ActionType projectedActionType, HSTRING* result)
{
    ActionType sharedActionType = static_cast<ActionType>(projectedActionType);
    return UTF8ToHString(ActionTypeToString(sharedActionType), result);
}

HRESULT ProjectedElementTypeToHString(ABI::AdaptiveCards::Uwp::ElementType projectedElementType, HSTRING* result)
{
    CardElementType sharedElementType = static_cast<CardElementType>(projectedElementType);
    return UTF8ToHString(CardElementTypeToString(sharedElementType), result);
}

bool IsWarning(int FailureStatusCode)
{
    int mask = 0xFF000000;
    return (FailureStatusCode & mask) == 0x2000000;
}
