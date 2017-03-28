using System.Windows;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace AdaptiveCards.Renderers
{
    public partial class XamlRenderer
        : AdaptiveRenderer<FrameworkElement, RenderContext>
    {
        /// <summary>
        /// Render this element
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        protected override FrameworkElement Render(Column column, RenderContext context)
        {
            return this.Render((Container)column, context);
        }
    }
}