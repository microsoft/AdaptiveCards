using System.Windows;
using System.Collections.Generic;
using System.Threading.Tasks;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Shapes;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using AsNum.XFControls;
using Xamarin.Forms;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering
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
            var uiColumn = new Grid();
            uiColumn.Style = this.GetStyle("Adaptive.Column");

            AddContainerElements(uiColumn, column.Items, null, context);

            if (column.SelectAction != null)
            {
                var uiButton = (Button)RenderAction(column.SelectAction, new RenderContext(this.actionCallback, this.missingDataCallback));
                if (uiButton != null)
                {
                    uiButton.Content = uiColumn;
                    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                    return uiButton;
                }
            }

            return uiColumn;
        }
    }
}