using System;

namespace AdaptiveCards.Rendering
{

    public abstract class AdaptiveCardRendererBase<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        protected AdaptiveCardRendererBase(AdaptiveHostConfig config)
        {
            HostConfig = config ?? throw new ArgumentNullException(nameof(config));
        }

        protected abstract AdaptiveSchemaVersion GetSupportedSchemaVersion();

        private AdaptiveSchemaVersion _supportedSchemaVersion;

        public AdaptiveSchemaVersion SupportedSchemaVersion => _supportedSchemaVersion ?? (_supportedSchemaVersion = GetSupportedSchemaVersion());

        public AdaptiveHostConfig HostConfig { get; set; }

        public AdaptiveElementRenderers<TUIElement, TContext> ElementRenderers { get; } = new AdaptiveElementRenderers<TUIElement, TContext>();
    }
}