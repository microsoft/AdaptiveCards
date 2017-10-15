namespace AdaptiveCards.Rendering
{
    public class HostConfigParseResult
    {
        public HostConfig HostConfig { get; private set; }

        internal HostConfigParseResult(HostConfig hostConfig)
        {
            HostConfig = hostConfig;
        }
    }
}