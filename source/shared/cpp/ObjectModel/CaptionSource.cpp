// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CaptionSource.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

CaptionSource::CaptionSource()
{
}

Json::Value CaptionSource::SerializeToJsonValue() const
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

std::string CaptionSource::GetMimeType() const
{
    return m_mimeType;
}

void CaptionSource::SetMimeType(const std::string& value)
{
    m_mimeType = value;
}

std::string CaptionSource::GetUrl() const
{
    return m_url;
}

void CaptionSource::SetUrl(const std::string& value)
{
    m_url = value;
}

void CaptionSource::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    RemoteResourceInformation sourceInfo;
    sourceInfo.url = GetUrl();
    sourceInfo.mimeType = GetMimeType();

    resourceInfo.push_back(sourceInfo);
    return;
}

std::shared_ptr<CaptionSource> CaptionSourceParser::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<CaptionSource> CaptionSource = std::make_shared<CaptionSource>();

    CaptionSource->SetMimeType(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MimeType, false));
    CaptionSource->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, false));

    return CaptionSource;
}

std::shared_ptr<CaptionSource> CaptionSourceParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return CaptionSourceParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
