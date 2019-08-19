using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering.Forms
{
    public class AdaptiveRenderContext
    {

        public AdaptiveHostConfig Config { get; set; }

        public AdaptiveElementRenderers<View, AdaptiveRenderContext> ElementRenderers { get; set; }

        public View Render(AdaptiveTypedElement element)
        {
            View viewOut = null;

            try
            {

                if (viewOut == null)
                {
                    var renderer = ElementRenderers.Get(element.GetType());
                    if (renderer != null)
                    {
                        viewOut = renderer.Invoke(element, this);
                    }
                }
            }
            catch (AdaptiveFallbackException)
            {
            }

            return viewOut;
        }

        public Color GetColor(string colorCode)
        {
            return Color.FromHex(colorCode);
        }

    }
}
