using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;


namespace Microsoft.MarkedNet
{
    public class MarkdownRenderer
    {
        #region Properties

        public Options Options { get; set; }

        #endregion

        #region Constructors

        public MarkdownRenderer()
            : this(null)
        {
        }

        public MarkdownRenderer(Options options)
        {
            Options = options ?? new Options();
        }

        #endregion

        #region Methods

        #region Block Level Renderer

        public virtual string Code(string code, string lang, bool escaped)
        {
            if (Options.Highlight != null)
            {
                var @out = Options.Highlight(code, lang);
                if (@out != null && @out != code)
                {
                    escaped = true;
                    code = @out;
                }
            }

            if (String.IsNullOrEmpty(lang))
            {
                return "<pre><code>" + (escaped ? code : StringHelper.Escape(code, true)) + "\n</code></pre>";
            }

            return "<pre><code class=\""
                + Options.LangPrefix
                + StringHelper.Escape(lang, true)
                + "\">"
                + (escaped ? code : StringHelper.Escape(code, true))
                + "\n</code></pre>\n";
        }

        public virtual string Blockquote(string quote)
        {
            return "<blockquote>\n" + quote + "</blockquote>\n";
        }

        public virtual string Html(string html)
        {
            return html;
        }

        public virtual string Heading(string text, int level, string raw)
        {
            return "<h"
                + level
                + " id=\""
                + Options.HeaderPrefix
                + Regex.Replace(raw.ToLower(), @"[^\w]+", "-")
                + "\">"
                + text
                + "</h"
                + level
                + ">\n";
        }

        public virtual string Hr()
        {
            return Options.XHtml ? "<hr/>\n" : "<hr>\n";
        }

        public virtual string List(string body, bool ordered, int start)
        {
            var type = ordered ? "ol" : "ul";
            if (ordered && start != 1)
                return $"<ol start=\"{start}\">\n{body}\n</ol>\n";
            return "<" + type + ">\n" + body + "</" + type + ">\n";
        }

        public virtual string ListItem(string text)
        {
            return "<li>" + text + "</li>\n";
        }

        public virtual string Paragraph(string text)
        {
            return "<p>" + text + "</p>\n";
        }

        public virtual string Table(string header, string body)
        {
            return "<table>\n"
                + "<thead>\n"
                + header
                + "</thead>\n"
                + "<tbody>\n"
                + body
                + "</tbody>\n"
                + "</table>\n";
        }

        public virtual string TableRow(string content)
        {
            return "<tr>\n" + content + "</tr>\n";
        }

        public virtual string TableCell(string content, TableCellFlags flags)
        {
            var type = flags.Header ? "th" : "td";
            var tag = !String.IsNullOrEmpty(flags.Align)
                ? "<" + type + " style=\"text-align:" + flags.Align + "\">"
                : "<" + type + ">";

            return tag + content + "</" + type + ">\n";
        }

        #endregion

        #region Span Level Renderer

        public virtual string Strong(string text)
        {
            return "<strong>" + text + "</strong>";
        }

        public virtual string Em(string text)
        {
            return "<em>" + text + "</em>";
        }

        public virtual string Codespan(string text)
        {
            return "<code>" + text + "</code>";
        }

        public virtual string Br()
        {
            return Options.XHtml ? "<br/>" : "<br>";
        }

        public virtual string Del(string text)
        {
            return "<del>" + text + "</del>";
        }

        public virtual string Link(string href, string title, string text)
        {
            if (Options.Sanitize)
            {
                string prot = null;
                
                try
                {
                    prot = Regex.Replace(StringHelper.DecodeURIComponent(StringHelper.Unescape(href)), @"[^\w:]", String.Empty).ToLower();
                }
                catch (Exception)
                {
                    return String.Empty;
                }

                if (prot.IndexOf("javascript:") == 0 || prot.IndexOf("vbscript:") == 0)
                {
                    return String.Empty;
                }
            }

            var @out = "<a href=\"" + href + "\"";
            if (!String.IsNullOrEmpty(title))
            {
                @out += " title=\"" + title + "\"";
            }

            @out += ">" + text + "</a>";
            return @out;
        }

        public virtual string Image(string href, string title, string text)
        {
            var @out = "<img src=\"" + href + "\" alt=\"" + text + "\"";
            if (!String.IsNullOrEmpty(title))
            {
                @out += " title=\"" + title + "\"";
            }

            @out += Options.XHtml ? "/>" : ">";
            return @out;
        }

        public virtual string Text(string text)
        {
          return text;
        }

        /// <summary>
        /// Preprocess entire input before parsing
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public virtual string Preprocess(string text)
        {
            return text;
        }

        /// <summary>
        /// ppostprocess entire output before returning
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public virtual string Postprocess(string text)
        {
            return text;
        }
    
        #endregion

        #endregion
    }
}
