
using System.Windows;

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {


        /// <summary>
        /// Get fallback text from the speech element 
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        protected string GetFallbackText(CardElement cardElement)
        {
#if WPF
            if (!string.IsNullOrEmpty(cardElement.Speak))
            {

                // TODO: Fix xamarin fallback
                var doc = new System.Xml.XmlDocument();
                var xml = cardElement.Speak;
                if (!xml.Trim().StartsWith("<"))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Speak>{xml}</Speak>";
                else if (!xml.StartsWith("<?xml "))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n{xml}";
                doc.LoadXml(xml);
                return doc.InnerText;
            }
#endif

            return null;
        }

    }
}