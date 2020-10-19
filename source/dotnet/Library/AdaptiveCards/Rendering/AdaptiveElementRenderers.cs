// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Reflection;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Encapsulates information needed to map from element types to factory methods for instantiating them.
    /// </summary>
    /// <typeparam name="TUIElement">The base UI element type the renderer implements (e.g. "HTMLElement" or
    /// "FrameworkElement").</typeparam>
    /// <typeparam name="TContext">The type of the renderer context to use (e.g. "AdaptiveRenderContext").</typeparam>
    public class AdaptiveElementRenderers<TUIElement, TContext>
        where TUIElement : class
        where TContext : class
    {
        private readonly Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>> _dictionary = new Dictionary<Type, Func<AdaptiveTypedElement, TContext, TUIElement>>();

        /// <summary>
        /// Registers or replaces a factory method for the given element type.
        /// </summary>
        /// <param name="renderer">Factory method for instantiating an element object of type TElement.</param>
        /// <typeparam name="TElement">The type of the element object.</typeparam>
        public void Set<TElement>(Func<TElement, TContext, TUIElement> renderer)
            where TElement : AdaptiveTypedElement
        {
            _dictionary[typeof(TElement)] = (typedElement, tContext) => renderer((TElement)typedElement, tContext);
        }

        /// <summary>
        /// Removes the registration for the element type.
        /// </summary>
        /// <typeparam name="TElement">The type of element object to remove.</typeparam>
        public void Remove<TElement>()
            where TElement : AdaptiveTypedElement
        {
            _dictionary.Remove(typeof(TElement));
        }

        /// <summary>
        /// Gets the factory method for an element type.
        /// </summary>
        /// <typeparam name="TElement">The type of element object to get.</typeparam>
        /// <returns>The factory method for the element object of type TElement.</returns>
        public Func<TElement, TContext, TUIElement> Get<TElement>()
            where TElement : AdaptiveTypedElement
        {
            return Get(typeof(TElement));
        }

        /// <summary>
        /// Gets the factory method for an element type.
        /// </summary>
        /// <param name="type">The type of object for which to retrieve the factory method.</param>
        /// <returns>The factory method for the element object.</returns>
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
