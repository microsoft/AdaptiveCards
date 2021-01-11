using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.MarkedNet;

namespace Microsoft.MarkedNet
{
    /// <summary>
    /// Renderer which renders to HTML with Emoji Support
    /// </summary>
    public class HtmlRenderer : EmojiMarkdownRenderer
    {
        public HtmlRenderer() : base()
        {
        }

        public HtmlRenderer(Options options) : base(options)
        {
        }
    }
}
