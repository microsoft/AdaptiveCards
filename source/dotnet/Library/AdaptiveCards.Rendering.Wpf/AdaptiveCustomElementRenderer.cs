using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveCustomElementRenderer
    {
        public static FrameworkElement Render(AdaptiveCustomElement customElement, AdaptiveRenderContext context)
        {
            try
            {
                if (customElement.ResolvedElement == null)
                {
                    context.Warnings.Add(new AdaptiveWarning(1, "Custom element resolution failed for " + customElement.Type));
                    return null;
                }

                return context.Render(customElement.ResolvedElement);
            }
            catch (Exception ex)
            {
                return new TextBlock()
                {
                    Text = ex.ToString(),
                    TextWrapping = TextWrapping.Wrap,
                    FontSize = 10
                };
            }
        }
    }
}
