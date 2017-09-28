using Newtonsoft.Json;
using System;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base class for all elements in a container
    /// </summary>
    public abstract class CardElement : TypedElement
    {
        /// <summary>
        /// The amount of space the element should be separated from the previous element. Default value is <see cref="Spacing.Default"/>.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public Spacing Spacing { get; set; }

        /// <summary>
        /// Indicates whether there should be a visible separator (e.g. a line) between the element and the one before it.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public bool Separator { get; set; }

        /// <summary>
        ///     SSML fragment for spoken interaction
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlElement]
#endif
        [Obsolete("CardElement.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }

        /// <summary>
        ///     How should this element be emphasized relative to previous element
        /// </summary>
        [JsonIgnore]
        [Obsolete("Use Separator and Spacing instead")]
#if NET452
        [XmlAttribute]
#endif
#pragma warning disable 612, 618
        public SeparationStyle Separation
        {
            get
            {
                // There's no good way to back-compat convert this, so we'll just go
                // based on the spacing value
                switch (Spacing)
                {
                    case Spacing.None:
                        return SeparationStyle.None;

                    case Spacing.Large:
                        return SeparationStyle.Strong;

                    default:
                        return SeparationStyle.Default;
                }
            }

            set
            {
                // Back-compat for upgrading the obsolete Separation value to the new values
                switch (value)
                {
                    case SeparationStyle.Default:
                        Separator = false;
                        Spacing = Spacing.Default;
                        break;

                    case SeparationStyle.None:
                        Separator = false;
                        Spacing = Spacing.None;
                        break;

                    case SeparationStyle.Strong:
                        Separator = true;
                        Spacing = Spacing.Large;
                        break;

                    default:
                        throw new NotImplementedException();
                }
            }
        }
#pragma warning restore 612, 618

        // Allow deserializing but not serializing: https://stackoverflow.com/questions/11564091/making-a-property-deserialize-but-not-serialize-with-json-net
        [JsonProperty("separation")]
#pragma warning disable 612, 618
        private SeparationStyle SeparationSetter
        {
            set
            {
                Separation = value;
            }
        }
#pragma warning restore 612, 618
    }
}