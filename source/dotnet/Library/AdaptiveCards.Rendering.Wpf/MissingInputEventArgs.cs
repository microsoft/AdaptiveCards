// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Windows;

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
