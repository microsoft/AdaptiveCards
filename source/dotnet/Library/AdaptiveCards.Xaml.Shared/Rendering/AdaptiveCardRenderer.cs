using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Config;
#if WPF
using System.Windows.Markup;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif


namespace AdaptiveCards.Rendering
{
    public partial class AdaptiveCardRenderer : AdaptiveCardRendererBase<FrameworkElement, RenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 0);
        }

        protected Action<object, ActionEventArgs> actionCallback;
        protected Action<object, MissingInputEventArgs> missingDataCallback;
        protected HostConfig _defaultCardStyling;

        public AdaptiveCardRenderer() : this(new HostConfig()) { }

        public AdaptiveCardRenderer(HostConfig hostConfig) : base(hostConfig)
        {
            SetObjectTypes();
        }

        private void SetObjectTypes()
        {
            this.ElementRenderers.Set<AdaptiveCard>(XamlAdaptiveCard.Render);

            this.ElementRenderers.Set<TextBlock>(XamlTextBlock.Render);
            this.ElementRenderers.Set<Image>(XamlImage.Render);

            this.ElementRenderers.Set<Container>(XamlContainer.Render);
            this.ElementRenderers.Set<Column>(XamlColumn.Render);
            this.ElementRenderers.Set<ColumnSet>(XamlColumnSet.Render);
            this.ElementRenderers.Set<FactSet>(XamlFactSet.Render);
            this.ElementRenderers.Set<ImageSet>(XamlImageSet.Render);

            this.ElementRenderers.Set<ChoiceSet>(XamlChoiceSet.Render);
            this.ElementRenderers.Set<TextInput>(XamlTextInput.Render);
            this.ElementRenderers.Set<NumberInput>(XamlNumberInput.Render);
            this.ElementRenderers.Set<DateInput>(XamlDateInput.Render);
            this.ElementRenderers.Set<TimeInput>(XamlTimeInput.Render);
            this.ElementRenderers.Set<ToggleInput>(XamlToggleInput.Render);

            this.ElementRenderers.Set<SubmitAction>(XamlSubmitAction.Render);
            this.ElementRenderers.Set<OpenUrlAction>(XamlOpenUrlAction.Render);
            this.ElementRenderers.Set<ShowCardAction>(XamlShowCardAction.Render);
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
        /// Renders an adaptive card.
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public RenderedAdaptiveCard RenderCard(AdaptiveCard card)
        {
            FrameworkElement el = null;
            RenderedAdaptiveCard answer = null;

            try
            {
                Action<object, ActionEventArgs> actionCallback = (sender, args) =>
                {
                    answer?.InvokeOnAction(args);
                };

                RenderContext context = new RenderContext(actionCallback, null)
                {
                    Config = this.HostConfig,
                    Resources = this.Resources,
                    ElementRenderers = this.ElementRenderers
                };
                el = context.Render(card);
            }
            catch { }

            answer = new RenderedAdaptiveCard(el, card);
            return answer;
        }
    }
}
