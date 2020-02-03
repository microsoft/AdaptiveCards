using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveFallbackException: AdaptiveException
    {
        public AdaptiveFallbackException()
        {
        }

        public AdaptiveFallbackException(string message) : base(message)
        {
        }

        public AdaptiveFallbackException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}
