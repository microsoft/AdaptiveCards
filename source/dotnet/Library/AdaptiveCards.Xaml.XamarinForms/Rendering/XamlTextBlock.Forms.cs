using System;
using System.Globalization;
using System.IO;
using System.Xml;
using MarkedNet;
using System.Collections.Generic;
using System.Linq;
#if WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{

    public static partial class XamlTextBlock
    {
        public static Xamarin.Forms.TextBlock CreateControl(TextBlock textBlock, RenderContext context)
        {
            var uiTextBlock = new Xamarin.Forms.TextBlock();
            uiTextBlock.Text = RendererUtilities.ApplyTextFunctions(textBlock.Text);
            uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock");
            // TODO: confirm text trimming
            uiTextBlock.LineBreakMode = LineBreakMode.TailTruncation;

            switch (textBlock.HorizontalAlignment)
            {
                case HorizontalAlignment.Left:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.Start;
                    break;

                case HorizontalAlignment.Center:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.Center;
                    break;

                case HorizontalAlignment.Right:
                    uiTextBlock.HorizontalTextAlignment = TextAlignment.End;
                    break;
            }

            uiTextBlock.TextColor = context.Resources.TryGetValue<Color>($"Adaptive.{textBlock.Color}");

            if (textBlock.Weight == TextWeight.Bolder)
                uiTextBlock.FontAttributes = FontAttributes.Bold;

            if (textBlock.Wrap == true)
                uiTextBlock.LineBreakMode = LineBreakMode.WordWrap;

            return uiTextBlock;
        }
    }
 
}
