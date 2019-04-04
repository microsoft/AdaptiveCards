#pragma once

#include "pch.h"

namespace AdaptiveSharedNamespace
{
    class FeatureRegistration
    {
    public:
        FeatureRegistration();

        void AddFeature(std::string const& featureName, const std::string& featureVersion);
        void RemoveFeature(std::string const& featureName);
        std::string GetFeatureVersion(const std::string& featureName) const;

    private:
        std::unordered_map<std::string, std::string> m_supportedFeatures;
    };
}
