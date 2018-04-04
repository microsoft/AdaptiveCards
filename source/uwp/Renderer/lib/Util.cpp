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
using namespace AdaptiveNamespace;
using namespace Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

HRESULT WStringToHString(const std::wstring& in, HSTRING* out)
{
    if (out == nullptr)
    {
        return E_INVALIDARG;
    }
    return WindowsCreateString(in.c_str(), static_cast<UINT32>(in.length()), out);
}

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

template <typename TSharedBaseType, typename TAdaptiveBaseType, typename TAdaptiveType>
std::shared_ptr<TSharedBaseType> GetSharedModel(TAdaptiveBaseType * item)
{
    ComPtr<TAdaptiveType> adaptiveElement = PeekInnards<TAdaptiveType>(item);

    std::shared_ptr<TSharedBaseType> sharedModelElement;
    if (adaptiveElement && SUCCEEDED(adaptiveElement->GetSharedModel(sharedModelElement)))
        return sharedModelElement;
    else
        return nullptr;
}

HRESULT GenerateSharedElements(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* items,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::IAdaptiveCardElement>(items, [&](ABI::AdaptiveNamespace::IAdaptiveCardElement* item)
    {
        ABI::AdaptiveNamespace::ElementType elementType;
        RETURN_IF_FAILED(item->get_ElementType(&elementType));

        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> baseCardElement;
        switch (elementType)
        {
            case ABI::AdaptiveNamespace::ElementType::ChoiceSetInput:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveChoiceSetInput>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::ColumnSet:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveColumnSet>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::Container:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveContainer>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::DateInput:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveDateInput>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::FactSet:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveFactSet>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::Image:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveImage>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::ImageSet:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveImageSet>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::NumberInput:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveNumberInput>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::TextBlock:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveTextBlock>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::TextInput:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveTextInput>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::TimeInput:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveTimeInput>(item);
                break;
            case ABI::AdaptiveNamespace::ElementType::ToggleInput:
                baseCardElement = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement, ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveToggleInput>(item);
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

HRESULT GenerateSharedAction(
    ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
    std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedAction)
{
    ABI::AdaptiveNamespace::ActionType actionType;
    RETURN_IF_FAILED(action->get_ActionType(&actionType));

    switch (actionType)
    {
        case ABI::AdaptiveNamespace::ActionType::OpenUrl:
            sharedAction = GetSharedModel<AdaptiveSharedNamespace::BaseActionElement, ABI::AdaptiveNamespace::IAdaptiveActionElement, AdaptiveNamespace::AdaptiveOpenUrlAction>(action);
            break;
        case ABI::AdaptiveNamespace::ActionType::ShowCard:
            sharedAction = GetSharedModel<AdaptiveSharedNamespace::BaseActionElement, ABI::AdaptiveNamespace::IAdaptiveActionElement, AdaptiveNamespace::AdaptiveShowCardAction>(action);
            break;
        case ABI::AdaptiveNamespace::ActionType::Submit:
            sharedAction = GetSharedModel<AdaptiveSharedNamespace::BaseActionElement, ABI::AdaptiveNamespace::IAdaptiveActionElement, AdaptiveNamespace::AdaptiveSubmitAction>(action);
            break;
        case ABI::AdaptiveNamespace::ActionType::Custom:
            sharedAction = std::make_shared<CustomActionWrapper>(action);
            break;
    }

    return S_OK;
}

HRESULT GenerateSharedActions(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* actions,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::IAdaptiveActionElement>(actions, [&](ABI::AdaptiveNamespace::IAdaptiveActionElement* action)
    {
        std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> baseActionElement;
        GenerateSharedAction(action, baseActionElement);
        containedElements.push_back(baseActionElement);
        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateSharedImages(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveImage*>* images,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::IAdaptiveImage>(images, [&](ABI::AdaptiveNamespace::IAdaptiveImage* image)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveImage> localImage = image;
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> imageAsElement;
        localImage.As(&imageAsElement);

        std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedImage = GetSharedModel<AdaptiveSharedNamespace::BaseCardElement,ABI::AdaptiveNamespace::IAdaptiveCardElement, AdaptiveNamespace::AdaptiveImage>(imageAsElement.Get());
        containedElements.push_back(std::AdaptivePointerCast<AdaptiveSharedNamespace::Image>(sharedImage));

        return S_OK;
    });

    return S_OK;
}

HRESULT GenerateSharedFacts(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveFact*>* facts,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::IAdaptiveFact>(facts, [&](ABI::AdaptiveNamespace::IAdaptiveFact* fact)
    {
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

HRESULT GenerateSharedChoices(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveChoiceInput*>* choices,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements)
{
    containedElements.clear();

    XamlHelpers::IterateOverVector<ABI::AdaptiveNamespace::IAdaptiveChoiceInput>(choices, [&](ABI::AdaptiveNamespace::IAdaptiveChoiceInput* choice)
    {
        ComPtr<AdaptiveNamespace::AdaptiveChoiceInput> adaptiveElement = PeekInnards<AdaptiveNamespace::AdaptiveChoiceInput>(choice);
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

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> projectedContainedElement;
        switch(containedElement->GetElementType())
        {
        case CardElementType::TextBlock:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveTextBlock>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::TextBlock>(containedElement)));
            break;
        case CardElementType::Image:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveImage>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::Image>(containedElement)));
            break;
        case CardElementType::Container:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveContainer>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::Container>(containedElement)));
            break;
        case CardElementType::ColumnSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveColumnSet>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::ColumnSet>(containedElement)));
            break;
        case CardElementType::FactSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveFactSet>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::FactSet>(containedElement)));
            break;
        case CardElementType::ImageSet:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveImageSet>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::ImageSet>(containedElement)));
            break;
        case CardElementType::ChoiceSetInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveChoiceSetInput>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::ChoiceSetInput>(containedElement)));
            break;
        case CardElementType::DateInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveDateInput>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::DateInput>(containedElement)));
            break;
        case CardElementType::NumberInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveNumberInput>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::NumberInput>(containedElement)));
            break;
        case CardElementType::TextInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveTextInput>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::TextInput>(containedElement)));
            break;
        case CardElementType::TimeInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveTimeInput>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::TimeInput>(containedElement)));
            break;
        case CardElementType::ToggleInput:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveToggleInput>(&projectedContainedElement,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::ToggleInput>(containedElement)));
            break;
        case CardElementType::Custom:
            RETURN_IF_FAILED(std::AdaptivePointerCast<CustomElementWrapper>(containedElement)->GetWrappedElement(&projectedContainedElement));
            break;
        }

        if (projectedContainedElement != nullptr)
        {
            RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
        }
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& containedActions,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* projectedParentContainer) noexcept try
{
    for (auto& containedAction : containedActions)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> projectedContainedAction;
        RETURN_IF_FAILED(GenerateActionProjection(containedAction, &projectedContainedAction));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedAction.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateActionProjection(
    const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> action,
    ABI::AdaptiveNamespace::IAdaptiveActionElement** projectedAction) noexcept try
{
    if (action == nullptr)
    {
        *projectedAction = nullptr;
        return S_OK;
    }

    switch (action->GetElementType())
    {
        case ActionType::OpenUrl:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveOpenUrlAction>(projectedAction,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::OpenUrlAction>(action)));
            break;
        case ActionType::ShowCard:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveShowCardAction>(projectedAction,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::ShowCardAction>(action)));
            break;
        case ActionType::Submit:
            RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveSubmitAction>(projectedAction,
                std::AdaptivePointerCast<AdaptiveSharedNamespace::SubmitAction>(action)));
            break;
        case ActionType::Custom:
            RETURN_IF_FAILED(std::AdaptivePointerCast<CustomActionWrapper> (action)->GetWrappedElement(projectedAction));
            break;
        default:
            return E_UNEXPECTED;
            break;
    }

    return S_OK;
} CATCH_RETURN;

HRESULT GenerateColumnsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Column>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveColumn*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveColumn> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveColumn>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveSharedNamespace::Column>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateFactsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveFact*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveFact> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveFact>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveSharedNamespace::Fact>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateImagesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveImage*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveImage> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveImage>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveSharedNamespace::Image>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveChoiceInput*>* projectedParentContainer) noexcept try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<ABI::AdaptiveNamespace::IAdaptiveChoiceInput> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<::AdaptiveNamespace::AdaptiveChoiceInput>(&projectedContainedElement,
            std::static_pointer_cast<AdaptiveSharedNamespace::ChoiceInput>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateSeparatorProjection(
    std::shared_ptr<AdaptiveSharedNamespace::Separator> sharedSeparator,
    ABI::AdaptiveNamespace::IAdaptiveSeparator** projectedSeparator) noexcept try
{
    *projectedSeparator = nullptr;
    if (sharedSeparator != nullptr)
    {
        return MakeAndInitialize<::AdaptiveNamespace::AdaptiveSeparator>(projectedSeparator, sharedSeparator);
    }
    return S_OK;
} CATCH_RETURN;

HRESULT GenerateSharedSeparator(
    ABI::AdaptiveNamespace::IAdaptiveSeparator* separator,
    std::shared_ptr<AdaptiveSharedNamespace::Separator>* sharedSeparatorOut) noexcept try
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
    ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveNamespace::ForegroundColor adaptiveColor,
    ABI::AdaptiveNamespace::ContainerStyle containerStyle,
    bool isSubtle,
    ABI::Windows::UI::Color * uiColor) noexcept try
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
} CATCH_RETURN;

HRESULT GetSpacingSizeFromSpacing(
    ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveNamespace::Spacing spacing,
    UINT* spacingSize) noexcept try
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
} CATCH_RETURN;

HRESULT GetBackgroundColorFromStyle(
    ABI::AdaptiveNamespace::ContainerStyle style,
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
} CATCH_RETURN;

HRESULT StringToJsonObject(const string inputString, IJsonObject** result)
{
    std::wstring asWstring = StringToWstring(inputString);
    return HStringToJsonObject(HStringReference(asWstring.c_str()).Get(), result);
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
    HString asHstring;
    RETURN_IF_FAILED(JsonObjectToHString(inputJson, asHstring.GetAddressOf()));
    return HStringToUTF8(asHstring.Get(), result);
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

HRESULT StringToJsonValue(const string inputString, IJsonValue** result)
{
    std::wstring asWstring = StringToWstring(inputString);
    return HStringToJsonValue(HStringReference(asWstring.c_str()).Get(), result);
}

HRESULT HStringToJsonValue(const HSTRING& inputHString, IJsonValue** result)
{
    ComPtr<IJsonValueStatics> jValueStatics;
    RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Data_Json_JsonValue).Get(), &jValueStatics));
    ComPtr<IJsonValue> jValue;
    HRESULT hr = jValueStatics->Parse(inputHString, &jValue);
    if (FAILED(hr))
    {
        RETURN_IF_FAILED(ActivateInstance(
            HStringReference(RuntimeClass_Windows_Data_Json_JsonValue).Get(),
            &jValue));
    }
    *result = jValue.Detach();
    return S_OK;
}


HRESULT JsonValueToString(IJsonValue* inputValue, string& result)
{
    HString asHstring;
    RETURN_IF_FAILED(JsonValueToHString(inputValue, asHstring.GetAddressOf()));
    return HStringToUTF8(asHstring.Get(), result);
}

HRESULT JsonValueToHString(IJsonValue* inputJsonValue, HSTRING* result)
{
    if (!inputJsonValue)
    {
        return E_INVALIDARG;
    }
    ComPtr<IJsonValue> localInputJsonValue(inputJsonValue);
    return (localInputJsonValue->Stringify(result));
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

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveNamespace::ActionType projectedActionType, HSTRING* result)
{
    ActionType sharedActionType = static_cast<ActionType>(projectedActionType);
    return UTF8ToHString(ActionTypeToString(sharedActionType), result);
}

HRESULT ProjectedElementTypeToHString(ABI::AdaptiveNamespace::ElementType projectedElementType, HSTRING* result)
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
    // Different platforms and compilers use different sizes for wchar_t, 
    // in Windows the size for wchar_t is 2 bytes (https://docs.microsoft.com/en-us/cpp/cpp/char-wchar-t-char16-t-char32-t)
    // while Android and iOS have a wchar_t size of 4 bytes
    #pragma warning( push )
    #pragma warning( disable : 4127)
    if (sizeof(wchar_t) == 2)
    #pragma warning( pop )
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utfConverter;
        return utfConverter.to_bytes(input);
    }
    else
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utfConverter;
        return utfConverter.to_bytes(input);
    }
}