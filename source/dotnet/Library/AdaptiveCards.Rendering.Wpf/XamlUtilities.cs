using System;
using System.Windows;
using System.Windows.Controls;
using xaml = System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{

    public class XamlUtilities
    {

        public static Button CreateActionButton(AdaptiveActionBase action, AdaptiveRenderContext context)
        {
            ActionsConfig styling = context.Config.Actions;
            var uiButton = new Button()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
            };

            uiButton.SetBackgroundColor(styling.BackgroundColor, context);
            uiButton.SetBorderColor(styling.BackgroundColor, context);
            uiButton.SetThickness(context.Config.Actions.BorderThickness);
            uiButton.Style = context.GetStyle($"Adaptive.{action.Type}");

            TextBlock uiTitle = new TextBlock()
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
        public static string GetFallbackText(AdaptiveElement adaptiveElement)
        {
#pragma warning disable CS0618 // Type or member is obsolete
            if (!string.IsNullOrEmpty(adaptiveElement.Speak))
            {
                var doc = new System.Xml.XmlDocument();
                var xml = adaptiveElement.Speak;
                if (!xml.Trim().StartsWith("<"))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Speak>{xml}</Speak>";
                else if (!xml.StartsWith("<?xml "))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n{xml}";
                doc.LoadXml(xml);
                return doc.InnerText;
            }
#pragma warning restore CS0618 // Type or member is obsolete

            return null;
        }

    }
}