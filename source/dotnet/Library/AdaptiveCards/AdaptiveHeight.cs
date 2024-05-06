// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls the vertical size (height) of element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveHeightType>), true)]

    public enum AdaptiveHeightType
    {
        /// <summary>
        /// The height of the element matches element content.
        /// </summary>
        Auto,

        /// <summary>
        /// The height of the element uses as much space as it is able to.
        /// </summary>
        Stretch,

        /// <summary>
        /// The height of the element was explicitly specified (only for Image elements).
        /// </summary>
        Pixel
    }

    /// <summary>
    /// Represents the height property in Adaptive Cards.
    /// </summary>
    public class AdaptiveHeight : IEquatable<AdaptiveHeight>
    {
        /// <summary>
        /// Returns a new AdaptiveHeight instance initialized for the <see cref="AdaptiveHeightType.Auto"/> height type.
        /// </summary>
        public static AdaptiveHeight Auto { get; } = new AdaptiveHeight(AdaptiveHeightType.Auto);

        /// <summary>
        /// Returns a new AdaptiveHeight instance initialized for the <see cref="AdaptiveHeightType.Stretch"/> height type.
        /// </summary>
        public static AdaptiveHeight Stretch { get; } = new AdaptiveHeight(AdaptiveHeightType.Stretch);

        /// <summary>
        /// Initializes an empty AdaptiveHeight instance.
        /// </summary>
        public AdaptiveHeight()
        {
        }

        /// <summary>
        /// Initializes an AdaptiveHeight instance with the given string "auto"|"stretch"|"100px"
        /// </summary>
        /// <param name="value">enumeration value or pixel .</param>
        public AdaptiveHeight(string value)
        {
            HeightType = AdaptiveHeightType.Auto;
            if (!String.IsNullOrEmpty(value))
            {
                if (value.EndsWith("px"))
                {
                    value = value.Substring(0, value.Length - 2);
                    // NOTE: We want to throw exception here if this is not valid as the Converter then will generate a warning on the value.
                    Unit = uint.Parse(value);
                    HeightType = AdaptiveHeightType.Pixel;
                }
                else if (uint.TryParse(value, out var val))
                {
                    HeightType = AdaptiveHeightType.Pixel;
                    Unit = val;
                }
                else
                {
                    // NOTE: We want to throw exception here if this is not valid as the Converter then will generate a warning on the value.
                    HeightType = (AdaptiveHeightType)Enum.Parse(typeof(AdaptiveHeightType), value, ignoreCase: true);
                }
            }
        }

        /// <summary>
        /// Parse string to adaptive height
        /// </summary>
        /// <param name="value">string value</param>
        /// <returns>AdaptiveHeight</returns>
        public static AdaptiveHeight Parse(string value)
        {
            return new AdaptiveHeight(value);
        }

        /// <summary>
        /// Initializes an AdaptiveHeight instance with the given pixel size.
        /// </summary>
        /// <param name="px">The device-independent pixel size to use.</param>
        public AdaptiveHeight(uint px)
        {
            HeightType = AdaptiveHeightType.Pixel;
            this.Unit = px;
        }

        /// <summary>
        /// Initializes an AdaptiveHeight instance with the given <see cref="AdaptiveHeightType"/>.
        /// </summary>
        /// <param name="heightType">The AdaptiveHeightType to use.</param>
        public AdaptiveHeight(AdaptiveHeightType heightType)
        {
            HeightType = heightType;
            Unit = null;
        }

        /// <summary>
        /// The <see cref="AdaptiveHeightType"/> this instance represents.
        /// </summary>
        [JsonProperty("heightType")]
        [XmlAttribute]
        public AdaptiveHeightType HeightType { get; set; }

        /// <summary>
        /// The specific height to use (only valid for the <see cref="AdaptiveHeightType.Pixel"/> type).
        /// </summary>
        [JsonProperty("unit")]
        [XmlIgnore]
        public uint? Unit { get; set; }

        /// <summary>
        /// Helper to aid in XML serialization of the <see cref="AdaptiveHeight.Unit"/> property.
        /// </summary>
        [XmlAttribute("Unit")]
        [JsonIgnore]
        public uint UnitXml { get { return Unit.HasValue ? Unit.Value : 0; } set { Unit = value; } }

        /// <summary>
        /// Determines whether to serialize the <see cref="AdaptiveHeight.UnitXml"/> property.
        /// </summary>
        public bool ShouldSerializeUnitXml() => Unit.HasValue;

        /// <summary>
        /// Returns true if this <see cref="AdaptiveHeight"/> instance represents the <see
        /// cref="AdaptiveHeightType.Pixel"/> <see cref="AdaptiveHeightType"/>.
        /// </summary>
        public bool IsPixel()
        {
            return HeightType == AdaptiveHeightType.Pixel;
        }

        /// <summary>
        /// Determines whether this <see cref="AdaptiveHeight"/> instance should be serialized.
        /// </summary>
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

        /// <summary>
        /// Assignment operator with uint pixels
        /// </summary>
        /// <param name="value"></param>
        public static implicit operator AdaptiveHeight(uint value)
        {
            return new AdaptiveHeight(value);
        }

        /// <summary>
        /// Assignment operator with type
        /// </summary>
        /// <param name="value"></param>
        public static implicit operator AdaptiveHeight(AdaptiveHeightType value)
        {
            return new AdaptiveHeight(value);
        }

        /// <summary>
        /// Assignment operator with string (100x)
        /// </summary>
        /// <param name="value"></param>
        public static implicit operator AdaptiveHeight(string value)
        {
            return new AdaptiveHeight(value);
        }

        /// <inheritdoc />
        public static bool operator ==(AdaptiveHeight ah1, AdaptiveHeight ah2)
        {
            return ah1.Equals(ah2);
        }

        /// <inheritdoc />
        public static bool operator !=(AdaptiveHeight ah1, AdaptiveHeight ah2)
        {
            return !ah1.Equals(ah2);
        }

        /// <inheritdoc />
        public override int GetHashCode()
        {
            if (!Unit.HasValue)
            {
                return -1;
            }
            return (int)(Unit.Value * 10 + (int)HeightType);
        }

        /// <inheritdoc />
        public override bool Equals(object obj)
        {
            return this.Equals(obj as AdaptiveHeight);
        }

        /// <inheritdoc />
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

        /// <inheritdoc/>
        public override string ToString()
        {
            if (HeightType == AdaptiveHeightType.Stretch)
                return "stretch";
            if (HeightType == AdaptiveHeightType.Auto)
                return "auto";
            return $"{Unit}px";
        }
    }
}
