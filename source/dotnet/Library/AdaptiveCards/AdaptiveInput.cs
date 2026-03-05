// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Text.Json.Serialization;
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
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(false)]
        public bool IsRequired { get; set; }

        /// <summary>
        /// Label to be shown next to input.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string Label { get; set; }

        /// <summary>
        /// Error message to be shown when validation fails.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        [DefaultValue(null)]
        public string ErrorMessage { get; set; }

        /// <summary>
        /// The string that will be rendered on a a host with "SupportsInteractivity" set to false.
        /// </summary>
        public abstract string GetNonInteractiveValue();
    }
}
