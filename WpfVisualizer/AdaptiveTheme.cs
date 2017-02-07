using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace WpfVisualizer
{
    interface IAdaptiveTheme
    {
        Brush AccentColor { get; }
        Brush AttentionColor { get; }
        Brush DarkColor { get; }
        Brush LightColor { get; }
        Brush DefaultColor { get; }
        Brush GoodColor { get; }
        Brush WarningColor { get; }
    }

    class DefaultTheme : IAdaptiveTheme
    {
        // COLORS
        public Brush AccentColor { get { return Brushes.Blue; } }
        public Brush AttentionColor { get { return Brushes.Red; } }
        public Brush DarkColor { get { return Brushes.Black; } }
        public Brush LightColor { get { return Brushes.White; } }
        public Brush DefaultColor { get { return Brushes.Black; } }
        public Brush GoodColor { get { return Brushes.Green; } }
        public Brush WarningColor { get { return Brushes.Yellow; } }
    }
}
