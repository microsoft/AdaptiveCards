using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Adaptive
{
    public partial class TypedElement 
    {
        public virtual Task PreRender()
        {
            return Task.Delay(0);
        }

        public virtual FrameworkElement Render(RenderContext context)
        {
            return new Grid();
        }

    }
}
