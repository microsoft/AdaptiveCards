using System;
using System.ComponentModel;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveBackgroundImage.TypeName)]
#endif
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

        public AdaptiveBackgroundImage(string url, AdaptiveBackgroundImageMode mode, AdaptiveHorizontalAlignment hAlignment, AdaptiveVerticalAlignment vAlignment)
        {
            Url = new Uri(url, UriKind.RelativeOrAbsolute);
            Mode = mode;
            HorizontalAlignment = hAlignment;
            VerticalAlignment = vAlignment;
        }

        public AdaptiveBackgroundImage(Uri url, AdaptiveBackgroundImageMode mode, AdaptiveHorizontalAlignment hAlignment, AdaptiveVerticalAlignment vAlignment)
        {
            Url = url;
            Mode = mode;
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
        public string BackgroundImageString
        {
            get { return Url?.ToString(); }
            set { Url = new Uri(value); }
        }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveBackgroundImageMode), "stretch")]
        public AdaptiveBackgroundImageMode Mode { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalAlignment), "left")]
        public AdaptiveHorizontalAlignment HorizontalAlignment { get; set; }

        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalAlignment), "top")]
        public AdaptiveVerticalAlignment VerticalAlignment { get; set; }

        public bool HasDefaultValues()
        {
            if (Mode == AdaptiveBackgroundImageMode.Stretch && HorizontalAlignment == AdaptiveHorizontalAlignment.Left && VerticalAlignment == AdaptiveVerticalAlignment.Top)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
