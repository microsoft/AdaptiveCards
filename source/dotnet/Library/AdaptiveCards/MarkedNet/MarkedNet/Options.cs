using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.MarkedNet
{
    public class Options
    {
        #region Fields

        private MarkdownRenderer _renderer;

        #endregion

        #region Properties

        public Func<string, string, string> Highlight { get; set; }

        public Func<string, string> Sanitizer { get; set; }

        public MarkdownRenderer Renderer
        {
            get { return _renderer; }
            set { _renderer = value; if (_renderer != null) _renderer.Options = this; }
        }

        public string LangPrefix { get; set; }

        public string HeaderPrefix { get; set; }

        public bool XHtml { get; set; }

        public bool Sanitize { get; set; }

        public bool Pedantic { get; set; }

        public bool Mangle { get; set; }

        public bool Smartypants { get; set; }

        public bool Breaks { get; set; }

        public bool Gfm { get; set; }

        public bool Tables { get; set; }

        public bool SmartLists { get; set; }

        public bool EscapeHtml { get; set; }

        #endregion

        #region Constructors

        public Options()
        {
            Highlight = null;
            Sanitizer = null;
            Renderer = new MarkdownRenderer(this);

            LangPrefix = "lang-";
            HeaderPrefix = "";
            XHtml = false;
            Sanitize = false;
            Pedantic = false;
            Mangle = false;
            Smartypants = false;
            Breaks = false;
            Gfm = true;
            Tables = true;
            SmartLists = false;
            EscapeHtml = true;
        }

        #endregion
    }
}
