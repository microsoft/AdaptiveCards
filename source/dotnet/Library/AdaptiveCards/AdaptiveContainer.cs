using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Container for a collection of elements
    /// </summary>
    public class AdaptiveContainer : AdaptiveElement
    {
        public const string TypeName = "Container";

        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     Elements of the container
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        [JsonConverter(typeof(IgnoreEmptyItemsConverter<AdaptiveElement>))]
        public IList<AdaptiveElement> Items { get; set; } = new List<AdaptiveElement>();

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveAction SelectAction { get; set; }

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore, NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveContainerStyle Style { get; set; }
    }
}