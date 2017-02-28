using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive
{

    /// <summary>
    /// Element which collects choice from the user
    /// </summary>
    public partial class InputChoiceSet : Input
    {
        public InputChoiceSet()
        {
        }

        /// <summary>
        /// The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public string Value { get; set; }

        /// <summary>
        /// Style for choice 
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public ChoiceInputStyle Style { get; set; }

        /// <summary>
        /// allow multiple choices to be selected (default false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        public bool IsMultiSelect { get; set; }

        /// <summary>
        ///  the choice options
        /// </summary>
        [JsonRequired]
        [XmlElement(ElementName="Choice", Type=typeof(Choice))]
        public List<Choice> Choices { get; set; } = new List<Choice>();

        public bool ShouldSerializeStyle() { return this.Style != ChoiceInputStyle.Expanded; }
    }

    /// <summary>
    /// Choice as part of a Input.ChoiceSet element
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public partial class Choice
    {
        public Choice()
        { }

        /// <summary>
        /// Display text for the choice
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Title { get; set; }

        /// <summary>
        /// Internal value which will be collected as input if the choice is selected
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Value { get; set; }

        /// <summary>
        /// Is this choice selected?
        /// </summary>
        [XmlAttribute]
        public bool IsSelected { get; set; } = false;

        /// <summary>
        /// (OPTIONAL) Speech description of the choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlElement]
        public string Speak { get; set; }
    }


}