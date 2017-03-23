using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Newtonsoft.Json.Linq;
using System;
using System.Xml;

namespace Adaptive
{

    public partial class ActionBase
    {
        protected Button CreateActionButton(RenderContext renderContext)
        {
            var uiButton = new Button();
            WPF.TextBlock uiTitle = new WPF.TextBlock() { Text = this.Title };
            uiTitle.Style = renderContext.GetStyle($"Adaptive.Action.Title");
            uiButton.Content = uiTitle;
            string name = this.GetType().Name.Replace("Action", String.Empty);
            uiButton.Style = renderContext.GetStyle($"Adaptive.Action.{name}");
            return uiButton;
        }

        /// <summary>
        /// Get fallback text from the speech element 
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public string GetFallbackText()
        {
            if (!string.IsNullOrEmpty(this.Speak))
            {
                XmlDocument doc = new XmlDocument();
                var xml = this.Speak;
                if (!xml.Trim().StartsWith("<"))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Speak>{xml}</Speak>";
                else if (!xml.StartsWith("<?xml "))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n{xml}";
                doc.LoadXml(xml);
                return doc.InnerText;
            }
            return null;
        }

    }
}