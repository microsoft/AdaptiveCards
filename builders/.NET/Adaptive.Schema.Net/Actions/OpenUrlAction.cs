using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive.Schema.Net
{

    /// <summary>
    /// When OpenUrlAction is invoked it will show the given url, either by launching it to an external web browser or showing in-situ with embedded web browser.
    /// </summary>
    public class OpenUrlAction : ActionBase
    {
        public OpenUrlAction()
        {

        }

        /// <summary>
        /// Url to open using default operating system browser
        /// </summary>
        [JsonRequired]
        public string Url { get; set; }

        /// <summary>
        /// Platform specific urls to use 
        /// </summary>
        public List<PlatformUrl> PlatformUrls { get; set; } = new List<PlatformUrl>();
    }


    /// <summary>
    /// PlatformUrl
    /// </summary>
    [JsonObject(NamingStrategyType = typeof(CamelCaseNamingStrategy))]
    public class PlatformUrl
    {
        public PlatformUrl() { }

        /// <summary>
        /// Os = {ios, android, windows}
        /// </summary>
        public string Os { get; set; }

        /// <summary>
        /// Url to open
        /// </summary>
        [JsonRequired]
        public string Url { get; set; }
    }
}
