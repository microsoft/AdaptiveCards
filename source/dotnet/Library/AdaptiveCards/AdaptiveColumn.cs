using Newtonsoft.Json;
using System;

namespace AdaptiveCards
{
    /// <summary>
    ///     Column
    /// </summary>
    public class AdaptiveColumn : AdaptiveContainer
    {
        public new const string TypeName = "Column";

        public override string Type => TypeName;

        /// <summary>
        ///     Size for the column (either ColumnSize string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        [Obsolete("Column.Size has been deprecated.  Use Column.Width", false)]
        public string Size { get { return _Size; } set { SetValue(ref _Size, value); } }
        private string _Size;

        /// <summary>
        ///     Width for the column (either ColumnWidth string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
        public string Width { get { return _Width; } set { SetValue(ref _Width, value); } }
        private string _Width;

    }
}