using System.Collections.Generic;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     The FactSet element makes it simple to display a se ries of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
    public class AdaptiveFactSet : AdaptiveElement
    {
        public const string TypeName = "FactSet";

        public override string Type { get; set; } = TypeName;

        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonRequired]
        public List<AdaptiveFact> Facts { get; set; } = new List<AdaptiveFact>();
    }
}