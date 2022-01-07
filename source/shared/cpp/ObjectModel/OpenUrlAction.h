// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "ActionParserRegistration.h"

namespace AdaptiveCards
{
class OpenUrlAction : public BaseActionElement
{
public:
    OpenUrlAction();
    OpenUrlAction(const OpenUrlAction&) = default;
    OpenUrlAction(OpenUrlAction&&) = default;
    OpenUrlAction& operator=(const OpenUrlAction&) = default;
    OpenUrlAction& operator=(OpenUrlAction&&) = default;
    ~OpenUrlAction() = default;

    Json::Value SerializeToJsonValue() const override;

    std::string GetUrl() const;
    void SetUrl(const std::string& value);

private:
    void PopulateKnownPropertiesSet();

    std::string m_url;
};

class OpenUrlActionParser : public ActionElementParser
{
public:
    OpenUrlActionParser() = default;
    OpenUrlActionParser(const OpenUrlActionParser&) = default;
    OpenUrlActionParser(OpenUrlActionParser&&) = default;
    OpenUrlActionParser& operator=(const OpenUrlActionParser&) = default;
    OpenUrlActionParser& operator=(OpenUrlActionParser&&) = default;
    virtual ~OpenUrlActionParser() = default;

    std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
    std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
