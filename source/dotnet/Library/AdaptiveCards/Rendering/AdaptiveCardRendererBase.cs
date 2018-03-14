using System;

namespace AdaptiveCards.Rendering
{
    public abstract class AdaptiveCardRendererBase<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        protected abstract AdaptiveSchemaVersion GetSupportedSchemaVersion();

        private AdaptiveSchemaVersion _supportedSchemaVersion;

        public AdaptiveSchemaVersion SupportedSchemaVersion => _supportedSchemaVersion ?? (_supportedSchemaVersion = GetSupportedSchemaVersion());

        /// <summary>
        /// A Host Configuration object to determine base styling and behavior of the rendered card
        /// </summary>
        public virtual AdaptiveHostConfig HostConfig { get; set; } = new AdaptiveHostConfig();

        /// <summary>
        /// The dictionary of supported element types and their associated rendering functions
        /// </summary>
        public virtual AdaptiveElementRenderers<TUIElement, TContext> ElementRenderers { get; } = new AdaptiveElementRenderers<TUIElement, TContext>();


        /// <summary>
        /// Throws if the card cannot be rendered
        /// </summary>
        public virtual void EnsureCanRender(AdaptiveCard card)
        {
            if (card.Version > SupportedSchemaVersion)
                throw new AdaptiveRenderException($"Payload Version ({card.Version}) is greater than the renderer supported version ({SupportedSchemaVersion})");
        }
    }
}