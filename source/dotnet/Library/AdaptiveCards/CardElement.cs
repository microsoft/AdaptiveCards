using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Base class for all elements in a container
    /// </summary>
    public class CardElement : TypedElement
    {
        /// <summary>
        ///     SSML fragment for spoken interaction
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET46
        [XmlElement]
#endif
        public string Speak { get; set; }

        /// <summary>
        ///     How should this element be emphasized relative to previous element
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET46
        [XmlAttribute]
#endif
        public SeparationStyle Separation { get; set; }

        public bool ShouldSerializeSeparation()
        {
            return Separation != SeparationStyle.Default;
        }
    }
}