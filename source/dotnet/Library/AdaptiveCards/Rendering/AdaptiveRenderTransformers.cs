// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Class for transforming elements.
    /// </summary>
    /// <typeparam name="TUIElement"></typeparam>
    /// <typeparam name="TContext"></typeparam>
    public class AdaptiveRenderTransformers<TUIElement, TContext>
           where TUIElement : class
           where TContext : class
    {
        private readonly Dictionary<Type, Action<AdaptiveTypedElement, TUIElement, TContext>> _dictionary = new Dictionary<Type, Action<AdaptiveTypedElement, TUIElement, TContext>>();

        /// <summary>
        /// Register
        /// </summary>
        /// <typeparam name="TElement"></typeparam>
        /// <param name="transformer"></param>
        public void Register<TElement>(Action<TElement, TUIElement, TContext> transformer)
            where TElement : AdaptiveTypedElement
        {
            _dictionary[typeof(TElement)] = (typedElement, uiElement, context) => transformer((TElement)typedElement, uiElement, context);
        }

        /// <summary>
        /// Remove
        /// </summary>
        /// <typeparam name="TElement"></typeparam>
        public void Remove<TElement>()
            where TElement : AdaptiveTypedElement
        {
            _dictionary.Remove(typeof(TElement));
        }

        /// <summary>
        /// Apply
        /// </summary>
        /// <typeparam name="TElement"></typeparam>
        /// <param name="element"></param>
        /// <param name="uiElement"></param>
        /// <param name="context"></param>
        public void Apply<TElement>(TElement element, TUIElement uiElement, TContext context)
            where TElement : AdaptiveTypedElement
        {
            if (_dictionary.ContainsKey(element.GetType()))
                _dictionary[element.GetType()].Invoke(element, uiElement, context);
        }
    }
}
