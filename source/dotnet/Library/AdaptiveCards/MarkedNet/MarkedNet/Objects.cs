using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.MarkedNet
{
    public class TableCellFlags
    {
        public bool Header { get; set; }
        public string Align { get; set; }
    }

    public class LinkObj
    {
        public string Href { get; set; }
        public string Title { get; set; }
    }
}
