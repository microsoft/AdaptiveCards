namespace AdaptiveCards
{
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