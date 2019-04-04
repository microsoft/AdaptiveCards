#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class FeatureRegistration
    {
    public:
        FeatureRegistration();

        void AddFeature(const std::string& featureName, const std::string& featureVersion);
        void RemoveFeature(const std::string& featureName);
        std::string GetFeatureVersion(const std::string& featureName) const;

    private:
        std::unordered_map<std::string, std::string> m_supportedFeatures;
    };
}
