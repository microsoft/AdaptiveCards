using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveElementRenderers<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        private Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>> _dictionary = new Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>>();

        public void Set<TElement>(Func<TElement, TContext, TUIElement> renderer)
            where TElement : AdaptiveTypedElement
        {
            _dictionary[typeof(TElement)] = (typedElement, tContext) => renderer((TElement)typedElement, tContext);
        }

        public void Remove<TElement>()
            where TElement : AdaptiveTypedElement
        {
            _dictionary.Remove(typeof(TElement));
        }

        public Func<TElement, TContext, TUIElement> Get<TElement>()
            where TElement : AdaptiveTypedElement
        {
            return Get(typeof(TElement));
        }

        public Func<AdaptiveTypedElement, TContext, TUIElement> Get(Type type)
        {
            return _dictionary[type];
        }
    }
}
