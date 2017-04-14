using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public interface IRender<TUIElement, TContext>
    {
        TUIElement Render(TContext context);
    }
}
