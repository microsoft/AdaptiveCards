using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;

namespace AdaptiveCards.Rendering.Wpf
{
    public partial class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(FrameworkElement frameworkElement, AdaptiveCard originatingCard)
            : base(originatingCard)
        {
            FrameworkElement = frameworkElement;
        }

        /// <summary>
        /// The rendered result. If there were errors present, this will be null.
        /// </summary
        public FrameworkElement FrameworkElement { get; }

        internal Dictionary<string, Func<object>> InputBindings { get; set; } = new Dictionary<string, Func<object>>();

        /// <summary>
        /// If any modifications were done to the rendered card they will be reported here
        /// </summary>
        public IList<AdaptiveViolation> Warnings { get; internal set; } = new List<AdaptiveViolation>();


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
        public RenderedAdaptiveCardInputs GetUserInputs(InputValueMode mode)
        {
            return new RenderedAdaptiveCardInputs(this, mode);
        }
    }
}
