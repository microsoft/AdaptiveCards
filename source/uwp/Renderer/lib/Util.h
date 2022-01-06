// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
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
#include "AdaptiveElementRendererRegistration.h"
#include "AdaptiveActionRendererRegistration.h"

class bad_string_conversion : public std::exception
{
public:
    bad_string_conversion() : _dwErr(GetLastError()) {}

private:
    DWORD _dwErr;
};

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
    winrt::IReference<TStored> m_stored;

    template<typename T> auto set(T const& t)
    {
        if constexpr (std::is_same_v<T, winrt::IReference<TStored>>)
        {
            m_stored = t;
        }
        else if constexpr (std::is_same_v<T, std::optional<T>>)
        {
            m_stored = t ? winrt::box_value(*t) : nullptr;
        }
        else if constexpr (std::is_null_pointer_v<T>)
        {
            m_stored = std::nullopt;
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

namespace rtxaml = winrt::Windows::UI::Xaml;

std::string WStringToString(std::wstring_view in);
std::wstring StringToWString(std::string_view in);

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts a std::string to an HSTRING.
winrt::hstring UTF8ToHString(std::string_view in);

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts from HSTRING to a standard std::string.
std::string HStringToUTF8(winrt::hstring const& in);

inline bool Boolify(const boolean value) noexcept
{
    return (value > 0);
}

// TODO: we don't need this, right?
template<typename T, typename TInterface, typename C>
void IterateOverVector(winrt::IVector<T> vector, C iterationCallback)
{
    for (T item : vector)
    {
        iterationCallback(item);
    }
}

template<typename T, typename C>
void IterateOverVector(winrt::IVector<T> vector, C iterationCallback)
{
    IterateOverVector<T, T, C>(vector, iterationCallback);
}

winrt::Windows::UI::Color GetColorFromString(std::string const& colorString);

// TODO: const& for enums?
winrt::Windows::UI::Color GetColorFromAdaptiveColor(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                                                    winrt::ForegroundColor adaptiveColor,
                                                    winrt::ContainerStyle containerStyle,
                                                    bool isSubtle,
                                                    bool highlight);

winrt::Windows::UI::Color GetBackgroundColorFromStyle(winrt::ContainerStyle const& style,
                                                      winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig);

winrt::Windows::UI::Color GetBorderColorFromStyle(winrt::ContainerStyle style,
                                                  winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig);

winrt::TextHighlighter
GetHighlighter(winrt::IAdaptiveTextElement const& adaptiveTextElement,
               winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderContext const& renderContext,
               winrt::AdaptiveCards::Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

winrt::hstring GetFontFamilyFromFontType(winrt::AdaptiveHostConfig const& hostConfig, winrt::FontType const& fontType);

uint32_t GetFontSizeFromFontType(winrt::AdaptiveHostConfig const& hostConfig,
                                 winrt::FontType const& fontType,
                                 winrt::TextSize const& desiredSize);

winrt::Windows::UI::Text::FontWeight GetFontWeightFromStyle(winrt::AdaptiveHostConfig const& hostConfig,
                                                            winrt::FontType const& fontType,
                                                            winrt::TextWeight const& desiredWeight);

winrt::AdaptiveFontTypeDefinition GetFontType(winrt::AdaptiveHostConfig const& hostConfig, winrt::FontType const& fontType);

uint32_t GetFontSize(winrt::AdaptiveFontSizesConfig const& sizesConfig, winrt::TextSize const& desiredSize);

uint16_t GetFontWeight(winrt::AdaptiveFontWeightsConfig const& weightsConfig, winrt::TextWeight const& desiredWeight);

uint32_t GetSpacingSizeFromSpacing(winrt::AdaptiveHostConfig const& hostConfig, winrt::Spacing const& spacing);

winrt::JsonObject StringToJsonObject(const std::string& inputString);
winrt::JsonObject HStringToJsonObject(winrt::hstring const& inputHString);
winrt::hstring JsonObjectToHString(winrt::JsonObject const& inputJson);
std::string JsonObjectToString(winrt::JsonObject const& inputJson);

// TODO: these functions live in ObjectModelUtil now if I'm correct? we don't need them here?
// HRESULT StringToJsonValue(const std::string inputString, _COM_Outptr_ ABI::winrt::IJsonValue** result);
// HRESULT HStringToJsonValue(const HSTRING& inputHString, _COM_Outptr_ ABI::winrt::IJsonValue** result);
// HRESULT JsonValueToHString(_In_ ABI::winrt::IJsonValue* inputJsonValue, _Outptr_ HSTRING* result);
// HRESULT JsonValueToString(_In_ ABI::winrt::IJsonValue* inputJsonValue, std::string& result);

// HRESULT JsonCppToJsonObject(const Json::Value& jsonCppValue, _COM_Outptr_ ABI::winrt::IJsonObject** result);
// HRESULT JsonObjectToJsonCpp(_In_ ABI::winrt::IJsonObject* jsonObject, _Out_ Json::Value* jsonCppValue);

// HRESULT ProjectedActionTypeToHString(ABI::AdaptiveCards::ObjectModel::Uwp::ElementType projectedActionType,
//                                     _Outptr_ HSTRING* result);
// HRESULT ProjectedElementTypeToHString(ABI::AdaptiveCards::ObjectModel::Uwp::ElementType projectedElementType,
//                                      _Outptr_ HSTRING* result);

bool MeetsRequirements(winrt::IAdaptiveCardElement const& cardElement, winrt::AdaptiveFeatureRegistration const& featureRegistration);

bool IsBackgroundImageValid(winrt::AdaptiveBackgroundImage backgroundImage);

// TODO: I don't see this typedef being used anywhere
// typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard*,
//                                                                                 ABI::AdaptiveCards::Rendering::Uwp::AdaptiveActionEventArgs*>>
//    ActionEventSource;
// typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard*,
//                                                                                 ABI::AdaptiveCards::Rendering::Uwp::AdaptiveMediaEventArgs*>>
//    MediaEventSource;

struct ShowCardInfo
{
    uint32_t actionSetId;
    winrt::Windows::UI::Xaml::UIElement cardUIElement{nullptr};
};


struct SeparatorParemeters
{
    winrt::Windows::UI::Color color{0};
    uint32_t spacing;
    uint32_t thickness;
};

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

winrt::Uri GetUrlFromString(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                                                 winrt::hstring const& urlString);

winrt::Windows::UI::Color GenerateLHoverColor(winrt::Windows::UI::Color const& originalColor);

winrt::DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day);

winrt::IReference<winrt::DateTime> GetDateTimeReference(unsigned int year,
                                                                                                  unsigned int month,
                                                                                                  unsigned int day);

winrt::IAdaptiveTextElement CopyTextElement(winrt::IAdaptiveTextElement const& textElement);

// TODO: rethink this perhaps?
template<typename T> inline T EnumBitwiseOR(T a, T b)
{
    return static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
}

// TODO: Helper to extract value from a ref. if will handle ref = nullptr as well.
template<typename T> inline T GetValueFromRef(winrt::IReference<T> const& ref, T defaultValue)
{
    if (ref != nullptr)
    {
        return ref.Value();
    }
    return defaultValue;
}

namespace AdaptiveCards::Rendering::Uwp
{
    struct XamlBuilder;

    // TODO: is this the correct way to do it? Should we also simply accept XamlBuilder* ?
    void RegisterDefaultElementRenderers(winrt::implementation::AdaptiveElementRendererRegistration* registration,
                                         winrt::com_ptr<XamlBuilder> xamlBuilder);

    void RegisterDefaultActionRenderers(winrt::implementation::AdaptiveActionRendererRegistration* registration);
}
