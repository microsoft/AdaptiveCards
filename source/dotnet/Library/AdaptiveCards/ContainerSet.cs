using System.Collections.Generic;
using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     A set of containers (each a container of items)
    /// </summary>
    public class ContainerSet : CardElement
    {
        public ContainerSet()
        {
            Type = "ContainerSet";
        }

        /// <summary>
        ///     Containers that are part of this group
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlElement(ElementName = "Container", Type = typeof(Container))]
#endif
        public List<Container> Containers { get; set; } = new List<Container>();
    }
}