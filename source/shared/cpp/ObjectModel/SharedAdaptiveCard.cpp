// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "ParseUtil.h"
#include "Util.h"
#include "ShowCardAction.h"
#include "TextBlock.h"
#include "AdaptiveCardParseWarning.h"
#include "SemanticVersion.h"
#include "ParseContext.h"
#include "BackgroundImage.h"

using namespace AdaptiveCards;

AdaptiveCard::AdaptiveCard() :
    AdaptiveCard("", "", std::shared_ptr<BackgroundImage>(), ContainerStyle::None, "", "", VerticalContentAlignment::Top, HeightType::Auto, 0)
{
}

AdaptiveCard::AdaptiveCard(std::string const& version,
                           std::string const& fallbackText,
                           std::string const& backgroundImageUrl,
                           ContainerStyle style,
                           std::string const& speak,
                           std::string const& language,
                           VerticalContentAlignment verticalContentAlignment,
                           HeightType height,
                           unsigned int minHeight) :
    AdaptiveCard(version, fallbackText, std::make_shared<BackgroundImage>(backgroundImageUrl), style, speak, language, verticalContentAlignment, height, minHeight)
{
}

AdaptiveCard::AdaptiveCard(std::string const& version,
                           std::string const& fallbackText,
                           std::string const& backgroundImageUrl,
                           ContainerStyle style,
                           std::string const& speak,
                           std::string const& language,
                           VerticalContentAlignment verticalContentAlignment,
                           HeightType height,
                           unsigned int minHeight,
                           std::vector<std::shared_ptr<BaseCardElement>>& body,
                           std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    AdaptiveCard(version, fallbackText, std::make_shared<BackgroundImage>(backgroundImageUrl), style, speak, language, verticalContentAlignment, height, minHeight, body, actions)
{
}

AdaptiveCard::AdaptiveCard(std::string const& version,
                           std::string const& fallbackText,
                           std::shared_ptr<BackgroundImage> backgroundImage,
                           ContainerStyle style,
                           std::string const& speak,
                           std::string const& language,
                           VerticalContentAlignment verticalContentAlignment,
                           HeightType height,
                           unsigned int minHeight) :
    m_version(version),
    m_fallbackText(fallbackText), m_backgroundImage(backgroundImage), m_speak(speak), m_style(style),
    m_language(language), m_verticalContentAlignment(verticalContentAlignment), m_height(height),
    m_minHeight(minHeight), m_internalId{InternalId::Next()}, m_additionalProperties{}
{
    PopulateKnownPropertiesSet();
}

AdaptiveCard::AdaptiveCard(std::string const& version,
                           std::string const& fallbackText,
                           std::shared_ptr<BackgroundImage> backgroundImage,
                           ContainerStyle style,
                           std::string const& speak,
                           std::string const& language,
                           VerticalContentAlignment verticalContentAlignment,
                           HeightType height,
                           unsigned int minHeight,
                           std::vector<std::shared_ptr<BaseCardElement>>& body,
                           std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    AdaptiveCard(version,
                 fallbackText,
                 backgroundImage,
                 std::shared_ptr<Refresh>(),
                 std::shared_ptr<Authentication>(),
                 style,
                 speak,
                 language,
                 verticalContentAlignment,
                 height,
                 minHeight,
                 body,
                 actions)
{
}

AdaptiveCard::AdaptiveCard(std::string const& version,
                           std::string const& fallbackText,
                           std::shared_ptr<BackgroundImage> backgroundImage,
                           std::shared_ptr<Refresh> refresh,
                           std::shared_ptr<Authentication> authentication,
                           ContainerStyle style,
                           std::string const& speak,
                           std::string const& language,
                           VerticalContentAlignment verticalContentAlignment,
                           HeightType height,
                           unsigned int minHeight,
                           std::vector<std::shared_ptr<BaseCardElement>>& body,
                           std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    m_version(version),
    m_fallbackText(fallbackText), m_backgroundImage(backgroundImage), m_refresh(refresh),
    m_authentication(authentication), m_speak(speak), m_style(style), m_language(language),
    m_verticalContentAlignment(verticalContentAlignment), m_height(height),
    m_minHeight(minHeight), m_internalId{InternalId::Next()}, m_body(body), m_actions(actions), m_additionalProperties{}
{
    PopulateKnownPropertiesSet();
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile,
                                                               std::string rendererVersion) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile, const std::string& rendererVersion)
#endif // __ANDROID__
{
    ParseContext context;
    return AdaptiveCard::DeserializeFromFile(jsonFile, rendererVersion, context);
}

#ifdef __ANDROID__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdynamic-exception-spec"
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile,
                                                               std::string rendererVersion,
                                                               ParseContext& context) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile,
                                                               const std::string& rendererVersion,
                                                               ParseContext& context)
#endif // __ANDROID__
{
    std::ifstream jsonFileStream(jsonFile);

    Json::Value root;
    jsonFileStream >> root;

    return AdaptiveCard::Deserialize(root, rendererVersion, context);
}

void AdaptiveCard::_ValidateLanguage(const std::string& language, std::vector<std::shared_ptr<AdaptiveCardParseWarning>>& warnings)
{
    try
    {
        if (language.empty())
        {
            // no need to validate locale
        }
        else if (language.length() == 2)
        {
            auto locale = std::locale(language.c_str());
        }
        else
        {
            warnings.push_back(std::make_shared<AdaptiveCardParseWarning>(AdaptiveCards::WarningStatusCode::InvalidLanguage,
                                                                          "Invalid language identifier: " + language));
        }
    }
    catch (std::runtime_error)
    {
        warnings.push_back(std::make_shared<AdaptiveCardParseWarning>(AdaptiveCards::WarningStatusCode::InvalidLanguage,
                                                                      "Invalid language identifier: " + language));
    }
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::Deserialize(const Json::Value& json,
                                                       std::string rendererVersion,
                                                       ParseContext& context) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::Deserialize(const Json::Value& json, const std::string& rendererVersion, ParseContext& context)
#endif // __ANDROID__
{
    ParseUtil::ThrowIfNotJsonObject(json);

    const bool enforceVersion = !rendererVersion.empty();

    // Verify this is an adaptive card
    ParseUtil::ExpectTypeString(json, CardElementType::AdaptiveCard);

    std::string version = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Version, enforceVersion);
    std::string fallbackText = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FallbackText);
    std::string language = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Language);
    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);

    // check if language is valid
    _ValidateLanguage(language, context.warnings);

    if (language.size())
    {
        context.SetLanguage(language);
    }
    else
    {
        language = context.GetLanguage();
    }

    // Perform version validation
    if (enforceVersion)
    {
        const SemanticVersion rendererMaxVersion(rendererVersion);
        const SemanticVersion cardVersion(version);

        if (rendererVersion < cardVersion)
        {
            if (fallbackText.empty())
            {
                fallbackText = "We're sorry, this card couldn't be displayed";
            }

            if (speak.empty())
            {
                speak = fallbackText;
            }

            context.warnings.push_back(std::make_shared<AdaptiveCardParseWarning>(AdaptiveCards::WarningStatusCode::UnsupportedSchemaVersion,
                                                                                  "Schema version not supported"));
            return std::make_shared<ParseResult>(MakeFallbackTextCard(fallbackText, language, speak), context.warnings);
        }
    }

    auto backgroundImage =
        ParseUtil::DeserializeValue<BackgroundImage>(json, AdaptiveCardSchemaKey::BackgroundImage, BackgroundImage::Deserialize);
    auto refresh = ParseUtil::DeserializeValue<Refresh>(context, json, AdaptiveCardSchemaKey::Refresh, Refresh::Deserialize);
    auto authentication =
        ParseUtil::DeserializeValue<Authentication>(context, json, AdaptiveCardSchemaKey::Authentication, Authentication::Deserialize);

    ContainerStyle style =
        ParseUtil::GetEnumValue<ContainerStyle>(json, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString);
    context.SetParentalContainerStyle(style);

    VerticalContentAlignment verticalContentAlignment =
        ParseUtil::GetEnumValue<VerticalContentAlignment>(json,
                                                          AdaptiveCardSchemaKey::VerticalContentAlignment,
                                                          VerticalContentAlignment::Top,
                                                          VerticalContentAlignmentFromString);
    HeightType height =
        ParseUtil::GetEnumValue<HeightType>(json, AdaptiveCardSchemaKey::Height, HeightType::Auto, HeightTypeFromString);

    unsigned int minHeight =
        ParseSizeForPixelSize(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MinHeight), &context.warnings).value_or(0);

    // Parse body
    auto body = ParseUtil::GetElementCollection<BaseCardElement>(true, context, json, AdaptiveCardSchemaKey::Body, false);
    // Parse actions if present
    auto actions = ParseUtil::GetActionCollection(context, json, AdaptiveCardSchemaKey::Actions, false);

    EnsureShowCardVersions(actions, version);

    auto result = std::make_shared<AdaptiveCard>(
        version, fallbackText, backgroundImage, refresh, authentication, style, speak, language, verticalContentAlignment, height, minHeight, body, actions);
    result->SetLanguage(language);
    result->SetRtl(ParseUtil::GetOptionalBool(json, AdaptiveCardSchemaKey::Rtl));

    // Parse optional selectAction
    result->SetSelectAction(ParseUtil::GetAction(context, json, AdaptiveCardSchemaKey::SelectAction, false));

    Json::Value additionalProperties;
    HandleUnknownProperties(json, result->GetKnownProperties(), additionalProperties);
    result->SetAdditionalProperties(additionalProperties);

    return std::make_shared<ParseResult>(result, context.warnings);
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString,
                                                                 std::string rendererVersion) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString, const std::string& rendererVersion)
#endif // __ANDROID__
{
    ParseContext context;
    return AdaptiveCard::DeserializeFromString(jsonString, rendererVersion, context);
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString,
                                                                 std::string rendererVersion,
                                                                 ParseContext& context) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString,
                                                                 const std::string& rendererVersion,
                                                                 ParseContext& context)
#endif // __ANDROID__
{
    return AdaptiveCard::Deserialize(ParseUtil::GetJsonValueFromString(jsonString), rendererVersion, context);
}

Json::Value AdaptiveCard::SerializeToJsonValue() const
{
    Json::Value root = GetAdditionalProperties();
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = CardElementTypeToString(CardElementType::AdaptiveCard);

    if (!m_version.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Version)] = m_version;
    }
    else
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Version)] = "1.0";
    }

    if (!m_fallbackText.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FallbackText)] = m_fallbackText;
    }
    if (m_backgroundImage != nullptr && m_backgroundImage->ShouldSerialize())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundImage)] = m_backgroundImage->SerializeToJsonValue();
    }
    if (m_refresh != nullptr && m_refresh->ShouldSerialize())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Refresh)] = m_refresh->SerializeToJsonValue();
    }
    if (m_authentication != nullptr && m_authentication->ShouldSerialize())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Authentication)] = m_authentication->SerializeToJsonValue();
    }
    if (!m_speak.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Speak)] = m_speak;
    }
    if (!m_language.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Language)] = m_language;
    }
    if (m_style != ContainerStyle::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = ContainerStyleToString(m_style);
    }
    if (m_verticalContentAlignment != VerticalContentAlignment::Top)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment)] =
            VerticalContentAlignmentToString(m_verticalContentAlignment);
    }

    if (m_minHeight)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MinHeight)] = std::to_string(GetMinHeight()) + "px";
    }

    if (m_rtl.has_value())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Rtl)] = m_rtl.value_or("");
    }

    const HeightType height = GetHeight();
    if (height != HeightType::Auto)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height)] = HeightTypeToString(GetHeight());
    }

    const std::string& bodyPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Body);
    root[bodyPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetBody())
    {
        root[bodyPropertyName].append(cardElement->SerializeToJsonValue());
    }

    const std::string& actionsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions);
    root[actionsPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& action : GetActions())
    {
        root[actionsPropertyName].append(action->SerializeToJsonValue());
    }

    return root;
}

#ifdef __ANDROID__
std::shared_ptr<AdaptiveCard> AdaptiveCard::MakeFallbackTextCard(const std::string& fallbackText,
                                                                 const std::string& language,
                                                                 const std::string& speak) throw(AdaptiveCards::AdaptiveCardParseException)
#else
std::shared_ptr<AdaptiveCard> AdaptiveCard::MakeFallbackTextCard(const std::string& fallbackText,
                                                                 const std::string& language,
                                                                 const std::string& speak)
#endif // __ANDROID__
{
    std::shared_ptr<AdaptiveCard> fallbackCard = std::make_shared<AdaptiveCard>(
        "1.0", fallbackText, "", ContainerStyle::Default, speak, language, VerticalContentAlignment::Top, HeightType::Auto, 0);

    std::shared_ptr<TextBlock> textBlock = std::make_shared<TextBlock>();
    textBlock->SetText(fallbackText);
    textBlock->SetLanguage(language);

    fallbackCard->GetBody().push_back(textBlock);

    return fallbackCard;
}

std::string AdaptiveCard::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

std::string AdaptiveCard::GetVersion() const
{
    return m_version;
}

void AdaptiveCard::SetVersion(const std::string& value)
{
    m_version = value;
}

std::string AdaptiveCard::GetFallbackText() const
{
    return m_fallbackText;
}

void AdaptiveCard::SetFallbackText(const std::string& value)
{
    m_fallbackText = value;
}

std::shared_ptr<BackgroundImage> AdaptiveCard::GetBackgroundImage() const
{
    return m_backgroundImage;
}

void AdaptiveCard::SetBackgroundImage(const std::shared_ptr<BackgroundImage> value)
{
    m_backgroundImage = value;
}

std::shared_ptr<Refresh> AdaptiveCard::GetRefresh() const
{
    return m_refresh;
}

void AdaptiveCard::SetRefresh(const std::shared_ptr<Refresh> value)
{
    m_refresh = value;
}

std::shared_ptr<Authentication> AdaptiveCard::GetAuthentication() const
{
    return m_authentication;
}

void AdaptiveCard::SetAuthentication(const std::shared_ptr<Authentication> value)
{
    m_authentication = value;
}

std::string AdaptiveCard::GetSpeak() const
{
    return m_speak;
}

void AdaptiveCard::SetSpeak(const std::string& value)
{
    m_speak = value;
}

ContainerStyle AdaptiveCard::GetStyle() const
{
    return m_style;
}

void AdaptiveCard::SetStyle(const ContainerStyle value)
{
    m_style = value;
}

const std::string& AdaptiveCard::GetLanguage() const
{
    return m_language;
}

void AdaptiveCard::SetLanguage(const std::string& value)
{
    m_language = value;
}

HeightType AdaptiveCard::GetHeight() const
{
    return m_height;
}

void AdaptiveCard::SetHeight(const HeightType value)
{
    m_height = value;
}

CardElementType AdaptiveCard::GetElementType() const
{
    return CardElementType::AdaptiveCard;
}

std::vector<std::shared_ptr<BaseCardElement>>& AdaptiveCard::GetBody()
{
    return m_body;
}

const std::vector<std::shared_ptr<BaseCardElement>>& AdaptiveCard::GetBody() const
{
    return m_body;
}

std::vector<std::shared_ptr<BaseActionElement>>& AdaptiveCard::GetActions()
{
    return m_actions;
}

const std::vector<std::shared_ptr<BaseActionElement>>& AdaptiveCard::GetActions() const
{
    return m_actions;
}

std::shared_ptr<BaseActionElement> AdaptiveCard::GetSelectAction() const
{
    return m_selectAction;
}

void AdaptiveCard::SetSelectAction(const std::shared_ptr<BaseActionElement> action)
{
    m_selectAction = action;
}

VerticalContentAlignment AdaptiveCard::GetVerticalContentAlignment() const
{
    return m_verticalContentAlignment;
}

void AdaptiveCard::SetVerticalContentAlignment(const VerticalContentAlignment value)
{
    m_verticalContentAlignment = value;
}

unsigned int AdaptiveCard::GetMinHeight() const
{
    return m_minHeight;
}

void AdaptiveCard::SetMinHeight(const unsigned int value)
{
    m_minHeight = value;
}

// value is present if and only if "rtl" property is explicitly set
std::optional<bool> AdaptiveCard::GetRtl() const
{
    return m_rtl;
}

void AdaptiveCard::SetRtl(const std::optional<bool>& value)
{
    m_rtl = value;
}

void AdaptiveCard::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Version),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Body),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FallbackText),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundImage),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Refresh),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Authentication),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MinHeight),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Speak),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Language),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::VerticalContentAlignment),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::SelectAction),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Schema)});
}

const std::unordered_set<std::string>& AdaptiveCard::GetKnownProperties() const
{
    return m_knownProperties;
}

const Json::Value& AdaptiveCard::GetAdditionalProperties() const
{
    return m_additionalProperties;
}

void AdaptiveCard::SetAdditionalProperties(Json::Value&& value)
{
    m_additionalProperties = std::move(value);
}
void AdaptiveCard::SetAdditionalProperties(const Json::Value& value)
{
    m_additionalProperties = value;
}

std::vector<RemoteResourceInformation> AdaptiveCard::GetResourceInformation()
{
    auto resourceVector = std::vector<RemoteResourceInformation>();

    auto backgroundImage = GetBackgroundImage();
    if (backgroundImage != nullptr)
    {
        RemoteResourceInformation backgroundImageInfo;
        backgroundImageInfo.url = backgroundImage->GetUrl();
        backgroundImageInfo.mimeType = "image";
        resourceVector.push_back(backgroundImageInfo);
    }

    for (auto item : m_body)
    {
        item->GetResourceInformation(resourceVector);
    }

    for (auto item : m_actions)
    {
        item->GetResourceInformation(resourceVector);
    }

    return resourceVector;
}
