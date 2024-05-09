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
        /// <summary>
        /// Constructor
        /// </summary>
        public EmojiMarkdownRenderer() : base()
        {
        }

        /// <summary>
        /// Constructor with options
        /// </summary>
        /// <param name="options"></param>
        public EmojiMarkdownRenderer(Options options) : base(options)
        {
        }

        /// <summary>
        /// Process text before it's used.
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public override string Preprocess(string text)
        {
            return EmojiConverter.ConvertMarkupToEmoji(text);
        }
    }
}
