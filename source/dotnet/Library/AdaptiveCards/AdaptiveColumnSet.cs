using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of columns
    /// </summary>
    public class AdaptiveColumnSet : AdaptiveCardElement
    {
        public const string TYPE = "ColumnSet";

        public AdaptiveColumnSet()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Columns that are part of this group
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlElement(ElementName = "Column", Type = typeof(AdaptiveColumn))]
#endif
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();

        /// <summary>
        ///     Action for this ColumnSet (this allows a default action at the column set level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveActionBase SelectAction { get; set; }
    }

    [Obsolete("Use AdaptiveColumnSet instead")]
    public class ColumnSet : AdaptiveColumnSet { }
}