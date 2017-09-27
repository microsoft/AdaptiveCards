using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input is used as part of a Form CardElement to collect information from a user
    /// </summary>
    public class Input : CardElement
    {
        /// <summary>
        ///     Id for the value (will be used to identify collected input when SUBMIT is clicked)
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlAttribute]
#endif
        public string Id { get; set; }

        /// <summary>
        ///     The input must have a value for it to be part of a Submit or Http action
        /// </summary>
#if NET452
        [XmlAttribute]
#endif
        public bool IsRequired { get; set; }

        public bool ShouldSerializeIsRequired()
        {
            return IsRequired;
        }
    }
}