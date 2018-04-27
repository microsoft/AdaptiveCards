#include "pch.h"
#include "Media.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

Media::Media() :
    BaseCardElement(CardElementType::Media)
{
    PopulateKnownPropertiesSet();
}

Json::Value Media::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    if (!m_poster.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Poster)] = m_poster;
    }

    if (!m_altText.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AltText)] = GetAltText();
    }

    std::string sourcesPropertyName = AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Sources);
    root[sourcesPropertyName] = Json::Value(Json::arrayValue);
    for (const auto& source : m_sources)
    {
        root[sourcesPropertyName].append(source->SerializeToJsonValue());
    }

    return root;
}

std::string Media::GetPoster() const
{
    return m_poster;
}

void Media::SetPoster(const std::string& value)
{
    m_poster = value;
}

std::string Media::GetAltText() const
{
    return m_altText;
}

void Media::SetAltText(const std::string& value)
{
    m_altText = value;
}

std::vector<std::shared_ptr<MediaSource>>& Media::GetSources()
{
    return m_sources;
}

std::shared_ptr<BaseCardElement> MediaParser::Deserialize(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::Media);

    std::shared_ptr<Media> media = BaseCardElement::Deserialize<Media>(json);

    media->SetPoster(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Poster, false));
    media->SetAltText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::AltText, false));

    auto sources = ParseUtil::GetElementCollectionOfSingleType<MediaSource>(elementParserRegistration, actionParserRegistration, json, AdaptiveCardSchemaKey::Sources, MediaSourceParser::Deserialize, true);
    media->m_sources= std::move(sources);

    return media;
}

std::shared_ptr<BaseCardElement> MediaParser::DeserializeFromString(
    std::shared_ptr<ElementParserRegistration> elementParserRegistration,
    std::shared_ptr<ActionParserRegistration> actionParserRegistration,
    const std::string& jsonString)
{
    return MediaParser::Deserialize(elementParserRegistration, actionParserRegistration, ParseUtil::GetJsonValueFromString(jsonString));
}

void Media::PopulateKnownPropertiesSet() 
{
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Poster));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AltText));
    m_knownProperties.insert(AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Sources));
}
