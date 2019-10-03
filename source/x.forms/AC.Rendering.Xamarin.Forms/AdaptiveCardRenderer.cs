using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using Xamarin.Forms;
using Xamarin.Forms.PlatformConfiguration.iOSSpecific;

namespace AdaptiveCards.Rendering.Forms
{
    public class AdaptiveCardRenderer : AdaptiveCardRendererBase<View, AdaptiveRenderContext>
    {
        protected override AdaptiveSchemaVersion GetSupportedSchemaVersion()
        {
            return new AdaptiveSchemaVersion(1, 0);
        }

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
            ElementRenderers.Set<AdaptiveColumnSet>(AdaptiveColumnSetRenderer.Render);
            ElementRenderers.Set<AdaptiveColumn>(AdaptiveColumnRenderer.Render);
        }

        public static View RenderAdaptiveCardWrapper(AdaptiveCard card, AdaptiveRenderContext context)
        {
            Grid cardContainer = new Grid();

            AddContainerElements(cardContainer, card.Body, context);

            return cardContainer;
        }

        public static View RenderSeparator(Grid uiContainer, AdaptiveElement cardElement, AdaptiveRenderContext context)
        {
            if (cardElement.Spacing == AdaptiveSpacing.None && !cardElement.Separator)
            {
                return null;
            }

            var uiSep = new Grid();
            int spacing = context.Config.GetSpacing(cardElement.Spacing);

            SeparatorConfig sepStyle = context.Config.Separator;

            var margin = (spacing - sepStyle.LineThickness) / 2;
            uiSep.Margin = new Thickness(0, margin, 0, margin);
            uiSep.HeightRequest = (sepStyle.LineThickness);
            if (!string.IsNullOrWhiteSpace(sepStyle.LineColor))
            {
                uiSep.BackgroundColor = context.GetColor(sepStyle.LineColor);
            }
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiSep, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiSep);

            return uiSep;
        }

        public static View RenderSpacing(Grid uiContainer, AdaptiveElement cardElement, AdaptiveRenderContext context)
        {
            if (cardElement.Spacing == AdaptiveSpacing.None)
            {
                return null;
            }

            var uiSpa = new Grid();
            int spacing = context.Config.GetSpacing(cardElement.Spacing);
            uiSpa.HeightRequest = spacing;

            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiSpa, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiSpa);

            return uiSpa;
        }

        public static View RenderSpacingAndSeparator(Grid uiContainer, AdaptiveElement cardElement, AdaptiveRenderContext context)
        {
            if (cardElement.Separator && uiContainer.Children.Count > 0)
            {
                return RenderSeparator(uiContainer, cardElement, context);
            }
            else if (uiContainer.Children.Count > 0)
            {
                return RenderSpacing(uiContainer, cardElement, context);
            }

            return null;
        }

        public static void AddContainerElements(Grid uiContainer, IList<AdaptiveElement> elements, AdaptiveRenderContext context)
        {
            // Keeping track of the index so we don't have to call IndexOf function on every iteration
            int index = 0;
            foreach (var cardElement in elements)
            {
                index++;

                // each element has a row
                View uiElement = context.Render(cardElement);
                if (uiElement != null)
                {
                    RenderSpacingAndSeparator(uiContainer, cardElement, context);

                    RowDefinition rowDefinition = new RowDefinition() { Height = GridLength.Auto };
                    uiContainer.RowDefinitions.Add(rowDefinition);
                    Grid.SetRow(uiElement, uiContainer.RowDefinitions.Count - 1);
                    uiContainer.Children.Add(uiElement);
                }
            }
        }

        /// <summary>
        /// Renders an adaptive card.
        /// </summary>
        /// <param name="card">The card to render</param>
        public RenderedAdaptiveCard RenderCard(AdaptiveCard card)
        {
            if (card == null) throw new ArgumentNullException(nameof(card));
            RenderedAdaptiveCard renderCard = null;
            
            var context = new AdaptiveRenderContext()
            {
                Config = HostConfig ?? new AdaptiveHostConfig(),
                ElementRenderers = ElementRenderers,
            };

            var element = context.Render(card);

            renderCard = new RenderedAdaptiveCard(element, card, new List<AdaptiveWarning>(), null);

            return renderCard;
        }

    }
}
