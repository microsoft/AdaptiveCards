using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web browser or
    ///     showing in-situ with embedded web browser.
    /// </summary>
    public class ActionOpenUrl : ActionBase
    {
        public ActionOpenUrl()
        {
            Type = "Action.OpenUrl";
        }

        /// <summary>
        ///     Url to open using default operating system browser
        /// </summary>
        [JsonRequired]
#if DESKTOP
        [XmlAttribute]
#endif
        public string Url { get; set; }
    }
}