using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Container for a collection of elements
    /// </summary>
    public class Container : CardElement
    {
        public const string TYPE = "Container";

        public Container()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Elements of the container
        /// </summary>
        [JsonRequired]
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
        public List<CardElement> Items { get; set; } = new List<CardElement>();

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionBase SelectAction { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public ContainerStyle Style { get; set; }
    }

    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<ImageStyle>), true)]
    public enum ContainerStyle
    {
        /// <summary>
        /// The container is a normal container
        /// </summary>
        Normal,

        /// <summary>
        /// The container should be emphasized as a grouping of elements
        /// </summary>
        Emphasis
    }
}