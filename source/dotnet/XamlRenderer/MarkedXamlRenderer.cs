using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MarkedNet;

namespace Adaptive
{

    /// <summary>
    /// Renderer which renders to pure text environments like SMS
    /// </summary>
    public class MarkedXamlRenderer : Renderer
    {
        public MarkedXamlRenderer() : base()
        {
        }

        public MarkedXamlRenderer(Options options) : base(options)
        {
        }

        public override string Blockquote(string quote)
        {
            // not supported
            return String.Empty;
        }

        public override string Br()
        {
            return "<LineBreak/>\n";
        }

        public override string Code(string code, string lang, bool escaped)
        {
            // not supported
            return string.Empty;
        }

        public override string Codespan(string text)
        {
            return "<Run FontFamily=\"Consolas\">" + text + "</Run>\n";
        }

        public override string Del(string text)
        {
            return $"<Run TextDecorations=\"Strikethrough\">{text}</Run>";
        }

        public override string Em(string text)
        {
            return $"<Italic>{text}</Italic>";
        }

        public override string Heading(string text, int level, string raw)
        {
            return text;
        }

        public override string Hr()
        {
            // not supported
            return String.Empty;
        }

        public override string Html(string html)
        {
            // not supported
            return String.Empty;
        }

        public override string Image(string href, string title, string text)
        {
            // not supported
            return String.Empty;
        }

        public override string Link(string href, string title, string text)
        {
            return $"<Hyperlink Command=\"NavigationCommands.GoToPage\" CommandParameter=\"{href}\">{text}</Hyperlink>";
        }

        public override string List(string body, bool ordered)
        {
            // not supported
            return String.Empty;
        }

        public override string ListItem(string text)
        {
            // not supported
            return String.Empty;
        }

        public override string Paragraph(string text)
        {
            // not supported
            return text;
        }

        public override string Strong(string text)
        {
            return $"<Bold>{text}</Bold>";
        }

        public override string Table(string header, string body)
        {
            // not supported
            return string.Empty;
        }

        public override string TableRow(string content)
        {
            // not supported
            return string.Empty;
        }

        public override string TableCell(string content, TableCellFlags flags)
        {
            // not supported
            return string.Empty;
        }
    }
}
