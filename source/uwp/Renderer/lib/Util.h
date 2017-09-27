#pragma once
#include <wrl.h>
#include <wrl/wrappers/corewrappers.h>
#include <string>

#include "AdaptiveCards.XamlCardRenderer.h"
#include "InputItem.h"
#include <BaseCardElement.h>
#include <BaseActionElement.h>
#include <ChoiceInput.h>
#include <Column.h>
#include <Fact.h>
#include <Image.h>
#include <windows.foundation.collections.h>

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts a std::string to an HSTRING.
HRESULT UTF8ToHString(const std::string& in, HSTRING* out);

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts from HSTRING to a standard std::string.
HRESULT HStringToUTF8(const HSTRING& in, std::string &out);

std::string HStringToUTF8(const HSTRING& in);

bool Boolify(const boolean value);

HRESULT GetColorFromString(std::string colorString, ABI::Windows::UI::Color *color) noexcept;

HRESULT GetColorFromAdaptiveColor(
    ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor adaptiveColor,
    ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle containerStyle,
    bool isSubtle,
    ABI::Windows::UI::Color *uiColor) noexcept;

HRESULT GetBackgroundColorFromStyle(
    ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle style,
    _In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* hostConfig,
    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept;

HRESULT GetSpacingSizeFromSpacing(
    ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveCards::XamlCardRenderer::Spacing spacing,
    UINT* spacingSize) noexcept;

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& actions,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement*>* projectedParentContainer) noexcept;

HRESULT GenerateColumnsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Column>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumn*>* projectedParentContainer) noexcept;

HRESULT GenerateFactsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Fact>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFact*>* projectedParentContainer) noexcept;

HRESULT GenerateImagesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Image>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveImage*>* projectedParentContainer) noexcept;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveChoiceInput*>* projectedParentContainer) noexcept;

HRESULT GenerateSeparatorProjection(
    std::shared_ptr<AdaptiveCards::Separator> sharedSeparator,
    ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator** projectedSeparator) noexcept;

HRESULT GenerateSharedSeparator(
    ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator* separator,
    std::shared_ptr<AdaptiveCards::Separator>* sharedSeparatorOut)noexcept;

HRESULT StringToJsonObject(const std::string inputString, ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToHString(ABI::Windows::Data::Json::IJsonObject* inputJson, HSTRING* result);
HRESULT JsonObjectToString(ABI::Windows::Data::Json::IJsonObject* inputJson, std::string& result);

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveCards::XamlCardRenderer::ActionType projectedActionType, HSTRING* result);
HRESULT ProjectedElementTypeToHString(ABI::AdaptiveCards::XamlCardRenderer::ElementType projectedElementType, HSTRING* result);

typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard*, ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*>> ActionEventSource;

