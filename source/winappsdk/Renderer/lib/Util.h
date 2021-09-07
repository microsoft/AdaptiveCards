// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include <wrl.h>
#include <wrl/wrappers/corewrappers.h>
#include <string>

#include "AdaptiveCards.Rendering.WinUI3.h"
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
    winrt::Windows::Foundation::IReference<TStored> m_stored;

    template<typename T> auto set(T const& t)
    {
        if constexpr (std::is_same_v<T, winrt::Windows::Foundation::IReference<TStored>>)
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

namespace rtom = winrt::AdaptiveCards::ObjectModel::WinUI3;
namespace rtrender = winrt::AdaptiveCards::Rendering::WinUI3;
namespace rtxaml = winrt::Windows::UI::Xaml;

template<typename D, typename I, typename... Args>
HRESULT MakeRt(Microsoft::WRL::ComPtr<I>& out, Args&&... args) noexcept
try
{
    out.Attach(winrt::make<D>(std::forward<Args>(args)...).as<I>().detach());
    return S_OK;
}
CATCH_RETURN();

template<typename> struct winrt_to_abi;
template<typename> struct abi_to_winrt;
#define map_rt_to_abi_(rt, abi) \
    template<> struct winrt_to_abi<winrt::rt> \
    { \
        using type = ::ABI::abi; \
    }; \
    template<> struct abi_to_winrt<ABI::abi> \
    { \
        using type = ::winrt::rt; \
    };

#define map_rt_to_abi(x) map_rt_to_abi_(x, x)

map_rt_to_abi(AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement);
map_rt_to_abi_(AdaptiveCards::ObjectModel::WinUI3::AdaptiveCard, AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard);
map_rt_to_abi_(AdaptiveCards::ObjectModel::WinUI3::AdaptiveMedia, AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia);
map_rt_to_abi_(AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionSet, AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionSet);
map_rt_to_abi_(AdaptiveCards::Rendering::WinUI3::AdaptiveActionInvoker, AdaptiveCards::Rendering::WinUI3::IAdaptiveActionInvoker);
map_rt_to_abi_(AdaptiveCards::Rendering::WinUI3::AdaptiveActionRendererRegistration,
               AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRendererRegistration);
map_rt_to_abi_(AdaptiveCards::Rendering::WinUI3::AdaptiveActionsConfig, AdaptiveCards::Rendering::WinUI3::IAdaptiveActionsConfig);
map_rt_to_abi_(AdaptiveCards::Rendering::WinUI3::AdaptiveElementRendererRegistration,
               AdaptiveCards::Rendering::WinUI3::IAdaptiveElementRendererRegistration);
map_rt_to_abi_(AdaptiveCards::Rendering::WinUI3::AdaptiveHostConfig, AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig);
map_rt_to_abi_(AdaptiveCards::Rendering::WinUI3::AdaptiveInputs, AdaptiveCards::Rendering::WinUI3::IAdaptiveInputs);
map_rt_to_abi_(AdaptiveCards::Rendering::WinUI3::AdaptiveRenderContext, AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext);
map_rt_to_abi_(Windows::Foundation::Uri, Windows::Foundation::IUriRuntimeClass);
map_rt_to_abi_(Windows::UI::Xaml::Controls::ColumnDefinition, Windows::UI::Xaml::Controls::IColumnDefinition);
map_rt_to_abi_(Windows::UI::Xaml::Controls::TextBox, Windows::UI::Xaml::Controls::ITextBox);
map_rt_to_abi_(Windows::UI::Xaml::DependencyObject, Windows::UI::Xaml::IDependencyObject);
map_rt_to_abi_(Windows::UI::Xaml::Media::Brush, Windows::UI::Xaml::Media::IBrush);
map_rt_to_abi_(Windows::UI::Xaml::ResourceDictionary, Windows::UI::Xaml::IResourceDictionary);
map_rt_to_abi_(Windows::UI::Xaml::UIElement, Windows::UI::Xaml::IUIElement);

template<typename I> auto to_winrt(I* src)
{
    return reinterpret_cast<abi_to_winrt<I>::type const&>(src);
}

template<typename I> auto to_winrt(Microsoft::WRL::ComPtr<I> const& src)
{
    return reinterpret_cast<abi_to_winrt<I>::type const&>(src);
}

inline auto to_winrt(_In_opt_ HSTRING abi)
{
    return reinterpret_cast<winrt::hstring const&>(abi);
}

inline auto to_winrt(Microsoft::WRL::Wrappers::HString const& abi)
{
    return to_winrt(abi.Get());
}

template<typename I> auto to_wrl(I const& i)
{
    return reinterpret_cast<Microsoft::WRL::ComPtr<winrt_to_abi<std::decay_t<I>>::type>&>(i);
}

template<typename I> auto to_wrl(I&& i)
{
    return reinterpret_cast<Microsoft::WRL::ComPtr<winrt_to_abi<std::decay_t<I>>::type>&>(i);
}

HRESULT WStringToHString(std::wstring_view in, _Outptr_ HSTRING* out) noexcept;

std::string WStringToString(std::wstring_view in);
std::wstring StringToWString(std::string_view in);

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts a std::string to an HSTRING.
HRESULT UTF8ToHString(std::string_view in, _Outptr_ HSTRING* out) noexcept;
winrt::hstring UTF8ToHString(std::string_view in);

// This function is needed to deal with the fact that non-windows platforms handle Unicode without the need for wchar_t.
// (which has a platform specific implementation) It converts from HSTRING to a standard std::string.
HRESULT HStringToUTF8(HSTRING in, std::string& out) noexcept;

std::string HStringToUTF8(HSTRING in);
std::string HStringToUTF8(winrt::hstring const& in);

winrt::Windows::UI::Color GetColorFromString(std::string const& colorString);

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

HRESULT GetColorFromAdaptiveColor(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::ObjectModel::WinUI3::ForegroundColor adaptiveColor,
                                  ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle containerStyle,
                                  bool isSubtle,
                                  bool highlight,
                                  _Out_ ABI::Windows::UI::Color* uiColor) noexcept;

HRESULT GetBackgroundColorFromStyle(ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle style,
                                    _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                    _Out_ ABI::Windows::UI::Color* backgroundColor) noexcept;

HRESULT GetBorderColorFromStyle(ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle style,
                                _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                _Out_ ABI::Windows::UI::Color* borderColor) noexcept;

HRESULT GetHighlighter(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* adaptiveTextElement,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderContext* renderContext,
                       _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs,
                       _Out_ ABI::Windows::UI::Xaml::Documents::ITextHighlighter** textHighlighter) noexcept;

HRESULT GetFontDataFromFontType(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::FontType fontType,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize desiredSize,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight desiredWeight,
                                _Outptr_ HSTRING* resultFontFamilyName,
                                _Out_ UINT32* resultSize,
                                _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontFamilyFromFontType(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::ObjectModel::WinUI3::FontType fontType,
                                  _Outptr_ HSTRING* resultFontFamilyName) noexcept;

HRESULT GetFontSizeFromFontType(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::FontType fontType,
                                ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize desiredSize,
                                _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeightFromStyle(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                               ABI::AdaptiveCards::ObjectModel::WinUI3::FontType fontType,
                               ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight desiredWeight,
                               _Out_ ABI::Windows::UI::Text::FontWeight* resultWeight) noexcept;

HRESULT GetFontType(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                    ABI::AdaptiveCards::ObjectModel::WinUI3::FontType fontType,
                    _COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFontTypeDefinition** styleDefinition) noexcept;

HRESULT GetFontSize(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFontSizesConfig* sizesConfig,
                    ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize desiredSize,
                    _Out_ UINT32* resultSize) noexcept;

HRESULT GetFontWeight(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFontWeightsConfig* weightsConfig,
                      ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight desiredWeight,
                      _Out_ UINT16* resultWeight) noexcept;

uint32_t GetSpacingSizeFromSpacing(rtrender::AdaptiveHostConfig const& hostConfig, rtom::Spacing const& spacing);

HRESULT GetSpacingSizeFromSpacing(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                                  ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing spacing,
                                  _Out_ UINT* spacingSize) noexcept;

HRESULT StringToJsonObject(const std::string& inputString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
HRESULT HStringToJsonObject(const HSTRING& inputHString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToHString(_In_ ABI::Windows::Data::Json::IJsonObject* inputJson, _Outptr_ HSTRING* result);
HRESULT JsonObjectToString(_In_ ABI::Windows::Data::Json::IJsonObject* inputJson, std::string& result);

winrt::Windows::Data::Json::JsonObject StringToJsonObject(const std::string& inputString);
winrt::Windows::Data::Json::JsonObject HStringToJsonObject(winrt::hstring const& inputHString);
winrt::hstring JsonObjectToHString(winrt::Windows::Data::Json::JsonObject const& inputJson);
std::string JsonObjectToString(winrt::Windows::Data::Json::JsonObject const& inputJson);

HRESULT StringToJsonValue(const std::string inputString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonValue** result);
HRESULT HStringToJsonValue(const HSTRING& inputHString, _COM_Outptr_ ABI::Windows::Data::Json::IJsonValue** result);
HRESULT JsonValueToHString(_In_ ABI::Windows::Data::Json::IJsonValue* inputJsonValue, _Outptr_ HSTRING* result);
HRESULT JsonValueToString(_In_ ABI::Windows::Data::Json::IJsonValue* inputJsonValue, std::string& result);

HRESULT JsonCppToJsonObject(const Json::Value& jsonCppValue, _COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
HRESULT JsonObjectToJsonCpp(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject, _Out_ Json::Value* jsonCppValue);

HRESULT ProjectedActionTypeToHString(ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType projectedActionType,
                                     _Outptr_ HSTRING* result);
HRESULT ProjectedElementTypeToHString(ABI::AdaptiveCards::ObjectModel::WinUI3::ElementType projectedElementType,
                                      _Outptr_ HSTRING* result);

HRESULT MeetsRequirements(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement* cardElement,
                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFeatureRegistration* featureRegistration,
                          _Out_ bool* meetsRequirements);

HRESULT IsBackgroundImageValid(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveBackgroundImage* backgroundImageElement,
                               _Out_ BOOL* isValid);

typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard*,
                                                                                 ABI::AdaptiveCards::Rendering::WinUI3::AdaptiveActionEventArgs*>>
    ActionEventSource;
typedef Microsoft::WRL::EventSource<ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard*,
                                                                                 ABI::AdaptiveCards::Rendering::WinUI3::AdaptiveMediaEventArgs*>>
    MediaEventSource;

struct ShowCardInfo
{
    uint32_t actionSetId;
    winrt::Windows::UI::Xaml::UIElement buttonUIElement{nullptr};
    winrt::Windows::UI::Xaml::UIElement overflowUIElement{nullptr};
    winrt::Windows::UI::Xaml::UIElement cardUIElement{nullptr};
    uint32_t primaryButtonIndex;
};

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

void GetUrlFromString(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig,
                      _In_ HSTRING urlString,
                      _Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** url);

ABI::Windows::UI::Color GenerateLHoverColor(const ABI::Windows::UI::Color& originalColor);

ABI::Windows::Foundation::DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day);

HRESULT GetDateTimeReference(unsigned int year,
                             unsigned int month,
                             unsigned int day,
                             _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::DateTime>** dateTimeReference);

HRESULT CopyTextElement(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement* textElement,
                        _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveTextElement** copiedTextElement);

namespace AdaptiveCards::Rendering::WinUI3
{
    struct XamlBuilder;

    void RegisterDefaultElementRenderers(rtrender::implementation::AdaptiveElementRendererRegistration* registration,
                                         XamlBuilder* xamlBuilder);

    void RegisterDefaultActionRenderers(rtrender::implementation::AdaptiveActionRendererRegistration* registration);
}
