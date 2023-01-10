// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Diagnostics;
using System.Linq;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    /// Represents the fallback property.
    /// </summary>
    [JsonConverter(typeof(AdaptiveFallbackConverter))]
    public partial class AdaptiveFallbackElement
#if !NETSTANDARD1_3
        : IXmlSerializable
#endif
    {

        /// <summary>
        /// Initializes an AdaptiveFallbackElement with the given <paramref name="fallbackType"/>.
        /// </summary>
        /// <param name="fallbackType">The type of fallback this instance represents.</param>
        public AdaptiveFallbackElement(AdaptiveFallbackType fallbackType)
        {
            Type = fallbackType;
            Content = null;
        }

        /// <summary>
        /// Initializes an AdaptiveFallbackElement with the given <paramref name="fallbackContent"/>.
        /// </summary>
        /// <param name="fallbackContent">The content to show in the event of fallback.</param>
        public AdaptiveFallbackElement(AdaptiveTypedElement fallbackContent)
        {
            Type = AdaptiveFallbackType.Content;
            Content = fallbackContent;
        }

        /// <summary>
        /// Initializes an AdaptiveFallbackElement with no fallback type.
        /// </summary>
        public AdaptiveFallbackElement()
        {
            Type = AdaptiveFallbackType.None;
        }

        /// <summary>
        /// Represents the type of fallback to perform.
        /// </summary>
        [JsonIgnore]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public AdaptiveFallbackType Type { get; set; }

        /// <summary>
        /// The content to show in the event of fallback.
        /// </summary>
        [JsonIgnore]
#if !NETSTANDARD1_3
        [XmlIgnore]
#endif
        public AdaptiveTypedElement Content { get; set; }

#if !NETSTANDARD1_3
        /// <summary>
        /// Convert xml to element.
        /// </summary>
        /// <param name="reader">xml reader.</param>
        public void ReadXml(XmlReader reader)
        {
            while (reader.MoveToNextAttribute())
            {
                switch (reader.Name)
                {
                    case "Type":
                        if (Enum.TryParse<AdaptiveFallbackType>(reader.Value, true, out var type))
                        {
                            Type = type;
                        }
                        return;
                }
            }

            while (reader.Read())
            {
                switch (reader.NodeType)
                {
                    case XmlNodeType.EndElement:
                        reader.ReadEndElement();
                        return;

                    case XmlNodeType.Element:
                        var elementTypes = AdaptiveTypedElementConverter.TypedElementTypes.Value.Values.ToList();
                        if (!AdaptiveTypedElementConverter.TypedElementTypes.Value.TryGetValue(reader.Name, out var typeToCreate))
                        {
                            typeToCreate = typeof(AdaptiveUnknownElement);
                        }
                        XmlSerializer serializer = new XmlSerializer(typeToCreate, elementTypes.ToArray());
                        Type = AdaptiveFallbackType.Content;
                        Content = (AdaptiveTypedElement)serializer.Deserialize(reader.ReadSubtree());
                        break; // we've read our content node, we should be done?
                }
            }

        }

        /// <summary>
        /// Write element as xml
        /// </summary>
        /// <param name="writer">xml writer.</param>
        public void WriteXml(XmlWriter writer)
        {
            if (this.Type == AdaptiveFallbackType.Drop)
            {
                writer.WriteAttributeString("Type", JToken.FromObject(this.Type).ToString());
            }
            else
            {
                XmlSerializer serializer = new XmlSerializer(Content.GetType());

                serializer.Serialize(writer, Content);
            }
        }

        /// <inheritdoc/>
        public XmlSchema GetSchema()
        {
            return null;
        }
#endif
    }
}
