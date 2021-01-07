using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.MarkedNet;

namespace Microsoft.MarkedNet
{
    /// <summary>
    /// Renderer which renders emoji markdown to unicode 
    /// </summary>
    public class EmojiMarkdownRenderer : MarkdownRenderer
    {
        public EmojiMarkdownRenderer() : base()
        {
        }

        public EmojiMarkdownRenderer(Options options) : base(options)
        {
        }

        public override string Preprocess(string text)
        {
            return EmojiConverter.ConvertMarkupToEmoji(text);
        }
    }
}
