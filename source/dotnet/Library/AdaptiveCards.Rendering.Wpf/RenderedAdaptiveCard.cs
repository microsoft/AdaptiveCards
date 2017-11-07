using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;

namespace AdaptiveCards.Rendering.Wpf
{
    public partial class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(FrameworkElement frameworkElement, AdaptiveCard originatingCard, IList<AdaptiveWarning> warnings)
            : base(originatingCard, warnings)
        {
            FrameworkElement = frameworkElement;
            UserInputs = new RenderedAdaptiveCardInputs(this);
        }

        /// <summary>
        /// The rendered result. If there were errors present, this will be null.
        /// </summary
        public FrameworkElement FrameworkElement { get; }

        internal Dictionary<string, Func<string>> InputBindings { get; set; } = new Dictionary<string, Func<string>>();

        /// <summary>
        /// Event handler for when user invokes an action.
        /// </summary>
        public event TypedEventHandler<RenderedAdaptiveCard, AdaptiveActionEventArgs> OnAction;

        internal void InvokeOnAction(AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(this, args);
        }

        /// <summary>
        /// Gather the current values from inputs on the card
        /// </summary>
        public RenderedAdaptiveCardInputs UserInputs { get; }
    }
}
