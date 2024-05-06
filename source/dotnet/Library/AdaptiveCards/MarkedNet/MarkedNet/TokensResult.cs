using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.MarkedNet
{
#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
    public class TokensResult
    {
        public IList<Token> Tokens { get; set; }
        public IDictionary<string, LinkObj> Links { get; set; }
        public int Length { get { return Tokens.Count; } }

        public IEnumerable<Token> Reverse()
        {
            return Tokens.Reverse();
        }

        public TokensResult()
        {
            Tokens = new List<Token>();
            Links = new Dictionary<string, LinkObj>();
        }


        public void Add(Token token)
        {
            Tokens.Add(token);
        }
    }
}
