using System;

namespace AdaptiveCards
{
    public class AdaptiveException : Exception
    {
        public AdaptiveException()
        {
        }

        public AdaptiveException(string message) : base(message)
        {
        }

        public AdaptiveException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}