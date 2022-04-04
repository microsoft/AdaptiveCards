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

    std::string GetMimeType() const;
    void SetMimeType(const std::string& value);

    std::string GetUrl() const;
    void SetUrl(const std::string& value);

    virtual void GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo);

private:
    std::string m_mimeType;
    std::string m_url;
};
} // namespace AdaptiveCards
