// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "TokenExchangeResource.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

std::string TokenExchangeResource::GetId()
{
    return m_id;
}

const std::string TokenExchangeResource::GetId() const
{
    return m_id;
}

void TokenExchangeResource::SetId(std::string id)
{
    m_id = id;
}

std::string TokenExchangeResource::GetUri()
{
    return m_uri;
}

const std::string TokenExchangeResource::GetUri() const
{
    return m_uri;
}

void TokenExchangeResource::SetUri(std::string uri)
{
    m_uri = uri;
}

std::string TokenExchangeResource::GetProviderId()
{
    return m_providerId;
}

const std::string TokenExchangeResource::GetProviderId() const
{
    return m_providerId;
}

void TokenExchangeResource::SetProviderId(std::string providerId)
{
    m_providerId = providerId;
}

// Indicates non-default values have been set. If false, serialization can be safely skipped.
bool TokenExchangeResource::ShouldSerialize() const
{
    return !m_id.empty() || !m_uri.empty() || !m_providerId.empty();
}

std::string TokenExchangeResource::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value TokenExchangeResource::SerializeToJsonValue() const
{
    Json::Value root;

    if (!m_id.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Id)] = m_id;
    }

    if (!m_uri.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Uri)] = m_uri;
    }

    if (!m_providerId.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ProviderId)] = m_providerId;
    }

    return root;
}

std::shared_ptr<TokenExchangeResource> TokenExchangeResource::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<TokenExchangeResource> resource = std::make_shared<TokenExchangeResource>();

    resource->SetId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Id));
    resource->SetUri(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Uri));
    resource->SetProviderId(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ProviderId));

    return resource;
}

std::shared_ptr<TokenExchangeResource> TokenExchangeResource::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return TokenExchangeResource::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
