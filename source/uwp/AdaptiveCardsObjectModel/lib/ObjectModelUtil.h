// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include <Inline.h>

template<typename TStored> struct property
{
    TStored m_stored;

    template<typename T> void operator()(T&& t) { m_stored = std::forward<T>(t); }
    TStored operator()() { return m_stored; }

    template<typename T> void operator=(T&& t) { m_stored = std::forward<T>(t); }
    operator TStored() { return m_stored; }

    TStored const& get() const { return m_stored; }
    auto operator->() { return std::addressof(m_stored); }
};

template<typename T, typename Q> std::optional<T> opt_cast(std::optional<Q> const& src)
{
    if (src.has_value())
    {
        return static_cast<T>(src.value());
    }
    else
    {
        return std::nullopt;
    }
}

template<typename TStored> struct property_opt
{
    winrt::Windows::Foundation::IReference<TStored> m_stored;

    template<typename T> auto set(T const& t)
    {
        if constexpr (std::is_same_v<T, winrt::Windows::Foundation::IReference<TStored>>)
        {
            m_stored = t;
        }
        else if constexpr (std::is_same_v<T, std::optional<TStored>>)
        {
            m_stored = t.has_value() ? winrt::box_value(t.value()).as<winrt::Windows::Foundation::IReference<TStored>>() : nullptr;
        }
        else if constexpr (std::is_null_pointer_v<T>)
        {
            m_stored = nullptr;
        }
        else
        {
            static_assert("unsupported");
        }

        return *this;
    }

    template<typename TOther = TStored> std::optional<TOther> get()
    {
        if constexpr (std::is_same_v<TOther, TStored>)
        {
            return m_stored.try_as<TStored>();
        }
        else
        {
            return opt_cast<TOther>(m_stored.try_as<TStored>());
        }
    };

    // C++/WinRT adapters
    auto operator()() { return m_stored; }
    template<typename T> auto operator()(T&& t) { return set(std::forward<T>(t)); }

    // Assignment helper
    template<typename T> auto operator=(T&& t) { return set(std::forward<T>(t)); }

    // Casting helpers "do you have a value" and "cast to your optional type"
    operator bool() const { return static_cast<bool>(m_stored); }
    operator std::optional<TStored>() { return get(); }
};

std::string WStringToString(std::wstring_view in);
std::wstring StringToWString(std::string_view in);

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts a std::string to an HSTRING.
winrt::hstring UTF8ToHString(std::string_view in);

std::string HStringToUTF8(winrt::hstring const& in);

std::shared_ptr<AdaptiveCards::BaseCardElement> GenerateSharedElement(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement const& item);

std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>> GenerateSharedElements(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement> const& items);

std::shared_ptr<AdaptiveCards::BaseActionElement>
GenerateSharedAction(winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& action);

std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>> GenerateSharedActions(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> const& actions);

std::unordered_map<std::string, AdaptiveCards::SemanticVersion> GenerateSharedRequirements(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement> const& adaptiveRequirements);

std::vector<std::shared_ptr<AdaptiveCards::Inline>> GenerateSharedInlines(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline> const& inlines);

winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement
GenerateElementProjection(const std::shared_ptr<AdaptiveCards::BaseCardElement>& baseElement);

template<typename TImpl, typename TShared, typename TCollection>
std::vector<std::shared_ptr<TShared>> GenerateSharedVector(TCollection const& cells)
{
    std::vector<std::shared_ptr<TShared>> shared;
    for (auto&& c : cells)
    {
        if (auto adaptive = peek_innards<TImpl>(c))
        {
            shared.emplace_back(std::dynamic_pointer_cast<TShared>(adaptive->GetSharedModel()));
        }
        else
        {
            throw winrt::hresult_invalid_argument();
        }
    }
    return shared;
}

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement>
GenerateContainedElementsProjection(const std::vector<std::shared_ptr<AdaptiveCards::BaseCardElement>>& containedElements);

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement>
GenerateActionsProjection(const std::vector<std::shared_ptr<AdaptiveCards::BaseActionElement>>& containedActions);

winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement
GenerateActionProjection(const std::shared_ptr<AdaptiveCards::BaseActionElement>& action);

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline>
GenerateInlinesProjection(const std::vector<std::shared_ptr<AdaptiveCards::Inline>>& containedElements);

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement>
GenerateRequirementsProjection(const std::unordered_map<std::string, AdaptiveCards::SemanticVersion>& sharedRequirements);

template<typename TRtTypeImpl, typename TSharedType, typename TRtType = typename TRtTypeImpl::class_type>
auto GenerateVectorProjection(std::vector<std::shared_ptr<TSharedType>> const& elements)
{
    std::vector<TRtType> converted;
    for (auto&& e : elements)
    {
        converted.emplace_back(winrt::make<TRtTypeImpl>(e));
    }
    return winrt::single_threaded_vector<TRtType>(std::move(converted));
}

winrt::Windows::Data::Json::JsonObject StringToJsonObject(const std::string& inputString);
winrt::Windows::Data::Json::JsonObject HStringToJsonObject(winrt::hstring const& inputHString);
winrt::hstring JsonObjectToHString(winrt::Windows::Data::Json::IJsonObject const& inputJson);

std::string JsonObjectToString(winrt::Windows::Data::Json::IJsonObject const& inputJson);

winrt::Windows::Data::Json::JsonValue StringToJsonValue(const std::string& inputString);
winrt::Windows::Data::Json::JsonValue HStringToJsonValue(winrt::hstring const& inputHString);
std::string JsonValueToString(winrt::Windows::Data::Json::IJsonValue const& inputValue);
winrt::hstring JsonValueToHString(winrt::Windows::Data::Json::IJsonValue const& inputJsonValue);

winrt::Windows::Data::Json::JsonObject JsonCppToJsonObject(const Json::Value& jsonCppValue);

Json::Value JsonObjectToJsonCpp(winrt::Windows::Data::Json::IJsonObject const& jsonObject);

void RemoteResourceElementToRemoteResourceInformationVector(
    winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementWithRemoteResources const& remoteResourceElement,
    std::vector<::AdaptiveCards::RemoteResourceInformation>& resourceUris);

// Peek interface to help get implementation types from winrt interfaces
struct DECLSPEC_UUID("defc7d5f-b4e5-4a74-80be-d87bd50a2f45") ITypePeek : IInspectable
{
    virtual void* PeekAt(REFIID riid) = 0;
    template<typename Q> void* PeekHelper(REFIID riid, Q* pQ) { return (__uuidof(Q) == riid) ? pQ : nullptr; }

protected:
    virtual ~ITypePeek() {}
};

template<typename D, typename I> winrt::com_ptr<D> peek_innards(I&& o)
{
    winrt::com_ptr<D> out;
    if (auto p = o.try_as<ITypePeek>())
    {
        if (p->PeekAt(__uuidof(D)))
        {
            out.copy_from(winrt::get_self<D>(o));
        }
    }

    return out;
}

void SharedWarningsToAdaptiveWarnings(
    const std::vector<std::shared_ptr<::AdaptiveCards::AdaptiveCardParseWarning>>& sharedWarnings,
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& toAddTo);

winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning>
SharedWarningsToAdaptiveWarnings(const std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& sharedWarnings);

void AdaptiveWarningsToSharedWarnings(
    winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& adaptiveWarnings,
    std::vector<std::shared_ptr<AdaptiveCards::AdaptiveCardParseWarning>>& sharedWarnings);

winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType MapSharedFallbackTypeToUwp(const AdaptiveCards::FallbackType type);

AdaptiveCards::FallbackType MapUwpFallbackTypeToShared(winrt::AdaptiveCards::ObjectModel::Uwp::FallbackType const& type);

winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration GetAdaptiveActionParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ActionParserRegistration>& sharedActionParserRegistration);

winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration GetAdaptiveElementParserRegistrationFromSharedModel(
    const std::shared_ptr<AdaptiveCards::ElementParserRegistration>& sharedElementParserRegistration);
