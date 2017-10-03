using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class ElementRenderers<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        private Dictionary<Type, Func<TypedElement, TContext, TUIElement>> _dictionary = new Dictionary<Type, Func<TypedElement, TContext, TUIElement>>();

        public void Set<TElement>(Func<TElement, TContext, TUIElement> renderer)
            where TElement : TypedElement
        {
            _dictionary[typeof(TElement)] = (typedElement, tContext) =>
            {
                return renderer((TElement)typedElement, tContext);
            };
        }

        public void Remove<TElement>()
            where TElement : TypedElement
        {
            _dictionary.Remove(typeof(TElement));
        }

        public Func<TElement, TContext, TUIElement> Get<TElement>()
            where TElement : TypedElement
        {
            return Get(typeof(TElement));
        }

        public Func<TypedElement, TContext, TUIElement> Get(Type type)
        {
            return _dictionary[type];
        }
    }
}
