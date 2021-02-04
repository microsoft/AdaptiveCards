using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;


namespace Microsoft.MarkedNet
{
    /// <summary>
    /// Inline-Level Grammar
    /// </summary>
    public class InlineRules
    {
        #region Fields

        private static readonly Regex escape = new Regex(@"^\\([\\`*{}\[\]()#+\-.!_>])", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex autoLink = new Regex(@"^<([^ >]+(@|:\/)[^ >]+)>", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex url = new Regex("", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0)); // noop
        private static readonly Regex tag = new Regex(@"^<!--[\s\S]*?-->|^<\/?\w+(?:""[^""]*""|'[^']*'|[^'"">])*?>", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex link = new Regex(@"^!?\[((?:\[[^\]]*\]|[^\[\]]|\](?=[^\[]*\]))*)\]\(\s*<?([\s\S]*?)>?(?:\s+['""]([\s\S]*?)['""])?\s*\)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex refLink = new Regex(@"^!?\[((?:\[[^\]]*\]|[^\[\]]|\](?=[^\[]*\]))*)\]\s*\[([^\]]*)\]", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex noLink = new Regex(@"^!?\[((?:\[[^\]]*\]|[^\[\]])*)\]", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex strong = new Regex(@"^__([\s\S]+?)__(?!_)|^\*\*([\s\S]+?)\*\*(?!\*)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex em = new Regex(@"^\b_((?:[^_]|__)+?)_\b|^\*((?:\*\*|[\s\S])+?)\*(?!\*)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex code = new Regex(@"^(`+)\s*([\s\S]*?[^`])\s*\1(?!`)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex br = new Regex(@"^ {2,}\n(?!\s*$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex del = new Regex("", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0)); // noop
        private static readonly Regex text = new Regex(@"^[\s\S]+?(?=[\\<!\[_*`]| {2,}\n|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));

        #endregion

        #region Properties

        public virtual Regex Escape { get { return escape; } }
        public virtual Regex AutoLink { get { return autoLink; } }
        public virtual Regex Url { get { return url; } } // noop
        public virtual Regex Tag { get { return tag; } }
        public virtual Regex Link { get { return link; } }
        public virtual Regex RefLink { get { return refLink; } }
        public virtual Regex NoLink { get { return noLink; } }
        public virtual Regex Strong { get { return strong; } }
        public virtual Regex Em { get { return em; } }
        public virtual Regex Code { get { return code; } }
        public virtual Regex Br { get { return br; } }
        public virtual Regex Del { get { return del; } } // noop
        public virtual Regex Text { get { return text; } }

        #endregion
    }

    /// <summary>
    /// Normal Inline Grammar
    /// </summary>
    public class NormalInlineRules : InlineRules
    {
    }

    /// <summary>
    /// Pedantic Inline Grammar
    /// </summary>
    public class PedanticInlineRules : InlineRules
    {
        #region Fields

        private static readonly Regex strong = new Regex(@"^__(?=\S)([\s\S]*?\S)__(?!_)|^\*\*(?=\S)([\s\S]*?\S)\*\*(?!\*)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex em = new Regex(@"^_(?=\S)([\s\S]*?\S)_(?!_)|^\*(?=\S)([\s\S]*?\S)\*(?!\*)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));

        #endregion

        #region Properties

        public override Regex Strong { get { return strong; } }
        public override Regex Em { get { return em; } }

        #endregion
    }

    /// <summary>
    /// GFM Inline Grammar
    /// </summary>
    public class GfmInlineRules : InlineRules
    {
        #region Fields

        private static readonly Regex escape = new Regex(@"^\\([\\`*{}\[\]()#+\-.!_>~|])", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex url = new Regex(@"^(https?:\/\/[^\s<]+[^<.,:;""')\]\s])", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex del = new Regex(@"^~~(?=\S)([\s\S]*?\S)~~", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex text = new Regex(@"^[\s\S]+?(?=[\\<!\[_*`~]|https?:\/\/| {2,}\n|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));

        #endregion

        #region Properties

        public override Regex Escape { get { return escape; } }
        public override Regex Url { get { return url; } }
        public override Regex Del { get { return del; } }
        public override Regex Text { get { return text; } }

        #endregion
    }

    /// <summary>
    /// GFM + Line Breaks Inline Grammar
    /// </summary>
    public class BreaksInlineRules : GfmInlineRules
    {
        #region Fields

        private static readonly Regex br = new Regex(@"^ *\n(?!\s*$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex text = new Regex(@"^[\s\S]+?(?=[\\<!\[_*`~]|https?:\/\/| *\n|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));

        #endregion

        #region Properties

        public override Regex Br { get { return br; } }
        public override Regex Text { get { return text; } }

        #endregion
    }
}
