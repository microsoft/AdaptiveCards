using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveCardParseResult
    {
        public AdaptiveCard Card { get; private set; }

        internal AdaptiveCardParseResult(AdaptiveCard card)
        {
            Card = card;
        }
    }
}
