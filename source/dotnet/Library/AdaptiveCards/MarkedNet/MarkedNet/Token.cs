using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Microsoft.MarkedNet
{
    public class Token
    {
        public string Text { get; set; }
        public string Type { get; set; }


        public int Depth { get; set; }
        public bool Escaped { get; set; }
        public string Lang { get; set; }
        public bool Ordered { get; set; }

        public int Start { get; set; }

        public bool Pre { get; set; }

        public IList<string> Header { get; set; }
        public IList<string> Align { get; set; }
        public IList<IList<string>> Cells { get; set; }
    }
}
