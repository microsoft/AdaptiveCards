using System;
using System.Windows;

#if WPF

#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(FrameworkElement frameworkElement, AdaptiveCard originatingCard)
            : base(originatingCard)
        {
            _framworkElement = frameworkElement;
        }

        private readonly FrameworkElement _framworkElement;

        /// <summary>
        /// The rendered result. If there were errors present, this will be null.
        /// </summary>
        public FrameworkElement FrameworkElement => _framworkElement;


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
