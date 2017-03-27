using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    /// A container inside of a ColumnSet
    /// </summary>
    public partial class Column : Container
    {
        public Column()
        {
            this.Type = "Column";
        }

        /// <summary>
        /// Size for the column (either ColumnSize string or number which is relative size of the column)
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Size { get; set; }
    }
}
