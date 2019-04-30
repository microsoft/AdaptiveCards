using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CardHub.Interfaces
{
    public class UpdateCardRequest
    {
        public string Token { get; set; }

        public CardData CardData { get; set; }
    }
}
