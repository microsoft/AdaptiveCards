using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using UI = System.Windows.Controls;

namespace AdaptiveCards.Renderers
{
    public static class RenderHelper
    {
        public static void SetHorizontalAlignment(this UI.Image image, HorizontalAlignment alignment)
        {
            System.Windows.HorizontalAlignment a;
            if (Enum.TryParse(alignment.ToString(), out a))
                image.HorizontalAlignment = a;
        }
    }
}