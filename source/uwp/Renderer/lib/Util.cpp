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
            RETURN_IF_FAILED(std::dynamic_pointer_cast<CustomElementWrapper> (containedElement)->GetWrappedElement(&projectedContainedElement));
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