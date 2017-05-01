
using AdaptiveCards.Rendering.Config;
using System;
using System.Linq;
using System.Windows;
#if WPF
using System.Windows.Controls;
using xaml = System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
{

    public class XamlUtilities
    {

        public static Button CreateActionButton(ActionBase action, RenderContext context)
        {
#if WPF
            ActionConfig styling = context.Config.Actions;
            var uiButton = new Button()
            {
                Background = context.GetColorBrush(styling.BackgroundColor),
                HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch,
                BorderBrush = context.GetColorBrush(styling.BorderColor),
                BorderThickness = new Thickness(context.Config.Actions.BorderThickness)
            };
            uiButton.Style = context.GetStyle($"Adaptive.{action.Type}");

            xaml.TextBlock uiTitle = new xaml.TextBlock()
            {
                Text = action.Title,
                FontWeight = FontWeight.FromOpenTypeWeight(styling.FontWeight),
                FontSize = styling.FontSize,
                Foreground = context.GetColorBrush(styling.TextColor),
                TextAlignment = TextAlignment.Center,
                Margin = new Thickness(styling.Padding.Left, styling.Padding.Top, styling.Padding.Right, styling.Padding.Bottom) ,
            };
            uiTitle.Style = context.GetStyle($"Adaptive.Action.Title");
            uiButton.Content = uiTitle;
            string name = context.GetType().Name.Replace("Action", String.Empty);
            return uiButton;

#elif XAMARIN
            var uiButton = new Button();
            // TODO: button styling
            uiButton.Text = action.Title;
            string name = context.GetType().Name.Replace("Action", String.Empty);
            uiButton.Style = context.GetStyle($"Adaptive.Action.{name}");
            return uiButton;
#endif
        }

        /// <summary>
        /// Get fallback text from the speech element 
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static string GetFallbackText(CardElement cardElement)
        {
#if WPF
            if (!string.IsNullOrEmpty(cardElement.Speak))
            {
                var doc = new System.Xml.XmlDocument();
                var xml = cardElement.Speak;
                if (!xml.Trim().StartsWith("<"))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Speak>{xml}</Speak>";
                else if (!xml.StartsWith("<?xml "))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n{xml}";
                doc.LoadXml(xml);
                return doc.InnerText;
            }
#elif XAMARIN 
            // TODO: Xamarin fallback
#endif

            return null;
        }

    }
}