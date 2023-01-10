// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    internal sealed class AdaptiveColumnWidthConverter : JsonConverter<AdaptiveColumnWidth>
    {
        public override bool CanRead => true;
        public override bool CanWrite => true;

        public override void WriteJson(JsonWriter writer, AdaptiveColumnWidth value, JsonSerializer serializer)
        {
            if (value.WidthType != null)
            {
                writer.WriteValue(value.ToString());
            }
            else
            {
                if (value.IsPixel)
                {
                    writer.WriteValue($"{value.Unit.Value}px");
                }
                else
                {
                    var i = Convert.ToInt64(value.Unit.Value);
                    if (i == value.Unit.Value)
                        writer.WriteValue(i);
                    else
                        writer.WriteValue(value.Unit.Value);
                }
            }
        }

        public override AdaptiveColumnWidth ReadJson(JsonReader reader, Type objectType, AdaptiveColumnWidth existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            return new AdaptiveColumnWidth(reader.Value.ToString());
        }
    }

    /// <summary>
    ///     Controls the horizontal size (width) of Column.
    /// </summary>
    public class AdaptiveColumnWidthType
    {
        /// <summary>
        ///     The width of the Column is optimally chosen depending on the space available in the element's container
        /// </summary>
        public const string Auto = "auto";

        /// <summary>
        ///     The width of the Column adjusts to match that of its container
        /// </summary>
        public const string Stretch = "stretch";
    }

    /// <summary>
    /// Represents the columnWidth property in Adaptive Cards.
    /// </summary>
    [JsonConverter(typeof(AdaptiveColumnWidthConverter))]
    public class AdaptiveColumnWidth : IEquatable<AdaptiveColumnWidth>
    {
        /// <summary>
        /// Returns a new AdaptiveColumnWidth instance initialized for the <see cref="AdaptiveColumnWidthType.Auto"/> columnWidth type.
        /// </summary>
        public static AdaptiveColumnWidth Auto { get; } = new AdaptiveColumnWidth(AdaptiveColumnWidthType.Auto);

        /// <summary>
        /// Returns a new AdaptiveColumnWidth instance initialized for the <see cref="AdaptiveColumnWidthType.Stretch"/> columnWidth type.
        /// </summary>
        public static AdaptiveColumnWidth Stretch { get; } = new AdaptiveColumnWidth(AdaptiveColumnWidthType.Stretch);

        /// <summary>
        /// Initializes an empty AdaptiveColumnWidth instance.
        /// </summary>
        public AdaptiveColumnWidth()
        {
        }

        /// <summary>
        /// Initializes an AdaptiveColumnWidth instance with the given width as ("auto","stretch", "100px", "1.5" /*relative size*/}
        /// </summary>
        /// <param name="width">The device-independent pixel size to use.</param>
        public AdaptiveColumnWidth(string width)
        {
            switch (width.ToLower())
            {
                case AdaptiveColumnWidthType.Auto:
                    WidthType = AdaptiveColumnWidthType.Auto;
                    break;
                case AdaptiveColumnWidthType.Stretch:
                    WidthType = AdaptiveColumnWidthType.Stretch;
                    break;
                default:
                    if (width.EndsWith("px"))
                    {
                        width = width.Substring(0, width.Length - 2);
                        IsPixel = true;
                        Unit = uint.Parse(width);
                    }
                    else
                    {
                        Unit = float.Parse(width);
                    }
                    break;
            }
        }

        /// <summary>
        /// Initializes an AdaptiveColumnWidth instance with the given pixel size.
        /// </summary>
        /// <param name="size">The device-independent pixel size to use.</param>
        public AdaptiveColumnWidth(float size)
        {
            this.Unit = (float)size;
        }

        public static implicit operator AdaptiveColumnWidth(string val) => new AdaptiveColumnWidth(val);

        public bool IsPixel { get; set; }

        /// <summary>
        /// The <see cref="AdaptiveColumnWidthType"/> this instance represents.
        /// </summary>
        public string WidthType { get; set; }

        /// <summary>
        /// The specific columnWidth .
        /// </summary>
        public float? Unit { get; set; }

        public override string ToString()
        {
            if (this.IsPixel)
            {
                // 100px
                return $"{Unit}px";
            }

            if (this.Unit != null)
            {
                // relative unit 1.5
                return this.Unit.ToString();
            }

            // auto or stretch
            return this.WidthType;
        }

        /// <inheritdoc />
        public static bool operator ==(AdaptiveColumnWidth ah1, AdaptiveColumnWidth ah2)
        {
            return ah1?.ToString() == ah2?.ToString();
        }

        /// <inheritdoc />
        public static bool operator !=(AdaptiveColumnWidth ah1, AdaptiveColumnWidth ah2)
        {
            return ah1?.ToString() != ah2?.ToString();
        }

        /// <inheritdoc />
        public override int GetHashCode()
        {
            return (int)this.ToString().GetHashCode();
        }

        /// <inheritdoc />
        public override bool Equals(object obj)
        {
            return this.ToString() == obj?.ToString();
        }

        /// <inheritdoc />
        public Boolean Equals(AdaptiveColumnWidth other)
        {
            return this.ToString() == other?.ToString();
        }
    }
}
