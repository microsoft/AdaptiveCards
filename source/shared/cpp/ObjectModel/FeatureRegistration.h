// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ParseUtil.h"

namespace AdaptiveCards
{
constexpr const char* const c_adaptiveCardsFeature = "adaptiveCards";

namespace ParseUtil
{
    std::string ToLowercase(const std::string& value);
}

struct CaseInsensitiveKeyHash
{
    size_t operator()(const std::string& keyVal) const
    {
        return std::hash<std::string>{}(ParseUtil::ToLowercase(keyVal));
    }
};

struct CaseInsensitiveKeyEquals
{
    bool operator()(const std::string& leftVal, const std::string& rightVal) const
    {
        return (ParseUtil::ToLowercase(leftVal) == ParseUtil::ToLowercase(rightVal));
    }
};

class SemanticVersion;
class FeatureRegistration
{
public:
    FeatureRegistration();

    void AddFeature(const std::string& featureName, const std::string& featureVersion);
    void RemoveFeature(const std::string& featureName);
    SemanticVersion GetAdaptiveCardsVersion() const;
    std::string GetFeatureVersion(const std::string& featureName) const;

private:
    std::unordered_map<std::string, std::string, CaseInsensitiveKeyHash, CaseInsensitiveKeyEquals> m_supportedFeatures;
};
} // namespace AdaptiveCards
