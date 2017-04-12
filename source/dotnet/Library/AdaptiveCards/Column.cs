using Newtonsoft.Json;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     A container inside of a ColumnSet
    /// </summary>
    public class Column : CardElement
    {
        public Column()
        {
            Type = "Column";
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
        [XmlElement(typeof(FactSet))]
        [XmlElement(typeof(ImageSet))]
        [XmlElement(typeof(InputText), ElementName ="Input.Text")]
        [XmlElement(typeof(InputDate), ElementName ="Input.Date")]
        [XmlElement(typeof(InputTime), ElementName = "Input.Time")]
        [XmlElement(typeof(InputNumber), ElementName = "Input.Number")]
        [XmlElement(typeof(InputToggle), ElementName = "Input.Toggle")]
        [XmlElement(typeof(InputChoiceSet), ElementName = "Input.ChoiceSet")]
#endif
        public List<CardElement> Items { get; set; } = new List<CardElement>();

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionBase SelectAction { get; set; }

        /// <summary>
        ///     Size for the column (either ColumnSize string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string Size { get; set; }
    }
}