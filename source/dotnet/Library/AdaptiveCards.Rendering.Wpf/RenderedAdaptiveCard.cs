using System;
using System.Collections.Generic;
using System.Windows;

namespace AdaptiveCards.Rendering.Wpf
{
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(
            FrameworkElement frameworkElement,
            AdaptiveCard originatingCard,
            IList<AdaptiveWarning> warnings,
            IDictionary<string, Func<string>> inputBindings)
            : base(originatingCard, warnings)
        {
            FrameworkElement = frameworkElement;
            UserInputs = new RenderedAdaptiveCardInputs(inputBindings);
        }

        /// <summary>
        /// The rendered card
        /// </summary>
        public FrameworkElement FrameworkElement { get; }

        /// <summary>
        /// Event handler for when user invokes an action.
        /// </summary>
        public event TypedEventHandler<RenderedAdaptiveCard, AdaptiveActionEventArgs> OnAction;

        internal void InvokeOnAction(AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(this, args);
        }
    }
}
