// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Abstract base class that every AdaptiveCards renderer must implement.
    /// </summary>
    /// <typeparam name="TUIElement">The base UI element type the renderer implements (e.g. "HTMLElement" or
    /// "FrameworkElement").</typeparam>
    /// <typeparam name="TContext">The type of the renderer context to use (e.g. "AdaptiveRenderContext").</typeparam>
    public abstract class AdaptiveCardRendererBase<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        /// <summary>
        /// Provides the highest schema version that this renderer supports.
        /// </summary>
        protected abstract AdaptiveSchemaVersion GetSupportedSchemaVersion();

        private AdaptiveSchemaVersion _supportedSchemaVersion;

        /// <summary>
        /// Provides the highest schema version that this renderer supports.
        /// </summary>
        public AdaptiveSchemaVersion SupportedSchemaVersion => _supportedSchemaVersion ?? (_supportedSchemaVersion = GetSupportedSchemaVersion());

        /// <summary>
        /// A Host Configuration object to determine base styling and behavior of the rendered card
        /// </summary>
        public virtual AdaptiveHostConfig HostConfig { get; set; } = new AdaptiveHostConfig();

        /// <summary>
        /// The dictionary of supported element types and their associated rendering functions
        /// </summary>
        public virtual AdaptiveElementRenderers<TUIElement, TContext> ElementRenderers { get; } = new AdaptiveElementRenderers<TUIElement, TContext>();

    }
}
