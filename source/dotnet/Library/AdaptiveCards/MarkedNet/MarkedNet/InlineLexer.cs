using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;


namespace Microsoft.MarkedNet
{
    /// <summary>
    /// Inline Lexer & Compiler
    /// </summary>
    public class InlineLexer
    {
        private Random _random = new Random();

        private Options _options;
        private InlineRules _rules;
        private IDictionary<string, LinkObj> links;
        private bool inLink;


        public InlineLexer(IDictionary<string, LinkObj> links, Options options)
        {
            _options = options ?? new Options();

            this.links = links;
            this._rules = new NormalInlineRules();

            if (this.links == null)
            {
                throw new Exception("Tokens array requires a `links` property.");
            }

            if (_options.Gfm)
            {
                if (this._options.Breaks)
                {
                    _rules = new BreaksInlineRules();
                }
                else
                {
                    _rules = new GfmInlineRules();
                }
            }
            else if (this._options.Pedantic)
            {
                _rules = new PedanticInlineRules();
            }
        }



        /// <summary>
        /// Lexing/Compiling
        /// </summary>
        public virtual string Output(string src)
        {
            var @out = String.Empty;
            LinkObj link;
            string text;
            string href;
            IList<string> cap;

            while (!String.IsNullOrEmpty(src))
            {
                // escape
                cap = this._rules.Escape.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    @out += cap[1];
                    continue;
                }

                // autolink
                cap = this._rules.AutoLink.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    if (cap[2] == "@")
                    {
                        text = cap[1][6] == ':'
                          ? this.Mangle(cap[1].Substring(7))
                          : this.Mangle(cap[1]);
                        href = this.Mangle("mailto:") + text;
                    }
                    else
                    {
                        text = this.EscapeHtml(cap[1]);
                        href = text;
                    }
                    @out += _options.Renderer.Link(href, null, text);
                    continue;
                }

                // url (gfm)
                if (!this.inLink && (cap = this._rules.Url.Exec(src)).Any())
                {
                    src = src.Substring(cap[0].Length);
                    text = this.EscapeHtml(cap[1]);
                    href = text;
                    @out += _options.Renderer.Link(href, null, text);
                    continue;
                }

                // tag
                cap = this._rules.Tag.Exec(src);
                if (cap.Any())
                {
                    if (!this.inLink && Regex.IsMatch(cap[0], "^<a ", RegexOptions.IgnoreCase))
                    {
                        this.inLink = true;
                    }
                    else if (this.inLink && Regex.IsMatch(cap[0], @"^<\/a>", RegexOptions.IgnoreCase))
                    {
                        this.inLink = false;
                    }
                    src = src.Substring(cap[0].Length);
                    @out += this._options.Sanitize
                      ? (this._options.Sanitizer != null)
                        ? this._options.Sanitizer(cap[0])
                        : this.EscapeHtml(cap[0])
                      : cap[0];
                    continue;
                }

                // link
                cap = this._rules.Link.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    this.inLink = true;
                    @out += this.OutputLink(cap, new LinkObj
                    {
                        Href = cap[2],
                        Title = cap[3]
                    });
                    this.inLink = false;
                    continue;
                }

                // reflink, nolink
                if ((cap = this._rules.RefLink.Exec(src)).Any() || (cap = this._rules.NoLink.Exec(src)).Any())
                {
                    src = src.Substring(cap[0].Length);
                    var linkStr = (StringHelper.NotEmpty(cap, 2, 1)).ReplaceRegex(@"\s+", " ");
                    
                    this.links.TryGetValue(linkStr.ToLower(), out link);
                    
                    if (link == null || String.IsNullOrEmpty(link.Href))
                    {
                        @out += cap[0][0];
                        src = cap[0].Substring(1) + src;
                        continue;
                    }
                    this.inLink = true;
                    @out += this.OutputLink(cap, link);
                    this.inLink = false;
                    continue;
                }

                // strong
                if ((cap = this._rules.Strong.Exec(src)).Any())
                {
                    src = src.Substring(cap[0].Length);
                    @out += _options.Renderer.Strong(this.Output(StringHelper.NotEmpty(cap, 2, 1)));
                    continue;
                }

                // em
                cap = this._rules.Em.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    @out += _options.Renderer.Em(this.Output(StringHelper.NotEmpty(cap, 2, 1)));
                    continue;
                }

                // code
                cap = this._rules.Code.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    @out += _options.Renderer.Codespan(this.EscapeHtml(cap[2], true));
                    continue;
                }

                // br
                cap = this._rules.Br.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    @out += _options.Renderer.Br();
                    continue;
                }

                // del (gfm)
                cap = this._rules.Del.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    @out += _options.Renderer.Del(this.Output(cap[1]));
                    continue;
                }

                // text
                cap = this._rules.Text.Exec(src);
                if (cap.Any())
                {
                    src = src.Substring(cap[0].Length);
                    @out += _options.Renderer.Text(this.EscapeHtml(this.Smartypants(cap[0])));
                    continue;
                }

                if (!String.IsNullOrEmpty(src))
                {
                    throw new Exception("Infinite loop on byte: " + (int)src[0]);
                }
            }

            return @out;
        }

        /// <summary>
        /// Compile Link
        /// </summary>
        protected virtual string OutputLink(IList<string> cap, LinkObj link)
        {
            string href = this.EscapeHtml(link.Href),
            title = !String.IsNullOrEmpty(link.Title) ? this.EscapeHtml(link.Title) : null;

            return cap[0][0] != '!'
                ? _options.Renderer.Link(href, title, this.Output(cap[1]))
                : _options.Renderer.Image(href, title, this.EscapeHtml(cap[1]));
        }

        /// <summary>
        /// Mangle Links
        /// </summary>
        protected virtual string Mangle(string text)
        {
            if (!this._options.Mangle) return text;
            var @out = String.Empty;

            for (int i = 0; i < text.Length; i++)
            {
                var ch = text[i].ToString();
                if (_random.NextDouble() > 0.5)
                {
                    ch = 'x' + Convert.ToString((int)ch[0], 16);
                }
                @out += "&#" + ch + ";";
            }

            return @out;
        }

        /// <summary>
        /// Smartypants Transformations
        /// </summary>
        protected virtual string Smartypants(string text)
        {
            if (!this._options.Smartypants) return text;

            return text
                // em-dashes
                .Replace("---", "\u2014")
                // en-dashes
                .Replace("--", "\u2013")
                // opening singles
                .ReplaceRegex(@"(^|[-\u2014/(\[{""\s])'", "$1\u2018")
                // closing singles & apostrophes
                .Replace("'", "\u2019")
                // opening doubles
                .ReplaceRegex(@"(^|[-\u2014/(\[{\u2018\s])""", "$1\u201c")
                // closing doubles
                .Replace("\"", "\u201d")
                // ellipses
                .Replace("...", "\u2026");
        }

        protected virtual string EscapeHtml(string text, bool encode = false)
        {
            if (!this._options.EscapeHtml) return text;

            return StringHelper.Escape(text, encode);
        }
    }
}
