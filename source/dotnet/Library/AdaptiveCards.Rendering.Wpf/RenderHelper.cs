using System;
using UI = System.Windows.Controls;

namespace AdaptiveCards.Rendering.Wpf
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