// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls the vertical size (Width) of element.
    /// </summary>
    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveWidthType>), true)]

    public enum AdaptiveWidthType
    {
        /// <summary>
        /// The Width of the element matches element content.
        /// </summary>
        Auto,

        /// <summary>
        /// The Width of the element uses as much space as it is able to.
        /// </summary>
        Stretch,

        /// <summary>
        /// The Width of the element was explicitly specified (only for Image elements).
        /// </summary>
        Pixel
    }


    /// <summary>
    /// Represents the Width property in Adaptive Cards.
    /// </summary>
    public class AdaptiveWidth : IEquatable<AdaptiveWidth>
    {
        /// <summary>
        /// Returns a new AdaptiveWidth instance initialized for the <see cref="AdaptiveWidthType.Auto"/> Width type.
        /// </summary>
        public static AdaptiveWidth Auto { get; } = new AdaptiveWidth(AdaptiveWidthType.Auto);

        /// <summary>
        /// Returns a new AdaptiveWidth instance initialized for the <see cref="AdaptiveWidthType.Stretch"/> Width type.
        /// </summary>
        public static AdaptiveWidth Stretch { get; } = new AdaptiveWidth(AdaptiveWidthType.Stretch);

        /// <summary>
        /// Initializes an empty AdaptiveWidth instance.
        /// </summary>
        public AdaptiveWidth()
        {
        }

        /// <summary>
        /// Initializes an AdaptiveWidth instance with the given string "auto"|"stretch"|"100px"
        /// </summary>
        /// <param name="value">enumeration value or pixel .</param>
        public AdaptiveWidth(string value)
        {
            WidthType = AdaptiveWidthType.Auto;
            if (!String.IsNullOrEmpty(value))
            {
                if (value.EndsWith("px"))
                {
                    value = value.Substring(0, value.Length - 2);
                    // NOTE: We want to throw exception here if this is not valid as the Converter then will generate a warning on the value.
                    Unit = uint.Parse(value);
                    WidthType = AdaptiveWidthType.Pixel;
                }
                else if (uint.TryParse(value, out var val))
                {
                    WidthType = AdaptiveWidthType.Pixel;
                    Unit = val;
                }
                else
                {
                    // NOTE: We want to throw exception here if this is not valid as the Converter then will generate a warning on the value.
                    WidthType = (AdaptiveWidthType)Enum.Parse(typeof(AdaptiveWidthType), value, ignoreCase: true);
                }
            }
        }

        /// <summary>
        /// Parse string into AdaptiveWidth
        /// </summary>
        /// <param name="value">string</param>
        /// <returns>AdaptiveWidth</returns>
        public static AdaptiveWidth Parse(string value)
        {
            return new AdaptiveWidth(value);
        }

        /// <summary>
        /// Initializes an AdaptiveWidth instance with the given pixel size.
        /// </summary>
        /// <param name="px">The device-independent pixel size to use.</param>
        public AdaptiveWidth(uint px)
        {
            WidthType = AdaptiveWidthType.Pixel;
            this.Unit = px;
        }

        /// <summary>
        /// Initializes an AdaptiveWidth instance with the given <see cref="AdaptiveWidthType"/>.
        /// </summary>
        /// <param name="widthType">The AdaptiveWidthType to use.</param>
        public AdaptiveWidth(AdaptiveWidthType widthType)
        {
            WidthType = widthType;
            Unit = null;
        }

        /// <summary>
        /// The <see cref="AdaptiveWidthType"/> this instance represents.
        /// </summary>
        [JsonProperty("WidthType")]
        [XmlAttribute]
        public AdaptiveWidthType WidthType { get; set; }

        /// <summary>
        /// The specific Width to use (only valid for the <see cref="AdaptiveWidthType.Pixel"/> type).
        /// </summary>
        [JsonProperty("unit")]
        [XmlIgnore]
        public uint? Unit { get; set; }

        /// <summary>
        /// Helper to aid in XML serialization of the <see cref="AdaptiveWidth.Unit"/> property.
        /// </summary>
        [XmlAttribute("Unit")]
        [JsonIgnore]
        public uint UnitXml { get { return Unit.HasValue ? Unit.Value : 0; } set { Unit = value; } }

        /// <summary>
        /// Determines whether to serialize the <see cref="AdaptiveWidth.UnitXml"/> property.
        /// </summary>
        public bool ShouldSerializeUnitXml() => Unit.HasValue;

        /// <summary>
        /// Returns true if this <see cref="AdaptiveWidth"/> instance represents the <see
        /// cref="AdaptiveWidthType.Pixel"/> <see cref="AdaptiveWidthType"/>.
        /// </summary>
        public bool IsPixel()
        {
            return WidthType == AdaptiveWidthType.Pixel;
        }

        /// <summary>
        /// Determines whether this <see cref="AdaptiveWidth"/> instance should be serialized.
        /// </summary>
        public bool ShouldSerializeAdaptiveWidth()
        {
            if (WidthType == AdaptiveWidthType.Auto)
            {
                return false;
            }

            if (WidthType == AdaptiveWidthType.Pixel)
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
        public static implicit operator AdaptiveWidth(uint value)
        {
            return new AdaptiveWidth(value);
        }

        /// <summary>
        /// Assignment operator with type
        /// </summary>
        /// <param name="value"></param>
        public static implicit operator AdaptiveWidth(AdaptiveWidthType value)
        {
            return new AdaptiveWidth(value);
        }

        /// <summary>
        /// Assignment operator with string (100x)
        /// </summary>
        /// <param name="value"></param>
        public static implicit operator AdaptiveWidth(string value)
        {
            return new AdaptiveWidth(value);
        }

        /// <inheritdoc />
        public static bool operator ==(AdaptiveWidth ah1, AdaptiveWidth ah2)
        {
            return ah1.Equals(ah2);
        }

        /// <inheritdoc />
        public static bool operator !=(AdaptiveWidth ah1, AdaptiveWidth ah2)
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
            return (int)(Unit.Value * 10 + (int)WidthType);
        }

        /// <inheritdoc />
        public override bool Equals(object obj)
        {
            return this.Equals(obj as AdaptiveWidth);
        }

        /// <inheritdoc />
        public Boolean Equals(AdaptiveWidth other)
        {
            if (this.WidthType == other.WidthType)
            {
                if (this.WidthType == AdaptiveWidthType.Pixel)
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
            if (WidthType == AdaptiveWidthType.Stretch)
                return "stretch";
            if (WidthType == AdaptiveWidthType.Auto)
                return "auto";
            return $"{Unit}px";
        }

    }
}
