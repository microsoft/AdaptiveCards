using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Cache;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public partial class AdaptiveCardRenderer : AdaptiveCardRendererBase<FrameworkElement, AdaptiveRenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 0);
        }

        protected Action<object, AdaptiveActionEventArgs> ActionCallback;
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

            ElementRenderers.Set<AdaptiveAction>(AdaptiveActionRenderer.Render);
        }


        /// <summary>
        /// Resource dictionary to use when rendering
        /// </summary>
        public ResourceDictionary Resources { get; set; }

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
        /// <param name="cardAssets">Any pre-fetched assets associated with the card</param>
        public RenderedAdaptiveCard RenderCard(AdaptiveCard card, IDictionary<Uri, MemoryStream> cardAssets = null)
        {
            if (card == null) throw new ArgumentNullException(nameof(card));

            ValidateCard(card);

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

            renderCard = new RenderedAdaptiveCard(element, card, context.Warnings, context.AssetTasks);
            renderCard.InputBindings = context.InputBindings;

            return renderCard;
        }

        public async Task<IDictionary<Uri, MemoryStream>> LoadAssetsForCardAsync(AdaptiveCard card)
        {
            var visitor = new PreFetchImageVisitor();
            await visitor.GetAllImages(card).ConfigureAwait(false);
            return visitor.LoadedImages;
        }
    }

    public class ResourceResolver
    {
        private readonly Dictionary<string, Func<Uri, Task<MemoryStream>>> _internalResolver = new Dictionary<string, Func<Uri, Task<MemoryStream>>>(StringComparer.OrdinalIgnoreCase);

        public ResourceResolver()
        {            
            Register("http", GetHttpAsync);
            Register("https", GetHttpAsync);
        }

        private static async Task<MemoryStream> GetHttpAsync(Uri uri)
        {
            using (var webclient = new WebClient())
            {
                webclient.CachePolicy = new RequestCachePolicy(RequestCacheLevel.CacheIfAvailable);
                var bytes = await webclient.DownloadDataTaskAsync(uri);
                return new MemoryStream(bytes);
            }
        }


        public void Register(string uriScheme, Func<Uri, Task<MemoryStream>> loadAsset)
        {
            _internalResolver[uriScheme] = loadAsset;
        }

        public void Clear()
        {
            _internalResolver.Clear();
        }

        public void Remove(string uriScheme)
        {
            _internalResolver.Remove(uriScheme);
        }

        public Task<MemoryStream> LoadAssetAsync(Uri uri)
        {
            if (uri == null) throw new ArgumentNullException(nameof(uri));

            if (_internalResolver.ContainsKey(uri.Scheme))
            {
                return _internalResolver[uri.Scheme].Invoke(uri);
            }

            // TODO: Context warning, no asset resolver for URI scheme
            return null;
        }
    }
}
