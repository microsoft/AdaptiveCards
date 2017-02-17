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
    /// When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web browser or showing in-situ with embedded web browser.
    /// </summary>
    public class ActionOpenUrl : ActionBase
    {
        public ActionOpenUrl()
        {

        }

        /// <summary>
        /// Url to open using default operating system browser
        /// </summary>
        [JsonRequired]
        public string Url { get; set; }
    }
}
