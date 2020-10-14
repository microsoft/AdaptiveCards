// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;


namespace AdaptiveCards
{
    /// <summary>
    ///     The Image element allows for the inclusion of images in an Adaptive Card.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveImage.TypeName)]
#endif
    public class AdaptiveImage : AdaptiveElement
    {
        public AdaptiveImage()
        {
        }

        public AdaptiveImage(string url)
        {
            Url = new Uri(url);
        }

        public AdaptiveImage(Uri url)
        {
            Url = url;
        }

        public const string TypeName = "Image";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [JsonProperty(Required = Required.Default)]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Size for the Image
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageSize), "auto")]
        public AdaptiveImageSize Size { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageStyle), "default")]
        public AdaptiveImageStyle Style { get; set; }

        /// <summary>
        ///     A url pointing to an image to display
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public Uri Url { get; set; }

        /// <summary>
        ///     This is necessary for XML serialization. You should use the <see cref="F:Url" /> property directly.
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
        ///     Horizontal alignment for element
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        /// <summary>
        ///     A background color for the image specified as #AARRGGBB or #RRGGBB
        /// </summary>
        [JsonConverter(typeof(HashColorConverter))]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string BackgroundColor { get; set; }

        /// <summary>
        ///     Action for this image (this allows a default action to happen when a click on an image happens)
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlElement]
#endif
        [DefaultValue(null)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        ///     Alternate text to display for this image
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string AltText { get; set; }

        /// <summary>
        ///    Explicit Image Width
        /// </summary>
        [JsonConverter(typeof(StringSizeWithUnitConverter), false)]
        [JsonProperty("width", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(0)]
        public uint PixelWidth { get; set; }

        /// <summary>
        ///    Explicit Image Height
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
