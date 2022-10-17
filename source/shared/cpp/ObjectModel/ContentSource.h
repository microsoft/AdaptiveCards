// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"

namespace AdaptiveCards
{
class ContentSource
{
public:
    virtual Json::Value SerializeToJsonValue() const;

    template <typename T>
    static std::shared_ptr<T> Deserialize(ParseContext& context, const Json::Value& root);

    std::string GetMimeType() const;
    void SetMimeType(const std::string& value);

    std::string GetUrl() const;
    void SetUrl(const std::string& value);

    virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo);

private:
    std::string m_mimeType;
    std::string m_url;
};

template <typename T>
std::shared_ptr<T> ContentSource::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<T> base = std::make_shared<T>();
    std::shared_ptr<ContentSource> contentSource = std::static_pointer_cast<ContentSource>(base);

    contentSource->SetMimeType(ParseUtil::GetString(json, AdaptiveCardSchemaKey::MimeType, false));
    contentSource->SetUrl(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Url, false));

    return base;
}
} // namespace AdaptiveCards
