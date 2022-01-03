// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "AuthCardButton.h"
#include "ParseContext.h"
#include "TokenExchangeResource.h"

namespace AdaptiveCards
{
class Authentication
{
public:
    Authentication()
    {
    }
    Authentication(
        std::string text,
        std::string connectionName,
        const std::shared_ptr<TokenExchangeResource>& tokenExchangeResource,
        const std::vector<std::shared_ptr<AuthCardButton>>& buttons) :
        m_text(text),
        m_connectionName(connectionName), m_tokenExchangeResource(tokenExchangeResource), m_buttons(buttons)
    {
    }

    std::string GetText();
    const std::string GetText() const;
    void SetText(std::string);

    std::string GetConnectionName();
    const std::string GetConnectionName() const;
    void SetConnectionName(std::string);

    std::shared_ptr<TokenExchangeResource> GetTokenExchangeResource();
    const std::shared_ptr<TokenExchangeResource> GetTokenExchangeResource() const;
    void SetTokenExchangeResource(std::shared_ptr<TokenExchangeResource>);

    std::vector<std::shared_ptr<AuthCardButton>>& GetButtons();
    const std::vector<std::shared_ptr<AuthCardButton>>& GetButtons() const;
    void SetButtons(std::vector<std::shared_ptr<AuthCardButton>>);

    bool ShouldSerialize() const;
    std::string Serialize() const;
    Json::Value SerializeToJsonValue() const;

    static std::shared_ptr<Authentication> Deserialize(ParseContext& context, const Json::Value& json);
    static std::shared_ptr<Authentication> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::string m_text;
    std::string m_connectionName;
    std::shared_ptr<TokenExchangeResource> m_tokenExchangeResource;
    std::vector<std::shared_ptr<AuthCardButton>> m_buttons;
};
} // namespace AdaptiveCards
