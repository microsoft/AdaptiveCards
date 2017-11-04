using System;

namespace AdaptiveCards
{
    public class AdaptiveSerializationException : AdaptiveException
    {
        public AdaptiveSerializationException()
        {
        }

        public AdaptiveSerializationException(string message) : base(message)
        {
        }

        public AdaptiveSerializationException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}