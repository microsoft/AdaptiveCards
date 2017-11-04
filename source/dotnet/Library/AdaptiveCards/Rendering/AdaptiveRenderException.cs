using System;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveRenderException : AdaptiveException
    {
        public AdaptiveRenderException()
        {
            
        }

        public AdaptiveRenderException(string message) : base(message)
        {
        }

        public AdaptiveRenderException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}