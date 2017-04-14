using System.Collections.Generic;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.Xml.Serialization;

namespace AdaptiveCards
{
    /// <summary>
    ///     The ActionSet element makes it simple to display a se ries of "facts" (e.g. name/value pairs) in a tabular form.
    /// </summary>
    public class ActionSet : CardElement
    {
        public const string TYPE = "ActionSet";

        public ActionSet()
        {
            Type = TYPE;
        }

        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
#if NET452
        [XmlArray("Actions")]
        [XmlArrayItem(ElementName = OpenUrlAction.TYPE, Type = typeof(OpenUrlAction))]
        [XmlArrayItem(ElementName = ShowCardAction.TYPE, Type = typeof(ShowCardAction))]
        [XmlArrayItem(ElementName = SubmitAction.TYPE, Type = typeof(SubmitAction))]
        [XmlArrayItem(ElementName = HttpAction.TYPE, Type = typeof(HttpAction))]
#endif
        public List<ActionBase> Actions { get; set; } = new List<ActionBase>();
    }
}