using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards
{

    /// <summary>
    /// Element which collects choice from the user
    /// </summary>
    public partial class InputChoiceSet : Input
    {
        public InputChoiceSet()
        {
            this.Type = "Input.ChoiceSet";
        }

        /// <summary>
        /// The initial value for the field
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Value { get; set; }

        /// <summary>
        /// Style for choice 
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public ChoiceInputStyle Style { get; set; }

        /// <summary>
        /// allow multiple choices to be selected (default false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public bool IsMultiSelect { get; set; }

        /// <summary>
        ///  the choice options
        /// </summary>
        [JsonRequired]
#if DESKTOP
        [XmlElement(ElementName="Choice", Type=typeof(Choice))]
#endif
        public List<Choice> Choices { get; set; } = new List<Choice>();

        public bool ShouldSerializeStyle() { return this.Style != ChoiceInputStyle.Expanded; }
        public bool ShouldSerializeIsMultiSelect() { return this.IsMultiSelect; }

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
#if DESKTOP
        [XmlAttribute]
#endif
        public string Title { get; set; }

        /// <summary>
        /// Internal value which will be collected as input if the choice is selected
        /// </summary>
        [JsonRequired]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Value { get; set; }

        /// <summary>
        /// Is this choice selected?
        /// </summary>
#if DESKTOP
        [XmlAttribute]
#endif
        public bool IsSelected { get; set; } = false;

        /// <summary>
        /// (OPTIONAL) Speech description of the choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlElement]
#endif
        public string Speak { get; set; }

        public bool ShouldSerializeIsSelected() { return this.IsSelected; }
    }


}