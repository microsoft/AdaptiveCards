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
    public class MissingInputException : Exception
    {
        public MissingInputException(string message, AdaptiveInput input, FrameworkElement frameworkElement)
            : base(message)
        {
            this.FrameworkElement = frameworkElement;
            this.AdaptiveInput = input;
        }

        public FrameworkElement FrameworkElement { get; set; }

        public AdaptiveInput AdaptiveInput { get; set; }
    }
}
