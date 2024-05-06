using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Microsoft.MarkedNet
{
#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
    public class Marked
    {
        public Options Options { get; set; }


        public Marked()
            : this(null)
        {
        }

        public Marked(Options options)
        {
            Options = options ?? new Options();
        }


        public virtual string Parse(string src)
        {
            if (String.IsNullOrEmpty(src))
            {
                return src;
            }

            src = Options.Renderer.Preprocess(src);
            var tokens = Lexer.Lex(src, Options);
            var result = Parser.Parse(tokens, Options);
            return Options.Renderer.Postprocess(result);
        }
    }
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
}
