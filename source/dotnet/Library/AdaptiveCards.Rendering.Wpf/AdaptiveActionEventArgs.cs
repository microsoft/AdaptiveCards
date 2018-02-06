using System;

namespace AdaptiveCards.Rendering.Wpf
{
    public class AdaptiveActionEventArgs : EventArgs
    {
        public AdaptiveActionEventArgs(AdaptiveAction action)
        {
            Action = action;
        }

        /// <summary>
        /// The action that fired
        /// </summary>
        public AdaptiveAction Action { get; set; }
    }
}