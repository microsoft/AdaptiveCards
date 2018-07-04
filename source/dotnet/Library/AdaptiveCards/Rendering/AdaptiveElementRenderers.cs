using System;
using System.Collections.Generic;
using System.Reflection;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveElementRenderers<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        /// <summary>
        /// </summary>
        private readonly Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>> _dictionary 
            = new Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>>();

        /// <summary>
        /// </summary>
        /// <typeparam name="TElement"></typeparam>
        /// <param name="renderer"></param>
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

        public virtual bool TryRemove<TElement>( )
            where TElement : AdaptiveTypedElement
        { 
            if(!_dictionary.ContainsKey(typeof(TElement)))
                return false;
            _dictionary.Remove(typeof(TElement));
            return true;
        }

        public Func<TElement, TContext, TUIElement> Get<TElement>()
            where TElement : AdaptiveTypedElement
        {
            return Get(typeof(TElement));
        }

        public virtual bool TryGet<TElement>(out Func<AdaptiveTypedElement, TContext, TUIElement> element)
            where TElement : AdaptiveTypedElement =>
                TryGet(typeof(TElement),out element);

        public virtual bool TryGet(Type type, out Func<AdaptiveTypedElement, TContext, TUIElement> element)
        {
            bool _isAssignableFrom = typeof(AdaptiveAction).GetTypeInfo().IsAssignableFrom(type.GetTypeInfo());
            
            element = _dictionary.TryGetValue(type, out Func<AdaptiveTypedElement, TContext, TUIElement> _element) 
                ? _element : null;
            
            if (_isAssignableFrom && element is null)
                element = _dictionary.TryGetValue(typeof(AdaptiveAction), out Func<AdaptiveTypedElement, TContext, TUIElement> __element) ?
                    __element : null;
         
            return (element is null);
        }

        public Func<AdaptiveTypedElement, TContext, TUIElement> Get(Type type)
        {
            if (_dictionary.ContainsKey(type))
                return _dictionary[type];

            // For Actions we can render the base AdaptiveAction type
            if (typeof(AdaptiveAction).GetTypeInfo().IsAssignableFrom(type.GetTypeInfo()))
                return _dictionary[typeof(AdaptiveAction)];

            throw new ArgumentOutOfRangeException(nameof(type), $"Unable to locate renderer for {type}");
        }
    }
}
