using System.Collections.Generic;
using System.Collections.ObjectModel;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     The FactSet element makes it simple to display a se ries of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
    public class AdaptiveFactSet : AdaptiveElement
    {
        public const string TypeName = "FactSet";

        public override string Type => TypeName;

        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonRequired]
        public ObservableCollection<AdaptiveFact> Facts { get { return _Facts; } set { SetPropertyValue(ref _Facts, value); } }
        private ObservableCollection<AdaptiveFact> _Facts = new ObservableCollection<AdaptiveFact>();
    }
}