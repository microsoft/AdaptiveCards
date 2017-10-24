using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [JsonConverter(typeof(ToStringJsonConverter))]
    public class AdaptiveSchemaVersion
    {
        public int Major { get; private set; }
        public int Minor { get; private set; }

        public AdaptiveSchemaVersion(int major, int minor)
        {
            Major = major;
            Minor = minor;
        }

        public override string ToString()
        {
            return $"{Major}.{Minor}";
        }

        /// <summary>
        /// Implicit converter to support assinging a string to properties.
        /// This is for back-compat since the Version property used to be a string, so developers were providing strings instead of the class.
        /// </summary>
        /// <param name="versionString"></param>
        public static implicit operator AdaptiveSchemaVersion(string versionString)
        {
            if (versionString == null)
            {
                return null;
            }

            string[] splits = versionString.Split('.');

            int major = int.Parse(splits[0]);

            int minor = 0;
            if (splits.Length > 1)
            {
                minor = int.Parse(splits[1]);
            }

            return new AdaptiveSchemaVersion(major, minor);
        }
    }
}
