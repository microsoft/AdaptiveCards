using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    public class HttpPOST : ExternalAction
    {
        public HttpPOST() : base() { }

        public string Target { get; set; }

        public string Body { get; set; }

        public string BodyContentType { get; set; }

        public string SuccessMessage { get; set; }

        public string ErrorMessage { get; set; }
    }
}
