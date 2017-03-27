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

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(InputToggle input, RenderContext context)
        {

            if (this.Options.SupportInteraction)
            {
                var uiToggle = new CheckBox();
                uiToggle.Content = input.Title;
                uiToggle.IsChecked = input.Value == (input.ValueOn ?? "true");
                uiToggle.Style = this.GetStyle($"Adaptive.Input.Toggle");
                uiToggle.DataContext = input;
                context.InputControls.Add(uiToggle);
                return uiToggle;
            }
            else
            {
                Container container = new Container() { Separation = input.Separation };
                container.Items.Add(new TextBlock() { Text = GetFallbackText(input)});
                if (input.Value != null)
                {
                    container.Items.Add(new TextBlock()
                    {
                        Text = (input.Value == (input.ValueOn ?? "true")) ? input.ValueOn ?? "selected" : input.ValueOff ?? "not selected",
                        Color = TextColor.Accent,
                        Wrap = true
                    });
                }
                return Render(container, context);
            }

        }
    }

}