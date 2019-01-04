#include "pch.h"
#include "Media.h"
#include "ParseUtil.h"
#include "ParseContext.h"

using namespace AdaptiveSharedNamespace;

Media::Media() : BaseCardElement(CardElementType::Media)
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

void Media::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Poster),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::AltText),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Sources)});
}

void Media::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    RemoteResourceInformation posterResourceInfo;
    posterResourceInfo.url = GetPoster();
    posterResourceInfo.mimeType = "image";
    resourceInfo.push_back(posterResourceInfo);

    auto sources = GetSources();
    for (auto source : sources)
    {
        source->GetResourceInformation(resourceInfo);
    }
    return;
}

std::shared_ptr<BaseCardElement> MediaParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::Media);

    std::shared_ptr<Media> media = BaseCardElement::Deserialize<Media>(context, json);
    context.PushElement({ media->GetId(), media->GetInternalId(), false});
    media->SetPoster(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Poster, false));
    media->SetAltText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::AltText, false));

    auto sources = ParseUtil::GetElementCollectionOfSingleType<MediaSource>(
        context, json, AdaptiveCardSchemaKey::Sources, MediaSourceParser::Deserialize, true);

    std::string mimeBaseType;
    for (auto source : sources)
    {
        std::string currentMimeType = source->GetMimeType();

        std::string slash("/");
        const size_t slashPosition = currentMimeType.find(slash, 0);
        std::string currentMimeBaseType = currentMimeType.substr(0, slashPosition);

        if (mimeBaseType.empty())
        {
            mimeBaseType = currentMimeBaseType;
        }
        else if (mimeBaseType != currentMimeBaseType)
        {
            context.warnings.push_back(
                std::make_shared<AdaptiveCardParseWarning>(AdaptiveSharedNamespace::WarningStatusCode::InvalidMediaMix,
                                                           "Media element containing a mix of audio and video was dropped"));
            return nullptr;
        }
    }

    media->m_sources = std::move(sources);
    context.PopElement();

    return media;
}

std::shared_ptr<BaseCardElement> MediaParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return MediaParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
