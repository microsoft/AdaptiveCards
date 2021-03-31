// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;

namespace AdaptiveCards
{
    /// <summary>
    /// Tracks features supported by a host. When an Adaptive Cards element declares "requires", this is the collection
    /// that gets used.
    /// </summary>
    public class AdaptiveFeatureRegistration
    {
        /// <summary>
        /// Initializes a new AdaptiveFeatureRegistration instance.
        /// </summary>
        public AdaptiveFeatureRegistration()
        {
            features[adaptiveCardFeature] = Globals.ObjectModelVersion;
        }

        /// <summary>
        /// Retrieves the version of a registered feature.
        /// </summary>
        /// <param name="feature">The feature whose version is being requested.</param>
        /// <returns>The version of the feature if it is registered. Otherwise, the empty string.</returns>
        public string Get(string feature)
        {
            if (!features.ContainsKey(feature))
            {
                return "";
            }
            else
            {
                return features[feature];
            }
        }

        /// <summary>
        /// Sets (or registers) a feature to a particular version.
        /// </summary>
        /// <param name="feature">The feature upon which to set a version.</param>
        /// <param name="version">The version to set.</param>
        public void Set(string feature, string version)
        {
            if (feature == adaptiveCardFeature)
            {
                throw new AdaptiveException("Not allowed to override adaptiveCards version");
            }
            else
            {
                features[feature] = version;
            }
        }

        /// <summary>
        /// Removes (or unregisters) a feature.
        /// </summary>
        /// <param name="feature">The feature to remove.</param>
        public void Remove(string feature)
        {
            if (feature == adaptiveCardFeature)
            {
                throw new AdaptiveException("Not allowed to remove adaptiveCards feature");
            }
            else if (features.ContainsKey(feature))
            {
                features.Remove(feature);
            }
        }

        private const string adaptiveCardFeature = "adaptiveCards";
        private Dictionary<string, string> features = new Dictionary<string, string>();
    }
}
