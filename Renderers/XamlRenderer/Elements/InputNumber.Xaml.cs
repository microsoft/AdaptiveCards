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
    public partial class InputNumber
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<InputNumber, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// Input.Number
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            IntegerUpDown numberPicker = new IntegerUpDown();
            // numberPicker.ShowButtonSpinner = true;

            float value;
            if (float.TryParse(this.Value, out value))
                numberPicker.Value = Convert.ToInt32(value);

            float minValue;
            if (float.TryParse(this.Min, out minValue))
                numberPicker.Minimum = Convert.ToInt32(minValue);

            float maxValue;
            if (float.TryParse(this.Max, out maxValue))
                numberPicker.Maximum = Convert.ToInt32(maxValue);

            numberPicker.Watermark = this.Placeholder;
            numberPicker.Style = context.GetStyle("Adaptive.Input.Number");
            numberPicker.DataContext = this;
            context.InputControls.Add(numberPicker);
            return numberPicker;
        }
    }
}