using Newtonsoft.Json;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    /// ChartDataSet 
    /// </summary>
    public class ChartDataSet
    {
        /// <summary>
        /// Label for the data set 
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute(Type = typeof(string), AttributeName = "Label")]
#endif
        [JsonProperty("label")]
        public string Label { get; set; }

        /// <summary>
        /// Data
        /// </summary>
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(List<float>), ElementName = "Data")]
#endif
        public List<float> Data { get; set; }

        /// <summary>
        /// Background color to use for this data set. RGBA(#,#,#,#)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute(Type = typeof(List<string>), AttributeName = "BackgroundColor")]
#endif
        [JsonProperty("backgroundColor")]
        public List<string> BackgroundColor { get; set; }

        /// <summary>
        /// Background colors to use for this data set. RGBA(#,#,#,#)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(List<string>), ElementName = "BackgroundColors")]
#endif
        [JsonProperty("backgroundColors")]
        public List<string> BackgroundColors { get; set; }


        /// <summary>
        /// Border color to use for this data set. RGBA(#,#,#,#)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlAttribute(Type = typeof(List<string>), AttributeName = "BorderColor")]
#endif
        [JsonProperty("borderColor")]
        public List<string> backgroundColor { get; set; }

        /// <summary>
        /// Border colors to use for this data set. RGBA(#,#,#,#)
        /// </summary>
#if !NETSTANDARD1_3
        [XmlElement(Type = typeof(List<string>), ElementName = "BorderColors")]
#endif
        [JsonProperty("borderColors")]
        public List<string> BorderColors { get; set; }
    }
}
