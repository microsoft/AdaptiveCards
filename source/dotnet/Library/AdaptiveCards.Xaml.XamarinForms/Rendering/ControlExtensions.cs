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
    }
}
