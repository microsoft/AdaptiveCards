// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;
using System.Xml.Serialization;
using System.ComponentModel;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the AdaptiveCards schema version.
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    [JsonConverter(typeof(AdaptiveSchemaJsonConverter))]
    public class AdaptiveSchemaVersion : IComparable<AdaptiveSchemaVersion>
    {
        /// <summary>
        /// Major version number.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public int Major { get; set; }

        /// <summary>
        /// Minor version number.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public int Minor { get; set; }

        /// <summary>
        /// Initializes an empty <see cref="AdaptiveSchemaVersion"/>.
        /// </summary>
        public AdaptiveSchemaVersion() { }

        /// <summary>
        /// Initializes an <see cref="AdaptiveSchemaVersion"/> instance.
        /// </summary>
        /// <param name="versionString">A string representing the schema version.</param>
        public AdaptiveSchemaVersion(string versionString)
        {
            if (versionString == null)
            {
                throw new ArgumentException(nameof(versionString));
            }

            try
            {
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
            catch (Exception ex)
            {
                throw new AdaptiveSerializationException($"'{versionString}' is not a valid version identifier", ex);
            }
        }

        /// <summary>
        /// Iniializes an <see cref="AdaptiveSchemaVersion"/> instance.
        /// </summary>
        /// <param name="major">The schema major version.</param>
        /// <param name="minor">The schema minor version.</param>
        public AdaptiveSchemaVersion(int major, int minor)
        {
            Major = major;
            Minor = minor;
        }

        /// <inheritdoc />
        public override string ToString()
        {
            return $"{Major}.{Minor}";
        }

        /// <inheritdoc />
        public override bool Equals(object obj)
        {
            var version = obj as AdaptiveSchemaVersion;
            return version != null &&
                   Major == version.Major &&
                   Minor == version.Minor;
        }

        /// <inheritdoc />
        public override int GetHashCode()
        {
            var hashCode = 317314336;
            hashCode = hashCode * -1521134295 + Major.GetHashCode();
            hashCode = hashCode * -1521134295 + Minor.GetHashCode();
            return hashCode;
        }

        /// <summary>
        /// Implicit conversion operator from <see cref="string"/> to <see cref="AdaptiveSchemaVersion"/>.
        /// </summary>
        /// <param name="versionString">A string representing the schema version.</param>
        public static implicit operator AdaptiveSchemaVersion(string versionString)
        {
            return new AdaptiveSchemaVersion(versionString);
        }

        /// <summary>
        /// Equality comparison operator.
        /// </summary>
        public static bool operator ==(AdaptiveSchemaVersion version1, AdaptiveSchemaVersion version2)
        {
            return EqualityComparer<AdaptiveSchemaVersion>.Default.Equals(version1, version2);
        }

        /// <summary>
        /// Inequality comparison operator.
        /// </summary>
        public static bool operator !=(AdaptiveSchemaVersion version1, AdaptiveSchemaVersion version2)
        {
            return !(version1 == version2);
        }

        /// <summary>
        /// Compares this instance to another instance.
        /// </summary>
        /// <param name="other">AdaptiveSchemaVersion instance to compare to.</param>
        /// <returns>0 iff the other AdaptiveSchemaVersion is equal to this one.</returns>
        public int CompareTo(AdaptiveSchemaVersion other)
        {
            if (ReferenceEquals(this, other))
            {
                return 0;
            }

            if (ReferenceEquals(null, other))
            {
                return 1;
            }

            var majorComparison = Major.CompareTo(other.Major);
            if (majorComparison != 0)
            {
                return majorComparison;
            }

            return Minor.CompareTo(other.Minor);
        }

        /// <summary>
        /// Less-than operator.
        /// </summary>
        public static bool operator <(AdaptiveSchemaVersion left, AdaptiveSchemaVersion right)
        {
            return Comparer<AdaptiveSchemaVersion>.Default.Compare(left, right) < 0;
        }

        /// <summary>
        /// Greater-than operator.
        /// </summary>
        public static bool operator >(AdaptiveSchemaVersion left, AdaptiveSchemaVersion right)
        {
            return Comparer<AdaptiveSchemaVersion>.Default.Compare(left, right) > 0;
        }

        /// <summary>
        /// Less-than-or-equal operator.
        /// </summary>
        public static bool operator <=(AdaptiveSchemaVersion left, AdaptiveSchemaVersion right)
        {
            return Comparer<AdaptiveSchemaVersion>.Default.Compare(left, right) <= 0;
        }

        /// <summary>
        /// Greater-than-or-equal operator.
        /// </summary>
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
