using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of columns
    /// </summary>
    public class AdaptiveColumnSet : AdaptiveElement
    {
        public const string TypeName = "ColumnSet";

        public AdaptiveColumnSet()
        {
            Type = TypeName;
        }

        /// <summary>
        ///     Columns that are part of this group
        /// </summary>
        [JsonRequired]
        public List<AdaptiveColumn> Columns { get; set; } = new List<AdaptiveColumn>();

        /// <summary>
        ///     Action for this ColumnSet (this allows a default action at the column set level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveActionBase SelectAction { get; set; }
    }
}