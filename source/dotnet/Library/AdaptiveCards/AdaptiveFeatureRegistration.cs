using System.Collections.Generic;

namespace AdaptiveCards
{
    public class AdaptiveFeatureRegistration
    {
        public AdaptiveFeatureRegistration()
        {
            features[adaptiveCardFeature] = Globals.ObjectModelVersion;
        }

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
