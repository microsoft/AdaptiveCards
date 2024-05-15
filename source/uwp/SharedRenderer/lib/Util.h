// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include <string>

#include <Inline.h>
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

std::string WStringToString(std::wstring_view in);
std::wstring StringToWString(std::string_view in);

std::optional<double> TryHStringToDouble(winrt::hstring const& in);

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

winrt::Windows::UI::Color GetColorFromString(std::string const& colorString);

winrt::Windows::UI::Color GetColorFromAdaptiveColor(winrt::AdaptiveHostConfig const& hostConfig,
                                                    winrt::ForegroundColor adaptiveColor,
                                                    winrt::ContainerStyle containerStyle,
                                                    bool isSubtle,
                                                    bool highlight);

winrt::Windows::UI::Color GetBackgroundColorFromStyle(winrt::ContainerStyle const& style, winrt::AdaptiveHostConfig const& hostConfig);

winrt::Windows::UI::Color GetBorderColorFromStyle(winrt::ContainerStyle style, winrt::AdaptiveHostConfig const& hostConfig);

winrt::TextHighlighter GetHighlighter(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                                      winrt::AdaptiveRenderContext const& renderContext,
                                      winrt::AdaptiveRenderArgs const& renderArgs);

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

bool MeetsRequirements(winrt::IAdaptiveCardElement const& cardElement, winrt::AdaptiveFeatureRegistration const& featureRegistration);

bool IsBackgroundImageValid(winrt::AdaptiveBackgroundImage const& backgroundImage);

struct ShowCardInfo
{
    uint32_t actionSetId;
    winrt::UIElement cardUIElement{nullptr};
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

winrt::Uri GetUrlFromString(winrt::AdaptiveHostConfig const& hostConfig, winrt::hstring const& urlString);

winrt::Windows::UI::Color GenerateLHoverColor(winrt::Windows::UI::Color const& originalColor);

winrt::DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day);

winrt::IReference<winrt::DateTime> GetDateTimeReference(unsigned int year, unsigned int month, unsigned int day);

winrt::IAdaptiveTextElement CopyTextElement(winrt::IAdaptiveTextElement const& textElement);

template<typename T> inline T EnumBitwiseOR(T a, T b)
{
    return static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
}

template<typename T> inline T GetValueFromRef(winrt::IReference<T> const& ref, T defaultValue)
{
    if (ref != nullptr)
    {
        return ref.Value();
    }
    return defaultValue;
}

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    struct XamlBuilder;

    void RegisterDefaultElementRenderers(winrt::implementation::AdaptiveElementRendererRegistration* registration,
                                         winrt::com_ptr<XamlBuilder> xamlBuilder);

    void RegisterDefaultActionRenderers(winrt::implementation::AdaptiveActionRendererRegistration* registration);
}

std::string ExtractSvgDataFromUri(winrt::Windows::Foundation::Uri const& imageUrl);

winrt::Windows::Foundation::Size ParseSizeOfSVGImageFromXmlString(winrt::hstring const& content);

winrt::IAsyncOperation<winrt::Windows::Foundation::Size> ParseSizeOfSVGImageFromStreamAsync(winrt::IRandomAccessStream const stream);

bool IsSvgImage(winrt::Windows::Foundation::Uri const& imageUrl);

auto inline GetDispatcher(winrt::ImageSource const& imageSource)
{
#ifdef USE_WINUI3
    return imageSource.DispatcherQueue();
#else
    return imageSource.Dispatcher();
#endif
}
