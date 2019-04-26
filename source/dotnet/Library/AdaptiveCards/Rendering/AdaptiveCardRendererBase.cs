// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
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

    }
}
