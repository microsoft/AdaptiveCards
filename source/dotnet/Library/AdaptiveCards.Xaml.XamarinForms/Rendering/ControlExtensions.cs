using System;
using System.Collections.Generic;
using System.Text;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    public static class ControlExtensions
    {
        public static object GetContext(this View element)
        {
            return element?.BindingContext;
        }

        public static void SetContext(this View element, object value)
        {
            element.BindingContext = value;
        }

        public static void SetState(this Switch control, bool value)
        {
            control.IsToggled = value;
        }

        public static bool GetState(this Switch control)
        {
            return control.IsToggled;
        }

        public static void Add(this StackLayout control, View item)
        {
            control.Children.Add(item);
        }

        public static void SetColor(this Xamarin.Forms.TextBlock textBlock, string color, RenderContext context)
        {
            textBlock.TextColor = Color.FromHex(color);
        }

        public static void SetBackgroundColor(this Xamarin.Forms.View view, string color, RenderContext context)
        {
            view.BackgroundColor = Color.FromHex(color);
        }

        public static void SetHeight(this Xamarin.Forms.View view, double height)
        {
            view.HeightRequest = height;
        }

        public static void SetBackgroundColor(this ContentButton view, string color, RenderContext context)
        {
            view.BackgroundColor = Color.FromHex(color);
        }

        public static void SetBorderColor(this ContentButton view, string color, RenderContext context)
        {
            // view.Button.BorderColor = Color.FromHex(color);
        }

        public static void SetThickness(this ContentButton view, double thickness)
        {
            //view.Button.BorderWidth = thickness;
        }

        public static void SetFontWeight(this Xamarin.Forms.TextBlock text, int weight)
        {
            // text.font
        }
        public static void SetPlaceholder(this TextBox textBlock, string placeholder)
        {
            textBlock.Placeholder = placeholder;
        }

    }
}
