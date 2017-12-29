using System.Collections.Generic;
using System.Collections.ObjectModel;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of columns
    /// </summary>
    public class AdaptiveColumnSet : AdaptiveElement
    {
        public const string TypeName = "ColumnSet";

        public override string Type => TypeName;

        /// <summary>
        ///     Columns that are part of this group
        /// </summary>
        [JsonRequired]
        public ObservableCollection<AdaptiveColumn> Columns { get { return _Columns; } set { SetPropertyValue(ref _Columns, value); } }
        private ObservableCollection<AdaptiveColumn> _Columns = new ObservableCollection<AdaptiveColumn>();

        /// <summary>
        ///     Action for this ColumnSet (this allows a default action at the column set level)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public AdaptiveAction SelectAction { get { return _SelectAction; } set { SetPropertyValue(ref _SelectAction, value); } }
        private AdaptiveAction _SelectAction;

    }
}