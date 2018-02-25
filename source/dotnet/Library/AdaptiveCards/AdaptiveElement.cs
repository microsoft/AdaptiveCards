using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base class for all elements in a container
    /// </summary>
    public abstract class AdaptiveElement : AdaptiveTypedElement
    {
        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="AdaptiveSpacing.Default"/>.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveSpacing), "default")]
        public AdaptiveSpacing Spacing { get; set; }

        /// <summary>
        /// Indicates whether there should be a visible separator (e.g. a line) between this element and the one before it.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(false)]
        public bool Separator { get; set; }

        /// <summary>
        ///     SSML fragment for spoken interaction
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("CardElement.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }

        /// <summary>
        ///     How should this element be emphasized relative to previous element
        /// </summary>
        [Obsolete("Use Separator and Spacing instead")]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public AdaptiveSeparationStyle Separation
        {
            get
            {
                // There's no good way to back-compat convert this, so we'll just go
                // based on the spacing value
                switch (Spacing)
                {
                    case AdaptiveSpacing.None:
                        return AdaptiveSeparationStyle.None;

                    case AdaptiveSpacing.Large:
                        return AdaptiveSeparationStyle.Strong;

                    default:
                        return AdaptiveSeparationStyle.Default;
                }
            }

            set
            {
                // Back-compat for upgrading the obsolete Separation value to the new values
                switch (value)
                {
                    case AdaptiveSeparationStyle.Default:
                        Separator = false;
                        Spacing = AdaptiveSpacing.Default;
                        break;

                    case AdaptiveSeparationStyle.None:
                        Separator = false;
                        Spacing = AdaptiveSpacing.None;
                        break;

                    case AdaptiveSeparationStyle.Strong:
                        Separator = true;
                        Spacing = AdaptiveSpacing.Large;
                        break;

                    default:
                        throw new NotImplementedException();
                }
            }
        }
    }
}