// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Controls the size (width or dimension) of element.
    /// </summary>

    public class AdaptiveDimensionType
    {
        /// <summary>
        /// The dimension of the element matches element content.
        /// </summary>
        public const string Auto = "auto";

        /// <summary>
        /// The dimension of the element uses as much space as it is able to.
        /// </summary>
        public const string Stretch = "stretch";
    }

    internal sealed class AdaptiveDimensionConverter : JsonConverter<AdaptiveDimension>
    {
        public override bool CanRead => true;
        public override bool CanWrite => true;

        public override void WriteJson(JsonWriter writer, AdaptiveDimension value, JsonSerializer serializer)
        {
            writer.WriteValue(value.ToString());
        }

        public override AdaptiveDimension ReadJson(JsonReader reader, Type objectType, AdaptiveDimension existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            return new AdaptiveDimension(reader.Value.ToString());
        }
    }


    /// <summary>
    /// Represents the dimension property in Adaptive Cards, which is either "auto","stretch" or 1.5px
    /// </summary>
    [JsonConverter(typeof(AdaptiveDimensionConverter))]
    public class AdaptiveDimension : IEquatable<AdaptiveDimension>
    {
        /// <summary>
        /// Returns a new Adaptivedimension instance initialized for the <see cref="AdaptiveDimensionType.Auto"/> dimension type.
        /// </summary>
        public static AdaptiveDimension Auto { get; } = new AdaptiveDimension(AdaptiveDimensionType.Auto);

        /// <summary>
        /// Returns a new Adaptivedimension instance initialized for the <see cref="AdaptiveDimensionType.Stretch"/> dimension type.
        /// </summary>
        public static AdaptiveDimension Stretch { get; } = new AdaptiveDimension(AdaptiveDimensionType.Stretch);

        /// <summary>
        /// Initializes an empty Adaptivedimension instance.
        /// </summary>
        public AdaptiveDimension()
        {
        }

        /// <summary>
        /// Initialize a adaptivedimension instance from a string.
        /// </summary>
        /// <param name="value">value of string ("auto","stretch","100px")</param>
        public AdaptiveDimension(string value)
        {
            if (value.EndsWith("px"))
            {
                value = value.Substring(0, value.Length - 2);
                this.Unit = int.Parse(value);
            }
            else
            {
                switch(value)
                {
                    case AdaptiveDimensionType.Auto:
                    case AdaptiveDimensionType.Stretch:
                        this.DimensionType = value;
                        break;
                    default:
                        throw new Exception($"Unknown dimension type: {value}");
                }
            }
        }

        /// <summary>
        /// Assignment operator
        /// </summary>
        /// <param name="val">string to convert to dimension.</param>
        public static implicit operator AdaptiveDimension(string val) => new AdaptiveDimension(val);

        /// <summary>
        /// Gets or sets the dimension type.
        /// </summary>
        public string DimensionType { get; set; }

        /// <summary>
        /// Gets or sets the units 
        /// </summary>
        public int? Unit { get; set; }

        public override string ToString()
            => (DimensionType != null) ? DimensionType : $"{Unit}px";

        /// <summary>
        /// Returns true if this <see cref="AdaptiveDimension"/> instance represents a pixel 
        /// </summary>
        public bool IsPixel()
        {
            return DimensionType == null;
        }

        /// <inheritdoc />
        public static bool operator ==(AdaptiveDimension ah1, AdaptiveDimension ah2)
        {
            return ah1?.ToString() == ah2?.ToString();
        }

        /// <inheritdoc />
        public static bool operator !=(AdaptiveDimension ah1, AdaptiveDimension ah2)
        {
            return ah1?.ToString() != ah2?.ToString();
        }

        /// <inheritdoc />
        public override int GetHashCode()
        {
            return this.ToString().GetHashCode();
        }

        /// <inheritdoc />
        public override bool Equals(object obj)
        {
            return this.Equals(obj as AdaptiveDimension);
        }

        /// <inheritdoc />
        public Boolean Equals(AdaptiveDimension other)
        {
            return (this.DimensionType == other?.DimensionType) && (this.Unit == other?.Unit);
        }
    }
}
