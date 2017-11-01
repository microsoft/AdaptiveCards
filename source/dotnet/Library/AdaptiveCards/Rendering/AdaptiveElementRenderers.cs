using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering
{
    public class AdaptiveActionHandlers
    {
        private readonly List<Type> _supportedActions = new List<Type>()
        {
            typeof(AdaptiveOpenUrlAction),
            typeof(AdaptiveSubmitAction),
            typeof(AdaptiveShowCardAction)
        };

        /// <summary>
        /// Adds support for a given action type. Any action in a payload not specifed here will be dropped from the rendered card
        /// </summary>
        public void AddSupportedAction<TAction>()
            where TAction : AdaptiveAction
        {
            _supportedActions.Add(typeof(TAction));
        }

        /// <summary>
        /// Remove support for an action type. This will prevent these actions from appearing in the rendered card
        /// </summary>
        public void RemoveSupportedAction<TAction>()
            where TAction : AdaptiveAction
        {
            _supportedActions.Remove(typeof(TAction));
        }

        /// <summary>
        /// Whether or not the action is supported by the renderer
        /// </summary>
        /// <returns></returns>
        public bool IsSupported(Type type)
        {
            return _supportedActions.Contains(type);
        }
    }

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
            // For AdaptiveActions we want to render the AdaptiveAction type
            if (typeof(AdaptiveAction).GetTypeInfo().IsAssignableFrom(type.GetTypeInfo()))
                return _dictionary[typeof(AdaptiveAction)];

            return _dictionary[type];
        }
    }
}
