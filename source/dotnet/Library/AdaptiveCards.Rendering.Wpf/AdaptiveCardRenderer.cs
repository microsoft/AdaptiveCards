using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;

namespace AdaptiveCards.Rendering.Wpf
{
    public partial class AdaptiveCardRenderer : AdaptiveCardRendererBase<FrameworkElement, AdaptiveRenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 0);
        }

        protected Action<object, AdaptiveActionEventArgs> actionCallback;
        protected Action<object, MissingInputEventArgs> missingDataCallback;
        protected AdaptiveHostConfig _defaultCardStyling;

        public AdaptiveCardRenderer() : this(new AdaptiveHostConfig()) { }

        public AdaptiveCardRenderer(AdaptiveHostConfig hostConfig) : base(hostConfig)
        {
            SetObjectTypes();
        }

        private void SetObjectTypes()
        {
            ElementRenderers.Set<AdaptiveCard>(RenderAdaptiveCardWrapper);

            ElementRenderers.Set<AdaptiveTextBlock>(AdaptiveTextBlockRenderer.Render);
            ElementRenderers.Set<AdaptiveImage>(AdaptiveImageRenderer.Render);

            ElementRenderers.Set<AdaptiveContainer>(AdaptiveContainerRenderer.Render);
            ElementRenderers.Set<AdaptiveColumn>(AdaptiveColumnRenderer.Render);
            ElementRenderers.Set<AdaptiveColumnSet>(AdaptiveColumnSetRenderer.Render);
            ElementRenderers.Set<AdaptiveFactSet>(AdaptiveFactSetRenderer.Render);
            ElementRenderers.Set<AdaptiveImageSet>(AdaptiveImageSetRenderer.Render);

            ElementRenderers.Set<AdaptiveChoiceSetInput>(AdaptiveChoiceSetRenderer.Render);
            ElementRenderers.Set<AdaptiveTextInput>(AdaptiveTextInputRenderer.Render);
            ElementRenderers.Set<AdaptiveNumberInput>(AdaptiveNumberInputRenderer.Render);
            ElementRenderers.Set<AdaptiveDateInput>(AdaptiveDateInputRenderer.Render);
            ElementRenderers.Set<AdaptiveTimeInput>(AdaptiveTimeInputRenderer.Render);
            ElementRenderers.Set<AdaptiveToggleInput>(AdaptiveToggleInputRenderer.Render);

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

                if (File.Exists(this.StylePath))
                {
                    using (var styleStream = File.OpenRead(this.StylePath))
                    {
                        _resources = (ResourceDictionary)XamlReader.Load(styleStream);
                    }
                }
                else
                    _resources = new ResourceDictionary();

                return _resources;
            }
            set => _resources = value;
        }

        /// <summary>
        /// Path to Xaml resource dictionary
        /// </summary>
        private string _stylePath;
        public string StylePath
        {
            get => _stylePath;
            set
            {
                this._stylePath = value;
                this._resources = null;
            }
        }

        public static FrameworkElement RenderAdaptiveCardWrapper(AdaptiveCard card, AdaptiveRenderContext context)
        {
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");

            outerGrid.Background = context.GetColorBrush(context.Config.ContainerStyles.Default.BackgroundColor);

            outerGrid.SetBackgroundSource(card.BackgroundImage, context);

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.Margin = new Thickness(context.Config.Spacing.Padding,
                context.Config.Spacing.Padding,
                context.Config.Spacing.Padding,
                context.Config.Spacing.Padding);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            AdaptiveContainerRenderer.AddContainerElements(grid, card.Body, context);
            AdaptiveActionSetRenderer.AddActions(grid, card.Actions, context);

            outerGrid.Children.Add(grid);
            return outerGrid;
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


            Action<object, AdaptiveActionEventArgs> actionCallback = (sender, args) =>
            {
                answer?.InvokeOnAction(args);
            };

            AdaptiveRenderContext context = new AdaptiveRenderContext(actionCallback, null)
            {
                Config = this.HostConfig,
                Resources = this.Resources,
                ElementRenderers = this.ElementRenderers
            };

            el = context.Render(card);

            answer = new RenderedAdaptiveCard(el, card);
            return answer;
        }
    }
}
