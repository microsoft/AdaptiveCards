// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ContentSource.h"

using namespace AdaptiveCards;

Json::Value ContentSource::SerializeToJsonValue() const
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

std::string ContentSource::GetMimeType() const
{
    return m_mimeType;
}

void ContentSource::SetMimeType(const std::string& value)
{
    m_mimeType = value;
}

std::string ContentSource::GetUrl() const
{
    return m_url;
}

void ContentSource::SetUrl(const std::string& value)
{
    m_url = value;
}

void ContentSource::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    RemoteResourceInformation sourceInfo;
    sourceInfo.url = GetUrl();
    sourceInfo.mimeType = GetMimeType();

    resourceInfo.push_back(sourceInfo);
    return;
}
