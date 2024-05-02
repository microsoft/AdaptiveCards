#pragma warning disable CS1591
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
