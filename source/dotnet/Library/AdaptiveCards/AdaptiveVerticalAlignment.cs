using Newtonsoft.Json;
using Newtonsoft.Json.Converters;


namespace AdaptiveCards
{
    [JsonConverter(typeof(StringEnumConverter), true)]
    public enum AdaptiveVerticalAlignment
    {
        Top,
        Center,
        Bottom
    }
}
