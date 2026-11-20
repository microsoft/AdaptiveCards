// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.ComponentModel;
using System.Reflection;
using System.Text.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base of Action types
    /// </summary>
    public abstract class AdaptiveAction : AdaptiveTypedElement
    {
        /// <summary>
        ///     Title of the action
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        public string Title { get; set; }

        /// <summary>
        ///     Speak phrase for this action
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [Obsolete("ActionBase.Speak has been deprecated.  Use AdaptiveCard.Speak", false)]
        public string Speak { get; set; }

        /// <summary>
        ///     IconUrl that can be specified for actions
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        public string IconUrl { get; set; }

        /// <summary>
        ///     Style that can be specified for actions
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue("default")]
        public string Style { get; set; } = "default";

        /// <summary>
        ///    When set false, action is disabled 
        /// </summary>
        [XmlAttribute]
        [DefaultValue(true)]
        public bool IsEnabled{ get; set; } = true;

        /// <summary>
        /// Determines whether the action should be displayed as a button or in the overflow menu.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingDefault)]
        [XmlAttribute]
        [DefaultValue(typeof(AdaptiveActionMode), "primary")]
        public AdaptiveActionMode Mode { get; set; }

        /// <summary>
        /// Defines text that should be displayed to the end user as they hover the mouse over the action, and read when using narration software.
        /// </summary>
        [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
        [XmlAttribute]
        public string Tooltip{ get; set; }
    }
}
