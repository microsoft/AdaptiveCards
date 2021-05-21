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
#include "TableCell.h"

class bad_string_conversion : public std::exception
{
public:
    bad_string_conversion() : _dwErr(GetLastError()) {}

private:
    DWORD _dwErr;
};

HRESULT WStringToHString(std::wstring_view in, _Outptr_ HSTRING* out) noexcept;

std::string WStringToString(std::wstring_view in);
std::wstring StringToWString(std::string_view in);

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

template<typename T, typename TInterface, typename C>
HRESULT IterateOverVectorWithFailure(_In_ ABI::Windows::Foundation::Collections::IVector<T*>* vector, const boolean stopOnFailure, C iterationCallback)
{
    Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<T*>> localVector(vector);
    ComPtr<IIterable<T*>> vectorIterable;
    HRESULT hr = localVector.As<IIterable<T*>>(&vectorIterable);

    if (SUCCEEDED(hr))
    {
        Microsoft::WRL::ComPtr<IIterator<T*>> vectorIterator;
        vectorIterable->First(&vectorIterator);

        boolean hasCurrent = false;
        hr = vectorIterator->get_HasCurrent(&hasCurrent);
        while (SUCCEEDED(hr) && hasCurrent)
        {
            Microsoft::WRL::ComPtr<TInterface> current = nullptr;
            if (FAILED(vectorIterator->get_Current(current.GetAddressOf())))
            {
                return S_OK;
            }

            hr = iterationCallback(current.Get());
            if (stopOnFailure && FAILED(hr))
            {
                return hr;
            }

            hr = vectorIterator->MoveNext(&hasCurrent);
        }
    }

    return hr;
}

template<typename T, typename C>
HRESULT IterateOverVectorWithFailure(_In_ ABI::Windows::Foundation::Collections::IVector<T*>* vector, const boolean stopOnFailure, C iterationCallback)
{
    return IterateOverVectorWithFailure<T, T, C>(vector, stopOnFailure, iterationCallback);
}

template<typename T, typename TInterface, typename C>
void IterateOverVector(_In_ ABI::Windows::Foundation::Collections::IVector<T*>* vector, C iterationCallback)
{
    Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<T*>> localVector(vector);
    ComPtr<ABI::Windows::Foundation::Collections::IIterable<T*>> vectorIterable;
    THROW_IF_FAILED(localVector.As<ABI::Windows::Foundation::Collections::IIterable<T*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IIterator<T*>> vectorIterator;
    if (FAILED(vectorIterable->First(&vectorIterator)))
    {
        return;
    }

    boolean hasCurrent = false;
    HRESULT hr = vectorIterator->get_HasCurrent(&hasCurrent);
    while (SUCCEEDED(hr) && hasCurrent)
    {
        Microsoft::WRL::ComPtr<TInterface> current = nullptr;
        hr = vectorIterator->get_Current(current.GetAddressOf());
        if (FAILED(hr))
        {
            break;
        }

        iterationCallback(current.Get());
        hr = vectorIterator->MoveNext(&hasCurrent);
    }
}

template<typename T, typename C>
void IterateOverVector(_In_ ABI::Windows::Foundation::Collections::IVector<T*>* vector, C iterationCallback)
{
    IterateOverVector<T, T, C>(vector, iterationCallback);
}

HRESULT GetColorFromString(const std::string& colorString, _Out_ ABI::Windows::UI::Color* color) noexcept;

HRESULT GetColorFromAdaptiveColor(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor adaptiveColor,
                                  ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle containerStyle,
                                  bool isSubtle,
                                  bool highlight,
                                  _Out_ ABI::Windows::UI::Color* uiColor) noexcept;

HRESULT GetBackgroundColorFromStyle(ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle style,
                                    _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept;

HRESULT GetHighlighter(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs,
                       _Out_ ABI::Windows::UI::Xaml::Documents::ITextHighlighter** textHighlighter) noexcept;

HRESULT GetFontDataFromFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                                ABI::AdaptiveCards::Rendering::Uwp::TextSize desiredSize,
                                ABI::AdaptiveCards::Rendering::Uwp::TextWeight desiredWeight,
                                _Outptr_ HSTRING* resultFontFamilyName,
                                _Out_ UINT32* resultSize,
                                _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontFamilyFromFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                                  _Outptr_ HSTRING* resultFontFamilyName) noexcept;

HRESULT GetFontSizeFromFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                                ABI::AdaptiveCards::Rendering::Uwp::TextSize desiredSize,
                                _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeightFromStyle(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                               ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                               ABI::AdaptiveCards::Rendering::Uwp::TextWeight desiredWeight,
                               _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontType(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                    ABI::AdaptiveCards::Rendering::Uwp::FontType fontType,
                    _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontTypeDefinition** styleDefinition) noexcept;

HRESULT GetFontSize(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontSizesConfig* sizesConfig,
                    ABI::AdaptiveCards::Rendering::Uwp::TextSize desiredSize,
                    _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeight(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontWeightsConfig* weightsConfig,
                      ABI::AdaptiveCards::Rendering::Uwp::TextWeight desiredWeight,
                      _Out_ UINT16* resultWeight) noexcept;

HRESULT GetSpacingSizeFromSpacing(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing,
                                  _Out_ UINT* spacingSize) noexcept;

HRESULT GenerateSharedElement(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* items,
                              std::shared_ptr<AdaptiveCards::BaseCardElement>& containedElement);

HRESULT GenerateSharedElements(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement*>* items,
                               std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements);

HRESULT GenerateSharedAction(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* action,
                             std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedAction);

HRESULT GenerateSharedActions(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement*>* items,
                              std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedElements);

HRESULT GenerateSharedRequirements(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRequirement*>* adaptiveRequirements,
    std::unordered_map<std::string, AdaptiveCards::SemanticVersion>& sharedRequirements) noexcept;

HRESULT GenerateSharedInlines(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline*>* items,
                              std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements);

template<class TSharedClass, class TWinrtInterface, class TWinrtClass, class TImplementationClass, class TReturnedSharedModelType>
HRESULT GenerateSharedVector(_In_ ABI::Windows::Foundation::Collections::IVector<TWinrtClass*>* tableCells,
                             std::vector<std::shared_ptr<TSharedClass>>& containedElements)
{
    containedElements.clear();

    IterateOverVector<TWinrtClass, TWinrtInterface>(tableCells, [&](TWinrtInterface* tableCell) {
        ComPtr<TImplementationClass> adaptiveElement = PeekInnards<TImplementationClass>(tableCell);
        if (adaptiveElement == nullptr)
        {
            return E_INVALIDARG;
        }

        std::shared_ptr<TReturnedSharedModelType> sharedTableCell;
        RETURN_IF_FAILED(adaptiveElement->GetSharedModel(sharedTableCell));
        containedElements.push_back(std::AdaptivePointerCast<TSharedClass>(sharedTableCell));
        return S_OK;
    });

    return S_OK;
}

#define GenerateSharedToggleElements(WINRTTOGGLEELEMENTS, SHAREDTOGGLEELEMENTS) \
    GenerateSharedVector<AdaptiveCards::ToggleVisibilityTarget, \
                         ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveToggleVisibilityTarget, \
                         ABI::AdaptiveCards::Rendering::Uwp::AdaptiveToggleVisibilityTarget, \
                         AdaptiveToggleVisibilityTarget, \
                         AdaptiveCards::ToggleVisibilityTarget>(WINRTTOGGLEELEMENTS, SHAREDTOGGLEELEMENTS);

#define GenerateSharedImages(WINRTIMAGES, SHAREDIMAGES) \
    GenerateSharedVector<AdaptiveCards::Image, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImage, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveImage, AdaptiveImage, AdaptiveCards::BaseCardElement>( \
        WINRTIMAGES, SHAREDIMAGES);

#define GenerateSharedFacts(WINRTFACTS, SHAREDFACTS) \
    GenerateSharedVector<AdaptiveCards::Fact, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFact, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveFact, AdaptiveFact, AdaptiveCards::Fact>( \
        WINRTFACTS, SHAREDFACTS);

#define GenerateSharedChoices(WINRTCHOICEINPUTS, SHAREDCHOICEINPUTS) \
    GenerateSharedVector<AdaptiveCards::ChoiceInput, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceInput, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveChoiceInput, AdaptiveChoiceInput, AdaptiveCards::ChoiceInput>( \
        WINRTCHOICEINPUTS, SHAREDCHOICEINPUTS);

#define GenerateSharedMediaSources(WINRTMEDIASOURCES, SHAREDMEDIASOURCES) \
    GenerateSharedVector<AdaptiveCards::MediaSource, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaSource, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveMediaSource, AdaptiveMediaSource, AdaptiveCards::MediaSource>( \
        WINRTMEDIASOURCES, SHAREDMEDIASOURCES);

#define GenerateSharedColumns(WINRTCOLUMNS, SHAREDCOLUMNS) \
    GenerateSharedVector<AdaptiveCards::Column, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColumn, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveColumn, AdaptiveColumn, AdaptiveCards::BaseCardElement>( \
        WINRTCOLUMNS, SHAREDCOLUMNS);

#define GenerateSharedTableCells(WINRTTABLECELLS, SHAREDTABLECELLS) \
    GenerateSharedVector<AdaptiveCards::TableCell, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableCell, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveTableCell, AdaptiveTableCell, AdaptiveCards::BaseCardElement>( \
        WINRTTABLECELLS, SHAREDTABLECELLS);

#define GenerateSharedTableRows(WINRTTABLEROWS, SHAREDTABLEROWS) \
    GenerateSharedVector<AdaptiveCards::TableRow, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableRow, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveTableRow, AdaptiveTableRow, AdaptiveCards::BaseCardElement>( \
        WINRTTABLEROWS, SHAREDTABLEROWS);

#define GenerateSharedTableColumnDefinitions(WINRTTABLECOLUMNS, SHAREDTABLECOLUMNS) \
    GenerateSharedVector<AdaptiveCards::TableColumnDefinition, \
                         ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableColumnDefinition, \
                         ABI::AdaptiveCards::Rendering::Uwp::AdaptiveTableColumnDefinition, \
                         AdaptiveTableColumnDefinition, \
                         AdaptiveCards::TableColumnDefinition>(WINRTTABLECOLUMNS, SHAREDTABLECOLUMNS);

HRESULT GenerateElementProjection(_In_ const std::shared_ptr<AdaptiveCards::BaseCardElement>& baseElement,
                                  _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** projectedElement) noexcept;

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& actions,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionProjection(const std::shared_ptr<AdaptiveCards::BaseActionElement>& action,
                                 _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement** projectedAction) noexcept;

HRESULT GenerateInlinesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline*>* projectedParentContainer) noexcept;

HRESULT GenerateRequirementsProjection(
    const std::unordered_map<std::string, AdaptiveCards::SemanticVersion>& sharedRequirements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRequirement*>* projectedRequirementVector) noexcept;

template<class TSharedClass, class TWinrtInterface, class TWinrtClass, class TImplementationClass>
HRESULT GenerateVectorProjection(const std::vector<std::shared_ptr<TSharedClass>>& containedElements,
                                 _In_ ABI::Windows::Foundation::Collections::IVector<TWinrtClass*>* projectedParentContainer) noexcept
try
{
    for (auto& containedElement : containedElements)
    {
        ComPtr<TWinrtInterface> projectedContainedElement;
        RETURN_IF_FAILED(MakeAndInitialize<TImplementationClass>(&projectedContainedElement,
                                                                 std::static_pointer_cast<TSharedClass>(containedElement)));

        RETURN_IF_FAILED(projectedParentContainer->Append(projectedContainedElement.Detach()));
    }
    return S_OK;
}
CATCH_RETURN;

#define GenerateImagesProjection(SHAREDIMAGES, WINRTIMAGES) \
    GenerateVectorProjection<AdaptiveCards::Image, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImage, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveImage, AdaptiveImage>( \
        SHAREDIMAGES, WINRTIMAGES);

#define GenerateFactsProjection(SHAREDFACTS, WINRTFACTS) \
    GenerateVectorProjection<AdaptiveCards::Fact, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFact, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveFact, AdaptiveFact>( \
        SHAREDFACTS, WINRTFACTS);

#define GenerateInputChoicesProjection(SHAREDCHOICES, WINRTCHOICES) \
    GenerateVectorProjection<AdaptiveCards::ChoiceInput, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveChoiceInput, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveChoiceInput, AdaptiveChoiceInput>( \
        SHAREDCHOICES, WINRTCHOICES);

#define GenerateMediaSourcesProjection(SHAREDMEDIASOURCES, WINRTMEDIASOURCES) \
    GenerateVectorProjection<AdaptiveCards::MediaSource, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaSource, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveMediaSource, AdaptiveMediaSource>( \
        SHAREDMEDIASOURCES, WINRTMEDIASOURCES);

#define GenerateColumnsProjection(SHAREDCOLUMNS, WINRTCOLUMNS) \
    GenerateVectorProjection<AdaptiveCards::Column, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColumn, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveColumn, AdaptiveColumn>( \
        SHAREDCOLUMNS, WINRTCOLUMNS);

#define GenerateToggleTargetProjection(SHAREDTOGGLETARGETS, WINRTTOGGLETARGETS) \
    GenerateVectorProjection<AdaptiveCards::ToggleVisibilityTarget, \
                             ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveToggleVisibilityTarget, \
                             ABI::AdaptiveCards::Rendering::Uwp::AdaptiveToggleVisibilityTarget, \
                             AdaptiveToggleVisibilityTarget>( \
        SHAREDTOGGLETARGETS, WINRTTOGGLETARGETS);

#define GenerateTableCellsProjection(SHAREDTABLECELLS, WINRTTABLECELLS) \
    GenerateVectorProjection<AdaptiveCards::TableCell, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableCell, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveTableCell, AdaptiveTableCell>( \
        SHAREDTABLECELLS, WINRTTABLECELLS);

#define GenerateTableRowsProjection(SHAREDTABLEROWS, WINRTTABLEROWS) \
    GenerateVectorProjection<AdaptiveCards::TableRow, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableRow, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveTableRow, AdaptiveTableRow>( \
        SHAREDTABLEROWS, WINRTTABLEROWS);

#define GenerateTableColumnDefinitionsProjection(SHAREDTABLECOLUMNDEFINITIONS, WINRTTABLECOLUMNDEFINITIONS) \
    GenerateVectorProjection<AdaptiveCards::TableColumnDefinition, ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableColumnDefinition, ABI::AdaptiveCards::Rendering::Uwp::AdaptiveTableColumnDefinition, AdaptiveTableColumnDefinition>( \
        SHAREDTABLECOLUMNDEFINITIONS, WINRTTABLECOLUMNDEFINITIONS);

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

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveCards::Rendering::Uwp::ActionType projectedActionType, _Outptr_ HSTRING* result);
HRESULT ProjectedElementTypeToHString(ABI::AdaptiveCards::Rendering::Uwp::ElementType projectedElementType, _Outptr_ HSTRING* result);

HRESULT MeetsRequirements(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* cardElement,
                          _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFeatureRegistration* featureRegistration,
                          _Out_ bool* meetsRequirements);

HRESULT IsBackgroundImageValid(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveBackgroundImage* backgroundImageElement,
                               _Out_ BOOL* isValid);

typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard*,
                                                                                 ABI::AdaptiveCards::Rendering::Uwp::AdaptiveActionEventArgs*>>
    ActionEventSource;
typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard*,
                                                                                 ABI::AdaptiveCards::Rendering::Uwp::AdaptiveMediaEventArgs*>>
    MediaEventSource;

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

void RemoteResourceElementToRemoteResourceInformationVector(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementWithRemoteResources* remoteResources,
                                                            std::vector<AdaptiveCards::RemoteResourceInformation>& resourceUris);

void GetUrlFromString(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* hostConfig,
                      _In_ HSTRING urlString,
                      _Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** url);

HRESULT SharedWarningsToAdaptiveWarnings(
    const std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& sharedWarnings,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings);

HRESULT AdaptiveWarningsToSharedWarnings(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* adaptiveWarnings,
    std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& sharedWarnings);

ABI::Windows::UI::Color GenerateLHoverColor(const ABI::Windows::UI::Color& originalColor);

ABI::Windows::Foundation::DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day);

HRESULT GetDateTimeReference(unsigned int year,
                             unsigned int month,
                             unsigned int day,
                             _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::DateTime>** dateTimeReference);

ABI::AdaptiveCards::Rendering::Uwp::FallbackType MapSharedFallbackTypeToUwp(const AdaptiveCards::FallbackType type);
AdaptiveCards::FallbackType MapUwpFallbackTypeToShared(const ABI::AdaptiveCards::Rendering::Uwp::FallbackType type);

HRESULT CopyTextElement(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextElement* textElement,
                        _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextElement** copiedTextElement);

HRESULT GetAdaptiveActionParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ActionParserRegistration>& sharedActionParserRegistration,
    _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionParserRegistration** adaptiveActionParserRegistration);

HRESULT GetAdaptiveElementParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ElementParserRegistration>& sharedElementParserRegistration,
    _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveElementParserRegistration** adaptiveElementParserRegistration);

namespace AdaptiveCards::Rendering::Uwp
{
    class XamlBuilder;

    template<class TRegistration>
    HRESULT RegisterDefaultElementRenderers(TRegistration registration, Microsoft::WRL::ComPtr<XamlBuilder> xamlBuilder)
    {
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ActionSet").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveActionSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Column").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveColumnRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ColumnSet").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveColumnSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Container").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveContainerRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"FactSet").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveFactSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Image").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveImageRenderer>(xamlBuilder).Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"ImageSet").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveImageSetRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.ChoiceSet").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveChoiceSetInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Date").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveDateInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Number").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveNumberInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Text").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveTextInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Time").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveTimeInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Input.Toggle").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveToggleInputRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Media").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveMediaRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"RichTextBlock").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveRichTextBlockRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"TextBlock").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveTextBlockRenderer>().Get()));

        return S_OK;
    }

    template<class TRegistration> HRESULT RegisterDefaultActionRenderers(TRegistration registration)
    {
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.OpenUrl").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveOpenUrlActionRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.ShowCard").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveShowCardActionRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.Submit").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveSubmitActionRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.ToggleVisibility").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveToggleVisibilityActionRenderer>().Get()));
        RETURN_IF_FAILED(registration->Set(HStringReference(L"Action.Execute").Get(),
                                           Make<AdaptiveCards::Rendering::Uwp::AdaptiveExecuteActionRenderer>().Get()));
        return S_OK;
    }
}
