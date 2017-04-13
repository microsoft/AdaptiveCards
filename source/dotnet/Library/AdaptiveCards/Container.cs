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
        public Container()
        {
            Type = "Container";
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
        [XmlElement(typeof(ActionSet))]
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

    }
}