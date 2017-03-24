using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Threading.Tasks;

namespace Adaptive
{
    public partial class Column
    {
        /// <summary>
        /// Render this element
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        public override FrameworkElement Render(RenderContext context)
        {
            if (AlternateRenderer != null)
                return AlternateRenderer(this, context);

            return base.Render(context);
        }

        public override async Task PreRender()
        {
            List<Task> tasks = new List<Task>();
            foreach (var item in this.Items)
                tasks.Add(item.PreRender());

            await Task.WhenAll(tasks.ToArray());
        }

    }
}