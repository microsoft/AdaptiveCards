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
    /// When CancelAction is invoked it resets any input that is in scope, and closes a card if it is part of a card which was shown via ShowCardAction.
    /// </summary>
    public class CancelAction : Action
    {
        public CancelAction()
        {
        }
    }
}
