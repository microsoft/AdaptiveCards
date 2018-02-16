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
    [XmlType(TypeName = AdaptiveOpenUrlAction.TypeName)]
    public class AdaptiveOpenUrlAction : AdaptiveAction
    {
        public const string TypeName = "Action.OpenUrl";

        [XmlIgnore]
        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Url to open using default operating system browser
        /// </summary>
        [JsonRequired]
        [XmlAttribute]
        public string Url { get; set; }
    }
}