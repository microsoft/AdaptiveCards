using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;

namespace AdaptiveCards.Rendering.Wpf
{
    public class AdaptiveCardRenderer : AdaptiveCardRendererBase<FrameworkElement, AdaptiveRenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 0);
        }

        protected Action<object, AdaptiveActionEventArgs> ActionCallback;
        protected Action<object, MissingInputEventArgs> missingDataCallback;

        public AdaptiveCardRenderer() : this(new AdaptiveHostConfig()) { }

        public AdaptiveCardRenderer(AdaptiveHostConfig hostConfig)
        {
            HostConfig = hostConfig;
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

            ElementRenderers.Set<AdaptiveAction>(AdaptiveActionRenderer.Render);
        }


        /// <summary>
        /// A path to a XAML resource dictionary
        /// </summary>
        public string ResourcesPath { get; set; }

        private ResourceDictionary _resources;

        /// <summary>
        /// Resource dictionary to use when rendering. Don't use this from a server, use <see cref="ResourcesPath"/> instead.
        /// </summary>
        public ResourceDictionary Resources
        {
            get
            {
                if (_resources != null)
                    return _resources;

                if (File.Exists(ResourcesPath))
                {
                    using (var styleStream = File.OpenRead(ResourcesPath))
                    {
                        _resources = (ResourceDictionary)XamlReader.Load(styleStream);
                    }
                }
                else
                {
                    _resources = new ResourceDictionary();
                }

                return _resources;
            }
            set => _resources = value;
        }

        public AdaptiveActionHandlers ActionHandlers { get; } = new AdaptiveActionHandlers();

        public ResourceResolver ResourceResolvers { get; } = new ResourceResolver();

        public static FrameworkElement RenderAdaptiveCardWrapper(AdaptiveCard card, AdaptiveRenderContext context)
        {
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");
            outerGrid.Background = context.GetColorBrush(context.Config.ContainerStyles.Default.BackgroundColor);
            outerGrid.SetBackgroundSource(card.BackgroundImage, context);

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.Margin = new Thickness(context.Config.Spacing.Padding);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });


            AdaptiveContainerRenderer.AddContainerElements(grid, card.Body, context);
            AdaptiveActionSetRenderer.AddActions(grid, card.Actions, context);

            outerGrid.Children.Add(grid);
            return outerGrid;
        }


        /// <summary>
        /// Renders an adaptive card.
        /// </summary>
        /// <param name="card">The card to render</param>
        public RenderedAdaptiveCard RenderCard(AdaptiveCard card)
        {
            if (card == null) throw new ArgumentNullException(nameof(card));
            EnsureCanRender(card);

            RenderedAdaptiveCard renderCard = null;

            void Callback(object sender, AdaptiveActionEventArgs args)
            {
                renderCard?.InvokeOnAction(args);
            }

            var context = new AdaptiveRenderContext(Callback, null)
            {
                ResourceResolvers = ResourceResolvers,
                ActionHandlers = ActionHandlers,
                Config = HostConfig ?? new AdaptiveHostConfig(),
                Resources = Resources,
                ElementRenderers = ElementRenderers
            };

            var element = context.Render(card);

            renderCard = new RenderedAdaptiveCard(element, card, context.Warnings, context.InputBindings);


            return renderCard;
        }

        /// <summary>
        /// Renders an adaptive card to a PNG image. This method cannot be called from a server. Use <see cref="RenderCardToImageOnStaThreadAsync"/> instead.
        /// </summary>
        /// <param name="createStaThread">If true this method will create an STA thread allowing it to be called from a server.</param>
        public async Task<RenderedAdaptiveCardImage> RenderCardToImageAsync(AdaptiveCard card, bool createStaThread, int width = 400, CancellationToken cancellationToken = default(CancellationToken))
        {
            if (card == null) throw new ArgumentNullException(nameof(card));
            EnsureCanRender(card);

            if (createStaThread)
            {
                return await await Task.Factory.StartNewSta(async () => await RenderCardToImageInternalAsync(card, width, cancellationToken));
            }
            else
            {
                return await RenderCardToImageInternalAsync(card, width, cancellationToken);
            }
        }

        private async Task<RenderedAdaptiveCardImage> RenderCardToImageInternalAsync(AdaptiveCard card, int width, CancellationToken cancellationToken)
        {
            RenderedAdaptiveCardImage renderCard = null;

            try
            {
                var cardAssets = await LoadAssetsForCardAsync(card, cancellationToken);

                var context = new AdaptiveRenderContext(null, null)
                {
                    CardAssets = cardAssets,
                    ResourceResolvers = ResourceResolvers,
                    ActionHandlers = ActionHandlers,
                    Config = HostConfig ?? new AdaptiveHostConfig(),
                    Resources = Resources,
                    ElementRenderers = ElementRenderers
                };

                var stream = context.Render(card).RenderToImage(width);
                renderCard = new RenderedAdaptiveCardImage(stream, card, context.Warnings);
            }
            catch(Exception e)
            {
                Debug.WriteLine($"RENDER Failed. {e.Message}");
            }

            return renderCard;
        }


        public async Task<IDictionary<Uri, MemoryStream>> LoadAssetsForCardAsync(AdaptiveCard card, CancellationToken cancellationToken = default(CancellationToken))
        {
            var visitor = new PreFetchImageVisitor(ResourceResolvers);
            await visitor.GetAllImages(card).WithCancellation(cancellationToken).ConfigureAwait(false);
            return visitor.LoadedImages;
        }
    }
}
