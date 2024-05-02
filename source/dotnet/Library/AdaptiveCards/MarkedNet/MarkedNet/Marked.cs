using System;

#pragma warning disable CS1591
namespace Microsoft.MarkedNet
{
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
}
