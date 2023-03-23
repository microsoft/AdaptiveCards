// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include <regex>

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

std::optional<double> TryHStringToDouble(winrt::hstring const& in)
{
    try
    {
        return std::stod(winrt::to_string(in));
    }
    catch (std::invalid_argument)
    {
        // in was not a valid double
        return {};
    }
}

// Get a Color object from color string
// Expected formats are "#AARRGGBB" (with alpha channel) and "#RRGGBB" (without alpha channel)
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

            auto alpha = strtol(alphaString.c_str(), nullptr, 16);

            color.A = static_cast<uint8_t>(alpha);

            hexColorString = hexColorString.substr(2, std::string::npos);
        }
        else
        {
            // Otherwise, set full opacity
            std::string alphaString = "FF";
            auto alpha = strtol(alphaString.c_str(), nullptr, 16);
            color.A = static_cast<uint8_t>(alpha);
        }

        // A valid string at this point should have 6 hex characters (RRGGBB)
        std::regex colorWithoutAlphaRegex("[0-9a-f]{6}", std::regex_constants::icase);
        if (regex_match(hexColorString, colorWithoutAlphaRegex))
        {
            // Then set all other Red, Green, and Blue channels
            std::string redString = hexColorString.substr(0, 2);
            auto red = strtol(redString.c_str(), nullptr, 16);

            std::string greenString = hexColorString.substr(2, 2);
            auto green = strtol(greenString.c_str(), nullptr, 16);

            std::string blueString = hexColorString.substr(4, 2);
            auto blue = strtol(blueString.c_str(), nullptr, 16);

            color.R = static_cast<uint8_t>(red);
            color.G = static_cast<uint8_t>(green);
            color.B = static_cast<uint8_t>(blue);

            return color;
        }
    }

    // All other formats are ignored (set alpha to 0)
    color.A = static_cast<uint8_t>(0);

    return color;
}

winrt::AdaptiveContainerStyleDefinition GetContainerStyleDefinition(winrt::ContainerStyle const& style,
                                                                    winrt::AdaptiveHostConfig const& hostConfig)
{
    auto containerStyles = hostConfig.ContainerStyles();

    switch (style)
    {
    case winrt::ContainerStyle::Accent:
        return containerStyles.Accent();
    case winrt::ContainerStyle::Attention:
        return containerStyles.Attention();
    case winrt::ContainerStyle::Emphasis:
        return containerStyles.Emphasis();
    case winrt::ContainerStyle::Good:
        return containerStyles.Good();
    case winrt::ContainerStyle::Warning:
        return containerStyles.Warning();
    case winrt::ContainerStyle::Default:
    default:
        return containerStyles.Default();
    }
}
winrt::Windows::UI::Color GetColorFromAdaptiveColor(winrt::AdaptiveHostConfig const& hostConfig,
                                                    winrt::ForegroundColor adaptiveColor,
                                                    winrt::ContainerStyle containerStyle,
                                                    bool isSubtle,
                                                    bool highlight)
{
    auto styleDefinition = GetContainerStyleDefinition(containerStyle, hostConfig);

    auto colorsConfig = styleDefinition.ForegroundColors();

    winrt::AdaptiveColorConfig colorConfig{};
    switch (adaptiveColor)
    {
    case winrt::ForegroundColor::Accent:
        colorConfig = colorsConfig.Accent();
        break;
    case winrt::ForegroundColor::Dark:
        colorConfig = colorsConfig.Dark();
        break;
    case winrt::ForegroundColor::Light:
        colorConfig = colorsConfig.Light();
        break;
    case winrt::ForegroundColor::Good:
        colorConfig = colorsConfig.Good();
        break;
    case winrt::ForegroundColor::Warning:
        colorConfig = colorsConfig.Warning();
        break;
    case winrt::ForegroundColor::Attention:
        colorConfig = colorsConfig.Attention();
        break;
    case winrt::ForegroundColor::Default:
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

winrt::TextHighlighter GetHighlighter(winrt::IAdaptiveTextElement const& adaptiveTextElement,
                                      winrt::AdaptiveRenderContext const& renderContext,
                                      winrt::AdaptiveRenderArgs const& renderArgs)
{
    winrt::TextHighlighter textHighlighter{};

    auto hostConfig = renderContext.HostConfig();

    winrt::ForegroundColor adaptiveForegroundColor = GetValueFromRef(adaptiveTextElement.Color(), winrt::ForegroundColor::Default);
    bool isSubtle = GetValueFromRef(adaptiveTextElement.IsSubtle(), false);

    auto containerStyle = renderArgs.ContainerStyle();

    auto backgroundColor = GetColorFromAdaptiveColor(hostConfig, adaptiveForegroundColor, containerStyle, isSubtle, true);
    auto foregroundColor = GetColorFromAdaptiveColor(hostConfig, adaptiveForegroundColor, containerStyle, isSubtle, false);

    textHighlighter.Background(winrt::SolidColorBrush{backgroundColor});
    textHighlighter.Foreground(winrt::SolidColorBrush{foregroundColor});

    return textHighlighter;
}

uint32_t GetSpacingSizeFromSpacing(winrt::AdaptiveHostConfig const& hostConfig, winrt::Spacing const& spacing)
{
    auto spacingConfig = hostConfig.Spacing();

    switch (spacing)
    {
    case winrt::Spacing::None:
        return 0;
    case winrt::Spacing::Small:
        return spacingConfig.Small();
    case winrt::Spacing::Medium:
        return spacingConfig.Medium();
    case winrt::Spacing::Large:
        return spacingConfig.Large();
    case winrt::Spacing::ExtraLarge:
        return spacingConfig.ExtraLarge();
    case winrt::Spacing::Padding:
        return spacingConfig.Padding();
    case winrt::Spacing::Default:
    default:
        return spacingConfig.Default();
    }
}

winrt::Windows::UI::Color GetBackgroundColorFromStyle(winrt::ContainerStyle const& style, winrt::AdaptiveHostConfig const& hostConfig)
{
    auto styleDefinition = GetContainerStyleDefinition(style, hostConfig);
    return styleDefinition.BackgroundColor();
}

winrt::Windows::UI::Color GetBorderColorFromStyle(winrt::ContainerStyle style, winrt::AdaptiveHostConfig const& hostConfig)
{
    auto styleDefinition = GetContainerStyleDefinition(style, hostConfig);
    return styleDefinition.BorderColor();
}

winrt::hstring GetFontFamilyFromFontType(winrt::AdaptiveHostConfig const& hostConfig, winrt::FontType const& fontType)
{
    // Get FontFamily from desired style
    auto typeDefinition = GetFontType(hostConfig, fontType);
    auto fontFamily = typeDefinition.FontFamily();
    if (fontFamily.empty())
    {
        if (fontType == winrt::FontType::Monospace)
        {
            // fallback to system default monospace FontFamily
            fontFamily = UTF8ToHString("Courier New");
        }
        else
        {
            // fallback to deprecated FontFamily
            fontFamily = hostConfig.FontFamily();
            if (fontFamily.empty())
            {
                // fallback to system default FontFamily
                fontFamily = UTF8ToHString("Segoe UI");
            }
        }
    }
    return fontFamily;
}

uint32_t GetFontSizeFromFontType(winrt::AdaptiveHostConfig const& hostConfig, winrt::FontType const& fontType, winrt::TextSize const& desiredSize)
{
    winrt::AdaptiveFontTypeDefinition fontTypeDefinition = GetFontType(hostConfig, fontType);
    winrt::AdaptiveFontSizesConfig sizesConfig = fontTypeDefinition.FontSizes();
    uint32_t result = GetFontSize(sizesConfig, desiredSize);

    if (result == std::numeric_limits<unsigned int>::max())
    {
        // Get FontSize from Default style
        fontTypeDefinition = GetFontType(hostConfig, winrt::FontType::Default);
        sizesConfig = fontTypeDefinition.FontSizes();
        result = GetFontSize(sizesConfig, desiredSize);

        if (result == std::numeric_limits<unsigned int>::max())
        {
            // get deprecated FontSize
            sizesConfig = hostConfig.FontSizes();
            result = GetFontSize(sizesConfig, desiredSize);

            if (result == std::numeric_limits<unsigned int>::max())
            {
                // set system default FontSize based on desired style
                switch (desiredSize)
                {
                case winrt::TextSize::Small:
                    result = 10;
                    break;
                case winrt::TextSize::Medium:
                    result = 14;
                    break;
                case winrt::TextSize::Large:
                    result = 17;
                    break;
                case winrt::TextSize::ExtraLarge:
                    result = 20;
                    break;
                case winrt::TextSize::Default:
                default:
                    result = 12;
                    break;
                }
            }
        }
    }
    return result;
}

winrt::Windows::UI::Text::FontWeight GetFontWeightFromStyle(winrt::AdaptiveHostConfig const& hostConfig,
                                                            winrt::FontType const& fontType,
                                                            winrt::TextWeight const& desiredWeight)
{
    winrt::AdaptiveFontTypeDefinition fontTypeDefinition = GetFontType(hostConfig, fontType);
    winrt::AdaptiveFontWeightsConfig weightConfig = fontTypeDefinition.FontWeights();
    uint16_t result = GetFontWeight(weightConfig, desiredWeight);

    if (result == MAXUINT16)
    {
        // get FontWeight from Default style
        fontTypeDefinition = GetFontType(hostConfig, winrt::FontType::Default);
        weightConfig = fontTypeDefinition.FontWeights();
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
                case winrt::TextWeight::Lighter:
                    result = 200;
                    break;
                case winrt::TextWeight::Bolder:
                    result = 800;
                    break;
                case winrt::TextWeight::Default:
                default:
                    result = 400;
                    break;
                }
            }
        }
    }
    return {result};
}

winrt::AdaptiveFontTypeDefinition GetFontType(winrt::AdaptiveHostConfig const& hostConfig, winrt::FontType const& fontType)
{
    auto fontTypes = hostConfig.FontTypes();
    switch (fontType)
    {
    case winrt::FontType::Monospace:
        return fontTypes.Monospace();
        break;
    case winrt::FontType::Default:
    default:
        return fontTypes.Default();
        break;
    }
}

uint32_t GetFontSize(winrt::AdaptiveFontSizesConfig const& sizesConfig, winrt::TextSize const& desiredSize)
{
    switch (desiredSize)
    {
    case winrt::TextSize::Small:
        return sizesConfig.Small();
        break;
    case winrt::TextSize::Medium:
        return sizesConfig.Medium();
        break;
    case winrt::TextSize::Large:
        return sizesConfig.Large();
        break;
    case winrt::TextSize::ExtraLarge:
        return sizesConfig.ExtraLarge();
        break;
    case winrt::TextSize::Default:
    default:
        return sizesConfig.Default();
        break;
    }
}

uint16_t GetFontWeight(winrt::AdaptiveFontWeightsConfig const& weightsConfig, winrt::TextWeight const& desiredWeight)
{
    switch (desiredWeight)
    {
    case winrt::TextWeight::Lighter:
        return weightsConfig.Lighter();
        break;
    case winrt::TextWeight::Bolder:
        return weightsConfig.Bolder();
        break;
    case winrt::TextWeight::Default:
    default:
        return weightsConfig.Default();
        break;
    }
}

winrt::JsonObject StringToJsonObject(const std::string& inputString)
{
    return HStringToJsonObject(UTF8ToHString(inputString));
}

winrt::JsonObject HStringToJsonObject(winrt::hstring const& inputHString)
{
    winrt::JsonObject obj{nullptr};

    if (!winrt::JsonObject::TryParse(inputHString, obj))
    {
        obj = {};
    }

    return obj;
}

std::string JsonObjectToString(winrt::JsonObject const& inputJson)
{
    return HStringToUTF8(JsonObjectToHString(inputJson));
}

winrt::hstring JsonObjectToHString(winrt::JsonObject const& inputJson)
{
    return inputJson.Stringify();
}

bool MeetsRequirements(winrt::IAdaptiveCardElement const& cardElement, winrt::AdaptiveFeatureRegistration const& featureRegistration)
{
    winrt::IVector<winrt::AdaptiveRequirement> requirements = cardElement.Requirements();
    bool meetsRequirementsLocal = true;

    if (requirements)
    {
        for (auto req : requirements)
        {
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
                    AdaptiveCards::SemanticVersion requirementSemanticVersion(requirementVersionString);
                    AdaptiveCards::SemanticVersion registrationSemanticVersion(HStringToUTF8(registrationVersion));
                    if (registrationSemanticVersion < requirementSemanticVersion)
                    {
                        meetsRequirementsLocal = false;
                    }
                }
            }
        }
    }

    return meetsRequirementsLocal;
}

bool IsBackgroundImageValid(winrt::AdaptiveBackgroundImage const& backgroundImage)
{
    if (backgroundImage)
    {
        return !backgroundImage.Url().empty();
    }
    return false;
}

winrt::Uri GetUrlFromString(winrt::AdaptiveHostConfig const& hostConfig, winrt::hstring const& urlString)
{
    winrt::Uri uri{nullptr};

    if (const auto uriFromAbsoluteUri = winrt::Uri{urlString})
    {
        return uriFromAbsoluteUri;
    }
    else
    {
        winrt::hstring imageBaseUrl = hostConfig.ImageBaseUrl();

        if (const auto uriFromRelativeUri = winrt::Uri{imageBaseUrl, urlString})
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
    hoverColor.R = originalColor.R - static_cast<uint8_t>(originalColor.R * hoverIncrement);
    hoverColor.G = originalColor.G - static_cast<uint8_t>(originalColor.G * hoverIncrement);
    hoverColor.B = originalColor.B - static_cast<uint8_t>(originalColor.B * hoverIncrement);
    return hoverColor;
}

winrt::DateTime GetDateTime(unsigned int year, unsigned int month, unsigned int day)
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

    return winrt::clock::from_FILETIME({fileTime});
}

winrt::IReference<winrt::DateTime> GetDateTimeReference(unsigned int year, unsigned int month, unsigned int day)
{
    return GetDateTime(year, month, day);
}

winrt::IAdaptiveTextElement CopyTextElement(winrt::IAdaptiveTextElement const& textElement)
{
    if (textElement)
    {
        winrt::AdaptiveTextRun textRun;

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

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    void RegisterDefaultElementRenderers(winrt::implementation::AdaptiveElementRendererRegistration* registration,
                                         winrt::com_ptr<XamlBuilder> xamlBuilder)
    {
        registration->Set(L"ActionSet", winrt::make<winrt::implementation::AdaptiveActionSetRenderer>());
        registration->Set(L"Column", winrt::make<winrt::implementation::AdaptiveColumnRenderer>());
        registration->Set(L"ColumnSet", winrt::make<winrt::implementation::AdaptiveColumnSetRenderer>());
        registration->Set(L"Container", winrt::make<winrt::implementation::AdaptiveContainerRenderer>());
        registration->Set(L"FactSet", winrt::make<winrt::implementation::AdaptiveFactSetRenderer>());
        registration->Set(L"Image", winrt::make<winrt::implementation::AdaptiveImageRenderer>(xamlBuilder));
        registration->Set(L"ImageSet", winrt::make<winrt::implementation::AdaptiveImageSetRenderer>());
        registration->Set(L"Input.ChoiceSet", winrt::make<winrt::implementation::AdaptiveChoiceSetInputRenderer>());
        registration->Set(L"Input.Date", winrt::make<winrt::implementation::AdaptiveDateInputRenderer>());
        registration->Set(L"Input.Number", winrt::make<winrt::implementation::AdaptiveNumberInputRenderer>());
        registration->Set(L"Input.Text", winrt::make<winrt::implementation::AdaptiveTextInputRenderer>());
        registration->Set(L"Input.Time", winrt::make<winrt::implementation::AdaptiveTimeInputRenderer>());
        registration->Set(L"Input.Toggle", winrt::make<winrt::implementation::AdaptiveToggleInputRenderer>());
        registration->Set(L"Media", winrt::make<winrt::implementation::AdaptiveMediaRenderer>());
        registration->Set(L"RichTextBlock", winrt::make<winrt::implementation::AdaptiveRichTextBlockRenderer>());
        registration->Set(L"Table", winrt::make<winrt::implementation::AdaptiveTableRenderer>());
        registration->Set(L"TextBlock", winrt::make<winrt::implementation::AdaptiveTextBlockRenderer>());
    }

    void RegisterDefaultActionRenderers(winrt::implementation::AdaptiveActionRendererRegistration* registration)
    {
        registration->Set(L"Action.OpenUrl", winrt::make<winrt::implementation::AdaptiveOpenUrlActionRenderer>());
        registration->Set(L"Action.ShowCard", winrt::make<winrt::implementation::AdaptiveShowCardActionRenderer>());
        registration->Set(L"Action.Submit", winrt::make<winrt::implementation::AdaptiveSubmitActionRenderer>());
        registration->Set(L"Action.ToggleVisibility",
                          winrt::make<winrt::implementation::AdaptiveToggleVisibilityActionRenderer>());
        registration->Set(L"Action.Execute", winrt::make<winrt::implementation::AdaptiveExecuteActionRenderer>());
    }
}
