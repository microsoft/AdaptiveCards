using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Xml.Serialization;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Element which collects choice from the user
    /// </summary>
    public class AdaptiveChoiceSetInput : Input
    {
        public const string TYPE = "Input.ChoiceSet";

        public AdaptiveChoiceSetInput()
        {
            Type = TYPE;
        }

        /// <summary>
        ///      Comma separated string of selected Choice values
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public string Value { get; set; }

        /// <summary>
        ///     Style for choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public ChoiceInputStyle Style { get; set; }

        /// <summary>
        ///     allow multiple choices to be selected (default false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlAttribute]
#endif
        public bool IsMultiSelect { get; set; }

        /// <summary>
        ///     the choice options
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlElement(ElementName="Choice", Type=typeof(Choice))]
#endif
        public List<Choice> Choices { get; set; } = new List<Choice>();

        public bool IsCompact => Style != ChoiceInputStyle.Expanded;

        public bool ShouldSerializeIsMultiSelect()
        {
            return IsMultiSelect;
        }
    }

    /// <summary>
    ///     Choice as part of a Input.ChoiceSet element
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class Choice
    {
        /// <summary>
        ///     Display text for the choice
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlAttribute]
#endif
        public string Title { get; set; }

        /// <summary>
        ///     Internal value which will be collected as input if the choice is selected
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlAttribute]
#endif
        public string Value { get; set; }

        /// <summary>
        ///     Is this choice selected?
        /// </summary>
#if NET452
        [XmlAttribute]
#endif
        [System.Obsolete("Choice.IsSelected has been deprecated.  Use ChoiceSet.Value", false)]
        public bool IsSelected { get; set; } = false;

        /// <summary>
        ///     (OPTIONAL) Speech description of the choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlElement]
#endif
        [Obsolete("ChoiceSet.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }

        public bool ShouldSerializeIsSelected()
        {
#pragma warning disable CS0618 // Type or member is obsolete
            return IsSelected;
#pragma warning restore CS0618 // Type or member is obsolete
        }
    }

    [Obsolete("Use AdaptiveChoiceSet instead")]
    public class ChoiceSet : AdaptiveChoiceSetInput { }
}