using System;
using System.Collections.Generic;
using System.Windows;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Rendering.Wpf
{
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(FrameworkElement frameworkElement, AdaptiveCard originatingCard)
            : base(originatingCard)
        {
            FrameworkElement = frameworkElement;
        }

        /// <summary>
        /// The rendered result. If there were errors present, this will be null.
        /// </summary>
        public FrameworkElement FrameworkElement { get; }

        internal Dictionary<string, Func<object>> InputBindings { get; set; } = new Dictionary<string, Func<object>>();


        /// <summary>
        /// Event handler for when user invokes an action.
        /// </summary>
        public event TypedEventHandler<RenderedAdaptiveCard, AdaptiveActionEventArgs> OnAction;

        internal void InvokeOnAction(AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(this, args);
        }

        /// <summary>
        /// Gather the current values from any inputs on the card
        /// </summary>
        /// <returns></returns>
        public virtual JObject GetInputData()
        {
            var jObj = new JObject();
            foreach (var id in InputBindings.Keys)
            {
                var value = InputBindings[id]();
                if (value != null)
                {
                    jObj[id] = JToken.FromObject(value);
                }
            }
            return jObj;
        }
    }
}
