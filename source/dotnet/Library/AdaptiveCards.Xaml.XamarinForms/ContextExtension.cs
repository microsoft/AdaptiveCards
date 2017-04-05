using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    public static class ContextExtension
    {
        public static object GetContext(this Element element)
        {
            return element?.BindingContext;
        }

        public static void SetContext(this Element element, object value)
        {
            element.BindingContext = value;
        }
    }
}
