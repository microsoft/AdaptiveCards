using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Container for a collection of elements
    /// </summary>
    public class AdaptiveContainer : AdaptiveCardElement
    {
        public const string TYPE = "Container";

        public AdaptiveContainer()
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
        [XmlElement(typeof(AdaptiveContainer))]
        [XmlElement(typeof(AdaptiveColumnSet))]
        [XmlElement(typeof(ImageSet))]
        [XmlElement(typeof(FactSet))]
        [XmlElement(typeof(TextInput), ElementName = TextInput.TYPE)]
        [XmlElement(typeof(DateInput), ElementName = DateInput.TYPE)]
        [XmlElement(typeof(TimeInput), ElementName = TimeInput.TYPE)]
        [XmlElement(typeof(NumberInput), ElementName = NumberInput.TYPE)]
        [XmlElement(typeof(ToggleInput), ElementName = ToggleInput.TYPE)]
        [XmlElement(typeof(AdaptiveChoiceSetInput), ElementName = AdaptiveChoiceSetInput.TYPE)]

#endif
        public List<AdaptiveCardElement> Items { get; set; } = new List<AdaptiveCardElement>();

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveActionBase SelectAction { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public AdaptiveContainerStyle Style { get; set; }
    }

    [Obsolete("Use AdaptiveContainer instead")]
    public class Container : AdaptiveContainer { }

    [JsonConverter(typeof(IgnoreDefaultStringEnumConverter<AdaptiveContainerStyle>), true)]
    public enum AdaptiveContainerStyle
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

    [Obsolete("Use AdaptiveContainerStyle instead")]
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