// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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
#include <Inline.h>
#include <MediaSource.h>
#include <ToggleVisibilityTarget.h>
#include <windows.foundation.collections.h>
#include <ParseContext.h>
#include "AdaptiveCardParseWarning.h"
#include "RemoteResourceInformation.h"

#ifdef ADAPTIVE_CARDS_WINDOWS
using namespace InternalNamespace;
#endif

class bad_string_conversion : public std::exception
{
public:
    bad_string_conversion() : _dwErr(GetLastError()) {}

private:
    DWORD _dwErr;
};

HRESULT WStringToHString(std::wstring_view in, _Outptr_ HSTRING* out) noexcept;

std::string WstringToString(std::wstring_view in);
std::wstring StringToWstring(std::string_view in);

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts a std::string to an HSTRING.
HRESULT UTF8ToHString(std::string_view in, _Outptr_ HSTRING* out) noexcept;

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts from HSTRING to a standard std::string.
HRESULT HStringToUTF8(HSTRING in, std::string& out) noexcept;

std::string HStringToUTF8(HSTRING in);

inline bool Boolify(const boolean value) noexcept
{
    return (value > 0);
}

HRESULT GetColorFromString(const std::string& colorString, _Out_ ABI::Windows::UI::Color* color) noexcept;

HRESULT GetColorFromAdaptiveColor(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveNamespace::ForegroundColor adaptiveColor,
                                  ABI::AdaptiveNamespace::ContainerStyle containerStyle,
                                  bool isSubtle,
                                  bool highlight,
                                  _Out_ ABI::Windows::UI::Color* uiColor) noexcept;

HRESULT GetBackgroundColorFromStyle(ABI::AdaptiveNamespace::ContainerStyle style,
                                    _In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept;

HRESULT GetHighlighter(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs,
                       _Out_ ABI::Windows::UI::Xaml::Documents::ITextHighlighter** textHighlighter) noexcept;

HRESULT GetFontDataFromFontType(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveNamespace::FontType fontType,
                                ABI::AdaptiveNamespace::TextSize desiredSize,
                                ABI::AdaptiveNamespace::TextWeight desiredWeight,
                                _Outptr_ HSTRING* resultFontFamilyName,
                                _Out_ UINT32* resultSize,
                                _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontFamilyFromFontType(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveNamespace::FontType fontType,
                                  _Outptr_ HSTRING* resultFontFamilyName) noexcept;

HRESULT GetFontSizeFromFontType(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveNamespace::FontType fontType,
                                ABI::AdaptiveNamespace::TextSize desiredSize,
                                _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeightFromStyle(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                               ABI::AdaptiveNamespace::FontType fontType,
                               ABI::AdaptiveNamespace::TextWeight desiredWeight,
                               _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontType(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                    ABI::AdaptiveNamespace::FontType fontType,
                    _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontTypeDefinition** styleDefinition) noexcept;

HRESULT GetFontSize(_In_ ABI::AdaptiveNamespace::IAdaptiveFontSizesConfig* sizesConfig,
                    ABI::AdaptiveNamespace::TextSize desiredSize,
                    _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeight(_In_ ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig* weightsConfig,
                      ABI::AdaptiveNamespace::TextWeight desiredWeight,
                      _Out_ UINT16* resultWeight) noexcept;

HRESULT GetSpacingSizeFromSpacing(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveNamespace::Spacing spacing,
                                  _Out_ UINT* spacingSize) noexcept;

HRESULT GenerateSharedElement(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* items,
                              std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& containedElement);

HRESULT GenerateSharedElements(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* items,
                               std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements);

HRESULT GenerateSharedAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action,
                             std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedAction);

HRESULT GenerateSharedActions(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* items,
                              std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& containedElements);

HRESULT GenerateSharedRequirements(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveRequirement*>* adaptiveRequirements,
                                   std::shared_ptr<std::unordered_map<std::string, AdaptiveSharedNamespace::SemanticVersion>> sharedRequirements) noexcept;

HRESULT GenerateSharedImages(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveImage*>* items,
                             std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements);

HRESULT GenerateSharedFacts(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveFact*>* items,
                            std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements);

HRESULT GenerateSharedChoices(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput*>* items,
                              std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements);

HRESULT GenerateSharedMediaSources(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveMediaSource*>* items,
                                   std::vector<std::shared_ptr<AdaptiveSharedNamespace::MediaSource>>& containedElements);

HRESULT GenerateSharedInlines(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveInline*>* items,
                              std::vector<std::shared_ptr<AdaptiveSharedNamespace::Inline>>& containedElements);

HRESULT GenerateSharedToggleElements(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>* items,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>>& containedElements);

HRESULT GenerateElementProjection(_In_ const std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& baseElement,
                                  _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** projectedElement) noexcept;

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>>& actions,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveActionElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionProjection(const std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement> action,
                                 _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** projectedAction) noexcept;

HRESULT GenerateColumnsProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Column>>& containedElements,
                                  _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveColumn*>* projectedParentContainer) noexcept;

HRESULT GenerateFactsProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Fact>>& containedElements,
                                _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveFact*>* projectedParentContainer) noexcept;

HRESULT GenerateInlinesProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Inline>>& containedElements,
                                  _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveInline*>* projectedParentContainer) noexcept;

HRESULT GenerateRequirementsProjection(const std::shared_ptr<std::unordered_map<std::string, AdaptiveSharedNamespace::SemanticVersion>>& sharedRequirements,
                                       _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveRequirement*>* projectedRequirementVector) noexcept;

HRESULT GenerateImagesProjection(const std::vector<std::shared_ptr<AdaptiveSharedNamespace::Image>>& containedElements,
                                 _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveImage*>* projectedParentContainer) noexcept;

HRESULT GenerateInputChoicesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::ChoiceInput>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveChoiceInput*>* projectedParentContainer) noexcept;

HRESULT GenerateMediaSourcesProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::MediaSource>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveMediaSource*>* projectedParentContainer) noexcept;

HRESULT GenerateToggleTargetProjection(
    const std::vector<std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityTarget>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveToggleVisibilityTarget*>* projectedParentContainer) noexcept;

HRESULT GenerateSeparatorProjection(std::shared_ptr<AdaptiveSharedNamespace::Separator> sharedSeparator,
                                    _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveSeparator** projectedSeparator) noexcept;

HRESULT GenerateSharedSeparator(_In_ ABI::AdaptiveNamespace::IAdaptiveSeparator* separator,
                                _Out_ std::shared_ptr<AdaptiveSharedNamespace::Separator>* sharedSeparatorOut) noexcept;

HRESULT StringToJsonObject(const std::string& inputString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
HRESULT HStringToJsonObject(const HSTRING& inputHString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToHString(_In_ ABI::Windows::Data::Json::IJsonObject* inputJson, _Outptr_ HSTRING* result);
HRESULT JsonObjectToString(_In_ ABI::Windows::Data::Json::IJsonObject* inputJson, std::string& result);

HRESULT StringToJsonValue(const std::string inputString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonValue** result);
HRESULT HStringToJsonValue(const HSTRING& inputHString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonValue** result);
HRESULT JsonValueToHString(_In_ ABI::Windows::Data::Json::IJsonValue* inputJsonValue, _Outptr_ HSTRING* result);
HRESULT JsonValueToString(_In_ ABI::Windows::Data::Json::IJsonValue* inputJsonValue, std::string& result);

HRESULT JsonCppToJsonObject(const Json::Value& jsonCppValue, _COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToJsonCpp(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject, _Out_ Json::Value* jsonCppValue);

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveNamespace::ActionType projectedActionType, _Outptr_ HSTRING* result);
HRESULT ProjectedElementTypeToHString(ABI::AdaptiveNamespace::ElementType projectedElementType, _Outptr_ HSTRING* result);

HRESULT MeetsRequirements(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* cardElement,
                          _In_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration* featureRegistration,
                          _Out_ bool* meetsRequirements);

HRESULT IsBackgroundImageValid(_In_ ABI::AdaptiveNamespace::IAdaptiveBackgroundImage* backgroundImageElement, _Out_ BOOL* isValid);

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

void RemoteResourceElementToRemoteResourceInformationVector(_In_ ABI::AdaptiveNamespace::IAdaptiveElementWithRemoteResources* remoteResources,
                                                            std::vector<AdaptiveSharedNamespace::RemoteResourceInformation>& resourceUris);

void GetUrlFromString(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* hostConfig,
                      _In_ HSTRING urlString,
                      _Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** url);

HRESULT SharedWarningsToAdaptiveWarnings(
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>> sharedWarnings,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings);

HRESULT AdaptiveWarningsToSharedWarnings(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* adaptiveWarnings,
    std::vector<std::shared_ptr<AdaptiveSharedNamespace::AdaptiveCardParseWarning>>& sharedWarnings);

ABI::Windows::UI::Color GenerateLighterColor(const ABI::Windows::UI::Color& originalColor);

ABI::Windows::Foundation::DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day);

HRESULT GetDateTimeReference(unsigned int year,
                             unsigned int month,
                             unsigned int day,
                             _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::DateTime>** dateTimeReference);

ABI::AdaptiveNamespace::FallbackType MapSharedFallbackTypeToUwp(const AdaptiveSharedNamespace::FallbackType type);
AdaptiveSharedNamespace::FallbackType MapUwpFallbackTypeToShared(const ABI::AdaptiveNamespace::FallbackType type);

HRESULT CopyTextElement(_In_ ABI::AdaptiveNamespace::IAdaptiveTextElement* textElement,
                        _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveTextElement** copiedTextElement);

HRESULT GetAdaptiveActionParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveSharedNamespace::ActionParserRegistration>& sharedActionParserRegistration,
    _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionParserRegistration** adaptiveActionParserRegistration);

HRESULT GetAdaptiveElementParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveSharedNamespace::ElementParserRegistration>& sharedElementParserRegistration,
    _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveElementParserRegistration** adaptiveElementParserRegistration);

namespace AdaptiveNamespace
{
    class XamlBuilder;

    template<class TRegistration>
    HRESULT RegisterDefaultElementRenderers(TRegistration registration, Microsoft::WRL::ComPtr<XamlBuilder> xamlBuilder)
    {
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ActionSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveActionSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Column").Get(),
                                           Make<AdaptiveNamespace::AdaptiveColumnRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ColumnSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveColumnSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Container").Get(),
                                           Make<AdaptiveNamespace::AdaptiveContainerRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"FactSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveFactSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Image").Get(),
                                           Make<AdaptiveNamespace::AdaptiveImageRenderer>(xamlBuilder).Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ImageSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveImageSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.ChoiceSet").Get(),
                                           Make<AdaptiveNamespace::AdaptiveChoiceSetInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Date").Get(),
                                           Make<AdaptiveNamespace::AdaptiveDateInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Number").Get(),
                                           Make<AdaptiveNamespace::AdaptiveNumberInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Text").Get(),
                                           Make<AdaptiveNamespace::AdaptiveTextInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Time").Get(),
                                           Make<AdaptiveNamespace::AdaptiveTimeInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Toggle").Get(),
                                           Make<AdaptiveNamespace::AdaptiveToggleInputRenderer>().Get()));
        RETURN_IF_FAILED(
            registration->Set(HStringReference(L"Media").Get(), Make<AdaptiveNamespace::AdaptiveMediaRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"RichTextBlock").Get(),
                                           Make<AdaptiveNamespace::AdaptiveRichTextBlockRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"TextBlock").Get(),
                                           Make<AdaptiveNamespace::AdaptiveTextBlockRenderer>().Get()));

        return S_OK;
    }

    template<class TRegistration> HRESULT RegisterDefaultActionRenderers(TRegistration registration)
    {
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.OpenUrl").Get(),
                                           Make<AdaptiveNamespace::AdaptiveOpenUrlActionRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.ShowCard").Get(),
                                           Make<AdaptiveNamespace::AdaptiveShowCardActionRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.Submit").Get(),
                                           Make<AdaptiveNamespace::AdaptiveSubmitActionRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.ToggleVisibility").Get(),
                                           Make<AdaptiveNamespace::AdaptiveToggleVisibilityActionRenderer>().Get()));
        return S_OK;
    }
}
