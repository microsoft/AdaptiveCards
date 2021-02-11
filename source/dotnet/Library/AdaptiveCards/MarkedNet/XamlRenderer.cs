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
    public class XamlRenderer : EmojiMarkdownRenderer
    {
        public XamlRenderer() : base()
        {
        }

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string CodeStyle { get; set; } = null;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string CodespanStyle { get; set; } = null;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string BlockQuoteStyle { get; set; } = null;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string CodeSpanStyle { get; set; } = String.Empty;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string[] HeadingStyles { get; set; } = new string[] { String.Empty, String.Empty, String.Empty, String.Empty, String.Empty, String.Empty };

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string OrderedListStyle { get; set; } = String.Empty;
        
        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string UnorderedListStyle{ get; set; } = String.Empty;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string ImageStyle { get; set; } = String.Empty;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string ImageTitleStyle { get; set; } = String.Empty;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string ParagraphStyle { get; set; } = String.Empty;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string CellHeaderStyle { get; set; } = String.Empty;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string CellStyle { get; set; } = String.Empty;

        /// <summary>
        ///  set style as string -> Style=\"..." 
        /// </summary>
        public string ListItemStyle { get; set; } = String.Empty;

        public XamlRenderer(Options options) : base(options)
        {
        }

        public override string Blockquote(string quote)
        {
            return quote.Replace(ParagraphStyle, BlockQuoteStyle);
        }

        public override string Br()
        {
            return "<LineBreak/>\n";
        }

        public override string Code(string code, string lang, bool escaped)
        {
            return $"<Paragraph {CodeStyle}\">" + code.Replace("\r\n", "<LineBreak/>") + "</Paragraph>\n";
        }

        public override string Codespan(string text)
        {
            return $"<Run {CodespanStyle}>{text}</Run>\n";
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
            return $"<Paragraph {HeadingStyles[level-1]}>{text}</Paragraph>\n";
        }

        public override string Hr()
        {
            return "<Paragraph>_____________________________</Paragraph>\n";
        }

        public override string Html(string html)
        {
            return String.Empty;
        }

        public override string Image(string href, string title, string text)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("<Grid><Grid.RowDefinitions><RowDefinition Height=\"*\"/><RowDefinition Height=\"Auto\"/></Grid.RowDefinitions>");
            sb.AppendLine($"<Button Command=\"NavigationCommands.GoToPage\" CommandParameter=\"{href}\"><Image Source=\"{href}\" ToolTip=\"{title}\" {ImageStyle}\"/></Button>");
            if (!String.IsNullOrEmpty(text))
                sb.AppendLine($"<TextBlock Grid.Row=\"1\" HorizontalAlignment=\"Center\" {ImageTitleStyle}>{text}</TextBlock>");
            sb.AppendLine("</Grid><LineBreak/>");
            return sb.ToString();
        }

        public override string Link(string href, string title, string text)
        {
            return $"<Hyperlink Command=\"NavigationCommands.GoToPage\" CommandParameter=\"{href}\">{text}</Hyperlink>";
        }

        public override string List(string body, bool ordered, int start)
        {
            StringBuilder sb = new StringBuilder();
            if (ordered)
                sb.AppendLine($"<List MarkerStyle=\"Decimal\" StartIndex=\"{start}\" {OrderedListStyle}>");
            else
                sb.AppendLine($"<List {UnorderedListStyle}>");
            sb.AppendLine(body);
            sb.AppendLine("</List>");
            return sb.ToString();
        }

        public override string ListItem(string text)
        {
            return $"<ListItem {ListItemStyle}>{Paragraph(text)}</ListItem>\n";
        }

        public override string Paragraph(string text)
        {
            if (text.StartsWith("<Paragraph"))
                return $"{text}\n";
            else
                return $"<Paragraph {ParagraphStyle}>{text}</Paragraph>\n";
        }

        public override string Strong(string text)
        {
            return $"<Bold>{text}</Bold>";
        }

        public override string Table(string header, string body)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("<Table><TableRowGroup Paragraph.TextAlignment=\"Left\">");
            sb.AppendLine(header);
            sb.AppendLine(body);
            sb.AppendLine("</TableRowGroup></Table>");
            return sb.ToString();
        }

        public override string TableRow(string content)
        {
            return $"<TableRow>{content}</TableRow>\n";
        }


        public override string TableCell(string content, TableCellFlags flags)
        {
            StringBuilder sb = new StringBuilder();

            switch (flags.Align)
            {
                case "right":
                    if (flags.Header)
                        return $"<TableCell TextAlignment=\"Right\" {CellHeaderStyle}><Paragraph>{content.Trim()}</Paragraph></TableCell>";
                    return $"<TableCell TextAlignment=\"Right\" {CellStyle}><Paragraph>{content.Trim()}</Paragraph></TableCell>";
                case "center":
                    if (flags.Header)
                        return $"<TableCell TextAlignment=\"Center\" {CellHeaderStyle}><Paragraph>{content.Trim()}</Paragraph></TableCell>";
                    return $"<TableCell TextAlignment=\"Center\" {CellStyle}><Paragraph>{content.Trim()}</Paragraph></TableCell>";
                case "left":
                default:
                    if (flags.Header)
                        return $"<TableCell TextAlignment=\"Left\" {CellHeaderStyle}><Paragraph>{content.Trim()}</Paragraph></TableCell>";
                    return $"<TableCell TextAlignment=\"Left\" {CellStyle}><Paragraph>{content.Trim()}</Paragraph></TableCell>";
            }
        }

    }
}
