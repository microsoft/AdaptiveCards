using System;
using System.Windows;

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


        /// <summary>
        /// Event handler for when user invokes an action.
        /// </summary>
        public event EventHandler<AdaptiveActionEventArgs> OnAction;

        internal void InvokeOnAction(AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(this, args);
        }
    }
}
