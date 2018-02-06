namespace AdaptiveCards
{
    // TODO: decide if standard error codes are useful or if this should just be string
    public class AdaptiveWarning
    {
        public AdaptiveWarning(int code, string message)
        {
            Code = code;
            Message = message;
        }

        public int Code { get; set; }

        public string Message { get; set; }
    }
}