// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
#if WPF
using System.Windows.Controls;
using System.Windows.Markup;
using System.Windows.Media;
#elif XAMARIN
using FrameworkElement = Xamarin.Forms.View;
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif


namespace AdaptiveCards.Rendering.Wpf
{
    public class AdaptiveCardRenderer : AdaptiveCardRendererBase<FrameworkElement, AdaptiveRenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 3);
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
            ElementRenderers.Set<AdaptiveActionSet>(AdaptiveActionSetRenderer.Render);

            ElementRenderers.Set<AdaptiveChoiceSetInput>(AdaptiveChoiceSetRenderer.Render);
            ElementRenderers.Set<AdaptiveTextInput>(AdaptiveTextInputRenderer.Render);
            ElementRenderers.Set<AdaptiveNumberInput>(AdaptiveNumberInputRenderer.Render);
            ElementRenderers.Set<AdaptiveDateInput>(AdaptiveDateInputRenderer.Render);
            ElementRenderers.Set<AdaptiveTimeInput>(AdaptiveTimeInputRenderer.Render);
            ElementRenderers.Set<AdaptiveToggleInput>(AdaptiveToggleInputRenderer.Render);

            ElementRenderers.Set<AdaptiveAction>(AdaptiveActionRenderer.Render);
        }

        public AdaptiveFeatureRegistration FeatureRegistration { get; } = new AdaptiveFeatureRegistration();

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
                        // _resources = (ResourceDictionary)XamlReader.Load(styleStream);
                    }
                }
                else
                {
                    _resources = new ResourceDictionary();
                }

                // Wrap this to avoid Console applications to crash because of this : https://github.com/Microsoft/AdaptiveCards/issues/2121
                try
                {
                    var resource = new ResourceDictionary
                    {
                        Source = new Uri("/AdaptiveCards.Rendering.Wpf;component/Themes/generic.xaml",
                       UriKind.RelativeOrAbsolute)
                    };
                    _resources.MergedDictionaries.Add(resource);
                }
                catch { }

                return _resources;
            }
            set
            {
                _resources = value;

                // Wrap this to avoid Console applications to crash because of this : https://github.com/Microsoft/AdaptiveCards/issues/2121
                try
                {
                    var resource = new ResourceDictionary
                    {
                        Source = new Uri("/AdaptiveCards.Rendering.Wpf;component/Themes/generic.xaml", UriKind.RelativeOrAbsolute)
                    };
                    _resources.MergedDictionaries.Add(resource);
                }
                catch { }

            }

        }

        public AdaptiveActionHandlers ActionHandlers { get; } = new AdaptiveActionHandlers();

        public ResourceResolver ResourceResolvers { get; } = new ResourceResolver();

        public static FrameworkElement RenderAdaptiveCardWrapper(AdaptiveCard card, AdaptiveRenderContext context)
        {
            var outerGrid = new Grid();
            outerGrid.Style = context.GetStyle("Adaptive.Card");

#if WPF
            outerGrid.Background = context.GetColorBrush(context.Config.ContainerStyles.Default.BackgroundColor);
#elif XAMARIN
            outerGrid.BackgroundColor = context.GetColor(context.Config.ContainerStyles.Default.BackgroundColor);
#endif
            outerGrid.SetBackgroundSource(card.BackgroundImage, context);

            if(context.CardRoot == null)
            {
                context.CardRoot = outerGrid;
            }

            // Reset the parent style
            context.RenderArgs.ParentStyle = AdaptiveContainerStyle.Default;

            var grid = new Grid();
            grid.Style = context.GetStyle("Adaptive.InnerCard");
            grid.Margin = new Thickness(context.Config.Spacing.Padding);

            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

#if WPF
            switch (card.VerticalContentAlignment)
            {

                case AdaptiveVerticalContentAlignment.Center:
                    grid.VerticalAlignment = VerticalAlignment.Center;
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    grid.VerticalAlignment = VerticalAlignment.Bottom;
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                default:
                    break;
            }
#elif XAMARIN
            switch (card.VerticalContentAlignment)
            {

                case AdaptiveVerticalContentAlignment.Center:
                    grid.VerticalOptions = LayoutOptions.CenterAndExpand;
                    break;
                case AdaptiveVerticalContentAlignment.Bottom:
                    grid.VerticalOptions = LayoutOptions.EndAndExpand;
                    break;
                case AdaptiveVerticalContentAlignment.Top:
                    grid.VerticalOptions = LayoutOptions.StartAndExpand;
                    break;
                default:
                    grid.VerticalOptions = LayoutOptions.FillAndExpand;
                    break;
            }
#endif

#if WPF
            outerGrid.MinHeight = card.PixelMinHeight;
#elif XAMARIN
            outerGrid.MinimumHeightRequest = card.PixelMinHeight;
#endif

            outerGrid.Children.Add(grid);

            AdaptiveContainerRenderer.AddContainerElements(grid, card.Body, context);
            AdaptiveActionSetRenderer.AddRenderedActions(grid, card.Actions, context, card.InternalID);


            if (card.SelectAction != null)
            {
                var outerGridWithSelectAction = context.RenderSelectAction(card.SelectAction, outerGrid);

                return outerGridWithSelectAction;
            }

            return outerGrid;
        }

        /// <summary>
        /// Renders an adaptive card.
        /// </summary>
        /// <param name="card">The card to render</param>
        public RenderedAdaptiveCard RenderCard(AdaptiveCard card)
        {
            if (card == null) throw new ArgumentNullException(nameof(card));
            RenderedAdaptiveCard renderCard = null;

            void ActionCallback(object sender, AdaptiveActionEventArgs args)
            {
                renderCard?.InvokeOnAction(args);
            }

            void MediaClickCallback(object sender, AdaptiveMediaEventArgs args)
            {
                renderCard?.InvokeOnMediaClick(args);
            }

            var context = new AdaptiveRenderContext(ActionCallback, null, MediaClickCallback)
            {
                ResourceResolvers = ResourceResolvers,
                ActionHandlers = ActionHandlers,
                Config = HostConfig ?? new AdaptiveHostConfig(),
                Resources = Resources,
                ElementRenderers = ElementRenderers,
                FeatureRegistration = FeatureRegistration,
                Lang = card.Lang,
                RenderArgs = new AdaptiveRenderArgs { ForegroundColors = (HostConfig != null) ? HostConfig.ContainerStyles.Default.ForegroundColors : new ContainerStylesConfig().Default.ForegroundColors }
            };

            string accentColor = HostConfig.ContainerStyles.Default.ForegroundColors.Accent.Default;
            string lighterAccentColor = ColorUtil.GenerateLighterColor(accentColor);
            string attentionColor = HostConfig.ContainerStyles.Default.ForegroundColors.Attention.Default;
            string lighterAttentionColor = ColorUtil.GenerateLighterColor(attentionColor);

            Resources["Adaptive.Action.Positive.Button.Static.Background"] = context.GetColor(accentColor);
            Resources["Adaptive.Action.Positive.Button.MouseOver.Background"] = context.GetColor(lighterAccentColor);
            Resources["Adaptive.Action.Destructive.Button.Foreground"] = context.GetColor(attentionColor);
            Resources["Adaptive.Action.Destructive.Button.MouseOver.Foreground"] = context.GetColor(lighterAttentionColor);

            var element = context.Render(card);

            renderCard = new RenderedAdaptiveCard(element, card, context.Warnings, context.InputBindings);

            return renderCard;
        }

#if WPF
        /// <summary>
        /// Renders an adaptive card to a PNG image. This method cannot be called from a server. Use <see cref="RenderCardToImageOnStaThreadAsync"/> instead.
        /// </summary>
        /// <param name="createStaThread">If true this method will create an STA thread allowing it to be called from a server.</param>
        public async Task<RenderedAdaptiveCardImage> RenderCardToImageAsync(AdaptiveCard card, bool createStaThread, int width = 400, CancellationToken cancellationToken = default(CancellationToken))
        {
            if (card == null) throw new ArgumentNullException(nameof(card));

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

                var context = new AdaptiveRenderContext(null, null, null)
                {
                    CardAssets = cardAssets,
                    ResourceResolvers = ResourceResolvers,
                    ActionHandlers = ActionHandlers,
                    Config = HostConfig ?? new AdaptiveHostConfig(),
                    Resources = Resources,
                    ElementRenderers = ElementRenderers,
                    Lang = card.Lang,
                    RenderArgs = new AdaptiveRenderArgs { ForegroundColors = (HostConfig != null) ? HostConfig.ContainerStyles.Default.ForegroundColors : new ContainerStylesConfig().Default.ForegroundColors }
                };

                var stream = context.Render(card).RenderToImage(width);
                renderCard = new RenderedAdaptiveCardImage(stream, card, context.Warnings);
            }
            catch (Exception e)
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
#endif
    }
}
