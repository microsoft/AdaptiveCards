// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    public class SerializableDictionary<TValue> : Dictionary<string, TValue>
#if !NETSTANDARD1_3
        , IXmlSerializable
#endif
    {
        public SerializableDictionary()
            : base()
        {
        }

        public SerializableDictionary(IEqualityComparer<string> comparer)
            : base(comparer)
        {
        }

#if !NETSTANDARD1_3
        #region IXmlSerializable Members
        public System.Xml.Schema.XmlSchema GetSchema()
        {
            return null;
        }

        [XmlType(TypeName = "Property")]
        public class Property
        {
            [JsonProperty]
            [XmlAttribute]
            public string Name { get; set; }

            [XmlElement]
            public TValue Value { get; set; }
        }

        public void ReadXml(System.Xml.XmlReader reader)
        {
            reader.Read();
            reader.MoveToContent();
            while (reader.IsStartElement())
            {
                var name = reader.GetAttribute("Name");
                var valueType = reader.GetAttribute("Type");
                object value = reader.ReadElementContentAsObject();
                switch (valueType)
                {
                    case "integer":
                        value = Int64.Parse(value.ToString());
                        break;
                    case "number":
                        value = Single.Parse(value.ToString());
                        break;
                    case "boolean":
                        value = Boolean.Parse(value.ToString());
                        break;
                }

                //var obj = reader.ReadContentAsObject();
                this.Add(name, (TValue)value);
            }
            reader.ReadEndElement();
        }

        public void WriteXml(System.Xml.XmlWriter writer)
        {

            foreach (string key in this.Keys)
            {
                writer.WriteStartElement(nameof(Property));
                writer.WriteAttributeString("Name", key);
                TValue value = this[key];
                string valueType = "string";
                switch (value.GetType().Name)
                {
                    case "Boolean":
                        valueType = "bool";
                        break;
                    case "Single":
                    case "Double":
                        valueType = "number";
                        break;
                    case "Int32":
                    case "Int64":
                    case "Int16":
                    case "UInt16":
                    case "UInt32":
                    case "UInt64":
                        valueType = "integer";
                        break;
                }
                if (valueType != "string")
                {
                    writer.WriteAttributeString("Type", valueType);
                }

                writer.WriteValue(value);
                writer.WriteEndElement();
            }
        }
        #endregion
#endif
    }
}
