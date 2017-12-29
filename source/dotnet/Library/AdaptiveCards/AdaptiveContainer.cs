using System.Collections.Generic;
using System.Collections.ObjectModel;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     Container for a collection of elements
    /// </summary>
    public class AdaptiveContainer : AdaptiveElement
    {
        public const string TypeName = "Container";

        public override string Type => TypeName;

        /// <summary>
        ///     Elements of the container
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore)]
        public ObservableCollection<AdaptiveElement> Items { get { return _Items; } set { SetPropertyValue(ref _Items, value); } }
        private ObservableCollection<AdaptiveElement> _Items = new ObservableCollection<AdaptiveElement>();

        /// <summary>
        ///     Action for this container (this allows a default action at the container level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveAction SelectAction { get { return _SelectAction; } set { SetPropertyValue(ref _SelectAction, value); } }
        private AdaptiveAction _SelectAction;

        /// <summary>
        ///     The style in which the image is displayed.
        /// </summary>
        [JsonProperty(DefaultValueHandling = DefaultValueHandling.Ignore, NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveContainerStyle Style { get { return _Style; } set { SetPropertyValue(ref _Style, value); } }
        private AdaptiveContainerStyle _Style;

    }
}