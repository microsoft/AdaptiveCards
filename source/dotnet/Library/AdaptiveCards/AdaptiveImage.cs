// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the Adaptive Cards Image element type.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveImage.TypeName)]
#endif
    public class AdaptiveImage : AdaptiveElement
    {
        /// <summary>
        /// Initializes an empty <see cref="AdaptiveImage"/> instance.
        /// </summary>
        public AdaptiveImage()
        {
        }

        /// <summary>
        /// Initializes an <see cref="AdaptiveImage"/> instance with the given URL.
        /// </summary>
        /// <param name="url">The URL of the image as a string.</param>
        public AdaptiveImage(string url)
        {
            Url = new Uri(url);
        }

        /// <summary>
        /// Initializes an <see cref="AdaptiveImage"/> instance with the given URL.
        /// </summary>
        /// <param name="url">The URL of the image.</param>
        public AdaptiveImage(Uri url)
        {
            Url = url;
        }

        /// <inheritdoc />
        public const string TypeName = "Image";

        /// <inheritdoc />
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [JsonProperty(Required = Required.Default)]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Controls the sizing (<see cref="AdaptiveImageSize"/>) of the displayed image.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageSize), "auto")]
        public AdaptiveImageSize Size { get; set; }

        /// <summary>
        /// The style (<see cref="AdaptiveImageStyle"/>) in which the image is displayed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageStyle), "default")]
        public AdaptiveImageStyle Style { get; set; }

        /// <summary>
        /// The URL of the image.
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public Uri Url { get; set; }

        /// <summary>
        /// This is necessary for XML serialization. You should use the <see cref="F:Url" /> property directly.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute("Url")]
        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
#endif
        [JsonIgnore]
        public string UrlString
        {
            get { return Url?.ToString(); }
            set { Url = new Uri(value); }
        }

        /// <summary>
        /// Horizontal alignment (<see cref="AdaptiveHorizontalAlignment"/>) to use.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        /// A background color for the image specified as #AARRGGBB or #RRGGBB.
        /// </summary>
        [JsonConverter(typeof(HashColorConverter))]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string BackgroundColor { get; set; }

        /// <summary>
        /// Action to execute when image is invoked.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        /// Alternate text (alttext) to display for this image.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string AltText { get; set; }

        /// <summary>
        /// Explicit image width.
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), false)]
        [JsonProperty("width", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public uint PixelWidth { get; set; }

        /// <summary>
        /// Explicit image height.
        /// </summary>
        [JsonIgnore]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public uint PixelHeight
        {
            get
            {
                if (Height.Unit != null)
                {
                    return Height.Unit.Value;
                }
                return 0;
            }
            set { Height = new AdaptiveHeight(value); }
        }
    }

}
