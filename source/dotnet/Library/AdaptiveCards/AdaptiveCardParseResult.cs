using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveCardParseResult
    {
        /// <summary>
        /// The parsed card object
        /// </summary>
        public AdaptiveCard Card { get; set; }

        /// <summary>
        /// If any modifications were done to the parsed card they will be reported here
        /// </summary>
        public IList<AdaptiveViolation> Warnings { get; } = new List<AdaptiveViolation>();   
    }

    public class AdaptiveViolation
    {
        public AdaptiveViolation(int code, string message)
        {
            Code = code;
            Message = message;
        }

        public int Code { get; set; }

        public string Message { get; set; }
    }
}
