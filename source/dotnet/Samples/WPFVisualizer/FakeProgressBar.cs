using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using AdaptiveCards;
using AdaptiveCards.Rendering.Wpf;

namespace WpfVisualizer
{
    public class FakeRating : AdaptiveTypedElement
    {
        public override string Type => "Rating";

        public double Rating { get; set; }
    }

    public static class FakeRatingRenderer
    {
        public static FrameworkElement Render(FakeRating rating, AdaptiveRenderContext context)
        {
            var tb = new TextBlock();
            tb.Text = "\u2606";
            return tb;
        }
    }
}
