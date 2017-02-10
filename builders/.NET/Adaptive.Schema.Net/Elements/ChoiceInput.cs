using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive.Schema.Net
{

    /// <summary>
    /// Element which collects choice from the user
    /// </summary>
    public class ChoiceInput : Input
    {
        public ChoiceInput()
        {
        }

        /// <summary>
        /// Style for choice 
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        ChoiceInputStyle? Style { get; set; }

        /// <summary>
        /// allow multiple choices to be selected (default false)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        bool? MultiSelect { get; set; }

        /// <summary>
        ///  the choice options
        /// </summary>
        [JsonRequired]
        Choice[] choices { get; set; }
    }

    /// <summary>
    /// Choice as part of a MultichoiceInput element
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class Choice
    {
        public Choice()
        { }

        /// <summary>
        /// Display text for the choice
        /// </summary>
        [JsonRequired]
        public string Display { get; set; }

        /// <summary>
        /// Internal value which will be collected as input if the choice is selected
        /// </summary>
        [JsonRequired]
        public string Value { get; set; }

        /// <summary>
        /// (OPTIONAL) Speech description of the choice
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Speak { get; set; }
    }


}