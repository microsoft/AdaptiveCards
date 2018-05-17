#include "pch.h"
#include "SharedAdaptiveCard.h"
#include "ParseUtil.h"
#include "Util.h"
#include "ShowCardAction.h"
#include "TextBlock.h"
#include "AdaptiveCardParseWarning.h"

using namespace AdaptiveSharedNamespace;

AdaptiveCard::AdaptiveCard(): m_style(ContainerStyle::None)
{
}

AdaptiveCard::AdaptiveCard(std::string const &version,
    std::string const &fallbackText,
    std::string const &backgroundImage,
    ContainerStyle style,
    std::string const &speak,
    std::string const &language) :
    m_version(version),
    m_fallbackText(fallbackText),
    m_backgroundImage(backgroundImage),
    m_speak(speak),
    m_style(style),
    m_language(language)
{
}

AdaptiveCard::AdaptiveCard(std::string const &version,
    std::string const &fallbackText,
    std::string const &backgroundImage,
    ContainerStyle style,
    std::string const &speak,
    std::string const &language,
    std::vector<std::shared_ptr<BaseCardElement>>& body, std::vector<std::shared_ptr<BaseActionElement>>& actions) :
    m_version(version),
    m_fallbackText(fallbackText),
    m_backgroundImage(backgroundImage),
    m_speak(speak),
    m_style(style),
    m_language(language),
    m_body(body),
    m_actions(actions)
{
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(
    const std::string& jsonFile,
    double rendererVersion,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromFile(
    const std::string& jsonFile,
    double rendererVersion,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration)
#endif // __ANDROID__
{
    std::ifstream jsonFileStream(jsonFile);

    Json::Value root;
    jsonFileStream >> root;

    return AdaptiveCard::Deserialize(root, rendererVersion, elementParserRegistration, actionParserRegistration);
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::Deserialize(
    const Json::Value& json,
    double rendererVersion,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::Deserialize(
    const Json::Value& json,
    double rendererVersion,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration)
#endif // __ANDROID__
{
    ParseUtil::ThrowIfNotJsonObject(json);

    // Verify this is an adaptive card
    ParseUtil::ExpectTypeString(json, CardElementType::AdaptiveCard);

    std::vector<std::shared_ptr<AdaptiveCardParseWarning>> warnings;

    std::string version = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Version);
    std::string fallbackText = ParseUtil::GetString(json, AdaptiveCardSchemaKey::FallbackText);
    std::string language = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Language);

    if (rendererVersion != std::numeric_limits<double>::max())
    {
        double versionAsDouble;
        try
        {
            versionAsDouble = std::stod(version.c_str());
        }
        catch (...)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue, "Card version not valid");
        }

        if (rendererVersion < versionAsDouble)
        {
            if (fallbackText.empty())
            {
                fallbackText = "We're sorry, this card couldn't be displayed";
            }

            warnings.push_back(std::make_shared<AdaptiveCardParseWarning>(AdaptiveSharedNamespace::WarningStatusCode::UnsupportedSchemaVersion, "Schema version not supported"));
            return std::make_shared<ParseResult>(MakeFallbackTextCard(fallbackText, language), warnings);
        }
    }

    std::string backgroundImageUrl = ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundImageUrl);
    std::string backgroundImage = backgroundImageUrl != "" ? backgroundImageUrl :
        ParseUtil::GetString(json, AdaptiveCardSchemaKey::BackgroundImage);
    std::string speak = ParseUtil::GetString(json, AdaptiveCardSchemaKey::Speak);
    ContainerStyle style = ParseUtil::GetEnumValue<ContainerStyle>(json, AdaptiveCardSchemaKey::Style, ContainerStyle::None, ContainerStyleFromString);

    if (elementParserRegistration == nullptr)
    {
        elementParserRegistration.reset(new ElementParserRegistration());
    }
    if (actionParserRegistration == nullptr)
    {
        actionParserRegistration.reset(new ActionParserRegistration());
    }

    // Parse body
    auto body = ParseUtil::GetElementCollection(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::Body, false);
    // Parse actions if present
    auto actions = ParseUtil::GetActionCollection(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::Actions, false);

    auto result = std::make_shared<AdaptiveCard>(version, fallbackText, backgroundImage, style, speak, language, body, actions);
    result->SetLanguage(language);

    // Parse optional selectAction
    result->SetSelectAction(ParseUtil::GetSelectAction(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::SelectAction, false));

    return std::make_shared<ParseResult>(result, warnings);
}

#ifdef __ANDROID__
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(
    const std::string& jsonString,
    double rendererVersion,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<ParseResult> AdaptiveCard::DeserializeFromString(
    const std::string& jsonString,
    double rendererVersion,
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration)
#endif // __ANDROID__
{
    return AdaptiveCard::Deserialize(ParseUtil::GetJsonValueFromString(jsonString), rendererVersion, elementParserRegistration, actionParserRegistration);
}

Json::Value AdaptiveCard::SerializeToJsonValue() const
{
    Json::Value root;
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = CardElementTypeToString(CardElementType::AdaptiveCard);
    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Version)] = GetVersion();

    if (!m_fallbackText.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FallbackText)] = m_fallbackText;
    }
    if (!m_backgroundImage.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::BackgroundImage)] = m_backgroundImage;
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
std::shared_ptr<AdaptiveCard> AdaptiveCard::MakeFallbackTextCard(
    const std::string& fallbackText,
    const std::string& language) throw(AdaptiveSharedNamespace::AdaptiveCardParseException)
#else
std::shared_ptr<AdaptiveCard> AdaptiveCard::MakeFallbackTextCard(
    const std::string& fallbackText,
    const std::string& language)
#endif // __ANDROID__
{
    std::shared_ptr<AdaptiveCard> fallbackCard = std::make_shared<AdaptiveCard>("1.0", fallbackText, "", ContainerStyle::Default, "", language);

    std::shared_ptr<TextBlock> textBlock = std::make_shared<TextBlock>();
    textBlock->SetText(fallbackText);
    textBlock->SetLanguage(language);

    fallbackCard->GetBody().push_back(textBlock);

    return fallbackCard;
}

std::string AdaptiveCard::Serialize() const
{
    Json::FastWriter writer;
    return writer.write(SerializeToJsonValue());
}

std::string AdaptiveCard::GetVersion() const
{
    return m_version;
}

void AdaptiveCard::SetVersion(const std::string &value)
{
    m_version = value;
}

std::string AdaptiveCard::GetFallbackText() const
{
    return m_fallbackText;
}

void AdaptiveCard::SetFallbackText(const std::string &value)
{
    m_fallbackText = value;
}

std::string AdaptiveCard::GetBackgroundImage() const
{
    return m_backgroundImage;
}

void AdaptiveCard::SetBackgroundImage(const std::string &value)
{
    m_backgroundImage = value;
}

std::string AdaptiveCard::GetSpeak() const
{
    return m_speak;
}

void AdaptiveCard::SetSpeak(const std::string &value)
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
    // Propagate language to ColumnSet, Containers, TextBlocks and showCardActions
    PropagateLanguage(value, m_body);

    for (auto& actionElement : m_actions)
    {
        if (actionElement->GetElementType() == ActionType::ShowCard)
        {
            auto showCard = std::static_pointer_cast<ShowCardAction>(actionElement);
            if (showCard != nullptr)
            {
                showCard->SetLanguage(value);
            }
        }
    }
}

const CardElementType AdaptiveCard::GetElementType() const
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

std::vector<std::string> AdaptiveCards::AdaptiveCard::GetResourceUris()
{
    auto uriVector = std::vector<std::string>();

    auto backgroundImage = GetBackgroundImage();
    if (!backgroundImage.empty())
    {
        uriVector.push_back(backgroundImage);
    }

    for (auto item : m_body)
    {
        item->GetResourceUris(uriVector);
    }

    for (auto item : m_actions)
    {
        item->GetResourceUris(uriVector);
    }

    return uriVector;
}
