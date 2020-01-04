using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class AdaptiveCardsTemplatingVisitorResult
    {
        private List<string> keys = new List<string>();
        private string tokens;

        public AdaptiveCardsTemplatingVisitorResult(string tokens = "")
        {
            this.tokens = tokens;
        }

        public List<string> Keys { get => keys; set => keys = value; }
        public string Tokens { get => tokens; set => tokens = value; }
    }
}
