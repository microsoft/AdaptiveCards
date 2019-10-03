using System;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering.Forms
{
    public static class AdaptiveTextBlockRenderer
    {

        public static View Render(AdaptiveTextBlock textBlock, AdaptiveRenderContext context)
        {
            Label label = new Label
            {
                Text = textBlock.Text
            };

            label.FontSize = context.Config.GetFontSize(textBlock.FontType, textBlock.Size);

            switch (textBlock.HorizontalAlignment)
            {
                case AdaptiveHorizontalAlignment.Center:
                    label.HorizontalTextAlignment = TextAlignment.Center;
                    break;
                case AdaptiveHorizontalAlignment.Right:
                    label.HorizontalTextAlignment = TextAlignment.End;
                    break;
                case AdaptiveHorizontalAlignment.Left:
                default:
                    label.HorizontalTextAlignment = TextAlignment.Start;
                    break;
            }

            return label;
        }

    }
}
