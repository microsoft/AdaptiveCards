// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include <Inline.h>

class bad_string_conversion : public std::exception
{
public:
    bad_string_conversion() : _dwErr(GetLastError()) {}

private:
    DWORD _dwErr;
};

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

HRESULT GenerateSharedElement(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* items,
                              std::shared_ptr<AdaptiveCards::BaseCardElement>& containedElement);

HRESULT GenerateSharedElements(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement*>* items,
                               std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements);

HRESULT GenerateSharedAction(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action,
                             std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedAction);

HRESULT GenerateSharedActions(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement*>* items,
                              std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedElements);

HRESULT GenerateSharedRequirements(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement*>* adaptiveRequirements,
    std::unordered_map<std::string, AdaptiveCards::SemanticVersion>& sharedRequirements) noexcept;

HRESULT GenerateSharedInlines(_In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline*>* items,
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
                         ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveToggleVisibilityTarget, \
                         ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveToggleVisibilityTarget, \
                         AdaptiveToggleVisibilityTarget, \
                         AdaptiveCards::ToggleVisibilityTarget>(WINRTTOGGLEELEMENTS, SHAREDTOGGLEELEMENTS);

#define GenerateSharedImages(WINRTIMAGES, SHAREDIMAGES) \
    GenerateSharedVector<AdaptiveCards::Image, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveImage, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveImage, AdaptiveImage, AdaptiveCards::BaseCardElement>( \
        WINRTIMAGES, SHAREDIMAGES);

#define GenerateSharedFacts(WINRTFACTS, SHAREDFACTS) \
    GenerateSharedVector<AdaptiveCards::Fact, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveFact, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveFact, AdaptiveFact, AdaptiveCards::Fact>( \
        WINRTFACTS, SHAREDFACTS);

#define GenerateSharedChoices(WINRTCHOICEINPUTS, SHAREDCHOICEINPUTS) \
    GenerateSharedVector<AdaptiveCards::ChoiceInput, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceInput, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveChoiceInput, AdaptiveChoiceInput, AdaptiveCards::ChoiceInput>( \
        WINRTCHOICEINPUTS, SHAREDCHOICEINPUTS);

#define GenerateSharedMediaSources(WINRTMEDIASOURCES, SHAREDMEDIASOURCES) \
    GenerateSharedVector<AdaptiveCards::MediaSource, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMediaSource, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveMediaSource, AdaptiveMediaSource, AdaptiveCards::MediaSource>( \
        WINRTMEDIASOURCES, SHAREDMEDIASOURCES);

#define GenerateSharedColumns(WINRTCOLUMNS, SHAREDCOLUMNS) \
    GenerateSharedVector<AdaptiveCards::Column, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveColumn, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveColumn, AdaptiveColumn, AdaptiveCards::BaseCardElement>( \
        WINRTCOLUMNS, SHAREDCOLUMNS);

#define GenerateSharedTableCells(WINRTTABLECELLS, SHAREDTABLECELLS) \
    GenerateSharedVector<AdaptiveCards::TableCell, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableCell, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableCell, AdaptiveTableCell, AdaptiveCards::BaseCardElement>( \
        WINRTTABLECELLS, SHAREDTABLECELLS);

#define GenerateSharedTableRows(WINRTTABLEROWS, SHAREDTABLEROWS) \
    GenerateSharedVector<AdaptiveCards::TableRow, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableRow, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableRow, AdaptiveTableRow, AdaptiveCards::BaseCardElement>( \
        WINRTTABLEROWS, SHAREDTABLEROWS);

#define GenerateSharedTableColumnDefinitions(WINRTTABLECOLUMNS, SHAREDTABLECOLUMNS) \
    GenerateSharedVector<AdaptiveCards::TableColumnDefinition, \
                         ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableColumnDefinition, \
                         ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableColumnDefinition, \
                         AdaptiveTableColumnDefinition, \
                         AdaptiveCards::TableColumnDefinition>(WINRTTABLECOLUMNS, SHAREDTABLECOLUMNS);

HRESULT GenerateElementProjection(_In_ const std::shared_ptr<AdaptiveCards::BaseCardElement>& baseElement,
                                  _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** projectedElement) noexcept;

HRESULT GenerateContainedElementsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionsProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& actions,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement*>* projectedParentContainer) noexcept;

HRESULT GenerateActionProjection(const std::shared_ptr<AdaptiveCards::BaseActionElement>& action,
                                 _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** projectedAction) noexcept;

HRESULT GenerateInlinesProjection(
    const std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline*>* projectedParentContainer) noexcept;

HRESULT GenerateRequirementsProjection(
    const std::unordered_map<std::string, AdaptiveCards::SemanticVersion>& sharedRequirements,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement*>* projectedRequirementVector) noexcept;

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
    GenerateVectorProjection<AdaptiveCards::Image, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveImage, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveImage, AdaptiveImage>( \
        SHAREDIMAGES, WINRTIMAGES);

#define GenerateFactsProjection(SHAREDFACTS, WINRTFACTS) \
    GenerateVectorProjection<AdaptiveCards::Fact, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveFact, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveFact, AdaptiveFact>( \
        SHAREDFACTS, WINRTFACTS);

#define GenerateInputChoicesProjection(SHAREDCHOICES, WINRTCHOICES) \
    GenerateVectorProjection<AdaptiveCards::ChoiceInput, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveChoiceInput, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveChoiceInput, AdaptiveChoiceInput>( \
        SHAREDCHOICES, WINRTCHOICES);

#define GenerateMediaSourcesProjection(SHAREDMEDIASOURCES, WINRTMEDIASOURCES) \
    GenerateVectorProjection<AdaptiveCards::MediaSource, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMediaSource, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveMediaSource, AdaptiveMediaSource>( \
        SHAREDMEDIASOURCES, WINRTMEDIASOURCES);

#define GenerateColumnsProjection(SHAREDCOLUMNS, WINRTCOLUMNS) \
    GenerateVectorProjection<AdaptiveCards::Column, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveColumn, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveColumn, AdaptiveColumn>( \
        SHAREDCOLUMNS, WINRTCOLUMNS);

#define GenerateToggleTargetProjection(SHAREDTOGGLETARGETS, WINRTTOGGLETARGETS) \
    GenerateVectorProjection<AdaptiveCards::ToggleVisibilityTarget, \
                             ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveToggleVisibilityTarget, \
                             ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveToggleVisibilityTarget, \
                             AdaptiveToggleVisibilityTarget>(SHAREDTOGGLETARGETS, WINRTTOGGLETARGETS);

#define GenerateTableCellsProjection(SHAREDTABLECELLS, WINRTTABLECELLS) \
    GenerateVectorProjection<AdaptiveCards::TableCell, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableCell, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableCell, AdaptiveTableCell>( \
        SHAREDTABLECELLS, WINRTTABLECELLS);

#define GenerateTableRowsProjection(SHAREDTABLEROWS, WINRTTABLEROWS) \
    GenerateVectorProjection<AdaptiveCards::TableRow, ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableRow, ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableRow, AdaptiveTableRow>( \
        SHAREDTABLEROWS, WINRTTABLEROWS);

#define GenerateTableColumnDefinitionsProjection(SHAREDTABLECOLUMNDEFINITIONS, WINRTTABLECOLUMNDEFINITIONS) \
    GenerateVectorProjection<AdaptiveCards::TableColumnDefinition, \
                             ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTableColumnDefinition, \
                             ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveTableColumnDefinition, \
                             AdaptiveTableColumnDefinition>(SHAREDTABLECOLUMNDEFINITIONS, WINRTTABLECOLUMNDEFINITIONS);

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

void RemoteResourceElementToRemoteResourceInformationVector(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementWithRemoteResources* remoteResources,
                                                            std::vector<AdaptiveCards::RemoteResourceInformation>& resourceUris);

HRESULT SharedWarningsToAdaptiveWarnings(
    const std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& sharedWarnings,
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>* adaptiveWarnings);

HRESULT AdaptiveWarningsToSharedWarnings(
    _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>* adaptiveWarnings,
    std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& sharedWarnings);

ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType MapSharedFallbackTypeToUwp(const AdaptiveCards::FallbackType type);
AdaptiveCards::FallbackType MapUwpFallbackTypeToShared(const ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType type);

HRESULT GetAdaptiveActionParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ActionParserRegistration>& sharedActionParserRegistration,
    _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionParserRegistration** adaptiveActionParserRegistration);

HRESULT GetAdaptiveElementParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ElementParserRegistration>& sharedElementParserRegistration,
    _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementParserRegistration** adaptiveElementParserRegistration);

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
    ComPtr<IIterable<T*>> vectorIterable;
    THROW_IF_FAILED(localVector.As<IIterable<T*>>(&vectorIterable));

    Microsoft::WRL::ComPtr<IIterator<T*>> vectorIterator;
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
