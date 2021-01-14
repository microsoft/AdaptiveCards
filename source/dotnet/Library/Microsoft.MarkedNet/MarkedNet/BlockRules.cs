using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;


namespace Microsoft.MarkedNet
{
    /// <summary>
    /// Block-Level Grammar
    /// </summary>
    public class BlockRules
    {
        #region Fields

        private static readonly Regex newline = new Regex(@"^\n+", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex code = new Regex(@"^( {4}[^\n]+\n*)+", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex fences = new Regex("", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0)); // noop
        private static readonly Regex hr = new Regex(@"^( *[-*_]){3,} *(?:\n+|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex heading = new Regex(@"^ *(#{1,6}) *([^\n]+?) *#* *(?:\n+|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex npTable = new Regex("", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0)); // noop
        private static readonly Regex lHeading = new Regex(@"^([^\n]+)\n *(=|-){2,} *(?:\n+|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex blockquote = new Regex(@"^( *>[^\n]+(\n(?! *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$))[^\n]+)*\n*)+", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex list = new Regex(@"^( *)((?:[*+-]|\d+\.)) [\s\S]+?(?:\n+(?=\1?(?:[-*_] *){3,}(?:\n+|$))|\n+(?= *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$))|\n{2,}(?! )(?!\1(?:[*+-]|\d+\.) )\n*|\s*$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex html = new Regex(@"^ *(?:<!--[\s\S]*?-->|<((?!(?:a|em|strong|small|s|cite|q|dfn|abbr|data|time|code|var|samp|kbd|sub|sup|i|b|u|mark|ruby|rt|rp|bdi|bdo|span|br|wbr|ins|del|img)\b)\w+(?!:\/|[^\w\s@]*@)\b)[\s\S]+?<\/\1>|<(?!(?:a|em|strong|small|s|cite|q|dfn|abbr|data|time|code|var|samp|kbd|sub|sup|i|b|u|mark|ruby|rt|rp|bdi|bdo|span|br|wbr|ins|del|img)\b)\w+(?!:\/|[^\w\s@]*@)\b(?:""[^""]*""|'[^']*'|[^'"">])*?>) *(?:\n{2,}|\s*$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex def = new Regex(@"^ *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex table = new Regex("", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0)); // noop
        private static readonly Regex paragraph = new Regex(@"^((?:[^\n]+\n?(?!( *[-*_]){3,} *(?:\n+|$)| *(#{1,6}) *([^\n]+?) *#* *(?:\n+|$)|([^\n]+)\n *(=|-){2,} *(?:\n+|$)|( *>[^\n]+(\n(?! *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$))[^\n]+)*\n*)+|<(?!(?:a|em|strong|small|s|cite|q|dfn|abbr|data|time|code|var|samp|kbd|sub|sup|i|b|u|mark|ruby|rt|rp|bdi|bdo|span|br|wbr|ins|del|img)\b)\w+(?!:\/|[^\w\s@]*@)\b| *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$)))+)\n*", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex text = new Regex(@"^[^\n]+", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex bullet = new Regex(@"(?:[*+-]|\d+\.)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex item = new Regex(@"^( *)((?:[*+-]|\d+\.)) [^\n]*(?:\n(?!\1(?:[*+-]|\d+\.) )[^\n]*)*", RegexOptions.Multiline | RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));

        #endregion

        #region Properties

        public virtual Regex Newline { get { return newline; } }
        public virtual Regex Сode { get { return code; } }
        public virtual Regex Fences { get { return fences; } } // noop
        public virtual Regex Hr { get { return hr; } }
        public virtual Regex Heading { get { return heading; } }
        public virtual Regex NpTable { get { return npTable; } } // noop
        public virtual Regex LHeading { get { return lHeading; } }
        public virtual Regex Blockquote { get { return blockquote; } }
        public virtual Regex List { get { return list; } }
        public virtual Regex Html { get { return html; } }
        public virtual Regex Def { get { return def; } }
        public virtual Regex Table { get { return table; } } // noop
        public virtual Regex Paragraph { get { return paragraph; } }
        public virtual Regex Text { get { return text; } }
        public virtual Regex Bullet { get { return bullet; } }
        public virtual Regex Item { get { return item; } }

        #endregion
    }

    /// <summary>
    /// Normal Block Grammar
    /// </summary>
    public class NormalBlockRules : BlockRules
    {
    }

    /// <summary>
    /// GFM Block Grammar
    /// </summary>
    public class GfmBlockRules : BlockRules
    {
        #region Fields

        private static readonly Regex fences = new Regex(@"^ *(`{3,}|~{3,}) *(\S+)? *\n([\s\S]+?)\s*\1 *(?:\n+|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex paragraph = new Regex(@"^((?:[^\n]+\n?(?! *(`{3,}|~{3,}) *(\S+)? *\n([\s\S]+?)\s*\2 *(?:\n+|$)|( *)((?:[*+-]|\d+\.)) [\s\S]+?(?:\n+(?=\3?(?:[-*_] *){3,}(?:\n+|$))|\n+(?= *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$))|\n{2,}(?! )(?!\1(?:[*+-]|\d+\.) )\n*|\s*$)|( *[-*_]){3,} *(?:\n+|$)| *(#{1,6}) *([^\n]+?) *#* *(?:\n+|$)|([^\n]+)\n *(=|-){2,} *(?:\n+|$)|( *>[^\n]+(\n(?! *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$))[^\n]+)*\n*)+|<(?!(?:a|em|strong|small|s|cite|q|dfn|abbr|data|time|code|var|samp|kbd|sub|sup|i|b|u|mark|ruby|rt|rp|bdi|bdo|span|br|wbr|ins|del|img)\b)\w+(?!:\/|[^\w\s@]*@)\b| *\[([^\]]+)\]: *<?([^\s>]+)>?(?: +[""(]([^\n]+)["")])? *(?:\n+|$)))+)\n*", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex heading = new Regex(@"^ *(#{1,6}) *([^\n]+?) *#* *(?:\n+|$)", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));

        #endregion

        #region Properties

        public override Regex Fences { get { return fences; } }
        public override Regex Paragraph { get { return paragraph; } }
        public override Regex Heading { get { return heading; } }

        #endregion
    }

    /// <summary>
    /// GFM + Tables Block Grammar
    /// </summary>
    public class TablesBlockRules : GfmBlockRules
    {
        #region Fields

        private static readonly Regex npTable = new Regex(@"^ *(\S.*\|.*)\n *([-:]+ *\|[-| :]*)\n((?:.*\|.*(?:\n|$))*)\n*", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));
        private static readonly Regex table = new Regex(@"^ *\|(.+)\n *\|( *[-:]+[-| :]*)\n((?: *\|.*(?:\n|$))*)\n*", RegexOptions.Compiled, TimeSpan.FromSeconds(2.0));

        #endregion

        #region Properties

        public override Regex NpTable { get { return npTable; } }
        public override Regex Table { get { return table; } }

        #endregion
    }
}
