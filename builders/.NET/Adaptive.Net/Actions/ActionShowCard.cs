using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace Adaptive
{

    /// <summary>
    /// ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.
    /// </summary>
    public partial class ActionShowCard: ActionBase
    {
        public ActionShowCard()
        {

        }

        /// <summary>
        /// Container card to show when the action is invoked
        /// </summary>
        [JsonRequired]
        public Container Card { get; set; }
    }
}
