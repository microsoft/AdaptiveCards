using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace AdaptiveCards.Rendering
{
    public static class ContextExtension
    {
        public static object GetContext(this FrameworkElement element)
        {
            return element?.DataContext;
        }

        public static void SetContext(this FrameworkElement element, object value)
        {
            element.DataContext = value;
        }
    }
}
