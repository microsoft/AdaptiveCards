// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "AuthCardButton.h"
#include "ParseContext.h"
#include "TokenExchangeResource.h"

namespace AdaptiveSharedNamespace
{
    class Authentication
    {
    public:
        Authentication() : Authentication("", "", nullptr, {}) {}
        Authentication(std::string text, std::string connectionName, const std::shared_ptr<TokenExchangeResource>& tokenExchangeResource, const std::vector<std::shared_ptr<AuthCardButton>>& buttons) :
            m_text(text), m_connectionName(connectionName), m_tokenExchangeResource(tokenExchangeResource), m_buttons(buttons) {}

        std::string GetText();
        void SetText(std::string);

        std::string GetConnectionName();
        void SetConnectionName(std::string);

        std::shared_ptr<TokenExchangeResource> GetTokenExchangeResource();
        void SetTokenExchangeResource(std::shared_ptr<TokenExchangeResource>);

        std::vector<std::shared_ptr<AuthCardButton>>& GetButtons();
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
}
