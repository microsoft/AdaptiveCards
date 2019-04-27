// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Reflection;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveElementRenderers<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        private readonly Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>> _dictionary = new Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>>();

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
            // AdaptiveUnknownElements and AdaptiveUnknownActions don't have a renderer
            if (type == typeof(AdaptiveUnknownElement) || type == typeof(AdaptiveUnknownAction))
            {
                return null;
            }

            if (_dictionary.ContainsKey(type))
            {
                return _dictionary[type];
            }

            // For Actions we can render the base AdaptiveAction type
            if (typeof(AdaptiveAction).GetTypeInfo().IsAssignableFrom(type.GetTypeInfo()))
            {
                return _dictionary[typeof(AdaptiveAction)];
            }

            throw new ArgumentOutOfRangeException(nameof(type), $"Unable to locate renderer for {type}");
        }
    }
}
