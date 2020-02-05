// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Controls the vertical size (height) of element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveHeightType>), true)]

    public enum AdaptiveHeightType
    {
        /// <summary>
        ///     The height of the element is wraps the element content
        /// </summary>
        Auto,

        /// <summary>
        ///     The height of the element uses as much space as it is able to
        /// </summary>
        Stretch,

        /// <summary>
        ///     The height of the element was explicitly specified (only for Image elements)
        /// </summary>
        Pixel
    }


    public class AdaptiveHeight : IEquatable<AdaptiveHeight>
    {
        public static AdaptiveHeight Auto { get; } = new AdaptiveHeight(AdaptiveHeightType.Auto);

        public static AdaptiveHeight Stretch { get; } = new AdaptiveHeight(AdaptiveHeightType.Stretch);

        public AdaptiveHeight()
        {
        }

        public AdaptiveHeight(uint px)
        {
            HeightType = AdaptiveHeightType.Pixel;
            this.Unit = px;
        }

        public AdaptiveHeight(AdaptiveHeightType heightType)
        {
            HeightType = heightType;
            Unit = null;
        }


        [JsonProperty("heightType")]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        public AdaptiveHeightType HeightType { get; set; }

        [JsonProperty("unit")]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public uint? Unit { get; set; }

#if !NETSTANDARD1_3
        [XmlAttribute("Unit")]
        [JsonIgnore]
        public uint UnitXml { get { return Unit.HasValue ? Unit.Value : 0; } set { Unit = value; } }
        public bool ShouldSerializeUnitXml() => Unit.HasValue;
#endif

        public bool IsPixel()
        {
            return HeightType == AdaptiveHeightType.Pixel;
        }

        public bool ShouldSerializeAdaptiveHeight()
        {
            if (HeightType == AdaptiveHeightType.Auto)
            {
                return false;
            }

            if (HeightType == AdaptiveHeightType.Pixel)
            {
                if (!Unit.HasValue)
                {
                    return false;
                }
                else if (Unit.Value == 0)
                {
                    return false;
                }
            }
            return true;
        }

        public static bool operator ==(AdaptiveHeight ah1, AdaptiveHeight ah2)
        {
            return ah1.Equals(ah2);
        }

        public static bool operator !=(AdaptiveHeight ah1, AdaptiveHeight ah2)
        {
            return !ah1.Equals(ah2);
        }
        public override int GetHashCode()
        {
            if (!Unit.HasValue)
            {
                return -1;
            }
            return (int)(Unit.Value * 10 + (int)HeightType);
        }

        public override bool Equals(object obj)
        {
            return this.Equals(obj as AdaptiveHeight);
        }

        public Boolean Equals(AdaptiveHeight other)
        {
            if (this.HeightType == other.HeightType)
            {
                if (this.HeightType == AdaptiveHeightType.Pixel)
                {
                    return this.Unit == other.Unit;
                }
                return true;
            }
            return false;
        }
    }
}
