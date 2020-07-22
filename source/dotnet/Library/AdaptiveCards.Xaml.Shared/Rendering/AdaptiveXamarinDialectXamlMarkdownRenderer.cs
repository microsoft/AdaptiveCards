using System;
using System.Collections.Generic;
using Microsoft.MarkedNet;

namespace AdaptiveCards.Rendering.Wpf
{
    public class AdaptiveXamarinDialectXamlMarkdownRenderer : MarkdownRenderer
    {
        public AdaptiveXamarinDialectXamlMarkdownRenderer() : base()
        {
        }

        public AdaptiveXamarinDialectXamlMarkdownRenderer(Options options) : base(options)
        {
        }

        private const string LIST_MARKER = "<ListMarker/>";

        private const string NEWLINE_MARKER = "<NEWLINE/>";

        private const string NEWLINE_SPAN_TEXT = "<Span.Text>\r\n</Span.Text>";

        private const string LINE_BREAK = "<Span>" + NEWLINE_MARKER + "</Span>\r\n";

        private const string SPAN_DECLARATION = "<Span {0} Text=\"{1}\">{2}</Span>\r\n";

        public override string Blockquote(string quote)
        {
            // not supported
            return String.Empty;
        }

        public override string Br()
        {
            return LINE_BREAK;
        }

        public override string Code(string code, string lang, bool escaped)
        {
            // not supported
            return string.Empty;
        }

        public override string Codespan(string text)
        {
            const string ATTRIBUTES = "FontFamily=\"Consolas\"";

            return "\r\n" + string.Format(SPAN_DECLARATION, ATTRIBUTES, text, "");
        }

        public override string Del(string text)
        {
            const string ATTRIBUTES = "TextDecorations=\"Strikethrough\"";

            return "\r\n" + string.Format(SPAN_DECLARATION, ATTRIBUTES, text, "");
        }

        public override string Em(string text)
        {
            const string ATTRIBUTES = "FontAttributes=\"Italic\"";

            return "\r\n" + string.Format(SPAN_DECLARATION, ATTRIBUTES, text, "");
        }

        public override string Heading(string text, int level, string raw)
        {
            return string.Format(SPAN_DECLARATION, "", text, "") + LINE_BREAK;
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
            var xamlString = "<Span.GestureRecognizers>" +
                             "<TapGestureRecognizer Command=\"{Binding ClickCommand}\"" +
                             $"CommandParameter=\"{href}\" />" +
                             "</Span.GestureRecognizers>";
            const string ATTRIBUTES = "TextColor=\"CornflowerBlue\" TextDecorations=\"Underline\"";

            return string.Format(SPAN_DECLARATION, ATTRIBUTES, title, xamlString);
        }

        public override string List(string body, bool ordered, int start)
        {
            if (ordered)
            {
                int outputNum;
                int iMarker;
                for (outputNum = start, iMarker = body.IndexOf(LIST_MARKER);
                    iMarker > 0;
                    iMarker = body.IndexOf(LIST_MARKER), outputNum++)
                {
                    body = body.Remove(iMarker, LIST_MARKER.Length).Insert(iMarker, outputNum.ToString() + ".");
                }
            }
            else
            {
                body = body.Replace(LIST_MARKER, "•");
            }
            return $"{body}"+ LINE_BREAK;
        }

        public override string ListItem(string text)
        {
            return $" {LIST_MARKER} {text}"+LINE_BREAK;
        }

        public override string Paragraph(string text)
        {
            return text;
        }

        public override string Strong(string text)
        {
            const string ATTRIBUTES = "FontAttributes=\"Bold\"";

            return "\r\n" + string.Format(SPAN_DECLARATION, ATTRIBUTES, text, "");
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

        public override string Postprocess(string text)
        {
            string[] lines = text.Split(new []{'\r'}, StringSplitOptions.None);
            List<string> processedLines = new List<string>();

            for (int i = 0; i < lines.Length; i++)
            {
                string line = lines[i].TrimStart('\n');

                if (!line.StartsWith("<", StringComparison.Ordinal))
                {
                    line = string.Format(SPAN_DECLARATION, "", line, "");
                    processedLines.Add(line);
                }
                else
                {
                    processedLines.Add(lines[i]);
                }
            }

            string spansXaml = string.Join("\r", processedLines);

            spansXaml = spansXaml.Replace(NEWLINE_MARKER, NEWLINE_SPAN_TEXT);

            spansXaml = $"<FormattedString>{spansXaml}</FormattedString>";

            return base.Postprocess(spansXaml);
        }
    }
}
