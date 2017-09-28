using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class ElementRenderers<TUIElement, TContext> : Dictionary<Type, Func<TypedElement, TContext, TUIElement>>
        where TUIElement : class
        where TContext : class
    {
        public void Set<TElement>(Func<TypedElement, TContext, TUIElement> renderer)
        {
            this[typeof(TElement)] = renderer;
        }

        public void Remove<TElement>()
        {
            this.Remove(typeof(TElement));
        }
    }
}
