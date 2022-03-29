// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseCardElement.h"
#include "ElementParserRegistration.h"
#include "Util.h"

namespace AdaptiveCards
{
class CaptionSource
{
public:
    CaptionSource();
    CaptionSource(const CaptionSource&) = default;
    CaptionSource(CaptionSource&&) = default;
    CaptionSource& operator=(const CaptionSource&) = default;
    CaptionSource& operator=(CaptionSource&&) = default;
    virtual ~CaptionSource() = default;

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

class CaptionSourceParser
{
public:
    CaptionSourceParser() = default;
    CaptionSourceParser(const CaptionSourceParser&) = default;
    CaptionSourceParser(CaptionSourceParser&&) = default;
    CaptionSourceParser& operator=(const CaptionSourceParser&) = default;
    CaptionSourceParser& operator=(CaptionSourceParser&&) = default;
    virtual ~CaptionSourceParser() = default;

    static std::shared_ptr<CaptionSource> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<CaptionSource> DeserializeFromString(ParseContext& context, const std::string& jsonString);
};
} // namespace AdaptiveCards
