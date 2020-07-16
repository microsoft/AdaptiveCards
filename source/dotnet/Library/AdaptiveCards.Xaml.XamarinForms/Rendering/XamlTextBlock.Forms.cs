using AdaptiveCards.Rendering.Wpf;
using Xamarin.Forms;

using FrameworkElement = Xamarin.Forms.View;

namespace AdaptiveCards.Rendering
{

    public static partial class XamlTextBlock
    {
        public static Xamarin.Forms.TextBlock CreateControl(AdaptiveTextBlock textBlock, AdaptiveRenderContext context)
        {
            var uiTextBlock = new Xamarin.Forms.TextBlock();
            uiTextBlock.Text = RendererUtilities.ApplyTextFunctions(textBlock.Text, "en");
            uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock");
            // TODO: confirm text trimming
            uiTextBlock.LineBreakMode = LineBreakMode.WordWrap;

            switch (textBlock.HorizontalAlignment)
            {
                case AdaptiveHorizontalAlignment.Left:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.Start;
                    break;

                case AdaptiveHorizontalAlignment.Center:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.Center;
                    break;

                case AdaptiveHorizontalAlignment.Right:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.End;
                    break;
            }

            uiTextBlock.TextColor = context.Resources.TryGetValue<Color>($"Adaptive.{textBlock.Color}");

            if (textBlock.Weight == AdaptiveTextWeight.Bolder)
                uiTextBlock.FontAttributes = FontAttributes.Bold;

            if (textBlock.Wrap == true)
                uiTextBlock.LineBreakMode = LineBreakMode.WordWrap;

            return uiTextBlock;
        }
    }
 
}
