using System;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveRenderException : Exception
    {
        public AdaptiveRenderException(string message) : base(message)
        {
        }

        public AdaptiveRenderException(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}