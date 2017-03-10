using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Xceed.Wpf.Toolkit;

namespace Adaptive
{
    public partial class InputTime
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<InputTime, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// Input.Time
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            if (context.Options.SupportInteraction)
            {
                var timePicker = new TimePicker();
                DateTime value;
                if (DateTime.TryParse(this.Value, out value))
                    timePicker.Value = value;
                TimeSpan minValue;
                if (TimeSpan.TryParse(this.Min, out minValue))
                    timePicker.EndTime = minValue;
                TimeSpan maxValue;
                if (TimeSpan.TryParse(this.Max, out maxValue))
                    timePicker.EndTime = maxValue;
                timePicker.Watermark = this.Placeholder;
                timePicker.Style = context.GetStyle("Adaptive.Input.Time");
                timePicker.DataContext = this;
                context.InputControls.Add(timePicker);
                return timePicker;
            }
            else
            {
                var textBlock = new TextBlock() { Text = GetFallbackText() ?? this.Placeholder };
                return textBlock.Render(context);
            }

        }
    }
}