// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "FeatureRegistration.h"

#include "AdaptiveCardParseException.h"
#include "SemanticVersion.h"

namespace AdaptiveSharedNamespace
{
    FeatureRegistration::FeatureRegistration() :
        m_supportedFeatures{{AdaptiveSharedNamespace::c_adaptiveCardsFeature, c_sharedModelVersion}}
    {
    }

    void FeatureRegistration::AddFeature(std::string const& featureName, const std::string& featureVersion)
    {
        // first, validate the version string. we only support "*" or a semantic version string (e.g. "1.0", or "1.2.3.4")
        if (featureVersion != "*")
        {
            // the below will throw if the version is invalid
            const SemanticVersion version(featureVersion);
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
                throw AdaptiveCardParseException(ErrorStatusCode::InvalidPropertyValue,
                                                 "Attempting to add a feature with a differing version");
            }
        }
    }

    void FeatureRegistration::RemoveFeature(const std::string& featureName)
    {
        if (featureName == AdaptiveSharedNamespace::c_adaptiveCardsFeature)
        {
            throw AdaptiveCardParseException(ErrorStatusCode::UnsupportedParserOverride,
                                             "Removing the Adaptive Cards feature is unsupported");
        }

        m_supportedFeatures.erase(featureName);
    }

    SemanticVersion FeatureRegistration::GetAdaptiveCardsVersion() const
    {
        SemanticVersion adaptiveCardsVersion{GetFeatureVersion(AdaptiveSharedNamespace::c_adaptiveCardsFeature)};
        return adaptiveCardsVersion;
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
