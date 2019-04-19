using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveFeatureRegistration
    {
        public AdaptiveFeatureRegistration()
        {
            features[adaptiveCardFeature] = "1.2";
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

        private readonly string adaptiveCardFeature = "adaptiveCards";
        private Dictionary<string, string> features = new Dictionary<string, string>();
    }
}
