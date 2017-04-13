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
        public ActionSet()
        {
            Type = "ActionSet";
        }

        /// <summary>
        ///     The facts to be displayed.
        /// </summary>
        [JsonRequired]
#if NET452
        [XmlElement(ElementName="Action", Type=typeof(ActionBase))]
#endif
        public List<ActionBase> Actions { get; set; } = new List<ActionBase>();
    }
}