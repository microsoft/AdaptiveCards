using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Microsoft.MarkedNet
{
    public class Parser
    {
        private Options _options; 
        private InlineLexer inline;
        private Stack<Token> tokens;
        private Token token;


        public Parser(Options options)
        {
            this.tokens = new Stack<Token>();
            this.token = null;
            _options = options ?? new Options();
        }


        /// <summary>
        /// Static Parse Method
        /// </summary>
        public static string Parse(TokensResult src, Options options)
        {
            var parser = new Parser(options);
            return parser.Parse(src);
        }

        /// <summary>
        /// Parse Loop
        /// </summary>
        public virtual string Parse(TokensResult src)
        {
            this.inline = new InlineLexer(src.Links, this._options);
            this.tokens = new Stack<Token>(src.Reverse());

            var @out = String.Empty;
            while (Next() != null)
            {
                @out += Tok();
            }

            return @out;
        }


        /// <summary>
        /// Next Token
        /// </summary>
        protected virtual Token Next()
        {
            return this.token = (this.tokens.Any()) ? this.tokens.Pop() : null;
        }


        /// <summary>
        /// Preview Next Token
        /// </summary>
        protected virtual Token Peek()
        {
            return this.tokens.Peek() ?? new Token();
        }


        /// <summary>
        /// Parse Text Tokens
        /// </summary>    
        protected virtual string ParseText()
        {
            var body = this.token.Text;

            while (this.Peek().Type == "text")
            {
                body += '\n' + this.Next().Text;
            }

            return this.inline.Output(body);
        }

        /// <summary>
        /// Parse Current Token
        /// </summary>    
        protected virtual string Tok()
        {
            switch (this.token.Type)
            {
                case "space":
                    {
                        return String.Empty;
                    }
                case "hr":
                    {
                        return _options.Renderer.Hr();
                    }
                case "heading":
                    {
                        return _options.Renderer.Heading(this.inline.Output(this.token.Text), this.token.Depth, this.token.Text);
                    }
                case "code":
                    {
                        return _options.Renderer.Code(this.token.Text, this.token.Lang, this.token.Escaped);
                    }
                case "table":
                    {
                        string header = String.Empty, body = String.Empty;

                        // header
                        var cell = String.Empty;
                        for (int i = 0; i < this.token.Header.Count; i++)
                        {
                            cell += _options.Renderer.TableCell(
                              this.inline.Output(this.token.Header[i]),
                              new TableCellFlags { Header = true, Align = i < this.token.Align.Count ? this.token.Align[i] : null }
                            );
                        }
                        header += _options.Renderer.TableRow(cell);

                        for (int i = 0; i < this.token.Cells.Count; i++)
                        {
                            var row = this.token.Cells[i];

                            cell = String.Empty;
                            for (int j = 0; j < row.Count; j++)
                            {
                                cell += _options.Renderer.TableCell(
                                  this.inline.Output(row[j]),
                                  new TableCellFlags { Header = false, Align = j < this.token.Align.Count ? this.token.Align[j] : null }
                                );
                            }

                            body += _options.Renderer.TableRow(cell);
                        }
                        return _options.Renderer.Table(header, body);
                    }
                case "blockquote_start":
                    {
                        var body = String.Empty;

                        while (this.Next().Type != "blockquote_end")
                        {
                            body += this.Tok();
                        }

                        return _options.Renderer.Blockquote(body);
                    }
                case "list_start":
                    {
                        var body = String.Empty;
                        var ordered = this.token.Ordered;
                        var start = this.token.Start;
                        while (this.Next().Type != "list_end")
                        {
                            body += this.Tok();
                        }

                        return _options.Renderer.List(body, ordered, start);
                    }
                case "list_item_start":
                    {
                        var body = String.Empty;

                        while (this.Next().Type != "list_item_end")
                        {
                            body += this.token.Type == "text"
                              ? this.ParseText()
                              : this.Tok();
                        }

                        return _options.Renderer.ListItem(body);
                    }
                case "loose_item_start":
                    {
                        var body = String.Empty;

                        while (this.Next().Type != "list_item_end")
                        {
                            body += this.Tok();
                        }

                        return _options.Renderer.ListItem(body);
                    }
                case "html":
                    {
                        var html = !this.token.Pre && !this._options.Pedantic
                          ? this.inline.Output(this.token.Text)
                          : this.token.Text;
                        return _options.Renderer.Html(html);
                    }
                case "paragraph":
                    {
                        return _options.Renderer.Paragraph(this.inline.Output(this.token.Text));
                    }
                case "text":
                    {
                        return _options.Renderer.Paragraph(this.ParseText());
                    }
            }

            throw new Exception();
        }
    }
}
