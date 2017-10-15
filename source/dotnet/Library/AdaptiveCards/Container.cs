using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Container for a collection of elements
    /// </summary>
    public class Container : CardElement
    {
        public const string TypeName = "Container";

        public Container()
        {
            Type = TypeName;
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
        [XmlElement(typeof(TextInput), ElementName = TextInput.TypeName)]
        [XmlElement(typeof(DateInput), ElementName = DateInput.TypeName)]
        [XmlElement(typeof(TimeInput), ElementName = TimeInput.TypeName)]
        [XmlElement(typeof(NumberInput), ElementName = NumberInput.TypeName)]
        [XmlElement(typeof(ToggleInput), ElementName = ToggleInput.TypeName)]
        [XmlElement(typeof(ChoiceSet), ElementName = ChoiceSet.TypeName)]

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

    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<ContainerStyle>), true)]
    public enum ContainerStyle
    {
        /// <summary>
        /// The container is a default container
        /// </summary>
        Default = 0,

        /// <summary>
        /// The container is a normal container
        /// </summary>
        [Obsolete("ContainerStyle.Normal has been deprecated.  Use ContainerStyle.Default", false)]
        Normal = 0,

        /// <summary>
        /// The container should be emphasized as a grouping of elements
        /// </summary>
        Emphasis = 1
    }
}