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

        /// <summary>
        /// A Host Configuration object to determine base styling and behavior of the rendered card
        /// </summary>
        public AdaptiveHostConfig HostConfig { get; set; }

        /// <summary>
        /// The dictionary of supported element types and their associated rendering functions
        /// </summary>
        public AdaptiveElementRenderers<TUIElement, TContext> ElementRenderers { get; } = new AdaptiveElementRenderers<TUIElement, TContext>();

        protected virtual void ValidateCard(AdaptiveCard card)
        {
            if (card.MinVersion > SupportedSchemaVersion)
                throw new AdaptiveRenderException($"Payload MinVersion ({card.MinVersion}) is greater than the renderer supported version ({SupportedSchemaVersion})");
        }
    }
}