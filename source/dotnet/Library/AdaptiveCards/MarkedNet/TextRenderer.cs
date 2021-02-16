using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.MarkedNet;

namespace Microsoft.MarkedNet
{
    /// <summary>
    /// Renderer which renders to pure text environments like SMS
    /// </summary>
    public class TextMarkdownRenderer : EmojiMarkdownRenderer
    {
        public TextMarkdownRenderer() : base()
        {
        }

        public TextMarkdownRenderer(Options options) : base(options)
        {
        }

        public override string Blockquote(string quote)
        {
            string[] lines = quote.Replace("\r", "").TrimEnd('\n').Split('\n');
            return String.Format("> {0}\n", String.Join("\n> ", lines));
        }

        public override string Br()
        {
            // NOTE: This HTML tag will be replaced by a newline in the call to Paragraph(), below.
            // If you override Paragraph(), you must account for this tag appearing in the stream!
            // The purpose of this tag is to mark a place in the content where we should visually
            // inticate a new paragraph in the rendered output, even though only one newline was
            // present.An example of this is whenever a newline is preceeded by two space characters,
            // e.g.: "This is line 1.  \nThis is line 2.\nThis is also line 2."
            return "<br/>";
        }

        public override string Code(string code, string lang, bool escaped)
        {
            return code + "\n";
        }

        public override string Codespan(string text)
        {
            return text;
        }

        public override string Del(string text)
        {
            return $"-{text}-";
        }

        public override string Em(string text)
        {
            return $"{text}";
        }

        public override string Heading(string text, int level, string raw)
        {
#if UNDERLINE
            char underline = '=';
            switch (level)
            {
                case 1: underline = '='; break;
                case 2: underline = '-'; break;
                default: underline = '.'; break;
            }
            StringBuilder sb = new StringBuilder();
            sb.AppendLine(text);
            sb.AppendLine(new string(underline, text.Length));
            return sb.ToString();
#else
            return $"{new string('#', level)} {text} {new string('#', level)}\n";
#endif
        }

        public override string Hr()
        {
            return new string('_', 20) + "\n";
        }

        public override string Html(string html)
        {
            return string.Empty;
        }

        public override string Image(string href, string title, string text)
        {
            return href;
        }

        public override string Link(string href, string title, string text)
        {
            if (!String.IsNullOrEmpty(text) && text != href)
                return $"{text} {href.Replace("&amp;", "&")}";
            if (!String.IsNullOrEmpty(title) && title != href)
                return $"{title} {href.Replace("&amp;", "&")}";
            return href.Replace("&amp;", "&");
        }

        public override string List(string body, bool ordered, int start)
        {
            StringBuilder sb = new StringBuilder();
            var lines = body.Split(new char[] { '\u2028' }, StringSplitOptions.RemoveEmptyEntries);
            if (ordered)
            {
                int i = start;
                foreach (var line in lines)
                {
                    sb.AppendLine($"{i++}. {line}");
                }
            }
            else
            {
                foreach (var line in lines)
                {
                    sb.AppendLine($"* {line}");
                }
            }
            return sb.Replace("\r\n", "\n").Replace("\n", "\r\n").ToString();
        }

        public override string ListItem(string text)
        {
            return $"{text}\u2028";
        }

        public override string Paragraph(string text)
        {
            // If you override Paragraph(), you must account for the <br/> appearing in the stream! It
            // has a special meaning here. Please read explanatory comment in the Br() method, above.
            return text.Replace("\n", " ").Replace("<br/>","\n") + "\n";
        }

        public override string Strong(string text)
        {
            return $"*{text}*";
        }

        public override string Table(string header, string body)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(header);
            sb.Append('\u2028');
            sb.Append(body);
            string[] lines = sb.ToString().Split(new[] { "\u2028" }, StringSplitOptions.RemoveEmptyEntries);
            int[] widths = null;

            foreach (var line in lines)
            {
                string[] cells = line.Trim('\u2000', '\u2001').Split('\u2000', '\u2001');
                if (widths == null)
                    widths = new int[cells.Length * 2];

                for (int i = 0; i < cells.Length; i++)
                {
                    var cell = cells[i].Trim(':');
                    if (cell.Length > widths[i])
                        widths[i] = cell.Length;
                }
            }
            sb.Clear();
            bool needHeader = !String.IsNullOrEmpty(header);

            foreach (var line in lines)
            {
                string[] cells = line.Trim('\u2000', '\u2001').Split('\u2000', '\u2001');

                var sbHeader = new StringBuilder();

                int iCell = 0;
                foreach (var cell in cells)
                {
                    if (cell.StartsWith(":") && cell.EndsWith(":"))
                    {
                        var c = cell.Trim(':');

                        // center
                        int left = (widths[iCell] - c.Length) / 2;

                        sb.Append($"|{c.PadLeft(left + c.Length).PadRight(widths[iCell])}");
                    }
                    else if (cell.EndsWith(":"))
                    {
                        var c = cell.Trim(':');
                        // right alighn
                        sb.Append($"|{c.PadLeft(widths[iCell])}");
                    }
                    else
                    {
                        var c = cell.Trim(':');
                        // left align
                        sb.Append($"|{c.PadRight(widths[iCell])}");
                    }
                    if (needHeader)
                        sbHeader.Append($"|{new string('-', widths[iCell])}");
                    iCell++;
                }
                sb.Append("|\n");
                if (needHeader)
                {
                    sbHeader.Append("|\n");
                    sb.Append(sbHeader);
                    needHeader = false;
                }
            }

            return sb.ToString();
        }

        public override string TableRow(string content)
        {
            return content + "\u2028";
        }


        public override string TableCell(string content, TableCellFlags flags)
        {
            StringBuilder sb = new StringBuilder();

            switch (flags.Align)
            {
                case "right":
                    if (flags.Header)
                        return $"\u2000{content.Trim()}:";
                    return $"\u2001{content.Trim()}:";
                case "center":
                    if (flags.Header)
                        return $"\u2000:{content.Trim()}:";
                    return $"\u2001:{content.Trim()}:";
                case "left":
                default:
                    if (flags.Header)
                        return $"\u2001:{content.Trim()}";
                    return $"\u2000:{content.Trim()}";
            }
        }

        public override string Postprocess(string text)
        {
            return text.Replace("&lt;", "<")
                .Replace("&gt;", ">")
                .Replace("&amp;", "&")
                .Replace("&quot;", "\"")
                .Replace("&#39;", "'"); 
        }
    }
}
