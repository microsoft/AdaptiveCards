using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive.Schema.Net
{
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class TargetUri
    {
        public TargetUri() { }

        public string Os { get; set; }

        [JsonRequired]
        public string Uri { get; set; }
    }

    public class ViewAction : ExternalAction
    {
        public ViewAction() : base() { }

        [JsonRequired]
        public List<TargetUri> Targets { get; set; } = new List<TargetUri>();
    }

    public class OpenUriAction : ViewAction
    {

    }
}
