// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web
    /// browser or showing in-situ with embedded web browser.
    /// </summary>
    [XmlType(TypeName = AdaptiveOpenUrlAction.TypeName)]
    public class AdaptiveOpenUrlAction : AdaptiveAction
    {
        /// <inheritdoc />
        public const string TypeName = "Action.OpenUrl";

        /// <inheritdoc />
        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        /// Url to open using default operating system browser.
        /// </summary>
        [JsonRequired]
        [XmlIgnore]
        [DefaultValue(null)]
        public Uri Url { get; set; }

        /// <summary>
        /// This is necessary for XML serialization. You should use the <see cref="F:Url" /> property directly.
        /// </summary>
        [XmlAttribute("Url")]
        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
        [JsonIgnore]
        public string UrlString
        {
            get { return Url?.ToString(); }
            set { Url = new Uri(value); }
        }
    }
}
