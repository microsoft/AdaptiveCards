using Newtonsoft.Json;

namespace AdaptiveCards
{
    /// <summary>
    ///     When ActionOpenUrl is invoked it will show the given url, either by launching it to an external web browser or
    ///     showing in-situ with embedded web browser.
    /// </summary>
    public class AdaptiveOpenUrlAction : AdaptiveAction
    {
        public const string TypeName = "Action.OpenUrl";

        public override string Type => TypeName;

        /// <summary>
        ///     Url to open using default operating system browser
        /// </summary>
        [JsonRequired]
        public string Url { get { return _Url; } set { SetValue(ref _Url, value); } }
        private string _Url;

    }
}