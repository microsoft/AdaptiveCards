using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Microsoft.MarkedNet
{
#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
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
#pragma warning restore CS1591 // Missing XML comment for publicly visible type or member
}
