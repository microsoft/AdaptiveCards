using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive
{
    [JsonConverter(typeof(TypedElementConverter))]
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public partial class TypedElement
    {
        public TypedElement()
        {
            this.Type = GetType().Name;
        }

        [JsonProperty(Order = -2, NullValueHandling = NullValueHandling.Ignore)]
        [JsonRequired]
        [XmlIgnore]
        public string Type { get; set; }

        protected EnumT? GetEnum<EnumT>(string value)
            where EnumT :struct
        {
            EnumT val;
            if (Enum.TryParse<EnumT>(value, out val))
                return val;
            return null;
        }

        protected int? GetInt(string value)
        {
            int val;
            if (int.TryParse(value, out val))
                return val;
            return null;
        }
        protected bool? GetBool(string value)
        {
            bool val;
            if (bool.TryParse(value, out val))
                return val;
            return null;
        }
    }
}
