using AdaptiveCards.Rendering.Config;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AdaptiveCards.Rendering
{

    public abstract class AdaptiveCardRendererBase<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        protected AdaptiveCardRendererBase(HostConfig config)
        {
            HostConfig = config ?? throw new ArgumentNullException(nameof(config));
        }

        protected abstract AdaptiveSchemaVersion GetSupportedSchemaVersion();
        private AdaptiveSchemaVersion _supportedSchemaVersion;
        public AdaptiveSchemaVersion SupportedSchemaVersion
        {
            get
            {
                if (_supportedSchemaVersion == null)
                {
                    _supportedSchemaVersion = GetSupportedSchemaVersion();
                }
                return _supportedSchemaVersion;
            }
        }

        public HostConfig HostConfig { get; set; }

        public Dictionary<Type, Func<TypedElement, TContext, TUIElement>> ElementRenderers = new Dictionary<Type, Func<TypedElement, TContext, TUIElement>>();

        public void SetRenderer<TElement>(Func<TypedElement, TContext, TUIElement> renderer)
        {
            ElementRenderers[typeof(TElement)] = renderer;
        }
    }
}