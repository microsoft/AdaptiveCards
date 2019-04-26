// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "MediaSource.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

MediaSource::MediaSource()
{
}

Json::Value MediaSource::SerializeToJsonValue() const
{
    Json::Value root;

    if (!m_mimeType.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MimeType)] = m_mimeType;
    }

    if (!m_url.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Url)] = m_url;
    }

    return root;
}

std::string MediaSource::GetMimeType() const
{
    return m_mimeType;
}

void MediaSource::SetMimeType(const std::string& value)
{
    m_mimeType = value;
}

std::string MediaSource::GetUrl() const
{
    return m_url;
}

void MediaSource::SetUrl(const std::string& value)
{
    m_url = value;
}

void MediaSource::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    RemoteResourceInformation sourceInfo;
    sourceInfo.url = GetUrl();
    sourceInfo.mimeType = GetMimeType();

    resourceInfo.push_back(sourceInfo);
    return;
}

std::shared_ptr<MediaSource> MediaSourceParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<MediaSource> mediaSource = std::make_shared<MediaSource>();

    mediaSource->SetMimeType(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MimeType, false));
    mediaSource->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, false));

    return mediaSource;
}

std::shared_ptr<MediaSource> MediaSourceParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return MediaSourceParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
