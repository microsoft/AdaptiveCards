using System;
using System.Collections.Generic;
using System.Text;
#if WPF
using System.Windows;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering
{
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(FrameworkElement frameworkElement, AdaptiveCard originatingCard)
            : base(originatingCard)
        {
            _framworkElement = frameworkElement;
        }

        private FrameworkElement _framworkElement;
        /// <summary>
        /// The rendered result. If there were errors present, this will be null.
        /// </summary>
        public FrameworkElement
#if WPF
            FrameworkElement
#elif XAMARIN
            View
#endif
        => _framworkElement;

        /// <summary>
        /// Event handler for when user invokes an action.
        /// </summary>
        public event EventHandler<ActionEventArgs> OnAction;

        internal void InvokeOnAction(ActionEventArgs args)
        {
            OnAction?.Invoke(this, args);
        }
    }
}
