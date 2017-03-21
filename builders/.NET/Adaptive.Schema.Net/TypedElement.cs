using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
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
        public string Type { get; set; }
    }
}
