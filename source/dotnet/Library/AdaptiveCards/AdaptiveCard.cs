using System.Collections.Generic;
using System.Linq;
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Adaptive card which has flexible container
    /// </summary>
    public class AdaptiveCard : TypedElement
    {
        public const string TYPE = "AdaptiveCard";

        public AdaptiveCard()
        {
            Type = TYPE;
        }

        public const string ContentType = "application/vnd.microsoft.card.adaptive";

#if NET452
        [XmlElement(typeof(TextBlock))]
        [XmlElement(typeof(Image))]
        [XmlElement(typeof(Container))]
        [XmlElement(typeof(ColumnSet))]
        [XmlElement(typeof(ImageSet))]
        [XmlElement(typeof(FactSet))]
        [XmlElement(typeof(ActionSet))]
        [XmlElement(typeof(TextInput), ElementName = TextInput.TYPE)]
        [XmlElement(typeof(DateInput), ElementName = DateInput.TYPE)]
        [XmlElement(typeof(TimeInput), ElementName = TimeInput.TYPE)]
        [XmlElement(typeof(NumberInput), ElementName = NumberInput.TYPE)]
        [XmlElement(typeof(ToggleInput), ElementName = ToggleInput.TYPE)]
        [XmlElement(typeof(ChoiceSet), ElementName = ChoiceSet.TYPE)]
#endif
        public List<CardElement> Body { get; set; } = new List<CardElement>();

        /// <summary>
        ///     Actions for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlArray("Actions")]
        [XmlArrayItem(ElementName = OpenUrlAction.TYPE, Type = typeof(OpenUrlAction))]
        [XmlArrayItem(ElementName = ShowCardAction.TYPE, Type = typeof(ShowCardAction))]
        [XmlArrayItem(ElementName = SubmitAction.TYPE, Type = typeof(SubmitAction))]
        [XmlArrayItem(ElementName = HttpAction.TYPE, Type = typeof(HttpAction))]
#endif
        public List<ActionBase> Actions { get; set; } = new List<ActionBase>();

        /// <summary>
        ///     Speak annotation for the card
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlElement]
#endif
        public string Speak { get; set; }

        /// <summary>
        ///     Title for the card (used when displayed in a dialog)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string Title { get; set; }

        /// <summary>
        ///     Background image for card
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string BackgroundImage { get; set; }

        /// <summary>
        ///     version of schema that this card was authored
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string Version { get; set; }

        /// <summary>
        ///     if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not
        ///     supported are safe to ignore
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string MinVersion { get; set; }

        /// <summary>
        ///     if a client is not able to show the card, show fallbackText to the user. This can be in markdown format.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string FallbackText { get; set; }

        public bool ShouldSerializeActions()
        {
            return Actions.Any();
        }
    }
}