namespace AdaptiveCards.Rendering
{
    public class AdaptiveHostConfigParseResult
    {
        public AdaptiveHostConfig HostConfig { get; }

        internal AdaptiveHostConfigParseResult(AdaptiveHostConfig hostConfig)
        {
            HostConfig = hostConfig;
        }
    }
}