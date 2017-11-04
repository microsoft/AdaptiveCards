using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveCardParseResult
    {
        /// <summary>
        /// The parsed card object
        /// </summary>
        public AdaptiveCard Card { get; set; }

        /// <summary>
        /// If any modifications were done to the parsed card they will be reported here
        /// </summary>
        public IList<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();   
    }
}
