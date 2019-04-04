#include "pch.h"
#include "FeatureRegistration.h"

#include "AdaptiveCardParseException.h"
#include "SemanticVersion.h"

namespace AdaptiveSharedNamespace
{
    FeatureRegistration::FeatureRegistration() : m_supportedFeatures{}
    {
    }

    void FeatureRegistration::AddFeature(std::string const& featureName, const std::string& featureVersion)
    {
        // first, validate the version string. we only support "*" or a semantic version string (e.g. 1.2.3.4)
        if (featureVersion != "*")
        {
            // the below will throw if the version is invalid
            SemanticVersion version(featureVersion);
        }

        if (m_supportedFeatures.find(featureName) == m_supportedFeatures.end())
        {
            m_supportedFeatures[featureName] = featureVersion;
        }
        else
        {
            // only allow a duplicate add attempt if the version is the same.
            if (m_supportedFeatures[featureName] != featureVersion)
            {
                throw AdaptiveCardParseException(ErrorStatusCode::DuplicateFeatureName,
                                                 "Attempting to add a feature with a differing version");
            }
        }
    }

    void FeatureRegistration::RemoveFeature(std::string const& featureName)
    {
        m_supportedFeatures.erase(featureName);
    }

    std::string FeatureRegistration::GetFeatureVersion(const std::string& featureName) const
    {
        if (m_supportedFeatures.find(featureName) != m_supportedFeatures.end())
        {
            return m_supportedFeatures.at(featureName);
        }
        else
        {
            return "";
        }
    }
}
