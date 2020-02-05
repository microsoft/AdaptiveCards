using System;
using System.IO;
#if WPF
using System.Windows.Markup;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif


namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer : AdaptiveCardRendererBase<FrameworkElement, RenderContext>
    {
        protected Action<object, ActionEventArgs> actionCallback;
        protected Action<object, MissingInputEventArgs> missingDataCallback;
        protected AdaptiveHostConfig _defaultCardStyling;

        public XamlRenderer(AdaptiveHostConfig hostConfig,
            ResourceDictionary resources,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
        {
            HostConfig = hostConfig;
            this.Resources = resources;
            this.actionCallback = actionCallback;
            this.missingDataCallback = missingDataCallback;
            SetObjectTypes();
        }

#if WPF
        public XamlRenderer(HostConfig hostConfig,
            string stylePath,
            Action<object, ActionEventArgs> actionCallback = null,
            Action<object, MissingInputEventArgs> missingDataCallback = null)
            : base(hostConfig)
        {
            this.StylePath = stylePath;
            this.actionCallback = actionCallback;
            this.missingDataCallback = missingDataCallback;
            SetObjectTypes();
        }
#endif

        private void SetObjectTypes()
        {
            ElementRenderers.Set<AdaptiveCard>(XamlAdaptiveCard.Render);
            ElementRenderers.Set<AdaptiveTextBlock>(XamlTextBlock.Render);
            ElementRenderers.Set<AdaptiveImage>(XamlImage.Render);

            ElementRenderers.Set<AdaptiveActionSet>(XamlActionSet.Render);
            ElementRenderers.Set<AdaptiveContainer>(XamlContainer.Render);
            ElementRenderers.Set<AdaptiveColumn>(XamlColumn.Render);
            ElementRenderers.Set<AdaptiveColumnSet>(XamlColumnSet.Render);
            ElementRenderers.Set<AdaptiveFactSet>(XamlFactSet.Render);
            ElementRenderers.Set<AdaptiveImageSet>(XamlImageSet.Render);

            ElementRenderers.Set<AdaptiveChoiceSetInput>(XamlChoiceSet.Render);
            ElementRenderers.Set<AdaptiveTextInput>(XamlTextInput.Render);
            ElementRenderers.Set<AdaptiveNumberInput>(XamlNumberInput.Render);
            ElementRenderers.Set<AdaptiveDateInput>(XamlDateInput.Render);
            ElementRenderers.Set<AdaptiveTimeInput>(XamlTimeInput.Render);
            ElementRenderers.Set<AdaptiveToggleInput>(XamlToggleInput.Render); ;

            ElementRenderers.Set<AdaptiveSubmitAction>(XamlSubmitAction.Render);
            ElementRenderers.Set<AdaptiveOpenUrlAction>(XamlOpenUrlAction.Render);
            ElementRenderers.Set<AdaptiveShowCardAction>(XamlShowCardAction.Render);
        }

        /// <summary>
        /// Resource dictionary to use when rendering
        /// </summary>
        private ResourceDictionary _resources;
        public ResourceDictionary Resources
        {
            get
            {
                if (_resources != null)
                    return _resources;

#if WPF
                if (File.Exists(this.StylePath))
                {
                    using (var styleStream = File.OpenRead(this.StylePath))
                    {
                        _resources = (ResourceDictionary)XamlReader.Load(styleStream);
                    }
                }
                else
                    _resources = new ResourceDictionary();
#elif XAMARIN
                // TODO
#endif
                return _resources;
            }
            set
            {
                this._resources = value;
            }
        }

        /// <summary>
        /// Path to Xaml resource dictionary
        /// </summary>
        private string _stylePath;
        public string StylePath
        {
            get { return _stylePath; }
            set
            {
                this._stylePath = value;
                this._resources = null;
            }
        }

        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public FrameworkElement RenderAdaptiveCard(AdaptiveCard card, Func<string, MemoryStream> imageResolver = null, AdaptiveHostConfig hostConfig = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Config = hostConfig ?? new AdaptiveHostConfig(),
                Resources = this.Resources,
                ElementRenderers = this.ElementRenderers
            };
            return context.Render(card);
        }

        public FrameworkElement RenderShowCard(AdaptiveShowCardAction showCard, Func<string, MemoryStream> imageResolver = null, AdaptiveHostConfig hostConfig = null)
        {
            RenderContext context = new RenderContext(this.actionCallback, this.missingDataCallback, imageResolver)
            {
                Config = hostConfig ?? new AdaptiveHostConfig(),
                Resources = this.Resources,
                ElementRenderers = this.ElementRenderers
            };

            return context.Render(showCard.Card);
        }

        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            throw new NotImplementedException();
        }
    }
}
