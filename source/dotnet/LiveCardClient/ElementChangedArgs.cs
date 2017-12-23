using AdaptiveCards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardClient
{
    public class ElementChangedArgs
    {
        public AdaptiveElement Element { get; set; }
    }

    public class CardChangedArgs
    {
        public AdaptiveCard Card { get; set; }
    }
}