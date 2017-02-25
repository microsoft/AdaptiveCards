using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace Adaptive
{
    /// <summary>
    /// Container for a collection of elements
    /// </summary>
    public partial class Container : CardElement
    {
        public Container()
        { }

        /// <summary>
        /// Elements of the container
        /// </summary>
        [JsonRequired]
        [XmlElement(typeof(TextBlock))]
        [XmlElement(typeof(Image))]
        [XmlElement(typeof(Container))]
        [XmlElement(typeof(ColumnSet))]
        [XmlElement(typeof(FactSet))]
        [XmlElement(typeof(ImageSet))]
        [XmlElement(typeof(InputText))]
        [XmlElement(typeof(InputDate))]
        [XmlElement(typeof(InputTime))]
        [XmlElement(typeof(InputNumber))]
        [XmlElement(typeof(InputToggle))]
        [XmlElement(typeof(InputChoiceSet))]
        public List<CardElement> Items { get; set; } = new List<CardElement>();

        /// <summary>
        /// Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public ActionBase SelectAction { get; set; }

        /// <summary>
        /// Actions for this container
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public List<ActionBase> Actions { get; set; } = new List<ActionBase>();

        /// <summary>
        /// visually separate this container from previous containers
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public bool StartGroup { get; set; }

        public bool ShouldSerializeStartGroup() { return this.StartGroup; }
    }
}
