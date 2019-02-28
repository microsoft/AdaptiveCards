using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Column
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveColumn.TypeName)]
#endif
    public class AdaptiveColumn : AdaptiveCollectionElement
    {
        public new const string TypeName = "Column";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [JsonProperty(Required = Required.Default)]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Size for the column (either ColumnSize string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("Column.Size has been deprecated.  Use Column.Width", false)]
        public string Size { get; set; }

        /// <summary>
        ///     Width for the column (either ColumnWidth string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(null)]
        public string Width { get; set; } // TODO: this should be a ColumnWidth type with implict converter

        [JsonConverter(typeof(AdaptiveBackgroundImageConverter))]
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [DefaultValue(null)]
        public AdaptiveBackgroundImage BackgroundImage { get; set; }

        /// <summary>
        ///     Elements of the container
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveElement>))]
#if !NETSTANDARD1_3
        [XmlElement(typeof(AdaptiveTextBlock))]
        [XmlElement(typeof(AdaptiveImage))]
        [XmlElement(typeof(AdaptiveContainer))]
        [XmlElement(typeof(AdaptiveColumnSet))]
        [XmlElement(typeof(AdaptiveImageSet))]
        [XmlElement(typeof(AdaptiveFactSet))]
        [XmlElement(typeof(AdaptiveTextInput))]
        [XmlElement(typeof(AdaptiveDateInput))]
        [XmlElement(typeof(AdaptiveTimeInput))]
        [XmlElement(typeof(AdaptiveNumberInput))]
        [XmlElement(typeof(AdaptiveChoiceSetInput))]
        [XmlElement(typeof(AdaptiveToggleInput))]
        [XmlElement(typeof(AdaptiveMedia))]
#endif
        public List<AdaptiveElement> Items { get; set; } = new List<AdaptiveElement>();

        protected override void PropagateBleedPropertyToChildren(AdaptiveTypedElement parent)
        {
            foreach (AdaptiveElement adaptiveElement in Items)
            {
                if (adaptiveElement is AdaptiveCollectionElement)
                {
                    AdaptiveCollectionElement adaptiveCollectionElement = adaptiveElement as AdaptiveCollectionElement;
                    adaptiveCollectionElement.PropagateBleedProperty(parent);
                }
            }
        }
    }
}
