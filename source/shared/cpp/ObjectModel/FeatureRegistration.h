// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    constexpr const char* const c_adaptiveCardsFeature = "adaptiveCards";

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
        std::unordered_map<std::string, std::string> m_supportedFeatures;
    };
}
