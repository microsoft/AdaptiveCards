using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Input is used as part of a Form CardElement to collect information from a user
    /// </summary>
    public class Input : CardElement
    {
        public Input()
        { }

        public string Id { get; set; }

        public string Title { get; set; }

        public string Value { get; set; }
    }
}
