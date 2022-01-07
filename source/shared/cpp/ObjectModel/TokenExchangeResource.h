// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
class TokenExchangeResource
{
public:
    TokenExchangeResource()
    {
    }
    TokenExchangeResource(std::string id, std::string uri, std::string providerId) :
        m_id(id), m_uri(uri), m_providerId(providerId)
    {
    }

    std::string GetId();
    const std::string GetId() const;
    void SetId(std::string);

    std::string GetUri();
    const std::string GetUri() const;
    void SetUri(std::string);

    std::string GetProviderId();
    const std::string GetProviderId() const;
    void SetProviderId(std::string);

    bool ShouldSerialize() const;
    std::string Serialize() const;
    Json::Value SerializeToJsonValue() const;

    static std::shared_ptr<TokenExchangeResource> Deserialize(ParseContext& context, const Json::Value& json);
    static std::shared_ptr<TokenExchangeResource> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::string m_id;
    std::string m_uri;
    std::string m_providerId;
};
} // namespace AdaptiveCards
