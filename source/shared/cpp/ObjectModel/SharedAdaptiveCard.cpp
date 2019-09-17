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

using namespace AdaptiveSharedNamespace;

AdaptiveCard::AdaptiveCard() :
    m_style(ContainerStyle::None), m_verticalContentAlignment(VerticalContentAlignment::Top), m_height(HeightType::Auto),
    m_minHeight(0), m_inputNecessityIndicators(InputNecessityIndicators::None), m_internalId{InternalId::Next()}
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
    m_version(version),
    m_fallbackText(fallbackText), m_speak(speak), m_style(style), m_language(language),
    m_verticalContentAlignment(verticalContentAlignment), m_height(height), m_minHeight(minHeight),
    m_inputNecessityIndicators(InputNecessityIndicators::None), m_internalId{InternalId::Next()}
{
    m_backgroundImage = std::make_shared<BackgroundImage>(backgroundImageUrl);
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
    m_version(version),
    m_fallbackText(fallbackText), m_speak(speak), m_style(style), m_language(language),
    m_verticalContentAlignment(verticalContentAlignment), m_height(height), m_minHeight(minHeight),
    m_inputNecessityIndicators(InputNecessityIndicators::None), m_internalId{InternalId::Next()}, m_body(body),
    m_actions(actions)
{
    m_backgroundImage = std::make_shared<BackgroundImage>(backgroundImageUrl);
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
    m_minHeight(minHeight), m_inputNecessityIndicators(InputNecessityIndicators::None), m_internalId{InternalId::Next()}
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
                           unsigned int minHeight,
                           std::vector<std::shared_ptr<BaseCardElement>>& body,
                           std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    m_version(version),
    m_fallbackText(fallbackText), m_backgroundImage(backgroundImage), m_speak(speak), m_style(style),
    m_language(language), m_verticalContentAlignment(verticalContentAlignment), m_height(height), m_minHeight(minHeight),
    m_inputNecessityIndicators(InputNecessityIndicators::None), m_internalId{InternalId::Next()}, m_body(body),
    m_actions(actions)
{
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile,
                                                               std::string rendererVersion) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile, std::string rendererVersion)
#endif // __ANDROID__
{
    ParseContext context;
    return AdaptiveCard::DeserializeFromFile(jsonFile, rendererVersion, context);
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile,
                                                               std::string rendererVersion,
                                                               ParseContext& context) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(const std::string& jsonFile, std::string rendererVersion, ParseContext& context)
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
        if (language.empty() || language.length() == 2 || language.length() == 3)
        {
            auto locale = std::locale(language.c_str());
        }
        else
        {
            warnings.push_back(std::make_shared<AdaptiveCardParseWarning>(AdaptiveSharedNamespace::WarningStatusCode::InvalidLanguage,
                                                                          "Invalid language identifier: " + language));
        }
    }
    catch (std::runtime_error)
    {
        warnings.push_back(std::make_shared<AdaptiveCardParseWarning>(AdaptiveSharedNamespace::WarningStatusCode::InvalidLanguage,
                                                                      "Invalid language identifier: " + language));
    }
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::Deserialize(const Json::Value& json,
                                                       std::string rendererVersion,
                                                       ParseContext& context) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::Deserialize(const Json::Value& json, std::string rendererVersion, ParseContext& context)
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

            context.warnings.push_back(std::make_shared<AdaptiveCardParseWarning>(AdaptiveSharedNamespace::WarningStatusCode::UnsupportedSchemaVersion,
                                                                                  "Schema version not supported"));
            return std::make_shared<ParseResult>(MakeFallbackTextCard(fallbackText, language, speak), context.warnings);
        }
    }

    auto backgroundImage = ParseUtil::GetBackgroundImage(json);

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
        ParseSizeForPixelSize(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MinHeight), &context.warnings);

    // Parse body
    auto body = ParseUtil::GetElementCollection<BaseCardElement>(true, context, json, AdaptiveCardSchemaKey::Body, false);
    // Parse actions if present
    auto actions = ParseUtil::GetActionCollection(context, json, AdaptiveCardSchemaKey::Actions, false);

    EnsureShowCardVersions(actions, version);

    auto result = std::make_shared<AdaptiveCard>(
        version, fallbackText, backgroundImage, style, speak, language, verticalContentAlignment, height, minHeight, body, actions);
    result->SetLanguage(language);

    // Parse optional selectAction
    result->SetSelectAction(ParseUtil::GetAction(context, json, AdaptiveCardSchemaKey::SelectAction, false));

    result->SetInputNecessityIndicators(ParseUtil::GetEnumValue<InputNecessityIndicators>(
        json, AdaptiveCardSchemaKey::InputNecessityIndicators, InputNecessityIndicators::None, InputNecessityIndicatorsFromString));

    return std::make_shared<ParseResult>(result, context.warnings);
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString,
                                                                 std::string rendererVersion) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString, std::string rendererVersion)
#endif // __ANDROID__
{
    ParseContext context;
    return AdaptiveCard::DeserializeFromString(jsonString, rendererVersion, context);
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString,
                                                                 std::string rendererVersion,
                                                                 ParseContext& context) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(const std::string& jsonString, std::string rendererVersion, ParseContext& context)
#endif // __ANDROID__
{
    return AdaptiveCard::Deserialize(ParseUtil::GetJsonValueFromString(jsonString), rendererVersion, context);
}

Json::Value AdaptiveCard::SerializeToJsonValue() const
{
    Json::Value root;
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
    if (m_backgroundImage != nullptr && !m_backgroundImage->GetUrl().empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundImage)] = m_backgroundImage->SerializeToJsonValue();
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

    const HeightType height = GetHeight();
    if (height != HeightType::Auto)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Height)] = HeightTypeToString(GetHeight());
    }

    if (m_inputNecessityIndicators != InputNecessityIndicators::None)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::InputNecessityIndicators)] =
            InputNecessityIndicatorsToString(m_inputNecessityIndicators);
    }

    std::string bodyPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Body);
    root[bodyPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& cardElement : GetBody())
    {
        root[bodyPropertyName].append(cardElement->SerializeToJsonValue());
    }

    std::string actionsPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Actions);
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
                                                                 const std::string& speak) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
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

std::string AdaptiveCard::GetLanguage() const
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

InputNecessityIndicators AdaptiveCard::GetInputNecessityIndicators() const
{
    return m_inputNecessityIndicators;
}

void AdaptiveCard::SetInputNecessityIndicators(const InputNecessityIndicators value)
{
    m_inputNecessityIndicators = value;
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
