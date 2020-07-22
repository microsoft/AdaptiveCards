using System;
using System.Diagnostics;
using AdaptiveCards.Rendering.Wpf;
using Microsoft.MarkedNet;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;
using FrameworkElement = Xamarin.Forms.View;

namespace AdaptiveCards.Rendering
{

    public static partial class XamlTextBlock
    {
        public static Xamarin.Forms.TextBlock CreateControl(AdaptiveTextBlock textBlock, AdaptiveRenderContext context)
        {
            var uiTextBlock = new Xamarin.Forms.TextBlock();

            var text = RendererUtilities.ApplyTextFunctions(textBlock.Text, context.Lang);

            if (string.IsNullOrWhiteSpace(text))
            {
                uiTextBlock.Text = text;
            }
            else
            {
                try
                {
                    Marked marked = new Marked();

                    marked.Options.Renderer = new AdaptiveXamarinDialectXamlMarkdownRenderer();

                    marked.Options.Mangle = false;

                    marked.Options.Sanitize = true;

                    string parsed = marked.Parse(text);

                    const string xamlDec = "<?xml version=\"1.0\" encoding=\"utf-8\" ?><{0} xmlns=\"http://xamarin.com/schemas/2014/forms\" xmlns:x=\"http://schemas.microsoft.com/winfx/2009/xaml\">";

                    var labelDec = string.Format(xamlDec, "TextBlock");

                    string labelXaml = $"{labelDec}<TextBlock.FormattedText>{parsed}</TextBlock.FormattedText></TextBlock>";

                    var label = new TextBlock().LoadFromXaml(labelXaml);

                    uiTextBlock = label;
                }
                catch(Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                    Debug.WriteLine(ex.StackTrace);
                    uiTextBlock.Text = text;
                }
            }

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

            uiTextBlock.FontSize = context.Config.GetFontSize(textBlock.FontType, textBlock.Size);

            return uiTextBlock;
        }
    }
 
}
