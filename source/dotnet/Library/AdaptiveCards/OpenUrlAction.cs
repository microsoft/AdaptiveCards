using Newtonsoft.Json;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web browser or
    ///     showing in-situ with embedded web browser.
    /// </summary>
    public class OpenUrlAction : ActionBase
    {
        public const string TYPE = "Action.OpenUrl";

        public OpenUrlAction()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     Url to open using default operating system browser
        /// </summary>
        [JsonRequired]
#if NET45
        [XmlAttribute]
#endif
        public string Url { get; set; }
    }
}