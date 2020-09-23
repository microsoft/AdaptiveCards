// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveBackgroundImage.TypeName)]
#endif
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class AdaptiveBackgroundImage
    {
        public AdaptiveBackgroundImage() { }

        public AdaptiveBackgroundImage(string url)
        {
            Url = new Uri(url, UriKind.RelativeOrAbsolute);
        }

        public AdaptiveBackgroundImage(Uri url)
        {
            Url = url;
        }

        public AdaptiveBackgroundImage(string url, AdaptiveImageFillMode fillMode, AdaptiveHorizontalAlignment hAlignment, AdaptiveVerticalAlignment vAlignment)
        {
            Url = new Uri(url, UriKind.RelativeOrAbsolute);
            FillMode = fillMode;
            HorizontalAlignment = hAlignment;
            VerticalAlignment = vAlignment;
        }

        public AdaptiveBackgroundImage(Uri url, AdaptiveImageFillMode fillMode, AdaptiveHorizontalAlignment hAlignment, AdaptiveVerticalAlignment vAlignment)
        {
            Url = url;
            FillMode = fillMode;
            HorizontalAlignment = hAlignment;
            VerticalAlignment = vAlignment;
        }

        public const string TypeName = "backgroundImage";

        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public Uri Url { get; set; }

#if !NETSTANDARD1_3
        [XmlAttribute("BackgroundImage")]
        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
#endif
        [JsonIgnore]
        public string UrlString
        {
            get { return Url?.ToString(); }
            set { Url = new Uri(value); }
        }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveImageFillMode), "cover")]
        public AdaptiveImageFillMode FillMode { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalAlignment), "top")]
        public AdaptiveVerticalAlignment VerticalAlignment { get; set; }

        public bool HasDefaultValues()
        {
            if (FillMode == AdaptiveImageFillMode.Cover && HorizontalAlignment == AdaptiveHorizontalAlignment.Left && VerticalAlignment == AdaptiveVerticalAlignment.Top)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static implicit operator AdaptiveBackgroundImage(Uri backgroundImageUrl)
        {
            return new AdaptiveBackgroundImage(backgroundImageUrl);
        }
    }
}
