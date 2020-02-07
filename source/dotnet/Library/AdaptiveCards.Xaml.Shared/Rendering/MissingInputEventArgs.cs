// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
#if WPF
using System.Windows;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    public class MissingInputEventArgs : EventArgs
    {
        public MissingInputEventArgs(AdaptiveInput input, FrameworkElement frameworkElement)
        {
            this.FrameworkElement = frameworkElement;
            this.AdaptiveInput = input;
        }

        public FrameworkElement FrameworkElement { get; private set; }

        public AdaptiveInput AdaptiveInput { get; private set; }
    }
}
