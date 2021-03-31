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
    ///     When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web browser or
    ///     showing in-situ with embedded web browser.
    /// </summary>
#if !NETSTANDARD1_3
    [XmlType(TypeName = AdaptiveOpenUrlAction.TypeName)]
#endif
    public class AdaptiveOpenUrlAction : AdaptiveAction
    {
        public const string TypeName = "Action.OpenUrl";

#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Url to open using default operating system browser
        /// </summary>
        [JsonRequired]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        [DefaultValue(null)]
        public Uri Url { get; set; }

        /// <summary>
        ///     This is necessary for XML serialization. You should use the <see cref="F:Url" /> property directly.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute("Url")]
        [Browsable(false), EditorBrowsable(EditorBrowsableState.Never)]
#endif
        [JsonIgnore]
        public string UrlString
        {
            get { return Url?.ToString(); }
            set { Url = new Uri(value); }
        }
    }
}
