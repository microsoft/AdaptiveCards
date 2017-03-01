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
    public partial class InputText
    {
        /// <summary>
        /// Override the renderer for this element
        /// </summary>
        public static Func<InputText, RenderContext, FrameworkElement> AlternateRenderer;

        /// <summary>
        /// Input.Text
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            var textBox = new WatermarkTextBox() { Text = this.Value };
            if (this.IsMultiline == true)
            {
                textBox.AcceptsReturn = true;
                textBox.TextWrapping = TextWrapping.Wrap;
                textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
            }
            if (this.MaxLength > 0)
                textBox.MaxLength = this.MaxLength;

            textBox.Watermark = this.Placeholder;
            textBox.Style = context.GetStyle($"Adaptive.Input.Text.{this.Style}");
            textBox.DataContext = this;
            context.InputControls.Add(textBox);
            return textBox;
        }
    }
}