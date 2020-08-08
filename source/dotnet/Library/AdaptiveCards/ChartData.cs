using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// ChartData 
    /// </summary>
    public class ChartData
    {
        /// <summary>
        /// The labels for each element in the dataset
        /// </summary>
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "Labels")]
#endif
        [JsonProperty("charts")]
        public List<string> Labels { get; set; } = new List<string>();

        /// <summary>
        /// the data sets to render.
        /// </summary>
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(AdaptiveFact), ElementName = "DataSets")]
#endif
        [JsonProperty("datasets")]
        public List<ChartDataSet> DataSets { get; set; } = new List<ChartDataSet>();

        /// <summary>
        /// Background color for chart RGB or RGBA(#,#,#,#))
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute(Type = typeof(AdaptiveFact), AttributeName = "BackgroundColor")]
#endif
        [JsonProperty("backgroundColor")]
        public string BackgroundColor { get; set; }

        /// <summary>
        /// Border color to use for this data set. RGBA(#,#,#,#)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute(Type = typeof(AdaptiveFact), AttributeName = "BorderColor")]
#endif
        [JsonProperty("borderColor")]
        public string BorderColor { get; set; }
    }
}
