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
#include <MediaSource.h>
#include <windows.foundation.collections.h>
#include <ParseContext.h>
#include "AdaptiveCardParseWarning.h"
#include "RemoteResourceInformation.h"

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
HRESULT HStringToUTF8(const HSTRING& in, std::string& out);

std::string HStringToUTF8(const HSTRING& in);

bool Boolify(const boolean value);

HRESULT GetColorFromString(std::string colorString, ABI::Windows::UI::Color* color) noexcept;

HRESULT GetColorFromAdaptiveColor(ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveNamespace::ForegroundColor adaptiveColor,
                                  ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                  bool isSubtle,
                                  ABI::Windows::UI::Color* uiColor) noexcept;

HRESULT GetBackgroundColorFromStyle(ABI::AdaptiveNamespace::ContainerStyle style,
                                    _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept;

HRESULT GetFontDataFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                             _In_ ABI::AdaptiveNamespace::FontStyle style,
                             _In_ ABI::AdaptiveNamespace::TextSize desiredSize,
                             _In_ ABI::AdaptiveNamespace::TextWeight desiredWeight,
                             _Out_ HSTRING* resultFontFamilyName,
                             _Out_ UINT32* resultSize,
                             _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontFamilyFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                               _In_ ABI::AdaptiveNamespace::FontStyle style,
                               _Out_ HSTRING* resultFontFamilyName) noexcept;

HRESULT GetFontSizeFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                             _In_ ABI::AdaptiveNamespace::FontStyle style,
                             _In_ ABI::AdaptiveNamespace::TextSize desiredSize,
                             _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeightFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                               _In_ ABI::AdaptiveNamespace::FontStyle style,
                               _In_ ABI::AdaptiveNamespace::TextWeight desiredWeight,
                               _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                     _In_ ABI::AdaptiveNamespace::FontStyle style,
                     _Out_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** styleDefinition) noexcept;

HRESULT GetFontSize(_In_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* sizesConfig,
                    _In_ ABI::AdaptiveNamespace::TextSize desiredSize,
                    _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeight(_In_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* weightsConfig,
                      _In_ ABI::AdaptiveNamespace::TextWeight desiredWeight,
                      _Out_ UINT16* resultWeight) noexcept;

HRESULT GetSpacingSizeFromSpacing(ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveNamespace::Spacing spacing,
                                  UINT* spacingSize) noexcept;

HRESULT GenerateSharedElements(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* items,
                               std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements);

HRESULT GenerateSharedAction(ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                             std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedAction);

HRESULT GenerateSharedActions(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* items,
                              std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& containedElements);

HRESULT GenerateSharedImages(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveImage*>* items,
                             std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements);

HRESULT GenerateSharedFacts(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveFact*>* items,
                            std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements);

HRESULT GenerateSharedChoices(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveChoiceInput*>* items,
                              std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements);

HRESULT GenerateSharedMediaSources(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveMediaSource*>* items,
                                   std::vector<std::shared_ptr<AdaptiveSharedNamespace::MediaSource>>& containedElements);

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& actions,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionProjection(const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> action,
                                 ABI::AdaptiveNamespace::IAdaptiveActionElement** projectedAction) noexcept;

HRESULT GenerateColumnsProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Column>>& containedElements,
                                  ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveColumn*>* projectedParentContainer) noexcept;

HRESULT GenerateFactsProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements,
                                ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveFact*>* projectedParentContainer) noexcept;

HRESULT GenerateImagesProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements,
                                 ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveImage*>* projectedParentContainer) noexcept;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveChoiceInput*>* projectedParentContainer) noexcept;

HRESULT GenerateMediaSourcesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::MediaSource>>& containedElements,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveMediaSource*>* projectedParentContainer) noexcept;

HRESULT GenerateSeparatorProjection(std::shared_ptr<AdaptiveSharedNamespace::Separator> sharedSeparator,
                                    ABI::AdaptiveNamespace::IAdaptiveSeparator** projectedSeparator) noexcept;

HRESULT GenerateSharedSeparator(ABI::AdaptiveNamespace::IAdaptiveSeparator* separator,
                                std::shared_ptr<AdaptiveSharedNamespace::Separator>* sharedSeparatorOut) noexcept;

HRESULT StringToJsonObject(const std::string inputString, ABI::Windows::Data::Json::IJsonObject** result);
HRESULT HStringToJsonObject(const HSTRING& inputHString, ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToHString(ABI::Windows::Data::Json::IJsonObject* inputJson, HSTRING* result);
HRESULT JsonObjectToString(ABI::Windows::Data::Json::IJsonObject* inputJson, std::string& result);

HRESULT StringToJsonValue(const std::string inputString, ABI::Windows::Data::Json::IJsonValue** result);
HRESULT HStringToJsonValue(const HSTRING& inputHString, ABI::Windows::Data::Json::IJsonValue** result);
HRESULT JsonValueToHString(ABI::Windows::Data::Json::IJsonValue* inputJsonValue, HSTRING* result);
HRESULT JsonValueToString(ABI::Windows::Data::Json::IJsonValue* inputJsonValue, std::string& result);

HRESULT JsonCppToJsonObject(Json::Value jsonCppValue, ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToJsonCpp(ABI::Windows::Data::Json::IJsonObject* jsonObject, Json::Value* jsonCppValue);

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveNamespace::ActionType projectedActionType, HSTRING* result);
HRESULT ProjectedElementTypeToHString(ABI::AdaptiveNamespace::ElementType projectedElementType, HSTRING* result);

typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveActionEventArgs*>> ActionEventSource;
typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveMediaEventArgs*>> MediaEventSource;

// Peek interface to help get implementation types from winrt interfaces
struct DECLSPEC_UUID("defc7d5f-b4e5-4a74-80be-d87bd50a2f45") ITypePeek : IInspectable
{
    virtual void* PeekAt(REFIID riid) = 0;
    template<typename Q> void* PeekHelper(REFIID riid, Q* pQ) { return (__uuidof(Q) == riid) ? pQ : nullptr; }

protected:
    virtual ~ITypePeek() {}
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

void RemoteResourceElementToRemoteResourceInformationVector(ABI::AdaptiveNamespace::IAdaptiveElementWithRemoteResources* remoteResources,
                                                            std::vector<AdaptiveSharedNamespace::RemoteResourceInformation>& resourceUris);

void GetUrlFromString(ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                      HSTRING urlString,
                      ABI::Windows::Foundation::IUriRuntimeClass** url);

HRESULT SharedWarningsToAdaptiveWarnings(
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>> sharedWarnings,
    ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>* adaptiveWarnings);

HRESULT AdaptiveWarningsToSharedWarnings(ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveWarning*>* adaptiveWarnings,
                                         std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>> sharedWarnings);

ABI::Windows::UI::Color GenerateLighterColor(ABI::Windows::UI::Color originalColor);
