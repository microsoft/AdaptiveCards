#pragma once
#include <wrl.h>
#include <wrl/wrappers/corewrappers.h>
#include <string>

#include "AdaptiveCards.Rendering.Uwp.h"
#include "InputValue.h"
#include <BaseCardElement.h>
#include <BaseActionElement.h>
#include <ChoiceInput.h>
#include <Column.h>
#include <Fact.h>
#include <Image.h>
#include <windows.foundation.collections.h>

#ifdef ADAPTIVE_CARDS_WINDOWS
using namespace InternalNamespace;
#endif

HRESULT WStringToHString(const std::wstring& in, HSTRING* out);

std::string WstringToString(const std::wstring& in);
std::wstring StringToWstring(const std::string& in);

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
    ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveNamespaceRef::ForegroundColor adaptiveColor,
    ABI::AdaptiveNamespaceRef::ContainerStyle containerStyle,
    bool isSubtle,
    ABI::Windows::UI::Color *uiColor) noexcept;

HRESULT GetBackgroundColorFromStyle(
    ABI::AdaptiveNamespaceRef::ContainerStyle style,
    _In_ ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig* hostConfig,
    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept;

HRESULT GetSpacingSizeFromSpacing(
    ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig* hostConfig,
    ABI::AdaptiveNamespaceRef::Spacing spacing,
    UINT* spacingSize) noexcept;

HRESULT SetSharedElementProperties(
    ABI::AdaptiveNamespaceRef::IAdaptiveCardElement * adaptiveCardElement,
    std::shared_ptr<AdaptiveCards::BaseCardElement> sharedCardElement);

HRESULT GenerateSharedElements(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveCardElement*>* items,
    std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements);

HRESULT GenerateSharedAction(
    ABI::AdaptiveNamespaceRef::IAdaptiveActionElement* action,
    std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedAction); 

HRESULT GenerateSharedActions(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveActionElement*>* items,
    std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedElements);

HRESULT GenerateSharedImages(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveImage*>* items,
    std::vector<std::shared_ptr<AdaptiveCards::Image>>& containedElements);

HRESULT GenerateSharedFacts(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveFact*>* items,
    std::vector<std::shared_ptr<AdaptiveCards::Fact>>& containedElements);

HRESULT GenerateSharedChoices(
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveChoiceInput*>* items,
    std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput>>& containedElements);

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveCardElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& actions,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveActionElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionProjection(
    const std::shared_ptr<AdaptiveCards::BaseActionElement> action,
    ABI::AdaptiveNamespaceRef::IAdaptiveActionElement** projectedAction) noexcept;

HRESULT GenerateColumnsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Column>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveColumn*>* projectedParentContainer) noexcept;

HRESULT GenerateFactsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Fact>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveFact*>* projectedParentContainer) noexcept;

HRESULT GenerateImagesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Image>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveImage*>* projectedParentContainer) noexcept;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::ChoiceInput>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveChoiceInput*>* projectedParentContainer) noexcept;

HRESULT GenerateSeparatorProjection(
    std::shared_ptr<AdaptiveCards::Separator> sharedSeparator,
    ABI::AdaptiveNamespaceRef::IAdaptiveSeparator** projectedSeparator) noexcept;

HRESULT GenerateSharedSeparator(
    ABI::AdaptiveNamespaceRef::IAdaptiveSeparator* separator,
    std::shared_ptr<AdaptiveCards::Separator>* sharedSeparatorOut)noexcept;

HRESULT StringToJsonObject(const std::string inputString, ABI::Windows::Data::Json::IJsonObject** result);
HRESULT HStringToJsonObject(const HSTRING& inputHString, ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToHString(ABI::Windows::Data::Json::IJsonObject* inputJson, HSTRING* result);
HRESULT JsonObjectToString(ABI::Windows::Data::Json::IJsonObject* inputJson, std::string& result);

HRESULT StringToJsonValue(const std::string inputString, ABI::Windows::Data::Json::IJsonValue ** result);
HRESULT HStringToJsonValue(const HSTRING& inputHString, ABI::Windows::Data::Json::IJsonValue** result);
HRESULT JsonValueToHString(ABI::Windows::Data::Json::IJsonValue* inputJsonValue, HSTRING* result);
HRESULT JsonValueToString(ABI::Windows::Data::Json::IJsonValue* inputJsonValue, std::string& result);

HRESULT JsonCppToJsonObject(Json::Value jsonCppValue, ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToJsonCpp(ABI::Windows::Data::Json::IJsonObject* jsonObject, Json::Value* jsonCppValue);

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveNamespaceRef::ActionType projectedActionType, HSTRING* result);
HRESULT ProjectedElementTypeToHString(ABI::AdaptiveNamespaceRef::ElementType projectedElementType, HSTRING* result);

typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespaceRef::RenderedAdaptiveCard*, ABI::AdaptiveNamespaceRef::AdaptiveActionEventArgs*>> ActionEventSource;

// Peek interface to help get implementation types from winrt interfaces
struct DECLSPEC_UUID("defc7d5f-b4e5-4a74-80be-d87bd50a2f45") ITypePeek : IInspectable
{
    virtual void *PeekAt(REFIID riid) = 0;
    template<typename Q> void *PeekHelper(REFIID riid, Q *pQ)
    {
        return (__uuidof(Q) == riid) ? pQ : nullptr;
    }
protected:
    virtual ~ITypePeek() { }
};

template<typename T, typename R> Microsoft::WRL::ComPtr<T> PeekInnards(R r)
{
    Microsoft::WRL::ComPtr<T> inner;
    Microsoft::WRL::ComPtr<ITypePeek> peeker;

    if (r && SUCCEEDED(r->QueryInterface(__uuidof(ITypePeek), &peeker)))
    {
        inner = reinterpret_cast<T*>(peeker->PeekAt(__uuidof(T)));
    }
    return inner;
}
