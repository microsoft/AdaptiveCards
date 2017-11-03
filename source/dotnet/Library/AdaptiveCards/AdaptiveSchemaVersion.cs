using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [JsonConverter(typeof(AdaptiveSchemaJsonConverter))]
    public class AdaptiveSchemaVersion : IComparable<AdaptiveSchemaVersion>
    {     
        public int Major { get; }

        public int Minor { get; }

        public AdaptiveSchemaVersion(string versionString)
        {
            if (versionString == null)
                throw new ArgumentException(nameof(versionString));

            var splits = versionString.Split('.');
            var major = int.Parse(splits[0]);

            var minor = 0;
            if (splits.Length > 1)
            {
                minor = int.Parse(splits[1]);
            }

            Major = major;
            Minor = minor;
        }

        public AdaptiveSchemaVersion(int major, int minor)
        { 
            Major = major;
            Minor = minor;
        }

        public override string ToString()
        {
            return $"{Major}.{Minor}";
        }

        public override bool Equals(object obj)
        {
            var version = obj as AdaptiveSchemaVersion;
            return version != null &&
                   Major == version.Major &&
                   Minor == version.Minor;
        }

        public override int GetHashCode()
        {
            var hashCode = 317314336;
            hashCode = hashCode * -1521134295 + Major.GetHashCode();
            hashCode = hashCode * -1521134295 + Minor.GetHashCode();
            return hashCode;
        }

        public static implicit operator AdaptiveSchemaVersion(string versionString)
        {
            return new AdaptiveSchemaVersion(versionString);
        }

        public static bool operator ==(AdaptiveSchemaVersion version1, AdaptiveSchemaVersion version2)
        {
            return EqualityComparer<AdaptiveSchemaVersion>.Default.Equals(version1, version2);
        }

        public static bool operator !=(AdaptiveSchemaVersion version1, AdaptiveSchemaVersion version2)
        {
            return !(version1 == version2);
        }

        public int CompareTo(AdaptiveSchemaVersion other)
        {
            if (ReferenceEquals(this, other)) return 0;
            if (ReferenceEquals(null, other)) return 1;
            var majorComparison = Major.CompareTo(other.Major);
            if (majorComparison != 0) return majorComparison;
            return Minor.CompareTo(other.Minor);
        }

        public static bool operator <(AdaptiveSchemaVersion left, AdaptiveSchemaVersion right)
        {
            return Comparer<AdaptiveSchemaVersion>.Default.Compare(left, right) < 0;
        }

        public static bool operator >(AdaptiveSchemaVersion left, AdaptiveSchemaVersion right)
        {
            return Comparer<AdaptiveSchemaVersion>.Default.Compare(left, right) > 0;
        }

        public static bool operator <=(AdaptiveSchemaVersion left, AdaptiveSchemaVersion right)
        {
            return Comparer<AdaptiveSchemaVersion>.Default.Compare(left, right) <= 0;
        }

        public static bool operator >=(AdaptiveSchemaVersion left, AdaptiveSchemaVersion right)
        {
            return Comparer<AdaptiveSchemaVersion>.Default.Compare(left, right) >= 0;
        }

        internal class AdaptiveSchemaJsonConverter : JsonConverter
        {
            public override bool CanConvert(Type objectType)
            {
                return objectType == typeof(AdaptiveSchemaVersion);
            }

            public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
            {
                writer.WriteValue(value.ToString());
            }

            public override bool CanRead => true;

            public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
            {
                return new AdaptiveSchemaVersion((string)reader.Value);
            }
        }
    }
}
