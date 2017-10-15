using System;
using System.Windows;
using System.Windows.Controls;
#if WPF
using xaml = System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
using xaml = Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering.Wpf
{

    public class XamlUtilities
    {

        public static Button CreateActionButton(ActionBase action, RenderContext context)
        {
            ActionsConfig styling = context.Config.Actions;
            var uiButton = new Button()
            {
#if WPF
                HorizontalAlignment = System.Windows.HorizontalAlignment.Stretch,
#endif
            };

            uiButton.SetBackgroundColor(styling.BackgroundColor, context);
            uiButton.SetBorderColor(styling.BackgroundColor, context);
            uiButton.SetThickness(context.Config.Actions.BorderThickness);
            uiButton.Style = context.GetStyle($"Adaptive.{action.Type}");

            xaml.TextBlock uiTitle = new xaml.TextBlock()
            {
                Text = action.Title,                
                FontSize = styling.FontSize,
                Margin = new Thickness(8, 8, 8, 8) ,
            };
            uiTitle.SetFontWeight(styling.FontWeight);
            uiTitle.SetColor(styling.TextColor, context);
            uiTitle.Style = context.GetStyle($"Adaptive.Action.Title");
            uiButton.Content = uiTitle;
            string name = context.GetType().Name.Replace("Action", String.Empty);
            return uiButton;
            
        }

        /// <summary>
        /// Get fallback text from the speech element 
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static string GetFallbackText(CardElement cardElement)
        {
#if WPF
#pragma warning disable CS0618 // Type or member is obsolete
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
#pragma warning restore CS0618 // Type or member is obsolete
#elif XAMARIN
            // TODO: Xamarin fallback
#endif

            return null;
        }

    }
}