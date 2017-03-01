using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Markup;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive
{
    /// <summary>
    /// Adaptive card which has flexible container
    /// </summary>
    [ContentProperty("Body")]
    public partial class AdaptiveCard : TypedElement
    {
        public AdaptiveCard() { }

        [XmlElement(typeof(TextBlock))]
        [XmlElement(typeof(Image))]
        [XmlElement(typeof(Container))]
        [XmlElement(typeof(ColumnSet))]
        [XmlElement(typeof(ImageSet))]
        [XmlElement(typeof(FactSet))]
        [XmlElement(typeof(InputText))]
        [XmlElement(typeof(InputDate))]
        [XmlElement(typeof(InputTime))]
        [XmlElement(typeof(InputNumber))]
        [XmlElement(typeof(InputToggle))]
        [XmlElement(typeof(InputChoiceSet))]
        public List<CardElement> Body { get; set; } = new List<CardElement>();

        /// <summary>
        /// Actions for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlArray("Actions")]
        [XmlArrayItem(ElementName = "OpenUrl", Type = typeof(ActionOpenUrl))]
        [XmlArrayItem(ElementName = "ShowCard", Type = typeof(ActionShowCard))]
        [XmlArrayItem(ElementName = "Submit", Type = typeof(ActionSubmit))]
        [XmlArrayItem(ElementName = "Http", Type = typeof(ActionHttp))]
        public List<ActionBase> Actions { get; set; } = new List<ActionBase>();

        /// <summary>
        /// Speak annotation for the card
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlElement]
        public string Speak { get; set; }

        /// <summary>
        /// Title for the card (used when displayed in a dialog)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Title { get; set; }

        /// <summary>
        /// Background image for card
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string BackgroundImage { get; set; }

        /// <summary>
        /// version of schema that this card was authored
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Version { get; set; }

        /// <summary>
        /// if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not supported are safe to ignore
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string MinVersion { get; set; }


        public bool ShouldSerializeActions() { return Actions.Any(); }
    }
}
