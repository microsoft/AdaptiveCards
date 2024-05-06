// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents any input element.
    /// </summary>
    public abstract class AdaptiveInput : AdaptiveElement
    {
        /// <summary>
        /// Sets the input as required for triggering Submit actions.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool IsRequired { get; set; }

        /// <summary>
        /// Label to be shown next to input.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Label { get; set; }

        /// <summary>
        /// Error message to be shown when validation fails.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string ErrorMessage { get; set; }

        /// <summary>
        /// The string that will be rendered on a a host with "SupportsInteractivity" set to false.
        /// </summary>
        public abstract string GetNonInteractiveValue();
    }
}
