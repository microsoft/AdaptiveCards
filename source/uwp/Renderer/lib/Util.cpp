// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include <regex>

#include "XamlHelpers.h"
#include "AdaptiveActionSetRenderer.h"
#include "AdaptiveColumnRenderer.h"
#include "AdaptiveColumnSetRenderer.h"
#include "AdaptiveContainerRenderer.h"
#include "AdaptiveFactSetRenderer.h"
#include "AdaptiveImageRenderer.h"
#include "AdaptiveImageSetRenderer.h"
#include "AdaptiveChoiceSetInputRenderer.h"
#include "AdaptiveDateInputRenderer.h"
#include "AdaptiveNumberInputRenderer.h"
#include "AdaptiveTextInputRenderer.h"
#include "AdaptiveTimeInputRenderer.h"
#include "AdaptiveToggleInputRenderer.h"
#include "AdaptiveMediaRenderer.h"
#include "AdaptiveRichTextBlockRenderer.h"
#include "AdaptiveTableRenderer.h"
#include "AdaptiveTextBlockRenderer.h"

#include "AdaptiveOpenUrlActionRenderer.h"
#include "AdaptiveShowCardActionRenderer.h"
#include "AdaptiveSubmitActionRenderer.h"
#include "AdaptiveToggleVisibilityActionRenderer.h"
#include "AdaptiveExecuteActionRenderer.h"

using namespace AdaptiveCards;
using namespace AdaptiveCards::Rendering::Uwp;


std::string WStringToString(std::wstring_view in)
{
    const int length_in = static_cast<int>(in.length());

    if (length_in > 0)
    {
        const int length_out = ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, in.data(), length_in, NULL, 0, NULL, NULL);

        if (length_out > 0)
        {
            std::string out(length_out, '\0');

            const int length_written =
                ::WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, in.data(), length_in, out.data(), length_out, NULL, NULL);

            if (length_written == length_out)
            {
                return out;
            }
        }

        throw bad_string_conversion();
    }

    return {};
}

std::wstring StringToWString(std::string_view in)
{
    const int length_in = static_cast<int>(in.length());

    if (length_in > 0)
    {
        const int length_out = ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, in.data(), length_in, NULL, 0);

        if (length_out > 0)
        {
            std::wstring out(length_out, L'\0');

            const int length_written =
                ::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, in.data(), length_in, out.data(), length_out);

            if (length_written == length_out)
            {
                return out;
            }
        }

        throw bad_string_conversion();
    }

    return {};
}

winrt::hstring UTF8ToHString(std::string_view in)
{
    return winrt::hstring{StringToWString(in)};
}

std::string HStringToUTF8(winrt::hstring const& in)
{
    return WStringToString(in);
}

// Get a Color object from color string
// Expected formats are "#AARRGGBB" (with alpha channel) and "#RRGGBB" (without alpha channel)
// TODO: do we want to keep try/catch here?
winrt::Windows::UI::Color GetColorFromString(const std::string& colorString)
{
    winrt::Windows::UI::Color color{};
    if (colorString.length() > 0 && colorString.front() == '#')
    {
        // Get the pure hex value (without #)
        std::string hexColorString = colorString.substr(1, std::string::npos);

        std::regex colorWithAlphaRegex("[0-9a-f]{8}", std::regex_constants::icase);
        if (regex_match(hexColorString, colorWithAlphaRegex))
        {
            // If color string has alpha channel, extract and set to color
            std::string alphaString = hexColorString.substr(0, 2);
            // TODO: instead of INT32, can we just put int or long?
            INT32 alpha = strtol(alphaString.c_str(), nullptr, 16);

            color.A = static_cast<BYTE>(alpha);

            hexColorString = hexColorString.substr(2, std::string::npos);
        }
        else
        {
            // Otherwise, set full opacity
            std::string alphaString = "FF";
            INT32 alpha = strtol(alphaString.c_str(), nullptr, 16);
            color.A = static_cast<BYTE>(alpha);
        }

        // A valid string at this point should have 6 hex characters (RRGGBB)
        std::regex colorWithoutAlphaRegex("[0-9a-f]{6}", std::regex_constants::icase);
        if (regex_match(hexColorString, colorWithoutAlphaRegex))
        {
            // Then set all other Red, Green, and Blue channels
            std::string redString = hexColorString.substr(0, 2);
            INT32 red = strtol(redString.c_str(), nullptr, 16);

            std::string greenString = hexColorString.substr(2, 2);
            INT32 green = strtol(greenString.c_str(), nullptr, 16);

            std::string blueString = hexColorString.substr(4, 2);
            INT32 blue = strtol(blueString.c_str(), nullptr, 16);

            color.R = static_cast<BYTE>(red);
            color.G = static_cast<BYTE>(green);
            color.B = static_cast<BYTE>(blue);

            return color;
        }
    }

    // All other formats are ignored (set alpha to 0)
    color.A = static_cast<BYTE>(0);

    return color;
}

rtrender::AdaptiveContainerStyleDefinition GetContainerStyleDefinition(rtom::ContainerStyle const& style,
                                                                       rtrender::AdaptiveHostConfig const& hostConfig)
{
    /*ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStylesDefinition> containerStyles;
    RETURN_IF_FAILED(hostConfig->get_ContainerStyles(&containerStyles));*/
    auto containerStyles = hostConfig.ContainerStyles();

    switch (style)
    {
    case rtom::ContainerStyle::Accent:
        return containerStyles.Accent();
    case rtom::ContainerStyle::Attention:
        return containerStyles.Attention();
    case rtom::ContainerStyle::Emphasis:
        return containerStyles.Emphasis();
    case rtom::ContainerStyle::Good:
        return containerStyles.Good();
    case rtom::ContainerStyle::Warning:
        return containerStyles.Warning();
    case rtom::ContainerStyle::Default:
    default:
        return containerStyles.Default();
    }
}
winrt::Windows::UI::Color GetColorFromAdaptiveColor(winrt::AdaptiveCards::Rendering::Uwp::AdaptiveHostConfig const& hostConfig,
                                                    winrt::AdaptiveCards::ObjectModel::Uwp::ForegroundColor adaptiveColor,
                                                    winrt::AdaptiveCards::ObjectModel::Uwp::ContainerStyle containerStyle,
                                                    bool isSubtle,
                                                    bool highlight)
{
    auto styleDefinition = GetContainerStyleDefinition(containerStyle, hostConfig);

    auto colorsConfig = styleDefinition.ForegroundColors();

    rtrender::AdaptiveColorConfig colorConfig{};
    switch (adaptiveColor)
    {
    case rtom::ForegroundColor::Accent:
        colorConfig = colorsConfig.Accent();
        break;
    case rtom::ForegroundColor::Dark:
        colorConfig = colorsConfig.Dark();
        break;
    case rtom::ForegroundColor::Light:
        colorConfig = colorsConfig.Light();
        break;
    case rtom::ForegroundColor::Good:
        colorConfig = colorsConfig.Good();
        break;
    case rtom::ForegroundColor::Warning:
        colorConfig = colorsConfig.Warning();
        break;
    case rtom::ForegroundColor::Attention:
        colorConfig = colorsConfig.Attention();
        break;
    case rtom::ForegroundColor::Default:
    default:
        colorConfig = colorsConfig.Default();
        break;
    }

    if (highlight)
    {
        auto highlightColorConfig = colorConfig.HighlightColors();
        return isSubtle ? highlightColorConfig.Subtle() : highlightColorConfig.Default();
    }
    else
    {
        return isSubtle ? colorConfig.Subtle() : colorConfig.Default();
    }
}

rtxaml::Documents::TextHighlighter GetHighlighter(rtom::IAdaptiveTextElement const& adaptiveTextElement,
                                                  rtrender::AdaptiveRenderContext const& renderContext,
                                                  rtrender::AdaptiveRenderArgs const& renderArgs)
{
    rtxaml::Documents::TextHighlighter textHighlighter{};

    auto hostConfig = renderContext.HostConfig();

    /* auto adaptiveForegroundColorRef = adaptiveTextElement.Color();*/

    // TODO: do we need to do it? Won't it default to 'Default' by default?
    // TODO: should I create a helper to extract a value from refs? GetValueFromRef(... const& ref, ... defaultValue); ?
    rtom::ForegroundColor adaptiveForegroundColor = GetValueFromRef(adaptiveTextElement.Color(), rtom::ForegroundColor::Default);
    bool isSubtle = GetValueFromRef(adaptiveTextElement.IsSubtle(), false);

    auto containerStyle = renderArgs.ContainerStyle();

    auto backgroundColor = GetColorFromAdaptiveColor(hostConfig, adaptiveForegroundColor, containerStyle, isSubtle, true);
    auto foregroundColor = GetColorFromAdaptiveColor(hostConfig, adaptiveForegroundColor, containerStyle, isSubtle, false);

    textHighlighter.Background(::AdaptiveCards::Rendering::Uwp::XamlHelpers::GetSolidColorBrush(backgroundColor));
    textHighlighter.Foreground(::AdaptiveCards::Rendering::Uwp::XamlHelpers::GetSolidColorBrush(foregroundColor));

    return textHighlighter;
}

// TODO: do we want try/catch here?
uint32_t GetSpacingSizeFromSpacing(rtrender::AdaptiveHostConfig const& hostConfig, rtom::Spacing const& spacing)
{
    auto spacingConfig = hostConfig.Spacing();

    switch (spacing)
    {
    case winrt::AdaptiveCards::ObjectModel::Uwp::Spacing::None:
        return 0;
    case winrt::AdaptiveCards::ObjectModel::Uwp::Spacing::Small:
        return spacingConfig.Small();
    case winrt::AdaptiveCards::ObjectModel::Uwp::Spacing::Medium:
        return spacingConfig.Medium();
    case winrt::AdaptiveCards::ObjectModel::Uwp::Spacing::Large:
        return spacingConfig.Large();
    case winrt::AdaptiveCards::ObjectModel::Uwp::Spacing::ExtraLarge:
        return spacingConfig.ExtraLarge();
    case winrt::AdaptiveCards::ObjectModel::Uwp::Spacing::Padding:
        return spacingConfig.Padding();
    case winrt::AdaptiveCards::ObjectModel::Uwp::Spacing::Default:
    default:
        return spacingConfig.Default();
    }
}

winrt::Windows::UI::Color GetBackgroundColorFromStyle(rtom::ContainerStyle const& style, rtrender::AdaptiveHostConfig const& hostConfig)
{
    // TODO: how do I handle errors here? are there gonna be any?
    auto styleDefinition = GetContainerStyleDefinition(style, hostConfig);
    return styleDefinition.BackgroundColor();
}

winrt::Windows::UI::Color GetBorderColorFromStyle(rtom::ContainerStyle style, rtrender::AdaptiveHostConfig const& hostConfig)

{
    // TODO: how do I handle error here?
    // TODO: what if this styleDef nullptr? check for that, see above the method from WRL (try/catch)
    auto styleDefinition = GetContainerStyleDefinition(style, hostConfig);
    return styleDefinition.BorderColor();
}


// TODO: do we want try/catch here?
winrt::hstring GetFontFamilyFromFontType(rtrender::AdaptiveHostConfig const& hostConfig, rtom::FontType const& fontType)
{
    try
    {
        // Get FontFamily from desired style
        // TODO: rename the function to GetFontTypeDefinition(..)?
        auto typeDefinition = GetFontType(hostConfig, fontType);
        auto fontFamily = typeDefinition.FontFamily();
        if (fontFamily.empty())
        {
            if (fontType == rtom::FontType::Monospace)
            {
                // fallback to system default monospace FontFamily
                fontFamily = UTF8ToHString("Courier New");
            }
            else
            {
                // fallback to deprecated FontFamily
                /* RETURN_IF_FAILED(hostConfig->get_FontFamily(result.GetAddressOf()));*/
                fontFamily = hostConfig.FontFamily();
                if (fontFamily.empty())
                {
                    // fallback to system default FontFamily
                    /*RETURN_IF_FAILED(UTF8ToHString("Segoe UI", result.GetAddressOf()));*/
                    fontFamily = UTF8ToHString("Segoe UI");
                }
            }
        }
        return fontFamily;
    }
    catch (winrt::hresult_error const& ex)
    {
        // TODO: what do we do here?
        return L"";
    }
}


uint32_t GetFontSizeFromFontType(rtrender::AdaptiveHostConfig const& hostConfig, rtom::FontType const& fontType, rtom::TextSize const& desiredSize)
{
    try
    {
        rtrender::AdaptiveFontTypeDefinition fontTypeDefinition = GetFontType(hostConfig, fontType);
        rtrender::AdaptiveFontSizesConfig sizesConfig = fontTypeDefinition.FontSizes();
        uint32_t result = GetFontSize(sizesConfig, desiredSize);

        // TODO: can we still use MAXUINT32?
        if (result == MAXUINT32)
        {
            // Get FontSize from Default style
            fontTypeDefinition = GetFontType(hostConfig, rtom::FontType::Default);
            sizesConfig = fontTypeDefinition.FontSizes();
            result = GetFontSize(sizesConfig, desiredSize);

            if (result == MAXUINT32)
            {
                // get deprecated FontSize
                sizesConfig = hostConfig.FontSizes();
                result = GetFontSize(sizesConfig, desiredSize);

                if (result == MAXUINT32)
                {
                    // set system default FontSize based on desired style
                    switch (desiredSize)
                    {
                    case rtom::TextSize::Small:
                        return 10;
                        break;
                    case rtom::TextSize::Medium:
                        return 14;
                        break;
                    case rtom::TextSize::Large:
                        return 17;
                        break;
                    case rtom::TextSize::ExtraLarge:
                        return 20;
                        break;
                    case rtom::TextSize::Default:
                    default:
                        return 12;
                        break;
                    }
                }
            }
        }
    }
    catch (winrt::hresult_error const& ex)
    {
        // TODO: what do we do here?
        return 0;
    }
}

winrt::Windows::UI::Text::FontWeight GetFontWeightFromStyle(rtrender::AdaptiveHostConfig const& hostConfig,
                                                            rtom::FontType const& fontType,
                                                            rtom::TextWeight const& desiredWeight)
{
    try
    {
        rtrender::AdaptiveFontTypeDefinition fontTypeDefinition = GetFontType(hostConfig, fontType);
        rtrender::AdaptiveFontWeightsConfig weightConfig = fontTypeDefinition.FontWeights();
        uint16_t result = GetFontWeight(weightConfig, desiredWeight);

        if (result == MAXUINT16)
        {
            // get FontWeight from Default style
            rtrender::AdaptiveFontTypeDefinition fontTypeDefinition = GetFontType(hostConfig, rtom::FontType::Default);
            rtrender::AdaptiveFontWeightsConfig weightConfig = fontTypeDefinition.FontWeights();
            result = GetFontWeight(weightConfig, desiredWeight);

            if (result == MAXUINT16)
            {
                // get deprecated FontWeight
                weightConfig = hostConfig.FontWeights();
                result = GetFontWeight(weightConfig, desiredWeight);

                if (result == MAXUINT16)
                {
                    // set system default FontWeight based on desired style
                    switch (desiredWeight)
                    {
                    case rtom::TextWeight::Lighter:
                        result = 200;
                        break;
                    case rtom::TextWeight::Bolder:
                        result = 800;
                        break;
                    case rtom::TextWeight::Default:
                    default:
                        result = 400;
                        break;
                    }
                }
            }
        }
        return {result};
    }
    catch (winrt::hresult_error const& ex)
    {
        // TODO: what do we do here? return default?
        return {400};
    }
}

rtrender::AdaptiveFontTypeDefinition GetFontType(rtrender::AdaptiveHostConfig const& hostConfig, rtom::FontType const& fontType)
{
    try
    {
        auto fontTypes = hostConfig.FontTypes();
        switch (fontType)
        {
        case rtom::FontType::Monospace:
            return fontTypes.Monospace();
            break;
        case rtom::FontType::Default:
        default:
            return fontTypes.Default();
            break;
        }
    }
    catch (winrt::hresult_error const& ex)
    {
        // TODO: what do we do here?
        return nullptr;
    }
}

uint32_t GetFontSize(rtrender::AdaptiveFontSizesConfig const& sizesConfig, rtom::TextSize const& desiredSize)
{
    try
    {
        switch (desiredSize)
        {
        case rtom::TextSize::Small:
            return sizesConfig.Small();
            break;
        case rtom::TextSize::Medium:
            return sizesConfig.Medium();
            break;
        case rtom::TextSize::Large:
            return sizesConfig.Large();
            break;
        case rtom::TextSize::ExtraLarge:
            return sizesConfig.ExtraLarge();
            break;
        case rtom::TextSize::Default:
        default:
            return sizesConfig.Default();
            break;
        }
    }
    catch (winrt::hresult_error const& ex)
    {
        // TODO: what do we do here? Return default?
        return sizesConfig.Default();
    }
}

uint16_t GetFontWeight(rtrender::AdaptiveFontWeightsConfig const& weightsConfig, rtom::TextWeight const& desiredWeight)
{
    try
    {
		// TODO: we have a lot of functions like this. Can we have a MAP of values?
		// TODO: so we don't have to do if/else all the time?
        switch (desiredWeight)
        {
        case rtom::TextWeight::Lighter:
            return weightsConfig.Lighter();
            break;
        case rtom::TextWeight::Bolder:
            return weightsConfig.Bolder();
            break;
        case rtom::TextWeight::Default:
        default:
            return weightsConfig.Default();
            break;
        }
    }
    catch (winrt::hresult_error const& ex)
    {
        // TODO: what do we do here? Return default?
        return weightsConfig.Default();
    }
}

winrt::Windows::Data::Json::JsonObject StringToJsonObject(const std::string& inputString)
{
    return HStringToJsonObject(UTF8ToHString(inputString));
}

winrt::Windows::Data::Json::JsonObject HStringToJsonObject(winrt::hstring const& inputHString)
{
    winrt::Windows::Data::Json::JsonObject obj{nullptr};

    if (!winrt::Windows::Data::Json::JsonObject::TryParse(inputHString, obj))
    {
        obj = {};
    }

    return obj;
}

std::string JsonObjectToString(winrt::Windows::Data::Json::JsonObject const& inputJson)
{
    return HStringToUTF8(JsonObjectToHString(inputJson));
}

winrt::hstring JsonObjectToHString(winrt::Windows::Data::Json::JsonObject const& inputJson)
{
	// TODO: do we want to check for null here?
    return inputJson.Stringify();
}

// TODO: these functions live in ObjectModelUtil now if I'm correct? we don't need them here?
// HRESULT StringToJsonValue(const std::string inputString, _COM_Outptr_ IJsonValue** result)
// {
//     HString asHstring;
//     RETURN_IF_FAILED(UTF8ToHString(inputString, asHstring.GetAddressOf()));
//     return HStringToJsonValue(asHstring.Get(), result);
// }

// HRESULT HStringToJsonValue(const HSTRING& inputHString, _COM_Outptr_ IJsonValue** result)
// {
//     ComPtr<IJsonValueStatics> jValueStatics;
//     RETURN_IF_FAILED(GetActivationFactory(HStringReference(RuntimeClass_Windows_Data_Json_JsonValue).Get(), &jValueStatics));
//     ComPtr<IJsonValue> jValue;
//     HRESULT hr = jValueStatics->Parse(inputHString, &jValue);
//     if (FAILED(hr))
//     {
//         RETURN_IF_FAILED(ActivateInstance(HStringReference(RuntimeClass_Windows_Data_Json_JsonValue).Get(), &jValue));
//     }
//     *result = jValue.Detach();
//     return S_OK;
// }

// HRESULT JsonValueToString(_In_ IJsonValue* inputValue, std::string& result)
// {
//     HString asHstring;
//     RETURN_IF_FAILED(JsonValueToHString(inputValue, asHstring.GetAddressOf()));
//     return HStringToUTF8(asHstring.Get(), result);
// }

// HRESULT JsonValueToHString(_In_ IJsonValue* inputJsonValue, _Outptr_ HSTRING* result)
// {
//     if (!inputJsonValue)
//     {
//         return E_INVALIDARG;
//     }
//     ComPtr<IJsonValue> localInputJsonValue(inputJsonValue);
//     return (localInputJsonValue->Stringify(result));ProjectedActionTypeToHString
// }

// HRESULT JsonCppToJsonObject(const Json::Value& jsonCppValue, _COM_Outptr_ IJsonObject** result)
// {
//     std::string jsonString = ParseUtil::JsonToString(jsonCppValue);
//     return StringToJsonObject(jsonString, result);
// }

// HRESULT JsonObjectToJsonCpp(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject, _Out_ Json::Value* jsonCppValue)
// {
//     std::string jsonString;
//     RETURN_IF_FAILED(JsonObjectToString(jsonObject, jsonString));

//     *jsonCppValue = ParseUtil::GetJsonValueFromString(jsonString);

//     return S_OK;
// }

// HRESULT ProjectedActionTypeToHString(ABI::AdaptiveCards::ObjectModel::Uwp::ElementType projectedActionType, _Outptr_ HSTRING* result)
// {
//     ActionType sharedActionType = static_cast<ActionType>(projectedActionType);
//     return UTF8ToHString(ActionTypeToString(sharedActionType), result);
// }

// HRESULT ProjectedElementTypeToHString(ABI::AdaptiveCards::ObjectModel::Uwp::ElementType projectedElementType, _Outptr_ HSTRING* result)
// {
//     CardElementType sharedElementType = static_cast<CardElementType>(projectedElementType);
//     return UTF8ToHString(CardElementTypeToString(sharedElementType), result);
//}

bool MeetsRequirements(rtom::IAdaptiveCardElement const& cardElement, rtrender::AdaptiveFeatureRegistration const& featureRegistration)
{
    winrt::Windows::Foundation::Collections::IVector<rtom::AdaptiveRequirement> requirements = cardElement.Requirements();
    bool meetsRequirementsLocal = true;

    for (auto req : requirements)
    {
        // winrt::hstring name = req.Name();
        winrt::hstring registrationVersion = featureRegistration.Get(req.Name());

        if (registrationVersion.empty())
        {
            meetsRequirementsLocal = false;
        }
        else
        {
            std::string requirementVersionString = HStringToUTF8(req.Version());
            if (requirementVersionString != "*")
            {
                SemanticVersion requirementSemanticVersion(requirementVersionString);
                SemanticVersion registrationSemanticVersion(HStringToUTF8(registrationVersion));
                if (registrationSemanticVersion < requirementSemanticVersion)
                {
                    meetsRequirementsLocal = false;
                }
            }
        }
    }

    return meetsRequirementsLocal;
}

bool IsBackgroundImageValid(rtom::AdaptiveBackgroundImage backgroundImage)
{
    // TODO: is this correct here? the logic?
    if (backgroundImage != nullptr)
    {
        // TODO: is this a proper check? instead of HString.isValid()?
        return !backgroundImage.Url().empty();
    }
    return false;
}


winrt::Windows::Foundation::Uri GetUrlFromString(rtrender::AdaptiveHostConfig const& hostConfig, winrt::hstring const& urlString)
{
    winrt::Windows::Foundation::Uri uri{nullptr};

    // TODO: We can also use the factory, but we don't need to, right? This will try to make absolute uri?
    if (const auto uriFromAbsoluteUri = winrt::Windows::Foundation::Uri{urlString})
    {
        return uriFromAbsoluteUri;
    }
    else
    {
        winrt::hstring imageBaseUrl = hostConfig.ImageBaseUrl();

        if (const auto uriFromRelativeUri = winrt::Windows::Foundation::Uri{imageBaseUrl, urlString})
        {
            return uriFromRelativeUri;
        }
    }
    return nullptr;
}

winrt::Windows::UI::Color GenerateLHoverColor(winrt::Windows::UI::Color const& originalColor)
{
    const double hoverIncrement = 0.25;

    winrt::Windows::UI::Color hoverColor;
    hoverColor.A = originalColor.A;
    hoverColor.R = originalColor.R - static_cast<BYTE>(originalColor.R * hoverIncrement);
    hoverColor.G = originalColor.G - static_cast<BYTE>(originalColor.G * hoverIncrement);
    hoverColor.B = originalColor.B - static_cast<BYTE>(originalColor.B * hoverIncrement);
    return hoverColor;
}

winrt::Windows::Foundation::DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day)
{
    // TODO: investigate the midnight bug. If the timezone will be ahead of UTC we can do -1 day when converting
    SYSTEMTIME systemTime = {(WORD)year, (WORD)month, 0, (WORD)day};

    // Convert to UTC
    TIME_ZONE_INFORMATION timeZone;
    GetTimeZoneInformation(&timeZone);
    TzSpecificLocalTimeToSystemTime(&timeZone, &systemTime, &systemTime);

    // Convert to ticks
    FILETIME fileTime;
    SystemTimeToFileTime(&systemTime, &fileTime);
    // DateTime dateTime{(INT64)fileTime.dwLowDateTime + (((INT64)fileTime.dwHighDateTime) << 32)};

    // TODO: should we just get it from fileTime instead of from .UniversalTime?
    // winrt::clock::from_FILETIME(fileTime);
    // return winrt::clock::from_FILETIME(winrt::file_time{dateTime.UniversalTime});
    // TODO: I can remove curly bracket, c++ will call the apropriate constructor anyway. This feels nicer tho :)
    return winrt::clock::from_FILETIME({fileTime});
}

winrt::Windows::Foundation::IReference<winrt::Windows::Foundation::DateTime> GetDateTimeReference(unsigned int year,
                                                                                                  unsigned int month,
                                                                                                  unsigned int day)
{
	// TODO: default constructor for reference will be invoked, right?
    return GetDateTime(year, month, day);
}


rtom::IAdaptiveTextElement CopyTextElement(rtom::IAdaptiveTextElement const& textElement)
{
    if (textElement != nullptr)
    {
        rtom::AdaptiveTextRun textRun;

        // TODO: is this the right way to do it? Or do we need to .Value()?
		// TODO: does IReference has copy constructor that will extract .Value() and copy it? (at least for primitifves)?
        textRun.Color(textElement.Color());
        textRun.FontType(textElement.FontType());
        textRun.IsSubtle(textElement.IsSubtle());
        textRun.Language(textElement.Language());
        textRun.Size(textElement.Size());
        textRun.Weight(textElement.Weight());
        textRun.Text(textElement.Text());
        return textRun;
    }
    return nullptr;
}

// TODO: Do I need const& for winrt::com_ptr?
// TODO: Can I just pass com_ptr of implementation? Can I just pass projection here?
namespace AdaptiveCards::Rendering::Uwp
{
    void RegisterDefaultElementRenderers(rtrender::implementation::AdaptiveElementRendererRegistration* registration,
                                         winrt::com_ptr<XamlBuilder> xamlBuilder)
    {
        // TODO: I don't need implementation of registration here, right? Or for safety reasons I do need it? (if
        // somebody implements interface and passes it in)
        registration->Set(L"ActionSet", winrt::make<rtrender::implementation::AdaptiveActionSetRenderer>());
        registration->Set(L"Column", winrt::make<rtrender::implementation::AdaptiveColumnRenderer>());
        registration->Set(L"ColumnSet", winrt::make<rtrender::implementation::AdaptiveColumnSetRenderer>());
        registration->Set(L"Container", winrt::make<rtrender::implementation::AdaptiveContainerRenderer>());
        registration->Set(L"FactSet", winrt::make<rtrender::implementation::AdaptiveFactSetRenderer>());
        registration->Set(L"Image", winrt::make<rtrender::implementation::AdaptiveImageRenderer>(xamlBuilder));
        registration->Set(L"ImageSet", winrt::make<rtrender::implementation::AdaptiveImageSetRenderer>());
        registration->Set(L"Input.ChoiceSet", winrt::make<rtrender::implementation::AdaptiveChoiceSetInputRenderer>());
        registration->Set(L"Input.Date", winrt::make<rtrender::implementation::AdaptiveDateInputRenderer>());
        registration->Set(L"Input.Number", winrt::make<rtrender::implementation::AdaptiveNumberInputRenderer>());
        registration->Set(L"Input.Text", winrt::make<rtrender::implementation::AdaptiveTextInputRenderer>());
        registration->Set(L"Input.Time", winrt::make<rtrender::implementation::AdaptiveTimeInputRenderer>());
        registration->Set(L"Input.Toggle", winrt::make<rtrender::implementation::AdaptiveToggleInputRenderer>());
        registration->Set(L"Media", winrt::make<rtrender::implementation::AdaptiveMediaRenderer>());
        registration->Set(L"RichTextBlock", winrt::make<rtrender::implementation::AdaptiveRichTextBlockRenderer>());
        registration->Set(L"Table", winrt::make<rtrender::implementation::AdaptiveTableRenderer>());
        registration->Set(L"TextBlock", winrt::make<rtrender::implementation::AdaptiveTextBlockRenderer>());
    }

    void RegisterDefaultActionRenderers(rtrender::implementation::AdaptiveActionRendererRegistration* registration)
    {
        registration->Set(L"Action.OpenUrl", winrt::make<rtrender::implementation::AdaptiveOpenUrlActionRenderer>());
        registration->Set(L"Action.ShowCard", winrt::make<rtrender::implementation::AdaptiveShowCardActionRenderer>());
        registration->Set(L"Action.Submit", winrt::make<rtrender::implementation::AdaptiveSubmitActionRenderer>());
        registration->Set(L"Action.ToggleVisibility",
                          winrt::make<rtrender::implementation::AdaptiveToggleVisibilityActionRenderer>());
        registration->Set(L"Action.Execute", winrt::make<rtrender::implementation::AdaptiveExecuteActionRenderer>());
    }
}
